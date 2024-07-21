#include <iostream>
using namespace std;
//constant variables
#define rows 4 //number of rows 
// global variables:
int nim[] = { 1, 3, 5, 7}; // the board has 4 rows and the numbers is the sticks, i avoided using 2d arrays for simplificationc
bool gameover; // to check the game status 


//*************API****************
void Playerturn(); //to make the player play
void CheckStatus(); // check status of the game 
void computerturn(); // unbeatable computer
//*****************************************
//************MAIN FUNCTION****************
//*****************************************
int main() {
   cout <<"*************************WELCOME TO NIM GAME**********************************"<<endl;
    //print the initial board
	for (int i = 0; i < rows; i++){
        for(int j =0; j<rows-i; j++){
         cout << " ";
        }                  //sticks
		for (int j = 0; j < nim[i]; j++){
			cout << "|";
		}
		cout << endl;
	}
	cout << "Rules: In each turn, you can pick as many sticks as you want from one single row. The player who picks the last stick loses"<<endl;
	char mode; // 2 players or vs unbeatable computer
    cout<< "choose mode : vs Human , vs unbeatble computer (H /C) :"<< endl;
    cin >> mode;
while (mode != 'H' && mode != 'C'){
		cout << "Enter H for vsHuman or C for vscomputer only!" << endl;
		cin >> mode;
	}
    gameover=false;//initilaze gameover
     char turn; // check who will start
	 cout << "************GAME STARTED********************"<<endl;
    if( mode == 'C'){ // if user choose to play against computer
        cout<< "do you want to start the game? (Y/N) "<<endl;
        cin >> turn;
        while (turn != 'Y' && turn != 'N'){
		cout << "Enter Y or N only!" << endl;
		cin >> turn;}

        while(!gameover){
	if (turn == 'Y') { // if player start the game
			Playerturn(); // call the player turn method
			CheckStatus(); //keep checking for status until the end of the game
			turn = 'N';
		}
		else{ // if computer start the game
		computerturn(); // call the computer turn method
		
		CheckStatus(); //keep checking for status until the end of the game
            turn = 'Y';
}
        }}
        // if user choose vs Human: 
    else{ 
        while(!gameover){
        Playerturn(); // call the computer turn method
		CheckStatus(); //keep checking for status until the end of the game
    }}
    }


    //*****************************************************************************************
    //*******************************METHODS IMPLEMETATIONS*************************************
    //*****************************************************************************************
//method for the player turn
void Playerturn() {
	int row; //current row choosen from user
    int sticks;
	cout << "your turn : choose a row from 1-"<<rows << endl;
	cin >> row; // let the player choose
 // nim[row-1] means number of sticks in the current row, eg if player choose row 3 then row[3-1] = row[2]= 5. 5 sticks
	while (row < 1 || row > rows || nim[row-1] == 0) //if player choose invalid row or the row was empty , keep trying again 
		{
		cout << "invalid row, you must choose row (1-"<<rows<<")  and should have sticks left,try again" << endl;
		cin >> row;
	}
	cout << "how many sticks you want to remove from row "<<row<<" ?: " << endl;
	cin >> sticks;
	while (sticks < 1 || sticks > nim[row-1]) //if player choose a negative int or more than sticks left in that row, try again
	{
		cout << "invalid sticks input , choose number from the sticks left in row " << row << endl;
		cin >> sticks;
	}
	nim[row-1] -= sticks; //remove sticks from the sticks of the row the user choose
}

// functionality for checking status
void CheckStatus() {
	if (nim[0] == 0 && nim[1] == 0 && nim[2] == 0 && nim[3] == 0){// if all rows has no sticks left or basically a={0,0,0,0}
		gameover = true; // game is over
		cout << "sorry , you lost"; //i didnt write a condition for winning because either ways there is always a looser,
                                    //the loser is the one who picks the last stick,the loser will know himself
	}
	else // if there is still sticks in the board , print the current board and keep playing
	{
		for (int i = 0; i < rows; i++){
		for(int j=0; j<rows-i;j++){
            cout <<" ";
        }
                               //nim[i] is the number of  sticks
			for (int j = 0; j < nim[i]; j++)
			{
				cout << "|";
			}
			cout << endl;
		}
	}
}




//THE NIM SUM OF TWO OR MORE INTEGERS CAN BE CALCULATED BY MEANS OF "XOR" IN LOGIC
// FOR EXAMPLE A XOR B = [(A OR B) AND (NOT ( A AND B))]
// XOR OPERATION RETURN 1 IN A BIT POSITION IF BITS OF ONE INT (BUT NOT BOTH) OPERANDS ARE 1'S
//UNBEATABLE COMPUTER
//***********************EXPLINATION*************************************
//***********************************************************************
//THE STRATEGY FOR ALWAYS WINNING IS TO ALWAYS TAKE STICKS AS POSSIBLE TO MAKE THE (NUM SUM) IS ALWAYS ZERO
//count the sticks in each row, change it to multiples of 4,2 and 1, AND CANCEL EACH EQUAL MULTIPLES, EVERYTIME THE COMPUTER
//LEAVE THE PLAYER WITH ZERO (NIM SUM), MORE CHANCE THE COMPUTER WINS
//FOR EXAMPLE:
// CURRENT BOARD IS 1,3,5,5 .. :
// row1 = 1 = 1x1                        1
// row2 = 3 = 1x2 + 1x1 =           2    1
// row3 = 5 = 1x4 + 1x1 =      4         1
// row4 = 5 = 1x4 + 1x1 =      4         1 
// total of unpaired =         0    1    0  ---> there is ONE 2 left alone 
// to obtain a ZERO NIMSUM, get rid of it by taking 2 sticks from second row:  YOU WILL LEAVE THE PLAYER WITH 1,1,5,5 
//which is a winning configuration for you (1^1^5^5)=0
// SO STARTING CONFIG : 1,3,5,7 IS ALWAYS LOSING IF YOU START THE GAME, because nimsum is zero,SO COMPUTER WILL ALWAYS WIN IF IT DIDNT START
void computerturn(){
int crow,sticks,i; //crow is the currentrow
int lastcount=0; // number of rows that has more than one stick
int emptyrows=0; // number of empty rows in the board
int lastmove=0; // the row that has more than one stick 
int nimsum = nim[0];// nim sum
	//define the nimsum MEANS OF XORS 
	for(int i=1; i < rows; i++){
		nimsum ^=nim[i]; // xor operator is '^'
	}
	cout << "v--computer move:--v"<<endl;// indicates the computer move
	//cout << "NIM SUM: " << nimsum<<endl;
	for (int j = 0; j < rows; j++){
		if (nim[j] > 1){ // if the current row still has more than one stick, count them 
			lastcount ++;
			lastmove = j; 
		}
		else if (nim[j] == 0){ //skip empty rows and count them
			emptyrows ++;
		}
	}
	if (lastcount == 1){  //if there is only one row that has more than one stick in the board.
		if (emptyrows == 3){ // if its the only row left, take all sticks but leave one, leaving the board with one stick, therfore wins
			nim[lastmove] = 1; 
		}
		else{//but if there is a row that has more than one stick AND a row that has only one, empty the row that has more than one stick
		//leaving only one row that has the only one  stick in the board and therfore wins.
			nim[lastmove] = 0;
		}
	}
	else{ // if there is still more than one row that has more than one stick
	if (nimsum != 0){ // if nimsum is not zero , make it equal to zero
        for (i=0; i<rows; i++){
            if ((nim[i] ^ nimsum) < nim[i]){ //if sticks xor nimsum is less than the sticks(not illegal move) 
                crow = i;
                sticks= nim[i]-(nim[i]^nimsum);//sticks of the row minus the xor of the sticks and the nonzero-nimsum
                nim[i] = nim[i] ^ nimsum;//now the nim sum is zero
            }
        }
    }
//if nimsum is zero(computer started first) 
else{
	//computer cant make the nimsum zero since the nim sum is already zero , so remove any random sticks
//if the row is empty, find a row that is not empty	
while(nim[crow] ==0){
	crow = rand() % 4;
}
        crow = rand() % rows;//pick a random row from the nonempty rows (4) in that case
        sticks= rand() % nim[crow] +1; // choose a random number of sticks from  the nonempty rows (+1 means inclusive) 
		//and substract it from the sticks of the row
        nim[crow] -= sticks;
		
    }

}
cout<< "computer removed "<<sticks<<" sticks from row "<<crow+1<<endl;
}
