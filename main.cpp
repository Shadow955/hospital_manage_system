#define funds = 0;
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include"base_struct.h"
#include"fileopt.h"
#include"allfunc.h"
//
//char ch[] = { "123" };
//int c = atoi(ch);
//int k = 100;
//sprintf(ch, "%d", k);

time_t t;



int main() {

	printf("��ǰʱ�䣺");
	char*T=gettime();
	char* year = getyear();
	printf("%s\n", T);

	if (!openfile())									//��ʼʱ��ִ���ļ����뺯��
		return 0;				

	record* rec_head = read_and_link();  //����Դ�ļ������е��������Ƽ�¼������һ������
	record* p;
	pill_term* pill_head = link_pill();
	che_term* che_head = link_che();
	doctor* doc_head = link_doc();
	int number;
	printf("������Ҫִ�й��ܶ�Ӧ�����֣�\n");
	printf("1 : ¼�����Ƽ�¼\n2 : �޸����Ƽ�¼\n3 : ɾ�����Ƽ�¼\n");
	printf("4 : ��ӡ��Ϣ\n5 : ͳ��Ӫҵ�����סԺ���߱���\n");
	printf("6 : ͳ��ҽ���ĳ�������͹�����æ�̶�\n7 : ���浱ǰϵͳ�е�������Ϣ\n");
	printf("8 : �鿴��ǰ������������Ƽ�¼\n0 : �˳�\n");
	while (EOF!=scanf("%d", &number)&&number  !=  0)
	{
		p = FindEnd(rec_head);
		//p->next = (record*)malloc(sizeof(record));
		switch (number) 
		{
			case 1: 
				p->next=getrecord(doc_head, pill_head, che_head); break;  //¼�����Ƽ�¼
			case 2: 
				alter_record(rec_head); break;  //�޸����Ƽ�¼
			case 3: 
				del_record(rec_head); break;  //ɾ�����Ƽ�¼
			case 4: 
				printf_number(rec_head, pill_head, che_head, doc_head); break;  //ȷ�ϴ�ӡ��Ϣ
			case 5: 
				statistics(rec_head); break;  //ͳ��Ӫҵ��
			case 6: 
				float abc(struct record* head); break;  //ͳ��ҽ���ĳ�������͹�����æ�̶�
			case 7: 
				save(rec_head); break;  //���浱ǰϵͳ�������Ϣ
			case 8: 
				stdprint(rec_head);
		}
		printf("������Ҫִ�й��ܶ�Ӧ�����֣�\n");
		printf("1 : ¼�����Ƽ�¼\n2 : �޸����Ƽ�¼\n3 : ɾ�����Ƽ�¼\n");
		printf("4 : ��ӡ��Ϣ\n5 : ͳ��Ӫҵ�����סԺ���߱���\n");
		printf("6 : ͳ��ҽ���ĳ�������͹�����æ�̶�\n7 : ���浱ǰϵͳ�е�������Ϣ\n");
		printf("8 : �鿴��ǰ������������Ƽ�¼\n0 : �˳�\n");//������ֶ�Ӧ����
		printf("��ǰʱ�䣺");
		char* T = gettime();
		printf("%s\n", T);                     
	}
	//fclose(file_rec);
	//free(p);
}

