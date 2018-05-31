#include "stdafx.h"
//#include<stdlib.h>
//#include<string.h>
//
//struct student
//{
//	int id;
//	char name[32];
//};
//
//struct marks
//{
//	int stu_id;
//	int smarks[4];
//};
//
//struct data_page_students
//{
//	char type = '1';
//	char id;
//	char unused[18];
//	student students[3];
//};
//
//struct data_page_marks
//{
//	char id;
//	char type = '1';
//	char unused[6];
//	marks stu_marks[6];
//};
//
//struct index_page
//{
//	char type = '2';
//	char unused[3];
//	int page_ids[16];
//	int keys[15];
//};
//
//struct table_page
//{
//	char type = '3';
//	char id;
//	int root_page_id[10];
//	char tablename[10][8];
//	char unused[2];
//};
//
//struct page
//{
//	char free = '0';
//	char unused[7];
//	int last_access_tick = 0;
//	int page_id = 0;
//	char data_page[128];
//};
//
//struct memory_pool
//{
//	int time = 0;
//	page page_pool[4];
//};
//
//memory_pool* create_pool()
//{
//	printf("Initializing memory pool...");
//	memory_pool *mem_pool = (memory_pool*)malloc(sizeof(memory_pool));
//	mem_pool->time = 0;
//	for (int i = 0; i < 4; i++)
//	{
//		mem_pool->page_pool[i].free = '0';
//		mem_pool->page_pool[i].page_id = 0;
//		mem_pool->page_pool[i].last_access_tick = 0;
//		mem_pool->page_pool[i].page_id = 0;
//	}
//	return mem_pool;
//}
//
//page* allocate_page_pool(memory_pool** mem_pool, int id)
//{
//	int min=INT_MAX;
//	int lru = 0;
//	int free = 0;
//	for (int i = 0; i < 4; i++)
//	{
//		if ((*mem_pool)->page_pool[i].page_id == id && (*mem_pool)->page_pool[i].free == '0')
//		{
//			(*mem_pool)->page_pool[i].free = '1';
//			(*mem_pool)->page_pool[i].last_access_tick = (*mem_pool)->time + 1;
//			(*mem_pool)->time += 1;
//			(*mem_pool)->page_pool[i].page_id = id;
//			printf("Existing page allocated! Data exists!\n");
//			return &(*mem_pool)->page_pool[i];
//		}
//		if ((*mem_pool)->page_pool[i].free == '0' && (*mem_pool)->page_pool[i].last_access_tick < min)
//		{
//			lru = i;
//			min = (*mem_pool)->page_pool[i].last_access_tick;
//			free = 1;
//		}
//	}
//	if (free)
//	{
//		(*mem_pool)->page_pool[lru].free = '1';
//		(*mem_pool)->page_pool[lru].last_access_tick = (*mem_pool)->time + 1;
//		(*mem_pool)->time += 1;
//		(*mem_pool)->page_pool[lru].page_id = id;
//		return &(*mem_pool)->page_pool[lru];
//	}
//	return NULL;
//}
//
//void release_page_pool(memory_pool **mem_pool, int id)
//{
//	int flag=1;
//	for (int i = 0; i < 4; i++)
//	{
//		if ((*mem_pool)->page_pool[i].page_id == id)
//		{
//			(*mem_pool)->page_pool[i].free = '0';
//			printf("\nPage pool for id-%d is released successfully!\n",id);
//			flag = 0;
//		}
//	}
//	if (flag)
//		printf("Error:No page found to release!\n");
//}
//
//void stats(memory_pool **mem_pool)
//{
//	printf("Memory Pool Statistics:\n");
//	for (int i = 0; i < 4; i++)
//		printf("Page-id:%d\nStatus:%c\nLast used at %d\nMax page_size:%d\n\n", (*mem_pool)->page_pool[i].page_id, (*mem_pool)->page_pool[i].free, (*mem_pool)->page_pool[i].last_access_tick, sizeof((*mem_pool)->page_pool[i].data_page));
//}
//
//void operations(memory_pool **mem_pool)
//{
//	char command[20];
//	int pool_data;
//	page *page;
//	while (1)
//	{
//		printf("\nMEMMANAGER>");
//		fscanf(stdin, "%s %d", command, &pool_data);
//		if (!_strcmpi(command, "GETPOOL"))
//		{
//			page = allocate_page_pool(mem_pool, pool_data);
//			if (page == NULL)
//				printf("\nMemory busy! Please try again later\n");
//			else
//			{
//				FILE *fp = fopen("Data.dat", "rb");
//				int type;
//				printf("Page allocated for size of 128 bytes\n");
//				printf("1->Students\n2->Marks\nEnter Choice:");
//				scanf("%d", &type);
//				if (type == 1)
//				{
//					data_page_students *stu = (data_page_students*)(void*)page->data_page;
//					if (stu->students->id - 1 != (pool_data - 1) * 3)
//					{
//						fseek(fp, (pool_data - 1) * 128, SEEK_SET);
//						fread(page->data_page, 128, 1, fp);
//						printf("Data loaded to page!\n");
//					}
//					for (int i = 0; i < 3; i++)
//						printf("%d %s\n", stu->students[i].id, stu->students[i].name);
//				}
//				else if (type == 2)
//				{
//					data_page_marks *stu = (data_page_marks*)page->data_page;
//					if (stu->stu_marks->stu_id - 1 != (pool_data - 1) * 6)
//					{
//						fseek(fp, (16 + pool_data) * 128, SEEK_SET);
//						fread(page->data_page, 128, 1, fp);
//						printf("Data loaded to page!\n");
//					}
//					for (int i = 0; i < 6; i++)
//						printf("%d %d %d %d %d\n", stu->stu_marks[i].stu_id, stu->stu_marks[i].smarks[0], stu->stu_marks[i].smarks[1], stu->stu_marks[i].smarks[2], stu->stu_marks[i].smarks[3]);
//				}
//				else
//					printf("Invalid choice!");
//			}
//		}
//		else if (!_strcmpi("FREEPOOL", command))
//		{
//			release_page_pool(mem_pool, pool_data);
//		}
//		else if (!_strcmpi("STATS", command))
//		{
//			stats(mem_pool);
//		}
//		else if (!_strcmpi("EXIT", command))
//		{
//			exit(0);
//		}
//		else
//		{
//			printf("Error: Command not found!");
//			continue;
//		}
//	}
//}
//
//int main()
//{
//	memory_pool *mem_pool = create_pool();
//	if (mem_pool)
//	{
//		printf("\nMemory pool for 4 pages created successfully and is ready for use!\n");
//		printf("\nGETPOOL PAGE_ID: Allocates a pool for your page!\nFREEPOOL PAGE_ID: Release the allocated pool!\nSTATS: Get memory pool statistics\nEXIT: Exit application\n");
//		operations(&mem_pool);
//	}
//	else
//		printf("\nMemory pool initialization failed! Try again!\n");
//	system("pause");
//	return 0;
//}