#include <iostream>
#include <string>

using namespace std;

#define CHECK(PRED) printf("%s...%s\n", (PRED) ? "\033[0;32m passed" : "\033[0;31m FAILED", #PRED)

// d_array class template.
template <class T>
class d_array {
private:
  T *arr;
  int size;
  int capacity;

  // Function to resize the capacity of the array subject
  // to size.
  void resize() {
    bool resized = false;
    if (size == capacity) {
      capacity *= 2;
      resized = true;
    } else if (size == (capacity / 4)) {
      capacity /= 2;
      resized = true;
    }

    if (resized) {
      T *n_arr = new T[capacity];
      for (int i = 0; i < size; ++i) {
        n_arr[i] = arr[i];
      }
      delete[] arr;
      arr = n_arr;
    }
  }

public:
  // Return size of array.
  int get_size() {
    return size;
  }

  // Return capacity of array.
  int get_capacity() {
    return capacity;
  }

  // Is it empty?
  bool isEmpty() {
    return size == 0;
  }

  // Check if the given index is out of bounds.
  bool index_iob(int index, int max) {
    return index > max;
  }

  // Insert data into given index.
  void insert(T data, int index) {
    T tmp;
    if (index_iob(index, size + 1)) {
      return;
    }
    resize();
    for (int i = index; i < size; ++i) {
      tmp = arr[i];
      arr[i] = data;
      data = tmp;
    }
    arr[size] = data;
    ++size;
  }

  // Push data to the end.
  void push(T const data) {
    insert(data, size);
  }

  // Prepend data.
  void prepend(T const data) {
    insert(data, 0);
  }

  // Remove item at the given index.
  void delete_index(int index) {
    --size;
    resize();
    for (int i = index; i < size; ++i) {
      arr[i] = arr[i + 1];
    }
  }

  // Remove all items with given data.
  void remove_item(T item) {
    for (int i = size - 1; i >= 0; --i) {
      if (arr[i] == item) {
        delete_index(i);
      }
    }
  }

  // Find FIRST occurrence of item in list.
  int find(T item) {
    for (int i = 0; i < size; ++i) {
      if (arr[i] == item) {
        return i;
      }
    }
    return -1;
  }

  // Pop item off of the end and return it.
  T pop() {
    T tmp = arr[size - 1];
    delete_index(size - 1);
    return tmp;
  }

  // Return item at given index.
  T at(int index) {
    return arr[index];
  }

  // Constructor.
  d_array() {
    size = 0;
    capacity = 2;
    arr = new T[capacity];
  }

  // Deconstructor
  ~d_array() {
    delete[] arr;
  }

};

// Main
int main() {
  d_array<string> da;
  for (int i = 0; i < 14; ++i) {
    da.push(to_string(i));
  }

  printf("\033[0m\nTesting get_size() @ 14\n");
  CHECK(da.get_size() == 14);

  printf("\033[0m\nTesting get_capacity() @ 16\n");
  CHECK(da.get_capacity() == 16);

  printf("\033[0m\nTesting isEmpty() @ 14\n");
  CHECK(da.isEmpty() == 0);

  printf("\033[0m\nTesting push(T item) by inserting \"15\"\n");
  da.push("15");
  CHECK(da.at(da.get_size() - 1) == "15");

  printf("\033[0m\nTesting prepend(T item) by inserting -1\n");
  da.prepend("-1");
  CHECK(da.at(0) == "-1");

  printf("\033[0m\nTesting insert(T data, int index) by inserting 2 @ 2\n");
  da.insert("2", 2);
  CHECK(da.at(2) == "2");

  printf("\033[0m\nTesting resize() by pushing past capacity in previous test\n");
  CHECK(da.get_capacity() == 32);

  printf("\033[0m\nTesting delete_index(int index) by deleting at 0\n");
  da.delete_index(0);
  CHECK(da.at(0) == "0");

  printf("\033[0m\nTesting pop() by popping at 15\n");
  CHECK(da.pop() == "15");

  printf("\033[0m\nTesting remove_item(int item) removing the both 2s\n");
  da.remove_item("2");
  CHECK(da.at(1) == "1" && da.at(2) == "3");

  printf("\033[0m\nTesting at(int index) by grabbing index 9\n");
  CHECK(da.at(9) == "10");

  printf("\033[0m\nTesting find(int item) by grabbing index 13\n");
  CHECK(da.find("13") == 12);

  printf("\033[0m\nTesting find(const d_array *da, int item) by failing to grab 2\n");
  CHECK(da.find("2") == -1);

  return 0;
}
