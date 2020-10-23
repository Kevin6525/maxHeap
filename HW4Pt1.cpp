#include <cstddef>
#include <iostream>
using namespace std;
//Creation of treeNode
struct treeNode {
	int data;
	treeNode *left, *right;
};
//struct to allow us to add nodes to the tree/modify it in main
struct treeNode *setNode(int data)
{
	struct treeNode* newNode = new treeNode;
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}
/* Was trying to use this function to compare the children and parent node to identify how to swap, but I think this way is simpler
int findMax(int a, int b, int c)
{
	if(a >= b && a >= c)
	{
		return a;
	}
	else if(b >= a && b >= c)
	{
		return b;
	}
	else
	{
		return c;
	}
}
*/
//Void function that helps us swap to node values (i.e. swap node w child)
void swap(treeNode * node1, treeNode* node2)
{
	int temp = node1->data;
	node1->data = node2->data;
	node2->data = temp;
}
//The function takes in two nodes as parameters
//This is to help us keep track of the previous parent node when going through the tree (in the case that
//we swap the child and parent, but the grandparent node value is less than the parent we will catch it)
//We go to the left-most child first by using recursion and compare it to the parent and swap if needed
//Then we compare the lowest right child to the parent and continue (We're going left to right through the tree w recursion)
//Note that there is a case to catch NULL for previousRoot, which will be addressed in the reorder function
void maxHeap(treeNode* root, treeNode* previousRoot)
{
	if(root == NULL)
	{
		return;
	}
	//Switched order of the conditions in if for the initial case, where the root data would be larger than the null data, which would make the program get stuck and force exit
	if(previousRoot != NULL && root->data > previousRoot->data)
	{
		cout<<"Swapped "<<root->data<<" with "<<previousRoot->data<<endl;
		swap(root, previousRoot);
	}
	maxHeap(root->left, root);
	maxHeap(root->right, root);
	return;
}
void printTree(treeNode* root) 
{ 
    if (root == NULL) 
    {
    	return;
	} 
     
    printTree(root->left);
    cout << root->data << " ";
    printTree(root->right); 
} 
//We call maxHeap with NULL as previousRoot as a placeholder for the pointer
//When we enter maxHeap recursively, we will use the parent as the previousRoot instead of NULL
//We also use recursion to call maxHeap to all of the tree
void reorder(treeNode* root)
{    
    if(root==NULL)
	{
		return;
	}
    maxHeap(root, NULL);
    reorder(root->left);
    reorder(root->right);
}
//Not sure why the second print isn't working, but I have the maxHeap function print out what values are being swapped so it is a little more clear.
//The tree is being printed in Inorder traversal
//The tree:
//             8
//          /    \
//        1       9 
//       / \     / \
//     2    4   3   5
int main()
{
	treeNode* node = setNode(8);
	node->left = setNode(1);
	node->right = setNode(9);
	node->left->left = setNode(2); 
    node->left->right = setNode(4); 
    node->right->left = setNode(3); 
    node->right->right = setNode(5);
    cout<<"Original tree in inorder (can be found in comments as well): "<<endl;
    printTree(node);
    cout<<endl;
	reorder(node);
	cout<<"New tree in inorder: "<<endl;
	printTree(node);
	return 0;
}
