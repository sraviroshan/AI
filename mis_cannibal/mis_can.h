#include <iostream>
#include <list>

#include <vector>
#include <utility>
#include <stdio.h>     
#include <stdlib.h>
using namespace std;

class node;

class node
{
public:
	float g_val;
	float h_val;
	int no_mis;
	int no_can;
	bool boat_pos;
	node* parent;
	
	
	node()
	{
		parent = NULL;
	}
};
bool compare(node * n1, node * n2)	
{
		if((n1->no_mis == n2->no_mis) && (n1->no_can == n2->no_can)&&(n1->boat_pos == n2->boat_pos))
		{
			return true;
		}
		else return false;
};

int adj_dist(){
	return 1;
};
bool node_validity(node* n)
{	//cout<<"node_validity"<<endl;
	if(n->no_mis <0 || n->no_can <0 || n->no_can >3||n->no_mis>3)
	{
		return false;
	}
	else if(n->no_mis < n->no_can && n->no_mis > 0 )
	{
		return false;
	}
	else if(n->no_mis > n->no_can && n->no_mis < 3){
		return false;
	}
	else
	{
	 return true;
	}
};
struct n_pair
{
	node* n;
	float e_cost;
};
bool flip_boatpos(bool bs)
{
	if(bs){return false;}
	else return true;
}
list<node*> get_neighbour_puzzle(node* n)
{
	list<node*> nl ;
	float delta = 1;
	int	no_mis = n->no_mis;
	int no_can = n->no_can;
	//who bring the boat from other end
	int mult =1;
	bool boat_pos = n->boat_pos;
	if(boat_pos){mult= -1;}
	
	boat_pos = flip_boatpos(boat_pos);
	


	node * neighbour1 = new	node();
	neighbour1->boat_pos = boat_pos;

	neighbour1->no_mis = no_mis - 2*mult;
	neighbour1->no_can = no_can;
	if(node_validity(neighbour1))
	{
		//cout<<"inside 1"<<endl;
		// n_pair n1;
		// n1.n = neighbour1;
		// n1.e_cost = delta;
		// nl.push_back(n1);
		nl.push_back(neighbour1);
	}
	node * neighbour2 = new	node();
	//boat_pos = boat_pos +1;
	neighbour2->boat_pos = boat_pos;
	neighbour2->no_mis = no_mis -1*mult;
	neighbour2->no_can = no_can -1*mult;
	if(node_validity(neighbour2))
	{
		//cout<<"inside 2"<<endl;
		// n_pair n1;
		// n1.n = neighbour2;
		// n1.e_cost = delta;
		// nl.push_back(n1);
		nl.push_back(neighbour2);
	}
	node * neighbour3 = new	node();
	//boat_pos = boat_pos +1;
	neighbour3->boat_pos = boat_pos;
	neighbour3->no_mis = no_mis -1*mult;
	neighbour3->no_can = no_can;
	if(node_validity(neighbour3))
	{
		//cout<<"inside 3"<<endl;
		// n_pair n1;
		// n1.n = neighbour3;
		// n1.e_cost = delta;
		// nl.push_back(n1);
		nl.push_back(neighbour3);
	}
	node * neighbour4 = new	node();
	//boat_pos = boat_pos +1;
	neighbour4->boat_pos = boat_pos;
	neighbour4->no_mis = no_mis;
	neighbour4->no_can = no_can -1*mult;
	if(node_validity(neighbour4))
	{
		//cout<<"inside 4"<<endl;
		// n_pair n1;
		// n1.n = neighbour4;
		// n1.e_cost = delta;
		// nl.push_back(n1);
		nl.push_back(neighbour4);
	}
	node * neighbour5 = new	node();
	//boat_pos = boat_pos +1;
	neighbour5->boat_pos = boat_pos;
	neighbour5->no_mis = no_mis;
	neighbour5->no_can = no_can- 2*mult;
	if(node_validity(neighbour5))
	{
		//cout<<"inside 5"<<endl;
		//cout<<"inside 1"<<endl;
		// n_pair n1;
		// n1.n = neighbour1;
		// n1.e_cost = delta;
		// nl.push_back(n1);
		// n_pair n1;
		// n1.n = neighbour5;
		// n1.e_cost = delta;
		// nl.push_back(n1);
		nl.push_back(neighbour5);
	}
	return nl;
};
float find_fval(node* n)
{
	return (n->g_val + n->h_val);
};
node* find_minf(list<node *> l)
{
	list<node*>::iterator it = l.begin();
	node* minf = *it;
	for(it;it!=l.end();it++)
	{
		if(find_fval(minf) >= find_fval(*it))
		{
			minf = *it;
		}
	}
	return minf;
};
struct pair_list
{
	list<node*> op;
	list<node*> cl;
};
bool check_inopen(list<node*> op, node* nf)
{
	bool rt =false;
	list<node*>::iterator it = op.begin();
	for(it; it!=op.end();it++)
	{
		if(compare(*it,nf)){ rt= true;}
	}
	return rt;
}
bool check_inclose(list<node*> cl, node* nf)
{
	bool rt =false;
	list<node*>::iterator it = cl.begin();
	for(it; it!=cl.end();it++)
	{
		if(compare(*it, nf)){ rt= true;}
	}
	return rt;
}
int heuristic_puzzle(node* n1)
{
	return ((n1->no_mis + n1->no_can)-1);
}


// pair_list open_node(list<node*> op, list<node*> cl, node* n_to)
// {
// 	list<node*> vnp= get_neighbour_puzzle(n_to);
// 	for(int i=0; i< vnp.size(); i++)
// 	{
		
// 	}
// }
bool print_nodes(node* n)
{
	cout<<n->no_mis<<" "<<n->no_can<<" "<<n->boat_pos<<endl;
}
bool print_neighur(list<node*> v)
{
	list<node*>:: const_iterator iterator;
	for(iterator = v.begin(); iterator!=v.end(); iterator++)
	{
		print_nodes(*iterator);
	}
}
bool print_open_list(list<node*> l)
{
	cout<<"open list : ";	
	list<node*>:: const_iterator iterator;
	for(iterator = l.begin(); iterator!=l.end(); iterator++)
	{
		cout<<"("<<(*iterator)->no_mis<<","<<(*iterator)->no_can<<" "<<(*iterator)->boat_pos<<")";
	}
	cout<<endl;
}