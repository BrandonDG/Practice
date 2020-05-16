#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define CHECK(PRED) printf("%s...%s\n", (PRED) ? "\033[0;32m passed" : "\033[0;31m FAILED", #PRED)

typedef struct d_array {
  int size;
  int capacity;
  int *arr;
} d_array;

// Function Prototypes
int size(const d_array *da);
int capacity(const d_array *da);
int isEmpty(const d_array *da);
int at(const d_array *da, int index);
void push(d_array *da, int item);
void prepend(d_array *da, int item);
void insert(d_array *da, int index, int item);
void delete(d_array *da, int index);
int pop(d_array *da);
void remove_item(d_array *da, int item);
int find(const d_array *da, int item);
void resize(d_array *da);

// Return size of dynamic array.
int size(const d_array *da) {
  return da->size;
}

// Return the capacity of the dynamic array.
int capacity(const d_array *da) {
  return da->capacity;
}

// Return the bool representing if the dynamic array is empty.
int isEmpty(const d_array *da) {
  return da->size == 0 ? TRUE : FALSE;
}

// Check if index is out of bounds of the size.
void index_iob(int index, int size) {
  if (index >= size) {
    printf("Index out of bounds exception: Index %d does not exist\n", index);
    exit(1);
  }
}

// Insert item item into the dynamic array at index.
void insert(d_array *da, int index, int item) {
  int tmp;

  index_iob(index, da->size + 1);
  resize(da);
  ++da->size;
  for (int i = index; i < da->size; ++i) {
    tmp = da->arr[i];
    da->arr[i] = item;
    item = tmp;
  }
}

// Push an item onto the back of the dynamic array.
void push(d_array *da, int item) {
  insert(da, da->size, item);
}

// Prepend item onto the dynamic array.
void prepend(d_array *da, int item) {
  insert(da, 0, item);
}

// Delete item in dynamic array at index.
void delete(d_array *da, int index) {
  index_iob(index, da->size);

  for (int i = index; i < da->size - 1; ++i) {
    da->arr[i] = da->arr[i + 1];
  }
  da->arr[da->size - 1] = 0;
  --da->size;
  resize(da);
}

// Pop item off the end of the dynamic array.
int pop(d_array *da) {
  int val = da->arr[da->size - 1];
  delete(da, da->size - 1);
  return val;
}

// Remove item from dynamic array if it matches item.
void remove_item(d_array *da, int item) {
  for (int i = da->size - 1; i >= 0; --i) {
    if (da->arr[i] == item) {
      delete(da, i);
    }
  }
}

// Return the item at the given index. Program closes if index is IOB.
int at(const d_array *da, int index) {
  index_iob(index, da->size);
  return *((da->arr) + index);
}

// Return index of the FIRST OCCURRENCE of item. Return -1 if item is not present.
int find(const d_array *da, int item) {
  for (int i = 0; i < da->size; ++i) {
    if (da->arr[i] == item) {
      return i;
    }
  }
  return -1;
}

// Resize dynamic array to be bigger or smaller depending on the difference
// between capacity and size.
void resize(d_array *da) {
  int *new_array;
  char resizing = 0;

  if (da->size >= da->capacity) {
    da->capacity *= 2;
    resizing = 1;
  } else if (da->size <= (da->capacity / 4)) {
    da->capacity /= 2;
    resizing = 1;
  }

  if (resizing) {
    new_array = malloc(sizeof(int) * da->capacity);
    for (int i = 0; i < da->size; ++i) {
      new_array[i] = da->arr[i];
    }
    free(da->arr);
    da->arr = new_array;
  }
}

int main() {
  int tmp = 0;
  d_array *da = malloc(sizeof(d_array));
  da->size = 0;
  da->capacity = 16;
  da->arr = malloc(sizeof(int) * 16);

  for (int i = 0; i < 14; ++i) {
    push(da, i);
  }

  printf("\033[0m\nTesting size(const d_array *da) @ 14\n");
  CHECK(size(da) == 14);

  printf("\033[0m\nTesting capacity(const d_array *da) @ 16\n");
  CHECK(capacity(da) == 16);

  printf("\033[0m\nTesting isEmpty(const d_array *da) @ 14\n");
  CHECK(isEmpty(da) == 0);

  printf("\033[0m\nTesting push(d_array *da, int item) by inserting 15\n");
  push(da, 15);
  CHECK(da->arr[da->size - 1] == 15);

  printf("\033[0m\nTesting prepend(d_array *da, int item) by inserting -1\n");
  prepend(da, -1);
  CHECK(da->arr[0] == -1);

  printf("\033[0m\nTesting insert(d_array *da, int index, int item) by inserting 2 @ 2\n");
  insert(da, 2, 2);
  CHECK(da->arr[2] == 2);

  printf("\033[0m\nTesting resize(d_array *da) by pushing past capacity\n");
  CHECK(capacity(da) == 32);

  printf("\033[0m\nTesting delete(d_array *da, int index) by deleting at 0\n");
  delete(da, 0);
  CHECK(da->arr[0] == 0);

  printf("\033[0m\nTesting pop(d_array *da) by popping at 15\n");
  tmp = pop(da);
  CHECK(tmp == 15);

  printf("\033[0m\nTesting remove_item(d_array *da, int item) removing the first 2\n");
  remove_item(da, 2);
  CHECK(da->arr[1] == 1 && da->arr[2] == 3);

  printf("\033[0m\nTesting at(const d_array *da, int index) by grabbing index 9\n");
  tmp = at(da, 9);
  CHECK(tmp == 10);

  printf("\033[0m\nTesting find(const d_array *da, int item) by grabbing index 13\n");
  tmp = find(da, 13);
  CHECK(tmp = 12);

  printf("\033[0m\nTesting find(const d_array *da, int item) by failing to grab 2\n");
  tmp = find(da, 2);
  CHECK(tmp = -1);

  return 0;
}
