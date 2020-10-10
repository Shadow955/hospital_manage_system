#include"base_struct.h"
#include<stdio.h>
#include"fileopt.h"
#include<malloc.h>
#include<string.h>
float info_turn(record* rec_head)                                   //统计目前营业额，不含住院押金
{
	float sum;
	record* p = rec_head->next;
	if (p != NULL) {
		sum +=(p->tre.che.cost_check)+(p->tre.pil.cost_pill)+(p->tre.hos.cost_hos);
		p = p->next;
	}
	else return sum;
}

void alter_record(int tag_bat_1,record* rec_head)                   //按照财务规范，修改诊疗记录，此为修改押金，是否需要修改其他信息？
{
	record* p = rec_head->next;
	int a = 1, m;
	m = tag_bat_1;
	while (a)
	{
		if ((p != NULL) && ((p->pat.tag_id) != m))
			p = p->next;
			if (p == NULL)
				printf("查无此人");
			if (p != NULL) {
				(p->tre.hos.deposit) = 0;                //撤销错误诊疗信息，是给予该信息NULL还是0？
					printf("请输入正确的押金：");
					scanf("%d", &(p->tre.hos.deposit));      //是否需要判断押金格式?
			}
		printf("继续请输入1，退出输入0");
		scanf("%d", &a);
		if (a = 0)
			return;
		else {
			printf("请输入要修改信息的挂号");
			scanf("%d", &m);
		}/*if*/									
	}/*while*/
}

void alter_record_out_time(record* rec_head)                            //修改出院时间
{
	record* p = rec_head;
	printf("请输入要修改信息的挂号：");
	int m;
	scanf("%d", &m);
	while (p != NULL) 
	{
		if((p->num_check)==m)
		{
			printf("请输入要改成的日期：");
			scanf("%s", &(p->out_doc));                            //出诊时间为啥是char型？而不是int型
		}
	}

}

void delete_record(int tag_bat_1,record* rec_head)                            //通过挂号的号码，删除诊疗信息
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
			printf("查无此人");
		else {
			p = p->next;
				free(q->next);
				q->next = p;
		}
		printf("继续请输入1，退出输入0");
		scanf("%d", &a);
		if (a = 0)
			return;
		else {
			printf("请输入要修改信息的挂号");
			scanf("%d", &m);
		}
	}
}

void print_time_record(int time1, int time2,record* rec_head)                        //打印某段时间内的所有诊疗记录
{
	record* p = rec_head->next;                                          //声明节点并标明其位置
	while(p != NULL){
		if ((p->tre.hos.time_start > time1) || (p->tre.hos.time_start == time1) || (p->tre.hos.time_start < time2))   //判断时间范围并打印诊疗信息
			printf("%d", p->num_check);
		printf("%s\n%d\n%d\n", p->pat.name_pat, p->pat.age, p->pat.tag_id);                                          //患者信息
		printf("%s\n%s\n%d\n", p->doc.name_doc, p->doc.sub, p->doc.num_work);                         //医生信息
		int i; 
		for (i = 0;i < (p->tre.che.tag_check);i++)                                                                     //检查信息
			printf("%s    %f    %d\n", p->tre.che.type[i], p->tre.che.cost_term[i], p->tre.che.cost_check);
		for (i = 0;i < (p->tre.pil.tag_pill);i++)                                                                      //开药信息
			printf("%s    %f    %d    %f\n", p->tre.pil.name_pill[i], p->tre.pil.cost_perpill[i], p->tre.pil.num_pill[i], p->tre.pil.cost_pill);
		printf("%d    %d    %d\n", p->tre.hos.time_start, p->tre.hos.time_end, p->tre.hos.deposit);                   //诊疗情况
		if ((p->out_doc) != NULL)                                                                                     //出院信息
			printf("%d", p->out_doc);                                                                                
		p = p->next;
	}/*while*/
}

void print_sub_record(record*rec_head)                                      //打印某科室信息
{
	printf("请输入你要打印信息的科室：");
	char m[5];                                               //保存输入的科室号
	scanf("%s", &m);
	record* p = rec_head->next;
	while(p != NULL)
	{
		if (strcmp(p->doc.sub, m) == 0) {                    //检索科室并输出诊疗信息
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

void print_doc_record(record* rec_head)                                                                   //打印某医生历史诊疗信息，工号检索
{
	record* p = rec_head->next;
	printf("请输入要查找的医生的工号：");
	int m;
	scanf("%d", &m);
	while(p != NULL) 
	{
		if ((p->doc.num_work) == m)
		{
			printf("%d", p->num_check);
			printf("%s\n%d\n%d\n", p->pat.name_pat, p->pat.age, p->pat.tag_id);                                          //患者信息
			printf("%s\n%s\n%d\n", p->doc.name_doc, p->doc.sub, p->doc.num_work);                         //医生信息
			int i;
			for (i = 0;i < (p->tre.che.tag_check);i++)                                                                    //检查信息
				printf("%s    %f    %d\n", p->tre.che.type[i], p->tre.che.cost_term[i], p->tre.che.cost_check);
			for (i = 0;i < (p->tre.pil.tag_pill);i++)                                                                      //开药信息
				printf("%s    %f    %d    %f\n", p->tre.pil.name_pill[i], p->tre.pil.cost_perpill[i], p->tre.pil.num_pill[i], p->tre.pil.cost_pill);
			printf("%d    %d    %d\n", p->tre.hos.time_start, p->tre.hos.time_end, p->tre.hos.deposit);                   //诊疗情况
			if((p->out_doc) != NULL)                                                                                     //出院日期，没出院则不打印
				printf("%d", p->out_doc);
		}/*if*/
		p = p->next;
	}/*while*/
}

void stat_doc_work()
{

}

void print_stat_pat(record* rec_head)                                  //打印住院患者报表
{
	record* p = rec_head;
	while(p != NULL)                    //出院日期为空则打印
	{
		if((p->out_doc) != NULL)
		printf("%s    %d    %d", p->pat.name_pat, p->pat.age, p->pat.tag_id);
		p = p->next;
	}
}