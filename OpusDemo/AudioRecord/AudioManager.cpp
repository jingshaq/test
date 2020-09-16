#include "stdafx.h"
#include "AudioManager.h"
#include "opus.h"
#include "logger.h"

#ifndef _min
#define _min(a,b)            (((a) < (b)) ? (a) : (b))
#endif //_min

OpusEncoder *encoder = NULL;
OpusDecoder *decoder = NULL;

CAudioManager::CAudioManager(IPlaybackEvent* pEvent)
	:m_pPlaybackEventHandler(pEvent)
{
	m_pFormat = NULL;
	m_nOffset = 0;
	int err;
	encoder = opus_encoder_create(48000, 2, OPUS_APPLICATION_AUDIO, &err);
	if (encoder == NULL || err != 0) {
		LOG_ERROR("Create encoder Error.");
	}
	if (encoder) {
		opus_encoder_ctl(encoder, OPUS_SET_VBR(0));//0:CBR, 1:VBR
	}

	decoder = opus_decoder_create(48000, 2, &err);
	if (decoder == NULL || err != 0) {
		LOG_ERROR("Create decoder Error.");
	}

}

CAudioManager::~CAudioManager()
{
	ClearData();
}

BOOL CAudioManager::StartCapture()
{
	BOOL bRet = m_capture.IsCapturing();
	if(!bRet)
	{
		if(m_capture.Initialize(this))
		{
			bRet = m_capture.Start();
		}
	}

	

	return bRet;
}

VOID CAudioManager::StopCapture()
{
	if(m_capture.IsCapturing())
	{
		m_capture.Stop();
		m_capture.Destroy();
	}
}

BOOL CAudioManager::IsCapturing() const
{
	return m_capture.IsCapturing();
}

BOOL CAudioManager::StartPlayback()
{
	BOOL bRet = m_render.IsRendering();

	if(!bRet)
	{
		if(m_render.Initialize(this))
		{
			bRet = m_render.Start();
		}
	}

	return bRet;
}

VOID CAudioManager::StopPlayback()
{
	if(m_render.IsRendering())
	{
		m_render.Stop();
		m_render.Destroy();
	}
}

BOOL CAudioManager::IsPlaybacking() const
{
	return m_render.IsRendering();
}

BOOL CAudioManager::CanPlay() const
{
	return !m_dataList.empty();
}

VOID CAudioManager::ClearData()
{
	LPBYTE p = (LPBYTE)m_pFormat;
	delete []p;
	m_pFormat = NULL;

	std::list<Audio_Data>::iterator itr = m_dataList.begin();
	while(itr != m_dataList.end())
	{
		Audio_Data& item = *itr;
		delete []item.pData;
		++itr;
	}
	m_dataList.clear();
}

VOID CAudioManager::OnCatpureStart(DWORD dwInterval)
{
	
}

VOID CAudioManager::OnCaptureStop()
{

}

VOID CAudioManager::OnAdjustCaptureFormat(WAVEFORMATEX* pFormat)
{
	ClearData();	

	INT nDataLen = sizeof(WAVEFORMATEX) + pFormat->cbSize;
	LPBYTE pData = new BYTE[nDataLen];
	if(pData != NULL)
	{
		memcpy_s(pData, nDataLen, pFormat, nDataLen);
		m_pFormat = (WAVEFORMATEX*)pData;
	}
}

VOID CAudioManager::OnCatpureData(LPBYTE pData, INT nDataLen)
{
	unsigned char outData[4000] = { 0 };
	int outDataSize = 4000;
	Audio_Data item;
	if(pData != NULL)
	{
		//debug opus
		LOG_DEBUG("nDataLen = %d", nDataLen);
		opus_int32 encode_size = opus_encode(encoder, (const opus_int16 *)pData, 480, outData, outDataSize);
		LOG_DEBUG("encode_size = %d", encode_size);
		item.nDataLen = encode_size;
		item.pData = new BYTE[encode_size];
		memcpy_s(item.pData, encode_size, outData, encode_size);
		m_dataList.push_back(item);
	}
}


VOID CAudioManager::OnRenderStart()
{
	m_nOffset = 0;
	m_itrCurrent = m_dataList.begin();
}

VOID CAudioManager::OnRenderStop()
{

}

VOID CAudioManager::OnAdjustRenderFormat(WAVEFORMATEX* pFormat)
{
	if(pFormat == NULL) return;

	INT nDataLen1 = sizeof(WAVEFORMATEX) + pFormat->cbSize;
	INT nDataLen2 = sizeof(WAVEFORMATEX) + m_pFormat->cbSize;
	if(nDataLen1 == nDataLen2)
	{
		memcpy_s(pFormat,nDataLen1,  m_pFormat, nDataLen2);
	}
	else
	{
		memcpy_s(pFormat,nDataLen1,  m_pFormat, sizeof(WAVEFORMATEX));
	}
}

VOID CAudioManager::OnGetRenderData(LPBYTE pData, INT nDataLen)
{
	INT nCopyed = 0;
	INT nNeedCopy = nDataLen;
	BOOL bEnd(FALSE);

	if(m_itrCurrent == m_dataList.end()) 
	{
		m_itrCurrent = m_dataList.begin();
		m_nOffset = 0;
	}

	//debug opus
	INT new_len;
	opus_int16 *pcm = new opus_int16[960];
	LOG_DEBUG("nDataLen------->%d", nDataLen);
	new_len = opus_decode(decoder, (const unsigned char *)(m_itrCurrent->pData), m_itrCurrent->nDataLen, (opus_int16 *)pcm, 480, 0);
	if (new_len <= 0) {
		LOG_ERROR("decode playback data error, new_len=%d", new_len);
	}
	LOG_DEBUG("new_len------->%d", new_len);
	char *pcmData = new char[480 * 2 * sizeof(opus_int16)];
	for (int i = 0; i < 2 * 480; ++i)
	{
		pcmData[i * 2] = pcm[i] & 0xFF;
		pcmData[i * 2 + 1] = (pcm[i] >> 8) & 0xFF;
	}
	delete[]pcm;
	delete[]m_itrCurrent->pData;
	m_itrCurrent->pData = (LPBYTE)pcmData;
	m_itrCurrent->nDataLen = 1920;

	while(nCopyed < nDataLen )
	{
		Audio_Data& item = *m_itrCurrent;
		INT nItemLeftDataLen = item.nDataLen - m_nOffset;
		INT nToCopy = _min(nNeedCopy, nItemLeftDataLen);
		if(nToCopy > 0)
		{
			memcpy_s(pData + nCopyed, nDataLen - nCopyed, item.pData + m_nOffset, nToCopy);
		}
		m_nOffset += nToCopy;
		nCopyed += nToCopy;
		nNeedCopy -= nToCopy;

		if(m_nOffset >= item.nDataLen)
		{
			++m_itrCurrent;
			m_nOffset = 0;

			if(m_itrCurrent == m_dataList.end())
			{
				bEnd = TRUE;
				break;
			}
		}
	}

	if(bEnd)
	{
		if(m_pPlaybackEventHandler != NULL)
		{
			m_pPlaybackEventHandler->OnPlaybackEnd();
		}
	}
}
