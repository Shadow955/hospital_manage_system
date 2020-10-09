#define funds = 0;
#include<stdio.h>
#include<stdlib.h>
#include"base_struct.h"
#include"fileopt.h"
#include"allfunc.h"


int main() {
	if (!openfile())									//开始时先执行文件读入函数，暂定以布尔类型判断
		return 0;					
	record* rec_head = read_and_link();//读入源文件中现有的所有诊疗记录并生成一条链表

	/***************************
	****此处应为主界面部分****
	***************************/
	int number;//保存输入的数字
	printf("请输入要执行功能对应的数字：\n1:录入诊疗记录\n2:修改诊疗记录\n3:删除诊疗记录\n4:打印信息\n5:统计营业额，生成住院患者报表\n6:统计医生的出诊情况和工作繁忙程度\n7:保存当前系统中的所有信息\n");//设计数字对应操作
	scanf("%d", &number);
	switch (number) {
		case 1: void input(struct record* p); break;//录入诊疗记录
		case 2: void alter_record(struct record* head); break;//修改诊疗记录
		case 3: void del_record(struct record* head); break;//删除诊疗记录
		case 4: printf_number(rec_head); break;//确认打印信息
		case 5: float espence(); break;//统计营业额
		case 6: float statistics(struct record* head); break;//统计医生的出诊情况和工作繁忙程度
		case 7: stdprint(rec_head); break;//保存当前系统保存的信息
	}
}

