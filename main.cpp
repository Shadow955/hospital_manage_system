#define funds = 0;
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include"base_struct.h"
#include"fileopt.h"
#include"allfunc.h"
//
//char ch[] = { "123" };
//int c = atoi(ch);
//int k = 100;
//sprintf(ch, "%d", k);

time_t t;



int main() {

	printf("当前时间：");
	char*T=gettime();
	char* year = getyear();
	printf("%s\n", T);

	if (!openfile())									//开始时先执行文件读入函数
		return 0;				

	record* rec_head = read_and_link();  //读入源文件中现有的所有诊疗记录并生成一条链表
	record* p;
	pill_term* pill_head = link_pill();
	che_term* che_head = link_che();
	doctor* doc_head = link_doc();
	int number;
	printf("请输入要执行功能对应的数字：\n");
	printf("1 : 录入诊疗记录\n2 : 修改诊疗记录\n3 : 删除诊疗记录\n");
	printf("4 : 打印信息\n5 : 统计营业额，生成住院患者报表\n");
	printf("6 : 统计医生的出诊情况和工作繁忙程度\n7 : 保存当前系统中的所有信息\n");
	printf("8 : 查看当前保存的所有诊疗记录\n0 : 退出\n");
	while (EOF!=scanf("%d", &number)&&number  !=  0)
	{
		p = FindEnd(rec_head);
		//p->next = (record*)malloc(sizeof(record));
		switch (number) 
		{
			case 1: 
				p->next=getrecord(doc_head, pill_head, che_head); break;  //录入诊疗记录
			case 2: 
				alter_record(rec_head); break;  //修改诊疗记录
			case 3: 
				del_record(rec_head); break;  //删除诊疗记录
			case 4: 
				printf_number(rec_head, pill_head, che_head, doc_head); break;  //确认打印信息
			case 5: 
				statistics(rec_head); break;  //统计营业额
			case 6: 
				float abc(struct record* head); break;  //统计医生的出诊情况和工作繁忙程度
			case 7: 
				save(rec_head); break;  //保存当前系统保存的信息
			case 8: 
				stdprint(rec_head);
		}
		printf("请输入要执行功能对应的数字：\n");
		printf("1 : 录入诊疗记录\n2 : 修改诊疗记录\n3 : 删除诊疗记录\n");
		printf("4 : 打印信息\n5 : 统计营业额，生成住院患者报表\n");
		printf("6 : 统计医生的出诊情况和工作繁忙程度\n7 : 保存当前系统中的所有信息\n");
		printf("8 : 查看当前保存的所有诊疗记录\n0 : 退出\n");//设计数字对应操作
		printf("当前时间：");
		char* T = gettime();
		printf("%s\n", T);                     
	}
	//fclose(file_rec);
	//free(p);
}

