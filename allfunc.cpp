#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include"base_struct.h"
#include"allfunc.h"
#include"fileopt.h"

int year = 2020;
float sumcheck(int tag_check,float cost_term[])              //计算检查总费用函数
{
	int i ;
	float sum = 0;
	for (i = 0; i < tag_check; i++)
	{
		sum = sum + cost_term[i];
	}
	return sum;
}

float sumpill(int tag_pill, float cost_perpill[30], int num_pill[30])        //计算药品总费用函数
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

int date_turn(char a[8])                 //将8位日期转化为天数
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

int days_hosp(int time_start, int time_end)                  //计算住院时长函数
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

int cost_hos(int a,int b,int c)           //住院费用函数
{
	int sum = 0;
	sum = sum + a + b + (c * 100);
	return sum;
}

record* getrecord()    //录入记录
{
	record* temp = (record*)malloc(sizeof(record));
	temp->next = NULL;
	printf("请输入挂号\n");
	scanf("%d", &(temp->num_check));
	printf("\n以下为输入患者信息，每条信息以回车结束\n\n请输入患者姓名：\n");
	scanf("%s", &(temp->pat.name_pat));getchar();
	printf("性别：\n");
	scanf("%s", temp->pat.sex);getchar();
	printf("年龄：\n");
	scanf("%d", &temp->pat.age);
	printf("身份证号后四位：\n");
	scanf("%s", temp->pat.tag_id);getchar();
	printf("\n以下为输入医生信息，每条信息以回车结束\n\n请输入主治医生姓名：\n");
	scanf("%s",&(temp->doc.name_doc));getchar();
	printf("医生级别：\n");
	scanf("%s", temp->doc.level);getchar();
	printf("医生科室：\n");
	scanf("%s", temp->doc.sub);getchar();
	printf("医生工号：\n");
	scanf("%d", &temp->doc.num_work);getchar();
	/*printf("输入就诊时间：\n");
	scanf("%s", temp->out_doc);getchar();*/
	strcpy(temp->out_doc , gettime());
	printf("请输入各项检查及其费用,输入“#”以结束\n");
	(temp->tre.che.tag_check) = 0; 
	bool flag_che = true; 
	int i = 0;
	while(flag_che)
	{
		printf("输入检查项目名称：\n");
		scanf("%s", &(temp->tre.che.type[i]));
		if (strcmp("#", temp->tre.che.type[i])==0)
		{
			flag_che = false;
			(temp->tre.che.cost_check) = sumcheck((temp->tre.che.tag_check), (temp->tre.che.cost_term));
			break;
		}
		printf("输入该项检查费用：\n");
		scanf("%f", &(temp->tre.che.cost_term[i]));
		(temp->tre.che.tag_check)++;
		i++;
	}
	printf("请输入各药品名称及其数量和单价,输入“#”以结束\n");
	(temp->tre.pil.tag_pill) = 0; 
	bool flag_pil = true; 
	i = 0;
	while (flag_pil)
	{
		printf("输入药品名称：\n");
		scanf("%s", temp->tre.pil.name_pill[i]);
		if (strcmp("#", temp->tre.pil.name_pill[i])==0)
		{
			flag_pil = false;
			(temp->tre.pil.cost_pill) = sumpill(temp->tre.pil.tag_pill, temp->tre.pil.cost_perpill, temp->tre.pil.num_pill);
			break;
		}
		printf("输入药品单价：\n");
		scanf("%f", &(temp->tre.pil.cost_perpill[i]));
		printf("输入药品数量：\n");
		scanf("%d", &temp->tre.pil.num_pill[i]);
		(temp->tre.pil.tag_pill)++;
		i++;
	}
	printf("\n请输入开始住院时间：\n");
	scanf("%04d", &(temp->tre.hos.time_start));
	printf("\n请输入预计出院时间：\n");
	scanf("%04d", &(temp->tre.hos.time_end));
	printf("\n请输入缴纳住院押金：\n");
	scanf("%d",&(temp->tre.hos.deposit));
	(temp->tre.hos.days_hos) = days_hosp(temp->tre.hos.time_start, temp->tre.hos.time_end);
	printf("\n诊疗记录录入成功！\n");
	return temp;
}

void outpatient_tag(struct record* head)   //查找患者身份证号并输出
{
	char tag_in[5];
	printf("请输入患者身份证后四位：\n");
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

void outpatient_name(struct record* head)		//检索患者姓名并输出
{
	char name[30];
	printf("请输入需要查询的患者姓名：\n");
	scanf("%s", &name);
	record* p;
	p = head; 
	int t, x = 0,m = 0;
	while (strcmp((p->pat.name_pat) , name) == 0&& p != NULL)
	{
		x = x + 1;
		printf("%d %s %d %s\n", x, ((p->pat).name_pat), ((p->pat).age),p->pat.tag_id);//输出患者信息部分
		p = p->next;
	}
	if (x == 0)
	{
		printf("查无此人！\n");
		return;
	}
	printf("请输入需要查询的患者序号：\n");
	scanf("%d", &t);
	for (strcmp((p->pat.name_pat), name) == 1; p != NULL; )
	{
		m = m + 1;
		if (m == t) 
		{
			printf("%s %d ", (p->pat.name_pat), (p->pat.age));//输出患者信息部分
			printf("%s %s %s %d ", p->doc.name_doc, p->doc.level, p->doc.sub, p->doc.num_work);//输出医生信息部分
			printf("%s ", p->out_doc);                         //输出出诊时间
			for (int i = 0; i < (p->tre.che.tag_check); i++)
			{
				printf("%s ", p->tre.che.type[i]);       //输出检查类型
				printf("%f ", p->tre.che.cost_term[i]);  //输出单项检查的费用
			}
			for (int i = 0; i < (p->tre.pil.tag_pill); i++)
			{
				printf("%s ", p->tre.pil.name_pill[i]);   //输出药品名称
				printf("%d ", p->tre.pil.cost_perpill[i]);//输出药品单价
				printf("%d ", p->tre.pil.num_pill[i]);    //输出药品数量
			}
			printf("%d  %d ", p->tre.hos.time_start, p->tre.hos.time_end);//输出住,出院时间
			printf("%d %d %d\n", p->tre.hos.days_hos, p->tre.hos.cost_hos, p->tre.hos.deposit);//输出住院天数,住院费用,住院押金
		}
	}
	return;
}

void outsub_doc(struct record* head)   //科室检索
{
	char sub_in[10];
	record* p = head;
	printf("请输入需要查询的科室\n");
	scanf("%s", sub_in);
	//for (strcmp((p->doc.sub), sub_in) == 1; q != NULL;)
	//{
	//	
	//	printf("%s %d ", (p->pat.name_pat), (p->pat.age));//输出患者信息部分
	//	printf("%s %s %s %d", p->doc.sub, p->doc.name_doc, p->doc.level, p->doc.num_work);//输出医生信息部分
	//	printf("%s ", p->out_doc);                         //输出出诊时间
	//	for (int i = 0; i < (p->tre.che.tag_check); i++)
	//	{
	//		printf("%s ", p->tre.che.type[i]);       //输出检查类型
	//		printf("%f ", p->tre.che.cost_term[i]);  //输出单项检查的费用
	//	}
	//	for (int i = 0; i < (p->tre.pil.tag_pill); i++)
	//	{
	//		printf("%s ", p->tre.pil.name_pill[i]);   //输出药品名称
	//		printf("%d ", p->tre.pil.cost_perpill[i]);//输出药品单价
	//		printf("%d ", p->tre.pil.num_pill[i]);    //输出药品数量
	//	}
	//	printf("%d  %d ", p->tre.hos.time_start, p->tre.hos.time_end);//输出住,出院时间
	//	printf("%d %d %d\n", p->tre.hos.days_hos, p->tre.hos.cost_hos, p->tre.hos.deposit);//输出住院天数,住院费用,住院押金
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

void outname_doc(struct record* head)  //医生工号检索
{
	int num;
	record* p = head; 
	printf("请输入需要查询的医生工号\n");
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
 //       printf("%d %s %s %s", p->doc.num_work, p->doc.name_doc, p->doc.sub, p->doc.level);//输出医生信息部分
	//	printf("%s %d ", (p->pat.name_pat), (p->pat.age));//输出患者信息部分
	//	printf("%s ", p->out_doc);                         //输出出诊时间
	//	for (int i = 0; i < (p->tre.che.tag_check); i++)
	//	{
	//		printf("%s ", p->tre.che.type[i]);       //输出检查类型
	//		printf("%f ", p->tre.che.cost_term[i]);  //输出单项检查的费用
	//	}
	//	for (int i = 0; i < (p->tre.pil.tag_pill); i++)
	//	{
	//		printf("%s ", p->tre.pil.name_pill[i]);   //输出药品名称
	//		printf("%d ", p->tre.pil.cost_perpill[i]);//输出药品单价
	//		printf("%d ", p->tre.pil.num_pill[i]);    //输出药品数量
	//	}
	//	printf("%d  %d ", p->tre.hos.time_start, p->tre.hos.time_end);//输出住,出院时间
	//	printf("%d %d %d\n", p->tre.hos.days_hos, p->tre.hos.cost_hos, p->tre.hos.deposit);//输出住院天数,住院费用,住院押金
	//}
	return;
}

void outtime_limit(struct record* head)        //时间段检索
{
	record* p, * q;
	p = head; q = p->next;
	char time_start[8], time_end[8];
	int start, end, tag_time;
	printf("请输入起始时间以及结束时间：\n");
	scanf("%s%s", &time_start, &time_end);
	start = date_turn(time_start); end = date_turn(time_end);
	
	int t, x = 0; t = 0;
	for (q != NULL;;) 
	{
		tag_time=date_turn(p->out_doc);
		for ((tag_time>=start)&&(tag_time<=end);;)
	    {
		    printf("%s ", p->out_doc);                         //输出出诊时间
		    printf("%d %s %s %s", p->doc.num_work, p->doc.name_doc, p->doc.sub, p->doc.level);//输出医生信息部分
		    printf("%s %d ", (p->pat.name_pat), (p->pat.age));//输出患者信息部分
		    for (int i = 0; i < (p->tre.che.tag_check); i++)
		    {
			    printf("%s ", p->tre.che.type[i]);       //输出检查类型
			    printf("%f ", p->tre.che.cost_term[i]);  //输出单项检查的费用
		    }
		    for (int i = 0; i < (p->tre.pil.tag_pill); i++)
		    {
			    printf("%s ", p->tre.pil.name_pill[i]);   //输出药品名称
			    printf("%d ", p->tre.pil.cost_perpill[i]);//输出药品单价
			    printf("%d ", p->tre.pil.num_pill[i]);    //输出药品数量
		    }
		    printf("%d  %d ", p->tre.hos.time_start, p->tre.hos.time_end);//输出住,出院时间
		    printf("%d %d %d\n", p->tre.hos.days_hos, p->tre.hos.cost_hos, p->tre.hos.deposit);//输出住院天数,住院费用,住院押金
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
		printf("%s %d ", (p->pat.name_pat), (p->pat.age));//输出患者信息部分
		printf("%s %s %s %d ", p->doc.name_doc, p->doc.level, p->doc.sub, p->doc.num_work);//输出医生信息部分
		printf("%s ", p->out_doc);                         //输出出诊时间
		for (int i = 0; i < (p->tre.che.tag_check); i++)
		{
			printf("%s ", p->tre.che.type[i]);       //输出检查类型
			printf("%f ", p->tre.che.cost_term[i]);  //输出单项检查的费用
		}
		for (int i = 0; i < (p->tre.pil.tag_pill); i++)
		{
			printf("%s ", p->tre.pil.name_pill[i]);   //输出药品名称
			printf("%d ", p->tre.pil.cost_perpill[i]);//输出药品单价
			printf("%d ", p->tre.pil.num_pill[i]);    //输出药品数量
		}
		printf("%d  %d ", p->tre.hos.time_start, p->tre.hos.time_end);//输出住,出院时间
		printf("%d %d %d\n", p->tre.hos.days_hos, p->tre.hos.cost_hos, p->tre.hos.deposit);//输出住院天数,住院费用,住院押金
		if (p->next== NULL)
			return;
		else
			p = p->next; 
		
	}
	return;
}

void del_record(struct record* head)   //删除操作
{
	record* p, * q,* r;
	p = head; q = p->next; r->next = p;
	int x, y; y = 0;
	output(head);
	printf("请选择需要删除的记录");
	scanf("%d", &x);
	for (p != NULL;;)
	{
		y = y + 1;
		if (x == y)
		{
			r->next = q; 
			free(p);
			printf("删除成功！");
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
	printf("请输入患者信息\n");
	scanf("%s%d", &(p->pat.name_pat), &(p->pat.age));
	printf("请输入挂号\n");
	scanf("%d", &(p->num_check));
	printf("请输入医生信息\n");
	scanf("%s%s%s%d", &(p->doc.name_doc), &(p->doc.level), &(p->doc.sub), &(p->doc.num_work));
	printf("请输入出诊时间\n");
	scanf("%s", &(p->out_doc[8]));
	printf("请输入各项检查及其费用,若输入结束请键入‘|’\n");
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
	printf("请输入各药品名称及其数量和单价,若输入结束请键入‘|’\n");
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
	printf("请输入开始住院时间，预计出院时间及已交纳的住院押金\n");
	scanf("%d%d%d", &(p->tre.hos.time_start), &(p->tre.hos.time_end), &(p->tre.hos.deposit));
	(p->tre.hos.days_hos) = days_hosp(p->tre.hos.time_start, p->tre.hos.time_end);
	return;
}

void alter_record(struct record* head)   //修改操作
{
	record* p, * q, * r;
	p = head; q = p->next; r->next = p;
	int x, y; y = 0;
	output(head);
	printf("请选择需要修改的记录");
	scanf("%d", &x);
	for (p != NULL;;)
	{
		y = y + 1;
		if (x == y)
		{
			printf("撤销成功！请重新输入：\n");
			input(q);
		}
		else
		{
			r = p; p = q; q = q->next;
		}
	}
	return;
}

float statistics(struct record* head)    //营业额
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

void yearchange(int a) {                              //改变系统年份
	printf("请输入目标年份：");
	scanf("%d", &a);
	return;
}

bool judge_year(int a) {                             //判断闰年
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

bool judge_name_pat(record* p) {                 //判断姓名
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

bool judge_age(record* p) {                            //判断年龄
	if ((p->pat.age) < 0 && (p->pat.age) > 150) {
		return false;
	}
	return true;
}

bool judge_sex(record* p) {                        //判断性别
	if (strcmp(p->pat.sex, "男") != 0 || strcmp(p->pat.sex, "女") != 0) {
		return false;
	}
	return true;
}

bool judge_tag_id(record* p) {                         //判断身份识别码
	int t = 0;
	for (t = 0; t < 3; t++) {
		if ((p->pat.tag_id[t]) <= '0' && (p->pat.tag_id[t]) >= '9') {
			return false;
		}
	}
	if (strcmp(p->pat.sex, "男") == 0 && (p->pat.tag_id[3]) % 2 == 0) {
		return false;
	}
	if (strcmp(p->pat.sex, "女") == 0 && (p->pat.tag_id[3]) % 2 != 0) {
		return false;
	}
	return true;
}

bool judge_num_check(record* p) {                  //判断挂号
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

bool judge_che_name(record* p, che_term* q) {       //判断检查名称
	int t = 0;
	for (t = 0; t < 19; t++) {
		if (strcmp(q->che_name, p->tre.che.type[p->tre.che.tag_check]) == 0) {
			return true;
		}
		else {
			q = q->next;
		}
	}
	return false;
}

bool judge_pill_name(record* p, pill_term* r) {               //判断药品
	int t = 0;
	for (t = 0; t < 30; t++) {
		if (strcmp(r->pill_name, p->tre.pil.name_pill[p->tre.pil.tag_pill]) == 0) {
			return true;
		}
		else {
			r = r->next;
		}
	}
	return false;
}

bool judge_num_work(record* p, doctor* s) {               //判断医生工号
	int t = 0;
	for (t = 0; t < 30; t++) {
		if (s->num_work == p->doc.num_work) {
			return true;
		}
		else {
			s = s->next;
		}
	}
	return false;
}

bool time(int a, int b) {                             //判断时间
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