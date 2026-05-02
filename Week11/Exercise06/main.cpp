#include "UniquePointer.hpp"
#include <utility>

int main() {
	UniquePointer<int> ptr(new int);
	// Този ред, без "std::move", ще хвърли грешка,
	// понеже нямаме копиращи семантики
	UniquePointer<int> ptr1 = std::move(ptr);
}
