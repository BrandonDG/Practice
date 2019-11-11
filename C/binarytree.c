#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node *left;
	struct node *right;
} node;

// Inorder traversal.
void inorder_traversal(node *root) {
	if (root != 0) {
		inorder_traversal(root->left);
		printf("%d\n", root->data);
		inorder_traversal(root->right);
	}
}

// Preorder traversal.
void preorder_traversal(node *root) {
	if (root != 0) {
		printf("%d\n", root->data);
		preorder_traversal(root->left);
		preorder_traversal(root->right);
	}
}

// Postorder traversal.
void postorder_traversal(node *root) {
	if (root != 0) {
		postorder_traversal(root->left);
		postorder_traversal(root->right);
		printf("%d\n", root->data);
	}
}

void destroy_tree(node *root) {
	if (root != 0) {
		destroy_tree(root->left);
		destroy_tree(root->right);
		free(root);
	}
}

// Create a new node and return a pointer.
node *create_node(int data) {
	node *new_node = malloc(sizeof(node));
	new_node->data = data;
	new_node->left = new_node->right = 0;
	return new_node;
}

// Insert node into binary tree.
node *insert_node(node* root, int data) {
	if (root == 0) {
		return create_node(data);
	}

	if (data < root->data) {
		root->left = insert_node(root->left, data);
	} else if (data > root->data) {
		root->right = insert_node(root->right, data);
	}

	return root;
}

// Main
int main() {
	// Create root
	node *root = 0;

	// Insert data into binary tree.
	root = insert_node(root, 50);
	insert_node(root, 100);
	insert_node(root, 150);
	insert_node(root, 25);
	insert_node(root, 5);

	// Traverse the tree in various forms.
	printf("Preorder\n");
	preorder_traversal(root);
	printf("\nInorder\n");
	inorder_traversal(root);
	printf("\nPostorder\n");
	postorder_traversal(root);

	printf("\nDestroying List\n");
	destroy_tree(root);

	return 0;
}
