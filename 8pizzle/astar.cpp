#include "puzzle.h"

list<node*> open_list;
list<node*> close_list;



void astar_algo(node* start,node* goal){
	
	//open_list.push_back(start)
	start->state= 1;
	openset.insert(start);
	list<node*> n_list;
	while(!openset.empty()){
		
		node* q;
		//q = find_minf(open_list);
		q = set_front();
		print_vec(q->id);
		if(q==goal){
			cout << "found the goal" <<endl;
			//return;
			cout<<endl<<"s"<<endl;
			print_vec(q->id);
			cout<<endl;
			while(q->parent!=NULL){
				print_vec((q->parent)->id);
				q = q->parent;
				cout<<endl;
			}
			return;
		}
		else
		{
			//close_list.push_back(q);
			//open_list.remove(q);
			remove_setfront();
			n_list = get_neighbour_puzzle(q);
			list<node*>:: const_iterator iterator;
			for (iterator = n_list.begin(); iterator != n_list.end(); ++iterator) {
				if((*iterator)->state == 0)
				{
					(*iterator)->parent = q;
					(*iterator)->g_val = q->g_val + adj_dist();
					(*iterator)->h_val = heuristic_puzzle(*iterator);
					(*iterator)->state =1;
					openset.insert((*iterator));
				}
				else if((*iterator)->state == 1)
				{
					int tmp = q->g_val + adj_dist();
					if((*iterator)->g_val > tmp)
					{
						node * n = (*iterator);
						openset.erase(n);
						n->g_val = tmp;
						n->parent = q;
						openset.insert(n);	
					}
				}
				else 
				{
					int tmp = q->g_val + adj_dist();
					if((*iterator)->g_val > tmp)
					{
						node * n = (*iterator);
						n->g_val = tmp;
						n->state =1;
						n->parent = q;
						openset.insert(n);
					}
				}	
			}
		}
	}
	cout << "Empty openlist.Should not come here" <<endl;

}

int main(){
	
	vector<vector<int> > final = {{1,2,3},{4,5,6},{7,8,-1}};
	vector<vector<int> > start = {{1,2,3},{-1,8,6},{4,5,7}};
	node* s = new node();
	node* e = new node();

	s->id = start;
	list<node*> gn=  get_neighbour_puzzle(s);
	print_list(gn);
	//return 1;
	e->id = final;
	s->g_val = 0;
	e->h_val = 0;
	s->parent = NULL;
	s->h_val = heuristic_puzzle(s);

	mymap[hash_key_n(s)] = s;
	mymap[hash_key_n(e)] = e;

	astar_algo(s,e);

	cout << "Size of graph discovered " << mymap.size() <<endl;
	return 0;
}
