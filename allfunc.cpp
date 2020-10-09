#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include"base_struct.h"
#include"allfunc.h"

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

void getrecord(struct record* head)    //录入记录
{
	record* temp = (record*)malloc(sizeof(record));
	temp->next = NULL;
	record* p, * q;
	p = head; q = p->next;
	while (q != NULL)
	{
		p = q;
		q = q->next;
	}
	if (q == NULL)
	{
		printf("请输入患者信息\n");
		p->next = temp; q = temp;
		scanf("%s %d", &(q->pat.name_pat), &(q->pat.age));
		printf("请输入挂号\n");
		scanf("%d", &(q->num_check));
		printf("请输入医生信息\n");
		scanf("%s%s%s%d",&(q->doc.name_doc) , &(q->doc.level), &(q->doc.sub), &(q->doc.num_work));
		printf("请输入出诊时间\n");
		scanf("%s", &(q->out_doc[8]));
		printf("请输入各项检查及其费用,若输入结束请键入‘|’\n");
		(q->tre.che.tag_check) = 0; bool flag_che = true; int i = 0;
		while(flag_che)
		{
			scanf("%s", &(q->tre.che.type[i]));
			if ((q->tre.che.type[i][0]) == '|')
			{
				flag_che = false;
				(q->tre.che.cost_check) = sumcheck((q->tre.che.tag_check), (q->tre.che.cost_term));
				break;
			}
			scanf("%f", &(q->tre.che.cost_term[i]));
			(q->tre.che.tag_check)++;
		}
		printf("请输入各药品名称及其数量和单价,若输入结束请键入‘|’\n");
		(q->tre.pil.tag_pill) = 0; bool flag_pil = true; i = 0;
		while (flag_pil)
		{
			scanf("%s", &(q->tre.pil.name_pill[i]));
			if ((q->tre.pil.name_pill[i][0]) == '|')
			{
				flag_pil = false;
				(q->tre.pil.cost_pill) = sumpill(q->tre.pil.tag_pill, q->tre.pil.cost_perpill, q->tre.pil.num_pill);
				break;
			}
			scanf("%d%d", &(q->tre.pil.cost_perpill[i]), &(q->tre.pil.num_pill[i]));
			(q->tre.pil.tag_pill)++;
		}
		printf("请输入开始住院时间，预计出院时间及已交纳的住院押金\n");
		scanf("%d%d%d", &(q->tre.hos.time_start), &(q->tre.hos.time_end), &(q->tre.hos.deposit));
		(q->tre.hos.days_hos) = days_hosp(q->tre.hos.time_start, q->tre.hos.time_end);
	}
    free(temp);
	return;
}

void outpatient_tag(struct record* head, int tag_in)   //依据患者识别码输出数据
{
	printf("请输入患者身份识别码");
	scanf("%d", &tag_in);
	record* p, * q;
	p = head; q = head->next;
	for (((p->pat).tag_pat) = tag_in; q != NULL;)
	{
		printf("%s %d ", ((p->pat).name_pat), ((p->pat).age));//输出患者信息部分
		printf("%s %s %s %d", ((p->doc).name_doc), ((p->doc).level), ((p->doc).sub), ((p->doc).num_work));//输出医生信息部分
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
		p = q; q = q->next;
	}
	return;
}

void outpatient_name(struct record* head)		//检索患者姓名并输出
{
	char name[30];
	printf("请输入需要查询的患者姓名：\n");
	scanf("%s", &name);
	record* p, * q;
	p = head; q = p->next;
	int m, t, x = 0; t = 0; m = 0;
	while (strcmp((p->pat.name_pat) , name) == 0&& q != NULL)
	{
		x = x + 1;
		printf("%d %s %d\n", x, ((p->pat).name_pat), ((p->pat).age));//输出患者信息部分
		p = q; q = q->next;
	}
	if (x == 0)
	{
		printf("查无此人！\n");
		return;
	}
	printf("请输入需要查询的患者序号：\n");
	scanf("%d", &t);
	for (strcmp((p->pat.name_pat), name) == 1; q != NULL; )
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
	char sub_in[5];
	record* p, * q;
	p = head; q = p->next;
	int t, x = 0; t = 0;
	printf("请输入需要查询的科室\n");
	scanf("%s", &sub_in);
	for (strcmp((p->doc.sub), sub_in) == 1; q != NULL;)
	{
		
		printf("%s %d ", (p->pat.name_pat), (p->pat.age));//输出患者信息部分
		printf("%s %s %s %d", p->doc.sub, p->doc.name_doc, p->doc.level, p->doc.num_work);//输出医生信息部分
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
	return;
}

void outname_doc(struct record* head)  //医生工号检索
{
	int num;
	record* p, * q;
	p = head; q = p->next;
	int t, x = 0; t = 0;
	printf("请输入需要查询的医生工号\n");
	scanf("%d", &num);
	for ((p->doc.num_work) = num; q != NULL;)
	{
        printf("%d %s %s %s", p->doc.num_work, p->doc.name_doc, p->doc.sub, p->doc.level);//输出医生信息部分
		printf("%s %d ", (p->pat.name_pat), (p->pat.age));//输出患者信息部分
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
	while (p!= NULL)
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
		p = p->next; 
		if(q!=NULL)
			q = q->next;
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
	float turnover = 0;
	record* p, * q;
	p = head; q = p->next;
	for (p != NULL;;)
	{
		turnover = turnover + (p->tre.che.cost_check) + (p->tre.pil.cost_pill) + (float)(p->tre.hos.cost_hos);
		p = q; q = q->next;
	}
	return turnover;
}