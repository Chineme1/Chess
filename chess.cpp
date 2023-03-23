#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <ctime>
#include <chrono>
#include <string>

#include "engine.h"

using namespace std;
using namespace std::chrono;

struct Marker {
	public:
		int type;
		const char* color;
		int posx;
		int posy;
};
struct Piece {
	public:
		int type;
		int color; //0forblk //1forwht
		int posx; //x position
		int posy;  //y position
		int scoreofpiece; //might be a fleat
		const char* symbol; 

};
struct King : public Piece
{
};
struct Queen : public Piece
{
};
struct Rook : public Piece
{
};

struct Bishop : public Piece
{

};

struct Knight : public Piece
{
};

struct Pawn : public Piece
{
};

struct Piece hold[32];//struct array

//Pawn pieces
struct Pawn paw1;
struct Pawn paw2;
struct Pawn paw3;
struct Pawn paw4;
struct Pawn paw5;
struct Pawn paw6;
struct Pawn paw7;
struct Pawn paw8;

//blk Pawn pieces
struct Pawn pawb1;
struct Pawn pawb2;
struct Pawn pawb3;
struct Pawn pawb4;
struct Pawn pawb5;
struct Pawn pawb6;
struct Pawn pawb7;
struct Pawn pawb8;


//knight
struct Knight kni1;
struct Knight kni2;
//blk knight
struct Knight knib1;
struct Knight knib2;

//bishop
struct Bishop bis1;
struct Bishop bis2;

struct Bishop bisb1;
struct Bishop bisb2;

//rook
struct Rook roo1;
struct Rook roo2;

struct Rook roob1;
struct Rook roob2;

//Queen
struct Queen que;

struct Queen queb;

//king
struct King kin;
struct King kinb;

int legalMoves[128];

void printBoard( struct Marker Mark) {
	for(int i=0; i<8;i++) {
		cout<<"\t\t";
		if(i==0) {
			cout<<" ";
			for(int j=0; j<8;j++)
			{
				cout<<" -";
			}
			cout<<"\n\t\t";
		}
		cout<<"|" ;

		for (int j=1; j<9; j++) {
			int cont =0;
			for(int k=0; k<legalMoves[0]; k++) {
				int mov =  k*2;
				if(i==Mark.posx &&(j)==Mark.posy){continue;}
				if(i==legalMoves[1+mov]&&(j-1)==legalMoves[mov+2])
				{
					cout << " \u2612";
					cont=1;
					break;
				}
			}
			if(cont==1) {
				continue;
			}
			int rando =0;
			if(i == Mark.posx && j == Mark.posy) {
				cout << Mark.color;
				rando = 1 ;
			} else {
				for(int iter=0; iter<32;iter++) {
					if(hold[iter].posx==i && j==hold[iter].posy) {
						cout << hold[iter].symbol;
						rando = 1;
						if(hold[iter].symbol==" \u2659"){numberboard[i][j-1]=13;}
						else if(hold[iter].symbol== " \u265F"){numberboard[i][j-1]=3;}//whitepawn
						else if(hold[iter].symbol== " \u265E"){numberboard[i][j-1]=4;}//knight
						else if(hold[iter].symbol== " \u265D"){numberboard[i][j-1]=5;}//bishop
						else if(hold[iter].symbol== " \u265C"){numberboard[i][j-1]=6;}//rook
						else if(hold[iter].symbol== " \u265B"){numberboard[i][j-1]=2;}//queen
						else if(hold[iter].symbol== " \u265A"){numberboard[i][j-1]=1;}//king
						else if(hold[iter].symbol== " \u2655"){numberboard[i][j-1]=12;}//blk queen
						else if(hold[iter].symbol== " \u2654"){numberboard[i][j-1]=11;}//king
						else if(hold[iter].symbol== " \u2659"){numberboard[i][j-1]=13;}//pawn
						else if(hold[iter].symbol== " \u2656"){numberboard[i][j-1]=16;}//rook
						else if(hold[iter].symbol== " \u2658"){numberboard[i][j-1]=14;}//knight
						else if(hold[iter].symbol== " \u2657"){numberboard[i][j-1]=15;}//bishop
						break;
					}
				}
			}
			if(rando == 0){cout<< " \u0020";}
		}
		
		cout<<" |"<<endl;
		if(i == 7) {
			cout << "\t\t ";
			for(int j=0;j<8;j++) {
				cout <<" -";
			}
			cout << endl;
		}
	}
}

int main() {
	struct Piece first;
	paw1.symbol = " \u265F";//white pawn
	paw1.posx= 6;
	paw1.posy= 1;

	paw2.symbol = " \u265F";//white pawn
	paw2.posx =6;
	paw2.posy =2;

	paw3.symbol = " \u265F";//white pawn
	paw3.posx =6;
	paw3.posy =3;

	
	paw4.symbol = " \u265F";//white pawn
	paw4.posx =6;
	paw4.posy =4;
	

	paw5.symbol = " \u265F";//white pawn
	paw5.posx =6;
	paw5.posy =5;


	paw6.symbol = " \u265F";//white pawn
	paw6.posx =6;
	paw6.posy =6;


	paw7.symbol = " \u265F";//white pawn
	paw7.posx =6;
	paw7.posy =7;


	paw8.symbol = " \u265F";//white pawn
	paw8.posx =6;
	paw8.posy =8;


	//blk pawn
	pawb1.symbol = " \u2659";//b pawn
	pawb1.posx= 1;
	pawb1.posy= 1;

	pawb2.symbol = " \u2659";//b pawn
	pawb2.posx =1;
	pawb2.posy =2;


	pawb3.symbol = " \u2659";//b pawn
	pawb3.posx =1;
	pawb3.posy =3;

	
	pawb4.symbol = " \u2659";//b pawn
	pawb4.posx =1;
	pawb4.posy =4;
	
	pawb5.symbol = " \u2659";//b pawn
	pawb5.posx =1;
	pawb5.posy =5;


	pawb6.symbol = " \u2659";//b pawn
	pawb6.posx =1;
	pawb6.posy =6;


	pawb7.symbol = " \u2659";//b pawn
	pawb7.posx =1;
	pawb7.posy =7;

	pawb8.symbol = " \u2659";//b pawn
	pawb8.posx =1;
	pawb8.posy =8;

	//knight
	kni1.symbol =" \u265E";//white knight
	kni1.posx = 7;
	kni1.posy = 2;

	kni2.symbol =" \u265E";//white knight
	kni2.posx = 7;
	kni2.posy = 7;

	knib1.symbol = " \u2658";//black knight
	knib1.posx = 0;
	knib1.posy = 2;
	
	knib2.symbol = " \u2658";//black knight
	knib2.posx = 0;
	knib2.posy = 7;

	//bishop
	bis1.symbol = " \u265D";//white bishop
	bis1.posx = 7;
	bis1.posy =3;

	bis2.symbol = " \u265D";//white bishop
	bis2.posx = 7;
	bis2.posy =6;

	bisb1.symbol = " \u2657";//black bishop
	bisb1.posx = 0;
	bisb1.posy =3;

	bisb2.symbol = " \u2657";//black bishop
	bisb2.posx = 0;
	bisb2.posy =6;
	//rook
	roo1.symbol=" \u265C";//white rook
	roo1.posx = 7;
	roo1.posy=1;

	roo2.symbol=" \u265C";//white rook
	roo2.posx = 7;
	roo2.posy=8;

	roob1.symbol = " \u2656";//black rook
	roob1.posx = 0;
	roob1.posy =1;
	
	roob2.symbol = " \u2656";//black rook
	roob2.posx = 0;
	roob2.posy =8;

	//queen
	que.symbol= " \u265B";//white queen
	que.posx= 7;
	que.posy =4;

	queb.symbol= " \u2655";//black queen
	queb.posx = 0;
	queb.posy = 4;

	//king
	kin.symbol= " \u265A";//white king
	kin.posx = 7;
	kin.posy = 5;

	kinb.symbol= " \u2654";//black king
	kinb.posx = 0;
	kinb.posy =5;
	
	hold[0] =paw1;
	hold[1] =paw2;
	hold[2] =paw3;
	hold[3] =paw4;
	hold[4] =paw5;
	hold[5] =paw6;
	hold[6] =paw7;
	hold[7] =paw8;
	
	hold[8] =pawb1;
	hold[9] =pawb2;
	hold[10] =pawb3;
	hold[11] =pawb4;
	hold[12] =pawb5;
	hold[13] =pawb6;
	hold[14] =pawb7;
	hold[15] =pawb8;
//knight
	hold[16] = kni1;
	hold[17] = kni2;

	hold[18] = knib1;
	hold[19] = knib2;
//bishop
	hold[20] = bis1;
	hold[21] =bis2;

	hold[22] = bisb1;
	hold[23] = bisb2;
//rook
	hold[24] = roo1;
	hold[25] =roo2;

	hold[26] = roob1;
	hold[27] = roob2;

//QueenBNBMagnetAlarms
	hold[28] = que;
	hold[29] = queb;

//King
	hold[30] = kin;
	hold[31] = kinb;

	cout<<"\tTo play press:\n"<<"\tw: up\n"<<"\ts: down\n"<<"\ta: left\n"<<"\td: down\n";
	struct Marker Mark;
	Mark.color = " \u2610";//x-marker
	Mark.posx = 4;
	Mark.posy = 4;
	int engineToMove = false;

	while(true) {
	START:
		srand((unsigned) time(NULL));
		int random = rand();
		if (engineToMove == true) {
			cout<<"I'm thinking of a response with my computer brain\n.... Give me a second\n";
			cout<<"....................................................\n";
			int replyarr[1024];
			double alpha = -INFINITY;
			double beta = INFINITY;

			uint64_t starttime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

			minimax(numberboard, 0, 0, 4, replyarr,alpha, beta);

			uint64_t endtime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
			cout << "Engine runtime: "<< ((float)(endtime-starttime)) / 1000 <<"\n";

			int val = replyarr[0];
			int inside = 0;
			int checkmate = 0;
			int totpiececount = movecount(numberboard);
			std::cout<<"\nCheck  " << check(0, numberboard) <<"\n";
			if(check(0, numberboard)==1)//blk king in check
			{
				checkmate =1;
				for(int i= replyarr[0]-1; i>=0; i--)
				{
					int rem = numberboard[replyarr[i*4 +3]][replyarr[i*4 +4]];
					numberboard[replyarr[i*4+3]][replyarr[i*4+4]] = numberboard[replyarr[i*4 +1]][replyarr[i*4+2]];
					numberboard[replyarr[i*4 +1]][replyarr[i*4+2]] = 0;
					if(check(0, numberboard) == 0)
					{
						checkmate =0;
						numberboard[replyarr[i*4 +1]][replyarr[i*4+2]] = numberboard[replyarr[i*4 +3]][replyarr[i*4+4]];
						numberboard[replyarr[i*4 +3]][replyarr[i*4+4]] = rem;
						val =i;
						goto CHECK;
						// Used
					}
					numberboard[replyarr[i*4 +1]][replyarr[i*4+2]] = numberboard[replyarr[i*4 +3]][replyarr[i*4+4]];
					numberboard[replyarr[i*4 +3]][replyarr[i*4+4]] = rem;
				}
			}
			if(checkmate==1) {
				cout<<"WHITE WINS!!\n\n CONGRATULATIONS YOU BEAT MY BOT!\n";
				break;
			}
			//picking the best move
			for(int i= val-1; i>=0; i--) {
				int rem = numberboard[replyarr[i*4 +3]][replyarr[i*4 +4]];
				numberboard[replyarr[i*4+3]][replyarr[i*4+4]] = numberboard[replyarr[i*4 +1]][replyarr[i*4+2]];
				numberboard[replyarr[i*4 +1]][replyarr[i*4+2]] = 0;
				if(movecount(numberboard) > totpiececount)
				{
					if(check(0,numberboard)==1){//blk king
						totpiececount = movecount(numberboard);
						numberboard[replyarr[i*4 +1]][replyarr[i*4+2]] = numberboard[replyarr[i*4 +3]][replyarr[i*4+4]];
						numberboard[replyarr[i*4 +3]][replyarr[i*4+4]] = rem;
						continue;
					}
					totpiececount = movecount(numberboard);
					numberboard[replyarr[i*4 +1]][replyarr[i*4+2]] = numberboard[replyarr[i*4 +3]][replyarr[i*4+4]];
					numberboard[replyarr[i*4 +3]][replyarr[i*4+4]] = rem;
					val = i;
					inside = 1;
				}
				numberboard[replyarr[i*4 +1]][replyarr[i*4+2]] = numberboard[replyarr[i*4 +3]][replyarr[i*4+4]];
				numberboard[replyarr[i*4 +3]][replyarr[i*4+4]] = rem;
			}
			if (inside==0) {
				val = random % replyarr[0];
			}
		CHECK:
			for (int i=0; i<32;i++) {

				if (hold[i].posx==replyarr[val*4 +1] && (hold[i].posy-1)==replyarr[val*4 +2]) {
					for (int j=0; j<32; j++) {
						if(hold[j].posx==replyarr[val*4+3] && (hold[j].posy-1)==replyarr[val*4+4]&&numberboard[replyarr[val*4+3]][replyarr[val*4+4]] <10&& numberboard[replyarr[val*4 +3]][replyarr[val*4+4]] !=0)
						{
							hold[j].posx = 100;
							hold[j].posy =100;
							numberboard[replyarr[val*4 +3]][replyarr[val*4+4]] =0;
							break;
						}
					}
					hold[i].posx= replyarr[val*4+3];
					hold[i].posy= replyarr[val*4 +4]+1;
					numberboard[replyarr[val*4+1]][replyarr[val*4+2]] = 0;
					break;
				}
			}
			cout<<"working wth different moves: "<< replyarr[0]<<"\n";
		}
		printBoard(Mark);
		int whitekingpresent =0;
		for(int i=0; i<8; i++)
		{
			for(int j =0; j<8; j++)
			{
				if(numberboard[i][j]==1)
				{
					whitekingpresent =1;
				}
			}
		}
		if(whitekingpresent==0)
		{
			cout<<"MY BOT WINS!!\n\n CONGRATULATIONS YOU PLAYED A GOOD GAME BUT YOU WERE JUST A PAWN IN THE END!\n";
			break;			
		}
		//Aprintf();
		int legalMovesLength=legalMoves[0];
		legalMoves[0] = 0; // delete after
		char in;
		engineToMove = false; // check for reply
		in = fgetc(stdin);
		if(in == 'w') // up arrow
		{
			Mark.posx--;
			if(numberboard[Mark.posx][Mark.posy-1] != 0 && numberboard[Mark.posx][Mark.posy-1] < 10) // Only if this is a white piece
			{
				Rules(numberboard[Mark.posx][Mark.posy-1], Mark.posx, Mark.posy-1, legalMoves);
			}
		} else if(in =='s') {
			Mark.posx +=1;
			if(numberboard[Mark.posx][Mark.posy-1] != 0 &&numberboard[Mark.posx][Mark.posy-1] <10)//if(numberboard[Mark.posx][Mark.posy-1] != 0)
			{
				Rules(numberboard[Mark.posx][Mark.posy-1], Mark.posx, Mark.posy-1, legalMoves);
			}
		}
		else if(in == 'a')
		{
			Mark.posy -=1;
			if(numberboard[Mark.posx][Mark.posy-1] != 0 &&numberboard[Mark.posx][Mark.posy-1] <10)
			{
				Rules(numberboard[Mark.posx][Mark.posy-1], Mark.posx, Mark.posy-1, legalMoves);

			}
		} else if(in == 'd') {
			Mark.posy +=1;
			if(numberboard[Mark.posx][Mark.posy-1] != 0 &&numberboard[Mark.posx][Mark.posy-1] <10)
			{
				Rules(numberboard[Mark.posx][Mark.posy-1], Mark.posx, Mark.posy-1, legalMoves);
			}

		}		
		else if(in == 0x0A) { // Enter
			cout <<" Piece at position: "<<numberboard[Mark.posx][Mark.posy-1]<<endl;
			if(numberboard[Mark.posx][Mark.posy-1]==0)
			{
				//std::cin.ignore();
				goto START;
			}
			if((legalMovesLength > 0) && numberboard[Mark.posx][Mark.posy-1] != 0) {
				int count = 0;
				struct Marker endmark;
				endmark.color = " \u2611";
				legalMoves[0] = legalMovesLength;
				while(true) {
					endmark.posx = legalMoves[count*2 + 1];
					endmark.posy = legalMoves[count*2 +2]+1;
					printBoard(endmark);
					char tempin = fgetc(stdin);
					if(tempin == 't') {
						count--;
						if(count<0) {
							cout << "Navigate other direction using b\n";
							count = legalMovesLength-1;
						}
					} else if(tempin=='q') {
						std::cin.ignore();
						goto START;
					} else if(tempin=='b') {
						count++;
						if(count == legalMovesLength) {
							cout << "Navigate other direction using t\n";
							count = 0;
						}
					} else if(tempin == 0x0A) { // Enter
						for(int i = 0;i<32;i++) {
							if(hold[i].posx == Mark.posx && hold[i].posy == Mark.posy) {
								for(int j=0; j< 32;j++) {
									if(hold[j].posx==endmark.posx &&hold[j].posy ==endmark.posy) {
										hold[j].posx = 100;
										hold[j].posy = 100;
										numberboard[endmark.posx][endmark.posy-1] =0;
									}
								}
								if(numberboard[Mark.posx][Mark.posy-1]==1 && (Mark.posy+2==endmark.posy)) {
									for(int j=0; j<32; j++) {
										if(hold[j].posx==Mark.posx && hold[j].posy==Mark.posy+3) {
											numberboard[Mark.posx][Mark.posy] = numberboard[Mark.posx][Mark.posy+2];
											numberboard[Mark.posx][Mark.posy+2] = 0;//remove from board
											hold[j].posy = Mark.posy+1;
											break;
										}
									}
								}
								if(numberboard[Mark.posx][Mark.posy-1]==1 && (Mark.posy-2==endmark.posy)) {
									//find left side rook and switch
									for(int j=0; j<32; j++) {
										if(hold[j].posx==Mark.posx && hold[j].posy==Mark.posy-4)
										{
											numberboard[Mark.posx][Mark.posy-2] = numberboard[Mark.posx][Mark.posy-5];
											numberboard[Mark.posx][Mark.posy-5] = 0;//remove from board
											hold[j].posy = Mark.posy-1;
											break;
										}
									}
								}
								numberboard[endmark.posx][endmark.posy-1] =  numberboard[Mark.posx][Mark.posy-1];
								hold[i].posx = endmark.posx;
								hold[i].posy = endmark.posy;
								numberboard[Mark.posx][Mark.posy-1] =0;
								Mark.posx = endmark.posx;
								Mark.posy = endmark.posy;
								engineToMove = true;
								//promotion
								if(numberboard[endmark.posx][endmark.posy-1]==3 && endmark.posx==0)
								{
									cout <<"\nFor Rook enter r\n";
									cout <<"\nFor Queen enter q\n";
									cout <<"\nFor Bishop enter b\n";
									cout <<"\nFor Knight enter k\n";
									char majorpiece;
									cin >> majorpiece;
									if(majorpiece =='r')
									{
										roo1.symbol=" \u265C";//white rook
										numberboard[endmark.posx][endmark.posy-1] =  6;										
									}
									if(majorpiece =='q')
									{
										hold[i].symbol= " \u265B";//white queen
										numberboard[endmark.posx][endmark.posy-1] =  2;
									}
									if(majorpiece =='b')
									{
										hold[i].symbol = " \u265D";//white bishop
										numberboard[endmark.posx][endmark.posy-1] =  5;
									}
									if(majorpiece =='k')
									{
										hold[i].symbol =" \u265E";//white knight
										numberboard[endmark.posx][endmark.posy-1] =  4;
									}
									std::cin.ignore();
								}
								goto START;
								cout<<"Press Enter to confirm change\n";
								break;
							}
						}
						cout << "\nholdx " << hold[3].posx << "\n";
						cout << "\nholdy " << hold[3].posy << "\n";
						break;
					} else {
						cout<<"Press t / b to navigate to your desired position\n";
					}
					std::cin.ignore();
				}
			}
		} else {
			cout << "Use Proper character inputs w/a/s/d to play\n";
		}
		std::cin.ignore();
	}
}
