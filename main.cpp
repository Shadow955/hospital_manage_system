#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include"base_struct.h"
#include"fileopt.h"
#include"allfunc.h"

time_t t;

int main() {
	printf("��ǰʱ�䣺");
	char*T=gettime();
	char* year = getyear();
	printf("%s\n", T);

	if (!openfile())									//��ʼʱ��ִ���ļ����뺯��
		return 0;				

	pill_term* pill_head = link_pill();
	che_term* che_head = link_che();
	doctor* doc_head = link_doc();
	record* rec_head = read_and_link(doc_head);  //����Դ�ļ������е��������Ƽ�¼������һ������
	record* p;
	int number;
	printf("������Ҫִ�й��ܶ�Ӧ�����֣�\n");
	printf("1 : �������Ƽ�¼\n2 : �������Ƽ�¼\n");
	printf("3 : �鿴��ǰ������������Ƽ�¼\n");
	printf("4 : �鿴ҽԺ����ҽ���ͷ�æ�̶�\n5 : �鿴ҽԺӪҵ��\n");
	printf("6 : �������ҩƷ���۸�\n7 : ������м����Ŀ���۸�\n");
	printf("8 : ���ҺŲ������Ƽ�¼������\n");
	printf("9 : ���浱ǰϵͳ�е�������Ϣ\n0 : �˳�\n");
	while (EOF != scanf("%d", &number)&&number>0&&number<10)
	{
		p = FindEnd(rec_head);
		switch (number) 
		{
			case 1: 
				p->next=getrecord(doc_head, pill_head, che_head,p->num_check); break;  //¼�����Ƽ�¼
			case 2: 
				printf_number(rec_head); break;
			case 3: 
				stdprint(rec_head); break;
			case 4: 
				docprint(doc_head); break;
			case 5: 
				statistics(rec_head); break;  //ͳ��Ӫҵ��
			case 6: 
				pillprint(pill_head); break;
			case 7: 
				cheprint(che_head); break;
			case 8:
				search(rec_head,doc_head,pill_head,che_head); break;
			case 9: 
				save(rec_head); break;  //���浱ǰϵͳ�������Ϣ
			default: 
				break;
		}
		char* T = gettime();
		printf("��ǰʱ�䣺");
		printf("%s\n", T); 
		printf("������Ҫִ�й��ܶ�Ӧ�����֣�\n");
		printf("1 : �������Ƽ�¼\n2 : �������Ƽ�¼\n");
		printf("3 : �鿴��ǰ������������Ƽ�¼\n");
		printf("4 : �鿴ҽԺ����ҽ���ͷ�æ�̶�\n5 : �鿴ҽԺӪҵ��\n");
		printf("6 : �������ҩƷ���۸�\n7 : ������м����Ŀ���۸�\n");
		printf("8 : ���ҺŲ������Ƽ�¼������\n");
		printf("9 : ���浱ǰϵͳ�е�������Ϣ\n0 : �˳�\n");
	}
	freerec(rec_head);
	freedoc(doc_head);
	freepill(pill_head);
	freeche(che_head);
	return 0;
}

