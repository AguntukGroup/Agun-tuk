#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#pragma GCC diagnostic ignored "-Wwrite-strings" 
#include <windows.h>   
#include <mmsystem.h>

#define BLUE 1
#define BLUEDR 2
#define BLUEBR 3
#define RED 4
#define REDDR 5
#define REDBR 6
#define GREEN 7
#define GREENDR 8
#define GREENBR 9
#define PURPLE 10
#define PURPLEDR 11
#define PURPLEBR 12
#define YELLOW 13
#define YELLOWDR 14
#define YELLOWBR 15
#define BLANK 0
#define REFRESH 0
#define ROWS 20
#define COLS 15



#define SHAPE_I  100
#define SHAPE_T  101
#define SHAPE_L  102
#define SHAPE_L2 103
#define SHAPE_O  104
#define SHAPE_S  105
#define SHAPE_S2 106



#define RIGHT 201
#define DOWN  203
#define TOP   30
#define LEFT  160



#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27
#define KEY_ENTER 13
#define KEY_SPACE 32





void Brick(int x, int y, char Color);         
void InitPalette();                           
void InitMatrix();                            
void GetImages();                             
void DisplayScreen();                         
void AssignShape(int Shape, int Color);       
int  DetectCollision(int Direction);          
int  MoveBlock(int Direction);               
void DisplayBlock(int x, int y);              
void DisplayNextShape();                      
void GetNextBlock();                          
void RotateBlock();                           
void UpdateScreen();                          
void CheckForLine();                          
void RemoveLine(int Number);                  
int  GetRandomColor();                        
int  GetRandomShape();                                                                            
void PrintLinesCleared();                     
void DrawBox(int x1, int y1, int x2, int y2, int Color1, int Color2, int Color3);                                
void StartScreen();                           
int  IncreaseSpeed();                                               
     



void far *bmpBlueBrick;           
void far *bmpRedBrick;
void far *bmpGreenBrick;
void far *bmpYellowBrick;
void far *bmpPurpleBrick;
void far *bmpBlankBrick;
void far *bmpLinesCleared;
void far *bmpScreen;



int BlockMatrix[4][4];                         
int ScreenLayout[COLS][ROWS];	               
int ScreenBackgroundLayout[COLS][ROWS];        
int PreviousScreenLayout[COLS][ROWS];	       
int LinesCleared=0;        
int Level=1;               
int LineScore=100;         
int Speed = 95;            
int CurrentShape;
int NextShape;
int NextColor;
int BlockX = 7;
int BlockY = 0;
int Quit=0;
int GameOver=0;       
char PLinesCleared[40];    
unsigned long Score=0;     



int ShapeI[4][4] = {
		 0,1,0,0,
		 0,1,0,0,
		 0,1,0,0,
		 0,1,0,0
	};
	
int ShapeT[4][4] = {
		 0,1,0,0,
		 0,1,1,0,
		 0,1,0,0,
		 0,0,0,0
	};
	
int ShapeL[4][4] = {
		 0,0,1,0,
		 1,1,1,0,
		 0,0,0,0,
		 0,0,0,0
	};
	
int ShapeL2[4][4] = {
		 1,0,0,0,
		 1,1,1,0,
		 0,0,0,0,
		 0,0,0,0
	};
	
int ShapeS[4][4] = {
		 0,1,1,0,
		 1,1,0,0,
		 0,0,0,0,
		 0,0,0,0
	};
	
int ShapeS2[4][4] = {
		 1,1,0,0,
		 0,1,1,0,
		 0,0,0,0,
		 0,0,0,0
	};
	
int ShapeO[4][4] = {
		 1,1,0,0,
		 1,1,0,0,
		 0,0,0,0,
		 0,0,0,0
	};





int main(){
    getchar();
	int gd=DETECT, gm;
	int Return=0;
	char Key, ScanCode;
	int Counter=0;                          
	initgraph(&gd, &gm,"c:\\tc\\bgi");      
	int randomize();                            
	cleardevice();                          
	InitPalette();                          
	InitMatrix();                           
	GetImages();                            
                        
	cleardevice();                          
	AssignShape(GetRandomShape(), GetRandomColor());      
	NextShape=GetRandomShape();
	NextColor=GetRandomColor();                                         	
	DisplayScreen();                        
    
	MoveBlock(LEFT);                        
	while(kbhit()) getch();  		
	while (!Quit && !GameOver) {            
		if(++Counter >= Speed)          
		{	Counter=0;
			MoveBlock(DOWN);
			
		}
		if(kbhit())                     
		{  Key = getch();
		   if(Key == 0)
		   {	   ScanCode = getch();
			   if(ScanCode == KEY_UP)
					RotateBlock();
			   else if(ScanCode == KEY_LEFT)
					MoveBlock(LEFT);
			   else if(ScanCode == KEY_RIGHT)
					MoveBlock(RIGHT);
			   else if(ScanCode == KEY_DOWN)
			   {		Score++;         

					MoveBlock(DOWN);
			   }
			   if(!Return)
				   
			   Return = 0;
		   }
		   else if(Key == KEY_ENTER || Key == KEY_SPACE)   
				RotateBlock();

		}
		delay(6);      	      
	}
	if(GameOver)                  
	{      	DisplayBlock(6,0);          
	}
	restorecrtmode();    
	
	return 0;
}




void Brick(int x, int y, char Color)
{	int up[6] = { x,y,  x+20,y,  x,y+20 };			
	int lw[6] = { x+20,y+20,  x+20,y,  x,y+20 };		
	switch(Color)
	{  case BLUE:
		setcolor(BLUEBR);
		setfillstyle(1,BLUEBR);				
		fillpoly(3, up);
		setcolor(BLUEDR);
	setfillstyle(1,BLUEDR);				
		fillpoly(3, lw);
		setcolor(BLUE);
	setfillstyle(1,BLUE);				
		bar(x+5, y+5, x+15, y+15);
		break;
	  case RED:
		setcolor(REDBR);
		setfillstyle(1,REDBR);				
		fillpoly(3, up);
		setcolor(REDDR);
		setfillstyle(1,REDDR);				
		fillpoly(3, lw);
		setcolor(RED);
		setfillstyle(1,RED);		       	        
		bar(x+5, y+5, x+15, y+15);
		break;
	  case GREEN:
		setcolor(GREENBR);
		setfillstyle(1,GREENBR);			
		fillpoly(3, up);
		setcolor(GREENDR);
		setfillstyle(1,GREENDR);			
		fillpoly(3, lw);
		setcolor(GREEN);
		setfillstyle(1,GREEN);				
		bar(x+5, y+5, x+15, y+15);
		break;
	  case PURPLE:
		setcolor(PURPLEBR);
		setfillstyle(1,PURPLEBR);			
		fillpoly(3, up);
		setcolor(PURPLEDR);
		setfillstyle(1,PURPLEDR);			
		fillpoly(3, lw);
		setcolor(PURPLE);
		setfillstyle(1,PURPLE);				
		bar(x+5, y+5, x+15, y+15);
		break;
	  case YELLOW:
		setcolor(YELLOWBR);
		setfillstyle(1,YELLOWBR);			
		fillpoly(3, up);
		setcolor(YELLOWDR);
		setfillstyle(1,YELLOWDR);			
		fillpoly(3, lw);
		setcolor(YELLOW);
		setfillstyle(1,YELLOW);				
		bar(x+5, y+5, x+15, y+15);
		break;
	}
}


void InitPalette()
{	
	setpalette(BLUE,1);    
	setpalette(BLUEDR,8);  
	setpalette(BLUEBR,9);  


	setpalette(RED,4);     
	setpalette(REDDR,32);  
	setpalette(REDBR,36);  


	setpalette(GREEN,2);     
	setpalette(GREENDR,16);  
	setpalette(GREENBR,18);  


	setpalette(PURPLE,13);    
	setpalette(PURPLEDR,33);  
	setpalette(PURPLEBR,61);  


	setpalette(YELLOW,6);     
	setpalette(YELLOWDR,48);  
	setpalette(YELLOWBR,62);  
}



void GetImages()
{	Brick(100,100,BLUE);         
	Brick(130,100,RED);          
	Brick(160,100,GREEN);        
	Brick(190,100,YELLOW);       
	Brick(220,100,PURPLE);       

	
	bmpBlueBrick   = malloc(imagesize(0,0,20,20));
	bmpRedBrick    = malloc(imagesize(0,0,20,20));
	bmpGreenBrick  = malloc(imagesize(0,0,20,20));
	bmpYellowBrick = malloc(imagesize(0,0,20,20));
	bmpPurpleBrick = malloc(imagesize(0,0,20,20));
	bmpBlankBrick  = malloc(imagesize(0,0,20,20));
	bmpLinesCleared= malloc(imagesize(501,51,607,69));
	bmpScreen      = malloc(imagesize(0,0,640,480));

	
	getimage(100,100,120,120,bmpBlueBrick);
	getimage(130,100,150,120,bmpRedBrick);
	getimage(160,100,180,120,bmpGreenBrick);
	getimage(190,100,210,120,bmpYellowBrick);
	getimage(220,100,240,120,bmpPurpleBrick);
	getimage(0,0,20,20,bmpBlankBrick);
	getimage(501,51,607,69,bmpLinesCleared);
}



void InitMatrix()
{	for(int x=0; x<COLS; x++)
	   for(int y=0; y<ROWS; y++)
	   {	  ScreenLayout[x][y] = BLANK;           
		  PreviousScreenLayout[x][y] = BLANK;
		  ScreenBackgroundLayout[x][y] = BLANK;
	   }
}



void DisplayScreen()
{	setcolor(3);
	rectangle(156,26,478,452);                                     

}



void AssignShape(int Shape, int Color)
{	int i,j;
	CurrentShape = Shape;
	switch(Shape)
	{ case SHAPE_I:
		for(i=0; i<4; i++)
		   for(j=0; j<4; j++)
			  BlockMatrix[j][i] = ShapeI[i][j]*Color;   
		break;
	  case SHAPE_T:
		for(i=0; i<4; i++)
		   for(j=0; j<4; j++)
			  BlockMatrix[j][i] = ShapeT[i][j]*Color;
		break;
	  case SHAPE_L:
		for(i=0; i<4; i++)
		   for(j=0; j<4; j++)
			  BlockMatrix[j][i] = ShapeL[i][j]*Color;
		break;
	  case SHAPE_L2:
		for(i=0; i<4; i++)
		   for(j=0; j<4; j++)
			  BlockMatrix[j][i] = ShapeL2[i][j]*Color;
		break;
	  case SHAPE_O:
		for(i=0; i<4; i++)
		   for(j=0; j<4; j++)
			  BlockMatrix[j][i] = ShapeO[i][j]*Color;
		break;
	  case SHAPE_S:
		for(i=0; i<4; i++)
		   for(j=0; j<4; j++)
			  BlockMatrix[j][i] = ShapeS[i][j]*Color;
		break;
	  case SHAPE_S2:
		for(i=0; i<4; i++)
		   for(j=0; j<4; j++)
			  BlockMatrix[j][i] = ShapeS2[i][j]*Color;
		break;
	  default:
		break;
	}
}



int GetRandomColor()
{	int Color = rand() % 5;
	switch(Color)
	{ case 0 :
	     return BLUE;
	  case 1:
	     return RED;
	  case 2:
	     return GREEN;
	  case 3:
	     return YELLOW;
	  case 4:
	     return PURPLE;
	}
	return 0;
}



int GetRandomShape()
{	int Shape = rand() % 7;
	switch(Shape)
	{  case 0 :
	      return SHAPE_I;
	   case 1:
	      return SHAPE_L;
	   case 2:
	      return SHAPE_T;
	   case 3:
	      return SHAPE_O;
	   case 4:
	      return SHAPE_S;
	   case 5:
	      return SHAPE_S2;
	   case 6:
	      return SHAPE_L2;
	}
	return 0;
}



int MoveBlock(int Direction)
{	switch(Direction)
	{  case LEFT:
		if(DetectCollision(LEFT))
			return 1;
		DisplayBlock(--BlockX, BlockY);
		break;
	   case RIGHT:
		if(DetectCollision(RIGHT))
			return 1;
		DisplayBlock(++BlockX, BlockY);
		break;
	   case DOWN:
		if(DetectCollision(DOWN)) {
			GetNextBlock();       
			return 1;
		}
		DisplayBlock(BlockX, ++BlockY);
		break;
	   case REFRESH:
		DisplayBlock(BlockX, BlockY);
		break;
	}
	return 0;
}



void RotateBlock()
{	int TempBlockMatrix[4][4];
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
		   TempBlockMatrix[i][j] = BlockMatrix[i][j];
	switch(CurrentShape)
	{  case SHAPE_O:      
		return;
	   case SHAPE_L:      
	   case SHAPE_L2:
	   case SHAPE_S:
	   case SHAPE_S2:
	   case SHAPE_T:
		BlockMatrix[0][0] = TempBlockMatrix[2][0];
		BlockMatrix[0][2] = TempBlockMatrix[0][0];
		BlockMatrix[2][2] = TempBlockMatrix[0][2];
		BlockMatrix[2][0] = TempBlockMatrix[2][2];

		BlockMatrix[0][1] = TempBlockMatrix[1][0];
		BlockMatrix[1][2] = TempBlockMatrix[0][1];
		BlockMatrix[2][1] = TempBlockMatrix[1][2];
		BlockMatrix[1][0] = TempBlockMatrix[2][1];
		break;
	   case SHAPE_I:
		BlockMatrix[0][1] = TempBlockMatrix[1][0];      
		BlockMatrix[1][0] = TempBlockMatrix[0][1];

		BlockMatrix[1][2] = TempBlockMatrix[2][1];
		BlockMatrix[2][1] = TempBlockMatrix[1][2];

		BlockMatrix[1][3] = TempBlockMatrix[3][1];
		BlockMatrix[3][1] = TempBlockMatrix[1][3];
		break;
	}
	if(DetectCollision(REFRESH))
	{	for(int i=0; i<4; i++)
			for(int j=0; j<4; j++)
			   BlockMatrix[i][j] = TempBlockMatrix[i][j];
		return;
	}
	MoveBlock(REFRESH);
}



void DisplayBlock(int x, int y)
{	int i, j;
	for(i=0; i<ROWS; i++)
	   for(j=0; j<COLS; j++)
		   ScreenLayout[j][i] = ScreenBackgroundLayout[j][i];   

	for(i=0; i<4; i++)
	{   if((x+i)<0 || (x+i) > COLS)
		  continue;
	   for(j=0; j<4; j++)
	   {	   if((y+j)>ROWS)
				continue;
		   if(BlockMatrix[i][j] == 0)
				continue;
		   ScreenLayout[x+i][y+j] = BlockMatrix[i][j];   
	   }
	}
	UpdateScreen();     
}



int DetectCollision(int Direction)
{	int x,y;
	int Bx=BlockX;
	int By=BlockY;
	switch(Direction)
	{  case LEFT:
		--Bx;
		break;
	   case RIGHT:
		++Bx;
		break;
	   case DOWN:
		By++;
		break;
	   default:
		break;
	}


	if(Bx < 0) {
	   for(x=0; (x+Bx)<0; x++)         
		  for(y=0; y<4; y++)
			 if(BlockMatrix[x][y]!=0)
				return 1;
	}

	
	if(Bx > COLS-4)
	{   for(x=Bx+3; x>=COLS; x--)      
		  for(y=0; y<4; y++)
			 if(BlockMatrix[x-Bx][y]!=0)
				return 1;
	}

	for(x=0; x<4; x++)
		  for(y=3; y>=0; y--)     
		  {		 if((ScreenBackgroundLayout[Bx+x][By+y]!=BLANK && BlockMatrix[x][y]!=BLANK) ||
				 ((By+y)>=ROWS && BlockMatrix[x][y]!=BLANK))
				return 1;
		  }

	return 0;
}



void GetNextBlock()
{	for(int x=0; x<4; x++)
	   for(int y=0; y<4; y++)
		  if(BlockMatrix[x][y] != BLANK)
			  ScreenBackgroundLayout[BlockX+x][BlockY+y] = BlockMatrix[x][y];   
	CheckForLine();             
	AssignShape(NextShape, NextColor);      
	NextShape = GetRandomShape();          
	NextColor = GetRandomColor();           
              
	BlockX = 7;                             
	BlockY = 0;
	if(MoveBlock(LEFT))     
	{   GameOver=1;
	}
}



void UpdateScreen()
{	for(int x=0; x<COLS; x++)
	   for(int y=0; y<ROWS; y++)
	   {	  if(PreviousScreenLayout[x][y] == ScreenLayout[x][y])
			  continue;           
		  PreviousScreenLayout[x][y] = ScreenLayout[x][y];
		  switch(ScreenLayout[x][y])                      
		  {  case BLUE:
			putimage(LEFT+x*21, TOP+y*21, bmpBlueBrick, 0);
			break;
		     case RED:
			putimage(LEFT+x*21, TOP+y*21, bmpRedBrick, 0);
			break;
		     case GREEN:
			putimage(LEFT+x*21, TOP+y*21, bmpGreenBrick, 0);
			break;
		     case YELLOW:
			putimage(LEFT+x*21, TOP+y*21, bmpYellowBrick, 0);
			break;
		     case PURPLE:
			putimage(LEFT+x*21, TOP+y*21, bmpPurpleBrick, 0);
			break;
		     default:
			putimage(LEFT+x*21, TOP+y*21, bmpBlankBrick, 0);
		  }
	   }
}







void CheckForLine()
{	int RemoveLines[10];
	int Remove;
	int x,y;
	int factor=1;
	for(y=0; y<ROWS; y++)
	{  Remove=1;
	   for(x=0; x<COLS; x++)
	   {	  if(ScreenLayout[x][y] == BLANK)
			 Remove=0;
	   }
	   if(Remove)
	   {	  RemoveLine(y);
		  Score += LineScore*factor;
		  factor++;

	   }
	}
	while (kbhit()) getch();      
}



void RemoveLine(int LineNumber)
{	int i,j;
	int count=0;  
	int Temp[COLS];
	for(i=0; i<COLS; i++)
	{   Temp[i]=ScreenLayout[i][LineNumber];    
	}
	for(j=0; j<10; j++)
	{	for(i=0; i<COLS; i++)               
		{  ScreenLayout[i][LineNumber]=(count ? Temp[i] : BLANK);    
		}
		count = !count;       
		UpdateScreen();
		delay(50);
	}
	for(i=LineNumber; i>0; i--)
	   for(j=0; j<COLS; j++)
	   {	  ScreenBackgroundLayout[j][i] = ScreenBackgroundLayout[j][i-1];    
	   }
	for(j=0; j<COLS; j++)
	   ScreenBackgroundLayout[j][0] = BLANK;     
	for(i=0; i<COLS; i++)
	   for(j=0; j<ROWS; j++)
		  ScreenLayout[i][j] = ScreenBackgroundLayout[i][j];     
	++LinesCleared;

	if(!(LinesCleared % 20))    
	   IncreaseSpeed();
}

int IncreaseSpeed()
{	if(Speed-5 <= 0)
		return 1;
	Speed -= 5;             
	Level++;                

	return 0;
}



void DrawBox(int x1, int y1, int x2, int y2, int Color1, int Color2, int Color3)
{	setlinestyle(0,0,1);
	setcolor(Color1);
	rectangle(x1,y1,x2,y2);
	setcolor(Color2);
	rectangle(x1+2,y1+2,x2-2,y2-2);
	setcolor(Color3);
	rectangle(x1+4,y1+4,x2-4,y2-4);
}






