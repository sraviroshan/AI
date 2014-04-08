#include <iostream>
#include <math.h>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>         // std::bitset
#include "neurons.h"

using namespace std;

//sigmoid function
double sigmoid(double x){
	double y = 1/(1+ exp(x*-1));
	return y;
}



//function to print value and error of neurons
void print_neurons(neurons *** array, int lc, int * larry){
		for (int m=1 ; m < lc ; m++){
			for (int l= 0 ; l < larry[m] ; l++){

				int isize = array[m][l]->input.size();
				for (int pa = 0 ; pa < isize ; pa++){ 
					cout<< " weight of input edge at layer "<<m<< " : "<<array[m][l]->input.at(pa)->weight<<endl; 
				}	

				cout<< "value of node " << l << " at layer "<<m<< " : "<< array[m][l]->value<<endl;
				cout<< "error of node " << l << " at layer "<<m<< " : "<< array[m][l]->error<<endl;
				int size = array[m][l]->output.size();
				for (int p = 0 ; p < size ; p++){ 
					cout<< " weight of output edge at layer "<<m<< " : "<<array[m][l]->output.at(p)->weight<<endl; 
				}


			cout<<endl;
			}
		cout<<endl;		
		}	
}


//function to print the whole network
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


double iris[7];

void getnext(string s){
	int pos = s.find(" ");
	string str;
	string rem;
	str.assign(s);
	rem.assign(s);
	int index1 = 0;
	while(pos != -1){
		str = rem.substr(0,pos);
		rem = rem.substr(pos+1);	
		iris[index1] = atof(str.c_str());
		pos = rem.find(" ");
		index1++;
	}
	iris[6]=atof(rem.c_str());
}



void forward_propagation(int layercount, int * length, neurons *** array){
	for (int k = 1  ; k < layercount; k++){
		for (int l = 0 ; l < length[k] ; l++){
			double summation = 0;
			int size = array[k][l]->input.size() ;
			for (int m = 0 ; m < size; m++){			
				double weighte = array[k][l]->input.at(m)->weight;
				double inpute = array[k][l]->input.at(m)->in->value;
				summation = summation +  weighte*inpute; 
			}
			array[k][l]->value = sigmoid(summation);		
		}	
	}
}

double last_layer_error_calculation(int layercount, int * length , neurons *** array){
	double cumulative_error = 0;
	for (int k =0 ; k < length[layercount-1]; k++){
		double z=array[layercount-1][k]->idealvalue;
		double y=array[layercount-1][k]->value;
		double delta = (z-y)*y*(1-y);
		array[layercount-1][k]->error = delta;
		cumulative_error = cumulative_error + (z-y)*(z-y);	
	}
	return cumulative_error;
}

void backward_propagation(int layercount, int * length, neurons *** array){
	for (int k = layercount -2 ; k > 0; k--){
		for (int l = 0 ; l < length[k] ; l++){
			double summation = 0;
			double mypreval = array[k][l]->value;
			int size = array[k][l]->output.size() ;
			for (int m = 0 ; m < size; m++){
				double weighte = array[k][l]->output.at(m)->weight;
				double inpute = array[k][l]->output.at(m)->out->error;
				summation = summation +  weighte*inpute; 
			}
			double delta = summation*mypreval*(1-mypreval);
			array[k][l]->error = delta;
		}	
	}
}


void weight_update(int layercount, int * length , neurons *** array,double eta, double momentum){
	for (int k = 1  ; k < layercount; k++){
		for (int l = 0 ; l < length[k] ; l++){
			int size = array[k][l]->input.size();				
			for (int m = 0 ; m < size; m++){	
				double currentweight = array[k][l]->input.at(m)->weight;
				double prevweight = array[k][l]->input.at(m)->pweight;
				double myerror = array[k][l]->error;
				double inval = array[k][l]->input.at(m)->in->value;
				double new_weight = currentweight + (1-momentum)*eta*myerror*inval + momentum*(currentweight-prevweight);						
				array[k][l]->input.at(m)->weight = new_weight;
				array[k][l]->input.at(m)->pweight = currentweight;		
			}
		}		
	}	
}

//main starts here


int main(){
	
	int layercount;
	cout<<"No. of Layers ?"<<endl;
	cin>>layercount;
	
	int i = layercount;
	neurons *** array = new neurons**[layercount]; // 2d array which contains neurons
	int length[layercount];					// array which contains the neuron count for each layer
	
	
	
	//-------------------------------------------------------------------------------------------------------------------------//
	
	//Taking neuron count as input for hidden layers
	for(int k = 0; k < layercount; k++)
    	{
		int neuroncount;
		cout<<"No. of neurons in layer "<<k<<" ?"<<endl;
		cin>>neuroncount;
		array[k] = new neurons*[neuroncount];
		length[k]=neuroncount;	
	}
	
	
	
	//adding neurons to each layer
	for (int k=0 ; k<layercount; k++){
		for (int l =0 ; l < length[k] ; l++ ){
			neurons * nron = new neurons();
			nron->layernumber = k;			
			array[k][l]=nron;
		}
	}

	
	
	cout<<length[0]<<endl;
	double eta;
	cout<<"Learning Rate ? "<<endl;
	cin>>eta;

	double threshold;
	cout<<" Threshold Value ? " <<endl;
	cin>>threshold;

	double momentum;
	cout<<" Momentum ? "<<endl;
	cin>>momentum;

	
	// filling up the network with edges
	for (int m =1 ; m < layercount; m++){
		for (int l =0 ; l < length[m] ; l++ ){
			for (int k =0 ; k< length[m-1]; k++){
				edge * e = new edge();
				e->pweight = e->weight;
				e->in = array[m-1][k];
				e->out = array[m][l];
				array[m][l]->input.push_back(e);
				array[m-1][k]->output.push_back(e);
			}
		}
	}
	
neurons * dummy_neuron = new neurons();	
	for (int m =1 ; m < layercount; m++){
		
		for (int l =0 ; l < length[m] ; l++ ){
			edge * e = new edge();
			e->pweight = e->weight;
			e->in = dummy_neuron;
			e->out = array[m][l];
			array[m][l]->input.push_back(e);
			dummy_neuron->output.push_back(e);
		}
	}
	
	
	int command;				//train or try
	int loop = 0;
	int iterations=0;
	int whileflag = 0;
	string line;
	string line2;
	int inputlines=0;
	ofstream myfile;
	myfile.open("output.txt");
	ifstream infile("datamy.txt");
	for (inputlines = 0; getline(infile,line); ++inputlines){
	}
	infile.close();
	ifstream infile2("datamy.txt");
	while (1){
		cout<<inputlines<<endl;
		cout<<"1 to train and 2 to try"<<endl;
		cin>>command;
		int index;
		if (command==1){
			while(1){
				double cumulative_error = 0;
				loop=0;
				ifstream infile2("datamy.txt");
				for(int index=0; index < inputlines ;index++){
					loop++;
						
					getline(infile2,line2);
					
					int h =0;
					getnext(line2);
					for(h=0; h<length[0]; h++){
						array[0][h]->value = iris[h];
			//			cout<<iris[h]<<" ";
					}
			//		cout<<"| ";
					//cout<<length[0]<<" "<<length[layercount - 1]<<endl;
					for(int g = 0; g < length[layercount-1];g++){
						array[layercount-1][g]->idealvalue = iris[g+h];
		//				cout<<iris[g+h]<<" ";
					}
		//			cout<<endl<<endl;
		//			continue;
				//	return 0;
					//forward propagation starts
					forward_propagation(layercount, length, array);
					// forward propagation ends

					//calculation of error for last layer starts
					cumulative_error = cumulative_error + last_layer_error_calculation(layercount, length, array);
					//calculation of error for last layer ends
					
					
					//backward propagation starts
					backward_propagation(layercount, length, array);
					//backward propagation ends


					//code for weight update starts
					weight_update(layercount, length, array,eta,momentum);
					//code for weight update ends
					
					if (loop == inputlines){
						myfile<<cumulative_error<<" "<<iterations<<endl;
						if (cumulative_error < threshold || iterations > 20000){
							print_neurons(array,layercount,length);
							printnetwork(array,layercount, length);
							whileflag=1;
							break;
						}
						else {
							cout<<"cumulative error : "<<cumulative_error<<endl;
						}
					}	
				}

				infile2.close();
				iterations++;
				if (whileflag == 1){
					break;				
				}
			}
		}			// command 1 ends here
		
		cout<<"perceptron trained"<<endl;
		myfile.close();
		cout<<"No. of iterations "<<iterations<<endl;
		if (command == 2){
			string inputgiven;
				int correctcount =0;		
				int h =0;
				//	cout<<"line is " << line2<<endl;
				ifstream checkfile("checkiris.txt");
				for(int index=0; index< 86 ;index++){					
					getline(checkfile,inputgiven);
			
				getnext(inputgiven);
				for(h=0; h<length[0]; h++ ){
					array[0][h]->value = iris[h];
				}
				
				for(int g=0; g<length[layercount-1]; g++){
					array[layercount-1][g]->idealvalue = iris[g+h];			
				}
			
				//forward propagation ends
				forward_propagation(layercount, length, array);
				//forward propagation ends
				int correct_flag = 0;
				
				for (int k=0 ; k < length[layercount-1]; k++){
					if (array[layercount-1][k]->value > .6 && array[layercount-1][k]->idealvalue == 1){
						correct_flag =1;
					}
					else if (array[layercount-1][k]->value < .4 && array[layercount-1][k]->idealvalue == 0){
						correct_flag =1;
					}
					else{
						correct_flag=0;
					}
				}
				if (correct_flag ==1){
					correctcount++;
				}
			}
			cout<<correctcount<<endl;
			float accuracy = correctcount*100/86;
			cout<<"accuracy is " <<accuracy<<" %"<<endl;
		}			// command 2 ends here
	}			// outer while loop ends here

return 0;
}

