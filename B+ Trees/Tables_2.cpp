#include "stdafx.h"
/*#include<stdlib.h>
#include<string.h>
#include<malloc.h>

struct student
{
	int id;
	char name[32];
};

struct marks
{
	int stu_id;
	int smarks[4];
};

struct data_page_students
{
	char type = '1';
	char id;
	char unused[18];
	student students[3];
};

struct data_page_marks
{
	char id;
	char type = '1';
	char unused[6];
	marks stu_marks[6];
};

struct index_page
{
	char type = '2';
	char unused[3];
	int page_ids[16];
	int keys[15];
};

struct table_page
{
	char type = '3';
	char id;
	int root_page_id[10];
	char tablename[10][8];
	char unused[2];
};

student* get_record(index_page index, data_page_students* students, int search_index)
{
	int i = 0, j = 0;
	for (i = 0; i < 15; i++)
	{
		if (index.keys[i] > search_index - 1)
		{
			int k=index.page_ids[i]-1;
			for (j = 0; j < 3; j++)
			{
				if (search_index  == students[k].students[j].id)
					return &students[k].students[j];
			}
			return NULL;
		}
	}
	if (search_index - 1 < index.keys[14] + 3)
	{
		for (j = 0; j < 3; j++)
		{
			if (search_index  == students[15].students[j].id)
				return &students[15].students[j];
		}
	}
	return NULL;
}

void print_range(index_page index, data_page_students* students, int low, int high, char *str)
{
	int k = 0, l = 0;
	int i, j;
	for (i = 0; i < 15; i++)
	{
		if (index.keys[i] > low-1 && index.keys[i]-3 < high)
		{
			k = index.page_ids[i] - 1;
			for (j = 0; j < 3; j++)
			{
				if (students[k].students[j].id >= low && students[k].students[j].id <= high && strstr(students[k].students[j].name, str==NULL?"\0":str))
					printf("%d %s\n", students[k].students[j].id, students[k].students[j].name);
			}
		}
	}
	if (high >= index.keys[14] + 3)
	{
		for (j = 0; j < 3; j++)
		{
			if (students[15].students[j].id >= low && students[15].students[j].id <= high && strstr(students[15].students[j].name, str == NULL ? "\0" : str))
				printf("%d %s\n", students[15].students[j].id, students[15].students[j].name);
		}
	}
}

void print_inner_join(data_page_students *student_data, data_page_marks *marks_data)
{
	for (int i = 0; i < 48; i++)
	{
		int stu_index = i / 3;
		int stu_offset = i % 3;
		int mark_index = i / 6;
		int mark_offset = i % 6;
		int total = 0;
		printf("%d\t%s\t\t", student_data[stu_index].students[stu_offset].id, student_data[stu_index].students[stu_offset].name);
		for (int j = 0; j < 4; j++)
		{
			printf("%d\t", marks_data[mark_index].stu_marks[mark_offset].smarks[j]);
			total += marks_data[mark_index].stu_marks[mark_offset].smarks[j];
		}
		printf("%d\n", total);
	}
}

/*int main()
{
	index_page index_pages[2];
	table_page page;
	data_page_students students[16];
	data_page_marks marks[8];
	printf("%d %d %d %d ", sizeof(data_page_marks), sizeof(data_page_students), sizeof(table_page), sizeof(index_page));
	int i = 0, j = 0, k = 0;
	char dummy[150];
	FILE *fp = fopen("students.csv", "r");
	fgets(dummy, 150, fp);
	for (i = 0; i < 48; i++)
	{
		j = i / 3;
		k = i % 3;
		fscanf(fp, "%d,%[^,],%s", &students[j].students[k].id,students[j].students[k].name,dummy);
		students[j].unused[0] = '\0';
		students[j].id = j;
	}
	fclose(fp);
	printf("Read done for students!\n");
	fp = fopen("marks.csv", "r");
	fgets(dummy, 150, fp);
	for (i = 0; i < 48; i++)
	{
		j = i / 6;
		k = i % 6;
		fscanf(fp, "%d,%d,%d,%d,%d\n", &marks[j].stu_marks[k].stu_id, &marks[j].stu_marks[k].smarks[0], &marks[j].stu_marks[k].smarks[1], &marks[j].stu_marks[k].smarks[2], &marks[j].stu_marks[k].smarks[3]);
		marks[j].unused[0] = '\0';
	}
	fclose(fp);
	printf("Read done for marks!\n");
	for (i = 0; i < 16; i++)
	{
		index_pages[0].page_ids[i] = i + 1;
		if (i < 15)
			index_pages[0].keys[i] = 3 * (i + 1);
	}
	for (i = 0; i < 15; i++)
	{
		index_pages[1].page_ids[i] = i + 1;
		if (i < 14)
			index_pages[1].keys[i] = 6 * (i + 1);
	}
	page.id = 1;
	strcpy(page.tablename[0], "Students");
	page.root_page_id[0] = 16;
	strcpy(page.tablename[1], "Marks");
	page.root_page_id[1] = 32;
	fp = fopen("Data.dat", "wb");
	for (i = 0; i < 16; i++)
		fwrite(&students[i], sizeof(data_page_students), 1, fp);
	fwrite(&index_pages[0], sizeof(index_page), 1, fp);
	for (i = 0; i < 8; i++)
		fwrite(&marks[i], sizeof(data_page_marks), 1, fp);
	fwrite(&index_pages[1], sizeof(index_page), 1, fp);
	fwrite(&page, sizeof(table_page), 1, fp);
	fclose(fp);
	printf("Write done!\n");
	/*void* page_read=malloc(128);
	fp = fopen("Data.dat", "rb");
	i = 0;
	j = 0;
	printf("\nStudents:\n");
	while (fread(page_read, sizeof(data_page_students), 1, fp))
	{
		if (((data_page_students*)page_read)->type != '1')
			break;
		for (j = 0; j < 3; j++)
			printf("%d %s\n", ((data_page_students*)page_read)->students[j].id, ((data_page_students*)page_read)->students[j].name);
	}
	if (((index_page*)page_read)->type == '2')
	{
		printf("\nStudents index page:\nPage-ids: ");
		for (j = 0; j < 16; j++)
			printf("%d ", ((index_page*)page_read)->page_ids[j]);
		printf("\nKeys: ");
		for (j = 0; j < 15; j++)
			printf("%d ", ((index_page*)page_read)->keys[j]);
		printf("\n");
	}
	printf("\nMarks:\n");
	while (fread(page_read, sizeof(data_page_marks), 1, fp))
	{
		if (((data_page_marks*)page_read)->type != '1')
			break;
		for (j = 0; j < 6; j++)
		{
			printf("%d ", ((data_page_marks*)page_read)->stu_marks[j].stu_id);
			for (k = 0; k < 4; k++)
				printf("%d ", ((data_page_marks*)page_read)->stu_marks[j].smarks[k]);
			printf("\n");
		}
	}
	if (((index_page*)page_read)->type == '2')
	{
		printf("\nMarks index page:\nPage-ids: ");
		for (j = 0; j < 16; j++)
			printf("%d ", ((index_page*)page_read)->page_ids[j]);
		printf("\nKeys: ");
		for (j = 0; j < 15; j++)
			printf("%d ", ((index_page*)page_read)->keys[j]);
		printf("\n");
	}
	fread(page_read, sizeof(table_page), 1, fp);
	printf("\nTable_Name\tRoot Page ID\n");
	for (i = 0; i < 2; i++)
		printf("%s\t%d\n", ((table_page*)page_read)->tablename[i], ((table_page*)page_read)->root_page_id);
	
	while (1)
	{
		int row_id;
		printf("\n\nEnter row-id for search: ");
		scanf("%d", &row_id);
		student *result = get_record(index_pages[0], students, row_id);
		if (result == NULL)
			printf("Record not found!\n");
		else
			printf("ID: %d\nName:%s\n", result->id, result->name);
		printf("Search again(1/0)?: ");
		scanf("%d", &row_id);
		if (!row_id)
			break;
	}
	char a[5] = "a";
	print_range(index_pages[0], students, 2, 2, NULL);
	print_inner_join(students, marks);
	system("pause");
	return 0;
}*/