#ifndef chessheader
#define chessheader



//		COLOURS

//Functions to change the colour of terminal output doesnt work on fucking windows :) kms
//turns out these are strictly linux compliant since windows works in mysteriously shit ways 

void red () {
  printf("\033[1;31m");
}

void green () {
  printf("\033[1;32m");
}

void yellow () {
  printf("\033[1;33m");
}

void blue () {
  printf("\033[1;34m");
}

void magenta () {
  printf("\033[1;35m");
}

void cyan () {
  printf("\033[1;36m");
}

void reset () {
  printf("\033[0m");
}

//these lines access the windows terminal, get the terminal handle, declare 2 "variables"
//this secret tool will help us later fetch the terminal default settings and save them so we can
//not only change the colour to red green or blue but also reset it to the default white :D

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

//windows compliant colouring functions


void wgreen(){
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
}

void wblue(){
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
}

void wred(){
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
}

void wreset(){
    SetConsoleTextAttribute(hConsole, saved_attributes);
}






//		STRUCTS

//Definition of the chess pieces as a struct

struct piece{
	char type;
	int colour;
	char display;
};

//Definition of a single tile of a chess board as a struct

struct position{
	int row;
	int col;
	piece figure;
};




//		CONVERSION FUNCTIONS

//Converts the tile column index (number) to column index (letter)

void convArt(int *a){
	*a=*a+65;
}

int c0nvArt(int a){
	a=a+65;
	return a;
}



//The above conversion backwards

int conv4rt(int a){
	a=a-65;
	return a;
}

//converts input text numbers to proper numbers

void c0nvert(int *a){
	*a=*a-49;
}

//convert small letters to large counterparts

void cOnvert(int *a){
	*a=*a-32;
}

//		MATH FUNCTIONS I GUESS?

//mom can we have absolute value function from math header?
//we have absolute function without math header at home!

int abs(int number){
	unsigned int absval;
	int const mask= number >> sizeof(int)* CHAR_BIT - 1;
	absval= (number+mask)^mask;
	return absval;
}


//order the 2 given int values min to max I guess

void limorder(int *min,int *max){
	int mi=*min;
	int ma=*max;
	if(ma<mi){
        *min=ma; *max=mi;
	}
}


//		PRINTING FUNCTIONS

//Function to print the appropriate figure

void printfigure(piece figure){
	if(figure.colour==0){
	cyan();
	printf("| %c",figure.display);
	reset();
	} else if(figure.colour==1){
	magenta();
	printf("| %c ",figure.display);
	reset();
	}else {reset(); printf("| %c ",figure.display);}
}

//same function now using the windows compliant colouring functions

void wprintfigure(piece figure){
	if(figure.colour==0){
	printf("|");
	wred();
	printf(" %c ",figure.display);
	wreset();
	} else if(figure.colour==1){
	printf("|");
	wblue();
	printf(" %c ",figure.display);
	wreset();
	}else {
	printf("|");
	//wgreen();
	printf(" %c ",figure.display);
	//wreset();
	}
}

//function to print the whole gameboard as it is made up of its parts


void printboard(position pfield[64]){
	for(int i=0;i<64;i++){
		if(i%8==0){
			printf("%d\t",int (i/8));
		}
		printfigure(pfield[i].figure);
		if(i%8==7){printf(" |\n");
		printf("\t---------------------------------\n");
		}
	}
	printf("\n\n\t| A | B | C | D | E | F | G | H |");
}


//same function, windows compliant

void wprintboard(position pfield[64]){
	for(int i=0;i<64;i++){
		if(i%8==0){
			wgreen();
			printf("%d ",(8-(i/8)));
			wreset();
		}
		wprintfigure(pfield[i].figure);
		if(i%8==7){printf("|\n");
		printf("  ---------------------------------\n");
		}
	}
	wgreen();
	printf("    A   B   C   D   E   F   G   H  \n\n");
	wreset();
}


//Function to print the board on any platform, without colours

void pmonboard(position pfield[64]){
	for(int i=0;i<64;i++){
		if(i%8==0){
			printf("%d\t",int (i/8));
		}
		wprintf(L"| %c ",pfield[i].figure.display);
		if(i%8==7){printf(" |\n");
		printf("---------------------------------\n");
		}
	}
	printf("| A | B | C | D | E | F | G | H |\n\n");
}


//		LOGIC OPERATIONS

//function resets the appropriate tile graphic on given piece of the board

void tiler(position *tile, piece btile, piece wtile){
	if(((tile->row + tile->col) %2)){  //this makes the checkerboard pattern
		tile->figure=btile;		
		} else{
		tile->figure=wtile;
		}
}

//function to move one thing to another

void swap(position *origin, position *destination, piece btile, piece wtile){
	if(origin->figure.colour==destination->figure.colour){//player pieces block same colour movement
		wred();
		printf("Why are you hitting yourself?\n");
		wreset();		
	}else if(origin->figure.colour<2){	//PLAYER pieces move to any space 
		destination->figure=origin->figure; //this condition disqualifies moving empty tiles
		tiler(origin,btile,wtile);	//after a piece left, recolour the tile appropriately
	}else{
		wred();
		printf("You can't move the big nothing, bloody wanker!\n\n");
		wreset();
	}
}

//		MOVEMENT RULES FOR PIECES


// movement rules of the pawn(s) 

//white moves upwards, black moves downwards

int movewpawn(position origin,position destination){
			//same as black pawn movement, but indices adjusted in the right direction
	if(
		(origin.row==6)&&(origin.col==destination.col)&&
		(destination.row==(origin.row-2))&&
		(destination.figure.colour>1)&&
		(origin.figure.colour==0)
		){
		return 1;
	}else if(
		(destination.row==(origin.row-1))&&
		(origin.col==destination.col)&&
		(destination.figure.colour>1)&&
		(origin.figure.colour==0)
		){
		return 1;
	}else if(
		((destination.col==(origin.col+1))||
		(destination.col==(origin.col-1)))&&
		(destination.row==(origin.row-1))&&
		(destination.figure.colour==1)&&
		(origin.figure.colour==0)
		){
		return 1;
	}else{
		wred();
		wreset();
		return 0;
	}
}



int movebpawn(position origin,position destination){
	
	if(
		(origin.row==1)&&(origin.col==destination.col)&& //from the original position
		(destination.row==(origin.row+2))&&	// can step 2 forward in same column
		(destination.figure.colour>1)&&	//can NOT take pieces with forward step
		(origin.figure.colour==1)
	){
		return 1;
	}else if(
		(destination.row==(origin.row+1))&& //can only move forward 
		(origin.col==destination.col)&& //can only move in same column
		(destination.figure.colour>1)&&	//can NOT take pieces with forward step
		(origin.figure.colour==1)
		){
		return 1;
	}else if(
		((destination.col==(origin.col+1))|| //can step right
		(destination.col==(origin.col-1)))&& //can step left
		(destination.row==(origin.row+1))&& //must also step forward (3 together diagonal)
		(destination.figure.colour==0)&& //can ONLY step 1 in fwd diagonal IF it takes a piece
		(origin.figure.colour==1) 
		){
		return 1;
	}else{
		wred();
		wreset();
		return 0;
	}
}



// movement rules of the rook

int moverook(position origin,position destination,int cplayer){
	if( 	//destination is in same row or column as the origin 
	((origin.row==destination.row)||(origin.col==destination.col)) && 
	((cplayer%2)==origin.figure.colour) 	//only the player whose turn it is shall move	
	){
		return 1;
	}else{
		wred();
		wreset();
	return 0;	
	}
}


//movement rules for the bishop

int movebishop(position origin,position destination,int cplayer){
	if(
		(abs(destination.col-origin.col)==abs(destination.row-origin.row))&&
		((cplayer%2)==origin.figure.colour)
		){
		return 1;
		}else{
		wred();
		wreset();
	return 0;	
	}
}


// movement rules for the queen

int movequeen(position origin,position destination,int cplayer){
	if(
		(((origin.row==destination.row)||(origin.col==destination.col)) || //rook rule
		(abs(destination.col-origin.col)==abs(destination.row-origin.row)))&& //bishop rule
		((cplayer%2)==origin.figure.colour) 	//only the player whose turn it is shall move	
		){
		return 1;
		}else{
		wred();
		wreset();
	return 0;
	}
}




// movement rules of the king

int moveking(position origin,position destination,int cplayer){
	if(
		(destination.row==origin.row+1)||
		(destination.row==origin.row-1)||//king may move to any neighbouring tile
		(destination.col==origin.col+1)||
		(destination.col==origin.col-1)
		){
			return 1;
	}else{
		wred();
		wreset();
	return 0;	
	}
}


// function to move knight, I mean hussar XD

int moveknight(position origin,position destination,int cplayer){
	if(
	( ((abs(destination.col-origin.col)==2)&& //side to side +-2
	 (abs(destination.row-origin.row)==1))||  //up down +-1
	 ((abs(destination.row-origin.row)==2)&& //up down +-2
	 (abs(destination.col-origin.col)==1)))&& //side to side +-1 net movement
	 ((cplayer%2)==origin.figure.colour)			
	){
		return 1;
	}else{
		wred();
		wreset();
	return 0;	
	}
} 


//		CONDITION CHECKS


//	function checks if the proposed movement was blocked	
	
int block(position origin,position destination,position pfield[]){
	int retval=0;
	
	if(origin.row==destination.row){
		if(origin.col<destination.col){
			for(int i=(origin.col+1);i<destination.col;i++){
				int j=conv4rt(i)+8*origin.row;
				if(pfield[j].figure.type!='t'){
					retval++;
				}
			}
		}else{
			for(int i=(origin.col-1);i>destination.col;i--){
				int j=conv4rt(i)+8*origin.row;
				if(pfield[j].figure.type!='t'){
					retval++;
				}
			}
		}	
	}
	
	if(origin.col==destination.col){
		if(origin.row<destination.row){
			for(int i=(origin.row+1);i<destination.row;i++){
				int j=i*8+conv4rt(origin.col);
				if(pfield[j].figure.type!='t'){
					retval++;
				}
			}
		}else{
			for(int i=(origin.row-1);i>destination.row;i--){
				int j=i*8+conv4rt(origin.col);
				if(pfield[j].figure.type!='t'){
					retval++;
				}
			}
		}
	}
	
	if((abs(destination.col-origin.col)==abs(destination.row-origin.row))){
		int cmin=origin.col;
		int cmax=destination.col;
		int rmin=origin.row;
		int rmax=destination.row;
		
		limorder(&cmin,&cmax);
		limorder(&rmin,&rmax);
		
		if((((origin.col-destination.col)<0)&&((origin.row-destination.row)<0))||
		(((origin.col-destination.col)>0)&&((origin.row-destination.row)>0))){
			for(rmin+1;rmin<(rmax-1);rmin++){
				cmin++;
				int j=(rmin+1)*8+conv4rt(cmin);
				if(pfield[j].figure.type!='t'){
					retval++;
				}
			}
		}else{
			for(rmin+1;rmin<(rmax-1);rmin++){
				cmax--;
				int j=(rmin+1)*8+conv4rt(cmax);
				if(pfield[j].figure.type!='t'){
					retval++;
				}
			}
		}
	}
	
	if(destination.figure.type=='k'){retval++;}
	
	if(retval!=0){wred();printf("Movement blocked fucko!\n");wreset();}
	return retval;		
}

// checks if movement would be blocked to give check

int checkblock(position origin,position destination,position pfield[]){
	int retval=0;
	
	if(origin.row==destination.row){
		if(origin.col<destination.col){
			for(int i=(origin.col+1);i<destination.col;i++){
				int j=conv4rt(i)+8*origin.row;
				if(pfield[j].figure.type!='t'){
					retval++;
				}
			}
		}else{
			for(int i=(origin.col-1);i>destination.col;i--){
				int j=conv4rt(i)+8*origin.row;
				if(pfield[j].figure.type!='t'){
					retval++;
				}
			}
		}	
	}
	
	if(origin.col==destination.col){
		if(origin.row<destination.row){
			for(int i=(origin.row+1);i<destination.row;i++){
				int j=i*8+conv4rt(origin.col);
				if(pfield[j].figure.type!='t'){
					retval++;
				}
			}
		}else{
			for(int i=(origin.row-1);i>destination.row;i--){
				int j=i*8+conv4rt(origin.col);
				if(pfield[j].figure.type!='t'){
					retval++;
				}
			}
		}
	}
	
	if((abs(destination.col-origin.col)==abs(destination.row-origin.row))){
		int cmin=origin.col;
		int cmax=destination.col;
		int rmin=origin.row;
		int rmax=destination.row;
		
		limorder(&cmin,&cmax);
		limorder(&rmin,&rmax);
		
		if((((origin.col-destination.col)<0)&&((origin.row-destination.row)<0))||
		(((origin.col-destination.col)>0)&&((origin.row-destination.row)>0))){
			for(rmin+1;rmin<(rmax-1);rmin++){
				cmin++;
				int j=(rmin+1)*8+conv4rt(cmin);
				if(pfield[j].figure.type!='t'){
					retval++;
				}
			}
		}else{
			for(rmin+1;rmin<(rmax-1);rmin++){
				cmax--;
				int j=(rmin+1)*8+conv4rt(cmax);
				if(pfield[j].figure.type!='t'){
					retval++;
				}
			}
		}
	}
	
	return retval;		
}


// this function should check for king to not step into the territory of another king

int kingblock(position origin, position destination, position pfield[64], int cplayer){
	int retval=0;
	for(int i=-1;i<2;i++){
		for(int j=-1;j<2;j++){
			int k= ((destination.row+i)*8)+conv4rt(destination.col+j);
			if((pfield[k].figure.type=='k')&&(pfield[k].figure.colour!=(cplayer%2))){
			retval++;
			}
		} 
	}
	return retval;
}



#endif

