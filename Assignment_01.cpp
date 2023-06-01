#include <bits/stdc++.h>
using namespace std;

struct Node {
	int data;
	struct Node *left, *right;
	Node(int data)
	{
		this->data = data;
	}
};

Node* create(Node* root){
	int data;
	cin>>data;

	if (data == -1){
		return NULL;
	}

	root = new Node(data);

	root->left = create(root->left);
	root->right = create(root->right);

	return root;
}

void printLevelorder(Node* root) {
    if(root == NULL){
		return;
	}

    queue<Node*> q; 
    q.push(root); 

    while(!q.empty()) {
        int size = q.size(); 
        for(int i = 0;i<size;i++) {
            Node *node = q.front(); 
            q.pop(); 
            if(node->left != NULL) q.push(node->left); 
            if(node->right != NULL) q.push(node->right); 
            cout<<node->data<<" "; 
        }
		cout<<endl; 
    } 
}

void printPostorder(Node* node){
	if (node == NULL)
		return;

	printPostorder(node->left);
	printPostorder(node->right);
	cout << node->data << " ";
}

void printInorder(Node* node){
	if (node == NULL)
		return;

	printInorder(node->left);
	cout << node->data << " ";
	printInorder(node->right);
}

void printPreorder(Node* node){
	if (node == NULL)
		return;

	cout << node->data << " ";
	printPreorder(node->left);
	printPreorder(node->right);
}

bool dep_search(Node* root, int lvl, int val, int height){
	if (root == NULL){
		return false;
	}

	if (height > lvl){
		return false;
	}

	if (root->data == val){
		return true;
	}

	return (dep_search(root->left, lvl, val, height+1) or dep_search(root->right, lvl, val, height+1));
}

bool bfs_search(Node* root, int val, int &tc, int &sc) {
    if(root == NULL){
		return false;
	}

	if (root->data == val){
		return true;
	}

    queue<Node*> q; 
    q.push(root);
	sc++; 

    while(!q.empty()) {
        int size = q.size();
		 
        for(int i = 0;i<size;i++) {
			tc++;
            Node *node = q.front();
            q.pop(); 
            if(node->left != NULL){
				q.push(node->left);
				sc++;
			} 
            if(node->right != NULL){
				q.push(node->right);
				sc++;
			}

            if(node->data == val){
				return true;
			} 
        }
    }

	return false; 
}

int main(){
	Node* root = NULL;
	root = create(root);

	cout << "\nLevel order traversal of binary tree is \n";
	printLevelorder(root);

	cout << "\nPreorder traversal of binary tree is \n";
	printPreorder(root);

	cout << "\nInorder traversal of binary tree is \n";
	printInorder(root);

	cout << "\nPostorder traversal of binary tree is \n";
	printPostorder(root);

	int choice;
	cout<<"\n\nUser Manual : \n1. DFS Search \n2. BFS Search";
	cout<<"\n\nEnter your choice : ";
	cin>>choice;


	if (choice == 1){
		int val, lvl;
		int tc;

		cout<<"\n\nEnter the value you want to search : ";
		cin>>val;
		cout<<"Enter the level to which you want to search : ";
		cin>>lvl;
		
		if (dep_search(root, lvl, val, 1)){
			cout<<"\nElement found";
		}
		else{
			cout<<"\nElement Not found";
		}
	}
	else if (choice == 2){
		int val;
		int tc = 0;
		int sc = 0;

		cout<<"\n\nEnter the value you want to search : ";
		cin>>val;
	
		if (bfs_search(root, val, tc, sc)){
			cout<<"\nElement Found\n";
		}
		else{
			cout<<"\nElement Not Found\n";
		}

		cout<<"\nTime complexity : "<<tc;
		cout<<"\nSpace Complexity : "<<sc;
	}
	else{
		cout<<"\nInvalid choice!!!\n";
	}

	return 0;
}
