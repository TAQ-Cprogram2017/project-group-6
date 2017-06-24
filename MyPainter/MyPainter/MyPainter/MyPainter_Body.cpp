# include <math.h>
# include <stdio.h>
# include <graphics.h>
# include <conio.h>
#include<easyx.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<iostream>   
#define MAX 16050
#define Pi 3.1415926535
#define NUMBER 0
#define SYMBOL 1
using   namespace   std;

/*define an array of double type to store the result of calculation*/
static double t[MAX];

/*Establish an Operate_Num stack with Operata_Num message name*/
typedef struct SNode_Num
{
	double datas[MAX];/*Operata_Num's member datas, to store a number*/
	int top;/*Operata_Num's member top, to record the top of the Operate_Num stack*/
}Operate_Num;
typedef Operate_Num *pOperate_Num;/*define a pointer of Operate_Num type*/

								  /*Establish an Operate_Symbol with Operata_Symbol message name*/
typedef struct SNode_Symbol
{
	char symbol[MAX];/*Operata_Symbol's member symbol, to store a Symbol*/
	int top;/*Operata_Symbol's member top, to record the top of the Operate_Symbol stack*/
}Operate_Symbol;
typedef Operate_Symbol *pOperate_Symbol;/*define a pointer of Operate_Symbol type*/


										/*************************************************
										Function: InitOperateNum
										Description: initialize the Operate_Num stack
										Calls:
										Called By: MainCal_Rectangular, MainCal_Polar
										Input: Stack_Num
										Output:
										Return: void type
										*************************************************/
void InitOperateNum(pOperate_Num Stack_Num)
{
	Stack_Num->top = -1;
}

/*************************************************
Function: InitOperateSymbol
Description: initialize the Operate_Symbol stack
Calls:
Called By: MainCal_Rectangular, MainCal_Polar
Input: Stack_Symbol
Output:
Return: void type
*************************************************/
void InitOperateSymbol(pOperate_Symbol Stack_Symbol)
{
	Stack_Symbol->top = -1;
}

/*************************************************
Function: PushOperateNum
Description: push a number into the Operate_Num stack
Calls:
Called By: MainCal_Rectangular, MainCal_Polar
Input: Stack_Num,x
Output:
Return: void type
*************************************************/
void PushOperateNum(pOperate_Num Stack_Num, double x)
{
	Stack_Num->top++;
	Stack_Num->datas[Stack_Num->top] = x;
}

/*************************************************
Function: PushOperateSymbol
Description: push a symbol into the Operate_System stack
Calls:
Called By: MainCal_Rectangular, MainCal_Polar
Input: Stack_Symbol,ch
Output:
Return: void type
*************************************************/
void PushOperateSymbol(pOperate_Symbol Stack_Symbol, char ch)
{
	Stack_Symbol->top++;
	Stack_Symbol->symbol[Stack_Symbol->top] = ch;
}

/*************************************************
Function: PopOperateNum
Description: pop a number from the Operate_Num stack
Calls:
Called By: MainCal_Rectangular, MainCal_Polar
Input: Stack_Num
Output: num
Return: double type
*************************************************/
double PopOperateNum(pOperate_Num Stack_Num)
{
	double num;
	num = Stack_Num->datas[Stack_Num->top];
	Stack_Num->top--;
	return num;
}

/*************************************************
Function: PopOperateSymbol
Description: pop a symbol from the Operate_Symbol stack
Calls:
Called By: MainCal_Rectangular, MainCal_Polar
Input: Stack_Symbol
Output: ch
Return: char type
*************************************************/
char PopOperateSymbol(pOperate_Symbol Stack_Symbol)
{
	char ch;
	ch = Stack_Symbol->symbol[Stack_Symbol->top];
	Stack_Symbol->top--;
	return ch;
}

/*************************************************
Function: GetOperateNum
Description: get the datas of the top of the Operate_Num stack
Calls:
Called By: MainCal_Rectangular, MainCal_Polar
Input: Stack_Num
Output: Stack_Num->datas[Stack_Num->top]
Return: double type
*************************************************/
double GetOperateNum(pOperate_Num Stack_Num)
{
	return Stack_Num->datas[Stack_Num->top];
}

/*************************************************
Function: GetOperateSymbol
Description: get the symbol of the top of the Operate_Symbol stack
Calls:
Called By: MainCal_Rectangular, MainCal_Polar
Input: Stack_Symbol
Output: Stack_Symbol->symbol[Stack_Symbol->top]
Return: char type
*************************************************/
char GetOperateSymbol(pOperate_Symbol Stack_Symbol)
{
	return Stack_Symbol->symbol[Stack_Symbol->top];
}

/*************************************************
Function: IsOperateSymbolOrNum
Description: judge whether ch is a number or symbol
Calls:
Called By: MainCal_Rectangular, MainCal_Polar
Input: ch
Output: SYMBOL(1) Or NUMBER(0)
Return: short type
*************************************************/
short IsOperateSymbolOrNum(char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '(' || ch == ')' || ch == '\0'
		|| ch == 'a' || ch == 'b' || ch == 'c' || ch == 'd' || ch == 'e' || ch == 'f' || ch == 'g'
		|| ch == 'h' || ch == 'i' || ch == 'j' || ch == 'k' || ch == 'l' || ch == 'm' || ch == 'n' || ch == 'o')
		return SYMBOL;
	else
		return NUMBER;
}

/*************************************************
Function: Priority
Description: judge the priority of the operation symbol
Calls:
Called By: MainCal_Rectangular, MainCal_Polar
Input: stack_top_symbol(the top symbol of the Operate_Symbol stack), ch(the traversing operation symbol)
Output: >, <, =
Return: char type
*************************************************/
char Priority(char stack_top_symbol, char ch)
{
	/*judge the priority between stack_top_symbol and ch*/
	switch (stack_top_symbol)
	{
		/*'+' and '-' are at the same proirity*/
	case '+':
	case '-':
	{
		if (ch == '+' || ch == '-')
			return '>';
		else if (ch == '*' || ch == '/')
			return '<';
		else if (ch == '^')
			return '<';
		else if (ch == 'a' || ch == 'b' || ch == 'c' || ch == 'd' || ch == 'e' || ch == 'f' || ch == 'g'
			|| ch == 'h' || ch == 'i' || ch == 'j' || ch == 'k' || ch == 'l' || ch == 'm' || ch == 'n' || ch == 'o')
			return'<';
		else if (ch == '(')
			return '<';
		else if (ch == ')')
			return '>';
		else
			return '>';
	}
	break;

	/*'*' and '/' are at the same proirity*/
	case '*':
	case '/':
	{
		if (ch == '+' || ch == '-')
			return '>';
		else if (ch == '*' || ch == '/')
			return '>';
		else if (ch == '^')
			return '<';
		else if (ch == 'a' || ch == 'b' || ch == 'c' || ch == 'd' || ch == 'e' || ch == 'f' || ch == 'g'
			|| ch == 'h' || ch == 'i' || ch == 'j' || ch == 'k' || ch == 'l' || ch == 'm' || ch == 'n' || ch == 'o')
			return'<';
		else if (ch == '(')
			return '<';
		else if (ch == ')')
			return '>';
		else
			return '>';
	}
	break;

	case'^':
	{
		if (ch == '+' || ch == '-')
			return '>';
		else if (ch == '*' || ch == '/')
			return '>';
		else if (ch == '^')
			return '>';
		else if (ch == 'a' || ch == 'b' || ch == 'c' || ch == 'd' || ch == 'e' || ch == 'f' || ch == 'g'
			|| ch == 'h' || ch == 'i' || ch == 'j' || ch == 'k' || ch == 'l' || ch == 'm' || ch == 'n' || ch == 'o')
			return'>';
		else if (ch == '(')
			return '<';
		else if (ch == ')')
			return '>';
		else
			return '>';
	}
	break;

	/*All the functin names are at the same proirity*/
	case'a':
	case'b':
	case'c':
	case'd':
	case'e':
	case'f':
	case'g':
	case'h':
	case'i':
	case'j':
	case'k':
	case'l':
	case'm':
	case'n':
	case'o':
	{
		if (ch == '+' || ch == '-')
			return '>';
		else if (ch == '*' || ch == '/')
			return '>';
		else if (ch == '^')
			return '<';
		else if (ch == 'a' || ch == 'b' || ch == 'c' || ch == 'd' || ch == 'e' || ch == 'f' || ch == 'g'
			|| ch == 'h' || ch == 'i' || ch == 'j' || ch == 'k' || ch == 'l' || ch == 'm' || ch == 'n' || ch == 'o')
			return '>';
		else if (ch == '(')
			return '<';
		else if (ch == ')')
			return '>';
		else
			return '>';
	}
	break;

	case '(':
	{
		if (ch == ')')
			return '=';
		else
			return '<';
	}
	break;

	case ')':
	{
		return '>';
	}
	break;

	case '\0':
	{
		if (ch == '\0')
			return '=';
		else
			return '<';
	}
	break;

	}
}

/*************************************************
Function: TurnFunctionName
Description: turn function name into a form that can be handled easily
Calls:
Called By: MainCal_Rectangular, MainCal_Polar
Input: i(the step of traversing),s[](an array to store the math expression inputted)
Output: ch
Return: char type
*************************************************/
char TurnFunctionName(int i, char s[])
{
	char ch;
	if ((s[i] == 's') && (s[i + 1] == 'i') && (s[i + 2] == 'n'))
	{
		ch = 'a';
		return ch;
	}
	else if ((s[i] == 'c') && (s[i + 1] == 'o') && (s[i + 2] == 's'))
	{
		ch = 'b';
		return ch;
	}
	else if ((s[i] == 't') && (s[i + 1] == 'a') && (s[i + 2] == 'n'))
	{
		ch = 'c';
		return ch;
	}
	else if ((s[i] == 'c') && (s[i + 1] == 'o') && (s[i + 2] == 't'))
	{
		ch = 'd';
		return ch;
	}
	else if ((s[i] == 'e') && (s[i + 1] == 'x') && (s[i + 2] == 'p'))
	{
		ch = 'e';
		return ch;
	}
	else if ((s[i] == 'f') && (s[i + 1] == 'a') && (s[i + 2] == 'b') && (s[i + 3] == 's'))
	{
		ch = 'f';
		return ch;
	}
	else if ((s[i] == 'l') && (s[i + 1] == 'g'))
	{
		ch = 'g';
		return ch;
	}
	else if ((s[i] == 'a') && (s[i + 1] == 'r') && (s[i + 2] == 'c') && (s[i + 3] == 's') && (s[i + 4] == 'i') && (s[i + 5] == 'n'))
	{
		ch = 'h';
		return ch;
	}
	else if ((s[i] == 'a') && (s[i + 1] == 'r') && (s[i + 2] == 'c') && (s[i + 3] == 'c') && (s[i + 4] == 'o') && (s[i + 5] == 's'))
	{
		ch = 'i';
		return ch;
	}
	else if ((s[i] == 'a') && (s[i + 1] == 'r') && (s[i + 2] == 'c') && (s[i + 3] == 't') && (s[i + 4] == 'a') && (s[i + 5] == 'n'))
	{
		ch = 'j';
		return ch;
	}
	else if ((s[i] == 's') && (s[i + 1] == 'h'))
	{
		ch = 'k';
		return ch;
	}
	else if ((s[i] == 'c') && (s[i + 1] == 'h'))
	{
		ch = 'l';
		return ch;
	}
	else if ((s[i] == 't') && (s[i + 1] == 'h'))
	{
		ch = 'm';
		return ch;
	}
	else if ((s[i] == 'l') && (s[i + 1] == 'n'))
	{
		ch = 'n';
		return ch;
	}
	else if ((s[i] == 'f') && (s[i + 1] == 'l') && (s[i + 2] == 'o') && (s[i + 3] == 'o') && (s[i + 4] == 'r'))
	{
		ch = 'o';
		return ch;
	}
	else if ((s[i] == 'P') && (s[i + 1] == 'i'))
	{
		ch = 'p';
		return ch;
	}
	else
		return s[i];
}

/*************************************************
Function: ChangeStep
Description: change the step of traversing whil eturning function name into a form that can be handled easily
Calls:
Called By: MainCal_Rectangular, MainCal_Polar
Input: i(the step of traversing),s[](an array to store the math expression inputted)
Output: i
Return: int type
*************************************************/
int ChangeStep(int i, char s[])
{
	if ((s[i] == 's') && (s[i + 1] == 'i') && (s[i + 2] == 'n'))
	{
		i += 3;
		return i;
	}
	else if ((s[i] == 'c') && (s[i + 1] == 'o') && (s[i + 2] == 's'))
	{
		i += 3;
		return i;
	}
	else if ((s[i] == 't') && (s[i + 1] == 'a') && (s[i + 2] == 'n'))
	{
		i += 3;
		return i;
	}
	else if ((s[i] == 'c') && (s[i + 1] == 'o') && (s[i + 2] == 't'))
	{
		i += 3;
		return i;
	}
	else if ((s[i] == 'e') && (s[i + 1] == 'x') && (s[i + 2] == 'p'))
	{
		i += 3;
		return i;
	}
	else if ((s[i] == 'f') && (s[i + 1] == 'a') && (s[i + 2] == 'b') && (s[i + 3] == 's'))
	{
		i += 4;
		return i;
	}
	else if ((s[i] == 'l') && (s[i + 1] == 'g'))
	{
		i += 2;
		return i;
	}
	else if ((s[i] == 'a') && (s[i + 1] == 'r') && (s[i + 2] == 'c') && (s[i + 3] == 's') && (s[i + 4] == 'i') && (s[i + 5] == 'n'))
	{
		i += 6;
		return i;
	}
	else if ((s[i] == 'a') && (s[i + 1] == 'r') && (s[i + 2] == 'c') && (s[i + 3] == 'c') && (s[i + 4] == 'o') && (s[i + 5] == 's'))
	{
		i += 6;
		return i;
	}
	else if ((s[i] == 'a') && (s[i + 1] == 'r') && (s[i + 2] == 'c') && (s[i + 3] == 't') && (s[i + 4] == 'a') && (s[i + 5] == 'n'))
	{
		i += 6;
		return i;
	}
	else if ((s[i] == 's') && (s[i + 1] == 'h'))
	{
		i += 2;
		return i;
	}
	else if ((s[i] == 'c') && (s[i + 1] == 'h'))
	{
		i += 2;
		return i;
	}
	else if ((s[i] == 't') && (s[i + 1] == 'h'))
	{
		i += 2;
		return i;
	}
	else if ((s[i] == 'l') && (s[i + 1] == 'n'))
	{
		i += 2;
		return i;
	}
	else if ((s[i] == 'f') && (s[i + 1] == 'l') && (s[i + 2] == 'o') && (s[i + 3] == 'o') && (s[i + 4] == 'r'))
	{
		i += 5;
		return i;
	}
	else if ((s[i] == 'P') && (s[i + 1] == 'i'))
	{
		i += 2;
		return i;
	}
	else
	{
		i += 1;
		return i;
	}
}

/*************************************************
Function: Calculate_Binary
Description: binary calculation
Calls:
Called By: MainCal_Rectangular, MainCal_Polar
Input: num1 ,ch, num2
Output: result
Return: double type
*************************************************/
double Calculate_Binary(double num1, char ch, double num2)
{
	double result;
	switch (ch)
	{
	case '+':
		result = num1 + num2;
		break;
	case '-':
		result = num1 - num2;
		break;
	case '*':
		result = num1 * num2;
		break;
	case '/':
		result = num1 / num2;
		break;
	case'^':
		result = pow(num1, num2);
		break;
	}
	return result;
}

/*************************************************
Function: Calculate_Unary
Description: unary calculation
Calls:
Called By: MainCal_Rectangular, MainCal_Polar
Input: num1 ,ch
Output: result
Return: double type
*************************************************/
double Calculate_Unary(double num1, char ch)
{
	double result;
	switch (ch)
	{
	case'a':
		result = sin(num1);
		break;
	case'b':
		result = cos(num1);
		break;
	case'c':
		result = tan(num1);
		break;
	case'd':
		result = 1 / (tan(num1));
		break;
	case'e':
		result = exp(num1);
		break;
	case'f':
		result = fabs(num1);
		break;
	case'g':
		result = log10(num1);
		break;
	case'h':
		result = asin(num1);
		break;
	case'i':
		result = acos(num1);
		break;
	case'j':
		result = atan(num1);
		break;
	case'k':
		result = sinh(num1);
		break;
	case'l':
		result = cosh(num1);
		break;
	case'm':
		result = tanh(num1);
		break;
	case'n':
		result = log(num1);
		break;
	case'o':
		result = floor(num1);
		break;
	}
	return result;
}

/*************************************************
Function: Set_Rectangular_Coordinate_System
Description: set up rectangular coordinate system
Calls:
Called By: DrawFunction_Under_RectangularCoordinateSystem
Input:
Output:
Return: void type
*************************************************/
void Set_Rectangular_Coordinate_System()
{
	/*initialize graphics mode*/
	int gd = DETECT, gm;
	initgraph(&gd, &gm, "");
	cleardevice();

	/*determine the color of text and background*/
	setbkcolor(BLACK);
	setcolor(WHITE);

	/*draw x-axis, y-axis; label x-axis, y-axis and origin '0'*/
	line(0, 240, 640, 240); line(320, 0, 320, 480);
	outtextxy(630, 245, _T("x")); outtextxy(626, 233, _T("¡ú"));
	outtextxy(330, 0, _T("y")); outtextxy(313, 0, _T("¡ü"));
	outtextxy(325, 245, _T("0"));

	/*draw the coordinate grid*/
	int x, y;
	for (y = 0; y <= 480; y += 40)
	{
		for (x = 0; x <= 640; x += 4)
		{
			line(x, y, x + 2, y);
		}
	}
	for (x = 0; x <= 640; x += 40)
	{
		for (y = 0; y <= 480; y += 4)
		{
			line(x, y, x, y + 2);
		}
	}
}

/*************************************************
Function: Set_Polar_Coordinate_System
Description: set up polar coordinate system
Calls:
Called By: DrawFunction_Under_RectangularCoordinateSystem
Input:
Output:
Return: void type
*************************************************/
void Set_Polar_Coordinate_System()
{
	/*initialize graphics mode*/
	int gd = DETECT, gm;
	initgraph(&gd, &gm, "");
	cleardevice();

	/*determine the color of text and background*/
	setbkcolor(BLACK);
	setcolor(WHITE);

	/*label the value of r*/
	outtextxy(352, 208, _T("0.2")); outtextxy(384, 176, _T("0.4"));
	outtextxy(416, 144, _T("0.6")); outtextxy(448, 112, _T("0.8")); outtextxy(480, 80, _T("1.0"));

	/*label the value of theta*/
	outtextxy(552, 232, _T("0")); outtextxy(518, 115, _T("30"));
	outtextxy(430, 30, _T("60")); outtextxy(315, 0, _T("90"));
	outtextxy(195, 25, _T("120")); outtextxy(105, 110, _T("150"));
	outtextxy(65, 232, _T("180")); outtextxy(105, 355, _T("210"));
	outtextxy(185, 435, _T("240")); outtextxy(310, 465, _T("270"));
	outtextxy(435, 435, _T("300")); outtextxy(520, 350, _T("330"));

	/*determine the style of line*/
	DWORD a[2] = { 4, 2 };
	setlinestyle(PS_SOLID, 2); circle(320, 240, 225);
	setlinestyle(PS_USERSTYLE | PS_ENDCAP_FLAT, 1, a, 2);

	/*draw the coordinate grid*/
	int x;
	for (x = 1; x <= 16; x += 1)
	{
		circle(320, 240, 45 * x);
	}
	line(0, 240, 640, 240); line(320, 0, 320, 480);
	line(320, 240, 458, 0); line(320, 240, 182, 480);
	line(320, 240, 640, 56); line(320, 240, 0, 424);
	line(320, 240, 182, 0); line(320, 240, 458, 480);
	line(320, 240, 0, 56); line(320, 240, 640, 424);

}

/*************************************************
Function: MainCal_Rectangular
Description: dispose the math expression  and calculate under the rectangular coordinate system
Calls:InitOperateNum,InitOperateSymbol,PushOperateNum,PushOperateSymbol,PopOperateNum,
PopOperateSymbol,GetOperateNum,GetOperateSymbol,IsOperateSymbolOrNum,Priority,
TurnFunctionName,ChangeStep,Calculate_Binary,Calculate_Unary
Called By: DrawFunction_Under_RectangularCoordinateSystem
Input:
Output:
Return: void type
*************************************************/
void MainCal_Rectangular()
{
	Operate_Num datas;//establish an Operation_Num stack
	Operate_Symbol symbol;//establish an Operation_Symbol stack
	InitOperateNum(&datas);//initialize the Operation_Num stack
	InitOperateSymbol(&symbol);//initialize the Operation_Symbol stack

	int i = 0, j = 0, k = 1;
	double num1, num2, result, num, x, u, x0 = -8;
	char ch, sign;
	char Math_Expression[MAX];

	/*guidance for users*/
	cout << "                                            " << endl;
	cout << "¡¤Please input the function you want to draw: " << endl;
	cout << "                                            " << endl;
	scanf("%s", Math_Expression);//input the math expression

								 /*evaluate a value to x, and then computer could get the result of calculation every circulation*/
	for (; x0 <= 8, j <= 16000; x0 += 0.001, j += 1)
	{
		PushOperateSymbol(&symbol, '\0');//push '\0' into the Operate_Symbol stack
		ch = TurnFunctionName(i, Math_Expression); i = ChangeStep(i, Math_Expression);//traverse
		while ((ch != '\0') || (GetOperateSymbol(&symbol) != '\0'))
		{
			if (!IsOperateSymbolOrNum(ch))//judge whether ch is a figure or not
			{
				if (ch == 'x')//turn 'x' into a figure to calculate
				{
					PushOperateNum(&datas, x0);
					ch = TurnFunctionName(i, Math_Expression); i = ChangeStep(i, Math_Expression);//traverse
					if (ch == 'x')//warning for error
					{
						cout << "Error:No operation between x and x!" << endl;
						exit(1);
					}
				}
				else if (ch == 'p')//recognize Pi and push it into Operate_Num stack
				{
					PushOperateNum(&datas, Pi);
					ch = TurnFunctionName(i, Math_Expression); i = ChangeStep(i, Math_Expression);//traverse
					if (ch == 'p')//warning for error
					{
						cout << "Error:Two Pi are adjoining!\n" << endl;
						exit(1);
					}
					if (ch == 'x')//warning for error
					{
						cout << "Error:No operation between x and Pi!" << endl;
						exit(1);
					}
				}
				else
				{
					num = atof(&ch);//turn char into figure
					ch = TurnFunctionName(i, Math_Expression); i = ChangeStep(i, Math_Expression);//traverse
					if (ch == '.')//handle '.'
					{
						ch = TurnFunctionName(i, Math_Expression); i = ChangeStep(i, Math_Expression);//traverse directly to skip '.'

																									  /*judge decimal digits:whether there exist other figures after'.' */
						for (k = 1; (!IsOperateSymbolOrNum(ch)) && (ch != 'x') && (ch != '.') && (ch != 'p'); k++)
						{
							u = pow(10, k);
							num = num + atof(&ch) / u;
							ch = TurnFunctionName(i, Math_Expression); i = ChangeStep(i, Math_Expression);//traverse
						}
						if ((ch == '.'))//warning for error
						{
							cout << "Error:Two '.' are adjoining!\n" << endl;
							exit(1);
						}
						if ((ch == 'p') || (ch == 'x'))//warning for error
						{
							cout << "Error: '.x' or '.p' is false format!\n" << endl;
							exit(1);
						}
						PushOperateNum(&datas, num);
					}
					//warning for error
					else if (ch == 'x' || ch == 'a' || ch == 'b' || ch == 'c' || ch == 'd' || ch == 'e' || ch == 'f' || ch == 'g'
						|| ch == 'h' || ch == 'i' || ch == 'j' || ch == 'k' || ch == 'l' || ch == 'm' || ch == 'n' || ch == 'o')
					{
						cout << "Error:No operation between figures and x(function name)!\n" << endl;
						exit(1);
					}
					else if (ch == 'p')//warning for error
					{
						cout << "Error:No operation between Pi and x!\n" << endl;
						exit(1);
					}
					else
					{
						while (!IsOperateSymbolOrNum(ch) && ch != 'x'&&ch != '.')//handle the integer part more than one digits 
						{
							num = num * 10 + atof(&ch);
							ch = TurnFunctionName(i, Math_Expression); i = ChangeStep(i, Math_Expression);//traverse
						}
						if (ch == '.')
						{
							ch = TurnFunctionName(i, Math_Expression); i = ChangeStep(i, Math_Expression);//traverse

																										  /*if meet '.' while traversing*/
							for (k = 1; (!IsOperateSymbolOrNum(ch)) && (ch != 'x') && (ch != '.') && (ch != 'p'); k++)
							{
								u = pow(10, k);
								num = num + atof(&ch) / u;
								ch = TurnFunctionName(i, Math_Expression); i = ChangeStep(i, Math_Expression);
							}
							if ((ch == '.'))//warning for error
							{
								cout << "Error:Two '.' are adjoining!\n" << endl;
								exit(1);
							}
							if ((ch == 'p') || (ch == 'x'))//warning for error
							{
								cout << "Error: '.x' or '.p' is false format!\n" << endl;
								exit(1);
							}
						}
						PushOperateNum(&datas, num);
					}
				}

			}
			else
			{
				switch (Priority(GetOperateSymbol(&symbol), ch))//judge the priority
				{
				case '<'://priority: symbol(the top symbol of the Operate_Symbol stack) < ch(the traversing operation symbol)
					PushOperateSymbol(&symbol, ch);
					ch = TurnFunctionName(i, Math_Expression); i = ChangeStep(i, Math_Expression);
					break;
				case '='://priority: symbol(the top symbol of the Operate_Symbol stack) = ch(the traversing operation symbol)
					sign = PopOperateSymbol(&symbol);
					ch = TurnFunctionName(i, Math_Expression); i = ChangeStep(i, Math_Expression);
					break;
				case '>'://priority: symbol(the top symbol of the Operate_Symbol stack) > ch(the traversing operation symbol)
					sign = PopOperateSymbol(&symbol);
					if (sign == '+' || sign == '-' || sign == '*' || sign == '/' || sign == '^')//binary calculation
					{
						num2 = PopOperateNum(&datas);
						num1 = PopOperateNum(&datas);
						result = Calculate_Binary(num1, sign, num2);
						PushOperateNum(&datas, result);
					}
					else if //unary calculation
						(sign == 'a' || sign == 'b' || sign == 'c' || sign == 'd' || sign == 'e' || sign == 'f' || sign == 'g'
							|| sign == 'h' || sign == 'i' || sign == 'j' || sign == 'k' || sign == 'l' || sign == 'm' || sign == 'n' || sign == 'o')
					{
						num1 = PopOperateNum(&datas);
						result = Calculate_Unary(num1, sign);
						PushOperateNum(&datas, result);
					}
					break;

				}
			}
		}
		result = GetOperateNum(&datas);
		t[j] = result;//store the result into array
		i = 0;//reset i and prepare for the next circulation
	}
}

/*************************************************
Function: MainCal_Polar
Description: dispose the math expression  and calculate under the polar coordinate system
Calls:InitOperateNum,InitOperateSymbol,PushOperateNum,PushOperateSymbol,PopOperateNum,
PopOperateSymbol,GetOperateNum,GetOperateSymbol,IsOperateSymbolOrNum,Priority,
TurnFunctionName,ChangeStep,Calculate_Binary,Calculate_Unary
Called By: DrawFunction_Under_RectangularCoordinateSystem
Output:
Return: void type
*************************************************/
void MainCal_Polar()
{
	Operate_Num datas;//establish an Operation_Num stack
	Operate_Symbol symbol;//establish an Operation_Symbol stack
	InitOperateNum(&datas);//initialize the Operation_Num stack
	InitOperateSymbol(&symbol);//initialize the Operation_Symbol stack

	int i = 0, j = 0, k = 1;
	double num1, num2, result, num, x, x0 = 0, u;
	char ch, sign;
	char Math_Expression[MAX];

	cout << "                                            " << endl;
	cout << "¡¤Please input the function you want to draw: " << endl;
	cout << "                                            " << endl;
	scanf("%s", Math_Expression);//input the math expression

								 /*evaluate a value to x, and then computer could get the result of calculation every circulation*/
	for (; x0 <= 360, j <= 360; x0 += 1, j += 1)
	{
		double theta = Pi*x0 / 180;//angular transformation
		PushOperateSymbol(&symbol, '\0');//push '\0' into the Operate_Symbol stack
		ch = TurnFunctionName(i, Math_Expression); i = ChangeStep(i, Math_Expression);//traverse
		while ((ch != '\0') || (GetOperateSymbol(&symbol) != '\0'))
		{
			if (!IsOperateSymbolOrNum(ch))//judge whether ch is a figure or not
			{
				if (ch == 'x')//turn 'x' into a figure to calculate
				{
					PushOperateNum(&datas, theta);
					ch = TurnFunctionName(i, Math_Expression); i = ChangeStep(i, Math_Expression);//traverse
					if (ch == 'x')//warning for error
					{
						cout << "Error:No operation between x and x!" << endl;
						exit(1);
					}
				}
				else if (ch == 'p')//recognize Pi and push it into Operate_Num stack
				{
					PushOperateNum(&datas, Pi);
					ch = TurnFunctionName(i, Math_Expression); i = ChangeStep(i, Math_Expression);//traverse
					if (ch == 'p')//warning for error
					{
						cout << "Error:Two Pi are adjoining!\n" << endl;
						exit(1);
					}
					if (ch == 'x')//warning for error
					{
						cout << "Error:No operation between x and Pi!" << endl;
						exit(1);
					}
				}
				else
				{
					num = atof(&ch);//turn char into figure
					ch = TurnFunctionName(i, Math_Expression); i = ChangeStep(i, Math_Expression);//traverse
					if (ch == '.')//handle '.'
					{
						ch = TurnFunctionName(i, Math_Expression); i = ChangeStep(i, Math_Expression);//traverse directly to skip '.'

																									  /*judge decimal digits:whether there exist other figures after'.' */
						for (k = 1; (!IsOperateSymbolOrNum(ch)) && (ch != 'x') && (ch != '.') && (ch != 'p'); k++)
						{
							u = pow(10, k);
							num = num + atof(&ch) / u;
							ch = TurnFunctionName(i, Math_Expression); i = ChangeStep(i, Math_Expression);//traverse
						}
						if ((ch == '.'))//warning for error
						{
							cout << "Error:Two '.' are adjoining!\n" << endl;
							exit(1);
						}
						if ((ch == 'p') || (ch == 'x'))//warning for error
						{
							cout << "Error: '.x' or '.p' is false format!\n" << endl;
							exit(1);
						}
						PushOperateNum(&datas, num);
					}
					//warning for error
					else if (ch == 'x' || ch == 'a' || ch == 'b' || ch == 'c' || ch == 'd' || ch == 'e' || ch == 'f' || ch == 'g'
						|| ch == 'h' || ch == 'i' || ch == 'j' || ch == 'k' || ch == 'l' || ch == 'm' || ch == 'n' || ch == 'o')
					{
						cout << "Error:No operation between figures and x(function name)!\n" << endl;
						exit(1);
					}
					else if (ch == 'p')//warning for error
					{
						cout << "Error:No operation between Pi and x!\n" << endl;
						exit(1);
					}
					else
					{
						while (!IsOperateSymbolOrNum(ch) && ch != 'x'&&ch != '.')//handle the integer part more than one digits 
						{
							num = num * 10 + atof(&ch);
							ch = TurnFunctionName(i, Math_Expression); i = ChangeStep(i, Math_Expression);//traverse
						}
						if (ch == '.')
						{
							ch = TurnFunctionName(i, Math_Expression); i = ChangeStep(i, Math_Expression);//traverse

																										  /*if meet '.' while traversing*/
							for (k = 1; (!IsOperateSymbolOrNum(ch)) && (ch != 'x') && (ch != '.') && (ch != 'p'); k++)
							{
								u = pow(10, k);
								num = num + atof(&ch) / u;
								ch = TurnFunctionName(i, Math_Expression); i = ChangeStep(i, Math_Expression);
							}
							if ((ch == '.'))//warning for error
							{
								cout << "Error:Two '.' are adjoining!\n" << endl;
								exit(1);
							}
							if ((ch == 'p') || (ch == 'x'))//warning for error
							{
								cout << "Error: '.x' or '.p' is false format!\n" << endl;
								exit(1);
							}
						}
						PushOperateNum(&datas, num);
					}
				}

			}
			else
			{
				switch (Priority(GetOperateSymbol(&symbol), ch))//judge the priority
				{
				case '<'://priority: symbol(the top symbol of the Operate_Symbol stack) < ch(the traversing operation symbol)
					PushOperateSymbol(&symbol, ch);
					ch = TurnFunctionName(i, Math_Expression); i = ChangeStep(i, Math_Expression);
					break;
				case '='://priority: symbol(the top symbol of the Operate_Symbol stack) = ch(the traversing operation symbol)
					sign = PopOperateSymbol(&symbol);
					ch = TurnFunctionName(i, Math_Expression); i = ChangeStep(i, Math_Expression);
					break;
				case '>'://priority: symbol(the top symbol of the Operate_Symbol stack) > ch(the traversing operation symbol)
					sign = PopOperateSymbol(&symbol);
					if (sign == '+' || sign == '-' || sign == '*' || sign == '/' || sign == '^')//binary calculation
					{
						num2 = PopOperateNum(&datas);
						num1 = PopOperateNum(&datas);
						result = Calculate_Binary(num1, sign, num2);
						PushOperateNum(&datas, result);
					}
					else if //unary calculation
						(sign == 'a' || sign == 'b' || sign == 'c' || sign == 'd' || sign == 'e' || sign == 'f' || sign == 'g'
							|| sign == 'h' || sign == 'i' || sign == 'j' || sign == 'k' || sign == 'l' || sign == 'm' || sign == 'n' || sign == 'o')
					{
						num1 = PopOperateNum(&datas);
						result = Calculate_Unary(num1, sign);
						PushOperateNum(&datas, result);
					}
					break;

				}
			}
		}
		result = GetOperateNum(&datas);
		t[j] = result;//store the result into array
		i = 0;//reset i and prepare for the next circulation
	}
}

/*************************************************
Function: DrawFunction_Under_RectangularCoordinateSystem
Description: draw the graph of function under rectangular coordinate system
Calls:MainCal_Rectangular,Set_Rectangular_Coordinate_System
Called By: Choose_Coordinate_System
Input:
Output:
Return: void type
*************************************************/
void DrawFunction_Under_RectangularCoordinateSystem()
{
	do
	{
		MainCal_Rectangular();//calculate

		Set_Rectangular_Coordinate_System();//set up coordinate system

											/*determine the color of text and background*/
		setcolor(YELLOW);
		setlinestyle(PS_SOLID, 2);

		int j = 0;
		double i = -8;
		double x0, y0, x1 = 0, y1 = 320, x2, y2;

		/*draw dot and ligature*/
		for (; i <= 8, j <= 16000; i += 0.001, j += 1)
		{
			x2 = x1;
			y2 = y1;
			x0 = i;
			y0 = t[j];
			x1 = 40 * x0 + 320;
			y1 = -40 * y0 + 240;
			line(x2, y2, x1, y1);
		}
		getch();
		closegraph();//close the graphincs mode
	} while (1);
}

/*************************************************
Function: DrawFunction_Under_PolarCoordinateSystem
Description: draw the graph of function under polar coordinate system
Calls:MainCal_Polar,Set_Polar_Coordinate_System
Called By: Choose_Coordinate_System
Input:
Output:
Return: void type
*************************************************/
void DrawFunction_Under_PolarCoordinateSystem()
{
	do
	{
		MainCal_Polar();//calculate

		Set_Polar_Coordinate_System();//set up coordinate system

									  /*determine the color of text and background*/
		setcolor(LIGHTRED);
		setlinestyle(PS_SOLID, 2);

		int i = 0, j = 0;
		double theta = Pi*i / 180;;
		double x0, y0, x1, y1, x2, y2;

		/*transformation of coordinates*/
		x2 = t[j] * cos(theta) * 225 + 320;
		y2 = t[j] * sin(theta) * (-225) + 240;

		/*draw dot and ligature*/
		for (j = 1, i = 1; i <= 360, j <= 360; i += 1, j += 1)
		{
			x1 = x2;
			y1 = y2;
			theta = Pi*i / 180;
			x2 = t[j] * cos(theta) * 225 + 320;
			y2 = t[j] * sin(theta) * (-225) + 240;
			line(x1, y1, x2, y2);
		}
		getch();
		closegraph();//close the graphincs mode
	} while (1);

}

/*************************************************
Function: Instructions
Description: print the instructions on the screen
Calls:
Called By: main
Input:
Output:
Return: void type
*************************************************/
void Instructions()
{
	system("color f3");
	cout << "                            ___________________________________________________________________" << endl;
	cout << "                            ¨‡                           MyPainter                            ¨‡" << endl;
	cout << "                            ¨‡----------------------------------------------------------------¨‡" << endl;
	cout << "                            ¨‡Instructions:                                                   ¨‡" << endl;
	cout << "                            ¨‡1.Two coordinate systems are provided:                          ¨‡" << endl;
	cout << "                            ¨‡    R)   rectangular coordinate system                          ¨‡" << endl;
	cout << "                            ¨‡    P)   polar coordinate system                                ¨‡" << endl;
	cout << "                            ¨‡2.Operation Supported:                                          ¨‡" << endl;
	cout << "                            ¨‡    +, -, *, /, ^                                               ¨‡" << endl;
	cout << "                            ¨‡3.Function supported:                                           ¨‡" << endl;
	cout << "                            ¨‡    1)x^a (a is arbitrary constant)                             ¨‡" << endl;
	cout << "                            ¨‡    2)sin x, cos x, tan x, cot x, arcsin x, arccos x,arctan x,  ¨‡" << endl;
	cout << "                            ¨‡      exp x,  fabs x, floor x, lg x, ln x, sh x, ch x, th x     ¨‡" << endl;
	cout << "                            ¨‡    3)constant function                                         ¨‡" << endl;
	cout << "                            ¨‡    4)composite function                                        ¨‡" << endl;
	cout << "                            ¨‡4.Const:                                                        ¨‡" << endl;
	cout << "                            ¨‡    Pi: 3.1415926535                                            ¨‡" << endl;
	cout << "                            ¨‡5.Support decimal input                                         ¨‡" << endl;
	cout << "                            ¨‡6.Announcements:                                                ¨‡" << endl;
	cout << "                            ¨‡  1)All the functions about theta use radian input.             ¨‡" << endl;
	cout << "                            ¨‡    Ex:If you want to use sin30¡ã,you should input sin(Pi/6)   ¨‡" << endl;
	cout << "                            ¨‡  2)Input format must be right and normative.                   ¨‡" << endl;
	cout << "                            ¨‡    Ex: 2sinx(¡Á)£¬ 2*sinx(¡Ì)                               ¨‡" << endl;
	cout << "                            ¨‡  3)No blank between function name and variable 'x'.            ¨‡" << endl;
	cout << "                            ¨‡    Ex: tan x(¡Á)£¬ tanx(¡Ì)                                 ¨‡" << endl;
	cout << "                            ¨‡----------------------------------------------------------------¨‡" << endl;
	cout << "                            ¨‡----------------------------------------------------------------¨‡" << endl;
	cout << "                            ¨‡________________________________________________________________¨‡" << endl;
}

/*************************************************
Function: Choose_Coordinate_System
Description: choose the coordinate system
Calls:
Called By: main
Input:
Output:
Return: void type
*************************************************/
void Choose_Coordinate_System()
{

	char choice;
	cout << "                                           " << endl;
	cout << "                                           " << endl;
	cout << "¡¤Please choose the painting system you want:" << endl;
	cout << "                                           " << endl;
	cout << "¡¤r(rectangular) Or p(polar) ?" << endl;
	scanf("%c", &choice);
	switch (choice)
	{
	case'r':
		DrawFunction_Under_RectangularCoordinateSystem();
	case'p':
		DrawFunction_Under_PolarCoordinateSystem();
	}
}