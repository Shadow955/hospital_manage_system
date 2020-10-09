//modified by Nero on 9/29
#include<stdlib.h>
#include<stdio.h>
#include"base_struct.h"
#include<string.h>
#include"fileopt.h"
#include"allfunc.h"
FILE* infile;																//Դ�ļ�Ϊinfile�����ĺ������ļ�Ϊoutfile
//FILE* outfile;
/*********************************

���飺�Ƿ���Դ�ļ���ֱ�Ӳ�����
			  �д����۽��

*********************************/
int openfile() {															//�ļ����뺯��
	infile = fopen("test.txt", "a");							//��ȡ�ļ����ж��Ƿ�ɹ���
	if (infile == NULL)
	{
		printf("�ļ���ʧ�ܣ�����Դ�ļ���\n");		//��ʧ�ܽ����������ϲ�
		return 0;
	}
	else
	{
		printf("�ļ��򿪳ɹ���\n");
		return 1;
	}
}
record* read_and_link() 
{
	//record* rec_head;

	/***********************************************************

	ע�⣺��ʽ������ʱ���Ƿ���Ҫ���˻س����д���һ������

	************************************************************/


	record* rec_head = (record*)malloc(sizeof(record));		//����ͷ�ڵ�
	//rec_head->next = NULL;
	//record* rec_this = rec_head;								//������ǰ�ڵ�
	//record* tp;
	record* tp;
		//= (record*)malloc(sizeof(record));//Ĭ�Ͻ����½ڵ�
	//rec_head->next = tp;
	tp = rec_head;
	while (fscanf(infile, "%d", &tp->num_check) !=EOF)																//ѭ������ֱ���ļ�ĩβ
	{
		//tp = (record*)malloc(sizeof(record));//Ĭ�Ͻ����½ڵ�
		fscanf(infile, "%s%d%d"
			, &tp->pat.name_pat
			, &tp->pat.age
			, &tp->pat.tag_pat);
		fscanf(infile, "%s%s%s%d"
			, &tp->doc.name_doc
			, &tp->doc.level
			, &tp->doc.sub
			, &tp->doc.num_work);
		fscanf(infile, "%s", tp->out_doc);
			//fscanf(infile, "%s", tp->tre.che.type[0]);
		int i = 0, j = 0;
		while(1)//�ڶ���over֮ǰ��ѭ����������Ŀ���������
		{
			fscanf(infile, "%s", tp->tre.che.type[i]);
			if(strcmp("over", tp->tre.che.type[i]) != 0)
				break;
			fscanf(infile, "%f", tp->tre.che.cost_term[i]);
			i++;
		}
		while(1)//�ڶ���over֮ǰ��ѭ������ҩƷ����������
		{
			fscanf(infile, "%s", &tp->tre.pil.name_pill[j]);
			if (strcmp("over", tp->tre.pil.name_pill[j]) != 0)
				break;
			fscanf(infile, "%d%d"
				, &tp->tre.pil.cost_perpill[j]
				, &tp->tre.pil.num_pill[j]);
			j++;
		}
		fscanf(infile, "%d%d%d"									//����סԺ��Ϣ����
			, &tp->tre.hos.time_start
			, &tp->tre.hos.time_end
			, &tp->tre.hos.deposit);
	
		tp->next = (record*)malloc(sizeof(struct record));
		tp = tp->next;
	}
	//if (rec_head->next == NULL)
	//	rec_head = tp;
	tp = NULL;											//׼�������½ڵ�
	//rec_this->next = tp;
	//rec_this = tp;
	//fclose(infile);
	printf("�������ɹ���\n");
	return (rec_head);
	/****************************************

	���������Ƿ������ر��ļ����д�̽��

	***************************************/
}
void printf_number(record* rec_head) {
	int number1;//�������������
	printf("�����빦�ܶ�Ӧ�����֣�\n1:��ӡĳ����������Ϣ\n2:��ӡĳҽ��������Ϣ\n3:��ӡĳ������ʷ���Ƽ�¼\n4:��ӡĳ��ʱ���ڵ����Ƽ�¼");
	scanf("%d", &number1);
	switch (number1) {
	case 1: outsub_doc(rec_head); break;//��ӡĳ����������Ϣ
	case 2: outname_doc(rec_head); break;//��ӡĳҽ��������Ϣ
	case 3: outpatient_name(rec_head); break;//��ӡĳ������ʷ���Ƽ�¼
	case 4: outtime_limit(rec_head); break;//��ӡĳ��ʱ���ڵ����Ƽ�¼
	}
}

void stdprint(record* p)
{
	printf("%d %s %d %d\n"
		, p->num_check
		, p->pat.name_pat
		, p->pat.age
		, p->pat.tag_pat);
	printf("%s %s %s %d\n"
		, p->doc.name_doc
		, p->doc.level
		, p->doc.sub
		, p->doc.num_work);
	printf("%s", p->out_doc);
	//fscanf(infile, "%s", tp->tre.che.type[0]);
	int i = 0, j = 0;
	while (strcmp("over", p->tre.che.type[i]) != 0)//�ڶ���over֮ǰ��ѭ����������Ŀ���������
	{
		printf("%s %f", p->tre.che.type[i],p->tre.che.cost_term[i]);
		i++;
	}
	printf("\n");
	while (strcmp("over", p->tre.pil.name_pill[j]) != 0)//�ڶ���over֮ǰ��ѭ�����ҩƷ����������
	{
		printf("%s %f %d"
			, p->tre.pil.name_pill[j]
			, p->tre.pil.cost_perpill[j]
			, p->tre.pil.num_pill[j]);
		j++;
	}
	printf("\n");
	printf("%d %d %d"									//���סԺ��Ϣ����
		, p->tre.hos.time_start
		, p->tre.hos.time_end
		, p->tre.hos.deposit);
}