//modified by Nero on 9/29
#include<stdlib.h>
#include<stdio.h>
#include"base_struct.h"
#include<string.h>
#include"fileopt.h"
#include"allfunc.h"
#include<time.h>
FILE* file_rec;
FILE* file_pill;
FILE* file_doc;
FILE* file_che;
//FILE* outfile;
extern time_t t;
extern char* Time;
int openfile() {															//�ļ����뺯�����ɹ�����1��ʧ�ܷ���0
	file_rec = fopen("test.txt", "r+");							//��ȡ�ļ����ж��Ƿ�ɹ���
	file_pill = fopen("pill.txt", "r");
	file_doc = fopen("doc.txt", "r");
	file_che = fopen("check.txt", "r");
	if (file_rec == NULL||file_pill==NULL||file_doc==NULL||file_che==NULL)
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

char* gettime()
{
	//���µ�ǰ��time_t ����Ϊ��ǰϵͳʱ��
	time(&t);
	//ctime���������ַ������͵� time_t ������ʽ
	char* Time = ctime(&t);
	Time += 4;
	Time[12] = '\0';
	return Time;
}

char* getyear()
{
	time(&t);
	char* year = ctime(&t);
	year += 20;
	year[4] = '\0';
	return year;
}

int turnyear(char a[5])
{
	char * s;
	char b[5];
	s = a;
	int m;
	strcpy(b, s);
	m = ((int)a[0] - 48) * 1000 + ((int)a[1] - 48) * 100 + ((int)a[2] - 48) * 10 + ((int)a[3] - 48);
	return m;
}

record* read_and_link() 
{
	record* rec_head = (record*)malloc(sizeof(record));		//����ͷ�ڵ�
	rec_head->next = NULL;
	record* tp;
	record* pre = NULL;
	tp = rec_head;
	while (!feof(file_rec))																//ѭ������ֱ���ļ�ĩβ
	{
		fscanf(file_rec, "%d", &tp->num_check);
		fscanf(file_rec, "%s%s%d%s"
			, tp->pat.name_pat
			, tp->pat.sex
			, &tp->pat.age
			, &tp->pat.tag_id);
		fscanf(file_rec, "%s%s%s%d"
			, tp->doc.name_doc
			, tp->doc.level
			, tp->doc.sub
			, &tp->doc.num_work);
		fgetc(file_rec);
		fgets( tp->out_doc,13,file_rec);
		int i = 0, j = 0;
		while(1)
		{
			fscanf(file_rec, "%s", tp->tre.che.type[i]);
			if(strcmp("#", tp->tre.che.type[i]) == 0)
				break;
			fscanf(file_rec, "%f", &tp->tre.che.cost_term[i]);
			i++;
		}
		tp->tre.che.tag_check = i;
		tp->tre.che.cost_check = sumcheck(tp->tre.che.tag_check, tp->tre.che.cost_term);
		while(1)//�ڶ���#֮ǰ��ѭ������ҩƷ����������
		{
			fscanf(file_rec, "%s", tp->tre.pil.name_pill[j]);
			if (strcmp("#", tp->tre.pil.name_pill[j]) == 0)
				break;
			fscanf(file_rec, "%f%d"
				, &tp->tre.pil.cost_perpill[j]
				, &tp->tre.pil.num_pill[j]);
			j++;
		}
		tp->tre.pil.tag_pill = j;
		tp->tre.pil.cost_pill = sumpill(tp->tre.pil.tag_pill, tp->tre.pil.cost_perpill, tp->tre.pil.num_pill);
		fscanf(file_rec, "%d%d%d"									//����סԺ��Ϣ����
			, &tp->tre.hos.time_start
			, &tp->tre.hos.time_end
			, &tp->tre.hos.deposit);
		tp->tre.hos.cost_hos = cost_hos(tp->tre.hos.time_start, tp->tre.hos.time_end, turndate(gettime()));
		tp->next = (record*)malloc(sizeof(record));
		tp->next->next = NULL;
		pre = tp;
		tp = tp->next;
	}
	free(tp);
	pre->next = NULL;
	printf("���Ƽ�¼�������ɹ���\n");
	return (rec_head);
}

pill_term* link_pill()
{
	pill_term* pill_head = (pill_term*)malloc(sizeof(pill_term));		
	pill_head->next = NULL;
	pill_term* tp;
	pill_term* pre = NULL;
	tp = pill_head;
	while (!feof(file_pill))
	{
		fscanf(file_pill, "%s%f", tp->pill_name, &tp->pill_price);
		tp->next = (pill_term*)malloc(sizeof(pill_term));
		tp->next->next = NULL;
		pre = tp;
		tp = tp->next;
	}
	free(tp);
	pre->next = NULL;
	printf("ҩƷ�������ɹ���\n");
	return (pill_head);
}

che_term* link_che()
{
	che_term* che_head = (che_term*)malloc(sizeof(che_term));
	che_head->next = NULL;
	che_term* tp;
	che_term* pre = NULL;
	tp = che_head;
	while (!feof(file_che))
	{
		fscanf(file_che, "%s%f", tp->che_name, &tp->che_price);
		tp->next = (che_term*)malloc(sizeof(che_term));
		tp->next->next = NULL;
		pre = tp;
		tp = tp->next;
	}
	free(tp);
	pre->next = NULL;
	printf("�����Ŀ�������ɹ���\n");
	return (che_head);
}

doctor* link_doc()
{
	doctor* doc_head = (doctor*)malloc(sizeof(doctor));
	doc_head->next = NULL;
	doctor* tp;
	doctor* pre = NULL;
	tp = doc_head;
	while (!feof(file_doc))
	{
		fscanf(file_doc, "%s%s%s%d", tp->name_doc, tp->level, tp->sub, &tp->num_work);
		tp->next = (doctor*)malloc(sizeof(doctor));
		tp->next->next = NULL;
		pre = tp;
		tp = tp->next;
	}
	free(tp);
	pre->next = NULL;
	printf("ҽ���������ɹ���\n");
	return (doc_head);
}

void printf_number(record* rec_head,pill_term* pill_head,che_term* che_head,doctor* doc_head) {
	int number1;//�������������
	printf("�����빦�ܶ�Ӧ�����֣�\n1 : ��ӡĳ����������Ϣ\n2 : ��ӡĳҽ��������Ϣ\n");
	printf("3 : ��ӡĳ������ʷ���Ƽ�¼\n4 : ��ӡĳ��ʱ���ڵ����Ƽ�¼\n");
	printf("5 : ���ȫ��ҽ������\n6 : ���ҩƷ������\n7 : ������������\n");
	scanf("%d", &number1);
	switch (number1) {
	case 1: 
		outsub_doc(rec_head); break;//��ӡĳ����������Ϣ
	case 2: 
		outname_doc(rec_head); break;//��ӡĳҽ��������Ϣ
	case 3: 
		outpatient_tag(rec_head); break;//��ӡĳ������ʷ���Ƽ�¼
	case 4: 
		//outtime_limit(rec_head); break;//��ӡĳ��ʱ���ڵ����Ƽ�¼
	case 5:
		docprint(doc_head); break;
	case 6:
		pillprint(pill_head); break;
	case 7:
		cheprint(che_head); break;
	}
}

record* FindEnd(record* head)
{
	record* p = head;
	while (p->next != NULL)
	{
		p = p->next;
	}
	return p;
}

void singleprint(record* p) 
{
	printf("�Һţ�%07d\n����������%s\n�Ա�%s  ���䣺%d  ���֤β�ţ�%s\n"
		, p->num_check
		, p->pat.name_pat
		, p->pat.sex
		, p->pat.age
		, p->pat.tag_id);
	printf("\n����ҽʦ��%s\n����%s  ���ң�%s  ҽ�����ţ�%07d\n"
		, p->doc.name_doc
		, p->doc.level
		, p->doc.sub
		, p->doc.num_work);
	printf("ҽ������ʱ�䣺%s", p->out_doc);
	int i = 0, j = 0;
	printf("\n\n���߼�������\n �����Ŀ           �۸�\n");
	while (strcmp("#", p->tre.che.type[i]) != 0)//�ڶ���#֮ǰ��ѭ����������Ŀ���������
	{
		printf("%-16s   %6.2fԪ\n", p->tre.che.type[i], p->tre.che.cost_term[i]);
		i++;
	}
	printf("\n���߿�ҩ�����\n ҩƷ��              ����      ����\n");
	while (strcmp("#", p->tre.pil.name_pill[j]) != 0)//�ڶ���#֮ǰ��ѭ�����ҩƷ����������
	{
		printf("%-16s   %6.2fԪ   %3d\n"
			, p->tre.pil.name_pill[j]
			, p->tre.pil.cost_perpill[j]
			, p->tre.pil.num_pill[j]);
		j++;
	}
	printf("\nסԺ��ʼʱ��:%04d\nԤ�Ƴ�Ժʱ��:%04d\nѺ��:%d"									//���סԺ��Ϣ����
		, p->tre.hos.time_start
		, p->tre.hos.time_end
		, p->tre.hos.deposit);
	//p = p->next;
	printf("\n---------------------------------------------------------------------------\n");
}
void stdprint(record* p)
{
	printf("\n---------------------------------------------------------------------------\n");
	while (p!=NULL)
	{
		singleprint(p);
		p = p->next;
	}
}

void docprint(doctor* p)
{
	printf("\n---------------------------------------------------------------------------\n");
	while (p->next!= NULL)
	{
		printf("%-25s%-12s%-10s%-10d\n", p->name_doc, p->level, p->sub, p->num_work);
		p = p->next;
	}
	printf("---------------------------------------------------------------------------\n\n");
}

void pillprint(pill_term* p) 
{
	printf("\n---------------------------------------------------------------------------\n");
	while (p->next!= NULL)
	{
		printf("%-15s%6.2fԪ\n", p->pill_name, p->pill_price);
		p = p->next;
	}
	printf("---------------------------------------------------------------------------\n\n");
}

void cheprint(che_term* p)
{
	printf("\n---------------------------------------------------------------------------\n");
	while (p->next!= NULL)
	{
		printf("%-15s%6.2fԪ\n", p->che_name, p->che_price);
		p = p->next;
	}
	printf("---------------------------------------------------------------------------\n\n");
}

void save(record* head)
{
	rewind(file_rec);
	record* tp = head;
	while (tp != NULL)
	{
		fprintf(file_rec, "%d ", tp->num_check);
		fprintf(file_rec, "%s %s %d %s "
			, tp->pat.name_pat
			, tp->pat.sex
			, tp->pat.age
			, tp->pat.tag_id);
		fprintf(file_rec, "%s %s %s %d "
			, tp->doc.name_doc
			, tp->doc.level
			, tp->doc.sub
			, tp->doc.num_work);
		fprintf(file_rec, "%s ", tp->out_doc);
		int i = 0, j = 0;
		while (1)
		{
			fprintf(file_rec, "%s ", tp->tre.che.type[i]);
			if (strcmp("#", tp->tre.che.type[i]) == 0)
				break;
			fprintf(file_rec, "%.2f ", tp->tre.che.cost_term[i]);
			i++;
		}
		while (1)//�ڶ���#֮ǰ��ѭ������ҩƷ����������
		{
			fprintf(file_rec, "%s ", tp->tre.pil.name_pill[j]);
			if (strcmp("#", tp->tre.pil.name_pill[j]) == 0)
				break;
			fprintf(file_rec, "%.2f %d "
				, tp->tre.pil.cost_perpill[j]
				, tp->tre.pil.num_pill[j]);
			j++;
		}
		fprintf(file_rec, "%04d %04d %d"									//����סԺ��Ϣ����
			, tp->tre.hos.time_start
			, tp->tre.hos.time_end
			, tp->tre.hos.deposit);
		if (tp->next != NULL)
			fprintf(file_rec, "\n");
		tp = tp->next;
	}
	//fclose(file_rec);
	printf("\n����ɹ���\n");
}

//int turndate(char data[20])  //ת�������ַ���Ϊ��λ���֣�����8����-1��
//{
//	char* s = data;
//	int month_num = 0, m = 0, n = 0, p = 0;
//	char b[4], c[3], d[3];
//	strcpy(b, s);
//	b[3] = '\0';
//	s += 4;
//	strcpy(c, s);
//	c[2] = '\0';
//	s += 3;
//	strcpy(d, s);
//	d[2] = '\0';
//	n = (int)(c[0] - 48);
//	p = (int)(c[1] - 48);
//	m = ((int)d[0] - 48) * 10 + (int)d[1] - 48;
//	if (strcmp(b, "Jan") == 0) {
//		if (m >= 8)
//			month_num += 100 + n * 10 + p;
//		else month_num += 100 + n * 10 + p - 1;
//	}
//	if (strcmp(b, "Feb") == 0) {
//		if (m >= 8)
//			month_num += 200 + n * 10 + p;
//		else month_num += 200 + n * 10 + p - 1;
//	}
//	if (strcmp(b, "Mar") == 0) {
//		if (m >= 8)
//			month_num += 300 + n * 10 + p;
//		else month_num += 300 + n * 10 + p - 1;
//	}
//	if (strcmp(b, "Apr") == 0) {
//		if (m >= 8)
//			month_num += 400 + n * 10 + p;
//		else month_num += 400 + n * 10 + p - 1;
//	}
//	if (strcmp(b, "May") == 0) {
//		if (m >= 8)
//			month_num += 500 + n * 10 + p;
//		else month_num += 500 + n * 10 + p - 1;
//	}
//	if (strcmp(b, "Jun") == 0) {
//		if (m >= 8)
//			month_num = 600 + n * 10 + p;
//		else month_num = 600 + n * 10 + p - 1;
//	}
//	if (strcmp(b, "Jul") == 0) {
//		if (m >= 8)
//			month_num = 700 + n * 10 + p;
//		else month_num = 700 + n * 10 + p - 1;
//	}
//	if (strcmp(b, "Aug") == 0) {
//		if (m >= 8)
//			month_num = 800 + n * 10 + p;
//		else month_num = 800 + n * 10 + p - 1;
//	}
//	if (strcmp(b, "Sep") == 0) {
//		if (m >= 8)
//			month_num = 900 + n * 10 + p;
//		else month_num = 900 + n * 10 + p - 1;
//	}
//	if (strcmp(b, "Oct") == 0) {
//		if (m >= 8)
//			month_num += 1000 + n * 10 + p;
//		else month_num += 1000 + n * 10 + p - 1;
//	}
//	if (strcmp(b, "Nov") == 0) {
//		if (m >= 8)
//			month_num = 1100 + n * 10 + p;
//		else month_num = 1100 + n * 10 + p - 1;
//	}
//	if (strcmp(b, "Dec") == 0) {
//		if (m >= 8)
//			month_num = 1200 + n * 10 + p;
//		else month_num = 1200 + n * 10 + p - 1;
//	}
//	return month_num;
//}

int turndate(char data[20])  //ת�������ַ���Ϊ��λ���֣�����8����-1��
{
	char* s = data;
	int month_num = 0, m = 0, n = 0, p = 0, i;
	char b[5], c[3], d[3];
	for (i = 0; i < 3; i++)
		b[i] = *(s + i);
	b[3] = '\0';
	for (i = 4; i < 6; i++)
		c[i - 4] = *(s + i);
	c[2] = '\0';
	for (i = 7; i < 9; i++)
		d[i - 7] = *(s + i);
	d[2] = '\0';
	n = (int)(c[0] - 48);
	p = (int)(c[1] - 48);
	m = ((int)d[0] - 48) * 10 + (int)d[1] - 48;
	if (strcmp(b, "Jan") == 0) {
		if (m >= 8)
			month_num += 100 + n * 10 + p;
		else month_num += 100 + n * 10 + p - 1;
	}
	if (strcmp(b, "Feb") == 0) {
		if (m >= 8)
			month_num += 200 + n * 10 + p;
		else month_num += 200 + n * 10 + p - 1;
	}
	if (strcmp(b, "Mar") == 0) {
		if (m >= 8)
			month_num += 300 + n * 10 + p;
		else month_num += 300 + n * 10 + p - 1;
	}
	if (strcmp(b, "Apr") == 0) {
		if (m >= 8)
			month_num += 400 + n * 10 + p;
		else month_num += 400 + n * 10 + p - 1;
	}
	if (strcmp(b, "May") == 0) {
		if (m >= 8)
			month_num += 500 + n * 10 + p;
		else month_num += 500 + n * 10 + p - 1;
	}
	if (strcmp(b, "Jun") == 0) {
		if (m >= 8)
			month_num = 600 + n * 10 + p;
		else month_num = 600 + n * 10 + p - 1;
	}
	if (strcmp(b, "Jul") == 0) {
		if (m >= 8)
			month_num = 700 + n * 10 + p;
		else month_num = 700 + n * 10 + p - 1;
	}
	if (strcmp(b, "Aug") == 0) {
		if (m >= 8)
			month_num = 800 + n * 10 + p;
		else month_num = 800 + n * 10 + p - 1;
	}
	if (strcmp(b, "Sep") == 0) {
		if (m >= 8)
			month_num = 900 + n * 10 + p;
		else month_num = 900 + n * 10 + p - 1;
	}
	if (strcmp(b, "Oct") == 0) {
		if (m >= 8)
			month_num += 1000 + n * 10 + p;
		else month_num += 1000 + n * 10 + p - 1;
	}
	if (strcmp(b, "Nov") == 0) {
		if (m >= 8)
			month_num = 1100 + n * 10 + p;
		else month_num = 1100 + n * 10 + p - 1;
	}
	if (strcmp(b, "Dec") == 0) {
		if (m >= 8)
			month_num = 1200 + n * 10 + p;
		else month_num = 1200 + n * 10 + p - 1;
	}
	return month_num;
}