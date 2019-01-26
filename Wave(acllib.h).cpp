#include"acllib.h"
#include<stdio.h>
#include<math.h>

//----------------------------------宏定义----------------------------
#define WIN_LENGTH 1520
#define WIN_HEIGHT 800
#define PI 3.14159
#define XO	50//坐标开始
#define X_X (WIN_HEIGHT/4)//三个x轴间距

//------------------------------函数原型声明--------------------------
void TimeListener(int id);
void MouseListener(int x, int y, int button, int event);
void KBListener(int key, int event);
void screen();

//------------------------------自定义变量类型------------------------
typedef struct
{
	double y;
	double a;
	double w;
	double v;
	double w1;
}COEF;

//-------------------------------全局变量定义--------------------------
COEF F1 = { 0, 100, 6 * PI / 1000 ,1,0 }, F2 = { 0,100,6 * PI / 1000,1,0 };
//		y1=a1*cos(w1*(t-x/v1)+f)+w11		y2=a2*cos(w2*(t+x/v2)+f)+w22

int PanSpeed = 10;//速度
double time = 0, x, f = 0;//时间变量、x坐标变量、初相位
int ox1, oy1, ox2, oy2, ox3, oy3;//辅助画线变量

//---------------------------------主函数-------------------------------
int Setup()
{
	initWindow("Synthesis of waves", 0, 0, WIN_LENGTH, WIN_HEIGHT);
	//initConsole();
	screen();

	startTimer(0, 100);//运行时尝试通过交互改变计时器时差   没用
	registerTimerEvent(TimeListener);
	registerMouseEvent(MouseListener);
	registerKeyboardEvent(KBListener);

	return 0;
}


//----------------------------自定义函数-----------------------------
void screen()
{
	beginPaint();
	clearDevice();

	//y1
	setPenColor(RED);
	line(XO, X_X, WIN_LENGTH, X_X);
	line(XO, XO, XO, X_X + XO);
	line(XO, XO, XO - 10, XO + 10);
	line(XO, XO, XO + 10, XO + 10);
	line(WIN_LENGTH, X_X, WIN_LENGTH - 10, X_X - 10);
	line(WIN_LENGTH, X_X, WIN_LENGTH - 10, X_X + 10);

	//y2
	setPenColor(GREEN);
	line(XO, X_X * 2, WIN_LENGTH, X_X * 2);
	line(XO, X_X + XO + 10, XO, X_X * 2 + XO + 10);
	line(XO, X_X + XO + 10, XO - 10, X_X + XO + 20);
	line(XO, X_X + XO + 10, XO + 10, X_X + XO + 20);
	line(WIN_LENGTH, X_X * 2, WIN_LENGTH - 10, X_X * 2 - 10);
	line(WIN_LENGTH, X_X * 2, WIN_LENGTH - 10, X_X * 2 + 10);

	//y3
	setPenColor(BLUE);
	line(XO, X_X * 3, WIN_LENGTH, X_X * 3);
	line(XO, X_X * 2 + XO + 20, XO, WIN_HEIGHT);
	line(XO, X_X * 2 + XO + 20, XO - 10, X_X * 2 + XO + 30);
	line(XO, X_X * 2 + XO + 20, XO + 10, X_X * 2 + XO + 30);
	line(WIN_LENGTH, X_X * 3, WIN_LENGTH - 10, X_X * 3 - 10);
	line(WIN_LENGTH, X_X * 3, WIN_LENGTH - 10, X_X * 3 + 10);

	endPaint();
}

void MouseListener(int x,int y,int button,int event)
{
	static int ox = 0, oy = 0;
	//printf("x=%d\ty=%d\tbutton=%d\tevent=%d\t\n", x, y, button, event);
	if (button == 2 && event == 3)
	{
		speed += 2;
	}
	else if (button == 2 && event == 4)
	{
		speed -= 2;
	}
}

void KBListener(int key,int event)
{
	if(event==0)
	switch (key)
	{
		//变频
	case 68:
		F1.w = F1.w + 0.001;
		break;
	case 65:
		F1.w = F1.w - 0.001;
		break;
	case 39:
		F2.w = F2.w + 0.001;
		break;
	case 37:
		F2.w = F2.w - 0.001;
		break;
		//变幅
	case 87:
		F1.a = F1.a + 10;
		break;
	case 83:
		F1.a = F1.a - 10;
		break;
	case 38:
		F2.a = F2.a + 10;
		break;
	case 40:
		F2.a = F2.a - 10;
		break;
	}
	//printf("key=%d\tevent=%d\n", key,event);
}

void TimeListener(int id)
{
	
	//if(key==....)
	//	if(id==...)
	//	do .....

	//	不能改变速度
		

	//change time    speed
			//if (id == 0)
			{
				screen();
				beginPaint();

				setTextSize(20);
				setTextColor(RED);
				paintText(100, 15, "f1变频:d↑、a↓");
				paintText(30, X_X - 10, "0");
				paintText(15, XO + 10, "y1");
				paintText(WIN_LENGTH - 40, X_X + 5, "x1");

				setTextColor(GREEN);
				paintText(400, 15, "f2变频:右↑、左↓");
				paintText(30, X_X * 2 - 10, "0");
				paintText(15, X_X + XO + 20, "y2");
				paintText(WIN_LENGTH - 40, X_X * 2 + 5, "x2");

				setTextColor(BLUE);
				paintText(700, 15, "鼠标滚轮变速");
				paintText(30, X_X * 3 - 10, "0");
				paintText(10, X_X * 2 + XO + 30, "y合");
				paintText(WIN_LENGTH - 40, X_X * 3 + 5, "X");

				setTextColor(RED);
				paintText(1000, 15, "f1变幅:w↑、s↓");
				setTextColor(GREEN);
				paintText(1300, 15, "f2变幅:上↑、下↓");

				ox1 = ox2 = ox3 = XO;
				oy1 = F1.a*cos(F1.w*time + f) + F1.w1 + X_X;
				oy2 = F2.a*cos(F2.w*time + f) + F2.w1 + (X_X * 2);
				oy3 = oy1 + oy2;

				for (x=0; x<WIN_LENGTH - XO; )
				{
					setPenColor(RED);
					F1.y = F1.a*cos(F1.w*(time - x / F1.v) + f) + F1.w1 + X_X;
					line(ox1, oy1, int(x + XO), int(F1.y));
					ox1 = int(x + XO);
					oy1 = int(F1.y);
					
					setPenColor(GREEN);
					F2.y = F2.a*cos(F2.w*(time + x / F2.v) + f) + F2.w1 + (X_X * 2);
					line(ox2, oy2, int(x + XO), int(F2.y));
					ox2 = int(x + XO);
					oy2 = int(F2.y);

					setPenColor(BLUE);
					line(ox3, oy3, int(x + XO), int(F1.y + F2.y));
					ox3 = int(x + XO);
					oy3 = int(F1.y + F2.y);
					x++;
				}
				endPaint();
				time += speed;
			}
}