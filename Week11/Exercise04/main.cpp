#include "Vector.hpp"
#include <iostream>

void print(const Vector<int> numbers) {
	for (unsigned i = 0; i < numbers.Count(); ++i)
		std::cout << numbers[i] << ' ';
	std::cout << std::endl;
}

int main() {
	Vector<int> nums;
	nums.PushBack(1);
	nums.PushBack(2);
	nums.PushBack(3);

	Vector<int> numsMore(nums);
	numsMore.PushBack(4);
	numsMore.PushBack(5);

	print(nums + numsMore);

	return 0;
}
