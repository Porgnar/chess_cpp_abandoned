//		HEADERS

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <unistd.h>
#include "wchess.h"



//		MAIN FUNCTION

int main(){

	sleep(1);
	
	printf("\n");
	
    //we read and store the default state of the windows console
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;


//Declare miscellanious variables
	
	int whitecheck=0;
	int blackcheck=0;

	int ro,co,rd,cd;
	int cplayer=0;
	char input[10];
	position blacking;
	position whiteking;	//these are secret tools, they are going to come in handy later
	piece shadowrealm;
	

//		PIECE DECLARATIONS

//	BOARD

	position pfield[64];	// the playboard


//	TILES

	piece btile;			// black tile

	btile.colour=2;			// tiles have colour identification 2
	btile.type='t';			// tiles are type t for tile
	btile.display=177;		// black tile character as ascii value 177

	piece wtile;			//white tile

	wtile.colour=2;
	wtile.type='t';
	wtile.display=176;		//176


//	BLACK PIECES

	piece bpawn;			// black pawn

	bpawn.colour=1;			// black pieces have colour identifier 1
	bpawn.type='p';			// type p for pawn
	bpawn.display=245;		// display character in ascii value, the colours are separated at printing

	piece bbishop;			//black bishop

	bbishop.colour=1;
	bbishop.type='b';		//type b for bishop
	bbishop.display=235;

	piece brook;			//black rook

	brook.colour=1;
	brook.type='r';			//r for rook,
	brook.display=219;

	piece bhussar;

	bhussar.colour=1;
	bhussar.type='h';		//https://www.youtube.com/watch?v=rcYhYO02f98
	bhussar.display=244;

	piece bqueen;

	bqueen.colour=1;
	bqueen.type='q';		//q for queen
	bqueen.display=234;

	piece bking;

	bking.colour=1;
	bking.type='k';			//k for king
	bking.display=224;



//	WHITE PIECES

	piece wpawn;

	wpawn.colour=0;
	wpawn.type='p';			//NO!
	wpawn.display=245;

	piece wbishop;

	wbishop.colour=0;
	wbishop.type='b';		//I SAID NO!
	wbishop.display=235;

	piece wrook;

	wrook.colour=0;
	wrook.type='r';			//I AM NOT WILLING TO
	wrook.display=219;

	piece whussar;

	whussar.colour=0;
	whussar.type='h';		//COMMENT ALL THIS SHIT AGAIN
	whussar.display=244;

	piece wqueen;

	wqueen.colour=0;
	wqueen.type='q';		//WHY DO WE EVEN COMMENT OUR CODE IN THE FIRST PLACE?
	wqueen.display=234;

	piece wking;

	wking.colour=0;
	wking.type='k';			//LIKE IF YOU WANT TO UNDERSTAND THE CODE JUST FIGURE IT OUT LOL
	wking.display=224;


//		Board default colouring setup

	for(int i=0;i<64;i++){
		
		int j=i%8;
		convArt(&j);
		pfield[i].row=i/8;
		pfield[i].col=j;
		tiler(&pfield[i],btile,wtile);
		}



//		Initial Board setup


//	Black backline

	pfield[0].figure=brook; //0
	pfield[1].figure=bhussar;
	pfield[2].figure=bbishop;
	pfield[4].figure=bking;//3
	pfield[3].figure=bqueen;
	pfield[5].figure=bbishop;
	pfield[6].figure=bhussar;
	pfield[7].figure=brook; //7

//	Black frontline

	for(int i=8;i<16;i++){
		pfield[i].figure=bpawn;
	}


//	white backline

	pfield[56].figure=wrook; //56
	pfield[57].figure=whussar;
	pfield[58].figure=wbishop;
	pfield[59].figure=wqueen;
	pfield[60].figure=wking;//60
	pfield[61].figure=wbishop;
	pfield[62].figure=whussar;
	pfield[63].figure=wrook; //63

//	white frontline

	for(int i=48;i<56;i++){
		pfield[i].figure=wpawn;
	}

	
	
//		ACTUAL GAME CODE?
	
		system("cls");
	
	wgreen();
	printf("Starting player is red, have fun ;)\n\n");
	wreset();	
	
	wprintboard(pfield); //displays the starting board

	
//		MAIN GAME LOOP

	while(1){




	wgreen();
	scanf("%s",input);	//read input first 4 letters are what I actually care about
	wreset();
	
//put first 4 characters into variables
	ro= input[1];
	co= input[0];
	rd= input[3];
	cd= input[2];
	
//small letters get converted to capital letters
	if(('a'<=co)&&(co<='h')){cOnvert(&co);}
	if(('a'<=cd)&&(cd<='h')){cOnvert(&cd);}
	
//if user types 1quit' the program ceases to run
	if((co=='q')&&(ro=='u')&&(cd=='i')&&(rd=='t')){system("cls");break;break;}
	
			
	
//if the input is a valid tile on the board the game proceeds
	if(('1'<=ro)&&(ro<='8')&&('1'<=rd)&&(rd<='8')&&('A'<=co)&&(co<='H')&&('A'<=cd)&&(cd<='H'))
	{
		
		
	system("cls"); //wipes terminal
	
	
	c0nvert(&ro);
	c0nvert(&rd);	
	co=conv4rt(co);
	cd=conv4rt(cd);
	
	
	ro=(8-ro)-1;	//the board numbers in reverse from our logic so an additional conversion was inserted
	rd=(8-rd)-1;	//yep :(
	

	
	int origin=co+(8*ro);
	int destination=cd+(8*rd);
	

//temporarily store the figure on the destination tile, so we can recover it if the proposed move was not allowed		

	shadowrealm=pfield[destination].figure; 
	
//the "proposed" move happens, switch determines what type of figure moves
	
	switch(pfield[origin].figure.type){
	
	case 'p':  //in case it is a pawn it applies pawn rules	
		if(cplayer%2){	//black and white pawns have different rules, so separation was needed
			if(movebpawn(pfield[origin],pfield[destination])&&		//we check if the proposed move is valid for the pawn
		(!(block(pfield[origin],pfield[destination],pfield)))){		//we check if the pawn can move there
				swap(&pfield[origin],&pfield[destination],btile,wtile);	//we move the pawn
				cplayer++;			//increment the current player, meaning it's the opposing player's turn now
			}
		}else{
			if(movewpawn(pfield[origin],pfield[destination])&&	
		(!(block(pfield[origin],pfield[destination],pfield)))){
				swap(&pfield[origin],&pfield[destination],btile,wtile);
				cplayer++;		
			}
	}
		break;
	
	case 'b':	//same as pawn but for bishop
		if(movebishop(pfield[origin],pfield[destination],cplayer)&&
		(!(block(pfield[origin],pfield[destination],pfield)))){
			swap(&pfield[origin],&pfield[destination],btile,wtile);
			cplayer++;
		}
		break;
		
	case 'r':	//again for rook
		if(moverook(pfield[origin],pfield[destination],cplayer)&&
		(!(block(pfield[origin],pfield[destination],pfield)))){
			swap(&pfield[origin],&pfield[destination],btile,wtile);
			cplayer++;
		}
		break;
	
	case 'h':	//are you not getting tired of this?
		if(moveknight(pfield[origin],pfield[destination],cplayer)&&
		(!(block(pfield[origin],pfield[destination],pfield)))){
			swap(&pfield[origin],&pfield[destination],btile,wtile);
			cplayer++;
		}
		break;
		
	case 'k':	//I know I sure am :(
		if(moveking(pfield[origin],pfield[destination],cplayer)&&
		(!kingblock(pfield[origin],pfield[destination],pfield,cplayer))){
			swap(&pfield[origin],&pfield[destination],btile,wtile);
			cplayer++;
		}
		break;
			
	case 'q':	//last line of comment yaaay!!4!444! :D
		if(movequeen(pfield[origin],pfield[destination],cplayer)&&
		(!(block(pfield[origin],pfield[destination],pfield)))){
			swap(&pfield[origin],&pfield[destination],btile,wtile);
			cplayer++;
		}
		break;
	}//switch
	

	
//		CHECK CHECK



	whitecheck=0;	//we actually count how many figures have the king in check
	blackcheck=0;	//such advanced much wow
	

	
// this cycle searches for the positions of both the black and the white king by sweeping the whole playfield
	
for(int i=0;i<64;i++){

	if((pfield[i].figure.type=='k')&&(pfield[i].figure.colour==0)){
	whiteking=pfield[i];	
	}
	if((pfield[i].figure.type=='k')&&(pfield[i].figure.colour==1)){
	blacking=pfield[i];
	}
}


//for every single tile on the sodden playfield if on the tile there is a specific figure, we propose
//that the figure moves from its current tile to both kings' tiles, we check if this is a valid move for the piece
//we check if the movement is blocked, then we check if the piece that could take the king is a different colour
//if all these are in order we increment the number of checks on the appropriate king


for(int i=0;i<64;i++){
	
	switch(pfield[i].figure.type){
	
	case 'p':	//well here we are again
		if(pfield[i].figure.colour==1){
			if(movebpawn(pfield[i],whiteking)&&
		(!(checkblock(pfield[i],whiteking,pfield)))){
				if(pfield[i].figure.colour==1){whitecheck++;}
			}
		}else{	//it's always such a pleasure
			if(movewpawn(pfield[i],blacking)&&
		(!(checkblock(pfield[i],blacking,pfield)))){
				if(pfield[i].figure.colour==0){blackcheck++;}
			}
	}
		break;
	
	case 'b':	//commenting the same copy pasted code
		if(movebishop(pfield[i],whiteking,cplayer-1)&&
		(!(checkblock(pfield[i],whiteking,pfield)))){
			if(pfield[i].figure.colour==1){whitecheck++;}
		}
		if(movebishop(pfield[i],blacking,cplayer-1)&&
		(!(checkblock(pfield[i],blacking,pfield)))){
			if(pfield[i].figure.colour==0){blackcheck++;}
		}

		break;
		
	case 'r':	//goodbye my only friend
		if(moverook(pfield[i],whiteking,cplayer-1)&&
		(!(checkblock(pfield[i],whiteking,pfield)))){
			if(pfield[i].figure.colour==1){whitecheck++;}
		}
		if(moverook(pfield[i],blacking,cplayer-1)&&
		(!(checkblock(pfield[i],blacking,pfield)))){
			if(pfield[i].figure.colour==0){blackcheck++;}
		}
		break;
	
	case 'h':	//oh, did you think I meant you?
		if(moveknight(pfield[i],whiteking,cplayer-1)&&
		(!(checkblock(pfield[i],whiteking,pfield)))){
			if(pfield[i].figure.colour==1){whitecheck++;}
		}
		if(moveknight(pfield[i],blacking,cplayer-1)&&
		(!(checkblock(pfield[i],blacking,pfield)))){
			if(pfield[i].figure.colour==0){blackcheck++;}
		}
		break;
		
			
	case 'q':	//it would be funny if it weren't so sad :(
		if(movequeen(pfield[i],whiteking,cplayer-1)&&
		(!(checkblock(pfield[i],whiteking,pfield)))){
			if(pfield[i].figure.colour==1){whitecheck++;}
		}
		if(movequeen(pfield[i],blacking,cplayer-1)&&
		(!(checkblock(pfield[i],blacking,pfield)))){
			if(pfield[i].figure.colour==0){blackcheck++;}
		}
		break;
	}//switch
	
	//phew, that was a lot of work, right? don't worry it's smooth sailing from here on out :)


}//for(64) sweep the field


//now it is time for us to check if the move we just made took us into check, because that is a big no-no
//so I kind of have to forbid it :/ "the stupid deserve to die" mentality is not present in chess 

//keep in mind, that we perform the check in the opposing person's turn technically 
//since we already incremented the current player variable during the step phase! 	

//this little caveat is crucial to keep in mind or the whole process would work inverted, which is not good,
//it would work one cycle off, and would allow movement into check

	if(cplayer%2!=0){	//if it's white's move, they moved
		if(whitecheck!=0){  //and if they moved so that they are now in check
		pfield[origin].figure=pfield[destination].figure; 
		pfield[destination].figure=shadowrealm;	//we swap back the figures taken basically undoing the turn
		cplayer--;	//we are not assholes we don't take your turn away
		wgreen();
		printf("Uncheck if you can >:)\n\n");	//we give a playful warning to the little fuckers
		wreset();
		}
	}else{	//same for black player
		if(blackcheck!=0){
		pfield[origin].figure=pfield[destination].figure;
		pfield[destination].figure=shadowrealm;
		cplayer--;
		wgreen();
		printf("Uncheck if you can >:)\n\n");
		wreset();
		}
	}



	wprintboard(pfield);	//self explanatory but we print the chessboard 

//we notify the players of them being in check

	if(whitecheck!=0){wgreen();printf("Red in check! :O\n");wreset();}
	if(blackcheck!=0){wgreen();printf("Blue in check! :O\n");wreset();}
		
	}else{
	wred();
	printf("invalid input bucko! :(\n");  //the input was shit we tell it to the user
	wreset();
	}
}//while(1)
	

return 0;
}//end of main
