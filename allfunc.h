#pragma once

float sumcheck(int tag_check, float cost_term[]);
//
float sumpill(int tag_pill, float cost_perpill[], int num_pill[]);        //����ҩƷ�ܷ��ú���
//
int date_turn(int,int);                 //��8λ����ת��Ϊ����

//int days_hosp(int time_start, int time_end);                  //����סԺʱ������

int cost_hos(int in, int out, int now);          //סԺ���ú���

record* getrecord(doctor*,pill_term*,che_term*);
//
void outpatient_tag(struct record* head);  //���ݻ��������Ϣ�������

void outpatient_name(struct record* head);		//�����������������

void outsub_doc(struct record* head);  //���Ҽ���

void outname_doc(struct record* head);  //ҽ�����ż���
//
//void outtime_limit(struct record* head);     //ʱ��μ���

//void output(struct record* head); //������Ƽ�¼

void del_record(record*,record*); //ɾ������

//void input(struct record* p);  //¼�����Ƽ�¼

void alter_record(record*,record*,doctor*,pill_term*,che_term*);  //�޸Ĳ���

void statistics(struct record* head);   //Ӫҵ��

void yearchange(int);

bool judge_year(int a);

bool judge_name_pat(char*);

bool judge_age(int);

bool judge_sex(char*);

bool judge_tag_id(char*,char*);

bool judge_num_check(record* p);

che_term* judge_che_name(char* p, che_term* q);
//
pill_term* judge_pill_name(char* p, pill_term* q);
//
doctor* judge_num_work(int num, doctor* s);
//
bool time(int a, int b);

//bool judge_time(record* p);