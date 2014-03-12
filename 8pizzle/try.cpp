#include <set>
#include <iostream>

using namespace std;

struct node
{
	int f;
	node(int x){
		f=x;
	}
};
struct lt {
    bool operator()(const node* v1, const node * v2)const
    {
        if((v1->f)<(v2->f)) return true;
        return false;
    }
};
int main()
{
	multiset<node*, struct lt> openset; 
	node* a1 = new node(2);
	node* a2 = new node(7);
	node* a3 = new node(5);

	openset.insert(a1);
	openset.insert(a2);
	openset.insert(a3);
	multiset<node*,lt>::iterator it;
	it = openset.begin();
	cout<<(*it)->f<<endl;

}
