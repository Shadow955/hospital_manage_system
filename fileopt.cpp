//modified by Nero on 9/29
#include<stdlib.h>
#include<stdio.h>
#include"base_struct.h"
#include<string.h>
#include"fileopt.h"
#include"allfunc.h"
FILE* file_rec;
FILE* file_pill;
FILE* file_doc;
FILE* file_che;
int openfile() {															//�ļ����뺯�����ɹ�����1��ʧ�ܷ���0
	file_rec = fopen("test.txt", "r");							//��ȡ�ļ����ж��Ƿ�ɹ���
	file_pill = fopen("pill.txt", "r");
	file_doc = fopen("doc.txt", "r");
	file_che = fopen("check.txt", "r");
	if (file_rec == NULL||file_pill==NULL||file_doc==NULL||file_che==NULL)
	{
		printf("�ļ���ʧ�ܣ�����Դ�ļ���\n");		//��ʧ�ܽ����������ϲ�
		return 0;
	}
	else
	{
		printf("�ļ��򿪳ɹ���\n");
		return 1;
	}
}
//DiagnosisRecord* ReadFromDiagnosisFile(const char* readPath) {
//	DiagnosisRecord* res = (DiagnosisRecord*)malloc(sizeof(DiagnosisRecord));
//	res->next = NULL;
//	FILE* fileReadPointer;
//	if ((fileReadPointer = fopen(readPath, "r")) == NULL) {
//		printf("�ļ�·������ȷ,����������!\n");
//		return NULL;
//	}
//	while (!feof(fileReadPointer)) {
//		//printf("��ʼ����\n");
//		DiagnosisRecord* nowRecord = InRecord(fileReadPointer);
//		//printf("�������\n");
//		if (!nowRecord) continue;
//		pushBackDiagnosisList(res, nowRecord);
//		if (nowRecord->diagnosisSituation.setFlag == 0) {
//			hospitalFund.checkCost.yuan += nowRecord->diagnosisSituation.
//				diagnosisSituationInfo.checkRecord.totalCost.yuan;
//			hospitalFund.checkCost.jiao += nowRecord->diagnosisSituation.
//				diagnosisSituationInfo.checkRecord.totalCost.jiao;
//			hospitalFund.checkCost.fen += nowRecord->diagnosisSituation.
//				diagnosisSituationInfo.checkRecord.totalCost.fen;
//		}
//		else if (nowRecord->diagnosisSituation.setFlag == 1) {
//			hospitalFund.drugCost.yuan += nowRecord->diagnosisSituation.
//				diagnosisSituationInfo.prescribeRecord.totalCost.yuan;
//			hospitalFund.drugCost.jiao += nowRecord->diagnosisSituation.
//				diagnosisSituationInfo.prescribeRecord.totalCost.jiao;
//			hospitalFund.drugCost.fen += nowRecord->diagnosisSituation.
//				diagnosisSituationInfo.prescribeRecord.totalCost.fen;
//		}
//		else if (nowRecord->diagnosisSituation.setFlag == 2) {
//			hospitalFund.inHosipitalCost.yuan += nowRecord->diagnosisSituation.
//				diagnosisSituationInfo.inHospitalRecord.costByNow.yuan;
//			hospitalFund.inHosipitalCost.jiao += nowRecord->diagnosisSituation.
//				diagnosisSituationInfo.inHospitalRecord.costByNow.jiao;
//			hospitalFund.inHosipitalCost.fen += nowRecord->diagnosisSituation.
//				diagnosisSituationInfo.inHospitalRecord.costByNow.fen;
//		}
//	}
//	int CF = 0;//��λ�Ĵ���
//	hospitalFund.allCost.fen += hospitalFund.checkCost.fen +
//		hospitalFund.drugCost.fen + hospitalFund.inHosipitalCost.fen;
//	CF = hospitalFund.allCost.fen / 10; hospitalFund.allCost.fen %= 10;
//	hospitalFund.allCost.jiao += hospitalFund.checkCost.jiao +
//		hospitalFund.drugCost.jiao + hospitalFund.inHosipitalCost.jiao + CF;
//	CF = hospitalFund.allCost.jiao / 10; hospitalFund.allCost.jiao %= 10;
//	hospitalFund.allCost.yuan += hospitalFund.checkCost.yuan +
//		hospitalFund.drugCost.yuan + hospitalFund.inHosipitalCost.yuan + CF;
//	fclose(fileReadPointer);
//	return res;
//}
record* read_and_link() 
{
	record* rec_head = (record*)malloc(sizeof(record));		//����ͷ�ڵ�
	rec_head->next = NULL;
	record* tp;
	record* pre = NULL;
	tp = rec_head;
	while (!feof(file_rec))																//ѭ������ֱ���ļ�ĩβ
	{
		fscanf(file_rec, "%d", &tp->num_check);
		fscanf(file_rec, "%s%s%d%d"
			, tp->pat.name_pat
			, tp->pat.sex
			, &tp->pat.age
			, &tp->pat.tag_id);
		fscanf(file_rec, "%s%s%s%d"
			, tp->doc.name_doc
			, tp->doc.level
			, tp->doc.sub
			, &tp->doc.num_work);
		fscanf(file_rec, "%s", tp->out_doc);
		int i = 0, j = 0;
		while(1)
		{
			fscanf(file_rec, "%s", tp->tre.che.type[i]);
			if(strcmp("#", tp->tre.che.type[i]) == 0)
				break;
			fscanf(file_rec, "%f", &tp->tre.che.cost_term[i]);
			i++;
		}
		while(1)//�ڶ���#֮ǰ��ѭ������ҩƷ����������
		{
			fscanf(file_rec, "%s", tp->tre.pil.name_pill[j]);
			if (strcmp("#", tp->tre.pil.name_pill[j]) == 0)
				break;
			fscanf(file_rec, "%f%d"
				, &tp->tre.pil.cost_perpill[j]
				, &tp->tre.pil.num_pill[j]);
			j++;
		}
		fscanf(file_rec, "%d%d%d"									//����סԺ��Ϣ����
			, &tp->tre.hos.time_start
			, &tp->tre.hos.time_end
			, &tp->tre.hos.deposit);
	
		tp->next = (record*)malloc(sizeof(struct record));
		tp->next->next = NULL;
		pre = tp;
		tp = tp->next;
	}
	free(tp);
	pre->next = NULL;
	printf("���Ƽ�¼�������ɹ���\n");
	return (rec_head);
}

pill_term* link_pill()
{
	pill_term* pill_head = (pill_term*)malloc(sizeof(pill_term));		
	pill_head->next = NULL;
	pill_term* tp;
	pill_term* pre = NULL;
	tp = pill_head;
	while (!feof(file_pill))
	{
		fscanf(file_pill, "%s%f", tp->pill_name, &tp->pill_price);
		tp->next = (pill_term*)malloc(sizeof(pill_term));
		tp->next->next = NULL;
		pre = tp;
		tp = tp->next;
	}
	free(tp);
	pre->next = NULL;
	printf("ҩƷ�������ɹ���\n");
	return (pill_head);
}

che_term* link_che()
{
	che_term* che_head = (che_term*)malloc(sizeof(che_term));
	che_head->next = NULL;
	che_term* tp;
	che_term* pre = NULL;
	tp = che_head;
	while (!feof(file_che))
	{
		fscanf(file_che, "%s%f", tp->che_name, &tp->che_price);
		tp->next = (che_term*)malloc(sizeof(che_term));
		tp->next->next = NULL;
		pre = tp;
		tp = tp->next;
	}
	free(tp);
	pre->next = NULL;
	printf("�����Ŀ�������ɹ���\n");
	return (che_head);
}

doctor* link_doc()
{
	doctor* doc_head = (doctor*)malloc(sizeof(doctor));
	doc_head->next = NULL;
	doctor* tp;
	doctor* pre = NULL;
	tp = doc_head;
	while (!feof(file_doc))
	{
		fscanf(file_doc, "%s%s%s%d", tp->name_doc, tp->level, tp->sub, &tp->num_work);
		tp->next = (doctor*)malloc(sizeof(doctor));
		tp->next->next = NULL;
		pre = tp;
		tp = tp->next;
	}
	free(tp);
	pre->next = NULL;
	printf("ҽ���������ɹ���\n");
	return (doc_head);
}

void printf_number(record* rec_head,pill_term* pill_head,che_term* che_head,doctor* doc_head) {
	int number1;//�������������
	printf("�����빦�ܶ�Ӧ�����֣�\n1 : ��ӡĳ����������Ϣ\n2 : ��ӡĳҽ��������Ϣ\n");
	printf("3 : ��ӡĳ������ʷ���Ƽ�¼\n4 : ��ӡĳ��ʱ���ڵ����Ƽ�¼\n");
	printf("5 : ���ȫ��ҽ������\n6 : ���ҩƷ������\n7 : ������������\n");
	scanf("%d", &number1);
	switch (number1) {
	case 1: 
		outsub_doc(rec_head); break;//��ӡĳ����������Ϣ
	case 2: 
		outname_doc(rec_head); break;//��ӡĳҽ��������Ϣ
	case 3: 
		outpatient_name(rec_head); break;//��ӡĳ������ʷ���Ƽ�¼
	case 4: 
		outtime_limit(rec_head); break;//��ӡĳ��ʱ���ڵ����Ƽ�¼
	case 5:
		docprint(doc_head); break;
	case 6:
		pillprint(pill_head); break;
	case 7:
		cheprint(che_head); break;
	}
}

record* FindEnd(record* head)
{
	record* p = head;
	while (p->next != NULL)
	{
		p = p->next;
	}
	return p;
}
void stdprint(record* p)
{
	printf("\n---------------------------------------------------------------------------\n");
	while (p!=NULL)
	{
		printf("�Һţ�%07d\n����������%s  �Ա�%s  ���䣺 %d  ���֤β�ţ�%04d\n"
			, p->num_check
			, p->pat.name_pat
			, p->pat.sex
			, p->pat.age
			, p->pat.tag_id);
 		printf("����ҽʦ��%s  ����%s  ���ң�%s  ҽ�����ţ�%07d\n"
			, p->doc.name_doc
			, p->doc.level
			, p->doc.sub
			, p->doc.num_work);
		printf("ҽ������ʱ�䣺%s", p->out_doc);
		//fscanf(file_rec, "%s", tp->tre.che.type[0]);
		int i = 0, j = 0;
		printf("\n\n���߼�������\n �����Ŀ    �۸�\n");
		while (strcmp("#", p->tre.che.type[i]) != 0)//�ڶ���#֮ǰ��ѭ����������Ŀ���������
		{
 			printf("%-8s   %6.2fԪ\n", p->tre.che.type[i], p->tre.che.cost_term[i]);
			i++;
		}
		printf("\n���߿�ҩ�����\n ҩƷ��     ����      ����\n");
		while (strcmp("#", p->tre.pil.name_pill[j]) != 0)//�ڶ���#֮ǰ��ѭ�����ҩƷ����������
		{
			printf("%-8s   %5.2fԪ   %3d\n"
				, p->tre.pil.name_pill[j]
				, p->tre.pil.cost_perpill[j]
				, p->tre.pil.num_pill[j]);
			j++;
		}
		printf("\nסԺ��ʼʱ��:%04d\nԤ�Ƴ�Ժʱ��:%04d\nѺ��:%d"									//���סԺ��Ϣ����
			, p->tre.hos.time_start
			, p->tre.hos.time_end
			, p->tre.hos.deposit);
		p = p->next;
		printf("\n---------------------------------------------------------------------------\n");
	}
}

void docprint(doctor* p)
{
	printf("\n---------------------------------------------------------------------------\n");
	while (p->next!= NULL)
	{
		printf("%-25s%-12s%-10s%-10d\n", p->name_doc, p->level, p->sub, p->num_work);
		p = p->next;
	}
	printf("---------------------------------------------------------------------------\n\n");
}

void pillprint(pill_term* p) 
{
	printf("\n---------------------------------------------------------------------------\n");
	while (p->next!= NULL)
	{
		printf("%-15s%6.2fԪ\n", p->pill_name, p->pill_price);
		p = p->next;
	}
	printf("---------------------------------------------------------------------------\n\n");
}

void cheprint(che_term* p)
{
	printf("\n---------------------------------------------------------------------------\n");
	while (p->next!= NULL)
	{
		printf("%-15s%6.2fԪ\n", p->che_name, p->che_price);
		p = p->next;
	}
	printf("---------------------------------------------------------------------------\n\n");
}