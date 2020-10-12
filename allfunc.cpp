#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include"base_struct.h"
#include"allfunc.h"
#include"fileopt.h"

int year = 2020;
float sumcheck(int tag_check,float cost_term[])              //�������ܷ��ú���
{
	int i ;
	float sum = 0;
	for (i = 0; i < tag_check; i++)
	{
		sum = sum + cost_term[i];
	}
	return sum;
}

float sumpill(int tag_pill, float cost_perpill[30], int num_pill[30])        //����ҩƷ�ܷ��ú���
{
	int i, j;
	float sum = 0;
	j = tag_pill;
	for (i = 0; i < j; i++)
	{
		sum = sum + ((cost_perpill[i]) * (num_pill[i]));
	}
	return (float)sum;
}

int date_turn(char a[8])                 //��8λ����ת��Ϊ����
{
	int mon, day, tag; tag = 0;
	mon = (int)((a[0] * 10) + a[1]);
	day = (int)((a[2] * 10) + a[3]);
	switch (mon)
	{
	case 1:tag = day;
	case 2:tag = day + 31;
	case 3:tag = day + 59;
	case 4:tag = day + 90;
	case 5:tag = day + 120;
	case 6:tag = day + 151;
	case 7:tag = day + 181;
	case 8:tag = day + 212;
	case 9:tag = day + 243;
	case 10:tag = day + 273;
	case 11:tag = day + 304;
	case 12:tag = day + 334;
	}
	return tag;
}

int days_hosp(int time_start, int time_end)                  //����סԺʱ������
{
	char ch1[8], ch2[8];
	char x, y;
	int durtime;
	sprintf(ch1, "%d", time_start);
	sprintf(ch2, "%d", time_end);
	x = date_turn(ch1);
	y = date_turn(ch2);
	durtime = (((int)x) - ((int)y));
	return durtime;
}

int cost_hos(int a,int b,int c)           //סԺ���ú���
{
	int sum = 0;
	sum = sum + a + b + (c * 100);
	return sum;
}

record* getrecord(doctor* doc,pill_term* pill,che_term* che)    //¼���¼
{
	record* temp = (record*)malloc(sizeof(record));
	temp->next = NULL;
	printf("������Һ�\n");
	scanf("%d", &(temp->num_check));
	printf("\n����Ϊ���뻼����Ϣ��ÿ����Ϣ�Իس�����\n\n�����뻼��������\n");
	scanf("%s", &(temp->pat.name_pat));getchar();
	printf("�Ա�\n");
	scanf("%s", temp->pat.sex);getchar();
	printf("���䣺\n");
	scanf("%d", &temp->pat.age);
	printf("���֤�ź���λ��\n");
	scanf("%s", temp->pat.tag_id);getchar();
	//printf("\n����Ϊ����ҽ����Ϣ��ÿ����Ϣ�Իس�����\n\n����������ҽ��������\n");
	//scanf("%s",&(temp->doc.name_doc));getchar();
	//printf("ҽ������\n");
	//scanf("%s", temp->doc.level);getchar();
	//printf("ҽ�����ң�\n");
	//scanf("%s", temp->doc.sub);getchar();
	printf("ҽ�����ţ�\n");
	scanf("%d", &temp->doc.num_work);getchar();
	doctor* tpdoc = judge_num_work(temp->doc.num_work, doc);
	while (tpdoc == NULL)
	{
		printf("���Ų����ڣ��������������\n");
		scanf("%d", &temp->doc.num_work); getchar();
		tpdoc = judge_num_work(temp->doc.num_work, doc);
	}
	strcpy(temp->doc.name_doc, tpdoc->name_doc);
	strcpy(temp->doc.level, tpdoc->level);
	strcpy(temp->doc.sub, tpdoc->sub);
	/*printf("�������ʱ�䣺\n");
	scanf("%s", temp->out_doc);getchar();*/
	strcpy(temp->out_doc , gettime());
	printf("����������鼰�����,���롰#���Խ���\n");
	(temp->tre.che.tag_check) = 0; 
	bool flag_che = true; 
	int i = 0;
	while(flag_che)
	{
		printf("��������Ŀ���ƣ�\n");
		scanf("%s", &(temp->tre.che.type[i]));
		if (strcmp("#", temp->tre.che.type[i])==0)
		{
			flag_che = false;
			(temp->tre.che.cost_check) = sumcheck((temp->tre.che.tag_check), (temp->tre.che.cost_term));
			break;
		}
		else {
			che_term* tpche = judge_che_name(temp->tre.che.type[i],che);
			while (tpche==NULL) 
			{
				printf("�ü����Ŀ�����ڣ��������������");
				scanf("%s", &(temp->tre.che.type[i]));
				if (strcmp("#", temp->tre.che.type[i]) == 0)
				{
					flag_che = false;
					(temp->tre.che.cost_check) = sumcheck((temp->tre.che.tag_check), (temp->tre.che.cost_term));
					break;
				}
				tpche = judge_che_name(temp->tre.che.type[i], che);
			}
			temp->tre.che.cost_term[i] = tpche->che_price;
		}
		//printf("�����������ã�\n");
		//scanf("%f", &(temp->tre.che.cost_term[i]));
		(temp->tre.che.tag_check)++;
		i++;
	}
	printf("�������ҩƷ���Ƽ��������͵���,���롰#���Խ���\n");
	(temp->tre.pil.tag_pill) = 0; 
	bool flag_pil = true; 
	i = 0;
	while (flag_pil)
	{
		printf("����ҩƷ���ƣ�\n");
		scanf("%s", temp->tre.pil.name_pill[i]);
		if (strcmp("#", temp->tre.pil.name_pill[i])==0)
		{
			flag_pil = false;
			(temp->tre.pil.cost_pill) = sumpill(temp->tre.pil.tag_pill, temp->tre.pil.cost_perpill, temp->tre.pil.num_pill);
			break;
		}
		else
		{
			pill_term* tppill = judge_pill_name(temp->tre.pil.name_pill[i], pill);
			while (tppill==NULL)
			{
				printf("��ҩƷ�������ڣ��������������");
				scanf("%s", temp->tre.pil.name_pill[i]);
				if (strcmp("#", temp->tre.pil.name_pill[i]) == 0)
				{
					flag_pil = false;
					(temp->tre.pil.cost_pill) = sumpill(temp->tre.pil.tag_pill, temp->tre.pil.cost_perpill, temp->tre.pil.num_pill);
					break;
				}
				tppill = judge_pill_name(temp->tre.pil.name_pill[i], pill);
			}
			temp->tre.pil.cost_perpill[i] = tppill->pill_price;
		}
		//printf("����ҩƷ���ۣ�\n");
		//scanf("%f", &(temp->tre.pil.cost_perpill[i]));
		printf("����ҩƷ������\n");
		scanf("%d", &temp->tre.pil.num_pill[i]);
		(temp->tre.pil.tag_pill)++;
		i++;
	}
	printf("\n�����뿪ʼסԺʱ�䣺\n");
	scanf("%04d", &(temp->tre.hos.time_start));
	printf("\n������Ԥ�Ƴ�Ժʱ�䣺\n");
	scanf("%04d", &(temp->tre.hos.time_end));
	printf("\n���������סԺѺ��\n");
	scanf("%d",&(temp->tre.hos.deposit));
	(temp->tre.hos.days_hos) = days_hosp(temp->tre.hos.time_start, temp->tre.hos.time_end);
	printf("\n���Ƽ�¼¼��ɹ���\n");
	return temp;
}

void outpatient_tag(struct record* head)   //���һ������֤�Ų����
{
	char tag_in[5];
	printf("�����뻼�����֤����λ��\n");
	scanf("%s", tag_in);
	record* p = head;
	while (p!= NULL)
	{
		if (strcmp(tag_in, p->pat.tag_id) == 0)
		{
			singleprint(p);
			p = p->next;
		}
		else
			p = p->next;
	}
	return;
}

void outpatient_name(struct record* head)		//�����������������
{
	char name[30];
	printf("��������Ҫ��ѯ�Ļ���������\n");
	scanf("%s", &name);
	record* p;
	p = head; 
	int t, x = 0,m = 0;
	while (strcmp((p->pat.name_pat) , name) == 0&& p != NULL)
	{
		x = x + 1;
		printf("%d %s %d %s\n", x, ((p->pat).name_pat), ((p->pat).age),p->pat.tag_id);//���������Ϣ����
		p = p->next;
	}
	if (x == 0)
	{
		printf("���޴��ˣ�\n");
		return;
	}
	printf("��������Ҫ��ѯ�Ļ�����ţ�\n");
	scanf("%d", &t);
	for (strcmp((p->pat.name_pat), name) == 1; p != NULL; )
	{
		m = m + 1;
		if (m == t) 
		{
			printf("%s %d ", (p->pat.name_pat), (p->pat.age));//���������Ϣ����
			printf("%s %s %s %d ", p->doc.name_doc, p->doc.level, p->doc.sub, p->doc.num_work);//���ҽ����Ϣ����
			printf("%s ", p->out_doc);                         //�������ʱ��
			for (int i = 0; i < (p->tre.che.tag_check); i++)
			{
				printf("%s ", p->tre.che.type[i]);       //����������
				printf("%f ", p->tre.che.cost_term[i]);  //���������ķ���
			}
			for (int i = 0; i < (p->tre.pil.tag_pill); i++)
			{
				printf("%s ", p->tre.pil.name_pill[i]);   //���ҩƷ����
				printf("%d ", p->tre.pil.cost_perpill[i]);//���ҩƷ����
				printf("%d ", p->tre.pil.num_pill[i]);    //���ҩƷ����
			}
			printf("%d  %d ", p->tre.hos.time_start, p->tre.hos.time_end);//���ס,��Ժʱ��
			printf("%d %d %d\n", p->tre.hos.days_hos, p->tre.hos.cost_hos, p->tre.hos.deposit);//���סԺ����,סԺ����,סԺѺ��
		}
	}
	return;
}

void outsub_doc(struct record* head)   //���Ҽ���
{
	char sub_in[10];
	record* p = head;
	printf("��������Ҫ��ѯ�Ŀ���\n");
	scanf("%s", sub_in);
	//for (strcmp((p->doc.sub), sub_in) == 1; q != NULL;)
	//{
	//	
	//	printf("%s %d ", (p->pat.name_pat), (p->pat.age));//���������Ϣ����
	//	printf("%s %s %s %d", p->doc.sub, p->doc.name_doc, p->doc.level, p->doc.num_work);//���ҽ����Ϣ����
	//	printf("%s ", p->out_doc);                         //�������ʱ��
	//	for (int i = 0; i < (p->tre.che.tag_check); i++)
	//	{
	//		printf("%s ", p->tre.che.type[i]);       //����������
	//		printf("%f ", p->tre.che.cost_term[i]);  //���������ķ���
	//	}
	//	for (int i = 0; i < (p->tre.pil.tag_pill); i++)
	//	{
	//		printf("%s ", p->tre.pil.name_pill[i]);   //���ҩƷ����
	//		printf("%d ", p->tre.pil.cost_perpill[i]);//���ҩƷ����
	//		printf("%d ", p->tre.pil.num_pill[i]);    //���ҩƷ����
	//	}
	//	printf("%d  %d ", p->tre.hos.time_start, p->tre.hos.time_end);//���ס,��Ժʱ��
	//	printf("%d %d %d\n", p->tre.hos.days_hos, p->tre.hos.cost_hos, p->tre.hos.deposit);//���סԺ����,סԺ����,סԺѺ��
	//}
	while (p != NULL)
	{
		if (strcmp(sub_in, p->doc.sub) == 0)
		{
			singleprint(p);
			p = p->next;
		}
		else
			p = p->next;
	}
}

void outname_doc(struct record* head)  //ҽ�����ż���
{
	int num;
	record* p = head; 
	printf("��������Ҫ��ѯ��ҽ������\n");
	scanf("%d", &num);
	while (p != NULL)
	{
		if (p->doc.num_work == num)
		{
			singleprint(p);
			p = p->next;
		}
		else
			p = p->next;
	}
	//for ((p->doc.num_work) = num; q != NULL;)
	//{
 //       printf("%d %s %s %s", p->doc.num_work, p->doc.name_doc, p->doc.sub, p->doc.level);//���ҽ����Ϣ����
	//	printf("%s %d ", (p->pat.name_pat), (p->pat.age));//���������Ϣ����
	//	printf("%s ", p->out_doc);                         //�������ʱ��
	//	for (int i = 0; i < (p->tre.che.tag_check); i++)
	//	{
	//		printf("%s ", p->tre.che.type[i]);       //����������
	//		printf("%f ", p->tre.che.cost_term[i]);  //���������ķ���
	//	}
	//	for (int i = 0; i < (p->tre.pil.tag_pill); i++)
	//	{
	//		printf("%s ", p->tre.pil.name_pill[i]);   //���ҩƷ����
	//		printf("%d ", p->tre.pil.cost_perpill[i]);//���ҩƷ����
	//		printf("%d ", p->tre.pil.num_pill[i]);    //���ҩƷ����
	//	}
	//	printf("%d  %d ", p->tre.hos.time_start, p->tre.hos.time_end);//���ס,��Ժʱ��
	//	printf("%d %d %d\n", p->tre.hos.days_hos, p->tre.hos.cost_hos, p->tre.hos.deposit);//���סԺ����,סԺ����,סԺѺ��
	//}
	return;
}

void outtime_limit(struct record* head)        //ʱ��μ���
{
	record* p, * q;
	p = head; q = p->next;
	char time_start[8], time_end[8];
	int start, end, tag_time;
	printf("��������ʼʱ���Լ�����ʱ�䣺\n");
	scanf("%s%s", &time_start, &time_end);
	start = date_turn(time_start); end = date_turn(time_end);
	
	int t, x = 0; t = 0;
	for (q != NULL;;) 
	{
		tag_time=date_turn(p->out_doc);
		for ((tag_time>=start)&&(tag_time<=end);;)
	    {
		    printf("%s ", p->out_doc);                         //�������ʱ��
		    printf("%d %s %s %s", p->doc.num_work, p->doc.name_doc, p->doc.sub, p->doc.level);//���ҽ����Ϣ����
		    printf("%s %d ", (p->pat.name_pat), (p->pat.age));//���������Ϣ����
		    for (int i = 0; i < (p->tre.che.tag_check); i++)
		    {
			    printf("%s ", p->tre.che.type[i]);       //����������
			    printf("%f ", p->tre.che.cost_term[i]);  //���������ķ���
		    }
		    for (int i = 0; i < (p->tre.pil.tag_pill); i++)
		    {
			    printf("%s ", p->tre.pil.name_pill[i]);   //���ҩƷ����
			    printf("%d ", p->tre.pil.cost_perpill[i]);//���ҩƷ����
			    printf("%d ", p->tre.pil.num_pill[i]);    //���ҩƷ����
		    }
		    printf("%d  %d ", p->tre.hos.time_start, p->tre.hos.time_end);//���ס,��Ժʱ��
		    printf("%d %d %d\n", p->tre.hos.days_hos, p->tre.hos.cost_hos, p->tre.hos.deposit);//���סԺ����,סԺ����,סԺѺ��
	    }
	}
	return;
}

void output(struct record* head)
{
	record* p, * q;
	p = head; q = p->next;
	int x; x = 0;
	while (p->next!=NULL)
	{
		x = x + 1;
		printf("%d ", x);
		printf("%s %d ", (p->pat.name_pat), (p->pat.age));//���������Ϣ����
		printf("%s %s %s %d ", p->doc.name_doc, p->doc.level, p->doc.sub, p->doc.num_work);//���ҽ����Ϣ����
		printf("%s ", p->out_doc);                         //�������ʱ��
		for (int i = 0; i < (p->tre.che.tag_check); i++)
		{
			printf("%s ", p->tre.che.type[i]);       //����������
			printf("%f ", p->tre.che.cost_term[i]);  //���������ķ���
		}
		for (int i = 0; i < (p->tre.pil.tag_pill); i++)
		{
			printf("%s ", p->tre.pil.name_pill[i]);   //���ҩƷ����
			printf("%d ", p->tre.pil.cost_perpill[i]);//���ҩƷ����
			printf("%d ", p->tre.pil.num_pill[i]);    //���ҩƷ����
		}
		printf("%d  %d ", p->tre.hos.time_start, p->tre.hos.time_end);//���ס,��Ժʱ��
		printf("%d %d %d\n", p->tre.hos.days_hos, p->tre.hos.cost_hos, p->tre.hos.deposit);//���סԺ����,סԺ����,סԺѺ��
		if (p->next== NULL)
			return;
		else
			p = p->next; 
		
	}
	return;
}

void del_record(struct record* head)   //ɾ������
{
	record* p, * q,* r;
	p = head; q = p->next; r->next = p;
	int x, y; y = 0;
	output(head);
	printf("��ѡ����Ҫɾ���ļ�¼");
	scanf("%d", &x);
	for (p != NULL;;)
	{
		y = y + 1;
		if (x == y)
		{
			r->next = q; 
			free(p);
			printf("ɾ���ɹ���");
		}
		else
		{
			r = p; p = q; q = q->next;
		}
	}
	return;
}

void input(struct record* p)
{
	printf("�����뻼����Ϣ\n");
	scanf("%s%d", &(p->pat.name_pat), &(p->pat.age));
	printf("������Һ�\n");
	scanf("%d", &(p->num_check));
	printf("������ҽ����Ϣ\n");
	scanf("%s%s%s%d", &(p->doc.name_doc), &(p->doc.level), &(p->doc.sub), &(p->doc.num_work));
	printf("���������ʱ��\n");
	scanf("%s", &(p->out_doc[8]));
	printf("����������鼰�����,�������������롮|��\n");
	(p->tre.che.tag_check) = 0; bool flag_che = true; int i = 0;
	while (flag_che)
	{
		scanf("%s", &(p->tre.che.type[i]));
		if ((p->tre.che.type[i][0]) == '|')
		{
			flag_che = false;
			(p->tre.che.cost_check) = sumcheck((p->tre.che.tag_check), (p->tre.che.cost_term));
			break;
		}
		scanf("%f", &(p->tre.che.cost_term[i]));
		(p->tre.che.tag_check)++;
	}
	printf("�������ҩƷ���Ƽ��������͵���,�������������롮|��\n");
	(p->tre.pil.tag_pill) = 0; bool flag_pil = true; i = 0;
	while (flag_pil)
	{
		scanf("%s", &(p->tre.pil.name_pill[i]));
		if ((p->tre.pil.name_pill[i][0]) == '|')
		{
			flag_pil = false;
			(p->tre.pil.cost_pill) = sumpill(p->tre.pil.tag_pill, p->tre.pil.cost_perpill, p->tre.pil.num_pill);
			break;
		}
		scanf("%d%d", &(p->tre.pil.cost_perpill[i]), &(p->tre.pil.num_pill[i]));
		(p->tre.pil.tag_pill)++;
	}
	printf("�����뿪ʼסԺʱ�䣬Ԥ�Ƴ�Ժʱ�估�ѽ��ɵ�סԺѺ��\n");
	scanf("%d%d%d", &(p->tre.hos.time_start), &(p->tre.hos.time_end), &(p->tre.hos.deposit));
	(p->tre.hos.days_hos) = days_hosp(p->tre.hos.time_start, p->tre.hos.time_end);
	return;
}

void alter_record(struct record* head)   //�޸Ĳ���
{
	record* p, * q, * r;
	p = head; q = p->next; r->next = p;
	int x, y; y = 0;
	output(head);
	printf("��ѡ����Ҫ�޸ĵļ�¼");
	scanf("%d", &x);
	for (p != NULL;;)
	{
		y = y + 1;
		if (x == y)
		{
			printf("�����ɹ������������룺\n");
			input(q);
		}
		else
		{
			r = p; p = q; q = q->next;
		}
	}
	return;
}

float statistics(struct record* head)    //Ӫҵ��
{
	float turn = 0;
	record* p, * q;
	p = head; q = p->next;
	for (p != NULL;;)
	{
		turn = turn+ (p->tre.che.cost_check) + (p->tre.pil.cost_pill) + (float)(p->tre.hos.cost_hos);
		p = q; q = q->next;
	}
	return turn;
}

void yearchange(int a) {                              //�ı�ϵͳ���
	printf("������Ŀ����ݣ�");
	scanf("%d", &a);
	return;
}

bool judge_year(int a) {                             //�ж�����
	if (a % 100 == 0) {
		if (a % 400 == 0) {
			return true;
		}
		return false;
	}
	else {
		if (a % 4 == 0 && a % 100 != 0) {
			return true;
		}
		return false;
	}
}

bool judge_name_pat(record* p) {                 //�ж�����
	int t = 0;
	for (t = 0; ((p->pat.name_pat[t]) != '/0') && t < 50; t++) {
		if ((p->pat.name_pat[t]) >= 32 && (p->pat.name_pat[t]) <= 64) {
			return false;
		}
		else if ((p->pat.name_pat[t]) >= 91 && (p->pat.name_pat[t]) <= 96) {
			return false;
		}
		else if ((p->pat.name_pat[t]) >= 123 && (p->pat.name_pat[t]) <= 126) {
			return false;
		}
	}
	return true;
}

bool judge_age(record* p) {                            //�ж�����
	if ((p->pat.age) < 0 && (p->pat.age) > 150) {
		return false;
	}
	return true;
}

bool judge_sex(record* p) {                        //�ж��Ա�
	if (strcmp(p->pat.sex, "��") != 0 || strcmp(p->pat.sex, "Ů") != 0) {
		return false;
	}
	return true;
}

bool judge_tag_id(record* p) {                         //�ж����ʶ����
	int t = 0;
	for (t = 0; t < 3; t++) {
		if ((p->pat.tag_id[t]) <= '0' && (p->pat.tag_id[t]) >= '9') {
			return false;
		}
	}
	if (strcmp(p->pat.sex, "��") == 0 && (p->pat.tag_id[3]) % 2 == 0) {
		return false;
	}
	if (strcmp(p->pat.sex, "Ů") == 0 && (p->pat.tag_id[3]) % 2 != 0) {
		return false;
	}
	return true;
}

bool judge_num_check(record* p) {                  //�жϹҺ�
	record* a, * b;
	char x[8];
	int m;
	a = p; b = p->next;
	while (b->next != NULL) {
		b = b->next;
	}
	while (a != b) {
		if (a->num_check == b->num_check) {
			return false;
		}
		a = a->next;
	}
	sprintf(x, "%d", b->num_check);
	m = (x[0] * 10) + x[1];
	if (m > 12 || m < 1) {
		return false;
	}
	m = (x[4] * 100) + (x[5] * 10) + x[6];
	if (m < 1 || m>500) {
		return false;
	}
	return true;
}

che_term* judge_che_name(char* p, che_term* q) {				 //�жϼ�������Ƿ���ȷ
	bool flag = false;
	while (q != NULL) {
		if (strcmp(p, q->che_name) == 0)
			return q;
		q = q->next;
	}
	return NULL;
}

pill_term* judge_pill_name(char* p, pill_term* q) {               //�ж�ҩƷ�����Ƿ���ȷ
	while (q != NULL) {
		if (strcmp(p, q->pill_name) == 0)
			return q;
		q = q->next;
	}
	return NULL;
}

doctor* judge_num_work(int num, doctor* s) {					//�ж�ҽ������
	while (s != NULL) {
		if (num == s->num_work)
			return s;
		s = s->next;
	}
	return NULL;
}

bool time(int a, int b) {                             //�ж�ʱ��
	char m[9]; int x, y, i, j;
	sprintf(m, "%d", a);
	x = (m[0] * 10) + m[1];
	y = (m[2] * 10) + m[3];
	i = (m[4] * 10) + m[5];
	j = (m[6] * 10) + m[7];
	if (x < 1 || x > 12 || y < 1 || i > 24 || j > 59) {
		return false;
	}
	if (x == 1 || x == 3 || x == 5 || x == 7 || x == 8 || x == 10 || x == 12) {
		if (y > 31) {
			return false;
		}
	}
	if (x == 2 || x == 4 || x == 6 || x == 9 || x == 11) {
		if (y > 30) {
			return false;
		}
	}
	if (judge_year(b)) {
		if (x == 2 || y > 29) {
			return false;
		}
	}
	else {
		if (x == 2 || y > 28) {
			return false;
		}
	}
	return true;
}

bool judge_time(record* p) {
	if (!(time(p->tre.hos.time_start, year))) {
		return false;
	}
	if (!(time(p->tre.hos.time_end, year))) {
		return false;
	}
	if (days_hosp(p->tre.hos.time_start, p->tre.hos.time_end) < 1) {
		return false;
	}
	return true;
}