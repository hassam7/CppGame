#include "stdafx.h"
#include <iostream>
#include <conio.h> //includes getch and goto functions//
#define _WIN32_WINNT 0x0500
#include <windows.h> //includes colour functions//
#include<iomanip>
#include<ctime>
using namespace std;
int x=0,y=0,score=0;
int number=0;
bool flag=false;
void startGame();
void gotoxy(int x, int y) 
{
	HANDLE console_handle; //gotoxy function header//
	COORD cursor_coord;
	cursor_coord.X=x;
	cursor_coord.Y=y;
	console_handle=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(console_handle,cursor_coord);
}
void setcolor() //sets area of the colour for the upper half of the game screen//
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute( hOut,BACKGROUND_RED );
	for(int a=1;a<=16 ;a++)
	{
		for(int b=1;b<=77;b++)
		{
			gotoxy(b,a);
			cout<<' ';
		}
		cout<<endl;
	}

}
void setcolor1() //sets area to colour the area where the robot moves//
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute( hOut,BACKGROUND_GREEN | BACKGROUND_BLUE );
	for(int c=17;c<=21;c++)
	{
		for(int d=1;d<=77;d++)
		{
			gotoxy(d,c);
			cout<<' ';
		}
		cout<<endl;
	}

}
void setcolor2() //makes and colours the pathway where the robot moves and colours the robot//
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute( hOut, BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY );
	for(int e=22;e<=22;e++)
	{
		for(int f=1;f<=77;f++)
		{
			gotoxy(f,e);
			cout<<char(176);
		}
		cout<<endl;
	}
}
char mygrid[24][79];
void grid()
{
	//grid structure//
	for(int g=0;g<=23;g++)
	{
		for(int h=0;h<=78;h++)
		{
			if(g==0||g==23)
				mygrid[g][h] = 219;

			else if(h==0||h==78)
				mygrid[g][h] = 219;

			else
				mygrid[g][h] = ' ';
		}

	}

}
void printgrid() //declaring idebtifier for printing grid//
{
	for(int i=0;i<24;i++)
	{
		for(int j=0;j<79;j++)
		{
			cout<<mygrid[i][j];
		}
		cout<<endl;
	}
}
void printitem(int &item_x,int &item_y)
{

	if(flag==false)
	{

		item_x=rand()%77+1;
		number=rand()%7;
		item_y=1;
		gotoxy(item_x,item_y);
		cout<<number;
		flag=true;
		Sleep(100);
	}
	else if((item_x>(x+36) && item_x<(x+36+7))&& (item_y>=(y+17)))
	{
		flag=false;
		if(number!=0)
			score+=number;
		else if(number==0)
			score=0;
	}
	else{
		item_y++;
		gotoxy(item_x,item_y);
		cout<<number;
		if(item_y>=22){
			flag=false;
		}

	}

}
void printscreen(char array[5][6])
{

	for(int i=0;i<5;i++)
	{	
		for(int j=0;j<6;j++)
		{ 
			gotoxy(x+j+36,y+i+17); //added values in x and y to place robot above the lower line of grid// 
			cout<<array[i][j]; //printing robot on the output screen//
		}
	}

}
void printStartUpScreen()
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	for(int z=0;z<26;z++)
	{
		for(int i=0;i<86;i++)
			{
				if(i<28)
				{
					SetConsoleTextAttribute(hOut,BACKGROUND_RED);
					cout <<' ';
				}
				else if(i<56)
				{
					SetConsoleTextAttribute(hOut,BACKGROUND_BLUE);
					cout <<' ';
				}
				else if (i>56 && i<86)
				{
					SetConsoleTextAttribute(hOut,0x0020);
					cout <<' ';
				}
			}
		

		cout << endl;
	}
}
void startUp()
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute( hOut,BACKGROUND_RED );
	HWND console = GetConsoleWindow();
	//SetConsoleTextAttribute(hOut,BACKGROUND_GREEN | FOREGROUND_RED);
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	//MoveWindow(window_handle, x, y, width, height, redraw_window);
	MoveWindow(console, r.left, r.top, 900, 600, TRUE);
	printStartUpScreen();
	//SetConsoleTextAttribute(hOut,FOREGROUND_GREEN);
	char ch;
	int y=10;
		gotoxy(36,y);
		cout << "Start Game\n";
		gotoxy(36,y+1);
		cout << "Help\n";
		gotoxy(36,y+2);
		cout << "About\n";
		gotoxy(36,y+3);
		cout << "Exit";
		gotoxy(36,y);
	do
	{
		ch=getch();
		if(ch == 'w')
		{
			y--;
			if(y<10)
			{
				y=13;
			}
			gotoxy(36,y);
		}
		else if(ch=='s')
		{
			
			y++;
			if(y>13)
			{
				y=10;
			}
			gotoxy(36,y);
		}
		else if(ch == '\r')
		{
			if(y==10)
			{
				cout << "Starting Game";
				startGame();

			}
			else if (y==11)
			{
				system("cls");
				system("color 07");
				printStartUpScreen();
				
				gotoxy(36,10);
				cout << "Type Your Help Message Here";
				getch();
				system("cls");
				system("color 07");
				startUp();
				
			}
			else if(y==12)
			{
				system("cls");
				system("color 07");
				printStartUpScreen();
				gotoxy(36,10);
				cout << "Type Your About Message Here";
				getch();
				system("cls");
				system("color 07");
				startUp();
				
			}
			else if(y==13)
			{
				exit(0);
			}
		}
	}
	while(true);
	
}
void displayScore()
{
	
		system("cls");
		gotoxy(5,10);
		cout<<"Score "<<score<<endl;
		cout << "Exiting..."<<endl;

		system("pause");
}
void startGame()
{
		system("color 70"); //Background colour of first screen and colour of the grid//


	gotoxy(0,10);
	//Instructions//
	srand(time(NULL));
	cout<<"Welcome to the moving robot game... "<<endl;
	cout<<"Press 'a' Or left arrow key to move left and right arrow key or 'd' to move right."<<endl;
	cout<<"Press any key to start the game."<<endl;
	cout<<"Press esc to exit."<<endl;
	
	
	
	system("cls"); //clears screen befor moving on//

	grid(); //Prints grid//
	printgrid();


	int item_x,item_y; 

	int movement;	



	char array[5][6]={ //robot structure using 2d array//


		{0,92,196,194,196,47},
		{0,0,0,179,001},
		{0,0,0,192,186,170},
		{0,0,0,218,208,191},
		{0,0,0,217,0,192}};
		double diff=0;
		int secs=180;
		time_t start;
		time(&start);
		time_t end;



		do { //perform the following steps until condition in while fulfills//


			printitem(item_x,item_y);
			printscreen(array);

			setcolor();
			setcolor1();	
			setcolor2();

			if(kbhit())
			{

				movement=getch(); //iniatalizing keys for movement//
				if(movement==77 || movement=='d') //keys used for right movement//
				{
					if(x!=35) //check so that robot doesnot gets away from the grid//
						x++; //for continuous movement//

				}

				else if(movement==75 || movement=='a') //keys used for left movement//
				{

					if(x!=-35) //check so that robot doesnot gets away from the grid//

						x--; 
					//for continuous movement//
				}

			}
			gotoxy(68,0);
			cout<<"score: "<<setw(3)<<score;
			time(&end);
			gotoxy(0,23);
			cout<<"Time Left(secs): "<<setw(3);
			cout<<secs-diff<<endl;
			diff=difftime(end,start);
			if(diff>secs)
			{
				cout<<"Time Up"<<endl;
				getch();
				break;
			}
			if(movement == 27)
			{
				displayScore();
				exit(0);
			}

		}
		


		while(movement!=27); //press esc to exit//



}
void main()
{
	SetConsoleTitle(L"Eggs");
	startUp();
	getch();


}