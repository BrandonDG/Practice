#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node *next;
} node;

typedef struct queue {
  node *front;
} queue;

// Enqueue
void enqueue(queue *q, int data) {
  node *new_node = malloc(sizeof(node));
  node *i;
  if (new_node == 0) {
    printf("Unable to allocate data for new node\n");
    return;
  } else {
    new_node->data = data;
    new_node->next = 0;
  }

  if (q->front == 0) {
    q->front = new_node;
  } else {
    i = q->front;
    while (i->next != 0) {
      i = i->next;
    }
    i->next = new_node;
  }
}

// Dequeue
node *dequeue(queue *q) {
  node *tmp;
  if (q->front == 0) {
    return 0;
  } else {
    tmp = q->front;
    q->front = (q->front)->next;
    return tmp;
  }
}

// Peek
node *peek(const queue *q) {
  if (q->front == 0) {
    return 0;
  } else {
    return q->front;
  }
}

// List
void viewqueue(const queue *q) {
  node *i = q->front;
  while (i != 0) {
    printf("%d\n", i->data);
    i = i->next;
  }
}

// Destroy
void destroy_queue(queue *q) {
  node *p, *n;
  if (q->front == 0) {
    return;
  }

  for (p = q->front; p != 0; p = n) {
    n = p->next;
    free(p);
  }
  q->front = 0;
}

int main() {
  queue *q = malloc(sizeof(queue));
  node *tmp;

  enqueue(q, 2);
  enqueue(q, 3);
  enqueue(q, 4);
  enqueue(q, 5);

  viewqueue(q);

  destroy_queue(q);

  enqueue(q, 2);

  printf("------------------\n");
  viewqueue(q);

  destroy_queue(q);
  free(q);

  return 0;
}
