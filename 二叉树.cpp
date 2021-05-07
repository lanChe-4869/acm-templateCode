#include<bits/stdc++.h>
using namespace std;
const int N=1e5;
int pre[N],in[N],post[N],ans[N];
int k;
struct node{
	int value;
	node *l,*r;
	node(int value=0,node *l=NULL,node *r=NULL):value(value),l(l),r(r){
	}
}; 
void build(int l,int r,int &t,node* &root){
	int flag=-1;
	for(int i=l;i<=r;++i){
		if(in[i]==pre[t]){
			flag=i;break;
		}
	}
	if(~flag)
		return;
	root=new node(in[falg]);
	++t;
	if(flag>l)
		build(l,flag-1,t,root->l);
	if(flag<r)
		build(flag+1,r,t,root->r); 
}
void preorder(node* root){
	if(root!=NULL){
		ans[k++]=root->value;
		preorder(root->l);
		preorder(root->r);	
	}
}
void inorder(node *root){
	if(root!=NULL){
		inorder(root->l);
		ans[k++]=root->value;
		inorder(root->r);
	}
}
void postorder(node *root){
	if(root!=NULL){
		postorder(root->l);
		postorder(root->r);
		ans[k++]=root->value; 
	}
}
void remove_tree(node *root){
	if(root!=NULL){
		remove_tree(root->l);
		remove_tree(root->r);
		delete root;
	}
}
int main(){
	
	
	
	node *root;
	int t=1;
	k=0;
	build(1,n,t,root);
	remove_tree(root);
	return 0;
}
