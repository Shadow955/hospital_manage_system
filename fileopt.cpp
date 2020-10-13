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
int openfile() {															//文件读入函数，成功返回1，失败返回0
	file_rec = fopen("test.txt", "r+");							//读取文件并判断是否成功打开
	file_pill = fopen("pill.txt", "r");
	file_doc = fopen("doc.txt", "r");
	file_che = fopen("check.txt", "r");
	if (file_rec == NULL||file_pill==NULL||file_doc==NULL||file_che==NULL)
	{
		printf("文件打开失败！请检查源文件！\n");		//打开失败结束并返回上层
		return 0;
	}
	else
	{
		printf("文件打开成功！\n");
		return 1;
	}
}

char* gettime()
{
	//更新当前的time_t 变量为当前系统时钟
	time(&t);
	//ctime（）返回字符串类型的 time_t 变量格式
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
	record* rec_head = (record*)malloc(sizeof(record));		//建立头节点
	rec_head->next = NULL;
	record* tp;
	record* pre = NULL;
	tp = rec_head;
	while (!feof(file_rec))																//循环读入直至文件末尾
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
		while(1)//在读至#之前，循环读入药品单价与数量
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
		fscanf(file_rec, "%d%d%d"									//读入住院信息部分
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
	printf("诊疗记录链表构建成功！\n");
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
	printf("药品链表构建成功！\n");
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
	printf("检查项目链表构建成功！\n");
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
	printf("医生链表构建成功！\n");
	return (doc_head);
}

void printf_number(record* rec_head,pill_term* pill_head,che_term* che_head,doctor* doc_head) {
	int number1;//保存输入的数字
	printf("请输入功能对应的数字：\n1 : 打印某科室诊疗信息\n2 : 打印某医生诊疗信息\n");
	printf("3 : 打印某患者历史诊疗记录\n4 : 打印某段时间内的诊疗记录\n");
	printf("5 : 浏览全部医生数据\n6 : 浏览药品库数据\n7 : 浏览各项检查费用\n");
	scanf("%d", &number1);
	switch (number1) {
	case 1: 
		outsub_doc(rec_head); break;//打印某科室诊疗信息
	case 2: 
		outname_doc(rec_head); break;//打印某医生诊疗信息
	case 3: 
		outpatient_tag(rec_head); break;//打印某患者历史诊疗记录
	case 4: 
		//outtime_limit(rec_head); break;//打印某段时间内的诊疗记录
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
	printf("挂号：%07d\n患者姓名：%s\n性别：%s  年龄：%d  身份证尾号：%s\n"
		, p->num_check
		, p->pat.name_pat
		, p->pat.sex
		, p->pat.age
		, p->pat.tag_id);
	printf("\n主治医师：%s\n级别：%s  科室：%s  医生工号：%07d\n"
		, p->doc.name_doc
		, p->doc.level
		, p->doc.sub
		, p->doc.num_work);
	printf("医生出诊时间：%s", p->out_doc);
	int i = 0, j = 0;
	printf("\n\n患者检查情况：\n 检查项目           价格\n");
	while (strcmp("#", p->tre.che.type[i]) != 0)//在读至#之前，循环输出检查项目名称与费用
	{
		printf("%-16s   %6.2f元\n", p->tre.che.type[i], p->tre.che.cost_term[i]);
		i++;
	}
	printf("\n患者开药情况：\n 药品名              单价      数量\n");
	while (strcmp("#", p->tre.pil.name_pill[j]) != 0)//在读至#之前，循环输出药品单价与数量
	{
		printf("%-16s   %6.2f元   %3d\n"
			, p->tre.pil.name_pill[j]
			, p->tre.pil.cost_perpill[j]
			, p->tre.pil.num_pill[j]);
		j++;
	}
	printf("\n住院开始时间:%04d\n预计出院时间:%04d\n押金:%d"									//输出住院信息部分
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
		printf("%-15s%6.2f元\n", p->pill_name, p->pill_price);
		p = p->next;
	}
	printf("---------------------------------------------------------------------------\n\n");
}

void cheprint(che_term* p)
{
	printf("\n---------------------------------------------------------------------------\n");
	while (p->next!= NULL)
	{
		printf("%-15s%6.2f元\n", p->che_name, p->che_price);
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
		while (1)//在读至#之前，循环读入药品单价与数量
		{
			fprintf(file_rec, "%s ", tp->tre.pil.name_pill[j]);
			if (strcmp("#", tp->tre.pil.name_pill[j]) == 0)
				break;
			fprintf(file_rec, "%.2f %d "
				, tp->tre.pil.cost_perpill[j]
				, tp->tre.pil.num_pill[j]);
			j++;
		}
		fprintf(file_rec, "%04d %04d %d"									//读入住院信息部分
			, tp->tre.hos.time_start
			, tp->tre.hos.time_end
			, tp->tre.hos.deposit);
		if (tp->next != NULL)
			fprintf(file_rec, "\n");
		tp = tp->next;
	}
	//fclose(file_rec);
	printf("\n保存成功！\n");
}

//int turndate(char data[20])  //转化日期字符串为四位数字（不到8点则-1）
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

int turndate(char data[20])  //转化日期字符串为四位数字（不到8点则-1）
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