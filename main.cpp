#define funds = 0;
#include<stdio.h>
#include<stdlib.h>
#include"base_struct.h"
#include"fileopt.h"
#include"allfunc.h"


int main() {
	if (!openfile())									//��ʼʱ��ִ���ļ����뺯�����ݶ��Բ��������ж�
		return 0;					
	record* rec_head = read_and_link();//����Դ�ļ������е��������Ƽ�¼������һ������

	/***************************
	****�˴�ӦΪ�����沿��****
	***************************/
	int number;//�������������
	printf("������Ҫִ�й��ܶ�Ӧ�����֣�\n1:¼�����Ƽ�¼\n2:�޸����Ƽ�¼\n3:ɾ�����Ƽ�¼\n4:��ӡ��Ϣ\n5:ͳ��Ӫҵ�����סԺ���߱���\n6:ͳ��ҽ���ĳ�������͹�����æ�̶�\n7:���浱ǰϵͳ�е�������Ϣ\n");//������ֶ�Ӧ����
	scanf("%d", &number);
	switch (number) {
		case 1: void input(struct record* p); break;//¼�����Ƽ�¼
		case 2: void alter_record(struct record* head); break;//�޸����Ƽ�¼
		case 3: void del_record(struct record* head); break;//ɾ�����Ƽ�¼
		case 4: printf_number(rec_head); break;//ȷ�ϴ�ӡ��Ϣ
		case 5: float espence(); break;//ͳ��Ӫҵ��
		case 6: float statistics(struct record* head); break;//ͳ��ҽ���ĳ�������͹�����æ�̶�
		case 7: stdprint(rec_head); break;//���浱ǰϵͳ�������Ϣ
	}
}

