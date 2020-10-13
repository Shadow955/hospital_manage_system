#pragma once

float sumcheck(int tag_check, float cost_term[]);
//
float sumpill(int tag_pill, float cost_perpill[], int num_pill[]);        //计算药品总费用函数
//
int date_turn(int,int);                 //将8位日期转化为天数

//int days_hosp(int time_start, int time_end);                  //计算住院时长函数

int cost_hos(int in, int out, int now);          //住院费用函数

record* getrecord(doctor*,pill_term*,che_term*);
//
void outpatient_tag(struct record* head);  //依据患者相关信息输出数据

void outpatient_name(struct record* head);		//检索患者姓名并输出

void outsub_doc(struct record* head);  //科室检索

void outname_doc(struct record* head);  //医生工号检索
//
//void outtime_limit(struct record* head);     //时间段检索

//void output(struct record* head); //输出诊疗记录

void del_record(struct record* head); //删除操作

//void input(struct record* p);  //录入诊疗记录

void alter_record(struct record* head);  //修改操作

float statistics(struct record* head);   //营业额

void yearchange(int);

bool judge_year(int a);

bool judge_name_pat(record* p);

bool judge_age(record* p);

bool judge_sex(record* p);

bool judge_tag_id(record* p);

bool judge_num_check(record* p);

che_term* judge_che_name(char* p, che_term* q);
//
pill_term* judge_pill_name(char* p, pill_term* q);
//
doctor* judge_num_work(int num, doctor* s);
//
bool time(int a, int b);

//bool judge_time(record* p);