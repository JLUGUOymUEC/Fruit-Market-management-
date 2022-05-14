#ifndef STRUCT_H_
#define STRUCT_H_

#include<stdio.h>

//=================
//һ.���ֻ�����
//=================
/*1.�޶�ˮ���۸�*/
  /*1.1�������Ƽ�*/
#define APPLE_P 20.50/*ƻ��*/
#define ORANGE_P 16.33/*����*/
#define PEAR_P 19.00/*��*/
  /*1.2�������Ƽ�*/
#define POMELO_P 9.83/*����*/
#define HAMI_MELON_P 15.80/*���ܹ�*/
/*2.��������:ˮ������*/
typedef enum { apple, orange, pear, pomelo, hami_melon }kind;
#define MAX 100
//=================
//��.���ֻ����ṹ��
//=================
//��Ա��
struct Membership_card {
	int card_number;/*��Ա����*/
	float balance;/*���*/
};
//����ʱ��
struct Time {
	int hour;/*Сʱ*/
	int min;/*����*/	
};
//ˮ��
struct Fruit {
	kind what_fruit;/*ˮ������*/
	float num;/*��������/���*/
};
//����ʽ
struct Money {
	int yuan;/*Ԫ*/
	int jiao;/*��*/
	int fen;/*��*/
	float value_m;/*����ܶ�*/
};	
//�ֽ�֧����Ϣ
struct Cash_info {
	float pay;/*֧�����*/
	float change;//������	
};
//֧����Ϣ
struct Pay_info {
	int flag;/*0Ϊ�ֽ�֧�� 1Ϊ��Ա��֧��*/
	Cash_info cash;/*�ֽ�֧����Ϣ*/
	Membership_card vip;/*��Ա��֧����Ϣ(����  ֧��ǰ���)*/
	float after_pay;/*֧�������*/
};
//������Ϣ
struct Shopping_info {
	int number;/*���*/
	Time shopping_time;/*����ʱ��(2)*/
	Fruit fruit[5];/*ˮ������(5)*/
	float sum_m;/*Ԫ�Ƿָ�ʽ���ܶ�*/
	Pay_info shopping_pay;/*֧����Ϣ(5)*/
};
//������
struct Node {
	Shopping_info si;
	Node *next;
};

//=================
//��.���ֻ�����������
//=================
//1.ʱ�乹�캯��
void Get_time(Time *tim);
//2.����ʽת������
Money Money_change(float t);
//3.��Ԫ�Ƿָ�ʽ������
void Print(Money m);
//4.��ȡ����֧���ܶ�
float Get_cost(Cash_info c);
//5.��Ա����ʼ������
void Vip_init(Membership_card * m);
//5.ˮ����ʼ������
void Fruit_init(Fruit *f,kind k);
//6.֧����Ϣ��ʼ������
void Pay_init(Pay_info *p);	
//7.������Ϣ��ʼ������
void Shopping_info_init(Shopping_info *s);
//8.ˮ����Ŀ�˵�
void Buy_fruit(Shopping_info *s);
//9.ѡ��֧����ʽ
void How_pay(Shopping_info *s);
//10.һ�������Ĺ���
void Buy();
//11.���ܲ˵�
void List();
//12.����Ա�����˵�
void Administrator_func_list();
	//12.1��ӡ�����б�
void Print_list();
//13.�����Ա��
void Register();
//14.��Ա����ֵ
void Recharge();
//=================
//��.����Ա��������
//=================
//1.��ѯ�����¼
bool Check_shopping_record(int n);
//2.¼�빺����Ϣ
void Input_shopping_record();
//3.�޸Ĺ�����Ϣ
void Change_shopping_record(int n);
	//3.1�޸�ˮ������
	void Change_fruit_num(int n);
		//3.1.1�޸�ˮ������������
		void Change_fruit_kind_num(kind a, Shopping_info*s, int i);
	//3.2�޸Ĺ��﷽ʽ
void Change_shopping_way(int n);
//4.ɾ�������¼
void Delete_shopping_record(int n);
//5.��ѯˮ����������˵�
void Check_fruit_selling_list();
	//5.1��ѯˮ���������
	void Check_fruit_selling(kind a);
//6.������Ϣ�ܻ�
void Print_shopping_record() ;
//7.��ѯ��Ա���տ���
void Check_vip_buy(int n);
//8.��ѯ������Ϣ
void Check_big_deal(float min,float max);
//9.��ѯĳ��ʱ���ڹ�����Ϣ
void Check_record_by_time(int former_hour, int former_min, int latter_hour, int latter_min);
//=================
//��.���������������
//=================
//a.����ˮ����������
float Input_fruit_num(kind a); 
//b.��ȡ��Ա���ļ�,����Ҫ�ͷŶ�̬�ռ�
Membership_card* Read_vb();
//c.�����Ա���Ż��߹�����ź���
int Input_number();
//d.��ȡ������Ϣ�ļ�������Ҫ�ͷŶ�̬�ռ�
Shopping_info* Read_si();
//e.���Ա���ļ�����������(ˢ�»�Ա�����)
void Write_vb(Membership_card *m);
//f.������Ϣ�ļ��������ݣ�ˢ�¹�����Ϣ��
void Write_si(Shopping_info *s);

//=================
//��.С����
//=================
//1.ʱ���ӳٺ���
void Delay(int time);
//2.��㺯��
void Print_dot(int n);
//3.��ջ�����(��Ҫ�����'\n')
void Flush_buffer();
//4.�������ʼ��
void Node_init(Node *t);
//5.��Ա�������ɺ���
int Get_card_number();
//6.����һ������
int Input_int();
//7.����һ��������
float Input_float();
#endif