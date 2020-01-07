#include <stdio.h>
#include <stdlib.h>

/* Staaaack API */

typedef struct node {
  int data;
  struct node *next;
} node;

typedef struct stack {
  node *top;
} stack;

// Push
int push(stack *s, int data) {
  node *new_node = malloc(sizeof(node));
  if (new_node == 0) {
    printf("Failure to create new node\n");
    return 0;
  } else {
    new_node->data = data;
    new_node->next = 0;
  }

  if (s->top == 0) {
    printf("Stack is null\n");
    s->top = new_node;
  } else {
    printf("Stack is not null\n");
    new_node->next = s->top;
    s->top = new_node;
  }

  return 1;
}

// Pop
node *pop(stack *s) {
  if (s->top == 0) {
    printf("Pop: Stack is empty\n");
    return 0;
  } else {
    node *tmp = s->top;
    s->top = (s->top)->next;
    return tmp;
  }
}

// Peek
node *peek(stack *s) {
  if (s->top == 0) {
    return 0;
  } else {
    return s->top;
  }
}

// ViewStack
void viewstack(const stack *s) {
  node *i;
  for (i = s->top; i != 0; i = i->next) {
    printf("%d\n", i->data);
  }
}

void viewstack_2(const stack *s) {
	node **tracer;
	for (tracer = &(s->top); *tracer != 0; tracer = &(*tracer)->next) {
		printf("%d\n", (*tracer)->data);
	}
}

// isEmpty
int isempty(const stack *s) {
  if (s->top == 0) {
    return 1;
  } else {
    return 0;
  }
}

// Destroy
void destroy(stack *s) {
  node *q;
  for (node *p = s->top; p != 0; p = q) {
    q = p->next;
    free(p);
  }
  s->top = 0;
}

int main() {
  node *holder;
  stack *s = malloc(sizeof(stack));
  s->top = 0;

  push(s, 2);
  push(s, 3);

  viewstack_2(s);

  destroy(s);

  viewstack_2(s);

  free(s);

  return 0;
}
