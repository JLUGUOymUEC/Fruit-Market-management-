#ifndef STRUCT_H_
#define STRUCT_H_

#include<stdio.h>

//=================
//一.各种基本量
//=================
/*1.限定水果价格*/
  /*1.1按重量计价*/
#define APPLE_P 20.50/*苹果*/
#define ORANGE_P 16.33/*橘子*/
#define PEAR_P 19.00/*梨*/
  /*1.2按个数计价*/
#define POMELO_P 9.83/*柚子*/
#define HAMI_MELON_P 15.80/*哈密瓜*/
/*2.定义类型:水果种类*/
typedef enum { apple, orange, pear, pomelo, hami_melon }kind;
#define MAX 100
//=================
//二.各种基本结构体
//=================
//会员卡
struct Membership_card {
	int card_number;/*会员卡号*/
	float balance;/*余额*/
};
//购物时间
struct Time {
	int hour;/*小时*/
	int min;/*分钟*/	
};
//水果
struct Fruit {
	kind what_fruit;/*水果种类*/
	float num;/*数量（个/公斤）*/
};
//金额格式
struct Money {
	int yuan;/*元*/
	int jiao;/*角*/
	int fen;/*分*/
	float value_m;/*金额总额*/
};	
//现金支付信息
struct Cash_info {
	float pay;/*支付金额*/
	float change;//找零金额	
};
//支付信息
struct Pay_info {
	int flag;/*0为现金支付 1为会员卡支付*/
	Cash_info cash;/*现金支付信息*/
	Membership_card vip;/*会员卡支付信息(卡号  支付前余额)*/
	float after_pay;/*支付后余额*/
};
//购物信息
struct Shopping_info {
	int number;/*序号*/
	Time shopping_time;/*购物时间(2)*/
	Fruit fruit[5];/*水果种类(5)*/
	float sum_m;/*元角分格式的总额*/
	Pay_info shopping_pay;/*支付信息(5)*/
};
//链表结点
struct Node {
	Shopping_info si;
	Node *next;
};

//=================
//三.各种基本操作函数
//=================
//1.时间构造函数
void Get_time(Time *tim);
//2.金额格式转换函数
Money Money_change(float t);
//3.按元角分格式输出金额
void Print(Money m);
//4.获取本次支付总额
float Get_cost(Cash_info c);
//5.会员卡初始化函数
void Vip_init(Membership_card * m);
//5.水果初始化函数
void Fruit_init(Fruit *f,kind k);
//6.支付信息初始化函数
void Pay_init(Pay_info *p);	
//7.购物信息初始化函数
void Shopping_info_init(Shopping_info *s);
//8.水果价目菜单
void Buy_fruit(Shopping_info *s);
//9.选择支付方式
void How_pay(Shopping_info *s);
//10.一次完整的购买
void Buy();
//11.功能菜单
void List();
//12.管理员操作菜单
void Administrator_func_list();
	//12.1打印功能列表
void Print_list();
//13.办理会员卡
void Register();
//14.会员卡充值
void Recharge();
//=================
//四.管理员操作函数
//=================
//1.查询购物记录
bool Check_shopping_record(int n);
//2.录入购物信息
void Input_shopping_record();
//3.修改购物信息
void Change_shopping_record(int n);
	//3.1修改水果数量
	void Change_fruit_num(int n);
		//3.1.1修改水果数量副函数
		void Change_fruit_kind_num(kind a, Shopping_info*s, int i);
	//3.2修改购物方式
void Change_shopping_way(int n);
//4.删除购物记录
void Delete_shopping_record(int n);
//5.查询水果销售情况菜单
void Check_fruit_selling_list();
	//5.1查询水果销售情况
	void Check_fruit_selling(kind a);
//6.购物信息总汇
void Print_shopping_record() ;
//7.查询会员当日开销
void Check_vip_buy(int n);
//8.查询大额购物信息
void Check_big_deal(float min,float max);
//9.查询某段时间内购物信息
void Check_record_by_time(int former_hour, int former_min, int latter_hour, int latter_min);
//=================
//五.各种输入输出函数
//=================
//a.输入水果数量函数
float Input_fruit_num(kind a); 
//b.读取会员卡文件,用完要释放动态空间
Membership_card* Read_vb();
//c.输入会员卡号或者购物序号函数
int Input_number();
//d.读取购物信息文件，用完要释放动态空间
Shopping_info* Read_si();
//e.向会员卡文件中输入数据(刷新会员卡余额)
void Write_vb(Membership_card *m);
//f.向购物信息文件输入数据（刷新购物信息）
void Write_si(Shopping_info *s);

//=================
//六.小函数
//=================
//1.时间延迟函数
void Delay(int time);
//2.打点函数
void Print_dot(int n);
//3.清空缓存区(主要是清除'\n')
void Flush_buffer();
//4.链表结点初始化
void Node_init(Node *t);
//5.会员卡号生成函数
int Get_card_number();
//6.输入一个整数
int Input_int();
//7.输入一个浮点数
float Input_float();
#endif