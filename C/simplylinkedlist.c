#include <stdio.h>
#include <stdlib.h>

#define LINESIZE 64

typedef struct node {
	int data;
	struct node* next;
} node;


// Iterate through the list using a single pointer.
void list_iterate(node *head) {
        for (node *p = head; p != 0; p = p->next) {
                printf("%d\n", p->data);
        }
}

// Iterate through the list using a double pointer.
void list_iterate_2(node **lst) {
	node **tracer;
	for (tracer = lst; (*tracer) != 0; tracer = &(*tracer)->next) {
		printf("%d\n", (*tracer)->data);
	}
}

// Insert node in the of the linked list.
int prepend_node(node **lst, int data) {
	node *new_node = malloc(sizeof(node));
	if (new_node == 0) {
		printf("Failed to allocate memory");
		return 0;
	}
	new_node->data = data;
	new_node->next = *lst;
	*lst = new_node;
	return 1;
}

// Destory the whole list.
void list_destroy(node *head) {
	node *q = 0;
        printf("Destroying the list.\n");
        for (node *p = head; p != 0; p = q) {
                printf("Freeing %d with value %d\n", (int)(&(*p)), p->data);
                q = p->next;
                free(p);
        }
}

// Remove the node that matches the data (first occurrence)
int remove_node(node **lst, int data) {
	node **tracer = 0;
	for (tracer = lst; *tracer != 0; tracer = &(*tracer)->next) {
		if ((*tracer)->data == data) {
			break;
		}
	}
	if ((*tracer)->data == data) {
		node *tmp = *tracer;
		*tracer = tmp->next;
		free(tmp);
		return 1;
	}
	return 0;
}

// Insert a node into a list
int list_insert_sorted(node **head, int data) {
	node **tracer;
	node *new_node = malloc(sizeof(node));
	if (new_node == 0) {
		return 0;
	}
	for (tracer = head; *tracer != 0; tracer = &(*tracer)->next) {
		if ((*tracer)->data > data) {
			break;
		}
	}
	new_node->data = data;
	new_node->next = *tracer;
	*tracer = new_node;
	return 1;
}

// Recieve the input from the user and store it in data.
int receive_input(int *data) {
	char line[LINESIZE];
	fgets(line, LINESIZE, stdin);
	if ((sscanf(line, "%d", data)) == 0) {
		return 0;
	}
	return 1;
}

// Prompt the user with choices in the program
void input_prompt() {
	printf("Please input a choice\n 1) Insert into linked list\n 2) Remove from linked list\n 3) Exit\n");
}

// Prompt to ask for data.
void data_prompt() {
	printf("Please enter data: ");
}

// Main
int main(int argc, char **argv) {
	char line[LINESIZE];
	int choice = -1;
	int data = 0;
	node *head = 0;
	node **lst = &head;

	head = 0;

	for (int i = 1; i < argc; i++) {
		printf("%s\n", argv[i]);
	}

	// Continuously get input from user.
	input_prompt();
	while(fgets(line, LINESIZE, stdin)) {
		// Scan the input, continue if no digit has been given.
		if ((sscanf(line, "%d", &choice)) == 0) {
			printf("Input not accepted\n");
			continue;
		}
		
		// Parse the choice from the user.
		switch(choice) {
			case 1:
				printf("Selected Insert \n");
				data_prompt();
				if (receive_input(&data)) {
					list_insert_sorted(lst, data);
					printf("Current List: \n");
					list_iterate_2(lst);
					printf("\n\n\n");
				}	
				break;
			case 2:
				printf("Selected Remove\n");
				data_prompt();
				if (receive_input(&data)) {
					remove_node(lst, data);
					printf("Current List: \n");
					list_iterate_2(lst);
					printf("\n\n\n");
				}
				break;
			case 3:
				printf("Selected Exit\n");
				list_destroy(*lst);
				return 0;
			default:
				printf("Input not accepted\n");
		}
		input_prompt();
	}
	return 0;
}
