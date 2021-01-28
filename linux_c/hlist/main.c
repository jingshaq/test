#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "hlist.h"

HLIST_HEAD(g_hlist_head);

struct data_node {
	int id;
	char name[32];
	struct hlist_node node;
};

void print_data(struct data_node* p_data)
{
	printf("id=%d, name=%s\n", p_data->id, p_data->name);
}

int main(int argc, char* argv[])
{
	int i;
	struct hlist_head *head;
	struct hlist_node *pos, *n;
	struct data_node *data;

	//初始化
	printf("init\n");
	INIT_HLIST_HEAD(&g_hlist_head);

	//插入
	printf("insert\n");
	for (i=0; i<10; i++) {
		data = (struct data_node *)malloc(sizeof(struct data_node));
		memset(data, 0, sizeof(struct data_node));
		data->id = 0;
		sprintf(data->name, "data-%d", i);
		hlist_add_head(&data->node, &g_hlist_head);
	}

	//遍历
	printf("traverse\n");
	hlist_for_each_entry(data, pos, &g_hlist_head, node) {
		print_data(data);
	}

	//删除
	printf("delete\n");
	hlist_for_each_entry_safe(data, pos, n, &g_hlist_head, node) {
		hlist_del(&data->node);
		free(data);
	}
	
	//遍历
	printf("traverse\n");
	hlist_for_each_entry(data, pos, &g_hlist_head, node) {
		print_data(data);
	}

	return 0;
}
