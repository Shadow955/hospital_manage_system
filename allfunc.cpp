#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include"base_struct.h"
#include"allfunc.h"
#include"fileopt.h"

//int year = 2020;
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

float sumpill(int tag_pill, float cost_perpill[], int num_pill[])        //����ҩƷ�ܷ��ú���
{
	int i;
	float sum = 0;
	for (i = 0; i < tag_pill ; i++)
	{
		sum = sum + ((cost_perpill[i]) * (num_pill[i]));
	}
	return sum;
}

int date_turn(int time)                 //��4λ����ת��Ϊ����
{
	int mon, day, tag = 0;
	mon = time / 100;
	day = time % 100;
	switch (mon)
	{
	case 1:tag = day; break;
	case 2:tag = day + 31; break;
	case 3:tag = day + 59; break;
	case 4:tag = day + 90; break;
	case 5:tag = day + 120; break;
	case 6:tag = day + 151; break;
	case 7:tag = day + 181; break;
	case 8:tag = day + 212; break;
	case 9:tag = day + 243; break;
	case 10:tag = day + 273; break;
	case 11:tag = day + 304; break;
	case 12:tag = day + 334; break;
	}
	if ((judge_year(turnyear(getyear()))) && mon > 2)
		tag++;
	return tag;
}

int cost_hos(int in,int out,int now)           //סԺ���ú���
{
	if (out > now)
		return (now - in) * 100;
	else
		return (out - in) * 100;
}

record* getrecord(doctor* doc,pill_term* pill,che_term* che,int tag)    //¼���¼
{
	record* temp = (record*)malloc(sizeof(record));
	temp->next = NULL;
	temp->num_check = tag + 1;
	printf("\n����Ϊ���뻼����Ϣ��ÿ����Ϣ�Իس�����\n\n�����뻼��������\n");
	scanf("%s", &(temp->pat.name_pat));getchar();
	while (!judge_name_pat(temp->pat.name_pat))
	{
		printf("�����������������������룡Ŀǰ��֧����������\n");
		scanf("%s", &(temp->pat.name_pat));getchar();
	}
	printf("�Ա�\n");
	scanf("%s", temp->pat.sex);getchar();
	while (!judge_sex(temp->pat.sex))
	{
		printf("�Ա���������������������\n");
		scanf("%s", &(temp->pat.sex)); getchar();
	}
	printf("���䣺\n");
	scanf("%d", &temp->pat.age); getchar();
	while (!judge_age(temp->pat.age))
	{
		printf("�����������������1-149������ ����С��������ȡ֤\n");
		scanf("%d", &temp->pat.age); getchar();
	}
	printf("���֤�ź���λ��\n");
	scanf("%s", temp->pat.tag_id);getchar();
	while (!judge_tag_id(temp->pat.sex, temp->pat.tag_id))
	{
		printf("���֤�����Ϲ淶��������������룡β��Ϊx��Сд\n");
		scanf("%s", temp->pat.tag_id); getchar();
	}
	printf("������ҽ�����ţ�\n");
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
				printf("�ü����Ŀ�����ڣ��������������\n");
				scanf("%s", &(temp->tre.che.type[i]));
				if (strcmp("#", temp->tre.che.type[i]) == 0)
				{
					flag_che = false;
					(temp->tre.che.cost_check) = sumcheck((temp->tre.che.tag_check), (temp->tre.che.cost_term));
					break;
				}
				tpche = judge_che_name(temp->tre.che.type[i], che);
			}
			if(tpche!=NULL)
				temp->tre.che.cost_term[i] = tpche->che_price;
		}
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
				printf("��ҩƷ�������ڣ��������������\n");
				scanf("%s", temp->tre.pil.name_pill[i]);
				if (strcmp("#", temp->tre.pil.name_pill[i]) == 0)
				{
					flag_pil = false;
					(temp->tre.pil.cost_pill) = sumpill(temp->tre.pil.tag_pill, temp->tre.pil.cost_perpill, temp->tre.pil.num_pill);
					break;
				}
					tppill = judge_pill_name(temp->tre.pil.name_pill[i], pill);
			}
			if(tppill!=NULL)
				temp->tre.pil.cost_perpill[i] = tppill->pill_price;
		}
		if (strcmp(temp->tre.pil.name_pill[i],"#")!=0) {
			printf("����ҩƷ������\n");
			scanf("%d", &temp->tre.pil.num_pill[i]);
		}
		(temp->tre.pil.tag_pill)++;
		i++;
	}
	while (1)
	{
		printf("\n�����뿪ʼסԺʱ�䣨��λ���֣���\n");
		scanf("%d", &(temp->tre.hos.time_start));
		while (!JudgeDate(temp->tre.hos.time_start))
		{
			printf("�������벻�Ϸ���������������룺\n");
			scanf("%d", &(temp->tre.hos.time_start));
		}
		printf("\n������Ԥ�Ƴ�Ժʱ�䣨��λ���֣���\n");
		scanf("%d", &(temp->tre.hos.time_end));
		while (!JudgeDate(temp->tre.hos.time_end))
		{
			printf("�������벻�Ϸ���������������룺\n");
			scanf("%d", &(temp->tre.hos.time_end));
		}
		if (temp->tre.hos.time_end > temp->tre.hos.time_start)
			break;
		else
			printf("��Ժʱ�䲻������סԺʱ�䣡����������\n");
	}
	int now = turndate(gettime());
	temp->tre.hos.cost_hos = cost_hos(date_turn(temp->tre.hos.time_start), date_turn(temp->tre.hos.time_end), date_turn(now));
	if (now <= temp->tre.hos.time_end)
		DoctorState(temp->doc.num_work, doc);
	printf("\n���������סԺѺ��\n");
	scanf("%d",&(temp->tre.hos.deposit));
	int price = 200 * (date_turn(temp->tre.hos.time_end) - date_turn(temp->tre.hos.time_start));
	if (price < 1000)
		price = 1000;
	while (temp->tre.hos.deposit < price)
	{
		printf("Ѻ���㣡����Ӧ����Ѻ��%dԪ������������\n", price);
		printf("\n���������סԺѺ��\n");
		scanf("%d", &(temp->tre.hos.deposit));
		price = 200 * (date_turn(temp->tre.hos.time_end) - date_turn(temp->tre.hos.time_start));
	}
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
	char name[30]; char patid[100][5];
	bool tag = true; record* p; p = head;
	int x = 0, y = 0, m = 0; char t[5];
	while (tag) {
		printf("��������Ҫ��ѯ�Ļ���������\n");
		scanf("%s", &name);
		while (p != NULL)
		{
			if (strcmp((p->pat.name_pat), name) == 0) {
				x = x + 1;
				for (int i = 0; i < x; i++) {
					if (x == 1) {
						strcpy(patid[0], p->pat.tag_id);
						printf("%d %s %d %s\n", x, p->pat.name_pat, p->pat.age, p->pat.tag_id);
						break;
					}
					if (strcmp(patid[x - 1], p->pat.tag_id) == 0) {
						break;
					}
					else {
						strcpy(patid[x], p->pat.tag_id);
						printf("%d %s %d %s\n", x, p->pat.name_pat, p->pat.age, p->pat.tag_id);
						break;
					}
				}
			}
			p = p->next;
		}
		if (x == 0)
		{
			printf("���޴��ˣ�����Ҫ����������\n1.��   2��\n");     //��־��
			scanf("%d", &y);
			if (y == 1) {
				tag = true;
			}
			else
				return;
		}
		else
			tag = false;
	}
	if (!tag) {
		outpatient_tag(head);
	}
	return;
}
void outsub_doc(struct record* head)   //���Ҽ���
{
	char sub_in[10];
	record* p = head;
	printf("��������Ҫ��ѯ�Ŀ���\n");
	scanf("%s", sub_in);
	while (strcmp(sub_in, "�ڿ�") != 0 &&
		strcmp(sub_in, "���") != 0 &&
		strcmp(sub_in, "����") != 0 &&
		strcmp(sub_in, "������") != 0 &&
		strcmp(sub_in, "��Ⱦ��") != 0 &&
		strcmp(sub_in, "�����") != 0 &&
		strcmp(sub_in, "������") != 0)
	{
		printf("���Ҳ����ڣ��������������\n");
		scanf("%s", sub_in);
	}
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
	int num, x = 0;
	record* p = head; 
	printf("��������Ҫ��ѯ��ҽ������\n");
	scanf("%d", &num);
	while (p != NULL)
	{
		if (p->doc.num_work == num)
		{
			singleprint(p);
			x++;
			p = p->next;
		}
		else
			p = p->next;
	}
	if (x == 0)
		printf("δ�������ù��ţ�\n");
}


void del_record(record* head,record* t)   //ɾ������
{
	record* p = head;
	record* pre = NULL;
	while (p != NULL && p != t) {
		pre = p;
		p = p->next;
	}
	if (p == t) {
		pre->next = p->next;
		free(p);
		printf("ɾ���ɹ���");
	}
}


void alter_record(record* head,record* t,doctor* doc,pill_term* pill,che_term* che)   //�޸Ĳ���
{
	record* p = head;
	record* pre = NULL;
	record* after = NULL;
	while (p != NULL && p != t)
	{
		pre = p;
		p = p->next;
	}
	if (p == t)
	{
		int tp = p->num_check;//��ʱ����Һ�
		after = p->next;
		printf("�������������Ƽ�¼��\n");
		p = getrecord(doc, pill, che,999);
		p->num_check = tp;
		pre->next = p;
		p->next = after;
		printf("���Ƽ�¼�޸ĳɹ���\n");
	}
}

void statistics(record* head)    //Ӫҵ��
{
	float turn = 0;
	record* p = head; 
	while (p != NULL)
	{
		turn = turn+ (p->tre.che.cost_check) + (p->tre.pil.cost_pill) + (float)(p->tre.hos.cost_hos);
		p = p->next;
	}
	printf("ҽԺ�����ʽ�%.2fԪ\n", turn);
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

bool judge_name_pat(char* name) {                 //�ж�����
	bool flag = true;
	int i = 0;
	while (name[i] != '\0') {
		if (name[i] >= 0) {
			flag = false;
			break;
		}
		i++;
	}
	return flag;
}

bool judge_age(int age) {                            //�ж�����
	if (age < 0 || age > 150) {
		return false;
	}
	else
		return true;
}

bool judge_sex(char* sex) {                        //�ж��Ա�
	if (strcmp(sex, "��") != 0 && strcmp(sex, "Ů") != 0) {
		return false;
	}
	else
		return true;
}

bool judge_tag_id(char* sex,char* id) {                         //�ж����֤β��
	int t = 0;
	bool flag = true;
	for (t = 0; t < 3; t++) {
		if ((id[t]) <= '0' || (id[t]) >= '9') {
			flag=false;
			return flag;
		}
	}
	if (id[3] <= '0' || id[3] >= '9') {
		flag = false;
		if (id[3] == 'x')
			flag = true;
	}
	if (strcmp(sex, "��") == 0 && (id[2]) % 2 == 0) {
		flag=false;
	}
	if (strcmp(sex, "Ů") == 0 && (id[2]) % 2 != 0) {
		flag=false;
	}
	return flag;
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

bool JudgeDate(int a) 
{ 
	int mon, day;
	mon = a / 100;
	day = a % 100;
	if (a < 101)
		return false;
	if (mon < 1 || mon>12)
		return false;
	if (mon == 1 || mon == 3 || mon == 5 || mon == 7 || mon == 8 || mon == 10 || mon == 12) {
		if (day < 1 || day>31)
			return false;
		else
			return true;
	}
	if (mon == 4 || mon == 6 || mon == 9 || mon == 11) {
		if (day < 1 || day>30)
			return false;
		else
			return true;
	}
	if (mon == 2) {
		if (judge_year(turnyear(getyear()))) {
			if (day < 1 || day>29)
				return false;
			else
				return true;
		}
		else {
			if (day < 1 || day>28)
				return false;
			else
				return true;
		}
	}
}

void DoctorState(int workNum, doctor* head)
{
	doctor* p = head;
	while (p != NULL && workNum != p->num_work) {
		p = p->next;
	}
	p->state++;
}

void outtime_limit(struct record* head)        //ʱ��μ���
{
	record* p = head;
	int start, end, tag_time;
	while (1)
	{
		printf("��������ʼʱ��(4λ��������ȷ����)��\n");
		scanf("%d", &start);
		while (!JudgeDate(start))
		{
			printf("���ڲ��Ϸ�������������\n");
			printf("��������ʼʱ��(4λ��������ȷ����)��\n");
			scanf("%d", &start);
		}
		printf("��������ֹʱ��(4λ��������ȷ����)��\n");
		scanf("%d", &end);
		while (!JudgeDate(end))
		{
			printf("���ڲ��Ϸ�������������\n");
			printf("��������ֹʱ��(4λ��������ȷ����)��\n");
			scanf("%d", &end);
		}
		if (start < end)
			break;
		else
			printf("��ֹ���ڱ�������ʼʱ��֮������������");
	}
	while (p != NULL)
	{
		tag_time = turndate(p->out_doc);
		if ((tag_time >= start) && (tag_time <= end))
		{
			singleprint(p);
		}
		p = p->next;
	}
	if (p == NULL)
		printf("δ�ҵ���ʱ����ڵ����Ƽ�¼��");
}