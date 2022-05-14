#include"struct.h"
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>


//=================
//各种基本操作函数
//=================
//1.时间构造函数
void Get_time(Time* tim) {
	struct tm t;   //tm结构指针
	time_t now;  //声明time_t类型变量
	time(&now);      //获取系统日期和时间
	localtime_s(&t, &now);   //获取当地日期和时间
	tim->hour = t.tm_hour;
	tim->min = t.tm_min;
}
//2.金额格式转换函数（返回money格式） 
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
//3.按元角分格式输出金额
void Print(Money m) {
	m=Money_change(m.value_m);
	printf("%d元%d角%d分",m.yuan,m.jiao,m.fen);
}
//4.获取本次支付总额(现金支付信息)
float Get_cost(Cash_info c) { 
	return c.pay - c.change; 
}
//5.会员卡初始化函数
void Vip_init(Membership_card * m) {
	m->card_number = -1;
	m->balance = -1;
}
//5.水果初始化函数
void Fruit_init(Fruit *f,kind k) {
	f->num = 0;
	f->what_fruit = k;
}
//6.支付信息初始化函数
void Pay_init(Pay_info *p) {
	p->flag = -1;
	p->cash.pay = -1;
	p->cash.change =-1 ;
	Vip_init(&(p->vip));
	p->after_pay = -1;
}
//7.购物信息初始化函数
void Shopping_info_init(Shopping_info *s) {
	s->number = -1;
	//2.购物时间初始化
	s->shopping_time.hour = -1;
	s->shopping_time.min = -1;
	//3.水果信息初始化
	Fruit_init(&(s->fruit[0]),apple);
	Fruit_init(&(s->fruit[1]), orange);
	Fruit_init(&(s->fruit[2]), pear);
	Fruit_init(&(s->fruit[3]), pomelo);
	Fruit_init(&(s->fruit[4]), hami_melon);
	//4.总额初始化
	s->sum_m= 0;
	//5.支付信息初始化
	Pay_init(&(s->shopping_pay));
}
//8.买水果
void Buy_fruit(Shopping_info *s){
	Get_time(&(s->shopping_time));
	printf( "________________水果价目菜单________________\n");
	printf( " ||#######################################||\n");
	printf( " ||------------1.苹果(20.50元/公斤)-------||\n");
	printf( " ||***************************************||\n");
	printf(" ||------------2.橘子(16.33元/公斤)-------||\n");
	printf(" ||***************************************||\n");
	printf(" ||------------3.梨(19.00元/公斤)---------||\n");
	printf(" ||***************************************||\n");
	printf(" ||------------4.柚子(9.83元/个)----------||\n");
	printf(" ||***************************************||\n");
	printf(" ||------------5.哈密瓜(15.80元/个)-------||\n");
	printf(" ||***************************************||\n");
	printf(" ||#######################################||\n");
	printf( "￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣\n");
	int flag1;//水果种类标志
	int flag2=0 ;//继续购买标志
	float count;//水果数量
	while(!flag2){
		printf("请输入你要购买的水果种类：");
		flag1 = Input_int();
		while (flag1 > 5 || flag1 <= 0) { printf("输入的序号不存在，请重新输入:"); flag1 = Input_int();}
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
		printf("选择继续购买请输入0，否则输入任意非零整数即可:");
		flag2 = Input_int(); 
	}
	printf("本次购买总金额:%f\n",s->sum_m);
	How_pay(s);
}
//9.选择购买方式
void How_pay(Shopping_info *s) {
	int i;/*循环变量*/
	int flag = 0;/*购买方式选择标志*/
	printf("请选择购买方式:(1)现金支付(2)会员卡支付\n");
	flag = Input_int();
	/*本次开销超过1000元，则只能选择现金支付*/
	if (s->sum_m > 1000) { printf("开销超过1000元，只能选择现金支付\n"); flag = 1; }
	while (!(flag == 1 || flag == 2)) {
		printf("请输入1或2:");
		flag = Input_int();
	}
	//1.选择现金支付
	if (flag == 1) {
		//1.1确定支付方式标志的值
		s->shopping_pay.flag = 0;
		float pay;/*支付金额*/
		printf("请输入支付金额:");
		pay = Input_float();
		//1.2支付金额不足
		while (pay < s->sum_m) {
			printf("支付金额不足!加钱:");
			float add_pay;
			add_pay = Input_float();
			pay += add_pay;
		}
		//1.3完成支付
		s->shopping_pay.cash.pay = pay;
		s->shopping_pay.cash.change = pay -(s->sum_m);
		printf("\n找零:%f\n",s->shopping_pay.cash.change);
	}
	//2.选择会员卡支付
	if (flag == 2) {
		s->shopping_pay.flag = 1;
		int num;/*输入的卡号*/
		int flag_exist=0;/*会员卡存在的标志*/
		Membership_card *mc = Read_vb();
		while (!flag_exist) {
			//2.1检测会员卡号是否存在
			num = Input_number();
			for (i = 0; i < MAX; i++) {	
				if (mc[i].card_number == -1)break;
				if (mc[i].card_number == num) { flag_exist = 1; break; }
			}
			/*会员卡不存在则重新输入*/
			if (!flag_exist) {
				int flag_e_e=1;
				printf("会员卡不存在,请重新输入\n");
				printf("若没有会员卡,请输入0退出:");
				flag_e_e = Input_int();
				if (!flag_e_e)break;
			}
			/*会员卡存在*/
			else {
				if (mc[i].balance < s->sum_m) { printf("会员卡余额不足，无法购买!\n"); break; }
				else {
					printf("支付前余额:%f\n",mc[i].balance);
					s->shopping_pay.vip.balance = mc[i].balance;
					s->shopping_pay.vip.card_number = mc[i].card_number;	
					s->shopping_pay.after_pay = mc[i].balance - s->sum_m;
					mc[i].balance = s->shopping_pay.after_pay;
					printf("支付后余额:%f\n", mc[i].balance);
					Write_vb(mc);
				}
			}
		}
		free(mc);
	}
}
//10.一次完整的购买
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
//11.功能菜单
void List() {
	int choose;
	int flag;
	printf("________________主菜单______________________\n");
	printf(" ||#######################################||\n");
	printf(" ||------------1.购买水果-----------------||\n");
	printf(" ||***************************************||\n");
	printf(" ||------------2.管理员操作---------------||\n");
	printf(" ||***************************************||\n");
	printf(" ||------------3.办理会员卡---------------||\n");
	printf(" ||***************************************||\n");
	printf(" ||------------4.会员卡充值---------------||\n");
	printf(" ||***************************************||\n");
	printf(" ||#######################################||\n");
	printf("￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣\n");
	printf("请输入对应操作的序号:");
	choose = Input_int();
	while (!(choose >=1&&choose<=4)) { printf("请输入对应的序号:"); choose = Input_int(); }
	switch (choose) {
	case 1:{
		system("cls");
		Buy();
		flag = 1;
		printf("输入0回到主菜单，否则退出程序:");
		 flag = Input_int();
		if (flag == 0) { system("cls"); List(); }
		break;
	}
	case 2: {
		system("cls");
		Administrator_func_list();
		/*清空缓存区*/
		//Flush_buffer();
		system("cls");
		List();
		break;
	}
	case 3: {
		system("cls");
		Register();
		flag = 1;
		printf("输入0回到主菜单，否则退出程序:");
		flag = Input_int();
		if (flag == 0) { system("cls"); List(); }
		break;
	}
	case 4: {
		system("cls");
		Recharge();
		flag = 1;
		printf("输入0回到主菜单，否则退出程序:");
	    flag = Input_int();
		if (flag == 0) { system("cls"); List(); }
		break;
	}
	}
}
//12.管理员操作菜单
void Administrator_func_list() {
	/*清空缓存区*/
	//Flush_buffer();
	int i;
	char password[6];
	char trueword[6] = {'1','2','3','4','5','6'};
	int flag = 0;
	int flag1=0;
	int choose;
	printf("请输入管理员通过密码:");
	for (i = 0; i < 6; i++) {
		scanf_s("%c", &password[i]);
		if (trueword[i] != password[i]) { flag1 = 1; break; }
	}
	if (flag1) { printf("密码输入错误,返回主菜单"); Print_dot(6); return; }
	printf("密码正确,进入管理员操作菜单");
	Print_dot(6);
	system("cls");
	//打印功能列表
	Print_list();
	while(flag==0){
		printf("请输入对应操作的序号:");
		choose = Input_int();
		while (!(choose >= 1 && choose <= 10)) { printf("请输入对应的序号:"); choose = Input_int(); }
		switch (choose) {
		case 1 : {
			system("cls");
			int num;
			printf("请输入购物序号");
			num = Input_number();
			Check_shopping_record(num);
			flag = 1;
			printf("输入0回到管理员操作菜单，否则返回主菜单:");
			flag = Input_int();
			if (flag == 0) { system("cls"); Print_list(); }
			break;
		}
		case 2 : {
			system("cls");
			Input_shopping_record();
			flag = 1;
			printf("输入0回到管理员操作菜单，否则返回主菜单:");
			flag = Input_int();
			if (flag == 0) { system("cls"); Print_list(); }
			break;
		}
		case 3 : {
			system("cls");
			int num;
			printf("请输入购物序号");
			num = Input_number();
			bool exist = true;
			exist=Check_shopping_record(num);
			if(exist)Change_shopping_record(num);
			flag = 1;
			printf("输入0回到管理员操作菜单，否则返回主菜单:");
			flag = Input_int();
			if (flag == 0) { system("cls"); Print_list(); }
			break;
		}
		case 4 : {
			system("cls");
			int num;
			printf("请输入购物序号");
			num = Input_number();
			Delete_shopping_record(num);
			flag = 1;
			printf("输入0回到管理员操作菜单，否则返回主菜单:");
			flag = Input_int();
			if (flag == 0) { system("cls"); Print_list(); }
			break;
		}
		case 5 : {
			system("cls");
			Check_fruit_selling_list();
			flag = 1;
			printf("输入0回到管理员操作菜单，否则返回主菜单:");
			flag = Input_int();
			if (flag == 0) { system("cls"); Print_list(); }
			break;
		}
		case 6 : {
			system("cls");
			Print_shopping_record();
			flag = 1;
			printf("输入0回到管理员操作菜单，否则返回主菜单:");
			flag = Input_int();
			if (flag == 0) { system("cls"); Print_list(); }
			break;
		}
		case 7 : {
			system("cls");
			int num;
			printf("请输入会员卡号");
			num = Input_number();
			Check_vip_buy(num);
			flag = 1;
			printf("输入0回到管理员操作菜单，否则返回主菜单:");
			flag = Input_int();
			if (flag == 0) { system("cls"); Print_list(); }
			break;
		}
		case 8 : {
			system("cls");
			printf("请输入要查询的购物信息总额的范围（eg.50 100）:");
			float min, max;
			min = Input_float();
			max = Input_float();
			while (min >= max) {
				printf("下限值必须小于上限值,请重新输入范围:");
				min = Input_float();
				max = Input_float();
			}
			Check_big_deal(min,max);
			flag = 1;
			printf("输入0回到管理员操作菜单，否则返回主菜单:");
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
				printf("请输入开始时间(eg.16 00):");
				former_hour = Input_int();
				former_min = Input_int();
				while (former_hour < 0 || former_hour >= 24 || former_min < 0 || former_min >= 60) {
					printf("时间格式输入错误,请重新输入:");
					former_hour = Input_int();
					former_min = Input_int();
				}
				printf("请输入结束时间(eg.16 00):");
				latter_hour = Input_int();
				latter_min = Input_int();
				while (latter_hour < 0 || latter_hour >= 24 || latter_min < 0 || latter_min >= 60) {
					printf("时间格式输入错误,请重新输入:");
					latter_hour = Input_int();
					latter_min = Input_int();
				}
				former_time = former_hour * 60 + former_min;
				latter_time = latter_hour * 60 + latter_min;
				if (former_time >= latter_time) {printf("开始时间必须早于结束时间,请重新输入\n"); right = 0;}
			}
			Check_record_by_time(former_hour,former_min, latter_hour, latter_min);
			flag = 1;
			printf("输入0回到管理员操作菜单，否则返回主菜单:");
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
	//12.1打印功能列表
void Print_list() {
	printf("________________管理员操作菜单_____________\n");
	printf(" ||#######################################||\n");
	printf(" ||------------1.查询购物记录-------------||\n");
	printf(" ||***************************************||\n");
	printf(" ||------------2.录入购物信息-------------||\n");
	printf(" ||***************************************||\n");
	printf(" ||------------3.修改购物信息-------------||\n");
	printf(" ||***************************************||\n");
	printf(" ||------------4.删除购物记录-------------||\n");
	printf(" ||***************************************||\n");
	printf(" ||------------5.查询水果销售情况---------||\n");
	printf(" ||***************************************||\n");
	printf(" ||------------6.购物信息总汇-------------||\n");
	printf(" ||***************************************||\n");
	printf(" ||------------7.查询会员当日开销---------||\n");
	printf(" ||***************************************||\n");
	printf(" ||------------8.查询大额购物信息---------||\n");
	printf(" ||***************************************||\n");
	printf(" ||------------9.查询某时间段内购物信息---||\n");
	printf(" ||***************************************||\n");
	printf(" ||------------10.返回上一级菜单----------||\n");
	printf(" ||***************************************||\n");
	printf(" ||#######################################||\n");
	printf("￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣\n");
}
//13.办理会员卡
void Register() {
	FILE *fp;
	Membership_card *mc = Read_vb();
	int i;
	int k;
	float add;
	if (fopen_s(&fp, "vip balance.txt", "a")) {
		printf("打开vip_balance.txt失败\n");
		exit(0);
	}
	printf("请输入充值金额(至少300元):");
	add = Input_float();
	while (add <= 300 || add > 10000) {
		printf("充值金额必须在300-10000元的范围内,请重新输入:");
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
//14.会员卡充值
void Recharge() {
	Membership_card *mc = Read_vb();
	int num;
	int i=0;
	int flag_exist = 0;
	float add;
	printf("请输入您的会员卡号:");
	while (!flag_exist) {
		//2.1检测会员卡号是否存在
		num = Input_number();
		for (i = 0; i < MAX; i++) {
			if (mc[i].card_number == -1)break;
			if (mc[i].card_number == num) { flag_exist = 1; break; }
		}
		/*会员卡不存在则重新输入*/
		if (!flag_exist) {
			int flag_e_e = 1;
			printf("会员卡不存在,请重新输入\n");
			printf("若没有会员卡,请输入0退出:");
			flag_e_e = Input_int();
			if (!flag_e_e)break;
		}
	}
	printf("会员卡号存在!当前余额:%f\n",mc[i].balance);
	printf("请输入您的充值金额:");
	add = Input_float();
	mc[i].balance += add;
	while (mc[i].balance > 10000 || add < 0) {
		printf("卡内当前余额:%f\n",mc[i].balance);
		if (add < 0)printf("充值金额不可为负数,请重新输入:");
		if(mc[i].balance>10000)printf("卡内金额不可超过10000元,请重新输入:");
		mc[i].balance =mc[i].balance-add;
		add = Input_float();
		mc[i].balance += add;
	}
	printf("卡内当前余额:%f\n", mc[i].balance);
	Write_vb(mc);
	free(mc);
}
//=================
//管理员操作函数
//=================
//1.查询购物记录
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
			/*序号和时间*/
			printf("\n购物序号:%04d\n购物时间:%02d:%02d\n", s[i].number, s[i].shopping_time.hour, s[i].shopping_time.min);
			/*水果数量*/
			printf("苹果(20.50元/斤):%.3f\n", s[i].fruit[0].num);
			printf("橘子(16.33元/斤):%.3f\n", s[i].fruit[1].num);
			printf("梨(19.00元/斤):.%.3f\n", s[i].fruit[2].num);
			printf("柚子(9.83元/个):%.3f\n", s[i].fruit[3].num);
			printf("哈密瓜(15.80元/个):%.3f\n", s[i].fruit[4].num);
			/*总额*/
			mo1 = Money_change(s[i].sum_m);
			printf("总额:%d元%d角%d分(%.3f元)\n", mo1.yuan, mo1.jiao, mo1.fen, s[i].sum_m);
			if (s[i].shopping_pay.flag == 0){
				/*现金信息*/
				mo2 = Money_change(s[i].shopping_pay.cash.pay);
				mo3 = Money_change(s[i].shopping_pay.cash.change);
				printf("现金支付\n支付金额:%d元%d角%d分(%.3f元)\n找零金额:%d元%d角%d分(%.3f元)\n", mo2.yuan, mo2.jiao, mo2.fen, s[i].shopping_pay.cash.pay, mo3.yuan, mo3.jiao, mo3.fen,s[i].shopping_pay.cash.change);
			}
			/*会员支付信息*/
			else
				printf("会员卡支付\n会员卡号:%04d\n支付前余额:%.6f\n支付后余额:%.6f\n\n", s[i].shopping_pay.vip.card_number, s[i].shopping_pay.vip.balance, s[i].shopping_pay.after_pay);
		}
	}
	if (!find) { printf("无该条记录!\n\n"); free(s); return false; }
	else {free(s); return true;}
}
//2.录入购物信息
void Input_shopping_record() {
	Buy();
}
//3.修改购物信息
void Change_shopping_record(int n) {
	printf("购物序号和购物时间不可修改!\n");
	printf("购物总额不可修改!\n");
	int choose;
	printf("________________可修改条目________________\n");
	printf(" ||#######################################||\n");
	printf(" ||------------1.水果数量-----------------||\n");
	printf(" ||***************************************||\n");
	printf(" ||------------2.购物方式-----------------||\n");
	printf(" ||***************************************||\n");
	printf(" ||#######################################||\n");
	printf("￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣\n");
	int flag2 = 0;//继续修改标志
	while (!flag2) {
		printf("请输入对应操作的序号:");
		choose = Input_int();
		while (!(choose == 1 || choose == 2)) { printf("请输入对应的序号:"); choose = Input_int(); }
		switch (choose) {
		case 1: {
			Change_fruit_num(n);
			break; }
		case 2: {
			Change_shopping_way(n);
			break; }
		}
		flag2 = 1;
		printf("选择继续修改请输入0，否则输入任意非零整数即可:");
		flag2 = Input_int();
	}
}
	//3.1修改水果数量
void Change_fruit_num(int n) {
	Shopping_info *s = Read_si();
	int i;
	int choose;
	int num;
	int find = 0;
	int m;
	for (i = 0; i < MAX; i++) 	if (s[i].number == n) { find = 1; break; }
	if (!find) { free(s); return; }
	printf("1.苹果 2.橘子 3.梨 4.柚子 5.哈密瓜\n");
	printf("请输入要修改水果种类的序号:");
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
		//3.1.1修改水果数量副函数
       /*
	    *a:水果种类
		*s：购物信息结构体指针
		*i:所要寻找的购物信息记录的序号
        */
void Change_fruit_kind_num(kind a, Shopping_info*s, int i) {
	float num;/*修改后的水果数量*/
	float less;/*修改水果数量后产生的差价*/
	//1.针对不同水果，产生差价计算方式不同
	num = Input_fruit_num(a);
	if(a==0)less = (s[i].fruit[0].num - num)*APPLE_P;
	if (a == 1)less = (s[i].fruit[1].num - num)*ORANGE_P;
	if (a == 2)less = (s[i].fruit[2].num - num)*PEAR_P;
	if (a == 3)less = (s[i].fruit[3].num - num)*POMELO_P;
	if (a == 4)less = (s[i].fruit[4].num - num)*HAMI_MELON_P;
	s[i].sum_m = s[i].sum_m -less ;
	s[i].fruit[a].num = num;
	//2.对于现金支付所需要做的修改
	if (s[i].shopping_pay.flag == 0) {
		s[i].shopping_pay.cash.change = s[i].shopping_pay.cash.pay - s[i].sum_m;
	}
	//3.对于会员支付所需要做的修改
	else {
		s[i].shopping_pay.after_pay = s[i].shopping_pay.vip.balance - s[i].sum_m;
		int m;
		//3.1修改本条记录及其以后相同会员的购物信息记录
		int ii = i;/*上一条该会员的购物信息的序号*/
		for (m = i + 1; m < MAX; m++) {
			if (s[m].number == -1)break;
			if(s[m].shopping_pay.vip.card_number==s[i].shopping_pay.vip.card_number){
				s[m].shopping_pay.vip.balance = s[ii].shopping_pay.after_pay;
				s[m].shopping_pay.after_pay += less;
				ii = m;
			}
		}
		int k;
		//3.2将修改过后的余额存入会员卡文件中
		Membership_card *mc = Read_vb();
			//3.2.1在会员看文件中找到该会员
		for (k = 0; k < MAX; k++) {
			if (mc[k].card_number == s[i].shopping_pay.vip.card_number)break;
		}
			//3.2.2找到该会员的最后一条记录		
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
	//3.2修改购物方式
void Change_shopping_way(int n) {
	Shopping_info *s = Read_si();	
	Membership_card *mc = Read_vb();
	int k;
	int i;
	int find = 0;
	int num;/*输入的卡号*/
	int flag_exist = 0;/*会员卡存在的标志*/
	for (k = 0; k < MAX; k++) 	if (s[k].number == n) {	find = 1; break;}
	if (!find) {free(s); free(mc); return;}
	if (s[k].shopping_pay.flag == 0) {
		printf("由现金支付方式改为会员支付方式\n");
		s[k].shopping_pay.flag = 1;
		s[k].shopping_pay.cash.change = -1;
		s[k].shopping_pay.cash.pay = -1;
		while (!flag_exist) {
			//2.1检测会员卡号是否存在
			num = Input_number();
			for (i = 0; i < MAX; i++) {
				if (mc[i].card_number == -1)break;
				if (mc[i].card_number == num) { flag_exist = 1; break; }
			}
			/*会员卡不存在则重新输入*/
			if (!flag_exist) {
				int flag_e_e = 1;
				printf("会员卡不存在,请重新输入\n");
				printf("若没有会员卡,请输入0退出:");
				flag_e_e = Input_int();
				if (!flag_e_e)break;
			}
			/*会员卡存在*/
			else {
				if (mc[i].balance < s[k].sum_m) { printf("会员卡余额不足，无法修改!\n"); break; }
				else {
					printf("支付前余额:%f\n", mc[i].balance);
					s[k].shopping_pay.vip.balance = mc[i].balance;
					s[k].shopping_pay.vip.card_number = mc[i].card_number;
					s[k].shopping_pay.after_pay = mc[i].balance - s[k].sum_m;
					mc[i].balance = s->shopping_pay.after_pay;
					printf("支付后余额:%f\n", mc[i].balance);
				}
			}
		}

	}
	if (s[k].shopping_pay.flag == 1) {
		printf("由会员支付方式改为现金支付方式\n");
		s[k].shopping_pay.flag = 0;
		for (i = 0; i < MAX; i++) if (mc[i].card_number == s[i].shopping_pay.vip.card_number)break;
		mc[i].balance += s[k].sum_m;
		s[k].shopping_pay.vip.balance = -1;
		s[k].shopping_pay.vip.card_number = -1;
		s[k].shopping_pay.after_pay = -1;
		float pay;
		printf("支付金额:");
		pay = Input_float();
		while (pay < s[k].sum_m) {
			printf("支付金额不足,加钱!");
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
//4.删除购物记录
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
		//找到购物序号对应的购物记录
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
	if (!find)printf("无该条记录!\n");
	else Write_si(s); 
	
	free(s);
}
//5.查询水果销售情况
void Check_fruit_selling_list() {
	int choose;
	int flag = 0;
	printf("________________水果列表___________________\n");
	printf(" ||#######################################||\n");
	printf(" ||------------1.苹果---------------------||\n");
	printf(" ||***************************************||\n");
	printf(" ||------------2.橘子---------------------||\n");
	printf(" ||***************************************||\n");
	printf(" ||------------3.梨-----------------------||\n");
	printf(" ||***************************************||\n");
	printf(" ||------------4.柚子---------------------||\n");
	printf(" ||***************************************||\n");
	printf(" ||------------5.哈密瓜-------------------||\n");
	printf(" ||#######################################||\n");
	printf("￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣\n");
	while (flag==0) {
		printf("请输入对应水果的序号:");
		choose = Input_int();
		while (!(choose >= 1 && choose <= 5)) { printf("请输入对应的序号:"); choose = Input_int(); }
		switch (choose) {
		case 1: {
			printf("苹果:\n");
			Check_fruit_selling(apple);
			break;
		}
		case 2: {
			printf("橘子:\n");
			Check_fruit_selling(orange);
			break;
		}
		case 3: {
			printf("梨:\n");
			Check_fruit_selling(pear);
			break;
		}
		case 4: {
			printf("柚子:\n");
			Check_fruit_selling(pomelo);
			break;
		}
		case 5: {
			printf("哈密瓜:\n");
			Check_fruit_selling(hami_melon);
			break;
		}
		}
		printf("继续查询请输入0，否则输入任意正整数即可:");
		flag = Input_int();
	}
}
	//5.1查询水果销售情况
void Check_fruit_selling(kind a) {
	int i;
	float sum = 0;
	Shopping_info *s = Read_si();
	for (i = 0;; i++) {
		if (s[i].number == -1)break;
		if (s[i].fruit[a].num != 0) {
			printf("购物序号:%d   销售时间%d:%d   销售数量:%.2f\n", s[i].number, s[i].shopping_time.hour, s[i].shopping_time.min, s[i].fruit[a].num);
			sum += s[i].fruit[a].num;
		}
		}
	printf("总销售量:%.2f\n",sum);
	free(s);
}
//6.购物信息总汇
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
//7.查询会员当日开销
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
			printf("购物序号:%d   销售时间%d:%d   花费:%.3f元\n  购物后余额:%6.f元\n", s[i].number, s[i].shopping_time.hour, s[i].shopping_time.min,s[i].sum_m,s[i].shopping_pay.after_pay);
			sum += s[i].sum_m;
		}
	}
	m = Money_change(sum);
	if(find)printf("当日总花销:%d元%d角%d分(%.3f元)\n",m.yuan,m.jiao,m.fen,sum);
	else printf("不存在该会员!\n");
	free(s);
}
//8.查询大额购物信息
void Check_big_deal(float min,float max) {
	int i;
	int find=0;
	//1.初始化哨位节点和第一个节点
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
	if (!find) { printf("无符合条件的购物信息!"); return; }
	else {
		temp1 = head->next;
		while (temp1->si.number != -1) {
			Check_shopping_record(temp1->si.number);
			temp1 = temp1->next;
		}
	}
	//释放动态空间
	temp1 = head;
	while (temp1 != NULL) { 
		Node *temp3 = temp1; 
		temp1 = temp1->next;
		free(temp3); temp3 = NULL;
	}
}
//9.查询某段时间内购物信息
void Check_record_by_time(int former_hour, int former_min, int latter_hour, int latter_min) {
	int i;
	int find = 0;
	int former_time = former_hour * 60 + former_min;
	int latter_time = latter_hour * 60 + latter_min;
	//1.初始化哨位节点和第一个节点
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
	if (!find) { printf("无符合条件的购物信息!"); return; }
	else {
		temp1 = head->next;
		while (temp1->si.number != -1) {
			Check_shopping_record(temp1->si.number);
			temp1 = temp1->next;
		}
	}
	//释放动态空间
	temp1 = head;
	while (temp1 != NULL) {
		Node *temp3 = temp1;
		temp1 = temp1->next;
		free(temp3); temp3 = NULL;
	}
}

//===============
//各种输入输出函数
//===============
//a.输入水果购买数量函数
float Input_fruit_num(kind a) {
	float count;
	int flag1 = 0;//购买数量为正数的标志位(0表示错误)
	int flag2 = 0;//购买数量是整数的标志位（柚子/哈密瓜）
	printf("请输入数量:");
	count = Input_float();
	while(flag1==0||flag2==1){
		while (count < 0) {
			printf("数量不可小于零，请重新输入:");
			count = Input_float();
		}flag1 = 1;
		if (a == 3 || a == 4) {	
			flag2 = 1;
			while (count - (int)count > 0) {
				printf("只可论个作为单位，请重新输入一个正整数:");
				count = Input_float();
			}flag2 = 0;if(count<=0)flag1 = 0;
		}
	}
	return count;
}
//b.读取会员卡文件,用完要释放动态空间
Membership_card* Read_vb() {
	FILE *fp;
	int i = 0;
	Membership_card *temp = (Membership_card*)malloc(MAX*sizeof(Membership_card));
	for (i = 0; i< MAX; i++) Vip_init(temp+i);
	if (fopen_s(&fp, "vip_balance.txt", "r")) {
		printf("打开vip_balance.txt失败\n");
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
//c.输入会员卡号或者购物序号函数
int Input_number() {
	char temp[4] = {0};
	char c;/*用来清空缓冲区*/
	int i;
	int num=0;
	int flag = 1;/*输入成功的标志*/
	printf("\n(输入位数4位数字，若超过4位则只看前4位)\n");
	printf("请输入:");
	while(flag){
		flag = 0;
		for (i = 0; i < 4; i++) {
			/*无缓冲输入*/
			temp[i] = _getch();
			putchar(temp[i]);
			if (!(temp[i] >= 48 && temp[i] <= 57)) {
				if (temp[i] == '\r')printf("\n位数不足,请重新输入:");
				else printf("\n只能输入数字,请重新输入:");
				flag = 1;
				break;
			}
		}
	}
	printf("\n");
	num = (temp[0] - 48) * 1000 + (temp[1] - 48) * 100 + (temp[2] - 48) * 10 + (temp[3] - 48);
	return num;
}
//d.读取购物信息文件，用完要释放动态空间
Shopping_info* Read_si() {
	FILE *fp;
	int i;
	int m;
	Shopping_info *temp = (Shopping_info*)malloc(MAX*sizeof(Shopping_info));
	for (i = 0; i < MAX; i++)Shopping_info_init(temp+i);
	if (fopen_s(&fp, "shopping_information.txt", "r")) {
		printf("打开shopping_information.txt失败\n");
		exit(0);
	}
	i = 0;
	while (!feof(fp)) {
		/*序号和时间*/
		fscanf_s(fp, "%d %d %d", &temp[i].number, &temp[i].shopping_time.hour, &temp[i].shopping_time.min);
		/*水果数量*/
		for(m=0;m<5;m++)fscanf_s(fp,"%f",&temp[i].fruit[m].num);
		/*总额*/
		fscanf_s(fp,"%f",&temp[i].sum_m);
		/*现金信息*/
		fscanf_s(fp,"%f%f",&temp[i].shopping_pay.cash.pay,&temp[i].shopping_pay.cash.change);
		/*会员支付信息*/
		fscanf_s(fp,"%d%f%f",&temp[i].shopping_pay.vip.card_number,&temp[i].shopping_pay.vip.balance,&temp[i].shopping_pay.after_pay);
		if (temp[i].shopping_pay.cash.pay == -1)temp[i].shopping_pay.flag = 1;
		if (temp[i].shopping_pay.vip.card_number == -1)temp[i].shopping_pay.flag = 0;
		i++;
	}
	fclose(fp);
	return temp;
}
//e.向会员卡文件中输入数据(刷新会员卡余额)
void Write_vb(Membership_card *m) {
	FILE *fp;
	int i;
	if (fopen_s(&fp, "vip_balance.txt", "w+")) {
		printf("打开vip_balance.txt失败\n");
		exit(0);
	}
	i = 0;
	while(m[i].card_number!=-1) {
		fprintf_s(fp,"%d  %f\n",m[i].card_number,m[i].balance);
		i++;
	}
	fclose(fp);

}
//f.向购物信息文件输入数据（刷新购物信息）
void Write_si(Shopping_info *s)																			 {
	FILE *fp;
	int i;
	int m;
	if (fopen_s(&fp, "shopping_information.txt", "w+")) {
		printf("打开shopping_information.txt失败\n");
		exit(0);
	}
	i = 0;
	while (s[i].number != -1) {
		/*序号和时间*/
		fprintf(fp, "%d %d %d ", s[i].number, s[i].shopping_time.hour, s[i].shopping_time.min);
		/*水果数量*/
		for (m = 0; m<5; m++)fprintf(fp, "%f ", s[i].fruit[m].num);
		/*总额*/
		fprintf(fp, "%f ", s[i].sum_m);
		/*现金信息*/
		fprintf(fp, "%f %f ", s[i].shopping_pay.cash.pay, s[i].shopping_pay.cash.change);
		/*会员支付信息*/
		fprintf(fp, "%d %f %f\n", s[i].shopping_pay.vip.card_number, s[i].shopping_pay.vip.balance, s[i].shopping_pay.after_pay);
		i++;
	}
	fclose(fp);
}


//=================
//小函数
//=================
//1.时间延迟函数
void   Delay(int   time)//time*1000为秒数 
{
	clock_t   now = clock();
	while (clock() - now   <   time);
}
//2.打点函数
void Print_dot(int n) {
	for (int i = 0; i < n; i++) { printf("."); Delay(0.5 * 1000); }
}
//3.清空缓存区(主要是清除'\n'和' ')
void Flush_buffer() {
	char ch;
	while ((ch = getchar()) != EOF && ch != '\n'&&ch!=' ');
}
//4.链表结点初始化
void Node_init(Node *t) {
	t->next = NULL;
	Shopping_info_init(&(t->si));
}
//5.会员卡号生成函数
int Get_card_number() {
	int id;
	srand((unsigned int)time(NULL));
	id = rand();
	while (id>=10000||id<=0) {
		id = rand() % 10000;
	}
	return id;
}
//6.输入一个整数
int Input_int() {
	int a;
	while (scanf_s("%d", &a) == 0) {
		Flush_buffer();
		printf("请输入一个实数:");
	}
	Flush_buffer();
	return a;
}
//7.输入一个浮点数
float Input_float() {
	float f;
	while (scanf_s("%f", &f) == 0) {
		Flush_buffer();
		printf("请输入一个实数:");
	}
	Flush_buffer();
	return f;
}
