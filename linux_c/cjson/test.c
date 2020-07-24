#include <stdio.h>
#include <stdlib.h>
#include "./cjson.h"

#define RT_SUCCESS "{\"message\":\"success!\",\"ret_code\":0}"

int main(void)
{
	cJSON *json = cJSON_Parse(RT_SUCCESS);
	cJSON_AddStringToObject(json, "key", "running"); 
	char *str = cJSON_Print(json);
	printf("%s\n", str);
	free(str);
	str=NULL;
	return 0;
}
