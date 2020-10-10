#include"base_struct.h"
#include<stdio.h>
#include"fileopt.h"
#include<malloc.h>
#include<string.h>
float info_turn(record* rec_head)                                   //ͳ��ĿǰӪҵ�����סԺѺ��
{
	float sum;
	record* p = rec_head->next;
	if (p != NULL) {
		sum +=(p->tre.che.cost_check)+(p->tre.pil.cost_pill)+(p->tre.hos.cost_hos);
		p = p->next;
	}
	else return sum;
}

void alter_record(int tag_bat_1,record* rec_head)                   //���ղ���淶���޸����Ƽ�¼����Ϊ�޸�Ѻ���Ƿ���Ҫ�޸�������Ϣ��
{
	record* p = rec_head->next;
	int a = 1, m;
	m = tag_bat_1;
	while (a)
	{
		if ((p != NULL) && ((p->pat.tag_id) != m))
			p = p->next;
			if (p == NULL)
				printf("���޴���");
			if (p != NULL) {
				(p->tre.hos.deposit) = 0;                //��������������Ϣ���Ǹ������ϢNULL����0��
					printf("��������ȷ��Ѻ��");
					scanf("%d", &(p->tre.hos.deposit));      //�Ƿ���Ҫ�ж�Ѻ���ʽ?
			}
		printf("����������1���˳�����0");
		scanf("%d", &a);
		if (a = 0)
			return;
		else {
			printf("������Ҫ�޸���Ϣ�ĹҺ�");
			scanf("%d", &m);
		}/*if*/									
	}/*while*/
}

void alter_record_out_time(record* rec_head)                            //�޸ĳ�Ժʱ��
{
	record* p = rec_head;
	printf("������Ҫ�޸���Ϣ�ĹҺţ�");
	int m;
	scanf("%d", &m);
	while (p != NULL) 
	{
		if((p->num_check)==m)
		{
			printf("������Ҫ�ĳɵ����ڣ�");
			scanf("%s", &(p->out_doc));                            //����ʱ��Ϊɶ��char�ͣ�������int��
		}
	}

}

void delete_record(int tag_bat_1,record* rec_head)                            //ͨ���Һŵĺ��룬ɾ��������Ϣ
{
	int a = 1, m;
	m = tag_bat_1;
	while (a)
	{
		record* q = rec_head, * p = q->next;
		if ((p != NULL) && ((p->pat.tag_id) != m))
		{
			q = p;
				p = p->next;
		}
		if (p == NULL)
			printf("���޴���");
		else {
			p = p->next;
				free(q->next);
				q->next = p;
		}
		printf("����������1���˳�����0");
		scanf("%d", &a);
		if (a = 0)
			return;
		else {
			printf("������Ҫ�޸���Ϣ�ĹҺ�");
			scanf("%d", &m);
		}
	}
}

void print_time_record(int time1, int time2,record* rec_head)                        //��ӡĳ��ʱ���ڵ��������Ƽ�¼
{
	record* p = rec_head->next;                                          //�����ڵ㲢������λ��
	while(p != NULL){
		if ((p->tre.hos.time_start > time1) || (p->tre.hos.time_start == time1) || (p->tre.hos.time_start < time2))   //�ж�ʱ�䷶Χ����ӡ������Ϣ
			printf("%d", p->num_check);
		printf("%s\n%d\n%d\n", p->pat.name_pat, p->pat.age, p->pat.tag_id);                                          //������Ϣ
		printf("%s\n%s\n%d\n", p->doc.name_doc, p->doc.sub, p->doc.num_work);                         //ҽ����Ϣ
		int i; 
		for (i = 0;i < (p->tre.che.tag_check);i++)                                                                     //�����Ϣ
			printf("%s    %f    %d\n", p->tre.che.type[i], p->tre.che.cost_term[i], p->tre.che.cost_check);
		for (i = 0;i < (p->tre.pil.tag_pill);i++)                                                                      //��ҩ��Ϣ
			printf("%s    %f    %d    %f\n", p->tre.pil.name_pill[i], p->tre.pil.cost_perpill[i], p->tre.pil.num_pill[i], p->tre.pil.cost_pill);
		printf("%d    %d    %d\n", p->tre.hos.time_start, p->tre.hos.time_end, p->tre.hos.deposit);                   //�������
		if ((p->out_doc) != NULL)                                                                                     //��Ժ��Ϣ
			printf("%d", p->out_doc);                                                                                
		p = p->next;
	}/*while*/
}

void print_sub_record(record*rec_head)                                      //��ӡĳ������Ϣ
{
	printf("��������Ҫ��ӡ��Ϣ�Ŀ��ң�");
	char m[5];                                               //��������Ŀ��Һ�
	scanf("%s", &m);
	record* p = rec_head->next;
	while(p != NULL)
	{
		if (strcmp(p->doc.sub, m) == 0) {                    //�������Ҳ����������Ϣ
			printf("%d", p->num_check);
			printf("%s\n%d\n%d\n", p->pat.name_pat, p->pat.age, p->pat.tag_id);
			printf("%s\n%s\n%d\n", p->doc.name_doc, p->doc.sub, p->doc.num_work);
			int i;
			for (i = 0;i < (p->tre.che.tag_check);i++)
				printf("%s    %f    %d\n", p->tre.che.type[i], p->tre.che.cost_term[i], p->tre.che.cost_check);
			for (i = 0;i < (p->tre.pil.tag_pill);i++)
				printf("%s    %f    %d    %f\n", p->tre.pil.name_pill[i], p->tre.pil.cost_perpill[i], p->tre.pil.num_pill[i], p->tre.pil.cost_pill);
			printf("%d    %d    %d\n", p->tre.hos.time_start, p->tre.hos.time_end, p->tre.hos.deposit);
			if ((p->out_doc) != NULL)
				printf("%d", p->out_doc);

		}/*if*/
		p = p->next;
	}/*while*/
}

void print_doc_record(record* rec_head)                                                                   //��ӡĳҽ����ʷ������Ϣ�����ż���
{
	record* p = rec_head->next;
	printf("������Ҫ���ҵ�ҽ���Ĺ��ţ�");
	int m;
	scanf("%d", &m);
	while(p != NULL) 
	{
		if ((p->doc.num_work) == m)
		{
			printf("%d", p->num_check);
			printf("%s\n%d\n%d\n", p->pat.name_pat, p->pat.age, p->pat.tag_id);                                          //������Ϣ
			printf("%s\n%s\n%d\n", p->doc.name_doc, p->doc.sub, p->doc.num_work);                         //ҽ����Ϣ
			int i;
			for (i = 0;i < (p->tre.che.tag_check);i++)                                                                    //�����Ϣ
				printf("%s    %f    %d\n", p->tre.che.type[i], p->tre.che.cost_term[i], p->tre.che.cost_check);
			for (i = 0;i < (p->tre.pil.tag_pill);i++)                                                                      //��ҩ��Ϣ
				printf("%s    %f    %d    %f\n", p->tre.pil.name_pill[i], p->tre.pil.cost_perpill[i], p->tre.pil.num_pill[i], p->tre.pil.cost_pill);
			printf("%d    %d    %d\n", p->tre.hos.time_start, p->tre.hos.time_end, p->tre.hos.deposit);                   //�������
			if((p->out_doc) != NULL)                                                                                     //��Ժ���ڣ�û��Ժ�򲻴�ӡ
				printf("%d", p->out_doc);
		}/*if*/
		p = p->next;
	}/*while*/
}

void stat_doc_work()
{

}

void print_stat_pat(record* rec_head)                                  //��ӡסԺ���߱���
{
	record* p = rec_head;
	while(p != NULL)                    //��Ժ����Ϊ�����ӡ
	{
		if((p->out_doc) != NULL)
		printf("%s    %d    %d", p->pat.name_pat, p->pat.age, p->pat.tag_id);
		p = p->next;
	}
}