#pragma once

float sumcheck(int tag_check, float cost_term[]);

float sumpill(int tag_pill, float cost_perpill[30], int num_pill[30]);        //����ҩƷ�ܷ��ú���

int date_turn(char a[8]);                 //��8λ����ת��Ϊ����

int days_hosp(int time_start, int time_end);                  //����סԺʱ������

int cost_hos(int a, int b, int c);          //סԺ���ú���

record* getrecord();

void outpatient_tag(struct record* head, int tag_in);  //���ݻ��������Ϣ�������

void outpatient_name(struct record* head);		//�����������������

void outsub_doc(struct record* head);  //���Ҽ���

void outname_doc(struct record* head);  //ҽ�����ż���

void outtime_limit(struct record* head);     //ʱ��μ���

void output(struct record* head); //������Ƽ�¼

void del_record(struct record* head); //ɾ������

void input(struct record* p);  //¼�����Ƽ�¼

void alter_record(struct record* head);  //�޸Ĳ���

float statistics(struct record* head);   //Ӫҵ��