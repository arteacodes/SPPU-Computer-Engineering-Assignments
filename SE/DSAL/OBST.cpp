/*
To write a program for implementing optimal binary search tree.
*/

#include <bits/stdc++.h>
using namespace std;

class Node{
	string data;
	Node* left;
	Node* right;
public:
	Node(string d){
		data=d;
		left=NULL;
		right=NULL;
	}
	friend class obst;
};

class obst{
	Node* root;
	int n;
	string *a;
	int *p;
	int *q;
	int **r;
	int **w;
	int **c;
public:
	obst(){
		root=NULL;
		cout<<"Enter the no. of nodes in tree :";
		int num;
		cin>>num;

		n=num;
		a=new string[n+1];
		p=new int[n+1];
		q=new int[n+1];

		r=new int*[n+1];
		w=new int*[n+1];
		c=new int*[n+1];

		for(int i=0;i<=n;i++){
			r[i]=new int[n+1];
			w[i]=new int[n+1];
			c[i]=new int[n+1];
		}

		cout<<"Enter node values";
		for(int i=1;i<=n;i++) cin>>a[i];

		cout<<"\nEnter successfull probability :";
		for(int i=1;i<=n;i++) cin>>p[i];

		cout<<"\nEnter unsuccessfull probability :";
		for(int i=0;i<=n;i++) cin>>q[i];

		cout<<"\nall values accepted"<<endl;
		calculate_wt();
		display();
	}
	void calculate_wt(){
		for(int i=0;i<n;i++){
			w[i][i]=q[i];
			r[i][i]=0;
			c[i][i]=0;

			w[i][i+1]=q[i]+p[i+1]+q[i+1];
			c[i][i+1]=w[i][i+1];
			r[i][i+1]=i+1;
		}

		w[n][n]=q[n];
		r[n][n]=0;
		c[n][n]=0;

		for(int m=2;m<=n;m++){
			for(int i=0;i<=n-m;i++){
				int j=i+m;
				int k;
				int min=9999;
				w[i][j]=w[i][j-1]+p[j]+q[j];
				for(int i1=i+1;i1<j;i1++){
					int sum1=c[i][i1-1]+c[i1][j];
					if(sum1<min){
						min=sum1;
						k=i1;
					}
				}
				c[i][j]=w[i][j]+min;
				r[i][j]=k;
			}
		}
		root=create_tree(0,n);
	}
	Node* create_tree(int i,int j){
		Node* temp;
		if(i==j){
			temp=NULL;
		}
		else{
			temp=new Node(a[r[i][j]]);
			temp->left=create_tree(i, r[i][j] - 1);
			temp->right=create_tree(r[i][j],j);
		}
		return temp;
	}
	void inorder(Node* temp){
		if(temp==NULL) return;

		inorder(temp->left);
		cout<<temp->data<<" ";
		inorder(temp->right);\
	}

	void preorder(Node* temp){
		if(temp==NULL) return;

		cout<<temp->data<<" ";
		preorder(temp->left);
		preorder(temp->right);
	}

	void display(){
		cout<<"Table :"<<endl<<endl;
		cout<<std::right << std::setw(13);
		for(int m=0;m<=n;m++){
			for(int i=0;i<=n-m;i++){
				int j=i+m;
				cout<<"Weight ("<<i<<","<<j<<") : "<<w[i][j]<<std::right <<setw(13);
			}
			cout<<endl;
			for(int i=0;i<=n-m;i++){
				int j=i+m;
				cout<<"Cost ("<<i<<","<<j<<") : "<<c[i][j]<<std::right << std::setw(13);
			}
			cout<<endl;
			for(int i=0;i<=n-m;i++){
				int j=i+m;
				cout<<"Root ("<<i<<","<<j<<") : "<<r[i][j]<<std::right << std::setw(13);
			}
			cout<<endl<<endl;
		}

		cout<<"Minimum cost : ";
		cout<<c[0][n]<<endl;
		cout<<"Tree :"<<endl;
		cout<<"Inorder :";
		inorder(root);
		cout<<endl;
		cout<<"Preorder :";
		preorder(root);
		cout<<endl;
	}
};
int main() {
	obst tr;
	return 0;
}
