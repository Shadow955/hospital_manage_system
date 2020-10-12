//base_struct.h version2.0 designed by Nero J on 9/11
//update to version2.1 by WSX on 9/15
//update to version2.2 by Nero J on 9/29

#ifndef BASE_STRUCT
#define BASE_STRUCT

#include<stdio.h>
struct patient {								//������Ϣ�ṹ��
	char name_pat[50];						    //��������
	int age;									//����	
	char sex[5];									//�Ա�
	char tag_id[5];                                //���֤�ţ�β��4λ���ɣ�
	patient* next = NULL;				        //����ʵ��
};

struct doctor {									//ҽ����Ϣ�ṹ��
	char name_doc[50];					        //ҽ������
	char level[20];							    //ҽ������
	char sub[20];							    //ҽ������
	int num_work;								//ҽ������
	doctor* next = NULL;                        //����ʵ��
};

struct check {									//���ṹ��
	int tag_check=0;                              //�������Ŀ��
	char type[50][10];                          //�������
	float cost_term[50];					    //���������
	float cost_check;							//�ܼ����ã��������㣩
};

struct pill {									//ҩƷ�ṹ��
	int tag_pill=0;                               //ҩƷ����Ŀ��
	char name_pill[30][30];				        //ҩƷ����
	float cost_perpill[30];                       //����
	int num_pill[30];                           //����
	float cost_pill;                            //ҩƷ�ܼ�
};

struct hospital {								//סԺ��Ϣ�ṹ��
	int time_start;							    //סԺ��ʼʱ��
	int time_end;							    //Ԥ��סԺ����ʱ��
	int days_hos;								//סԺ�������������㣩
	int cost_hos;								//סԺ���ã��������㣩
    int deposit;                                //סԺѺ��
};

struct treat {									//�������
	struct check che;							//������
	struct pill pil;							//��ҩ���
	struct hospital hos;						//סԺ��Ϣ
};

struct record {									//���Ƽ�¼
	int num_check;                              //�Һ�
	struct patient pat;							//������Ϣ
	struct doctor doc;							//ҽ����Ϣ
	char out_doc[13];							//����ʱ��
	struct treat tre;							//�������
	record* next = NULL;					    //����ʵ��
};

struct pill_term {
	char pill_name[30];
	float pill_price;
	pill_term* next = NULL;
};

struct che_term {
	char che_name[20];
	float che_price;
	che_term* next = NULL;
};

#endif

//modified by Nero J on 9/15