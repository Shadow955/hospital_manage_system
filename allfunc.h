#pragma once

float sumcheck(int tag_check, float cost_term[]);
//
float sumpill(int tag_pill, float cost_perpill[], int num_pill[]);        //计算药品总费用函数
//
int date_turn(int);                 //将8位日期转化为天数
//
int cost_hos(int , int , int);          //住院费用函数
//
record* getrecord(doctor*,pill_term*,che_term*,int );
//
void outpatient_tag(record*);  //依据患者相关信息输出数据
//
void outpatient_name(record*);		//检索患者姓名并输出
//
void outsub_doc(record*);  //科室检索
//
void outname_doc(record*);  //医生工号检索
//
void outtime_limit(record*);     //时间段检索
//
void del_record(record*,record*); //删除操作
//
void alter_record(record*,record*,doctor*,pill_term*,che_term*);  //修改操作
//
void statistics(record*);   //营业额
//
void yearchange(int);
//
bool judge_year(int);
//
bool judge_name_pat(char*);
//
bool judge_age(int);
//
bool judge_sex(char*);
//
bool judge_tag_id(char*,char*);
//
bool judge_num_check(record*);
//
che_term* judge_che_name(char*, che_term*);
//
pill_term* judge_pill_name(char*, pill_term*);
//
doctor* judge_num_work(int, doctor*);
//
bool JudgeDate(int);
//
void DoctorState(int, doctor*);
//bool judge_time(record* p);