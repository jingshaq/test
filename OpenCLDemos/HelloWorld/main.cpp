#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CL/cl.h>                 // OpenCL 的头文件

int main()
{
	cl_platform_id *pPlatform;  // 平台数据结构数组，每个结构表示一个在主机上的 OpenCL 执行平台（执行设备）
	cl_uint nPlatform;
	cl_int i, err;
	char* extraInformation;     // 额外信息缓冲区
	size_t extraSize;           // 额外信息缓冲区大小
	bool supportICD = false;    // 记录主机是否支持 OpenCL Installable Client Driver (ICD)

								// platform工作的步骤：0、询问主机上有多少计算平台；1、为平台数据结构分配内存空间；2、初始化这些数据结构
	if (err = clGetPlatformIDs(2, NULL, &nPlatform) < 0)// 查询平台数，返回值非零说明调用错误，参数：1、需要的平台数上限；2、NULL 表查询平台总数；3、输出平台数的变量指针
	{
		perror("Couldn't find any pPlatform.");                             // 输出错误信息用的函数
		exit(1);
	}
	printf("Platform count: %d\n", nPlatform);

	pPlatform = (cl_platform_id*)malloc(sizeof(cl_platform_id) * nPlatform);// 创建主机数据结构
	clGetPlatformIDs(nPlatform, pPlatform, NULL);                           // 初始化结构

	for (i = 0; i < nPlatform; i++)                                         // 循环获取平台信息
	{
		if (err = clGetPlatformInfo(pPlatform[i], CL_PLATFORM_EXTENSIONS, 0, NULL, &extraSize) < 0) // 获取额外信息，第五个参数为信息长度
		{
			perror("Couldn't read extension data.");
			exit(1);
		}
		printf("\nExtension data size: %d\n", extraSize);

		extraInformation = (char*)malloc(extraSize);                                                // 输出信息缓存
		clGetPlatformInfo(pPlatform[i], CL_PLATFORM_EXTENSIONS, extraSize, extraInformation, NULL); // 获取相关信息，第二参数为信息内容，这里是OpenCL支持的扩展功能信息
		printf("Platform %d supports extensions: %s\n", i, extraInformation);
		if (strstr(extraInformation, "cl_khr_icd") != NULL)                                         // 检查是否支持 ICD，支持则输出平台编号
		{
			printf("\nPlatform %d supports ICD extension.\n", i);
			supportICD = true;
		}
		clGetPlatformInfo(pPlatform[i], CL_PLATFORM_NAME, extraSize, extraInformation, NULL);       // 产商名
		printf("Platform %d name: %s\n", i, extraInformation);
		clGetPlatformInfo(pPlatform[i], CL_PLATFORM_VENDOR, extraSize, extraInformation, NULL);     // 供应商名
		printf("Platform %d vendor: %s\n", i, extraInformation);
		clGetPlatformInfo(pPlatform[i], CL_PLATFORM_VERSION, extraSize, extraInformation, NULL);    // OpenCL版本
		printf("Platform %d version: %s\n", i, extraInformation);
		clGetPlatformInfo(pPlatform[i], CL_PLATFORM_PROFILE, extraSize, extraInformation, NULL);    // 完整模式 / 嵌入式
		printf("Profile: %s\n", extraInformation);
		free(extraInformation);
	}
	if (!supportICD)
		printf("\nNo platform support ICD extension.\n");
	free(pPlatform);
	getchar();
	return 0;
}