#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include"base_struct.h"
#include"allfunc.h"
#include"fileopt.h"

//int year = 2020;
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

float sumpill(int tag_pill, float cost_perpill[], int num_pill[])        //计算药品总费用函数
{
	int i;
	float sum = 0;
	for (i = 0; i < tag_pill ; i++)
	{
		sum = sum + ((cost_perpill[i]) * (num_pill[i]));
	}
	return sum;
}

int date_turn(int time)                 //将4位日期转化为天数
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

int cost_hos(int in,int out,int now)           //住院费用函数
{
	if (out > now)
		return (now - in) * 100;
	else
		return (out - in) * 100;
}

record* getrecord(doctor* doc,pill_term* pill,che_term* che,int tag)    //录入记录
{
	record* temp = (record*)malloc(sizeof(record));
	temp->next = NULL;
	temp->num_check = tag + 1;
	printf("\n以下为输入患者信息，每条信息以回车结束\n\n请输入患者姓名：\n");
	scanf("%s", &(temp->pat.name_pat));getchar();
	while (!judge_name_pat(temp->pat.name_pat))
	{
		printf("姓名输入错误！请检查后重新输入！目前仅支持中文输入\n");
		scanf("%s", &(temp->pat.name_pat));getchar();
	}
	printf("性别：\n");
	scanf("%s", temp->pat.sex);getchar();
	while (!judge_sex(temp->pat.sex))
	{
		printf("性别输入错误！请检查后重新输入\n");
		scanf("%s", &(temp->pat.sex)); getchar();
	}
	printf("年龄：\n");
	scanf("%d", &temp->pat.age); getchar();
	while (!judge_age(temp->pat.age))
	{
		printf("年龄输入错误！请输入1-149的整数 输入小数将向下取证\n");
		scanf("%d", &temp->pat.age); getchar();
	}
	printf("身份证号后四位：\n");
	scanf("%s", temp->pat.tag_id);getchar();
	while (!judge_tag_id(temp->pat.sex, temp->pat.tag_id))
	{
		printf("身份证不符合规范！请检查后重新输入！尾数为x请小写\n");
		scanf("%s", temp->pat.tag_id); getchar();
	}
	printf("请输入医生工号：\n");
	scanf("%d", &temp->doc.num_work);getchar();
	doctor* tpdoc = judge_num_work(temp->doc.num_work, doc);
	while (tpdoc == NULL)
	{
		printf("工号不存在！请检查后重新输入\n");
		scanf("%d", &temp->doc.num_work); getchar();
		tpdoc = judge_num_work(temp->doc.num_work, doc);
	}
	strcpy(temp->doc.name_doc, tpdoc->name_doc);
	strcpy(temp->doc.level, tpdoc->level);
	strcpy(temp->doc.sub, tpdoc->sub);
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
		else {
			che_term* tpche = judge_che_name(temp->tre.che.type[i],che);
			while (tpche==NULL) 
			{
				printf("该检查项目不存在！请检查后重新输入\n");
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
		else
		{
			pill_term* tppill = judge_pill_name(temp->tre.pil.name_pill[i], pill);
			while (tppill==NULL)
			{
				printf("该药品名不存在！请检查后重新输入\n");
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
			printf("输入药品数量：\n");
			scanf("%d", &temp->tre.pil.num_pill[i]);
		}
		(temp->tre.pil.tag_pill)++;
		i++;
	}
	while (1)
	{
		printf("\n请输入开始住院时间（四位数字）：\n");
		scanf("%d", &(temp->tre.hos.time_start));
		while (!JudgeDate(temp->tre.hos.time_start))
		{
			printf("日期输入不合法！请检查后重新输入：\n");
			scanf("%d", &(temp->tre.hos.time_start));
		}
		printf("\n请输入预计出院时间（四位数字）：\n");
		scanf("%d", &(temp->tre.hos.time_end));
		while (!JudgeDate(temp->tre.hos.time_end))
		{
			printf("日期输入不合法！请检查后重新输入：\n");
			scanf("%d", &(temp->tre.hos.time_end));
		}
		if (temp->tre.hos.time_end > temp->tre.hos.time_start)
			break;
		else
			printf("出院时间不能早于住院时间！请重新输入\n");
	}
	int now = turndate(gettime());
	temp->tre.hos.cost_hos = cost_hos(date_turn(temp->tre.hos.time_start), date_turn(temp->tre.hos.time_end), date_turn(now));
	if (now <= temp->tre.hos.time_end)
		DoctorState(temp->doc.num_work, doc);
	printf("\n请输入缴纳住院押金：\n");
	scanf("%d",&(temp->tre.hos.deposit));
	int price = 200 * (date_turn(temp->tre.hos.time_end) - date_turn(temp->tre.hos.time_start));
	if (price < 1000)
		price = 1000;
	while (temp->tre.hos.deposit < price)
	{
		printf("押金不足！至少应缴纳押金%d元，请重新输入\n", price);
		printf("\n请输入缴纳住院押金：\n");
		scanf("%d", &(temp->tre.hos.deposit));
		price = 200 * (date_turn(temp->tre.hos.time_end) - date_turn(temp->tre.hos.time_start));
	}
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
	char name[30]; char patid[100][5];
	bool tag = true; record* p; p = head;
	int x = 0, y = 0, m = 0; char t[5];
	while (tag) {
		printf("请输入需要查询的患者姓名：\n");
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
			printf("查无此人！你想要重新输入吗？\n1.是   2否\n");     //郭志泽
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
void outsub_doc(struct record* head)   //科室检索
{
	char sub_in[10];
	record* p = head;
	printf("请输入需要查询的科室\n");
	scanf("%s", sub_in);
	while (strcmp(sub_in, "内科") != 0 &&
		strcmp(sub_in, "外科") != 0 &&
		strcmp(sub_in, "儿科") != 0 &&
		strcmp(sub_in, "妇产科") != 0 &&
		strcmp(sub_in, "传染科") != 0 &&
		strcmp(sub_in, "放射科") != 0 &&
		strcmp(sub_in, "肿瘤科") != 0)
	{
		printf("科室不存在！请检查后重新输入\n");
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

void outname_doc(struct record* head)  //医生工号检索
{
	int num, x = 0;
	record* p = head; 
	printf("请输入需要查询的医生工号\n");
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
		printf("未搜索到该工号！\n");
}


void del_record(record* head,record* t)   //删除操作
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
		printf("删除成功！");
	}
}


void alter_record(record* head,record* t,doctor* doc,pill_term* pill,che_term* che)   //修改操作
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
		int tp = p->num_check;//暂时保存挂号
		after = p->next;
		printf("请重新输入诊疗记录！\n");
		p = getrecord(doc, pill, che,999);
		p->num_check = tp;
		pre->next = p;
		p->next = after;
		printf("诊疗记录修改成功！\n");
	}
}

void statistics(record* head)    //营业额
{
	float turn = 0;
	record* p = head; 
	while (p != NULL)
	{
		turn = turn+ (p->tre.che.cost_check) + (p->tre.pil.cost_pill) + (float)(p->tre.hos.cost_hos);
		p = p->next;
	}
	printf("医院现有资金：%.2f元\n", turn);
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

bool judge_name_pat(char* name) {                 //判断姓名
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

bool judge_age(int age) {                            //判断年龄
	if (age < 0 || age > 150) {
		return false;
	}
	else
		return true;
}

bool judge_sex(char* sex) {                        //判断性别
	if (strcmp(sex, "男") != 0 && strcmp(sex, "女") != 0) {
		return false;
	}
	else
		return true;
}

bool judge_tag_id(char* sex,char* id) {                         //判断身份证尾号
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
	if (strcmp(sex, "男") == 0 && (id[2]) % 2 == 0) {
		flag=false;
	}
	if (strcmp(sex, "女") == 0 && (id[2]) % 2 != 0) {
		flag=false;
	}
	return flag;
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

che_term* judge_che_name(char* p, che_term* q) {				 //判断检查名称是否正确
	bool flag = false;
	while (q != NULL) {
		if (strcmp(p, q->che_name) == 0)
			return q;
		q = q->next;
	}
	return NULL;
}

pill_term* judge_pill_name(char* p, pill_term* q) {               //判断药品名称是否正确
	while (q != NULL) {
		if (strcmp(p, q->pill_name) == 0)
			return q;
		q = q->next;
	}
	return NULL;
}

doctor* judge_num_work(int num, doctor* s) {					//判断医生工号
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

void outtime_limit(struct record* head)        //时间段检索
{
	record* p = head;
	int start, end, tag_time;
	while (1)
	{
		printf("请输入起始时间(4位整数，精确到日)：\n");
		scanf("%d", &start);
		while (!JudgeDate(start))
		{
			printf("日期不合法！请重新输入\n");
			printf("请输入起始时间(4位整数，精确到日)：\n");
			scanf("%d", &start);
		}
		printf("请输入终止时间(4位整数，精确到日)：\n");
		scanf("%d", &end);
		while (!JudgeDate(end))
		{
			printf("日期不合法！请重新输入\n");
			printf("请输入终止时间(4位整数，精确到日)：\n");
			scanf("%d", &end);
		}
		if (start < end)
			break;
		else
			printf("终止日期必须在起始时间之后！请重新输入");
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
		printf("未找到该时间段内的诊疗记录！");
}