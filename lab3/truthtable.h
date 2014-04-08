#include <iostream>
#include <fstream>
using namespace std;




void inputpalindrome(int x1,int x2, int x3, int x4, int x5, ofstream& myfile){
	
	if((x1 == x5) && (x2== x4)){
		myfile<< x1<<x2<<x3<<x4<<x5<<1<<endl;	
	}
	else{ myfile<< x1<<x2<<x3<<x4<<x5<<0<<endl;	
	}

}


void palindrome(){
	ofstream myfile;
	myfile.open("truthtable.txt");
	for(int a =0; a<2; a++){
		for(int b =0; b<2; b++){
			for(int c =0; c<2; c++){
				for(int d =0; d<2; d++){
					for(int e =0; e<2;e++){
						inputpalindrome(a,b,c,d,e,myfile);				
					}
				}
			}
		}	
	}
	myfile.close();
}





void tinputpalindrome(int x1,int x2, int x3, ofstream& myfile){
	
	if((x1 == x3)){
		myfile<< x1<<x2<<x3<<1<<endl;	
	}
	else{ myfile<< x1<<x2<<x3<<0<<endl;	
	}

}


void tpalindrome(){
	ofstream myfile;
	myfile.open("truthtable.txt");
	for(int a =0; a<2; a++){
		for(int b =0; b<2; b++){
			for(int c =0; c<2; c++){
				tinputpalindrome(a,b,c,myfile);	
			}
		}	
	}
	myfile.close();
}







void fiveparity(int x1,int x2,int x3,int x4, ofstream& myfile){
	if((x1+ x2 + x3 + x4)%2 ==0){
		myfile<< x1<<x2<<x3<<x4<<1<<endl;		
	}
	else{
	    myfile<< x1<<x2<<x3<<x4<<0<<endl;		
	}
}


void fiveinputparity(){
	ofstream myfile;
	myfile.open("truthtable.txt");
	for(int a =0; a<2; a++){
		for(int b =0; b<2; b++){
			for(int c =0; c<2; c++){
				for(int d =0; d<2; d++){
					//for(int e =0; e<2;e++){
						fiveparity(a, b, c, d,myfile);				
					//}
				}
			}
		}	
	}
	myfile.close();
}
void fivemajority(int x1,int x2, int x3, int x4, int x5, ofstream& myfile){
	
	if((x1+ x2 + x3 + x4 + x5)>=3){
		myfile<< x1<<x2<<x3<<x4<<x5<<1<<endl;	
	}
	else{ myfile<< x1<<x2<<x3<<x4<<x5<<0<<endl;	
	}
}


void fiveinputmajority(){
	ofstream myfile;
	myfile.open("truthtable.txt");
	for(int a =0; a<2; a++){
		for(int b =0; b<2; b++){
			for(int c =0; c<2; c++){
				for(int d =0; d<2; d++){
					for(int e =0; e<2;e++){
						fivemajority(a,b,c,d,e, myfile);				
					}
				}
			}
		}	
	}
	myfile.close();
}
void nand(){
	ofstream myfile;
	myfile.open("truthtable.txt");
	for(int i =0; i<2;i++){
		for(int j=0; j<2;j++){
			if((i+j)==2){
				myfile<<i<<j<<0<<endl;
			}
			else{
				myfile<<i<<j<<1<<endl;
			}
		}
	}
	myfile.close();
}

void myxor(){
	ofstream myfile;
	myfile.open("truthtable.txt");
	for(int i =0; i<2;i++){
		for(int j=0; j<2;j++){
			if((i+j)==1){
				myfile<<i<<j<<1<<endl;
			}
			else{
				myfile<<i<<j<<0<<endl;
			}
		}
	}
	myfile.close();	
}
void sevensegment(){
	ofstream myfile;
	myfile.open("truthtable.txt");
	bitset<7> display;	
	for(int i=0; i<128; i++){	
		display=i;
		if(display[6]==1 && display[5]==1 && display[4]==1 && display[3]==1 && display[2]==1 && display[1]==1 && display[0]==0){
			myfile<<display<<"0000000001"<<endl;
		}
		else if(display[6]==0 && display[5]==1 && display[4]==1 && display[3]==0 && display[2]==0 && display[1]==0 && display[0]==0){
			myfile<<display<<"0000000010"<<endl;
		}
		else if(display[6]==1 && display[5]==1 && display[4]==0 && display[3]==1 && display[2]==1 && display[1]==0 && display[0]==1){
			myfile<<display<<"0000000100"<<endl;
		}
		else if(display[6]==1 && display[5]==1 && display[4]==1 && display[3]==1 && display[2]==0 && display[1]==0 && display[0]==1){
			myfile<<display<<"0000001000"<<endl;
		}
		else if(display[6]==0 && display[5]==1 && display[4]==1 && display[3]==0 && display[2]==0 && display[1]==1 && display[0]==1){
			myfile<<display<<"0000010000"<<endl;
		}
		else if(display[6]==1 && display[5]==0 && display[4]==1 && display[3]==1 && display[2]==0 && display[1]==1 && display[0]==1){
			myfile<<display<<"0000100000"<<endl;
		}
		else if(display[6]==1 && display[5]==0 && display[4]==1 && display[3]==1 && display[2]==1 && display[1]==1 && display[0]==1){
			myfile<<display<<"0001000000"<<endl;
		}
		else if(display[6]==1 && display[5]==1 && display[4]==1 && display[3]==0 && display[2]==0 && display[1]==0 && display[0]==0){
			myfile<<display<<"0010000000"<<endl;
		}
		else if(display[6]==1 && display[5]==1 && display[4]==1 && display[3]==1 && display[2]==1 && display[1]==1 && display[0]==1){
			myfile<<display<<"0100000000"<<endl;
		}
		else if(display[6]==1 && display[5]==1 && display[4]==1 && display[3]==1 && display[2]==0 && display[1]==1 && display[0]==1){
			myfile<<display<<"1000000000"<<endl;
		}
		else{
			myfile<<display<<"0000000000"<<endl;
		}
	}
	myfile.close(); 	
}

/*
void printnetwork(neurons *** array, int layercount,int * larray){
	cout<<"*********************************Network*****************************"<<endl;
	//int layercount = larray.size();
	for(int i=0; i<layercount; i++){
		int layer_neurons = larray[i];
		cout<<"layer "<<i<<":";
		for(int j=0; j<layer_neurons; j++){
			cout<<" 			"<<array[i][j]->value;
		}
		cout<<endl;
		for(int j=0; j<layer_neurons; j++){
			cout<<" 	|input: ";
			if(i!=0){
				int isize = array[i][j]->input.size();
				for(int k=0;k<isize; k++){
					if(k!= (isize-1)){cout<<array[i][j]->input.at(k)->weight<<", ";}
					else{cout<<array[i][j]->input.at(k)->weight;}
				}
			}
			cout<<" output: ";
			if(i!= layercount-1){
				int osize = array[i][j]->output.size();
				for(int k=0;k<osize; k++){
					if(k!= (osize-1)){cout<<array[i][j]->output.at(k)->weight<<", ";}
					else{cout<<array[i][j]->output.at(k)->weight;}
				}
				cout<<"|";
			}
		}
		cout<<endl<<endl<<endl;
	}
}

*/

