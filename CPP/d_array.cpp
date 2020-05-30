#include <iostream>
#include <string>

using namespace std;

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
  for (int i = 0; i < 16; ++i) {
    da.prepend(to_string(i));
  }

  da.delete_index(0);
  da.delete_index(4);
  da.remove_item("9");

  cout << "Pop: " << da.pop() << endl;
  cout << "Size: " << da.get_size() << endl;
  cout << "Capacity: " << da.get_capacity() << endl;
  cout << "isEmpty: " << da.isEmpty() << endl;
  cout << "At(0): " << da.at(4) << endl;
  cout << "Find(5): " << da.find("5") << endl;

  for (int i = 0; i < da.get_size(); ++i) {
    cout << da.at(i) << endl;
  }

  return 0;
}
