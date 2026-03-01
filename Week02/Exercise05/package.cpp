#include <iostream>
#include "package.h"

Package readPackage() {
	Package p;
	std::cin.getline(p.ID, 11);
	// Когато getline не стигне искания знак ('\n'),
	// една специална "fail" променлива става true и
	// това задължава всеки следващ вход да се провали.
	// С clear правим "fail" променливата на false
	std::cin.clear();
	std::cin >> p.weight;
	return p;
}
