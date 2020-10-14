#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include"base_struct.h"
#include"fileopt.h"
#include"allfunc.h"

time_t t;

int main() {
	printf("当前时间：");
	char*T=gettime();
	char* year = getyear();
	printf("%s\n", T);

	if (!openfile())									//开始时先执行文件读入函数
		return 0;				

	pill_term* pill_head = link_pill();
	che_term* che_head = link_che();
	doctor* doc_head = link_doc();
	record* rec_head = read_and_link(doc_head);  //读入源文件中现有的所有诊疗记录并生成四条链表
	record* p;
	int number;
	printf("请输入要执行功能对应的数字：\n");
	printf("1 : 新增诊疗记录\n2 : 查找诊疗记录\n");
	printf("3 : 查看当前保存的所有诊疗记录\n");
	printf("4 : 查看医院所有医生和繁忙程度\n5 : 查看医院营业额\n");
	printf("6 : 浏览现有药品及价格\n7 : 浏览所有检查项目及价格\n");
	printf("8 : 按挂号查找诊疗记录并操作\n");
	printf("9 : 保存当前系统中的所有信息\n0 : 退出\n");
	while (EOF != scanf("%d", &number)&&number>0&&number<10)
	{
		p = FindEnd(rec_head);
		switch (number) 
		{
			case 1: 
				p->next=getrecord(doc_head, pill_head, che_head,p->num_check); break;  //录入诊疗记录
			case 2: 
				printf_number(rec_head); break;
			case 3: 
				stdprint(rec_head); break;
			case 4: 
				docprint(doc_head); break;
			case 5: 
				statistics(rec_head); break;  //统计营业额
			case 6: 
				pillprint(pill_head); break;
			case 7: 
				cheprint(che_head); break;
			case 8:
				search(rec_head,doc_head,pill_head,che_head); break;
			case 9: 
				save(rec_head); break;  //保存当前系统保存的信息
			default: 
				break;
		}
		char* T = gettime();
		printf("当前时间：");
		printf("%s\n", T); 
		printf("请输入要执行功能对应的数字：\n");
		printf("1 : 新增诊疗记录\n2 : 查找诊疗记录\n");
		printf("3 : 查看当前保存的所有诊疗记录\n");
		printf("4 : 查看医院所有医生和繁忙程度\n5 : 查看医院营业额\n");
		printf("6 : 浏览现有药品及价格\n7 : 浏览所有检查项目及价格\n");
		printf("8 : 按挂号查找诊疗记录并操作\n");
		printf("9 : 保存当前系统中的所有信息\n0 : 退出\n");
	}
	freerec(rec_head);
	freedoc(doc_head);
	freepill(pill_head);
	freeche(che_head);
	return 0;
}

