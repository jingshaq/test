#include "stdafx.h"
#include <atlbase.h>
#include <Windows.h>
#pragma warning(disable:4996)  
#include <Aclapi.h> 
#pragma comment (lib,"Advapi32.lib")


DWORD AddAceToObjectsSecurityDescriptor(
	LPTSTR pszObjName,          // name of object
	SE_OBJECT_TYPE ObjectType,  // type of object
	LPTSTR pszTrustee,          // trustee for new ACE
	TRUSTEE_FORM TrusteeForm,   // format of trustee structure
	DWORD dwAccessRights,       // access mask for new ACE
	ACCESS_MODE AccessMode,     // type of ACE
	DWORD dwInheritance         // inheritance flags for new ACE
)
{
	DWORD dwRes = 0;
	PACL pOldDACL = NULL, pNewDACL = NULL;
	PSECURITY_DESCRIPTOR pSD = NULL;
	EXPLICIT_ACCESS ea;

	if (NULL == pszObjName)
		return ERROR_INVALID_PARAMETER;

	// Get a pointer to the existing DACL.

	dwRes = GetNamedSecurityInfo(pszObjName, ObjectType,
		DACL_SECURITY_INFORMATION,
		NULL, NULL, &pOldDACL, NULL, &pSD);
	if (ERROR_SUCCESS != dwRes) {
		printf("GetNamedSecurityInfo Error %u\n", dwRes);
		goto Cleanup;
	}

	// Initialize an EXPLICIT_ACCESS structure for the new ACE. 

	ZeroMemory(&ea, sizeof(EXPLICIT_ACCESS));
	ea.grfAccessPermissions = dwAccessRights;
	ea.grfAccessMode = AccessMode;
	ea.grfInheritance = dwInheritance;
	ea.Trustee.TrusteeForm = TrusteeForm;
	ea.Trustee.ptstrName = pszTrustee;

	// Create a new ACL that merges the new ACE
	// into the existing DACL.

	dwRes = SetEntriesInAcl(1, &ea, pOldDACL, &pNewDACL);
	if (ERROR_SUCCESS != dwRes) {
		printf("SetEntriesInAcl Error %u\n", dwRes);
		goto Cleanup;
	}

	// Attach the new ACL as the object's DACL.

	dwRes = SetNamedSecurityInfo(pszObjName, ObjectType,
		DACL_SECURITY_INFORMATION,
		NULL, NULL, pNewDACL, NULL);
	if (ERROR_SUCCESS != dwRes) {
		printf("SetNamedSecurityInfo Error %u\n", dwRes);
		goto Cleanup;
	}

Cleanup:

	if (pSD != NULL)
		LocalFree((HLOCAL)pSD);
	if (pNewDACL != NULL)
		LocalFree((HLOCAL)pNewDACL);

	return dwRes;
}

void SetRegPrivilege()
{
	DWORD dwRet;

	// 下面这个字符串的值修改为想要进行权限操作的注册表项，注册表每一级的权限是不一样的，所以需要很具体地指定到某一级
	LPTSTR SamName = _T("MACHINE\\SOFTWARE\\TestNode1");
	PSECURITY_DESCRIPTOR pSD = NULL;
	PACL pOldDacl = NULL;
	PACL pNewDacl = NULL;
	EXPLICIT_ACCESS ea;
	HKEY hKey = NULL;


	// 获取主键的DACL 
	dwRet = GetNamedSecurityInfo(SamName, SE_REGISTRY_KEY, DACL_SECURITY_INFORMATION,
		NULL, NULL, &pOldDacl, NULL, &pSD);
	if (dwRet != ERROR_SUCCESS)
	{
		printf("GetNamedSecurityInfo Error: %d\n", dwRet);
		goto FreeAndExit;
	}

	// 创建一个ACE，允许Everyone完全控制对象，并允许子对象继承此权限 
	ZeroMemory(&ea, sizeof(EXPLICIT_ACCESS));
	BuildExplicitAccessWithName(&ea, _T("Administrators"), KEY_ALL_ACCESS, SET_ACCESS,
		SUB_CONTAINERS_AND_OBJECTS_INHERIT);

	// 将新的ACE加入DACL 
	dwRet = SetEntriesInAcl(1, &ea, pOldDacl, &pNewDacl);
	if (dwRet != ERROR_SUCCESS)
	{
		printf("SetEntriesInAcl Error: %d\n", dwRet);
		goto FreeAndExit;
	}

	// 更新SAM主键的DACL 
	dwRet = SetNamedSecurityInfo(SamName, SE_REGISTRY_KEY, DACL_SECURITY_INFORMATION,
		NULL, NULL, pNewDacl, NULL);
	if (dwRet != ERROR_SUCCESS)
	{
		printf("SetNamedSecurityInfo Error: %d\n", dwRet);
		goto FreeAndExit;
	}

	// 打开SAM的子键 
	dwRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\TestNode1"),
		0, KEY_ALL_ACCESS, &hKey);
	if (dwRet != ERROR_SUCCESS)
	{
		printf("RegOpenKeyEx Error: %d\n", dwRet);
		goto FreeAndExit;
	}

	printf("Open SAM Subkey Successfully.\n");

FreeAndExit:
	if (hKey) RegCloseKey(hKey);
	if (pNewDacl) LocalFree(pNewDacl);
	// 还原SAM主键的DACL 
	if (pOldDacl) SetNamedSecurityInfo(SamName, SE_REGISTRY_KEY, DACL_SECURITY_INFORMATION,
		NULL, NULL, pOldDacl, NULL);
	if (pSD) LocalFree(pSD);
	return;
}


int find_reg_key(HKEY hKey, LPCTSTR lpSubKey)
{
	HKEY hKeyRet;
	long lError;
#ifdef _WIN64  
	if (ERROR_SUCCESS == ::RegOpenKeyEx(hKey, lpSubKey, 0, KEY_READ | KEY_WOW64_64KEY, &hKeyRet))
#else
	if (ERROR_SUCCESS == ::RegOpenKeyEx(hKey, lpSubKey, 0, KEY_READ, &hKeyRet))
#endif
	{
		RegCloseKey(hKeyRet);
	}
	else
	{
		return -1;
	}
	return 0;
}

int create_reg_key(HKEY hKey, LPCTSTR lpSubKey)
{
	HKEY hKeyRet;
	TCHAR *sSubKey = NULL;
	TCHAR *sChildKey = NULL;
	long lLastError = ERROR_SUCCESS;
	TCHAR szKey[260] = { 0 };
	int flag = 0;

	sSubKey = (TCHAR *)malloc(sizeof(TCHAR) * 260);
	_tcscpy(sSubKey, lpSubKey);
	sChildKey = _tcstok(sSubKey, _T("\\"));
	while (sChildKey != NULL && sChildKey != _T(""))
	{
		if (flag > 0)
		{
			_tcscat(szKey, _T("\\"));
		}
		_tcscat(szKey, sChildKey);
		flag = 1;
		if (find_reg_key(hKey, szKey) != 0)
		{
			lLastError = RegCreateKey(hKey, szKey, &hKeyRet);
			RegCloseKey(hKeyRet);
		}
		if (ERROR_SUCCESS != lLastError)
			break;
		sChildKey = _tcstok(NULL, _T("\\"));
	}

	free(sSubKey);
	sSubKey = NULL;

	if (ERROR_SUCCESS != lLastError)
	{
		return -1;
	}
	return 0;
}


int get_reg_value(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData)
{
	HKEY hKeyRet;

#ifdef _WIN64  
	if (ERROR_SUCCESS == ::RegOpenKeyEx(hKey, lpSubKey, 0, KEY_READ | KEY_WOW64_64KEY, &hKeyRet))
#else
	if (ERROR_SUCCESS == ::RegOpenKeyEx(hKey, lpSubKey, 0, KEY_READ, &hKeyRet))
#endif
	{
		if (::RegQueryValueEx(hKeyRet, lpValueName, 0, lpType, lpData, lpcbData) != ERROR_SUCCESS)
		{
			::RegCloseKey(hKeyRet);
			return -1;
		}
	}
	::RegCloseKey(hKeyRet);
	return 0;
}

int set_reg_value(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName, DWORD dwType, const BYTE *lpData, DWORD cbData)
{
	HKEY hKeyRet;

#ifdef _WIN64  
	if (ERROR_SUCCESS == ::RegOpenKeyEx(hKey, lpSubKey, 0, KEY_SET_VALUE | KEY_WOW64_64KEY, &hKeyRet))
#else
	if (ERROR_SUCCESS == ::RegOpenKeyEx(hKey, lpSubKey, 0, KEY_READ, &hKeyRet))
#endif
	{
		if (ERROR_SUCCESS != ::RegSetValueEx(hKeyRet, lpValueName, 0, dwType, lpData, cbData))
		{
			return -1;
		}
	}
	::RegCloseKey(hKeyRet);
	return 0;
}

int delete_reg_value(HKEY hKey, LPCTSTR lpSubKey, LPCTSTR lpValueName)
{
	HKEY hKeyRet;

#ifdef _WIN64  
	if (ERROR_SUCCESS == ::RegOpenKeyEx(hKey, lpSubKey, 0, KEY_SET_VALUE | KEY_WOW64_64KEY, &hKeyRet))
#else
	if (ERROR_SUCCESS == ::RegOpenKeyEx(hKey, lpSubKey, 0, KEY_READ, &hKeyRet))
#endif
	{
		if (ERROR_SUCCESS != ::RegDeleteValue(hKeyRet, lpValueName))
		{
			::RegCloseKey(hKeyRet);
			return -1;
		}
	}
	::RegCloseKey(hKeyRet);
	return 0;
}

int delete_reg_key(HKEY hKey, LPCTSTR lpSubKey)
{
	if (ERROR_SUCCESS != ::RegDeleteKey(hKey, lpSubKey))
	{
		return -1;
	}
	return 0;
}


void test_find_reg_key(void)
{
	LPCTSTR lpSubKey = _T("SOFTWARE\\TestNode1\\configs\\test1");
	int ret = find_reg_key(HKEY_LOCAL_MACHINE, lpSubKey);
	if (ret == 0) 
	{
		printf("key exist!\n");
	}
	else 
	{
		printf("key not found!\n");
	}
}


void test_create_reg_key(void)
{
	LPCTSTR lpSubKey = _T("SOFTWARE\\TestNode1\\configs\\test1");
	int ret = create_reg_key(HKEY_LOCAL_MACHINE, lpSubKey);
	if (ret == 0)
	{
		printf("%s success!\n", __FUNCTION__);
	}
	else
	{
		printf("%s failed!\n", __FUNCTION__);
	}
}

void test_read_reg_dword(void)
{
	LPCTSTR lpSubKey = _T("SOFTWARE\\TestNode1\\GuestTools");
	LPCTSTR lpValueName = _T("installed");
	DWORD dwType = REG_DWORD;
	DWORD dwValue = 0;
	DWORD dwSize = sizeof(DWORD);
	int ret = get_reg_value(HKEY_LOCAL_MACHINE, lpSubKey, lpValueName, &dwType, (LPBYTE)(&dwValue), &dwSize);
	if (ret == 0)
	{
		printf("%s success!\n", __FUNCTION__);
	}
	else
	{
		printf("%s failed!\n", __FUNCTION__);
	}
	printf("dwType=%d, dwValue=%d, dwSize=%d\n", dwType, dwValue, dwSize);
}

void test_read_reg_sz(void)
{
	LPCTSTR lpSubKey = _T("SOFTWARE\\TestNode1\\configs\\test1");
	LPCTSTR lpValueName = _T("log_level");
	DWORD dwType = REG_SZ;
	TCHAR dwValue[20] = {0};
	char value[20] = { 0 };
	DWORD dwSize = sizeof(dwValue);
	int ret = get_reg_value(HKEY_LOCAL_MACHINE, lpSubKey, lpValueName, &dwType, (LPBYTE)dwValue, &dwSize);
	if (ret == 0)
	{
		printf("%s success!\n", __FUNCTION__);
	}
	else
	{
		printf("%s failed!\n", __FUNCTION__);
	}
	WideCharToMultiByte(CP_ACP, 0, dwValue, -1, value, 20, NULL, NULL);
	printf("dwType=%d, dwValue=%s, dwSize=%d\n", dwType, value, dwSize);
}

void test_write_reg_dword(void)
{
	LPCTSTR lpSubKey = _T("SOFTWARE\\TestNode1\\GuestTools");
	LPCTSTR lpValueName = _T("installed");
	DWORD dwType = REG_DWORD;
	DWORD dwValue = 12;
	DWORD dwSize = sizeof(DWORD);
	int ret = set_reg_value(HKEY_LOCAL_MACHINE, lpSubKey, lpValueName, dwType, (LPBYTE)(&dwValue), dwSize);
	if (ret == 0)
	{
		printf("%s success!\n", __FUNCTION__);
	}
	else
	{
		printf("%s failed!\n", __FUNCTION__);
	}
	printf("dwType=%d, dwValue=%d, dwSize=%d\n", dwType, dwValue, dwSize);
}

void test_write_reg_sz(void)
{
	LPCTSTR lpSubKey = _T("SOFTWARE\\TestNode1\\configs\\test1");
	LPCTSTR lpValueName = _T("log_level");
	DWORD dwType = REG_SZ;
	TCHAR dwValue[20] = _T("info");
	char value[20] = {0};
	DWORD dwSize = sizeof(dwValue);
	int ret = set_reg_value(HKEY_LOCAL_MACHINE, lpSubKey, lpValueName, dwType, (const BYTE *)dwValue, dwSize);
	if (ret == 0)
	{
		printf("%s success!\n", __FUNCTION__);
	}
	else
	{
		printf("%s failed!\n", __FUNCTION__);
	}
	WideCharToMultiByte(CP_ACP, 0, dwValue, -1, value, 20, NULL, NULL);
	printf("dwType=%d, dwValue=%s, dwSize=%d\n", dwType, value, dwSize);
}

void test_delete_reg_value(void)
{
	LPCTSTR lpSubKey = _T("SOFTWARE\\TestNode1\\configs\\test1");
	LPCTSTR lpValueName = _T("log_level");
	int ret = delete_reg_value(HKEY_LOCAL_MACHINE, lpSubKey, lpValueName);
	if (ret == 0)
	{
		printf("%s success!\n", __FUNCTION__);
	}
	else
	{
		printf("%s failed!\n", __FUNCTION__);
	}
}

void test_delete_reg_key(void)
{
	LPCTSTR lpSubKey = _T("SOFTWARE\\TestNode1\\configs\\test1");
	int ret = delete_reg_key(HKEY_LOCAL_MACHINE, lpSubKey);
	if (ret == 0)
	{
		printf("%s success!\n", __FUNCTION__);
	}
	else
	{
		printf("%s failed!\n", __FUNCTION__);
	}
}

int main()
{
	//test_create_reg_key();
	//test_find_reg_key();
	//test_read_reg_dword();
	//test_read_reg_sz();
	//test_write_reg_dword();
	//test_write_reg_sz();
	//test_delete_reg_value();
	//test_delete_reg_key();
	system("pause");
	return 0;
}

