#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int key;
	struct TreeNode* left, * right;
} TreeNode;

void insert_node(TreeNode** root, int key)
{
	TreeNode* p, * t; //p=parent, t=current
	TreeNode* n;
	t = *root;
	p = NULL;
	
	while (t != NULL) {
		if (key == t->key) {
			return;
		}
		p = t;
		if (key < t->key) t = t->left;
		else t = t->right;
	}
	
	n = (TreeNode*)malloc(sizeof(TreeNode));
	if (n == NULL) return;
	n->key = key;
	n->left = n->right = NULL;

	if (p != NULL)
		if (key < p->key)
			p->left = n;
		else p->right = n;
	else *root = n;
}

void inorder(TreeNode* root) {
	if (root) {
		inorder(root->left); 
		printf("%5d\t", root->key); 
		inorder(root->right);
	}
}

int random(int n) {
	return rand() % n;
}

void main() {
	TreeNode* root = NULL;

	int input_size = 1000;
	int data_maxval = 10000;

	int* input = (int*)malloc(sizeof(int) * input_size);

	for (int i = 0; i < input_size; i++) {
		input[i] = random(data_maxval);
		insert_node(&root, input[i]);
	}

	inorder(root);
}