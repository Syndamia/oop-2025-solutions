#ifndef _OPTION
#define _OPTION

template <class T>
class Option {
	T obj;
	bool isSomething;

	Option();
public:
	static Option Some(T value);
	static Option None();

	bool IsSome() const;
	bool IsNone() const;
	T Unwrap();
};

template <class T>
Option<T>::Option() : obj(), isSomething(false)
{ }

template <class T>
Option<T> Option<T>::Some(T value) {
	Option op;
	op.isSomething = true;
	op.obj = value;
	return op;
}

// Какво запазваме, когато искаме да запазим нищо?
// Ако работехме с T*, щяхме да запазим nullptr.
// В нашия случай, няма голямо значение каква е стойността на obj,
// затова просто ще запазим стойността по подразбиране.
// Ако съответния тип няма конструктор по подразбиране, тогава ще
// получим грешка по време на компилация.
template <class T>
Option<T> Option<T>::None() {
	return Option();
}

template <class T>
bool Option<T>::IsSome() const {
	return isSomething;
}

template <class T>
bool Option<T>::IsNone() const {
	return !isSomething;
}

// Както при None метода, тук е нужно T да има имплементиран
// копиращи и/или преместващи семантики (конструктор и operator=).
//
// Обаче, ако ние сме създали обект чрез None, тогава Unwrap ще ни
// върне потенциално валидна стойност: тази по подразбиране.
// Коректното решение тук е да имаме проверка за isSomething,
// и ако не е, да "хвърлим грешка". Но това още не сме го учили.
//
// За момента ще приемем, че ако програмист направи Unwrap на обект,
// създаден чрез None, тогава това е негов пропуск, който сам трябва
// да си оправи.
template <class T>
T Option<T>::Unwrap() {
	return obj;
}

#endif /* _OPTION */
