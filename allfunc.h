#pragma once

float sumcheck(int tag_check, float cost_term[]);

float sumpill(int tag_pill, float cost_perpill[30], int num_pill[30]);        //计算药品总费用函数

int date_turn(char a[8]);                 //将8位日期转化为天数

int days_hosp(int time_start, int time_end);                  //计算住院时长函数

int cost_hos(int a, int b, int c);          //住院费用函数

void getrecord(struct record* head);

void outpatient_tag(struct record* head, int tag_in);  //依据患者相关信息输出数据

void outpatient_name(struct record* head);		//检索患者姓名并输出

void outsub_doc(struct record* head);  //科室检索

void outname_doc(struct record* head);  //医生工号检索

void outtime_limit(struct record* head);     //时间段检索

void output(struct record* head); //输出诊疗记录

void del_record(struct record* head); //删除操作

void input(struct record* p);  //录入诊疗记录

void alter_record(struct record* head);  //修改操作

float statistics(struct record* head);   //营业额