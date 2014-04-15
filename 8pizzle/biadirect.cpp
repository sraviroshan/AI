#include "biadirect.h"

list<node*> open_list;
list<node*> close_list;



void astar_algo(node* start,node* goal,node* start_e,node* goal_e){
	
	//open_list.push_back(start)
	start->state= 1;
	start_e->state=1;
	openset.insert(start);
	openset_e.insert(start_e);
	list<node*> n_list;
	list<node*> n_list_e;
	int count =0;
	int step_count =0;
	while(!openset.empty() && !openset_e.empty()){
		
		node* q;
		node* q_e;
		//q = find_minf(open_list);
		q = set_front();
		q_e = set_front_e();
		print_vec(q->id);
		string q_key = hash_key_v(q->id);
		string q_e_key = hash_key_v(q_e->id);
		if(check_hashmap_e(q_key).tval && check_hashmap_e(q_key).n->state==2)
		{
			cout << "found the match" <<endl;
			cout<<endl<<endl;
			print_vec(q->id);
			cout<<endl;
			count++;
			while(q->parent!=NULL){
				print_vec((q->parent)->id);
				q = q->parent;
				cout<<endl;
				count++;
			}
			cout<<"sssssssssss"<<endl;
			node* n1 = check_hashmap_e(q_key).n;
			print_vec(n1->id);
			cout<<endl;
			count++;
			while(n1->parent!=NULL){
				print_vec((n1->parent)->id);
				n1 = n1->parent;
				cout<<endl;
				count++;
			}
			cout<<"count: "<<count-3<<endl;
			cout<<"step count: "<<2*step_count<<endl;
			return;
		}
		else if(check_hashmap(q_e_key).tval && check_hashmap(q_e_key).n->state==2)
		{
			cout << "found the match" <<endl;
			cout<<endl<<endl;
			print_vec(q_e->id);
			cout<<endl;
			count++;
			while(q_e->parent!=NULL){
				print_vec((q_e->parent)->id);
				q_e = q_e->parent;
				cout<<endl;
				count++;
			}
			cout<<"sssssssssss"<<endl;
			node* n1 = check_hashmap(q_e_key).n;
			print_vec(n1->id);
			cout<<endl;
			count++;
			while(n1->parent!=NULL){
				print_vec((n1->parent)->id);
				n1 = n1->parent;
				cout<<endl;
				count++;
			}
			cout<<"count: "<<count-3<<endl;
			cout<<"step count: "<<2*step_count<<endl;								
			return;
		}

		else
		{
			step_count++;
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
					(*iterator)->h_val = heuristic_puzzle((*iterator), goal->id);
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
			/*******************************end************/
			remove_setfront_e();
			n_list_e = get_neighbour_puzzle_e(q_e);
			//list<node*>:: const_iterator iterator;
			for (iterator = n_list_e.begin(); iterator != n_list_e.end(); ++iterator) {
				if((*iterator)->state == 0)
				{
					(*iterator)->parent = q_e;
					(*iterator)->g_val = q_e->g_val + adj_dist();
					(*iterator)->h_val = heuristic_puzzle((*iterator),goal_e->id);
					(*iterator)->state =1;
					openset_e.insert((*iterator));
				}
				else if((*iterator)->state == 1)
				{
					int tmp = q_e->g_val + adj_dist();
					if((*iterator)->g_val > tmp)
					{
						node * n_e = (*iterator);
						openset_e.erase(n_e);
						n_e->g_val = tmp;
						n_e->parent = q_e;
						openset_e.insert(n_e);	
					}
				}
				else 
				{
					int tmp = q_e->g_val + adj_dist();
					if((*iterator)->g_val > tmp)
					{
						node * n_e = (*iterator);
						n_e->g_val = tmp;
						n_e->state =1;
						n_e->parent = q;
						openset_e.insert(n_e);
					}
				}	
			}
		}
	}
	cout << "Empty openlist.Should not come here" <<endl;

}

int main(){
	
	vector<vector<int> > final = {{1,2,3},{4,5,6},{7,8,-1}};
	vector<vector<int> > start = {{1,2,-1},{3,8,6},{4,5,7}};
	node* s = new node();
	node* e = new node();
	node* s_e = new node();
	node* e_e = new node();

	s->id = start;
	list<node*> gn=  get_neighbour_puzzle(s);
	print_list(gn);
	//return 1;
	e->id = final;
	s->g_val = 0;
	e->h_val = 0;
	s->parent = NULL;
	s->h_val = heuristic_puzzle(s,e->id);

	s_e->id = final;
	e_e->id = start;
	s_e->g_val=0;
	e_e->h_val=0;
	s_e->h_val= heuristic_puzzle(s_e,e_e->id);
	mymap[hash_key_n(s)] = s;
	mymap[hash_key_n(e)] = e;
	mymap_e[hash_key_n(s_e)] = s_e;
	mymap_e[hash_key_n(e_e)] = e_e;


	astar_algo(s,e,s_e,e_e);

	cout << "Size of graph discovered " << mymap.size() <<endl;
	cout << "Size of graph discovered " << mymap_e.size() <<endl;
	cout<<"no of different node "<<count_diff_node()<<endl;
	return 0;
}
