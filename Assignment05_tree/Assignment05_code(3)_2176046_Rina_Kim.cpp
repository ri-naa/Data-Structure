#include "stdlib.h"
#include "stdio.h"
#include "string.h"

typedef struct TreeNode {
	int data;
	struct TreeNode* left, * right, * parent;
}TreeNode;

//		 G
//   C		  F
// A   B    D   E

TreeNode n1 = { 'A',NULL,NULL,NULL };
TreeNode n2 = { 'B',NULL,NULL,NULL };
TreeNode n3 = { 'C',&n1,&n2,NULL };
TreeNode n4 = { 'D',NULL,NULL,NULL };
TreeNode n5 = { 'E',NULL,NULL,NULL };
TreeNode n6 = { 'F',&n4,&n5, NULL };
TreeNode n7 = { 'G',&n3,&n6,NULL };
TreeNode* exp = &n7;

TreeNode* tree_predecessor(TreeNode* p) { 

	TreeNode* y = (TreeNode*)malloc(sizeof(TreeNode));
	if (p->left != NULL) {
		y = p->left;
		while (y->right != NULL) {
			y = y->right;
		}
		return y;
	}

	y = p->parent;
	while (y != NULL && p == y->left) {
		p = y;
		y = y->parent;
	}
	return y;

}

void main() {

	TreeNode* q = exp;
	n1.parent = &n3;
	n2.parent = &n3;
	n3.parent = &n7;
	n4.parent = &n6;
	n5.parent = &n6;
	n6.parent = &n7;
	n7.parent = NULL;

	while (q->right) q = q->right; 
	do
	{
		printf("%c\n", q->data);
		q = tree_predecessor(q);
	} while (q);

}
