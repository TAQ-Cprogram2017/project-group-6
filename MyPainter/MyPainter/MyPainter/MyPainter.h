#ifndef _MYPAINTER_
#define _MYPAINTER_

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

static double t[MAX];//define an array of double type to store the result of calculation

typedef struct SNode_Num Operate_Num;//establish an Operate_Num stack
typedef Operate_Num *pOperate_Num;

typedef struct SNode_Symbol Operate_Symbol;//establish an Operate_Symbol stack
typedef Operate_Symbol *pOperate_Symbol;

void InitOperateNum(pOperate_Num Stack_Num);//initialize the Operate_Num stack

void InitOperateSymbol(pOperate_Symbol Stack_Symbol);//initialize the Operate_Symbol stack

void PushOperateNum(pOperate_Num Stack_Num, double x);//push a number into the Operate_Num stack

void PushOperateSymbol(pOperate_Symbol Stack_Symbol, char ch);//push a symbol into the Operate_Symbol stack

double PopOperateNum(pOperate_Num Stack_Num);//pop a number from the Operate_Num stack

char PopOperateSymbol(pOperate_Symbol Stack_Symbol);//pop a symbol from the Operate_Symbol stack

double GetOperateNum(pOperate_Num Stack_Num);//get the datas of the top of the Operate_Num stack

char GetOperateSymbol(pOperate_Symbol Stack_Symbol);//get the symbol of the top of the Operate_Symbol stack

short IsOperateSymbolOrNum(char ch);//judge whether ch is a number or symbol

char Priority(char stack_top_symbol, char ch);//judge the priority of the operation symbol

char TurnFunctionName(int i, char s[]);//turn function name into a form that can be handled easily

int ChangeStep(int i, char s[]);//change the step of traversing whil eturning function name into a form 
								//that can be handled easily
double Calculate_Binary(double num1, char ch, double num2);//binary calculation

double Calculate_Unary(double num1, char ch);//unary calculation

void MainCal_Rectangular();//the main calculation under the rectangular coordinate system

void MainCal_Polar();//the main calculation under the polar coordinate system

void Set_Rectangular_Coordinate_System();//set up rectangular coordinate system

void Set_Polar_Coordinate_System();//set up polar coordinate system

void DrawFunction_Under_RectangularCoordinateSystem();//draw the graph of function under rectangular coordinate system

void DrawFunction_Under_PolarCoordinateSystem();//draw the graph of function under polar coordinate system

void Instructions();//print the instructions on the screen

void Choose_Coordinate_System();//choose the coordinate system

#endif


