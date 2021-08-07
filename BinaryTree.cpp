//Binary Tree
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
struct Node{
    int data;
    struct Node* left;
    struct Node* right;

    Node(int val){
        data = val;
        right = NULL;
        left = NULL;
    }
};
//1. PreOrder Traversal
void preorder(struct Node* root ){
    if(root == NULL)
    return;
    cout<<root->data<<" ";
    preorder(root->left);
    preorder(root->right);
}
//2. PostOrder Traversal
void postorder(struct Node* root ){
    if(root == NULL)
    return;
    postorder(root->left);
    postorder(root->right);
    cout<<root->data<<" ";
}
//3. Build a tree from Preorder & Inorder
int search(int in[],int start,int end,int curr){
    for(int i=start;i<=end;i++){
     if(in[i]==curr)
     return i;
    }
    return -1;
}
Node* buildTree(int pre[],int in[],int start,int end){
    if(start>end)
    return NULL;
    static int idx =0;
    int curr = pre[idx];
    idx++;
    Node* node= new Node(curr);
    if(start == end)
    return node;
    int pos = search(in,start,end,curr);
    node->left = buildTree(pre,in,start,pos-1);
    node->right = buildTree(pre,in,pos+1,end);
    return node;
}
//4.  Level Order Traversal
void levelorder(Node *root){
    if(root==NULL)
    return;
    queue< Node*> q;
    q.push(root);
    q.push(NULL);
    while(!q.empty()){
        Node* node = q.front();
        q.pop();
        if(node!= NULL){
            cout<<node->data;
            if(node->left)
            q.push(node->left);
            if(node->right)
            q.push(node->right);
        }
        else if(!q.empty())
        q.push(NULL);

    }
}
//5. Counting the number of nodes
int countNode(Node* root){
    if(root == NULL)
    return 0;
    return countNode(root->left) + countNode(root->right) +1;
}
//6. Sum of the Nodes
int  countSum(Node* root){
    if(root == NULL)
    return 0;
    return countSum(root->left)+countSum(root->right)+root->data;
}
//7. Height of the Binary Tree
int height(Node* root){
    if(root==NULL)
    return 0;
    int lheight= height(root->left);
    int rheight= height(root->right);
    return max(lheight,rheight)+1;
}
//8. Check is the tree is Height balanced Binary Tree or not
bool isbalance(Node *root){
    if(root == NULL)
    return true;
    if(isbalance(root->left)==false)
    return false;
    if(isbalance(root->right)==false)
    return false;
    int lh=height(root->left);
    int rh=height(root->right);
    if(abs(lh-rh)<=1)
    return true;
    else
    return false;
}
//9.Right View
void rightView(Node* root){
    if(root==NULL)
    return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty())
    {
        int n = q.size();
        for(int i=0;i<n;i++){
            Node* curr=q.front();
            q.pop();
            if(i==n-1)
            cout<<curr->data<<" ";
            if(curr->left != NULL)
            q.push(curr->left);
            if(curr->right != NULL)
            q.push(curr->right);
        }
    }
    
}
void leftView(Node* root){
    if(root==NULL)
    return;
    queue<Node*> q;
    q.push(root);
    while (!q.empty())
    {
        int n= q.size();
        for (int i = 1; i <=n; i++)
        {
            Node* temp = q.front();
            q.pop();
            if(i==1)
            cout<<temp->data<<" ";
            if(temp->left)
            q.push(temp->left);
            if(temp->right)
            q.push(temp->right);
        }
        
    }
    
}
//Shortesr distance between two path
Node* LCA(Node* root,int n1,int n2){
    if(root== NULL)
    return NULL;
    if(root->data==n1 || root->data==n2)
    return root;
    Node* left=LCA(root->left,n1,n2);
    Node* right=LCA(root->right,n1,n2);
    if(left!=NULL && right!=NULL)
    return root;
    if(left==NULL && right==NULL)
    return NULL;
    if(left!=NULL)
    return LCA(root->left,n1,n2);
    return LCA(root->right,n1,n2);
}
int findDist(Node* root,int k,int dist){
    if(root==NULL)
    return -1;
    if(root->data == k)
    return dist;
    int left = findDist(root->left,k,dist+1);
    if(left!=-1)
    return left;
    return findDist(root->right,k,dist+1);
}
int distBtwNodes(Node* root,int n1,int n2){
    Node* lca = LCA(root,n1,n2);
    int d1 = findDist(lca,n1,0);
    int d2 = findDist(lca,n2,0);
    return d1+d2;
}
//Flaten the Binary Tree
void flatten(Node* root){
    if(root==NULL ||(root->left==NULL&& root->right == NULL))
    return;
    if(root->left!=NULL){
    flatten(root->left);
    Node* temp = root->right;
    root->right = root->left;
    root->left = NULL;
    Node* t = root->right;
    while (t->right!= NULL)
    {
        t = t->right;
    }
    t->right = temp;
    }
    flatten(root->right);
    
}
//Max Sum Path from One Node to Another 
int maxpathSunUtil(Node* root,int ans){
    if(root==NULL)
    return 0;
    int left = maxpathSunUtil(root->left,ans);
    int right= maxpathSunUtil(root->right,ans);

    int nodeMax = max(max(root->data,root->data +left+right),max(root->data+ left,root->data + right));
    ans = max(ans,nodeMax);
    int singlepathSum = max(root->data, max(root->data + left,root->data + right));
    return singlepathSum;
}
int maxpathSum(Node* root){
    int ans = INT_MIN;
    maxpathSunUtil(root,ans);
    return ans;
}
int main()
{
    struct Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(5);
    root->left->right = new Node(6);
    cout<<"1.Preorder Traversal- "<<endl;
    preorder(root);
    cout<<"\n2.Postorder Traversal- "<<endl;
    postorder(root);
    //Creating Binary Tree from Preorder and Postorder
    cout<<"\n3.Binary Tree from pre& Inorder\n";
    int pre[] ={1,2,5,6,3};
    int in[] = {5,2,6,1,3};
    int start = 0,end =4;
    Node* newroot= buildTree(pre,in,start,end);
    preorder(newroot);  
    //Level order tree traversal
    cout<<"\n4.Level Order traversal- "<<endl;
    levelorder(root);
    cout<<"\n5.Count the number of Nodes- \n";
    cout<<countNode(root);
    //Count the sum of Nodes
    cout<<"\n6.Count the Sum of nodes->";
    cout<<countSum(root);
    //Height of a tree
    cout<<"\n7.Height of a tree";
    cout<<"\nHeight->"<<height(root)<<endl;
    //Checking the tree is balanced or not
    cout<<"8.Height balance of tree\n";
    if(isbalance(root))
    cout<<"Balanced Tree\n";
    else
    cout<<"Unbalanced Tree\n";
    //Right View of a Binary Tree
    cout<<"Right side view of the tree\n";
    rightView(root);
    cout<<"\nLeft side view of the tree\n";
    leftView(root);
    //Shortest Distance between two path
    int n1,n2;
    cout<<"\nGiven path for n1 = 5 & n2 = 3";
    n1 =5,n2 =3;
    cout<<endl<<distBtwNodes(root,n1,n2);
    //Flatten the Binary tree
    cout<<"\nFlatten the binary Tree";
    flatten(root);
    //Max Sum Path from One Node to Another 
    cout<<"\nMax Sum Path from One Node to Another ";
    cout<<"\nMaximum Sum path of the node -> "<<maxpathSum(root);
}