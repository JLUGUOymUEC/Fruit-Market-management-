#include <stdio.h>
#include <String.h>
#include <math.h>
#include <iostream>
using namespace std;

typedef struct student {
	int number;
	int score;
	char name[50];
	struct student *next;
}LinkList;

int main()
{
	FILE *preadFile=fopen("C:\\Users\\shine\\Desktop\\cyuyan.txt", "r");
	if (preadFile == NULL) { printf("没有找到文件."); return 0; }
	LinkList *head= (LinkList*)malloc(sizeof(LinkList));
	head->next=NULL;
	while (!feof(preadFile))
	{

		LinkList *node = (LinkList*)malloc(sizeof(LinkList));
		node->next=NULL;
		fscanf(preadFile, "%d %d %s", &(node->number), &(node->score), (node->name));
		/*fscanf_s(preadFile, "%d", &(node->number));
		fscanf_s(preadFile, "%d", &(node->score));
		fscanf_s(preadFile, "%c", &(node->name));*/
		LinkList *pnode = head;
		int* i;
		while (pnode->next != NULL) {
			if (pnode->next->number > node->number)
			{
				node->next = pnode->next->next;
				pnode->next->next = node; 
				break;
			}
			else pnode = pnode->next;
		}
		if (pnode->next == NULL) { pnode->next = node; }
		
	}
	fclose(preadFile);
	LinkList *ppnode = head;
	while (ppnode->next != NULL) { 
		printf("%d\t%s\t%d", ppnode->next->number, ppnode->next->name, ppnode->next->score); 

		ppnode=ppnode->next;
	
	}

	return 0;
}
