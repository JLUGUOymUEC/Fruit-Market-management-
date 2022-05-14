#include"struct.h"
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>


//=================
//���ֻ�����������
//=================
//1.ʱ�乹�캯��
void Get_time(Time* tim) {
	struct tm t;   //tm�ṹָ��
	time_t now;  //����time_t���ͱ���
	time(&now);      //��ȡϵͳ���ں�ʱ��
	localtime_s(&t, &now);   //��ȡ�������ں�ʱ��
	tim->hour = t.tm_hour;
	tim->min = t.tm_min;
}
//2.����ʽת������������money��ʽ�� 
Money Money_change(float t) {
	Money a;
	a.value_m = t;
	int temp = int(1000 * t);
	a.yuan = temp /1000;
	a.jiao = (temp / 100) % 10;
	if ((temp % 1000) >= 5)a.fen = ((temp%100) / 10 )+ 1;
	else a.fen = (temp % 100 )/ 10;
	return a;
}
//3.��Ԫ�Ƿָ�ʽ������
void Print(Money m) {
	m=Money_change(m.value_m);
	printf("%dԪ%d��%d��",m.yuan,m.jiao,m.fen);
}
//4.��ȡ����֧���ܶ�(�ֽ�֧����Ϣ)
float Get_cost(Cash_info c) { 
	return c.pay - c.change; 
}
//5.��Ա����ʼ������
void Vip_init(Membership_card * m) {
	m->card_number = -1;
	m->balance = -1;
}
//5.ˮ����ʼ������
void Fruit_init(Fruit *f,kind k) {
	f->num = 0;
	f->what_fruit = k;
}
//6.֧����Ϣ��ʼ������
void Pay_init(Pay_info *p) {
	p->flag = -1;
	p->cash.pay = -1;
	p->cash.change =-1 ;
	Vip_init(&(p->vip));
	p->after_pay = -1;
}
//7.������Ϣ��ʼ������
void Shopping_info_init(Shopping_info *s) {
	s->number = -1;
	//2.����ʱ���ʼ��
	s->shopping_time.hour = -1;
	s->shopping_time.min = -1;
	//3.ˮ����Ϣ��ʼ��
	Fruit_init(&(s->fruit[0]),apple);
	Fruit_init(&(s->fruit[1]), orange);
	Fruit_init(&(s->fruit[2]), pear);
	Fruit_init(&(s->fruit[3]), pomelo);
	Fruit_init(&(s->fruit[4]), hami_melon);
	//4.�ܶ��ʼ��
	s->sum_m= 0;
	//5.֧����Ϣ��ʼ��
	Pay_init(&(s->shopping_pay));
}
//8.��ˮ��
void Buy_fruit(Shopping_info *s){
	Get_time(&(s->shopping_time));
	printf( "________________ˮ����Ŀ�˵�________________\n");
	printf( " ||#######################################||\n");
	printf( " ||------------1.ƻ��(20.50Ԫ/����)-------||\n");
	printf( " ||***************************************||\n");
	printf(" ||------------2.����(16.33Ԫ/����)-------||\n");
	printf(" ||***************************************||\n");
	printf(" ||------------3.��(19.00Ԫ/����)---------||\n");
	printf(" ||***************************************||\n");
	printf(" ||------------4.����(9.83Ԫ/��)----------||\n");
	printf(" ||***************************************||\n");
	printf(" ||------------5.���ܹ�(15.80Ԫ/��)-------||\n");
	printf(" ||***************************************||\n");
	printf(" ||#######################################||\n");
	printf( "��������������������������������������������\n");
	int flag1;//ˮ�������־
	int flag2=0 ;//���������־
	float count;//ˮ������
	while(!flag2){
		printf("��������Ҫ�����ˮ�����ࣺ");
		flag1 = Input_int();
		while (flag1 > 5 || flag1 <= 0) { printf("�������Ų����ڣ�����������:"); flag1 = Input_int();}
		switch (flag1) {
		case 1: {
			count = Input_fruit_num(apple);
			s->fruit[0].num+=count;
			s->sum_m +=count*APPLE_P;
			break; }
		case 2: {
			count = Input_fruit_num(orange);
			s->fruit[1].num += count;
			s->sum_m += count*ORANGE_P;
			break; }
		case 3: {
			count = Input_fruit_num(pear);
			s->fruit[2].num += count;
			s->sum_m += count*PEAR_P;
			break; }
		case 4: {
			count = Input_fruit_num(pomelo);
			s->fruit[3].num += count;
			s->sum_m += count*POMELO_P;
			break; }
		case 5: {
			count = Input_fruit_num(hami_melon);
			s->fruit[4].num += count;
			s->sum_m += count*HAMI_MELON_P;
			break; }
	}
		flag2 = 1;
		printf("ѡ���������������0�������������������������:");
		flag2 = Input_int(); 
	}
	printf("���ι����ܽ��:%f\n",s->sum_m);
	How_pay(s);
}
//9.ѡ����ʽ
void How_pay(Shopping_info *s) {
	int i;/*ѭ������*/
	int flag = 0;/*����ʽѡ���־*/
	printf("��ѡ����ʽ:(1)�ֽ�֧��(2)��Ա��֧��\n");
	flag = Input_int();
	/*���ο�������1000Ԫ����ֻ��ѡ���ֽ�֧��*/
	if (s->sum_m > 1000) { printf("��������1000Ԫ��ֻ��ѡ���ֽ�֧��\n"); flag = 1; }
	while (!(flag == 1 || flag == 2)) {
		printf("������1��2:");
		flag = Input_int();
	}
	//1.ѡ���ֽ�֧��
	if (flag == 1) {
		//1.1ȷ��֧����ʽ��־��ֵ
		s->shopping_pay.flag = 0;
		float pay;/*֧�����*/
		printf("������֧�����:");
		pay = Input_float();
		//1.2֧������
		while (pay < s->sum_m) {
			printf("֧������!��Ǯ:");
			float add_pay;
			add_pay = Input_float();
			pay += add_pay;
		}
		//1.3���֧��
		s->shopping_pay.cash.pay = pay;
		s->shopping_pay.cash.change = pay -(s->sum_m);
		printf("\n����:%f\n",s->shopping_pay.cash.change);
	}
	//2.ѡ���Ա��֧��
	if (flag == 2) {
		s->shopping_pay.flag = 1;
		int num;/*����Ŀ���*/
		int flag_exist=0;/*��Ա�����ڵı�־*/
		Membership_card *mc = Read_vb();
		while (!flag_exist) {
			//2.1����Ա�����Ƿ����
			num = Input_number();
			for (i = 0; i < MAX; i++) {	
				if (mc[i].card_number == -1)break;
				if (mc[i].card_number == num) { flag_exist = 1; break; }
			}
			/*��Ա������������������*/
			if (!flag_exist) {
				int flag_e_e=1;
				printf("��Ա��������,����������\n");
				printf("��û�л�Ա��,������0�˳�:");
				flag_e_e = Input_int();
				if (!flag_e_e)break;
			}
			/*��Ա������*/
			else {
				if (mc[i].balance < s->sum_m) { printf("��Ա�����㣬�޷�����!\n"); break; }
				else {
					printf("֧��ǰ���:%f\n",mc[i].balance);
					s->shopping_pay.vip.balance = mc[i].balance;
					s->shopping_pay.vip.card_number = mc[i].card_number;	
					s->shopping_pay.after_pay = mc[i].balance - s->sum_m;
					mc[i].balance = s->shopping_pay.after_pay;
					printf("֧�������:%f\n", mc[i].balance);
					Write_vb(mc);
				}
			}
		}
		free(mc);
	}
}
//10.һ�������Ĺ���
void Buy() {
	int i;
	Shopping_info s;
	Shopping_info_init(&s);
	Buy_fruit(&s);
	Shopping_info *s_all = Read_si();
	for (i = 0; i < MAX; i++)if (s_all[i].number == -1)break;
	if (i != 0)s.number = s_all[i - 1].number + 1;
	else s.number = 1;
	s_all[i] = s;
	Write_si(s_all);
	free(s_all);
}
//11.���ܲ˵�
void List() {
	int choose;
	int flag;
	printf("________________���˵�______________________\n");
	printf(" ||#######################################||\n");
	printf(" ||------------1.����ˮ��-----------------||\n");
	printf(" ||***************************************||\n");
	printf(" ||------------2.����Ա����---------------||\n");
	printf(" ||***************************************||\n");
	printf(" ||------------3.�����Ա��---------------||\n");
	printf(" ||***************************************||\n");
	printf(" ||------------4.��Ա����ֵ---------------||\n");
	printf(" ||***************************************||\n");
	printf(" ||#######################################||\n");
	printf("��������������������������������������������\n");
	printf("�������Ӧ���������:");
	choose = Input_int();
	while (!(choose >=1&&choose<=4)) { printf("�������Ӧ�����:"); choose = Input_int(); }
	switch (choose) {
	case 1:{
		system("cls");
		Buy();
		flag = 1;
		printf("����0�ص����˵��������˳�����:");
		 flag = Input_int();
		if (flag == 0) { system("cls"); List(); }
		break;
	}
	case 2: {
		system("cls");
		Administrator_func_list();
		/*��ջ�����*/
		//Flush_buffer();
		system("cls");
		List();
		break;
	}
	case 3: {
		system("cls");
		Register();
		flag = 1;
		printf("����0�ص����˵��������˳�����:");
		flag = Input_int();
		if (flag == 0) { system("cls"); List(); }
		break;
	}
	case 4: {
		system("cls");
		Recharge();
		flag = 1;
		printf("����0�ص����˵��������˳�����:");
	    flag = Input_int();
		if (flag == 0) { system("cls"); List(); }
		break;
	}
	}
}
//12.����Ա�����˵�
void Administrator_func_list() {
	/*��ջ�����*/
	//Flush_buffer();
	int i;
	char password[6];
	char trueword[6] = {'1','2','3','4','5','6'};
	int flag = 0;
	int flag1=0;
	int choose;
	printf("���������Աͨ������:");
	for (i = 0; i < 6; i++) {
		scanf_s("%c", &password[i]);
		if (trueword[i] != password[i]) { flag1 = 1; break; }
	}
	if (flag1) { printf("�����������,�������˵�"); Print_dot(6); return; }
	printf("������ȷ,�������Ա�����˵�");
	Print_dot(6);
	system("cls");
	//��ӡ�����б�
	Print_list();
	while(flag==0){
		printf("�������Ӧ���������:");
		choose = Input_int();
		while (!(choose >= 1 && choose <= 10)) { printf("�������Ӧ�����:"); choose = Input_int(); }
		switch (choose) {
		case 1 : {
			system("cls");
			int num;
			printf("�����빺�����");
			num = Input_number();
			Check_shopping_record(num);
			flag = 1;
			printf("����0�ص�����Ա�����˵������򷵻����˵�:");
			flag = Input_int();
			if (flag == 0) { system("cls"); Print_list(); }
			break;
		}
		case 2 : {
			system("cls");
			Input_shopping_record();
			flag = 1;
			printf("����0�ص�����Ա�����˵������򷵻����˵�:");
			flag = Input_int();
			if (flag == 0) { system("cls"); Print_list(); }
			break;
		}
		case 3 : {
			system("cls");
			int num;
			printf("�����빺�����");
			num = Input_number();
			bool exist = true;
			exist=Check_shopping_record(num);
			if(exist)Change_shopping_record(num);
			flag = 1;
			printf("����0�ص�����Ա�����˵������򷵻����˵�:");
			flag = Input_int();
			if (flag == 0) { system("cls"); Print_list(); }
			break;
		}
		case 4 : {
			system("cls");
			int num;
			printf("�����빺�����");
			num = Input_number();
			Delete_shopping_record(num);
			flag = 1;
			printf("����0�ص�����Ա�����˵������򷵻����˵�:");
			flag = Input_int();
			if (flag == 0) { system("cls"); Print_list(); }
			break;
		}
		case 5 : {
			system("cls");
			Check_fruit_selling_list();
			flag = 1;
			printf("����0�ص�����Ա�����˵������򷵻����˵�:");
			flag = Input_int();
			if (flag == 0) { system("cls"); Print_list(); }
			break;
		}
		case 6 : {
			system("cls");
			Print_shopping_record();
			flag = 1;
			printf("����0�ص�����Ա�����˵������򷵻����˵�:");
			flag = Input_int();
			if (flag == 0) { system("cls"); Print_list(); }
			break;
		}
		case 7 : {
			system("cls");
			int num;
			printf("�������Ա����");
			num = Input_number();
			Check_vip_buy(num);
			flag = 1;
			printf("����0�ص�����Ա�����˵������򷵻����˵�:");
			flag = Input_int();
			if (flag == 0) { system("cls"); Print_list(); }
			break;
		}
		case 8 : {
			system("cls");
			printf("������Ҫ��ѯ�Ĺ�����Ϣ�ܶ�ķ�Χ��eg.50 100��:");
			float min, max;
			min = Input_float();
			max = Input_float();
			while (min >= max) {
				printf("����ֵ����С������ֵ,���������뷶Χ:");
				min = Input_float();
				max = Input_float();
			}
			Check_big_deal(min,max);
			flag = 1;
			printf("����0�ص�����Ա�����˵������򷵻����˵�:");
			flag = Input_int();
			if (flag == 0) { system("cls"); Print_list(); }
			break;
		}
		case 9 : {
			system("cls");
			int former_hour, former_min, latter_hour, latter_min;
			int former_time, latter_time;
			int right = 0;
			while (!right) {
				right = 1;
				printf("�����뿪ʼʱ��(eg.16 00):");
				former_hour = Input_int();
				former_min = Input_int();
				while (former_hour < 0 || former_hour >= 24 || former_min < 0 || former_min >= 60) {
					printf("ʱ���ʽ�������,����������:");
					former_hour = Input_int();
					former_min = Input_int();
				}
				printf("���������ʱ��(eg.16 00):");
				latter_hour = Input_int();
				latter_min = Input_int();
				while (latter_hour < 0 || latter_hour >= 24 || latter_min < 0 || latter_min >= 60) {
					printf("ʱ���ʽ�������,����������:");
					latter_hour = Input_int();
					latter_min = Input_int();
				}
				former_time = former_hour * 60 + former_min;
				latter_time = latter_hour * 60 + latter_min;
				if (former_time >= latter_time) {printf("��ʼʱ��������ڽ���ʱ��,����������\n"); right = 0;}
			}
			Check_record_by_time(former_hour,former_min, latter_hour, latter_min);
			flag = 1;
			printf("����0�ص�����Ա�����˵������򷵻����˵�:");
			flag = Input_int();
			if (flag == 0) { system("cls"); Print_list(); }
			break;
		}
		case 10: {
		return;
	}
	}
	}
}	
	//12.1��ӡ�����б�
void Print_list() {
	printf("________________����Ա�����˵�_____________\n");
	printf(" ||#######################################||\n");
	printf(" ||------------1.��ѯ�����¼-------------||\n");
	printf(" ||***************************************||\n");
	printf(" ||------------2.¼�빺����Ϣ-------------||\n");
	printf(" ||***************************************||\n");
	printf(" ||------------3.�޸Ĺ�����Ϣ-------------||\n");
	printf(" ||***************************************||\n");
	printf(" ||------------4.ɾ�������¼-------------||\n");
	printf(" ||***************************************||\n");
	printf(" ||------------5.��ѯˮ���������---------||\n");
	printf(" ||***************************************||\n");
	printf(" ||------------6.������Ϣ�ܻ�-------------||\n");
	printf(" ||***************************************||\n");
	printf(" ||------------7.��ѯ��Ա���տ���---------||\n");
	printf(" ||***************************************||\n");
	printf(" ||------------8.��ѯ������Ϣ---------||\n");
	printf(" ||***************************************||\n");
	printf(" ||------------9.��ѯĳʱ����ڹ�����Ϣ---||\n");
	printf(" ||***************************************||\n");
	printf(" ||------------10.������һ���˵�----------||\n");
	printf(" ||***************************************||\n");
	printf(" ||#######################################||\n");
	printf("��������������������������������������������\n");
}
//13.�����Ա��
void Register() {
	FILE *fp;
	Membership_card *mc = Read_vb();
	int i;
	int k;
	float add;
	if (fopen_s(&fp, "vip balance.txt", "a")) {
		printf("��vip_balance.txtʧ��\n");
		exit(0);
	}
	printf("�������ֵ���(����300Ԫ):");
	add = Input_float();
	while (add <= 300 || add > 10000) {
		printf("��ֵ��������300-10000Ԫ�ķ�Χ��,����������:");
		add = Input_float();
	}
	for (i = 0; i < MAX; i++) if (mc[i].card_number == -1)break;
	mc[i].balance = add;
	mc[i].card_number = 3;
	for (k = 0; k < i; k++) {
		if (mc[k].card_number == -1)break;
		if (mc[k].card_number == mc[i].card_number) {
			mc[i].card_number = Get_card_number();
			k = -1;
		}
	}
	Write_vb(mc);
	free(mc);
}
//14.��Ա����ֵ
void Recharge() {
	Membership_card *mc = Read_vb();
	int num;
	int i=0;
	int flag_exist = 0;
	float add;
	printf("���������Ļ�Ա����:");
	while (!flag_exist) {
		//2.1����Ա�����Ƿ����
		num = Input_number();
		for (i = 0; i < MAX; i++) {
			if (mc[i].card_number == -1)break;
			if (mc[i].card_number == num) { flag_exist = 1; break; }
		}
		/*��Ա������������������*/
		if (!flag_exist) {
			int flag_e_e = 1;
			printf("��Ա��������,����������\n");
			printf("��û�л�Ա��,������0�˳�:");
			flag_e_e = Input_int();
			if (!flag_e_e)break;
		}
	}
	printf("��Ա���Ŵ���!��ǰ���:%f\n",mc[i].balance);
	printf("���������ĳ�ֵ���:");
	add = Input_float();
	mc[i].balance += add;
	while (mc[i].balance > 10000 || add < 0) {
		printf("���ڵ�ǰ���:%f\n",mc[i].balance);
		if (add < 0)printf("��ֵ����Ϊ����,����������:");
		if(mc[i].balance>10000)printf("���ڽ��ɳ���10000Ԫ,����������:");
		mc[i].balance =mc[i].balance-add;
		add = Input_float();
		mc[i].balance += add;
	}
	printf("���ڵ�ǰ���:%f\n", mc[i].balance);
	Write_vb(mc);
	free(mc);
}
//=================
//����Ա��������
//=================
//1.��ѯ�����¼
bool Check_shopping_record(int n) {
	int i;
	int m;
	int find = 0;
	Money mo1,mo2,mo3;
	Shopping_info *s = Read_si();
	for (i = 0;; i++) {
		if (s[i].number == -1)break;
		if (s[i].number == n) {
			find = 1;
			/*��ź�ʱ��*/
			printf("\n�������:%04d\n����ʱ��:%02d:%02d\n", s[i].number, s[i].shopping_time.hour, s[i].shopping_time.min);
			/*ˮ������*/
			printf("ƻ��(20.50Ԫ/��):%.3f\n", s[i].fruit[0].num);
			printf("����(16.33Ԫ/��):%.3f\n", s[i].fruit[1].num);
			printf("��(19.00Ԫ/��):.%.3f\n", s[i].fruit[2].num);
			printf("����(9.83Ԫ/��):%.3f\n", s[i].fruit[3].num);
			printf("���ܹ�(15.80Ԫ/��):%.3f\n", s[i].fruit[4].num);
			/*�ܶ�*/
			mo1 = Money_change(s[i].sum_m);
			printf("�ܶ�:%dԪ%d��%d��(%.3fԪ)\n", mo1.yuan, mo1.jiao, mo1.fen, s[i].sum_m);
			if (s[i].shopping_pay.flag == 0){
				/*�ֽ���Ϣ*/
				mo2 = Money_change(s[i].shopping_pay.cash.pay);
				mo3 = Money_change(s[i].shopping_pay.cash.change);
				printf("�ֽ�֧��\n֧�����:%dԪ%d��%d��(%.3fԪ)\n������:%dԪ%d��%d��(%.3fԪ)\n", mo2.yuan, mo2.jiao, mo2.fen, s[i].shopping_pay.cash.pay, mo3.yuan, mo3.jiao, mo3.fen,s[i].shopping_pay.cash.change);
			}
			/*��Ա֧����Ϣ*/
			else
				printf("��Ա��֧��\n��Ա����:%04d\n֧��ǰ���:%.6f\n֧�������:%.6f\n\n", s[i].shopping_pay.vip.card_number, s[i].shopping_pay.vip.balance, s[i].shopping_pay.after_pay);
		}
	}
	if (!find) { printf("�޸�����¼!\n\n"); free(s); return false; }
	else {free(s); return true;}
}
//2.¼�빺����Ϣ
void Input_shopping_record() {
	Buy();
}
//3.�޸Ĺ�����Ϣ
void Change_shopping_record(int n) {
	printf("������ź͹���ʱ�䲻���޸�!\n");
	printf("�����ܶ���޸�!\n");
	int choose;
	printf("________________���޸���Ŀ________________\n");
	printf(" ||#######################################||\n");
	printf(" ||------------1.ˮ������-----------------||\n");
	printf(" ||***************************************||\n");
	printf(" ||------------2.���﷽ʽ-----------------||\n");
	printf(" ||***************************************||\n");
	printf(" ||#######################################||\n");
	printf("��������������������������������������������\n");
	int flag2 = 0;//�����޸ı�־
	while (!flag2) {
		printf("�������Ӧ���������:");
		choose = Input_int();
		while (!(choose == 1 || choose == 2)) { printf("�������Ӧ�����:"); choose = Input_int(); }
		switch (choose) {
		case 1: {
			Change_fruit_num(n);
			break; }
		case 2: {
			Change_shopping_way(n);
			break; }
		}
		flag2 = 1;
		printf("ѡ������޸�������0�������������������������:");
		flag2 = Input_int();
	}
}
	//3.1�޸�ˮ������
void Change_fruit_num(int n) {
	Shopping_info *s = Read_si();
	int i;
	int choose;
	int num;
	int find = 0;
	int m;
	for (i = 0; i < MAX; i++) 	if (s[i].number == n) { find = 1; break; }
	if (!find) { free(s); return; }
	printf("1.ƻ�� 2.���� 3.�� 4.���� 5.���ܹ�\n");
	printf("������Ҫ�޸�ˮ����������:");
	choose = Input_int();
	switch (choose) {
	case 1: {
		Change_fruit_kind_num(apple, s, i);
		break;
	}
	case 2: {
		Change_fruit_kind_num(orange, s, i);
		break;
	}
	case 3: {
		Change_fruit_kind_num(pear, s, i);
		break;
	}
	case 4: {
		Change_fruit_kind_num(pomelo, s, i);
		break;
	}
	case 5: {
		Change_fruit_kind_num(hami_melon, s, i);
		break;
	}
	}
	Write_si(s);
	free(s);
}
		//3.1.1�޸�ˮ������������
       /*
	    *a:ˮ������
		*s��������Ϣ�ṹ��ָ��
		*i:��ҪѰ�ҵĹ�����Ϣ��¼�����
        */
void Change_fruit_kind_num(kind a, Shopping_info*s, int i) {
	float num;/*�޸ĺ��ˮ������*/
	float less;/*�޸�ˮ������������Ĳ��*/
	//1.��Բ�ͬˮ����������ۼ��㷽ʽ��ͬ
	num = Input_fruit_num(a);
	if(a==0)less = (s[i].fruit[0].num - num)*APPLE_P;
	if (a == 1)less = (s[i].fruit[1].num - num)*ORANGE_P;
	if (a == 2)less = (s[i].fruit[2].num - num)*PEAR_P;
	if (a == 3)less = (s[i].fruit[3].num - num)*POMELO_P;
	if (a == 4)less = (s[i].fruit[4].num - num)*HAMI_MELON_P;
	s[i].sum_m = s[i].sum_m -less ;
	s[i].fruit[a].num = num;
	//2.�����ֽ�֧������Ҫ�����޸�
	if (s[i].shopping_pay.flag == 0) {
		s[i].shopping_pay.cash.change = s[i].shopping_pay.cash.pay - s[i].sum_m;
	}
	//3.���ڻ�Ա֧������Ҫ�����޸�
	else {
		s[i].shopping_pay.after_pay = s[i].shopping_pay.vip.balance - s[i].sum_m;
		int m;
		//3.1�޸ı�����¼�����Ժ���ͬ��Ա�Ĺ�����Ϣ��¼
		int ii = i;/*��һ���û�Ա�Ĺ�����Ϣ�����*/
		for (m = i + 1; m < MAX; m++) {
			if (s[m].number == -1)break;
			if(s[m].shopping_pay.vip.card_number==s[i].shopping_pay.vip.card_number){
				s[m].shopping_pay.vip.balance = s[ii].shopping_pay.after_pay;
				s[m].shopping_pay.after_pay += less;
				ii = m;
			}
		}
		int k;
		//3.2���޸Ĺ�����������Ա���ļ���
		Membership_card *mc = Read_vb();
			//3.2.1�ڻ�Ա���ļ����ҵ��û�Ա
		for (k = 0; k < MAX; k++) {
			if (mc[k].card_number == s[i].shopping_pay.vip.card_number)break;
		}
			//3.2.2�ҵ��û�Ա�����һ����¼		
		float min = s[i].shopping_pay.after_pay;
		int l;
		for (l = i + 1; l < MAX; l++) {
			if (s[l].number == -1)break;
			if (s[l].number==mc[k].card_number&&s[l].shopping_pay.after_pay < min)min = s[l].shopping_pay.after_pay;
		}
		mc[k].balance = min;
		Write_vb(mc);
		free(mc);
	}
}
	//3.2�޸Ĺ��﷽ʽ
void Change_shopping_way(int n) {
	Shopping_info *s = Read_si();	
	Membership_card *mc = Read_vb();
	int k;
	int i;
	int find = 0;
	int num;/*����Ŀ���*/
	int flag_exist = 0;/*��Ա�����ڵı�־*/
	for (k = 0; k < MAX; k++) 	if (s[k].number == n) {	find = 1; break;}
	if (!find) {free(s); free(mc); return;}
	if (s[k].shopping_pay.flag == 0) {
		printf("���ֽ�֧����ʽ��Ϊ��Ա֧����ʽ\n");
		s[k].shopping_pay.flag = 1;
		s[k].shopping_pay.cash.change = -1;
		s[k].shopping_pay.cash.pay = -1;
		while (!flag_exist) {
			//2.1����Ա�����Ƿ����
			num = Input_number();
			for (i = 0; i < MAX; i++) {
				if (mc[i].card_number == -1)break;
				if (mc[i].card_number == num) { flag_exist = 1; break; }
			}
			/*��Ա������������������*/
			if (!flag_exist) {
				int flag_e_e = 1;
				printf("��Ա��������,����������\n");
				printf("��û�л�Ա��,������0�˳�:");
				flag_e_e = Input_int();
				if (!flag_e_e)break;
			}
			/*��Ա������*/
			else {
				if (mc[i].balance < s[k].sum_m) { printf("��Ա�����㣬�޷��޸�!\n"); break; }
				else {
					printf("֧��ǰ���:%f\n", mc[i].balance);
					s[k].shopping_pay.vip.balance = mc[i].balance;
					s[k].shopping_pay.vip.card_number = mc[i].card_number;
					s[k].shopping_pay.after_pay = mc[i].balance - s[k].sum_m;
					mc[i].balance = s->shopping_pay.after_pay;
					printf("֧�������:%f\n", mc[i].balance);
				}
			}
		}

	}
	if (s[k].shopping_pay.flag == 1) {
		printf("�ɻ�Ա֧����ʽ��Ϊ�ֽ�֧����ʽ\n");
		s[k].shopping_pay.flag = 0;
		for (i = 0; i < MAX; i++) if (mc[i].card_number == s[i].shopping_pay.vip.card_number)break;
		mc[i].balance += s[k].sum_m;
		s[k].shopping_pay.vip.balance = -1;
		s[k].shopping_pay.vip.card_number = -1;
		s[k].shopping_pay.after_pay = -1;
		float pay;
		printf("֧�����:");
		pay = Input_float();
		while (pay < s[k].sum_m) {
			printf("֧������,��Ǯ!");
			float add;
			add = Input_float();
			pay += add;
		}
		s[k].shopping_pay.cash.pay = pay;
		s[k].shopping_pay.cash.change = pay - s[k].sum_m;
	}
	Write_si(s);
	free(s);
	Write_vb(mc);
	free(mc);
}
//4.ɾ�������¼
void Delete_shopping_record(int n) {
	int i;
	int k;
	int m;
	int find = 0;
	Shopping_info *s = Read_si();
	Membership_card *mc = Read_vb();
	for (i = 0;; i++) {
		if (s[i].number == -1)break;
		k = i + 1;
		//�ҵ�������Ŷ�Ӧ�Ĺ����¼
		if (s[i].number == n) {
			if(s[i].shopping_pay.flag==1){
				for (m= 0; m < MAX; m++) if (mc[m].card_number == s[i].shopping_pay.vip.card_number)break;
				mc[m].balance = s[i].shopping_pay.vip.balance;
				Write_vb(mc);free(mc);}
			find = 1;
			s[i].number = -1;
			while (s[k].number != -1) {
				s[k].number--;
				s[k - 1] = s[k];
				k++;
			}
			break;
		}
	}
	Shopping_info_init(&s[k-1]);
	if (!find)printf("�޸�����¼!\n");
	else Write_si(s); 
	
	free(s);
}
//5.��ѯˮ���������
void Check_fruit_selling_list() {
	int choose;
	int flag = 0;
	printf("________________ˮ���б�___________________\n");
	printf(" ||#######################################||\n");
	printf(" ||------------1.ƻ��---------------------||\n");
	printf(" ||***************************************||\n");
	printf(" ||------------2.����---------------------||\n");
	printf(" ||***************************************||\n");
	printf(" ||------------3.��-----------------------||\n");
	printf(" ||***************************************||\n");
	printf(" ||------------4.����---------------------||\n");
	printf(" ||***************************************||\n");
	printf(" ||------------5.���ܹ�-------------------||\n");
	printf(" ||#######################################||\n");
	printf("��������������������������������������������\n");
	while (flag==0) {
		printf("�������Ӧˮ�������:");
		choose = Input_int();
		while (!(choose >= 1 && choose <= 5)) { printf("�������Ӧ�����:"); choose = Input_int(); }
		switch (choose) {
		case 1: {
			printf("ƻ��:\n");
			Check_fruit_selling(apple);
			break;
		}
		case 2: {
			printf("����:\n");
			Check_fruit_selling(orange);
			break;
		}
		case 3: {
			printf("��:\n");
			Check_fruit_selling(pear);
			break;
		}
		case 4: {
			printf("����:\n");
			Check_fruit_selling(pomelo);
			break;
		}
		case 5: {
			printf("���ܹ�:\n");
			Check_fruit_selling(hami_melon);
			break;
		}
		}
		printf("������ѯ������0������������������������:");
		flag = Input_int();
	}
}
	//5.1��ѯˮ���������
void Check_fruit_selling(kind a) {
	int i;
	float sum = 0;
	Shopping_info *s = Read_si();
	for (i = 0;; i++) {
		if (s[i].number == -1)break;
		if (s[i].fruit[a].num != 0) {
			printf("�������:%d   ����ʱ��%d:%d   ��������:%.2f\n", s[i].number, s[i].shopping_time.hour, s[i].shopping_time.min, s[i].fruit[a].num);
			sum += s[i].fruit[a].num;
		}
		}
	printf("��������:%.2f\n",sum);
	free(s);
}
//6.������Ϣ�ܻ�
void Print_shopping_record() {
	int i;
	Shopping_info *s = Read_si();
	for (i = 0;; i++) {
		if (s[i].number == -1)break;
		Check_shopping_record(s[i].number);
		printf("\n");
	}
	free(s);
}
//7.��ѯ��Ա���տ���
void Check_vip_buy(int n) {
	int i;
	Money m;
	float sum = 0;
	int find = 0;
	Shopping_info *s = Read_si();
	for (i = 0;; i++) {
		if (s[i].number == -1)break;
		if (s[i].shopping_pay.vip.card_number==n) {
			find = 1;
			printf("�������:%d   ����ʱ��%d:%d   ����:%.3fԪ\n  ��������:%6.fԪ\n", s[i].number, s[i].shopping_time.hour, s[i].shopping_time.min,s[i].sum_m,s[i].shopping_pay.after_pay);
			sum += s[i].sum_m;
		}
	}
	m = Money_change(sum);
	if(find)printf("�����ܻ���:%dԪ%d��%d��(%.3fԪ)\n",m.yuan,m.jiao,m.fen,sum);
	else printf("�����ڸû�Ա!\n");
	free(s);
}
//8.��ѯ������Ϣ
void Check_big_deal(float min,float max) {
	int i;
	int find=0;
	//1.��ʼ����λ�ڵ�͵�һ���ڵ�
	Node *head=(Node *)malloc(sizeof(Node));
	Node_init(head);
	Node *temp1 = head;
	temp1->next= (Node *)malloc(sizeof(Node));
	Node_init(temp1->next);
	Shopping_info *s = Read_si();
	for (i = 0; i < MAX; i++) {
		if (s[i].number == -1)break;
		if (s[i].sum_m >= min&&s[i].sum_m <= max) {
			find = 1;
			temp1->next->si = s[i];
			Node *temp2 = (Node *)malloc(sizeof(Node));
			Node_init(temp2);
			temp1->next->next = temp2;
			temp1 = temp1->next;
		}
	}
	if (!find) { printf("�޷��������Ĺ�����Ϣ!"); return; }
	else {
		temp1 = head->next;
		while (temp1->si.number != -1) {
			Check_shopping_record(temp1->si.number);
			temp1 = temp1->next;
		}
	}
	//�ͷŶ�̬�ռ�
	temp1 = head;
	while (temp1 != NULL) { 
		Node *temp3 = temp1; 
		temp1 = temp1->next;
		free(temp3); temp3 = NULL;
	}
}
//9.��ѯĳ��ʱ���ڹ�����Ϣ
void Check_record_by_time(int former_hour, int former_min, int latter_hour, int latter_min) {
	int i;
	int find = 0;
	int former_time = former_hour * 60 + former_min;
	int latter_time = latter_hour * 60 + latter_min;
	//1.��ʼ����λ�ڵ�͵�һ���ڵ�
	Node *head = (Node *)malloc(sizeof(Node));
	Node_init(head);
	Node *temp1 = head;
	temp1->next = (Node *)malloc(sizeof(Node));
	Node_init(temp1->next);
	Shopping_info *s = Read_si();
	for (i = 0; i < MAX; i++) {
		if (s[i].number == -1)break;
		int time = s[i].shopping_time.hour * 60 + s[i].shopping_time.min;
		if (time>= former_time&&time<= latter_time) {
			find = 1;
			temp1->next->si = s[i];
			Node *temp2 = (Node *)malloc(sizeof(Node));
			Node_init(temp2);
			temp1->next->next = temp2;
			temp1 = temp1->next;
		}
	}
	if (!find) { printf("�޷��������Ĺ�����Ϣ!"); return; }
	else {
		temp1 = head->next;
		while (temp1->si.number != -1) {
			Check_shopping_record(temp1->si.number);
			temp1 = temp1->next;
		}
	}
	//�ͷŶ�̬�ռ�
	temp1 = head;
	while (temp1 != NULL) {
		Node *temp3 = temp1;
		temp1 = temp1->next;
		free(temp3); temp3 = NULL;
	}
}

//===============
//���������������
//===============
//a.����ˮ��������������
float Input_fruit_num(kind a) {
	float count;
	int flag1 = 0;//��������Ϊ�����ı�־λ(0��ʾ����)
	int flag2 = 0;//���������������ı�־λ������/���ܹϣ�
	printf("����������:");
	count = Input_float();
	while(flag1==0||flag2==1){
		while (count < 0) {
			printf("��������С���㣬����������:");
			count = Input_float();
		}flag1 = 1;
		if (a == 3 || a == 4) {	
			flag2 = 1;
			while (count - (int)count > 0) {
				printf("ֻ���۸���Ϊ��λ������������һ��������:");
				count = Input_float();
			}flag2 = 0;if(count<=0)flag1 = 0;
		}
	}
	return count;
}
//b.��ȡ��Ա���ļ�,����Ҫ�ͷŶ�̬�ռ�
Membership_card* Read_vb() {
	FILE *fp;
	int i = 0;
	Membership_card *temp = (Membership_card*)malloc(MAX*sizeof(Membership_card));
	for (i = 0; i< MAX; i++) Vip_init(temp+i);
	if (fopen_s(&fp, "vip_balance.txt", "r")) {
		printf("��vip_balance.txtʧ��\n");
		exit(0);
	}
	i = 0;
	while (!feof(fp)) {
		fscanf_s(fp,"%d",&temp[i].card_number);
		fscanf_s(fp,"%f",&temp[i].balance);
		i++;
	}
	fclose(fp);
	return temp;
}
//c.�����Ա���Ż��߹�����ź���
int Input_number() {
	char temp[4] = {0};
	char c;/*������ջ�����*/
	int i;
	int num=0;
	int flag = 1;/*����ɹ��ı�־*/
	printf("\n(����λ��4λ���֣�������4λ��ֻ��ǰ4λ)\n");
	printf("������:");
	while(flag){
		flag = 0;
		for (i = 0; i < 4; i++) {
			/*�޻�������*/
			temp[i] = _getch();
			putchar(temp[i]);
			if (!(temp[i] >= 48 && temp[i] <= 57)) {
				if (temp[i] == '\r')printf("\nλ������,����������:");
				else printf("\nֻ����������,����������:");
				flag = 1;
				break;
			}
		}
	}
	printf("\n");
	num = (temp[0] - 48) * 1000 + (temp[1] - 48) * 100 + (temp[2] - 48) * 10 + (temp[3] - 48);
	return num;
}
//d.��ȡ������Ϣ�ļ�������Ҫ�ͷŶ�̬�ռ�
Shopping_info* Read_si() {
	FILE *fp;
	int i;
	int m;
	Shopping_info *temp = (Shopping_info*)malloc(MAX*sizeof(Shopping_info));
	for (i = 0; i < MAX; i++)Shopping_info_init(temp+i);
	if (fopen_s(&fp, "shopping_information.txt", "r")) {
		printf("��shopping_information.txtʧ��\n");
		exit(0);
	}
	i = 0;
	while (!feof(fp)) {
		/*��ź�ʱ��*/
		fscanf_s(fp, "%d %d %d", &temp[i].number, &temp[i].shopping_time.hour, &temp[i].shopping_time.min);
		/*ˮ������*/
		for(m=0;m<5;m++)fscanf_s(fp,"%f",&temp[i].fruit[m].num);
		/*�ܶ�*/
		fscanf_s(fp,"%f",&temp[i].sum_m);
		/*�ֽ���Ϣ*/
		fscanf_s(fp,"%f%f",&temp[i].shopping_pay.cash.pay,&temp[i].shopping_pay.cash.change);
		/*��Ա֧����Ϣ*/
		fscanf_s(fp,"%d%f%f",&temp[i].shopping_pay.vip.card_number,&temp[i].shopping_pay.vip.balance,&temp[i].shopping_pay.after_pay);
		if (temp[i].shopping_pay.cash.pay == -1)temp[i].shopping_pay.flag = 1;
		if (temp[i].shopping_pay.vip.card_number == -1)temp[i].shopping_pay.flag = 0;
		i++;
	}
	fclose(fp);
	return temp;
}
//e.���Ա���ļ�����������(ˢ�»�Ա�����)
void Write_vb(Membership_card *m) {
	FILE *fp;
	int i;
	if (fopen_s(&fp, "vip_balance.txt", "w+")) {
		printf("��vip_balance.txtʧ��\n");
		exit(0);
	}
	i = 0;
	while(m[i].card_number!=-1) {
		fprintf_s(fp,"%d  %f\n",m[i].card_number,m[i].balance);
		i++;
	}
	fclose(fp);

}
//f.������Ϣ�ļ��������ݣ�ˢ�¹�����Ϣ��
void Write_si(Shopping_info *s)																			 {
	FILE *fp;
	int i;
	int m;
	if (fopen_s(&fp, "shopping_information.txt", "w+")) {
		printf("��shopping_information.txtʧ��\n");
		exit(0);
	}
	i = 0;
	while (s[i].number != -1) {
		/*��ź�ʱ��*/
		fprintf(fp, "%d %d %d ", s[i].number, s[i].shopping_time.hour, s[i].shopping_time.min);
		/*ˮ������*/
		for (m = 0; m<5; m++)fprintf(fp, "%f ", s[i].fruit[m].num);
		/*�ܶ�*/
		fprintf(fp, "%f ", s[i].sum_m);
		/*�ֽ���Ϣ*/
		fprintf(fp, "%f %f ", s[i].shopping_pay.cash.pay, s[i].shopping_pay.cash.change);
		/*��Ա֧����Ϣ*/
		fprintf(fp, "%d %f %f\n", s[i].shopping_pay.vip.card_number, s[i].shopping_pay.vip.balance, s[i].shopping_pay.after_pay);
		i++;
	}
	fclose(fp);
}


//=================
//С����
//=================
//1.ʱ���ӳٺ���
void   Delay(int   time)//time*1000Ϊ���� 
{
	clock_t   now = clock();
	while (clock() - now   <   time);
}
//2.��㺯��
void Print_dot(int n) {
	for (int i = 0; i < n; i++) { printf("."); Delay(0.5 * 1000); }
}
//3.��ջ�����(��Ҫ�����'\n'��' ')
void Flush_buffer() {
	char ch;
	while ((ch = getchar()) != EOF && ch != '\n'&&ch!=' ');
}
//4.�������ʼ��
void Node_init(Node *t) {
	t->next = NULL;
	Shopping_info_init(&(t->si));
}
//5.��Ա�������ɺ���
int Get_card_number() {
	int id;
	srand((unsigned int)time(NULL));
	id = rand();
	while (id>=10000||id<=0) {
		id = rand() % 10000;
	}
	return id;
}
//6.����һ������
int Input_int() {
	int a;
	while (scanf_s("%d", &a) == 0) {
		Flush_buffer();
		printf("������һ��ʵ��:");
	}
	Flush_buffer();
	return a;
}
//7.����һ��������
float Input_float() {
	float f;
	while (scanf_s("%f", &f) == 0) {
		Flush_buffer();
		printf("������һ��ʵ��:");
	}
	Flush_buffer();
	return f;
}
