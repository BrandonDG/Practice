#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to compare the integers for sorting.
// This is for ascending order, for descending, reverse *pp and *qq.
int int_cmp(const void *p, const void *q) {
	const int *pp = p;
	const int *qq = q;
	return *pp - *qq;
}

// Function to compare the strings for sorting.
// /This is for ascending order, for descending, reerse *pp and *qq.
int str_cmp(const void *p, const void *q) {
	char * const *pp = p;
	char * const *qq = q;
	return strcmp(*pp, *qq);
}

// Main.
int main() {
	// Allocate memory for the ints using calloc.
	int *p = calloc(25, sizeof(int));
	// Create a collection of strings
	char *a[] = { "Hello", "World", "Goodbye", "This", "Will", "Be", "Sorted" };

	// If we failed to allocate the integers, print error message to stderr and exit.
	if (p == 0) {
		fprintf(stderr, "Unable to allocate memory\n");
		exit(1);
	}

	// Iterate through the int array, populate the values, 
	// and print them. 
	printf("Unsorted int array: \n");
	for (size_t i = 0; i < 25; i++) {
		p[i] = (i * 3) % 7;
		printf("%d ", p[i]);
	}

	printf("\n");

	// Sort the integers
	qsort(p, 25, sizeof(int), int_cmp);
	
	// Print the sorted integers.
	printf("Sorted int array(Ascending): \n");
	for (size_t i = 0; i < 25; i++) {
		printf("%d ", p[i]);
	}

	printf("\n");

	// Print the unsorted string array.
	printf("Unsorted string array: \n");
	for (size_t i = 0; i < 7; i++) {
		printf("%s ", a[i]);
	}

	printf("\n");

	// Sort the string array.
	qsort(a, sizeof(a)/sizeof(a[0]), sizeof(a[0]), str_cmp);

	// Print the sorted string array.
	printf("Sorted string array (Ascending): \n");
	for (size_t i = 0; i < 7; i++) {
		printf("%s ", a[i]);
	}

	printf("\n");

	return 0;
}
