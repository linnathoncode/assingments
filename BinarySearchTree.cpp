#include <iostream>

using namespace std;

class node
{
	
	public:
		node * left;
		node * right;
		int data;
};

class BinarySearchTree
{
	
	private:
		node * leaf;
		node *root;
		
	public:
		BinarySearchTree()
		{
			root = NULL;
		}
	bool isEmpty() const {return root == NULL;}
	void print_inorder();
	void inorder(node *);
	void print_preorder();
	void preorder(node *);
	void print_postorder();
	void postorder(node *);
	void insert(int);
	void remove(int);
};

//smaller elements go left
//bigger elements go right

void BinarySearchTree::insert(int d)
{
	
	node * t = new node;
	node * parent;
	t -> data = d;
	t -> right = NULL;
	t -> left = NULL;
	parent = NULL;
	
	//if its a new tree root is the new node
	if(isEmpty()) root = t; 
	else
	{
		
		//curr pointer to keep track of the nodes
		
		node * curr;
		curr = root;
		
		while(curr)
		{
			
			parent = curr;
			if(t -> data > curr -> data) curr = curr -> right;	
			else curr = curr -> left;
		}
		//when it reaches to the bottom of the tree 
		//it checks if the new node should go to its parents right or left
		if(t -> data < parent -> data) parent -> left = t;
		else parent -> right = t;
	}
	
}

void BinarySearchTree::remove(int d)
{
	//locate the element
	bool found = false;
	
	if(isEmpty())
	{	
		cout << "Tree is empty! "<<endl;
		return; 
	}
	
	node *curr;
	node *parent;
	curr = root;
	
	while(curr)
	{
		if(curr -> data == d)
		{
			found = true;
			break;
		}		
		else
		{
			parent = curr;
			if(d> curr -> data) curr = curr -> right;
			else curr = curr -> left;
		}	
		
	}
	
	if(!found)
	{
		cout<<"Data not found!"<<endl;
		return;
	}	
	
	
	//if data found there are 3 cases to remove
	//0 - wer are removing the root 
	//1 - we are removing a leaf
	//2 - we are removing a node with 1 child
	//3- we are removing a node with 2 child

	//removing root
	if(curr == root && root != NULL)
	{
		//1 - root is the only node
		if(root -> left == NULL && root -> right == NULL)
		{
			delete root;
			root = NULL;
			return;
		}
		
		//2 - root has only left child
		
		if((root -> left != NULL) && (root -> right == NULL))
		{
			//if root has only left child
			//we should go all the way right in the left side and find the biggest node
			if((root -> left != NULL) && (root -> right == NULL))
			{	
				curr = root -> left;
				node *currPa = root;
				if(curr -> right)
				{	
					while(curr -> right)
					{
						currPa = curr;
						curr = curr -> right;	
					}
				}
				//if the rightest node has a left node
				if(curr -> left)
				{
					currPa -> right = curr -> left;
					curr -> left = NULL;
					root -> data = curr -> data;
					delete curr;
				}
				else
				{
					root -> data = curr -> data;
					delete curr;
					currPa -> right = NULL;
				}
					
			}
			

		}
		//root has 2 children or root has only right child
		//if root has 2 children we can just pretend that it only has right child
	
		else
		{
			//if root has only right child 
		
			curr = root -> right;
			node *currPa = root;
			if(curr -> left)
			{	
				while(curr -> left)
				{
					currPa = curr;
					curr = curr -> left;
				}
			}
			//if the leftist node has a right node
			if(curr -> right)
			{
				currPa -> left = curr -> right;
				curr -> right = NULL;
				root -> data = curr -> data;
				delete curr;
			}
			else
			{
				root -> data = curr -> data;
				delete curr;
				currPa -> left = NULL;
			}
		
		}
			
		return;		
	}
	
	
	
	//node with single child
	if((curr -> left == NULL) && (curr -> right != NULL) 
	||(curr ->left != NULL) && (curr -> right == NULL))
	{
		
		// only right child
		if(curr -> left == NULL && curr -> right != NULL )
		{
			if(parent -> left == curr)
			{
				
				parent -> left = curr -> right;
				delete curr;
			}
			else
			{
				
				parent -> right = curr -> right;
				delete curr;
			}
			return;
		}	
		
		
		// only left child
		else
		{
		
			if(parent -> left == curr)
			{
				
				parent -> left = curr -> left;
				delete curr;
			}
			else
			{
				
				parent -> right = curr -> left;
				delete curr;
			}
			return;
		
		}	
	}
	
	//leaf node 
	if(curr -> left == NULL && curr -> right == NULL)
	{
		if(parent -> left == curr) parent -> left = NULL;
		else parent -> right = NULL;
		delete curr;
		return;
	}
	
	//node with 2 children
	//replace node with smallest value in right subtree
	if(curr -> left != NULL && curr -> right != NULL)
	{
		node * chkr;
		chkr = curr -> right;
		
		if((chkr -> left = NULL ) && (chkr -> right == NULL))
		{
			curr = chkr;
			delete chkr;
			curr -> right = NULL;
		}
		//right child has children
		else
		{
			//if the node's right child has a left child
			//move all the way down to the left to locate smallest element
			
			if((curr-> right) -> left != NULL)
			{
				node *lcurr;
				node *lcurrPa;
				lcurrPa = curr -> right;
				lcurr = (curr -> right) -> left;
				while(lcurr -> left != NULL)
				{
					lcurrPa = lcurr;
					lcurr = lcurr -> left;					
				}
				curr -> data = lcurr -> data;
				delete lcurr;
				lcurrPa -> left = NULL;
			}
			
			//if the node's right child has no left child
			else
			{
				node *temp;
				temp = curr -> right;
				curr -> data = temp -> data;
				curr -> right = temp -> right;
				delete temp;
			}
			
		}
	return;
	}
		
}
	
	
void BinarySearchTree::print_inorder()
{
	inorder(root);
}

//left value right order
void BinarySearchTree::inorder(node* p)
{
	if(p != NULL)
	{	
		//recursion
		if(p-> left) inorder(p -> left);
		cout << " "<< p ->data<< " ";
		if(p -> right) inorder(p -> right);
	}
	else return;	
}

void BinarySearchTree::print_preorder()
{
	preorder(root);
}

//value left right order
void BinarySearchTree::preorder(node* p)
{
	if(p != NULL)
	{	
		//recursion
		cout << " "<< p ->data<< " ";
		if(p-> left) preorder(p -> left);
		if(p -> right) preorder(p -> right);
	}
	else return;	
}

void BinarySearchTree::print_postorder()
{
	postorder(root);
}

//left right value order
void BinarySearchTree::postorder(node* p)
{
	if(p != NULL)
	{	
		//recursion
		if(p-> left) postorder(p -> left);
		if(p -> right) postorder(p -> right);
		cout << " "<< p ->data<< " ";
	}
	else return;	
}

int main()
{
	BinarySearchTree b;
    int ch,tmp,tmp1;
    while(1)
    {
       cout<<endl<<endl;
       cout<<" Binary Search Tree Operations "<<endl;
       cout<<" ----------------------------- "<<endl;
       cout<<" 1. Insertion/Creation "<<endl;
       cout<<" 2. In-Order Traversal "<<endl;
       cout<<" 3. Pre-Order Traversal "<<endl;
       cout<<" 4. Post-Order Traversal "<<endl;
       cout<<" 5. Removal "<<endl;
       cout<<" 6. Exit "<<endl;
       cout<<" Enter your choice : ";
       cin>>ch;
       switch(ch)
       {
           case 1 : cout<<" Enter Number to be inserted : ";
                    cin>>tmp;
                    b.insert(tmp);
                    break;
           case 2 : cout<<endl;
                    cout<<" In-Order Traversal "<<endl;
                    cout<<" -------------------"<<endl;
                    b.print_inorder();
                    break;
           case 3 : cout<<endl;
                    cout<<" Pre-Order Traversal "<<endl;
                    cout<<" -------------------"<<endl;
                    b.print_preorder();
                    break;
           case 4 : cout<<endl;
                    cout<<" Post-Order Traversal "<<endl;
                    cout<<" --------------------"<<endl;
                    b.print_postorder();
                    break;
           case 5 : cout<<" Enter data to be deleted : ";
                    cin>>tmp1;
                    b.remove(tmp1);
                    break;
           case 6 : system("pause");
                    return 0;
                    break;
       }
    }
}
