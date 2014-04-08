#include <iostream>
#include <cstdlib>
using namespace std;

class neurons;
class edge;

class neurons {

public :
double value;
double idealvalue;
double error;
int layernumber;
vector<edge*> input;
vector<edge*> output;

neurons(){
	error=0;
	value = -1;
	input.resize(0);
	output.resize(0);
}
};



class edge {

public :
double weight;
double pweight;
neurons * in;
neurons * out;
edge(){
	weight=(double)(rand()%1000)/1000;
	pweight =-1;
}
};



