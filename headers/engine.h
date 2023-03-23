#include <iostream>
#include <string> 
#include <cstring> 
int wcastleleft = 1;
int wcastleright = 1;
int bcastleleft = 1; 
int bcastleright = 1; 
int numberboard[8][8];
using std::string;
std::string transpositionarray[15000000];
int transpositioncount=0;
//int takcount=0;


int fakewcastleleft = 1;
int fakewcastleright = 1;
int fakebcastleleft = 1;
int fakebcastleright = 1;

int totalcount=0;
int shorten(int num)
{

	if(num ==3)
	{
		//return -=1;
		return -1;
	}
	else if(num ==4)
	{
		return -3;
	}
	else if(num ==5)
	{
		return -3;
	}
	else if(num ==2)
	{
		return -9;
	}
	else if(num ==6)
	{
		return -5;
	}
	else if(num ==16)
	{
		return 5;
	}
	else if(num ==13)
	{
		return 1;
	}
	else if(num ==12)
	{
		return 9;
	}
	else if(num ==15)
	{
		return 3;
	}
	else if(num ==14)
	{
		return 3;
	}
	else if(num ==1)
	{
		return -90;
	}
	else if(num ==11)
	{
		return 90;
	}
	else
	{
		return 0;
	}
}

int movecount(int number[][8])
{
	int total=0;
	for(int i=0; i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			total +=shorten(number[i][j]);
		}
	}
	return total;
}
void evaluate(int i,int j,int value)
{
	if(i==100 &&j==100)
	{
		//int board[8][8];
		for(int i=0; i<8;i++)
		{
			for(int j=0;j<8;j++)
			{
				numberboard[i][j] = 0;
			}
		}

	}
	numberboard[i][j] = value;
}

bool horz(int blkorwht, int x, int y)
{
	int iterx =x;
	//int itery =y;
	if(blkorwht==1)
	{
		for(int iter =0; iter<8; iter++)
		{
			if(iterx >=0&&iterx<8)
			{
				if(numberboard[iterx][y] >10 &&numberboard[iterx][y]==16)
				{
					return false;

				}
				if(numberboard[iterx][y] <10&&numberboard[iterx][y] !=0)
				{
					return true;

				}
				else
				{
					iterx=x-iter;
					//itery = y-iter;
				}

			}
		}
		return true;
	}
	else
	{
		for(int iter =0; iter<8; iter++)
		{
			if(iterx >=0 && iterx<8)
			{
				if(numberboard[iterx][y]==6||numberboard[iterx][y] ==2)
				{
					return false;
				}
				if(numberboard[iterx][y] >10&&numberboard[iterx][y] !=0)
				{
					return true;
				}
				else
				{
					iterx= x+iter;
					//itery = y-iter;
				}
			}
		}
		return true;
	}

}
bool leftd(int blkorwht, int x, int y)
{
	int iterx = x;
	int itery = y;
	if(blkorwht==1)
	{
		for(int iter =0;iter<8;iter++)
		{
			if(iterx>=0 &&iterx<8&&itery>=0 &&itery<8)
			{
				if(numberboard[iterx][itery] >10)
				{
					return false;

				}
				if(numberboard[iterx][itery] <10&&numberboard[iterx][itery] !=0)
				{
					return true;
				}
				else
				{
					iterx = x-iter;
					itery = y-iter;
				}
			}
		}
		return true;
	}
	else
	{
		for(int iter =0;iter<8;iter++)
		{
			if(iterx>=0 &&iterx<8&&itery>=0 &&itery<8)
			{
				if(numberboard[iterx][itery] ==5||numberboard[iterx][itery]==2)//bishop
				{
					return false;
				}
				if(numberboard[iterx][itery] >10&&numberboard[iterx][itery] !=0)
				{
					return true;
				}
				else
				{
					iterx = x+iter;
					itery = y-iter;
				}
			}
		}
		return true;

	}
}

bool rightd(int blkorwhite, int x, int y)
{
	int iterx =x;
	int itery =y;
	if(blkorwhite==1)
	{
		for(int iter =0;iter<8;iter++)
		{
			if(iterx>=0 &&iterx<8&&itery>=0 &&itery<8)
			{
				if(numberboard[iterx][itery]==15||numberboard[iterx][itery]==12)
				{
					return false;

				}
				if(numberboard[iterx][itery] <10&&numberboard[iterx][itery] !=0)
				{
					return true;
				}
				else
				{
					iterx = x-iter;
					itery = y+iter;
				}
			}
		}
		return true;
	}
	else//black
	{
		for(int iter =0;iter<8;iter++)
		{
			if(iterx>=0 &&iterx<8&&itery>=0 &&itery<8)
			{
				if(numberboard[iterx][itery] == 5||numberboard[iterx][itery]== 2)//bishop
				{
					return false;
				}
				if(numberboard[iterx][itery] >10 && numberboard[iterx][itery] !=0)
				{
					return true;
				}
				else
				{
					iterx=x+iter;
					itery = y+iter;
				}
			}
		}
		return true;
	}
}

void Aprintf(int number[][8]=numberboard)
{
	for(int i=0; i<8;i++)
	{
		std::cout <<" \n";
		for(int j=0; j<8;j++)
		{
			std::cout<< number[i][j] <<" ";
		}
	}

	std::cout<<"\n";
}

//legalmoves
void Rules(int piece,int i, int j, int legalmoves[])
{
	//int rlegalmoves[128];
	if(numberboard[7][0] != 6 ||numberboard[7][4] !=1)//white leftsidecastle
	{
		wcastleleft =-1;
	}
	if(numberboard[0][0] != 16 ||numberboard[0][4] !=11)//blk leftsidecastle
	{
		bcastleleft =-1;
	}
	if(numberboard[7][7] != 6 ||numberboard[7][4] !=1)//white rightsidecastle
	{
		wcastleright =-1;
	}
	if(numberboard[0][7] != 16 ||numberboard[0][4] !=11)//blk rightsidecastle
	{
		bcastleright =-1;
	}
	legalmoves[0] = 0;
	int count =0; //replace
	if(piece==3)//white pawn
	{

		if(i==6)
		{
			if(numberboard[i-1][j]==0 && numberboard[i-2][j]==0)
			{
				count +=4;
				legalmoves[0]=count;
				legalmoves[1] = i-1;
				legalmoves[2] = j;
				legalmoves[3] = i-2;
				legalmoves[4] = j;
				//return legalmoves;
			}
			else if(numberboard[i-1][j] ==0)
			{
				count+=2;
				legalmoves[0] = count;
				legalmoves[1] = i-1;
				legalmoves[2] = j;
				//return legalmoves;
			}

		}
		else
		{
			if(numberboard[i-1][j] ==0)
			{
				count+=2;
				legalmoves[0] = count;
				legalmoves[1] = i-1;
				legalmoves[2] = j;
			//	return legalmoves;
			}
			else
			{
				//return legalmoves;
			}
		}
		if(numberboard[i-1][j-1] >10)
		{
			legalmoves[count +1] = i-1;
			legalmoves[count +2] = j-1;
			count +=2;
		}
		if(numberboard[i-1][j+1] >10)
		{
			legalmoves[count +1] = i-1;
			legalmoves[count +2] = j+1;
			count +=2;
		}
		count = count/2;
		legalmoves[0]=count;

	}
	else if(piece ==13)//blk pawn
	{
		legalmoves[0] = 0;
		int count =0;
		if(i==1)
		{
			if(numberboard[i+1][j]==0 &&numberboard[i+2][j]==0 && i+1<8 && i+2<8)
			{
				count +=4;
				legalmoves[0]=count;
				legalmoves[1] = i+1;
				legalmoves[2] = j;
				legalmoves[3] = i+2;
				legalmoves[4] = j;
				//return legalmoves;
			}
			else if(numberboard[i+1][j] ==0)
			{
				count+=2;
				legalmoves[0] = count;
				legalmoves[1] = i+1;
				legalmoves[2] = j;
				//return legalmoves;
			}
			else
			{
				//	return legalmoves;
			}
		}
		else
		{
			if(numberboard[i+1][j] ==0)
			{
				count+=2;
				legalmoves[0] = count;
				legalmoves[1] = i+1;
				legalmoves[2] = j;
				//return legalmoves;
			}
			else
			{
			//return legalmoves;
			}
		}
		if(numberboard[i+1][j+1] <10 && i+1<8 &&j+1<8 && numberboard[i+1][j+1]>0)
		{
			legalmoves[count +1] = i+1;
			legalmoves[count +2] = j+1;
			count +=2;
		}
		if(numberboard[i+1][j-1] <10 && j-1>=0 && i+1<8 && numberboard[i+1][j-1]>0)
		{
			legalmoves[count +1] = i+1;
			legalmoves[count +2] = j-1;
			count +=2;
		}
		count = count/2;
		legalmoves[0] = count;
	}
	else if(piece ==6)//white rook
	{
		int count=0;
		for(int iteri =i+1; iteri< 8 ;iteri++)//going up
		{
			if(numberboard[iteri][j] == 0)
			{
				legalmoves[count +1] = iteri;
				legalmoves[count +2] = j;
				count+=2;
				continue;
			}
			if(numberboard[iteri][j] < 10)
			{
				break;
			}
			else//opponent pieces
			{
				legalmoves[count +1] = iteri;
				legalmoves[count +2] = j;
				count+=2;
				break;
			}
		}
		for(int iteri =i-1; iteri >=0; iteri--)//going down
		{
//			if(numberboard[iteri][j] < 10)
			if(numberboard[iteri][j] == 0)
			{
				legalmoves[count +1] = iteri;
				legalmoves[count +2] = j;
				count+=2;
				continue;
			}
			if(numberboard[iteri][j] < 10)
			{
				break;
			}
			else
			{
				legalmoves[count +1] = iteri;
				legalmoves[count +2] = j;
				count+=2;
				break;
			}
		}

		for(int iterj =j+1; iterj <8; iterj++)//right
		{

			if(numberboard[i][iterj] ==0)
			{
				legalmoves[count +1] = i;
				legalmoves[count +2] = iterj;
				count+=2;
				continue;
			}
			if(numberboard[i][iterj] < 10)
			{
				break;
			}
			else
			{
				legalmoves[count +1] = i;
				legalmoves[count +2] = iterj;
				count+=2;
				break;
			}
		}
		for(int iterj =j-1; iterj >=0; iterj--)//left
		{
//			if(numberboard[i][iterj] < 10)
			if(numberboard[i][iterj] ==0)
			{
				legalmoves[count +1] = i;
				legalmoves[count +2] = iterj;
				count +=2;
				continue;
			}
			if(numberboard[i][iterj] < 10)
			{
				break;
			}
			else
			{
				legalmoves[count +1] = i;
				legalmoves[count +2] = iterj;
				count +=2;
				break;
			}
		}
		count = count/2;
		legalmoves[0] =count;
	}
	else if(piece==16)//blk rook
	{
		legalmoves[0] =0;
		int count=0;
		for(int iteri =i+1; iteri< 8 ;iteri++)//going up
		{
			if(numberboard[iteri][j] ==0)
			{
				legalmoves[count +1] = iteri;
				legalmoves[count +2] = j;
				count+=2;
				continue;
			}
			if(numberboard[iteri][j] > 10)
			{
				break;
			}
			else
			{
				legalmoves[count +1] = iteri;
				legalmoves[count +2] = j;
				count+=2;
				break;
			}
		}
		for(int iteri =i-1; iteri >=0; iteri--)//going down
		{
			if(numberboard[iteri][j] ==0)
			{
				legalmoves[count +1] = iteri;
				legalmoves[count +2] = j;
				count+=2;
				continue;
			}
			if(numberboard[iteri][j] > 10)
			{
				break;
			}
//			else if(numberboard[iteri][j] < 10)
			else
			{
				legalmoves[count +1] = iteri;
				legalmoves[count +2] = j;
				count+=2;
				break;
			}
		}

		for(int iterj =j+1; iterj <8; iterj++)//right
		{
			if(numberboard[i][iterj]==0)
			{
				legalmoves[count +1] = i;
				legalmoves[count +2] = iterj;
				count+=2;
				continue;
			}
			
			if(numberboard[i][iterj] > 10)
			{
				break;
			}
			else
			{
				legalmoves[count +1] = i;
				legalmoves[count +2] = iterj;
				count+=2;
				break;
			}
		}

		for(int iterj =j-1; iterj >=0; iterj--)//left
		{
			if(numberboard[i][iterj] > 10)
			{
				break;
			}
//			if(numberboard[i][iterj] < 10)
			else if(numberboard[i][iterj] < 10 &&numberboard[i][iterj] !=0)
			{
				legalmoves[count +1] = i;
				legalmoves[count +2] = iterj;
				count +=2;
				break;
			}
			legalmoves[count +1] = i;
			legalmoves[count +2] = iterj;
			count +=2;
		}
		count = count/2;
		legalmoves[0] =count;
	}
	else if(piece==4)//white knight
	{
		legalmoves[0] =0;
		int count =0;
		int y = i-2;
		int x = j-1;

		//a
		if(x>=0 && x<8 &&y>=0 && y<8)
		{
			if(numberboard[y][x]==0 || numberboard[y][x] >10)
			{
				legalmoves[count +1]= y;
				legalmoves[count + 2] = x;
				count+=2;
			}
		}

		//b
		y = i-2;
		x = j+1;
		if(x>=0 && x<8 &&y>=0 && y<8)
		{
//			if(numberboard[y][x]==0)
			if(numberboard[y][x]==0||numberboard[y][x] >10)
			{
				legalmoves[count +1]= y;
				legalmoves[count + 2] = x;
				count+=2;
			}
		}
		
		//c
		y = i-1;
		x = j-2;
		if(x>=0 && x<8 &&y>=0 && y<8)
		{
//			if(numberboard[y][x]==0)
			if(numberboard[y][x]==0||numberboard[y][x] >10)
			{
				legalmoves[count +1]= y;
				legalmoves[count + 2] = x;
				count+=2;
			}

		}

		//d
		y = i-1;
		x = j+2;
		if(x>=0 && x<8 &&y>=0 && y<8)
		{
//			if(numberboard[y][x]==0)
			if(numberboard[y][x]==0 || numberboard[y][x] >10)
			{
				legalmoves[count +1]= y;
				legalmoves[count + 2] = x;
				count+=2;
			}
		}

		//e
		y= i+1;
		x= j-2;
		if(x>=0 && x<8 &&y>=0 && y<8)
		{
//			if(numberboard[y][x]==0)
			if(numberboard[y][x]==0 || numberboard[y][x] >10)
			{
				legalmoves[count +1]= y;
				legalmoves[count + 2] = x;
				count+=2;
			}

		}

		//f
		y = i+1;
		x = j+2;
		if(x>=0 && x<8 &&y>=0 && y<8)
		{
//			if(numberboard[y][x]==0)
			if(numberboard[y][x]==0 || numberboard[y][x] >10)
			{
				legalmoves[count +1]= y;
				legalmoves[count + 2] = x;
				count+=2;
			}

		}

		//g
		y= i+2;
		x= j-1;
		if(x>=0 && x<8 &&y>=0 && y<8)
		{
//			if(numberboard[y][x]==0)
			if(numberboard[y][x]==0 || numberboard[y][x] >10)
			{
				legalmoves[count +1]= y;
				legalmoves[count + 2] = x;
				count+=2;
			}
		}

		//h
		y = i+2;
		x = j+1;
		if(x>=0 && x<8 &&y>=0 && y<8)
		{
//			if(numberboard[y][x]==0)
			if(numberboard[y][x]==0 || numberboard[y][x] >10)
			{
				legalmoves[count +1]= y;
				legalmoves[count + 2] = x;
				count+=2;
			}

		}
		count = count/2;
		legalmoves[0]=count;
	}
	else if(piece==14)//blk knight
	{
		legalmoves[0] =0;
		int count =0;
		int y = i-2;
		int x = j-1;
		//a
		if(x>=0 && x<8 &&y>=0 && y<8)
		{
//			if(numberboard[y][x]==0)
			if(numberboard[y][x]==0 || numberboard[y][x] <10)
			{
				legalmoves[count +1]= y;
				legalmoves[count + 2] = x;
				count+=2;
			}
		}

		//b
		y = i-2;
		x = j+1;
		if(x>=0 && x<8 &&y>=0 && y<8)
		{
//			if(numberboard[y][x]==0)
			if(numberboard[y][x]==0 || numberboard[y][x] <10)
			{
				legalmoves[count +1]= y;
				legalmoves[count + 2] = x;
				count+=2;
			}
		}
		
		//c
		y =  i-1;
		x = j-2;
		if(x>=0 && x<8 &&y>=0 && y<8)
		{
//			if(numberboard[y][x]==0)
			if(numberboard[y][x]==0 || numberboard[y][x] <10)
			{
				legalmoves[count +1]= y;
				legalmoves[count + 2] = x;
				count+=2;
			}
			
		}
		
		//d
		y = i-1;
		x = j+2;
		if(x>=0 && x<8 &&y>=0 && y<8)
		{
//			if(numberboard[y][x]==0)
			if(numberboard[y][x]==0 || numberboard[y][x] <10)
			{
				legalmoves[count +1]= y;
				legalmoves[count + 2] = x;
				count+=2;
			}
		}

		//e
		y= i+1;
		x= j-2;
		if(x>=0 && x<8 &&y>=0 && y<8)
		{
//			if(numberboard[y][x]==0)
			if(numberboard[y][x]==0 || numberboard[y][x] <10)
			{
				legalmoves[count +1]= y;
				legalmoves[count + 2] = x;
				count+=2;
			}
			
		}
		
		//f
		y = i+1;
		x = j+2;
		if(x>=0 && x<8 &&y>=0 && y<8)
		{
//			if(numberboard[y][x]==0)
			if(numberboard[y][x]==0 || numberboard[y][x] <10)
			{
				legalmoves[count +1]= y;
				legalmoves[count + 2] = x;
				count+=2;
			}
			
		}
		//g
		y= i+2;
		x= j-1;
		if(x>=0 && x<8 &&y>=0 && y<8)
		{
//			if(numberboard[y][x]==0)
			if(numberboard[y][x]==0 || numberboard[y][x] <10)
			{
				legalmoves[count +1]= y;
				legalmoves[count + 2] = x;
				count+=2;
			}
			
		}
		
		//h
		y = i+2;
		x = j+1;
		if(x>=0 && x<8 &&y>=0 && y<8)
		{
//			if(numberboard[y][x]==0)
			if(numberboard[y][x]==0 || numberboard[y][x] <10)
			{
				legalmoves[count +1]= y;
				legalmoves[count + 2] = x;
				count+=2;
			}

		}
		count = count/2;
		legalmoves[0]=count;

	}
	else if(piece==5)//white bishop
	{
		//left diagonal
		int x =i-1;
		int y  = j-1;
		count =0;
		for(int iter =0; iter <8;iter++)
		{
			if(x>=0 && x<8 &&y>=0 && y<8)
			{
				if(numberboard[x][y]==0)
				{
					legalmoves[count +1] = x;
					legalmoves[count +2] = y;
					count+=2;
					x-=1;
					y-=1;
				}
				else if(numberboard[x][y] > 10)
				{
					legalmoves[count +1] = x;
					legalmoves[count +2] = y;
					count+=2;
					x-=1;
					y-=1;
					break;
				}
				else
				{
					break;
				}

			}
			else
			{
				break;
			}
		}

		//top right diagonal
		x= i-1;
		y= j+1;
		for(int iter =0; iter <8;iter++)
		{
			if(x>=0 && x<8 &&y>=0 && y<8)
			{
				if(numberboard[x][y]==0)
				{
					legalmoves[count +1] = x;
					legalmoves[count +2] = y;
					count+=2;
					x-=1;
					y+=1;
				}
				else if(numberboard[x][y] > 10)
				{
					legalmoves[count +1] = x;
					legalmoves[count +2] = y;
					count+=2;
					x-=1;
					y-=1;
					break;
				}
				else
				{
					break;
				}

			}
			else
			{
				break;
			}
		}

		//bottom left diagonal
		x = i+1;
		y = j-1;
		for(int iter =0; iter <8;iter++)
		{
			if(x>=0 && x<8 &&y>=0 && y<8)
			{
				if(numberboard[x][y]==0)
				{
					legalmoves[count +1] = x;
					legalmoves[count +2] = y;
					count+=2;
					x+=1;
					y-=1;
				}
				else if(numberboard[x][y] > 10)
				{
					legalmoves[count +1] = x;
					legalmoves[count +2] = y;
					count+=2;
					x-=1;
					y-=1;
					break;
				}
				else
				{
					break;
				}

			}
			else
			{
				break;
			}
		}
	
		//bottom right diagonal
		x=i+1;
		y=j+1;
		for(int iter =0; iter <8;iter++)
		{
			if(x>=0 && x<8 &&y>=0 && y<8)
			{
				if(numberboard[x][y]==0)
				{
					legalmoves[count +1] = x;
					legalmoves[count +2] = y;
					count+=2;
					x+=1;
					y+=1;
				}
				else if(numberboard[x][y] > 10)
				{
					legalmoves[count +1] = x;
					legalmoves[count +2] = y;
					count+=2;
					x-=1;
					y-=1;
					break;
				}
				else
				{
					break;
				}

			}
			else
			{
				break;
			}
		}
		count = count/2;
		legalmoves[0] = count;
	}
	else if(piece==15)//blk bishop
	{
		//top left diagonal
		int x =i-1;
		int y  = j-1;
		count =0;
		for(int iter =0; iter <8;iter++)
		{
			if(x>=0 && x<8 &&y>=0 && y<8)
			{
				if(numberboard[x][y]==0)
				{
					legalmoves[count +1] = x;
					legalmoves[count +2] = y;
					count+=2;
					x-=1;
					y-=1;
				}
				else if(numberboard[x][y] < 10)
				{
					legalmoves[count +1] = x;
					legalmoves[count +2] = y;
					count+=2;
					x-=1;
					y-=1;
					break;
				}
				else
				{
					break;
				}

			}
			else
			{
				break;
			}
		}

		//top right diagonal
		x= i-1;
		y= j+1;		
		for(int iter =0; iter <8;iter++)
		{
			if(x>=0 && x<8 &&y>=0 && y<8)
			{
				if(numberboard[x][y]==0)
				{
					legalmoves[count +1] = x;
					legalmoves[count +2] = y;
					count+=2;
					x-=1;
					y+=1;
				}
				else if(numberboard[x][y] < 10)
				{
					legalmoves[count +1] = x;
					legalmoves[count +2] = y;
					count+=2;
					x-=1;
					y-=1;
					break;
				}
				else
				{
					break;
				}

			}
			else
			{
				break;
			}
		}

		//bottom left diagonal
		x = i+1;
		y = j-1;
		for(int iter =0; iter <8;iter++)
		{
			if(x>=0 && x<8 &&y>=0 && y<8)
			{
				if(numberboard[x][y]==0)
				{
					legalmoves[count +1] = x;
					legalmoves[count +2] = y;
					count+=2;
					x+=1;
					y-=1;
				}
				else if(numberboard[x][y] < 10)
				{
					legalmoves[count +1] = x;
					legalmoves[count +2] = y;
					count+=2;
					x-=1;
					y-=1;
					break;
				}
				else
				{
					break;
				}

			}
			else
			{
				break;
			}
		}
	
		//bottom right diagonal
		x=i+1;
		y=j+1;
		for(int iter =0; iter <8;iter++)
		{
			if(x>=0 && x<8 &&y>=0 && y<8)
			{
				if(numberboard[x][y]==0)
				{
					legalmoves[count +1] = x;
					legalmoves[count +2] = y;
					count+=2;
					x+=1;
					y+=1;
				}
				else if(numberboard[x][y] < 10)
				{
					legalmoves[count +1] = x;
					legalmoves[count +2] = y;
					count+=2;
					x-=1;
					y-=1;
					break;
				}
				else
				{
					break;
				}

			}
			else
			{
				break;
			}
		}
		count = count/2;
		legalmoves[0] = count;
	}
	else if(piece==1)//white king
	{
		count =0;
		int x =i-1;
		int y  = j-1;
		if(x>=0 && x<8 &&y>=0 && y<8 &&( numberboard[x][y]==0|| numberboard[x][y] >10))
		{
			legalmoves[count +1] = x;
			legalmoves[count +2] = y;
			count+=2;
		}
		x= i+1;
		y= j-1;
		if(x>=0 && x<8 &&y>=0 && y<8 && (numberboard[x][y]==0 || numberboard[x][y] >10))
		{
			legalmoves[count +1] = x;
			legalmoves[count +2] = y;
			count+=2;
		}

		x= i-1;
		y =j+1;
		//if(x>=0 && x<8 &&y>=0 && y<8 && numberboard[x][y]==0)
		if(x>=0 && x<8 &&y>=0 && y<8 && (numberboard[x][y]==0 || numberboard[x][y] >10))
		{
			legalmoves[count +1] = x;
			legalmoves[count +2] = y;
			count+=2;			
		}

		x= i+1;
		y= j+1;
//		if(x>=0 && x<8 &&y>=0 && y<8 && numberboard[x][y]==0)
		if(x>=0 && x<8 &&y>=0 && y<8 && (numberboard[x][y]==0 || numberboard[x][y] >10))
		{
			legalmoves[count +1] = x;
			legalmoves[count +2] = y;
			count+=2;			
		}
		
		x =i-1;
		y =j;
//		if(x>=0 && x<8 &&y>=0 && y<8 && numberboard[x][y]==0)
		if(x>=0 && x<8 &&y>=0 && y<8 && (numberboard[x][y]==0 || numberboard[x][y] >10))
		{
			legalmoves[count +1] = x;
			legalmoves[count +2] = y;
			count+=2;			
		}
		
		x= i+1;
		y= j;
//		if(x>=0 && x<8 &&y>=0 && y<8 && numberboard[x][y]==0)
		if(x>=0 && x<8 &&y>=0 && y<8 && (numberboard[x][y]==0 || numberboard[x][y] >10))
		{
			legalmoves[count +1] = x;
			legalmoves[count +2] = y;
			count+=2;			
		}
		x =i;
		y= j-1;
//		if(x>=0 && x<8 &&y>=0 && y<8 && numberboard[x][y]==0)
		if(x>=0 && x<8 &&y>=0 && y<8 && (numberboard[x][y]==0 || numberboard[x][y] >10))
		{
			legalmoves[count +1] = x;
			legalmoves[count +2] = y;
			count+=2;			
		}

		x=i;
		y= j+1;
//		if(x>=0 && x<8 &&y>=0 && y<8 && numberboard[x][y]==0)
		if(x>=0 && x<8 &&y>=0 && y<8 && (numberboard[x][y]==0 || numberboard[x][y] >10))
		{
			legalmoves[count +1] = x;
			legalmoves[count +2] = y;
			count+=2;
		}

		//castle

		//rightside
		int check =0;
		if(wcastleright == 1)
		{
			for(int tempi=5; tempi<7; tempi++)//right row
			{
				if(numberboard[i][tempi] != 0)
				{
					check =1;
					break;
				}
			}
			if(check==0)
			{
			//left and right digonal and  horizontal

				if( leftd(1,i,j+1) && rightd(1,i,j+1) && leftd(1,i,j+2)&&rightd(1,i,j+2)&&horz(1,i,j+1)&&horz(1,i,j+2))
				{
					legalmoves[count+1] =i;
					legalmoves[count +2] = j+2;
					count+=2;
				}
			}
				//check =1;
		}
		check =0;
		if(wcastleleft ==1)//leftside
		{
			for(int tempi=3; tempi>0; tempi--)
			{
				if(numberboard[i][tempi] != 0)
				{
					check =1;
					break;
				}
			}
			
			if(check==0)
			{
				//left side
				if( leftd(1,i,j-1)&&rightd(1,i,j-1)&&leftd(1,i,j-2)&&rightd(1,i,j-2)&&leftd(1,i,j-3)&&rightd(1,i,j-3)&&horz(1,i,j-1)&&horz(1,i,j-2)&&horz(1,i,j-3))
				{
					legalmoves[count+1] =i;
					legalmoves[count +2] = j-2;
					count+=2;
				}
			}
		}
		count = count/2 ;
		legalmoves[0] =count;
	}
	else if(piece==11)//blk king
	{
		int x =i-1;
		int y  = j-1;
		if(x>=0 && x<8 &&y>=0 && y<8 && (numberboard[x][y]==0 || numberboard[x][y]<10))
		{
			legalmoves[count +1] = x;
			legalmoves[count +2] = y;
			count+=2;
		}
		x= i+1;
		y= j-1;
//		if(x>=0 && x<8 &&y>=0 && y<8 && numberboard[x][y]==0)
		if(x>=0 && x<8 &&y>=0 && y<8 && (numberboard[x][y]==0 || numberboard[x][y]<10))
		{
			legalmoves[count +1] = x;
			legalmoves[count +2] = y;
			count+=2;
		}
		x= i-1;
		y =j+1;
//		if(x>=0 && x<8 &&y>=0 && y<8 && numberboard[x][y]==0)
		if(x>=0 && x<8 &&y>=0 && y<8 && (numberboard[x][y]==0 || numberboard[x][y]<10))
		{
			legalmoves[count +1] = x;
			legalmoves[count +2] = y;
			count+=2;
		}

		x= i+1;
		y= j+1;
//		if(x>=0 && x<8 &&y>=0 && y<8 && numberboard[x][y]==0)
		if(x>=0 && x<8 &&y>=0 && y<8 && (numberboard[x][y]==0 || numberboard[x][y]<10))
		{
			legalmoves[count +1] = x;
			legalmoves[count +2] = y;
			count+=2;
		}
		x =i-1;
		y =j;
//		if(x>=0 && x<8 &&y>=0 && y<8 && numberboard[x][y]==0)
		if(x>=0 && x<8 &&y>=0 && y<8 && (numberboard[x][y]==0 || numberboard[x][y]<10))
		{
			legalmoves[count +1] = x;
			legalmoves[count +2] = y;
			count+=2;
		}
		x= i+1;
		y= j;
//		if(x>=0 && x<8 &&y>=0 && y<8 && numberboard[x][y]==0)
		if(x>=0 && x<8 &&y>=0 && y<8 && (numberboard[x][y]==0 || numberboard[x][y]<10))
		{
			legalmoves[count +1] = x;
			legalmoves[count +2] = y;
			count+=2;
		}
		x =i;
		y= j-1;
//		if(x>=0 && x<8 &&y>=0 && y<8 && numberboard[x][y]==0)
		if(x>=0 && x<8 &&y>=0 && y<8 && (numberboard[x][y]==0 || numberboard[x][y]<10))
		{
			legalmoves[count +1] = x;
			legalmoves[count +2] = y;
			count+=2;
		}

		x=i;
		y= j+1;
//		if(x>=0 && x<8 &&y>=0 && y<8 && numberboard[x][y]==0)
		if(x>=0 && x<8 &&y>=0 && y<8 && (numberboard[x][y]==0 || numberboard[x][y]<10))
		{
			legalmoves[count +1] = x;
			legalmoves[count +2] = y;
			count+=2;
		}
		//


		//black castle
		//rightside
		int check =0;
		if(bcastleright == 1)
		{
			for(int tempi=5; tempi<7; tempi++)//right row
			{
				if(numberboard[i][tempi] != 0)
				{
					check =1;
					break;
				}
			}
			if(check==0)
			{
			//left and right digonal and  horizontal
				//int test =check(0,numberboard);
				if(leftd(0,i,j+1) && rightd(0,i,j+1) && leftd(0,i,j+2)&&rightd(0,i,j+2)&&horz(0,i,j+1)&&horz(0,i,j+2))
				{
					legalmoves[count+1] =i;
					legalmoves[count +2] = j+2;
					count+=2;
				}
			}
				//check =1;
		}
		check =0;
		if(bcastleleft ==1)//leftside
		{
			for(int tempi=3; tempi>0; tempi--)
			{
				if(numberboard[i][tempi] != 0)
				{
					check =1;
					break;
				}
			}

			if(check==0)
			{
				//int test =check(0,numberboard);	//left side
				if(leftd(0,i,j-1)&&rightd(0,i,j-1)&&leftd(0,i,j-2)&&rightd(0,i,j-2)&&leftd(0,i,j-3)&&rightd(0,i,j-3)&&horz(0,i,j-1)&&horz(0,i,j-2)&&horz(0,i,j-3))
				{
					legalmoves[count+1] =i;
					legalmoves[count +2] = j-2;
					count+=2;
				}
			}
		}
		count = count/2;
		legalmoves[0] =count;
	}
	else if(piece==2)//white queen
	{
		//bishop
		int x =i-1;
		int y  = j-1;
		count =0;
		for(int iter =0; iter <8;iter++)
		{
			if(x>=0 && x<8 &&y>=0 && y<8)
			{
				if(numberboard[x][y]==0)
				{
					legalmoves[count +1] = x;
					legalmoves[count +2] = y;
					count+=2;
					x-=1;
					y-=1;
				}
				else if(numberboard[x][y] > 10)
				{
					legalmoves[count +1] = x;
					legalmoves[count +2] = y;
					count+=2;
					x-=1;
					y-=1;
					break;
				}
				else
				{
					break;
				}

			}
			else
			{
				break;
			}
		}

		//top right diagonal
		x= i-1;
		y= j+1;
		for(int iter =0; iter <8;iter++)
		{
			if(x>=0 && x<8 &&y>=0 && y<8)
			{
				if(numberboard[x][y]==0)
				{
					legalmoves[count +1] = x;
					legalmoves[count +2] = y;
					count+=2;
					x-=1;
					y+=1;
				}
				else if(numberboard[x][y] > 10)
				{
					legalmoves[count +1] = x;
					legalmoves[count +2] = y;
					count+=2;
					x-=1;
					y-=1;
					break;
				}		
				else
				{
					break;
				}

			}
			else
			{
				break;
			}
		}

		//bottom left diagonal
		x = i+1;
		y = j-1;
		for(int iter =0; iter <8;iter++)
		{
			if(x>=0 && x<8 &&y>=0 && y<8)
			{
				if(numberboard[x][y]==0)
				{
					legalmoves[count +1] = x;
					legalmoves[count +2] = y;
					count+=2;
					x+=1;
					y-=1;
				}
				else if(numberboard[x][y] > 10)
				{
					legalmoves[count +1] = x;
					legalmoves[count +2] = y;
					count+=2;
					x-=1;
					y-=1;
					break;
				}
				else
				{
					break;
				}

			}
			else
			{
				break;
			}
		}
		//bottom right diagonal
		x=i+1;
		y=j+1;
		for(int iter =0; iter <8;iter++)
		{
			if(x>=0 && x<8 &&y>=0 && y<8)
			{
				if(numberboard[x][y]==0)
				{
					legalmoves[count +1] = x;
					legalmoves[count +2] = y;
					count+=2;
					x+=1;
					y+=1;
				}
				else if(numberboard[x][y] > 10)
				{
					legalmoves[count +1] = x;
					legalmoves[count +2] = y;
					count+=2;
					x-=1;
					y-=1;
					break;
				}
				else
				{
					break;
				}

			}
			else
			{
				break;
			}
		}


		//legalmoves[0] = count;


		//rook
		for(int iteri =i+1; iteri< 8 ;iteri++)//going up
		{
			if(numberboard[iteri][j] == 0)
			{
				legalmoves[count +1] = iteri;
				legalmoves[count +2] = j;
				count+=2;
				continue;
			}
			if(numberboard[iteri][j] < 10)
			{
				break;
			}
			else//opponent pieces
			{
				legalmoves[count +1] = iteri;
				legalmoves[count +2] = j;
				count+=2;
				break;
			}
		}
		for(int iteri =i-1; iteri >=0; iteri--)//going down
		{
//			if(numberboard[iteri][j] < 10)
			if(numberboard[iteri][j] == 0)
			{
				legalmoves[count +1] = iteri;
				legalmoves[count +2] = j;
				count+=2;
				continue;
			}
			if(numberboard[iteri][j] < 10)
			{
				break;
			}
			else
			{
				legalmoves[count +1] = iteri;
				legalmoves[count +2] = j;
				count+=2;
				break;
			}
		}

		for(int iterj =j+1; iterj <8; iterj++)//right
		{

			if(numberboard[i][iterj] ==0)
			{
				legalmoves[count +1] = i;
				legalmoves[count +2] = iterj;
				count+=2;
				continue;
			}
			if(numberboard[i][iterj] < 10)
			{
				break;
			}
			else
			{
				legalmoves[count +1] = i;
				legalmoves[count +2] = iterj;
				count+=2;
				break;
			}
		}
		for(int iterj =j-1; iterj >=0; iterj--)//left
		{
//			if(numberboard[i][iterj] < 10)
			if(numberboard[i][iterj] ==0)
			{
				legalmoves[count +1] = i;
				legalmoves[count +2] = iterj;
				count +=2;
				continue;
			}
			if(numberboard[i][iterj] < 10)
			{
				break;
			}
			else
			{
				legalmoves[count +1] = i;
				legalmoves[count +2] = iterj;
				count +=2;
				break;
			}
		}

		count = count/2;
		legalmoves[0] =count;
		
//		legalmoves[0] =count;

	}
	else if(piece==12)//blk queen
	{
		//bishop
		int x =i-1;
		int y  = j-1;
		count =0;
		for(int iter =0; iter <8;iter++)
		{
			if(x>=0 && x<8 &&y>=0 && y<8)
			{
				if(numberboard[x][y]==0)
				{
					legalmoves[count +1] = x;
					legalmoves[count +2] = y;
					count+=2;
					x-=1;
					y-=1;
				}
				else if(numberboard[x][y] < 10)
				{
					legalmoves[count +1] = x;
					legalmoves[count +2] = y;
					count+=2;
					x-=1;
					y-=1;
					break;
				}
				else
				{
					break;
				}

			}
			else
			{
				break;
			}
		}

		//top right diagonal
		x= i-1;
		y= j+1;
		for(int iter =0; iter <8;iter++)
		{
			if(x>=0 && x<8 &&y>=0 && y<8)
			{
				if(numberboard[x][y]==0)
				{
					legalmoves[count +1] = x;
					legalmoves[count +2] = y;
					count+=2;
					x-=1;
					y+=1;
				}
				else if(numberboard[x][y] < 10)
				{
					legalmoves[count +1] = x;
					legalmoves[count +2] = y;
					count+=2;
					x-=1;
					y-=1;
					break;
				}
				else
				{
					break;
				}

			}
			else
			{
				break;
			}
		}

		//bottom left diagonal
		x = i+1;
		y = j-1;
		for(int iter =0; iter <8;iter++)
		{
			if(x>=0 && x<8 &&y>=0 && y<8)
			{
				if(numberboard[x][y]==0)
				{
					legalmoves[count +1] = x;
					legalmoves[count +2] = y;
					count+=2;
					x+=1;
					y-=1;
				}
				else if(numberboard[x][y] < 10)
				{
					legalmoves[count +1] = x;
					legalmoves[count +2] = y;
					count+=2;
					x-=1;
					y-=1;
					break;
				}
				else
				{
					break;
				}

			}
			else
			{
				break;
			}
		}
	
		//bottom right diagonal
		x=i+1;
		y=j+1;
		for(int iter =0; iter <8;iter++)
		{
			if(x>=0 && x<8 &&y>=0 && y<8)
			{
				if(numberboard[x][y]==0)
				{
					legalmoves[count +1] = x;
					legalmoves[count +2] = y;
					count+=2;
					x+=1;
					y+=1;
				}
				else if(numberboard[x][y] < 10)
				{
					legalmoves[count +1] = x;
					legalmoves[count +2] = y;
					count+=2;
					x-=1;
					y-=1;
					break;
				}
				else
				{
					break;
				}

			}
			else
			{
				break;
			}
		}
	//	legalmoves[0] = count;

		//legalmoves[0] = count;
		
//rook
		for(int iteri =i+1; iteri< 8 ;iteri++)//going up
		{
			if(numberboard[iteri][j] ==0)
			{
				legalmoves[count +1] = iteri;
				legalmoves[count +2] = j;
				count+=2;
				continue;
			}
			if(numberboard[iteri][j] > 10)
			{
				break;
			}
			else
			{
				legalmoves[count +1] = iteri;
				legalmoves[count +2] = j;
				count+=2;
				break;
			}
		}
		for(int iteri =i-1; iteri >=0; iteri--)//going down
		{
			if(numberboard[iteri][j] ==0)
			{
				legalmoves[count +1] = iteri;
				legalmoves[count +2] = j;
				count+=2;
				continue;
			}
			if(numberboard[iteri][j] > 10)
			{
				break;
			}
//			else if(numberboard[iteri][j] < 10)
			else
			{
				legalmoves[count +1] = iteri;
				legalmoves[count +2] = j;
				count+=2;
				break;
			}
		}

		for(int iterj =j+1; iterj <8; iterj++)//right
		{
			if(numberboard[i][iterj]==0)
			{
				legalmoves[count +1] = i;
				legalmoves[count +2] = iterj;
				count+=2;
				continue;
			}
			
			if(numberboard[i][iterj] > 10)
			{
				break;
			}
			else
			{
				legalmoves[count +1] = i;
				legalmoves[count +2] = iterj;
				count+=2;
				break;
			}
		}

		for(int iterj =j-1; iterj >=0; iterj--)//left
		{
			if(numberboard[i][iterj] > 10)
			{
				break;
			}
//			if(numberboard[i][iterj] < 10)
			else if(numberboard[i][iterj] < 10 &&numberboard[i][iterj] !=0)
			{
				legalmoves[count +1] = i;
				legalmoves[count +2] = iterj;
				count +=2;
				break;
			}
			legalmoves[count +1] = i;
			legalmoves[count +2] = iterj;
			count +=2;
		}

		count = count/2;
		legalmoves[0] =count;

		//rook
	}
	else
	{
	}
}


void findreply(int whtblk, int replyarr[], int numb[][8])//white moves
{
	int cot =0;
	if(whtblk==1)//white
	{
		for(int i=0; i< 8;i++)
		{
			int (&fullarr)[8]= numb[i];
			for(int j=0; j<8;j++)
			{
				int piecenum = fullarr[j];
				if(piecenum <10 && piecenum>0)//white
				{
					int arr[512];
					arr[0] =0;
					Rules(piecenum, i, j, arr);
					//put into the replyarr
					for(int k=0;k<arr[0];k++)
					{
						int start =cot*4;
						replyarr[start +1]= i;
						replyarr[start+ 2]= j;
						replyarr[start +3] = arr[k*2+1];
						replyarr[start +4] = arr[k*2 +2];
						cot+=1;
					}
				}
			}

		}
	}
	else
	{
		for(int i=0; i< 8;i++)
		{
			int (&fullarr)[8]= numb[i];
			for(int j=0; j<8;j++)
			{
				int piecenum =fullarr[j];
				if(piecenum >10)
				{
					int arr[512];
					arr[0] =0;
					Rules(piecenum, i, j, arr);
					//put into the replyarr
					for(int k=0;k<arr[0];k++)
					{
						int start = cot*4;
						replyarr[start +1]= i;
						replyarr[start+ 2]= j;
						replyarr[start +3] = arr[k*2+1];
						replyarr[start +4] = arr[k*2 +2];
						cot+=1; 
					}
				}
			}

		}

	}
	replyarr[0] = cot;
}

int check(int whtblk, int boardcopy[][8])
{
        if(whtblk==0)
        {
		//scan all white pieces and see who attacks kings
		int replyar[1024];
		findreply(1, replyar, boardcopy);//white moves		
		for(int i=0; i<replyar[0];i++)
		{
			int start = i*4;
			if(boardcopy[replyar[start+3]][replyar[start+4]]==11)
			{
				return 1;//king is in check
			}

		}
//                for(int i =0; i<8; i++)
//                {
//                        //std::cout<<"\n";
//                        for(int j=0; j<8;j++)
//                        {
//				if(boardcopy[i][j]==11)
//				{
//					//std::cout<<"\nOut of the works\n";
//
//					//more complicated than that
//
//					//check all of white pieces to see if they are in check
//
//					if(horz(0,i,j)&&leftd(0,i,j)&&rightd(0,i,j))
//					{
//						return 0;
//					}
//					return 1;
//				}
//                        }
//                        //std::cout<<"\n";
//                }
                return 0;//In check
        }
        else
        {
		int replyar[1024];
		findreply(0, replyar, boardcopy);//white moves
		for(int i=0; i<replyar[0];i++)
		{
			int start = i*4;
			if(boardcopy[replyar[start+3]][replyar[start+4]]==1)
			{
				return 1;//king is in check
			}

		}
                return 0;//not in check
        }
}


int Transposition(string representation)
{
	//representation is the key
	//std::cout <<"representation: "<<representation<<"\n";
	for(int i=0; i<transpositioncount; i++)
	{
		if(transpositionarray[i]==representation)
		{
			//takcount+=1;
			return 1;
		}
	}
	transpositionarray[transpositioncount] = representation;
	transpositioncount +=1;
	//create something like a dictionary that deletes itself after minimax is called
	//make a hash table to store it
	//return 0 if it's not there
	//return 1  if it's there
	return 0;
}


string changer(string input, int position, int insert, int word)//add rook castle
{

	int numberofdashes =0;
	int lengthofcover =1;

	if(word>10)
	{
		lengthofcover +=1;
	}

	for(int i=0; i<144; i++)
	{
		if(input[i]== '-')
		{
			numberofdashes +=1;
		}
		if(input[i]=='-' && numberofdashes==position)
		{
			string newstuff ="";
			newstuff = input.substr(0, i+1);
			//std::cout <<"Cout :  "<<newstuff<<"\n";
			newstuff+= std::to_string(insert)+ input.substr(i+lengthofcover+1);
			//std::cout <<"end of this: "<< newstuff<<"\n";
			return newstuff;
		}
	}
	return "alpha";
}
//break
int minimax(int numberb[][8], int whtblk, int currdepth, int depth, int replyarr[], double alpha, double beta)
{
//	int boardcopy[8][8];
//	for(int i=0; i<8;i++)
//	{
//		for(int j=0; j<8; j++)
//		{
//			boardcopy[i][j] =numberb[i][j];//copy done
//		}
//	}


	if(currdepth==0)
	{
		fakewcastleleft = wcastleleft;
		fakewcastleright = wcastleright;
		fakebcastleleft = bcastleleft;
		fakebcastleright = bcastleright;
	}

//	int minormax = -13;
//	if(currdepth %2 ==0)
//	{
//		minormax =13;//might be used later on
//	}
//	if(currdepth==0)
//	{
//		std::cout<<" The START  of minimax "<<"\n";
//		Aprintf(numberb);
//	}
	if(whtblk==0)//black to move
	{
		//here is the max we pick from
		int replyar[512];
		findreply(0, replyar, numberb);
		int bestindices[512];//besin= best index
		int maxcount =0;
		if(currdepth==depth)//straight calculation
		{
			int max =0;
			//return max
			for(int i=0; i<replyar[0]; i++)
			{
				int start =i*4;
				int lcastle =0;
				int rcastle =0;
				int endfile = replyar[start+3];
				int endrank = replyar[start+4];
				int startfile = replyar[start+1];
				int startrank = replyar[start+2];
				if(numberb[startfile][startrank] ==11 &&(endrank-startrank ==2))//rightcastle
				{
					rcastle =1;
					numberb[startfile][endrank-1]= numberb[startfile][endrank+1];
					numberb[startfile][endrank+1]=0;
				}
				if(numberb[startfile][startrank] ==11 &&(endrank-startrank ==-2))//leftcastle
				{
					lcastle =1;
					numberb[startfile][endrank+1]= numberb[startfile][0];
					numberb[startfile][0]=0;
				}
				int rem = numberb[endfile][endrank];
				numberb[endfile][endrank] = numberb[startfile][startrank];
				numberb[startfile][startrank] = 0;
				int total =0;
				for(int j=0; j< 8; j++)//calculation
				{
					for(int k=0; k<8; k++)
					{
						total += shorten(numberb[j][k]);
					}
				}
				//end
				if(total>=max)
				{
					max =total;
				}
				//change back
				if(rcastle==1)
				{
					numberb[startfile][endrank+1]= numberb[startfile][endrank-1];
					numberb[startfile][endrank-1]= 0;
				}
				if(lcastle==1)
				{
					numberb[startfile][0]= 	numberb[startfile][endrank+1];
					numberb[startfile][endrank+1]= 0;
				}
				numberb[startfile][startrank] = numberb[endfile][endrank];
				numberb[endfile][endrank] = rem;
			}
			//setting the array right
			return max;//maximum
		}
		//check different legal moves and make them
		//pass it in
		int max= -500;
		//string below
		string firststring ="";
		for(int i =0; i<8; i++)
		{
			for(int j=0; j<8;j++)
			{
				firststring+= std::to_string(numberboard[i][j]);
				//if(j==7){continue;}
				firststring +="-";
			}
		}
		for(int i=0; i<replyar[0]; i++)
		{
			//Aprintf(numberb);
			totalcount +=1;
			int start =i*4;
			int lcastle =0;
			int rcastle =0;
			int endfile = replyar[start+3];
			int endrank = replyar[start+4];
			int startfile = replyar[start+1];
			int startrank = replyar[start+2];
//			string loopstring = firststring;//loop-string
			if(numberb[startfile][startrank] ==11 &&(endrank-startrank ==2))//rightcastle
			{
				rcastle =1;
//				loopstring = changer(loopstring, (startfile*8)+startrank, 0, numberb[startfile][startrank]);//changing string
//				loopstring = changer(loopstring, (endfile*8)+endrank, numberb[startfile][startrank], numberb[endfile][endrank]);
//				//white rightside rook exchange
//				loopstring = changer(loopstring, (startfile*8)+endrank-1, numberb[startfile][endrank+1], numberb[startfile][endrank-1]);
//				loopstring = changer(loopstring, (startfile*8)+endrank+1, 0, numberb[startfile][endrank+1]);
				numberb[startfile][endrank-1]= numberb[startfile][endrank+1];
				numberb[startfile][endrank+1]=0;
				//goto AFTERCHANGE;
			}
			if(numberb[startfile][startrank] ==11 &&(endrank-startrank ==-2))//leftcastle
			{
				lcastle =1;
//				loopstring = changer(loopstring, (startfile*8)+startrank, 0, numberb[startfile][startrank]);//changing string
//				loopstring = changer(loopstring, (endfile*8)+endrank, numberb[startfile][startrank], numberb[endfile][endrank]);
//				loopstring = changer(loopstring, (startfile*8)+endrank+1, numberb[startfile][0], numberb[startfile][endrank+1]);
//				loopstring = changer(loopstring, (startfile*8), 0, numberb[startfile][0]);
				numberb[startfile][endrank+1]= numberb[startfile][0];
				numberb[startfile][0]=0;
				//goto AFTERCHANGE;
			}
//			loopstring = changer(loopstring, (startfile*8)+startrank, 0, numberb[startfile][startrank]);//changing string
//			loopstring = changer(loopstring, (endfile*8)+endrank, numberb[startfile][startrank], numberb[endfile][endrank]);
//			AFTERCHANGE:
			int rem = numberb[endfile][endrank];
			numberb[endfile][endrank] = numberb[startfile][startrank];
			numberb[startfile][startrank] =0;
//			if(Transposition(loopstring)==1)//add loop
//			{
//				if(rcastle==1)//right castle
//				{
//					numberb[startfile][endrank+1]= numberb[startfile][endrank-1];
//					numberb[startfile][endrank-1]= 0;
//				}
//				if(lcastle==1)//left castle
//				{
//					numberb[startfile][0]= 	numberb[startfile][endrank+1];
//					numberb[startfile][endrank+1]= 0;
//				}
//				numberb[startfile][startrank] = numberb[endfile][endrank];
//				numberb[endfile][endrank] =rem;
//				continue;
//			}
			//should account for castling
			int score = minimax(numberb, 1, currdepth+1, depth, replyar, alpha, beta);//
			if(score >= max)
			{
				max = score;
			}
			if(currdepth==0 && score>=max)
			{
				bestindices[maxcount] =i;
				maxcount+=1;
			}
			if(score> alpha)
			{
				alpha= (double) score;
			}
			if(beta<=alpha && currdepth>0)
			{
				//break;			//alpha-beta-prune
			}
			//should deaccount for castling
			if(rcastle==1)//right castle
			{
				numberb[startfile][endrank+1]= numberb[startfile][endrank-1];
				numberb[startfile][endrank-1]= 0;
			}
			if(lcastle==1)//left castle
			{
				numberb[startfile][0]= 	numberb[startfile][endrank+1];
				numberb[startfile][endrank+1]= 0;
			}
			numberb[startfile][startrank] = numberb[endfile][endrank];
			numberb[endfile][endrank] =rem;
		}

		if(currdepth==0)
		{
			//maxcount =1;
			for(int k=0; k <maxcount;k++)
			{
				//these two replyarr $ replyar are different
				replyarr[k*4 +1] = replyar[bestindices[k]*4 +1];
				replyarr[k*4 +2] = replyar[bestindices[k]*4 +2];
				replyarr[k*4 +3] = replyar[bestindices[k]*4 +3];
				replyarr[k*4 +4] = replyar[bestindices[k]*4 +4];
			}
			replyarr[0] = maxcount;
			//return castlings rights
			wcastleleft = fakewcastleleft;
			wcastleright = fakewcastleright;
			bcastleleft= fakebcastleleft;
			bcastleright= fakebcastleright;
			//std::cout<<"tcount: "<<takcount<<"\n";
			transpositioncount=0;
		}
		return max;
	}
	else//white
	{
//		if(currdepth==1)
//		{
//
//			std::cout<<" The START  of minimax 1 "<<"\n";
//			Aprintf(numberb);
//		}
		int replyar[512];
		int min = 1000;
		findreply(1, replyar, numberb);//white moves
		if(currdepth==depth)
		{
			//return min
//			for(int i=0; i<replyar[0]; i++)
//			{
//				int whtcastlleft =0;
//				int whtcastlergt =0;
//				int start =i*4;
//				if(numberb[replyar[start+1]][replyar[start +2]] ==1 && ((replyar[start +4])-(replyar[start +2])==2))
//				{
//					whtcastlergt =1;
//					//change rook position;
//				}
//				int rem = numberb[replyar[start+3]][replyar[start +4]];//change
//				numberb[replyar[start+3]][replyar[start +4]] = numberb[replyar[start+1]][replyar[start +2]];
//				numberb[replyar[start+1]][replyar[start +2]] = 0;
//				int total =0;
//				//should account for castling above
//
//				for(int j=0; j< 8; j++)//calculation
//				{
//					for(int k=0; k<8; k++)
//					{
//						total += shorten(numberb[j][k]);
//					}
//				}
//				//end
//				if(total<min)
//				{
//					min =total;
//				}
//				//change back
//				//should remove account of castling
//				numberb[replyar[start+1]][replyar[start +2]] = numberb[replyar[start+3]][replyar[start +4]];
//				numberb[replyar[start+3]][replyar[start +4]]= rem;
//			}
//			return min;//end
		}
			for(int i=0; i<replyar[0]; i++)
			{
				totalcount+=1;
				int start =i*4;
				int lcastle =0;
				int rcastle =0;
				int endfile = replyar[start+3];
				int endrank = replyar[start+4];
				int startfile = replyar[start+1];
				int startrank = replyar[start+2];
	//			string loopstring = secstring;
				if(numberb[startfile][startrank] ==1 &&(endrank-startrank ==2))//rightcastle
				{
					rcastle =1;
	//				loopstring = changer(loopstring, (startfile*8)+startrank, 0, numberb[startfile][startrank]);//changing string 
	//				loopstring = changer(loopstring, (endfile*8)+endrank, numberb[startfile][startrank], numberb[endfile][endrank]);
	//				loopstring = changer(loopstring, (startfile*8)+endrank-1, numberb[startfile][endrank+1], numberb[startfile][endrank-1]);
	//				loopstring = changer(loopstring, (startfile*8)+endrank+1, 0, numberb[startfile][endrank+1]);
					numberb[startfile][endrank-1]= numberb[startfile][endrank+1];
					numberb[startfile][endrank+1]=0;
	//				goto AFTERCASTLE;
				}
				if(numberb[startfile][startrank] ==1 &&(endrank-startrank ==-2))//leftcastle
				{
					lcastle =1;
	//				loopstring = changer(loopstring, (startfile*8)+startrank, 0, numberb[startfile][startrank]);//changing string 
	//				loopstring = changer(loopstring, (endfile*8)+endrank, numberb[startfile][startrank], numberb[endfile][endrank]);
	//				loopstring = changer(loopstring, (startfile*8)+endrank+1, numberb[startfile][0], numberb[startfile][endrank+1]);
	//				loopstring = changer(loopstring, (startfile*8), 0, numberb[startfile][0]);
					numberb[startfile][endrank+1]= numberb[startfile][0];
					numberb[startfile][0]=0;
	//				goto AFTERCASTLE;
				}
	//			loopstring = changer(loopstring, (startfile*8)+startrank, 0, numberb[startfile][startrank]);//changing string 
	//			loopstring = changer(loopstring, (endfile*8)+endrank, numberb[startfile][startrank], numberb[endfile][endrank]);
	//			AFTERCASTLE:
				int rem = numberb[endfile][endrank];
				numberb[endfile][endrank] = numberb[startfile][startrank];
				numberb[startfile][startrank] = 0;
	//			if(Transposition(loopstring)==1)
	//			{
	//				if(rcastle==1)//right castle
	//				{
	//					numberb[startfile][endrank+1]= numberb[startfile][endrank-1];
	//					numberb[startfile][endrank-1]= 0;
	//				}
	//				if(lcastle==1)//left castle
	//				{
	//					numberb[startfile][0]= 	numberb[startfile][endrank+1];
	//					numberb[startfile][endrank+1]= 0;
	//				}
	//				numberb[startfile][startrank] = numberb[endfile][endrank];
	//				numberb[endfile][endrank] = rem;
	//				continue;
	//			}
				//should account for castling
				//white castling
				int whtcastlleft =0;
				int whtcastlergt =0;
				int total =  minimax(numberb, 0, currdepth+1, depth, replyar, alpha, beta);//recursive//end
				if(total<min)
				{
					min =total;
				}
				//change back
				//should remove account of castling

				//prune begin
				if(total<beta)
				{
					beta = (double) total;
				}
				if(beta<= alpha&& currdepth>0)
				{
					//break;			//alpha-beta-prune
				}

				//alpha-beta
				if(rcastle==1)//right castle
				{
					numberb[startfile][endrank+1]= numberb[startfile][endrank-1];
					numberb[startfile][endrank-1]= 0;
				}
				if(lcastle==1)//left castle
				{
					numberb[startfile][0]= 	numberb[startfile][endrank+1];
					numberb[startfile][endrank+1]= 0;
				}
				numberb[startfile][startrank] = numberb[endfile][endrank];
				numberb[endfile][endrank] = rem;
			}
		return min;//
		//return recursive call
	}

}
