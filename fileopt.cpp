//modified by Nero on 9/29
#include<stdlib.h>
#include<stdio.h>
#include"base_struct.h"
#include<string.h>
#include"fileopt.h"
#include"allfunc.h"
FILE* infile;																//源文件为infile，更改后的输出文件为outfile
//FILE* outfile;
/*********************************

争议：是否在源文件内直接操作？
			  有待讨论解决

*********************************/
int openfile() {															//文件读入函数
	infile = fopen("test.txt", "a");							//读取文件并判断是否成功打开
	if (infile == NULL)
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
record* read_and_link() 
{
	//record* rec_head;

	/***********************************************************

	注意：格式化读入时，是否需要过滤回车？有待进一步测试

	************************************************************/


	record* rec_head = (record*)malloc(sizeof(record));		//建立头节点
	//rec_head->next = NULL;
	//record* rec_this = rec_head;								//建立当前节点
	//record* tp;
	record* tp;
		//= (record*)malloc(sizeof(record));//默认建立新节点
	//rec_head->next = tp;
	tp = rec_head;
	while (fscanf(infile, "%d", &tp->num_check) !=EOF)																//循环读入直至文件末尾
	{
		//tp = (record*)malloc(sizeof(record));//默认建立新节点
		fscanf(infile, "%s%d%d"
			, &tp->pat.name_pat
			, &tp->pat.age
			, &tp->pat.tag_pat);
		fscanf(infile, "%s%s%s%d"
			, &tp->doc.name_doc
			, &tp->doc.level
			, &tp->doc.sub
			, &tp->doc.num_work);
		fscanf(infile, "%s", tp->out_doc);
			//fscanf(infile, "%s", tp->tre.che.type[0]);
		int i = 0, j = 0;
		while(1)//在读至over之前，循环读入检查项目名称与费用
		{
			fscanf(infile, "%s", tp->tre.che.type[i]);
			if(strcmp("over", tp->tre.che.type[i]) != 0)
				break;
			fscanf(infile, "%f", tp->tre.che.cost_term[i]);
			i++;
		}
		while(1)//在读至over之前，循环读入药品单价与数量
		{
			fscanf(infile, "%s", &tp->tre.pil.name_pill[j]);
			if (strcmp("over", tp->tre.pil.name_pill[j]) != 0)
				break;
			fscanf(infile, "%d%d"
				, &tp->tre.pil.cost_perpill[j]
				, &tp->tre.pil.num_pill[j]);
			j++;
		}
		fscanf(infile, "%d%d%d"									//读入住院信息部分
			, &tp->tre.hos.time_start
			, &tp->tre.hos.time_end
			, &tp->tre.hos.deposit);
	
		tp->next = (record*)malloc(sizeof(struct record));
		tp = tp->next;
	}
	//if (rec_head->next == NULL)
	//	rec_head = tp;
	tp = NULL;											//准备建立新节点
	//rec_this->next = tp;
	//rec_this = tp;
	//fclose(infile);
	printf("链表构建成功！\n");
	return (rec_head);
	/****************************************

	链表建立后是否立即关闭文件？有待探讨

	***************************************/
}
void printf_number(record* rec_head) {
	int number1;//保存输入的数字
	printf("请输入功能对应的数字：\n1:打印某科室诊疗信息\n2:打印某医生诊疗信息\n3:打印某患者历史诊疗记录\n4:打印某段时间内的诊疗记录");
	scanf("%d", &number1);
	switch (number1) {
	case 1: outsub_doc(rec_head); break;//打印某科室诊疗信息
	case 2: outname_doc(rec_head); break;//打印某医生诊疗信息
	case 3: outpatient_name(rec_head); break;//打印某患者历史诊疗记录
	case 4: outtime_limit(rec_head); break;//打印某段时间内的诊疗记录
	}
}

void stdprint(record* p)
{
	printf("%d %s %d %d\n"
		, p->num_check
		, p->pat.name_pat
		, p->pat.age
		, p->pat.tag_pat);
	printf("%s %s %s %d\n"
		, p->doc.name_doc
		, p->doc.level
		, p->doc.sub
		, p->doc.num_work);
	printf("%s", p->out_doc);
	//fscanf(infile, "%s", tp->tre.che.type[0]);
	int i = 0, j = 0;
	while (strcmp("over", p->tre.che.type[i]) != 0)//在读至over之前，循环输出检查项目名称与费用
	{
		printf("%s %f", p->tre.che.type[i],p->tre.che.cost_term[i]);
		i++;
	}
	printf("\n");
	while (strcmp("over", p->tre.pil.name_pill[j]) != 0)//在读至over之前，循环输出药品单价与数量
	{
		printf("%s %f %d"
			, p->tre.pil.name_pill[j]
			, p->tre.pil.cost_perpill[j]
			, p->tre.pil.num_pill[j]);
		j++;
	}
	printf("\n");
	printf("%d %d %d"									//输出住院信息部分
		, p->tre.hos.time_start
		, p->tre.hos.time_end
		, p->tre.hos.deposit);
}