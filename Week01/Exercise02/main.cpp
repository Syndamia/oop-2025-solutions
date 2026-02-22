#include <iostream>
#include "arrmath.h"

int main() {
	unsigned N;
	std::cin >> N;

	int* arr = new int[N];
	for (unsigned i = 0; i < N; ++i)
		std::cin >> arr[i];

	int startIndex = findIndex(arr, N, smallest(arr, N));
	int endIndex = findIndex(arr, N, largest(arr, N));

	if (startIndex > endIndex) {
		int temp = startIndex;
		startIndex = endIndex;
		endIndex = temp;
	}

	std::cout << average(arr + startIndex, endIndex - startIndex + 1) << std::endl;

	delete[] arr;

	return 0;
}
