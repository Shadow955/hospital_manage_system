//modified by Nero on 9/29
#include<stdlib.h>
#include<stdio.h>
#include"base_struct.h"
#include<string.h>
#include"fileopt.h"
#include"allfunc.h"
FILE* infile;																//Դ�ļ�Ϊinfile�����ĺ������ļ�Ϊoutfile
//FILE* outfile;
/*********************************

���飺�Ƿ���Դ�ļ���ֱ�Ӳ�����
			  �д����۽��

*********************************/
int openfile() {															//�ļ����뺯��
	infile = fopen("test.txt", "r");							//��ȡ�ļ����ж��Ƿ�ɹ���
	if (infile == NULL)
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
	record* tp;
	tp = rec_head;
	int x = 0;
	while (!feof(infile))																//ѭ������ֱ���ļ�ĩβ
	{
		x++;
		fscanf(infile, "%d", &tp->num_check);
		fscanf(infile, "%s%d%d"
			, tp->pat.name_pat
			, &tp->pat.age
			, &tp->pat.tag_pat);
		fscanf(infile, "%s%s%s%d"
			, tp->doc.name_doc
			, tp->doc.level
			, tp->doc.sub
			, &tp->doc.num_work);
		fscanf(infile, "%s", tp->out_doc);
		int i = 0, j = 0;
		while(1)
		{
			fscanf(infile, "%s", tp->tre.che.type[i]);
			if(strcmp("over", tp->tre.che.type[i]) == 0)
				break;
			fscanf(infile, "%f", &tp->tre.che.cost_term[i]);
			i++;
		}
		while(1)//�ڶ���over֮ǰ��ѭ������ҩƷ����������
		{
			fscanf(infile, "%s", tp->tre.pil.name_pill[j]);
			if (strcmp("over", tp->tre.pil.name_pill[j]) == 0)
				break;
			fscanf(infile, "%d%d"
				, &tp->tre.pil.cost_perpill[j]
				, &tp->tre.pil.num_pill[j]);
			j++;
		}
		fscanf(infile, "%d%d%d"									//����סԺ��Ϣ����
			, &tp->tre.hos.time_start
			, &tp->tre.hos.time_end
			, &tp->tre.hos.deposit);
	
		tp->next = (record*)malloc(sizeof(struct record));
		tp = tp->next;
		tp->next= NULL;
	}
	//if (rec_head->next == NULL)
	//	rec_head = tp;
	//tp = NULL;	
	//free(tp);
	//tp = NULL;
	printf("%d", x);
	//׼�������½ڵ�
	//rec_this->next = tp;
	//rec_this = tp;
	//fclose(infile);
	printf("�������ɹ���\n");
	return (rec_head);
	/****************************************

	���������Ƿ������ر��ļ����д�̽��

	***************************************/
}
void printf_number(record* rec_head) {
	int number1;//�������������
	printf("�����빦�ܶ�Ӧ�����֣�\n1:��ӡĳ����������Ϣ\n2:��ӡĳҽ��������Ϣ\n3:��ӡĳ������ʷ���Ƽ�¼\n4:��ӡĳ��ʱ���ڵ����Ƽ�¼");
	scanf("%d", &number1);
	switch (number1) {
	case 1: outsub_doc(rec_head); break;//��ӡĳ����������Ϣ
	case 2: outname_doc(rec_head); break;//��ӡĳҽ��������Ϣ
	case 3: outpatient_name(rec_head); break;//��ӡĳ������ʷ���Ƽ�¼
	case 4: outtime_limit(rec_head); break;//��ӡĳ��ʱ���ڵ����Ƽ�¼
	}
}

void stdprint(record* p)
{
	printf("\n---------------------------------------------------------------------------\n");
	while (p->next!=NULL) {

		printf("�Һţ�%d\n����������%s  ���䣺 %d  ���ʶ���룺%03d\n"
			, p->num_check
			, p->pat.name_pat
			, p->pat.age
			, p->pat.tag_pat);
		printf("����ҽʦ��%s  ����%s  ���ң�%s  ҽ�����ţ�%d\n"
			, p->doc.name_doc
			, p->doc.level
			, p->doc.sub
			, p->doc.num_work);
		printf("ҽ������ʱ�䣺%s", p->out_doc);
		//fscanf(infile, "%s", tp->tre.che.type[0]);
		int i = 0, j = 0;
		printf("\n\n���߼�������\n �����Ŀ    �۸�\n");
		while (strcmp("over", p->tre.che.type[i]) != 0)//�ڶ���over֮ǰ��ѭ����������Ŀ���������
		{
			printf("%-8s   %6.2fԪ\n", p->tre.che.type[i], p->tre.che.cost_term[i]);
			i++;
		}
		printf("\n���߿�ҩ�����\n ҩƷ��    ����    ����\n");
		while (strcmp("over", p->tre.pil.name_pill[j]) != 0)//�ڶ���over֮ǰ��ѭ�����ҩƷ����������
		{
			printf("%-8s   %4.2fԪ   %-4d\n"
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