#ifndef NTREE_H_INCLUDED
#define NTREE_H_INCLUDED

#include <bits/stdc++.h>
using namespace std;
template<typename T>
class node{
 public:
  T data;
  node *left=NULL;
  node *right=NULL;

};
template<class g>
class b_tree{
  node <g>*root=NULL;
  node <g>* l=root; //creating node which holds value of data type g (int/char/string)
  public:
       b_tree();                            //constructor
      ~b_tree();                               //destructor
      int empty();                             //returns 1 if root is equal to NULL else returns 0
      void creat(g arr[],int n);               //creates tree using elements of an arry arr(elements are in level order traversal)
      void insertl(g data);
  virtual  node <g> *getroot();                //returns reference to root node of tree
      g * preorder(node<g>*);                  //returns pointer to an array of type g containing preorder traversal
      g * postorder(node<g>*);                 //returns pointer to an array of type g containing postorder traversal
      g * inorder(node<g>*);                   //returns pointer to an array of type g containing inorder traversal
      int count(node<g>*Root);                 //returns no. of nodes in tree with Root=root
      node<g>*retrieve(g DataKey);             //returns reference to node with data=Data
      node<g>*getParent(g DataKey);            //returns reference to parent of Node
      bool Delete(g delKey);                   //deletes data=delKey, returns 1 if successful
      void swap(node<g>*a,node<g>*b);          //swaps data at node a & b
      bool search(g X,node<g> *);              //searches X in tree,returns 1 if found else 0
      int height(node<g> *Root);               //returns the height of tree
      int leafcount(node<g>* Root) ;           //returns number of leaf node in tree
      bool isfull(struct node<g> *) ;          //returns 1 if binary tree is full binary tree else returns 0
};
template<class g>
class bs_tree:public b_tree<g>{
  node <g>* bstroot=NULL;
 public:
        bs_tree();                                  //constructor
       ~bs_tree();                                  //destructor
        void bstinsert(node <g> *,g );              //inserts element in bs tree
        node<g>*getroot();                          //returns reference to root node of tree
        void creatbst(g arr[],int n);               //creats bs tree using array elements
        int bstcount(node<g>*Root);                 //returns no. of nodes in tree with Root=root
        node<g>*bstretrieve(node<g>*Root,g DataKey);//returns reference to node with data=Data
        node<g>*bstgetParent(g DataKey);            //returns reference to parent of Node
        bool bstdelete(g delKey);                   //deletes data=delKey, returns 1 if successful
        node<g>*bstLargest(node<g>*Root);           //returns reference to node with largest data value
        void bstswap(node<g>*a,node<g>*b);          //swaps data at node a & b
        bool bstsearch(g key,node<g>*r);

};

///////////////////////////////////////BST//////////////////////////////////////////////////
template<typename g>
bs_tree<g>::bs_tree() //constructor for binary search tree
{
    bstroot=NULL;

}
template<typename g> //destructor for binary search tree
bs_tree<g>::~bs_tree()
{
}
template<typename g>// returns 1 if tree is empty else 0
void bs_tree<g>:: bstinsert(node <g> *root1,g data)
{
    node <g> *node1=new node<g>; //creating node to insert
    node1->data=data;
    node1->left=NULL;
    node1->right=NULL;
    if(root1==NULL)           //if root1 is NULL then tree is empty
        {bstroot=node1;}           //the new node is root node
    else
    {
        node <g> *x=root1;
        node<g> *y=NULL;
        while(x!=NULL)
        {

            y=x;
            if(data<x->data)
                x=x->left;
            else if(data>x->data)
                x=x->right;
        }
        if (y==NULL)
            y=node1;
        else if(data<y->data)
            y->left=node1;
        else if(data >y->data)
            y->right=node1;
    }
}
template<class g>
node<g>* bs_tree<g>::getroot()
     {

         return bstroot;
     }
template<class g>
void bs_tree<g>::creatbst(g arr[],int n)
{
    for(long int i=0;i<n;i++)
    {
        bstinsert(this->bstroot,arr[i]);
    }
}




template <class g>
int bs_tree<g>::bstcount(node<g>*Root)//returns no. of nodes in tree with Root=root
{
    if(Root==NULL)
        return 0;
    return bstcount(Root->left)+bstcount(Root->right)+1;
}

template <class g>
node<g>* bs_tree<g>::bstLargest(node<g>*Root)//returns reference to node with largest data value
{
    if(Root->right==NULL)
        return Root;
    bstLargest(Root->right);
}

template <class g>
node<g>* bs_tree<g>::bstretrieve(node<g>*Root,g DataKey)//returns reference to node with data=DataKey
{
    if(Root==NULL)//empty tree
        return NULL;
    if(Root->data<DataKey)
        bstretrieve(Root->right,DataKey);
    else if(Root->data>DataKey)
        bstretrieve(Root->left,DataKey);
    else
        return Root;
}

template <class g>
node<g>* bs_tree<g>::bstgetParent(g DataKey)//returns reference to parent of node with data=DataKey
{
    node<g>*Node=bstroot;
    node<g>*Parent=bstroot;
    if(Node==NULL||bstroot->data==DataKey)//empty tree or if no parent
        return NULL;
    while(1)
    {
        if(Node==NULL)
            return NULL;
        if(Node->data==DataKey)
            return Parent;
        else if(Node->data<DataKey)
        {
            Parent=Node;
            Node=Node->right;
        }
        else if(Node->data>DataKey)
        {
            Parent=Node;
            Node=Node->left;
        }
    }
}

template <class g>
bool bs_tree<g>::bstdelete(g delKey)//deletes node with data=delKey, returns 1 if successful
{
    if(bstroot==NULL)//empty tree
        return false;
    node<g>*delNode=bstretrieve(bstroot,delKey);
    if(delNode==NULL)//not found
        return false;
    node<g>*Parent=bstgetParent(delKey);
    if(delNode->right==NULL)//no right subtree
    {
        if(Parent->right==delNode)
            Parent->right=delNode->left;
        else
            Parent->left=delNode->left;
        delete delNode;
    }
    else if(delNode->left==NULL)//no left subtree
    {
        if(Parent->right==delNode)
            Parent->right=delNode->right;
        else
            Parent->left=delNode->right;
        delete delNode;
    }
    else
    {
        node<g>*exc=bstLargest(delNode->left);
        bstswap(delNode,exc);
        exc=NULL;
        delete exc;
    }
    return true;
}

template <class g>
void bs_tree<g>::bstswap(node<g>*a,node<g>*b)//swaps data at node a & b
{
    g temp=a->data;
    a->data=b->data;
    b->data=temp;
}
template<class g>
bool bs_tree<g>::bstsearch(g key,node<g>*r)
{
    if(r==NULL)
        return false;
    if(r->data==key)
        return true;
    if(key<r->data)
    {
        if(r->left!=NULL)
           return bstsearch(key,r->left);
    }
    if(key>r->data)
    {
        if(r->right!=NULL)
            return bstsearch(key,r->right);
    }
}

//////////////////////////////////BINARY TREE////////////////////////////////////////////////////////////
template<typename g>
b_tree<g>::b_tree() //constructor for binary tree
{
    root=NULL;

}
template<typename g> //distructor for binary tree
b_tree<g>::~b_tree()
{
}
template<typename g>// returns 1 if tree is empty else 0
int b_tree<g>::empty()
{
    if(root==NULL)
        return 1;
    return 0;
}
template<typename g>
node<g>* b_tree<g>::getroot()
{
    return root;
}
template<class g>
void b_tree<g>::creat(g arr[],int n)
{ node  <g> *rroot=NULL;
  queue <node <g>*> Q;

  for(long long int i=0;i<n;i++)
  {
     node <g>*b_node = new node<g>;
     b_node->data=arr[i];
     b_node->left=NULL;
     b_node->right=NULL;
    if (rroot == NULL)
        rroot = b_node;

    else if (Q.front()->left == NULL)

            {
                Q.front()->left =b_node;
            }

    // The right child of the current Node is used
    // if it is available. Since the left child of this
    // node has already been used, the Node is popped
    // from the queue after using its right child.
    else {
           Q.front()->right = b_node;
           Q.pop();
         }

    // When a new node is created, its
    // address is pushed into the queue.
    // So that its children Nodes can be used later.

    Q.push(b_node);
  }
    root=rroot;
}
template<class g>
void b_tree<g>::insertl(g data)
{
   node <g>*b_node = new node<g>;
     b_node->data=data;
     b_node->left=NULL;
     b_node->right=NULL;
     queue <node<g>*> Q;
     if(root==NULL)
            {root=b_node;
            return ;}
    else
    {
        Q.push(root);
        while(Q.empty()!=1)
        {
            if(Q.front()->left==NULL)
            {
                Q.front()->left=b_node;
                return ;
            }
            else if(Q.front()->right==NULL)
            {
                Q.front()->right=b_node;
                return ;
            }
            else{
                Q.push(Q.front()->left);
                Q.push(Q.front()->right);

            }
            Q.pop();
        }
        while(!Q.empty())
            Q.pop();
    }


}

template<typename h>
h *b_tree<h>::preorder(node<h>*root1)             //returns pointer to an array of type g containing preorder traversal
{
    h *arr =new h[count(root1)];    //crneating dynamic array of size=number of nodes
    int i=0;
    stack<node<h>*> stk;
    if(root1==NULL)
        return arr;
    else
       {
         stk.push(root1);
         while(stk.empty()==0)
         {
              node<h> *temp=stk.top();
             arr[i++]=temp->data;
             stk.pop();
             if(temp->right!=NULL)
                stk.push(temp->right);
             if(temp->left!=NULL)
                stk.push(temp->left);

         }
         return arr;
      }
}

template<typename h1>
h1* b_tree<h1>::postorder(node<h1>* root2)
{
    int i=0;
   h1 *arr1 =new h1[count(root2)];
   stack <node<h1>*> stk1,stk2;

      stk1.push(root2);

      while(stk1.empty()==0)
       {
        node<h1> *temp=stk1.top();
        stk1.pop();
        stk2.push(temp);
        if(temp->left)
            stk1.push(temp->left);
        if(temp->right)
            stk1.push(temp->right);
       }
       while(stk2.empty()==0)
       {
         node<h1> *temp2=stk2.top();
         stk2.pop();
         arr1[i++]=temp2->data;
       }
      return arr1;


}
template<typename h>
h *b_tree<h>::inorder(node<h>*root3)
{

    h *arr =new h[count(root3)];
    int i=0;
    stack<node<h>*> stk;


    node<h> *temp=root3;
    while(temp!=NULL||!stk.empty())
        {

          if(temp!=NULL)
          {
              stk.push(temp);
              temp=temp->left;
          }
          else
          {
            temp=stk.top();
            stk.pop();
            arr[i++]=temp->data;
            temp=temp->right;
          }

        }



    return arr;
}

template <class g>
int b_tree<g>::count(node<g>*Root)//returns no. of nodes in tree with Root=root
{
    if(Root==NULL)
        return 0;
    return count(Root->left)+count(Root->right)+1;
}
template <class g>
node<g>* b_tree<g>::retrieve(g data)			//returns reference to node with data=Data
{
	queue <node<g>*> q;					//queue for level order traversal
	q.push(root);						//starting with root
	while(!q.empty())
	{
		node<g> *a=q.front();
		q.pop();
		if(a->data==data)				//found, return
			return a;
		if(a->left!=NULL)
			q.push(a->left);			//storing address of branches
		if(a->right!=NULL)
			q.push(a->right);			//storing address of branches
	}
	return NULL;						//not found
}

template <class g>
node<g>* b_tree<g>::getParent(g data)	//returns reference to parent of Node
{
	if(data==root->data)
		return NULL;
	queue <node<g>*> q;
	q.push(root);
	while(!q.empty())
	{
		node<g> *a=q.front();
		q.pop();
		if((a->right&&a->right->data==data)||(a->left&&a->left->data==data))
			return a;
		if(a->left!=NULL)
			q.push(a->left);
		if(a->right!=NULL)
			q.push(a->right);
	}
	return NULL;
}

template <class g>
void b_tree<g>::swap(node<g>*a,node<g>*b)//swaps data at node a & b
{
    g temp=a->data;
    a->data=b->data;
    b->data=temp;
}

template <class g>
bool b_tree<g>::Delete(g delkey)		//deletes data=delKey, returns 1 if successful
{
	if(root==NULL)
		return false;
	if(root->left==NULL&&root->right==NULL)
	{
		if(root->data==delkey)
		{
			root==NULL;
			return true;
		}
		else
			return false;
	}
	node<g> *deepest;
	node<g> *delNode;
	queue <node<g>*> q;
	q.push(root);
	while(!q.empty())
	{
		deepest=q.front();
		q.pop();
		if(deepest->data==delkey)
			delNode=deepest;
		if(deepest->left)
			q.push(deepest->left);
		if(deepest->right)
			q.push(deepest->right);
	}
	if(delNode!=NULL)
	{
		node<g> *parent=getParent(deepest->data);
		delNode->data=deepest->data;
		if(parent->left==deepest)
			parent->left=NULL;
		else
			parent->right=NULL;
		delete deepest;
		return true;
	}
	return false;
}

template<typename g>
int b_tree<g>:: height(node<g> *Root)
          {   //two variable for counting height of left and right child
              int x=0,y=0;
              //checking tree empty condition
                if(Root==NULL)
                   return 0;
              //calculate height of tree with recursive function
              x=height(Root->left);
              y=height(Root->right);
              //compare both side height tree and give largest height
                if(x>y)
                  return x+1;
                else
                  return y+1;
           }
//function for Searching element in Tree
template<typename g>
  bool b_tree<g>:: search(g X,node<g> *Root)
          {  //checking tree exist beyond or not
               if(Root==NULL){
                 return false;}

           //check whether element is a matching or not
              if(Root->data==X)
                 {
                    return true;}
            //if not match then goto child node for check
              bool x=search(X,Root->left);
              if(x)
                return true;
             bool y= search(X,Root->right);
             if(y)
                return true;

           }
  template<typename g>
  int b_tree<g>::leafcount(node<g>* Root)
  {
      if(Root==NULL)                       //return 0 if root is NULL
        return 0;
      if(Root->left==NULL&&Root->left==NULL) //if left and right child nodes are NULL return 1
        return 1;
     else
        return leafcount(Root->right) + leafcount(Root->left); //else recursively call function for left and right child

  }
template<typename g>
bool b_tree<g>:: isfull(struct node<g> *root1)
  {
    if(root1==NULL)            //returns 1 if root1 is null
     return true;
    if(root1->left==NULL&&root1->right==NULL) //returns 1 if it is leaf node
     return true;

    if( (root1->left)&&(root1->right))        //checks for right and left sub tree
     {
      return isfull(root1->left)&&isfull(root1->right);
     }
    return false;                           //if none of above condition works
}



/*int main()
{
b_tree <char> b2;
char bbc[]={'b','a','c','d','e','f','g','h','i','j','k'};


 bs_tree<int> b;
 bs_tree<char> bb;
 bb.creatbst(bbc,11);

b.bstinsert(b.getroot(),10);
b.bstinsert(b.getroot(),55);
b.bstinsert(b.getroot(),20);





    return 0;
}*/

#endif // NTREE_H_INCLUDED
