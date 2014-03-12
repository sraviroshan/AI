#include "mis_can.h"

list<node*> open_list;
list<node*> close_list;

// node* find_minf(list<node*> l){
// 	node* n = new node();
// 	n = l.front();
// 	int min = l.front()->g_val + l.front()->h_val;
// 	list<node*>:: const_iterator iterator;
// 	for (iterator = l.begin(); iterator != l.end(); ++iterator) {
// 		if((*iterator)->g_val + (*iterator)->h_val < min){
// 			n = *iterator;
// 		}
//  	}
//  	return n;
// }

void astar_algo(node* start,node* goal){
	
	open_list.push_back(start);
	list<node*> n_list;
	while(!open_list.empty()){
		
		print_open_list(open_list);
		node* q = new node();
		q = find_minf(open_list);
		if(compare(q,goal)){
			cout<<"terminate"<<endl;
			//print_nodes(q);
			while(q->parent!=NULL){
				print_nodes(q);
				q = q->parent;
			}
			break;
		}
		else
		{
			//cout<<"in open_list"<<endl;
			close_list.push_back(q);
			open_list.remove(q);
			print_nodes(q);
			cout<<endl;
			n_list = get_neighbour_puzzle(q);
			print_neighur(n_list);
			list<node*>:: const_iterator iterator;
			list<node*>:: const_iterator iterator1;
			//cout<<"sravi"<<n_list.size()<<endl;
			for (iterator = n_list.begin(); iterator != n_list.end(); ++iterator) 
			{
				//cout<<" get_neighbour_puzzle"<<endl;
				(*iterator)->parent = q;
				(*iterator)->g_val = q->g_val + adj_dist();
				(*iterator)->h_val = heuristic_puzzle(*iterator);
			}
			for (iterator = n_list.begin(); iterator != n_list.end(); ++iterator) 
			{	
				for (iterator1 = close_list.begin(); iterator1 != close_list.end(); ++iterator1) 
				{	
					if(compare(*iterator,*iterator1))
					{	//cout<<"close_list"<<endl;
						if((*iterator)->g_val < (*iterator1)->g_val)
						{	//cout<<"close_list"<<endl;
							close_list.remove(*iterator1);
							open_list.push_back(*iterator);
						}
						break;
					}
				}
			}
			for (iterator = n_list.begin(); iterator != n_list.end(); ++iterator)
			{	
				for (iterator1 = open_list.begin(); iterator1 != open_list.end(); ++iterator1) 
				{	
					if(compare(*iterator,*iterator1))
					{	//cout<<"open_list"<<endl;
						if((*iterator)->g_val < (*iterator1)->g_val)
						{	cout<<"open list"<<endl;
							open_list.remove(*iterator1);
							open_list.push_back(*iterator);
						}
						break;
					}					
				}
			}
			for(iterator = n_list.begin(); iterator !=n_list.end(); iterator ++)
			{
				if(!check_inopen(open_list, *iterator) && !check_inclose(close_list, *iterator))
				{	//cout<<"_list"<<endl;
					open_list.push_back(*iterator);
				}
			}
		}
	}
}

int main(){
	
	//vector<vector<int> > final = {{1,2,3},{4,5,6},{7,8,-1}};
	//vector<vector<int> > start = {{1,2,3},{4,5,6},{-1,7,8}};
	node* n1 = new node();
	node* n2 = new node();
	// n1->id = start;
	// n2->id = final;

	n1->no_mis=3;
	n1->no_can=3;
	n1->boat_pos = 0;
	n1->boat_pos=0;
	n2->no_mis=0;
	n2->no_can=0;
	n2->boat_pos=1;

	n1->g_val = 0;
	n2->h_val = 0;
	n1->parent = NULL;
	n1->h_val = heuristic_puzzle(n1);
	astar_algo(n1,n2);
	return 0;
}
