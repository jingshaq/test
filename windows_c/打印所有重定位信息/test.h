# define _CRT_SECURE_NO_WARNINGS
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
                                                                    //&&&
typedef unsigned char BYTE;											//&&&
typedef unsigned short WORD;											//&&&
typedef unsigned int DWORD;											//&&&
# define IMAGE_SIZEOF_SHORT_NAME 8										//&&&
# define IMAGE_NUMBEROF_DIRECTORY_ENTRIES    16							//&&&
                         											//&&&
typedef struct _IMAGE_DATA_DIRECTORY {
	DWORD   VirtualAddress;
	DWORD   Size;
}IMAGE_DATA_DIRECTORY;		//&&&
     															    //&&&
typedef struct _IMAGE_BASE_RELOCATION {
	DWORD   VirtualAddress;
	DWORD   SizeOfBlock;
}BASE_RELOCATION;	        //&&&
                                                                    //&&&
typedef struct _DOS_Header
{
	WORD e_magic;
	WORD e_cblp;
	WORD e_cp;
	WORD e_crlc;
	WORD e_aparhdr;
	WORD e_minalloc;
	WORD e_maxalloc;
	WORD e_ss;
	WORD e_sp;
	WORD e_csum;
	WORD e_ip;
	WORD e_cs;
	WORD e_lfarlc;
	WORD e_ovno;
	WORD e_res[4];
	WORD e_oeminfo;
	WORD e_res2[10];
	DWORD e_lfanew;
}DOS_Header;							//&&&
                                                                    //&&&
typedef struct _File_Header
{
	WORD		Machine;
	WORD		NumberOfSections;
	DWORD 	TimeDateStamp;
	DWORD	PointerToSymbolTable;
	DWORD	NumberOfSymbols;
	WORD		SizeOfOptionalHeader;
	WORD		Characteristics;
}File_Header;						//&&&
                                                                    //&&&
typedef struct _Optional_Header
{
	WORD    Magic;
	BYTE    MajorLinkerVersion;
	BYTE    MinorLinkerVersion;
	DWORD   SizeOfCode;
	DWORD   SizeOfInitializedData;
	DWORD   SizeOfUninitializedData;
	DWORD   AddressOfEntryPoint;
	DWORD   BaseOfCode;
	DWORD   BaseOfData;
	DWORD   ImageBase;
	DWORD   SectionAlignment;
	DWORD   FileAlignment;
	WORD    MajorOperatingSystemVersion;
	WORD    MinorOperatingSystemVersion;
	WORD    MajorImageVersion;
	WORD    MinorImageVersion;
	WORD    MajorSubsystemVersion;
	WORD    MinorSubsystemVersion;
	DWORD   Win32VersionValue;
	DWORD   SizeOfImage;
	DWORD   SizeOfHeaders;
	DWORD   CheckSum;
	WORD    Subsystem;
	WORD    DllCharacteristics;
	DWORD   SizeOfStackReserve;
	DWORD   SizeOfStackCommit;
	DWORD   SizeOfHeapReserve;
	DWORD   SizeOfHeapCommit;
	DWORD   LoaderFlags;
	DWORD   NumberOfRvaAndSizes;
	IMAGE_DATA_DIRECTORY DataDirectory[IMAGE_NUMBEROF_DIRECTORY_ENTRIES];
}Optional_Header;	     			//&&&
                                                                    //&&&
typedef struct _NT_Header
{
	DWORD			Signature;
	File_Header		FileHeader;
	Optional_Header	OptionalHeader;
}NT_Header;							//&&&
                                                                    //&&&
typedef struct _Section_Header
{
	BYTE Name[IMAGE_SIZEOF_SHORT_NAME];
	union {
		DWORD PhysicalAddress;
		DWORD VirtualSize;
	} Misc;
	DWORD VirtualAddress;
	DWORD SizeOfRawData;
	DWORD PointerToRawData;
	DWORD PointerToRelocations;
	DWORD PointerToLinenumbers;
	WORD NumberOfRelocations;
	WORD NumberOfLinenumbers;
	DWORD Characteristics;

}Section_Header;                   //&&&		
                                                                    //&&&
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


//为了兼容，有创建一个函数进行WORD类型的转换
DWORD RAV_TO_FOA17_2(WORD RAV, WORD *FOA, DWORD *FileAdd)
{
	DWORD ret = 0;

	DOS_Header *DosHeader = (DOS_Header *)FileAdd;
	NT_Header *NTHeader = (NT_Header *)((BYTE *)FileAdd + DosHeader->e_lfanew);
	Section_Header *SectionGroup = (Section_Header *)((BYTE *)NTHeader + sizeof(File_Header) + NTHeader->FileHeader.SizeOfOptionalHeader + 0x04);

	for (DWORD i = 0; i < NTHeader->FileHeader.NumberOfSections; i++)
	{
		if (RAV >= SectionGroup->VirtualAddress && RAV < SectionGroup->VirtualAddress + SectionGroup->Misc.VirtualSize)
		{
			*FOA = RAV - SectionGroup->VirtualAddress + SectionGroup->PointerToRawData;
			break;
		}
		SectionGroup++;
	}

	return ret;
}

DWORD RAV_TO_FOA17(DWORD RAV, DWORD *FOA, DWORD *FileAdd)
{
	DWORD ret = 0;

	DOS_Header *DosHeader = (DOS_Header *)FileAdd;
	NT_Header *NTHeader = (NT_Header *)((BYTE *)FileAdd + DosHeader->e_lfanew);
	Section_Header *SectionGroup = (Section_Header *)((BYTE *)NTHeader + sizeof(File_Header) + NTHeader->FileHeader.SizeOfOptionalHeader + 0x04);

	for (DWORD i = 0; i < NTHeader->FileHeader.NumberOfSections; i++)
	{
		if (RAV >= SectionGroup->VirtualAddress && RAV < SectionGroup->VirtualAddress + SectionGroup->Misc.VirtualSize)
		{
			*FOA = RAV - SectionGroup->VirtualAddress + SectionGroup->PointerToRawData;
			break;
		}
		SectionGroup++;
	}

	return ret;
}

DWORD FileLength17(void *Filepath, DWORD *length)
{
	DWORD ret = 0;

	FILE *pf = fopen(Filepath, "rb");
	if (pf == NULL)
	{
		ret = -1;
		printf("func fopen error !\n");
		return ret;
	}

	fseek(pf, 0, SEEK_END);
	*length = ftell(pf);
	fseek(pf, 0, SEEK_SET);

	fclose(pf);
	return ret;
}

DWORD FileRead17(void *Filepath, DWORD length, void **FileAdd)
{
	DWORD ret = 0;
	void *Add = NULL;

	FILE *pf = fopen(Filepath, "rb");
	if (pf == NULL)
	{
		ret = -2;
		printf("func fopen error !\n");
		return ret;
	}

	Add = malloc(length);
	if (Add == NULL)
	{
		ret = -3;
		printf("func malloc error !!\n");
		return ret;
	}

	memset(Add, 0, length);

	fread_s(Add, length, length, 1, pf);
	*FileAdd = Add;
	fclose(pf);

	return ret;
}

DWORD PrintReLoctionInformation(void *FileAdd)
{
	DWORD ret = 0;

	DOS_Header *DosHeader = (DOS_Header *)FileAdd;
	NT_Header *NTHeader = (NT_Header *)((BYTE *)FileAdd + DosHeader->e_lfanew);

	DWORD BaseRelocation_RAVAdd = NTHeader->OptionalHeader.DataDirectory[5].VirtualAddress;
	DWORD BaseRelocation_FOAAdd = 0;
	ret = RAV_TO_FOA17(BaseRelocation_RAVAdd, &BaseRelocation_FOAAdd, FileAdd);
	if (ret != 0)
	{
		printf("func RAV_TO_FOA error !\n");
		return ret;
	}

	//指向重定向表
	BASE_RELOCATION *BaseRelocation = (BASE_RELOCATION *)((BYTE *)FileAdd + BaseRelocation_FOAAdd);
	
	//如果重定向表的一个结构体大小的内存块都为零，跳出循环
	DWORD Index = 0;
	while (BaseRelocation->VirtualAddress != 0 && BaseRelocation->SizeOfBlock != 0)
	 {
		Index++;
		DWORD BaseReloc_RAV = BaseRelocation->VirtualAddress;
		DWORD BaseReloc_FOA = 0;
		ret = RAV_TO_FOA17(BaseReloc_RAV, &BaseReloc_FOA, FileAdd);
		if (ret != 0)
		{
			printf("func RAV_TO_FOA error !\n");
			return ret;
		}
		
		//计算需要重定向的块的数量
		DWORD NumberOfBlock = (BaseRelocation->SizeOfBlock - 0x8) / sizeof(WORD);

		printf("===================================================================\n");
		printf("BaseRelocation_RAV :%X			Index :%d\n", BaseReloc_RAV, Index);
		printf("BaseRelocation_FOA :%x			NumberOfBlock :%d\n", BaseReloc_FOA, NumberOfBlock); 
		printf("====================================================================\n");
		printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
		printf("序号：		RAV：		FOA：\n");

		for (int i = 0; i < NumberOfBlock; i++)
		{
			WORD AddData_RAV = *(WORD *)((BYTE *)BaseRelocation + 0x8 + sizeof(WORD) * i);
			WORD AddData_FOA = 0;
			//判断该数据是否有效
			if (AddData_RAV / 0x3000)
			{
				ret = RAV_TO_FOA17_2((AddData_RAV % 0x3000) + BaseReloc_RAV, &AddData_FOA, FileAdd);
				if (ret != 0)
				{
					printf("func RAV_TO_FOA error !\n");
					return ret;
				}
				printf("%d		%X		%X\n", i + 1, AddData_RAV % 0x3000, AddData_FOA % 0x3000);
			}
			else
			{
				printf("%d		填充数据\n", i + 1);
			}
		}
		BaseRelocation = (BASE_RELOCATION *)((BYTE *)BaseRelocation + BaseRelocation->SizeOfBlock);
	}

	return ret;
}