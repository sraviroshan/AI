#include <iostream>
#include <list>
#include <vector>
#include <utility>
#include <stdio.h>     
#include <stdlib.h>
#include <unordered_map>
#include <set>

using namespace std;
//node1->g_val == node2->g_val && node1->h_val == node2->h_val


struct node{
	node* parent;
	vector<vector<int> > id;
	int g_val;
	int h_val;
	int state;
	//0= not initialise, 1= open list, 2= close list
		
	node(){
		parent = NULL;
		state =0;
	}
};
struct lt 
{
    bool operator()(const node* v1, const node * v2)
    {
        if((v1->g_val + v1->h_val)<(v2->g_val + v2->h_val)) return true;
        return false;
    }
};
multiset<node*, lt> openset; 

node* set_front()
{
	multiset<node*,lt>::iterator it;
	it = openset.begin();
	return *it;
}
bool remove_setfront()
{
	multiset<node*,lt>::iterator it;
	it = openset.begin();
	(*it)->state=2;
	openset.erase(it);	
}



unordered_map<string,node*> mymap; 
bool compare(node* node1 , node* node2){
		if(node1->id == node2->id && node1->g_val == node2->g_val && node1->h_val == node2->h_val){
			return true;
		}
		else return false;
	}
/////////////////////////////////////////
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



int adj_dist(){
	return 1;
}

pair<int,int> original_pos(int n){
	pair<int,int> pos;
	if(n==1){
		pos.first = 0; pos.second = 0;
	}
	if(n==2){
		pos.first = 0; pos.second = 1;
	}
	if(n==3){
		pos.first = 0; pos.second = 2;
	}
	if(n==4){
		pos.first = 1; pos.second = 0;
	}
	if(n==5){
		pos.first = 1; pos.second = 1;
	}
	if(n==6){
		pos.first = 1; pos.second = 2;
	}
	if(n==7){
		pos.first = 2; pos.second = 0;
	}
	if(n==8){
		pos.first = 2; pos.second = 1;
	}
	return pos;
}

int diff(pair<int,int> p1, pair<int,int> p2){
	int a = p1.first - p2.first;
	int b = p1.second - p2.second;
	return abs(a) + abs(b);
}

pair<int,int> find_pos(int n , vector<vector<int> > v){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(v[i][j] == n){
				pair<int,int> p (i,j);
				return p;
			}
		}
	}
	
}




int heuristic_puzzle(node* n){
	//return 1;
	int sum =0;
	pair<int,int> p1;
	pair<int,int> p2;
	for(int i=1;i<9;i++){
		p1 = find_pos(i,n->id);
		p2 = original_pos(i);
		sum = sum + diff(p1,p2) ;	
	}
	srand( time(0));
	//random heuristic 
	// int rande = rand() % (sum +1) ;
	// cout<<"rand: "<< rande<<endl;
	// return rande;
	return sum;
}


void print_vec(vector<vector<int> > v){
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			cout<< v[i][j] << " ";
		}
		cout<<endl;

	}
}
void print_list(list<node*> nl)
{
	list<node*>:: iterator it;
	for (it= nl.begin(); it != nl.end(); it++)
	{
		print_vec((*it)->id);
		cout<<endl;
	}
			
}
//index validity
bool index_validity(int a, int b)
{
	if(a<0 || b<0) return false;
	else if(a>2 || b>2) return false;
	else return true;
}
//hash key genrater
string hash_key_n(node* n)
{
	string key="";
	for(int i=0; i<3;i++)
	{
		for(int j=0; j<3;j++)
		{
			key = key.append(to_string(n->id[i][j])); 
		}
	}
	return key;
}

//hash key from vector
string hash_key_v(vector<vector<int>> v)
{
	string key="";
	for(int i=0; i<3;i++)
	{
		for(int j=0; j<3;j++)
		{
			key = key.append(to_string(v[i][j])); 
		}
	}
	return key;
}
struct r_pair
{
	node* n;
	bool tval;
};

//find in hash map
r_pair check_hashmap(string key)
{
	r_pair ck;
	unordered_map<string,node*>::const_iterator got = mymap.find (key);
	if(got == mymap.end())
	{
		ck.tval = false;
	}
	else
	{
		ck.tval= true;
		ck.n = got->second;
	}
	return ck;
}


list<node*> get_neighbour_puzzle(node* b){
	list<node*> mylist;
	cout<<"hash key :  "<<hash_key_n(b)<<endl<<endl;
	//node* n1 = new node();
	//n1->id = b->id;
	int pos1 =0;int pos2=0;int id1 , id2  ,id3, id4 = 0;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(b->id[i][j] == -1){
				pos1 = i;
				pos2 = j;
			}
		}
	}

		vector<vector<int>> v_n,v_s,v_e,v_w;
		
		if(index_validity(pos1-1, pos2)){
			v_n = b->id;
			v_n[pos1][pos2] =v_n[pos1-1][pos2];
			v_n[pos1-1][pos2]=-1;
			string v_ns= hash_key_v(v_n);
			r_pair v_np =check_hashmap(v_ns);
			if(v_np.tval)
			{
				mylist.push_back(v_np.n);			
			}
			else
			{
				node* north = new node();
				north->id = v_n;
				mymap[v_ns]= north;
				mylist.push_back(north);	
			}
		}
		if(index_validity(pos1+1, pos2)){
			v_s = b->id;
			v_s[pos1][pos2] =v_s[pos1+1][pos2];
			v_s[pos1+1][pos2]=-1;
			string v_ss= hash_key_v(v_s);
			r_pair v_sp =check_hashmap(v_ss);
			if(v_sp.tval)
			{
				mylist.push_back(v_sp.n);			
			}
			else
			{
				node* south = new node();
				south->id = v_s;
				mymap[v_ss]= south;
				mylist.push_back(south);	
			}
		}
		if(index_validity(pos1, pos2-1)){
			v_w = b->id;
			v_w[pos1][pos2] =v_w[pos1][pos2-1];
			v_w[pos1][pos2-1]=-1;
			string v_ws= hash_key_v(v_w);
			r_pair v_wp =check_hashmap(v_ws);
			if(v_wp.tval)
			{
				mylist.push_back(v_wp.n);			
			}
			else
			{
				node* west = new node();
				west->id = v_w;
				mymap[v_ws]= west;
				mylist.push_back(west);	
			}
		}
		if(index_validity(pos1, pos2+1)){
			v_e = b->id;
			v_e[pos1][pos2] =v_e[pos1][pos2+1];
			v_e[pos1][pos2+1]=-1;
			string v_es= hash_key_v(v_e);
			r_pair v_ep =check_hashmap(v_es);
			if(v_ep.tval)
			{
				mylist.push_back(v_ep.n);			
			}
			else
			{
				node* east = new node();
				east->id = v_e;
				mymap[v_es]= east;
				mylist.push_back(east);	
			}
		}
		

	return mylist;

}
