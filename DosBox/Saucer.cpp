#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<dos.h>
#include<math.h>
#include<graphics.h>
#include<iostream.h>
#include<time.h>
const int  MaxX = 639;
const int  MaxY = 479;
const int  MaxColors = 15;
const int Seconds = 180;
const int Falling = 10;
class SmileyFace
{
	friend class CollisionDetection;
	int x,y,r;//x-axis,y-axis,radius
	int steps;
	int min,max;
	void *bg;
	int array[1000][3];
	int firstRun;
	void initGraph()
	{
		/* request auto detection graphics driver*/
		int gdriver = DETECT, gmode, errorcode;
		/* initialize graphics mode */
		initgraph(&gdriver, &gmode, "..\\bgi");
		/* read result of initialization */
		errorcode = graphresult();
		if (errorcode != grOk) /* an error occurred */
		{
			printf("Graphics error: %s\n", grapherrormsg(errorcode));
			printf("Press any key to halt:");
			getch();
			exit(1); /* return with error code */
		}

	}
	void drawStars()
	{ 
		int i;
		for ( i=0 ; i<1000; ++i )
		{
			putpixel(array[i][0], array[i][1], array[i][2]);

		}
	}
public:
	SmileyFace()
	{
		initGraph();
		plotStars();
		firstRun=0;
		x=20;
		y=getmaxy();
		r=20;
		steps=10;
	}
	~SmileyFace()
	{
		closegraph();
	}
	void drawSmiley()
	{
		plotStars();// slows down the program
		//outer Circle Below
		setcolor(RED);
		circle(20+x,y-20,20);
		setfillstyle(1,YELLOW);
		floodfill(20+x-2,y-20-2,RED);
		//left eye
		setcolor(MAGENTA);
		circle(20-10+x,y-20-10,5);
		setfillstyle(1,GREEN);
		floodfill(20-10+x,y-20-10,MAGENTA);
		//right eye
		setcolor(MAGENTA);
		circle(20-10+20+x,y-20-10,5);
		setfillstyle(1,GREEN);
		floodfill(20-10+x+20,y-20-10,MAGENTA);
		circle(20+x,y-20+10,5);
		setfillstyle(1,BLUE);
		floodfill(20+x,y-20+10,5);
	}
	void moveLeft()
	{
		if(!(x<=0))
			x=x-steps;
	}
	void moveRight()
	{
		if(!(x>=600))
			x=x+steps;
	}
	void plotStars()
	{
		if(firstRun==0)
		{
			int i;
			for ( i=0 ; i<1000; ++i )
			{
				int x=random(MaxX);
				int y = random(MaxY);
				int numbers = random( MaxColors-1 )+1;
				putpixel(x, y, numbers);
				array[i][0] = x;
				array[i][1] = y;
				array[i][2] = numbers;
			}
			firstRun=1;
		}
		else
			drawStars();
	}
};
struct circleObjects
{
	int x,y,radius;
	int points;
	int color;
	int scores;
	int isDetected;
	circleObjects():x(0),y(0),radius(3),isDetected(0)
	{
		color = random(15)+1;
		scores = (color%5)+1;
	}
};
class cDrop
{
	friend class CollisionDetection;
	circleObjects c[Falling];
	int locationsTaken[Falling];
	int pos;
	void init()
	{
		pos=0;
		int i;
		for(i=0;i<Falling;i++)
		{
			int x;
			do
			{
				x = random(639)+1;
				if(x==0) continue;
			}while(validLocation(x)==1);
			c[i].x = x;
			c[i].y = random(8)+1;
		}
	}
	int validLocation(int toFind)
	{
		if(toFind % 12 !=0) //to keep distance between circles
			return 1;
		int i;
		for(i=0;i<Falling;i++)
		{
			if(toFind==locationsTaken[i])
				return 1;
		}
		return 0;
	}
public:
	cDrop()
	{
		init();
	}
	void display()
	{
		int i;
		for(i=0;i<Falling;i++)
		{
			setcolor(c[i].color);
			circle(c[i].x,c[i].y,c[i].radius);
		}
	}
	void increment()
	{
		int i;
		for(i=0;i<Falling;i++)
		{
			c[i].y+=3;
		}
		pos++;
		if(158<pos)
		{
			for(int i=0;i<Falling;i++)
			{
				c[i].y = 0;
				c[i].isDetected=0;
			}
			init();
		}
	}
};
void displayScore(int score)
{
	char a[30];

	setcolor(YELLOW);
	setfillstyle(SOLID_FILL,YELLOW);
	bar(10,10,95,40);
	setcolor(BLACK);
	sprintf(a,"Score : %d",score);
	outtextxy(15,20,a);
}
void timeLeft(int time)
{
	char a[30];

	setcolor(YELLOW);
	setfillstyle(SOLID_FILL,YELLOW);
	bar(600-95,10,639,40);
	setcolor(RED);
	sprintf(a,"Time Left : %d",time);
	outtextxy(515,20,a);
}
class CollisionDetection
{
public:
	static void detectCollision(cDrop &c,SmileyFace &sf, int &score)
	{
		for(int i=0;i<Falling;i++)
		{
			if(CollisionDetection::in_circle(sf.x,sf.y,sf.r,c.c[i].x,c.c[i].y)==1)
			{
				if(c.c[i].isDetected==0)
				{

					c.c[i].isDetected=1;
					score += c.c[i].scores;
				}
			}
		}
	}
	static int in_circle(int center_x, int center_y, int radius, int x,int y)
	{
		double square_dist = pow((center_x - x),2) + pow((center_y - y), 2);
		if(square_dist <= pow(radius,2))
		{
			return 1;
		}
		else
			return 0;
	}
};
int showEndScreen(int &score)
{
	char msg[30];
	clearviewport();
	setcolor(YELLOW);
	settextstyle(4,0,8);
	setcolor(RED);
	sprintf(msg,"Game Over!!!");
	outtextxy(getmaxx()/2-200,getmaxy()/2-80,msg);
	settextstyle(3,0,3);
	sprintf(msg,"Your Score:%d",score);
	outtextxy(getmaxx()/2-100,getmaxy()/2+40,msg);
	outtextxy(getmaxx()/2-100,getmaxy()/2+60,"Play another Game?");
	settextstyle(1,0,2);
	outtextxy(getmaxx()/2-100,getmaxy()/2+90,"Y for Yes");
	outtextxy(getmaxx()/2-100,getmaxy()/2+110,"N for No");
	char ch = getch();
	if(ch=='y' || ch == 'Y')
		return 1;
	else
		return 0;
}
int start(SmileyFace &sf)
{
	time_t first,second;
	int score=0;
	sf.drawSmiley();
	cDrop cd,cd1,cd2;
	cd.display();
	int i;
	first = time(NULL);
	char ch;
	do
	{
		clearviewport();
		sf.drawSmiley();
		cd.display();
		cd.increment();
		CollisionDetection::detectCollision(cd,sf,score);
		displayScore(score);
		if(kbhit())
		{
			ch= getch();
			if(ch=='a')
			{
				sf.moveLeft();
			}
			else if(ch=='d')
			{
				sf.moveRight();
			}
			else
			{
				clearviewport();
				break;
			}
		}
		second = time(NULL);
		timeLeft(Seconds-difftime(second,first));
		if(difftime(second,first) > Seconds)
		{
			int cont = showEndScreen(score);
			settextstyle(0, 0, 0);
			return cont;
		}
		delay(20);
	}
	while(1);
}
int welcome()
{
	char msg[30];
	clearviewport();
	setcolor(YELLOW);
	settextstyle(4,0,4);
	setcolor(RED);
	sprintf(msg,"Welcome to Catch the Numbers");
	outtextxy(100,getmaxy()/2-80,msg);
	settextstyle(3,0,3);
	outtextxy(getmaxy()/2-50,getmaxy()/2+40,"Are You Ready to Play?");
	settextstyle(1,0,2);
	outtextxy(getmaxx()/2-50,getmaxy()/2+70,"Y for Yes");
	outtextxy(getmaxx()/2-50,getmaxy()/2+90,"N for No");
	settextstyle(0, 0, 0); //reset text Style
	char ch = getch();
	if(ch=='y' || ch=='Y')
		return 1;
	else
		return 0;
}
void main()
{
	SmileyFace sf; // ctor call init method for initliazing graphic display
	if(welcome()==1)
	{
		clearviewport();
		int cont;
		do
		{
			cont = start(sf);
		}while(cont==1);
	}
}

