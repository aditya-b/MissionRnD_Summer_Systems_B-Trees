//// ConsoleApplication1.cpp : Defines the entry point for the console application.
////
#include "stdafx.h"
//#include<stdlib.h>
//#include<string.h>
//#include<malloc.h>
//
//struct student
//{
//	int id;
//	char name[32];
//};
//
//struct data_page
//{
//	student students[3];
//	char unused[20];
//};
//
//struct index_page
//{
//	int page_ids[16];
//	int keys[15];
//	char unused[4];
//};
//
//int main()
//{
//	index_page index_pages[17];
//	data_page data_pages[256];
//	int i = 0, j = 0,k = 0;
//	char dummy[150];
//	FILE *fp = fopen("students.csv", "r");
//	fgets(dummy, 150, fp);
//	for (i = 0; i < 768; i++)
//	{
//		j = i / 3;
//		k = i % 3;
//		fscanf(fp, "%d,%[^,],%s", &data_pages[j].students[k].id, &data_pages[j].students[k].name, dummy);
//		data_pages[j].unused[0] = '\0';
//	}
//	fclose(fp);
//	printf("Read done!\n");
//	fp = fopen("Data.dat", "wb");
//	for (i = 0; i < 256; i++)
//	{
//		fwrite(&data_pages[i], sizeof(data_page), 1, fp);
//	}
//	for (i = 0; i < 256; i++)
//	{
//		j = i / 16;
//		k = i % 16;
//		index_pages[j].page_ids[k] = i ;
//		if (k < 15)
//			index_pages[j].keys[k] = index_pages[j].page_ids[k]*3+3;
//	}
//	for (i = 0; i < 16; i++)
//	{
//		index_pages[16].page_ids[i] = i + 1;
//		if (i < 15)
//			index_pages[16].keys[i] = data_pages[(i+1) * 16].students[0].id;
//	}
//	for (i = 0; i < 17; i++)
//	{
//		fwrite(&index_pages[i], sizeof(data_page), 1, fp);
//	}
//	fclose(fp);
//	printf("Write done!\n");
//	data_page page;
//	fp = fopen("Data.dat", "rb");
//	i = 0;
//	j = 0;
//	while (i<256 && fread(&page, 128, 1, fp))
//	{
//		for (j = 0; j < 3; j++)
//			printf("%d %s\n", page.students[j].id, page.students[j].name);
//		i++;
//	}
//	i = 0;
//	index_page ipage;
//	while (fread(&ipage, 128, 1, fp))
//	{
//		printf("Index page-%d:\nPage-ids: ",i++);
//		for (j = 0; j < 16; j++)
//			printf("%d ", ipage.page_ids[j]);
//		printf("\nKeys: ");
//		for (j = 0; j < 15; j++)
//			printf("%d ", ipage.keys[j]);
//		printf("\n\n");
//	}
//	return 0;
//}
//
