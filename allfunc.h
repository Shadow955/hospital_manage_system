#pragma once

float sumcheck(int tag_check, float cost_term[]);
//
float sumpill(int tag_pill, float cost_perpill[], int num_pill[]);        //����ҩƷ�ܷ��ú���
//
int date_turn(int);                 //��8λ����ת��Ϊ����
//
int cost_hos(int , int , int);          //סԺ���ú���
//
record* getrecord(doctor*,pill_term*,che_term*,int );
//
void outpatient_tag(record*);  //���ݻ��������Ϣ�������
//
void outpatient_name(record*);		//�����������������
//
void outsub_doc(record*);  //���Ҽ���
//
void outname_doc(record*);  //ҽ�����ż���
//
void outtime_limit(record*);     //ʱ��μ���
//
void del_record(record*,record*); //ɾ������
//
void alter_record(record*,record*,doctor*,pill_term*,che_term*);  //�޸Ĳ���
//
void statistics(record*);   //Ӫҵ��
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