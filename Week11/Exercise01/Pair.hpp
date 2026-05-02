#ifndef _PAIR
#define _PAIR

template<class T, class U>
class Pair {
	T left;
	U right;

public:
	Pair(const T& left, const U& right);

	T& Left();
	const T& Left() const;

	U& Right();
	const U& Right() const;
};

template<class T, class U>
Pair<T, U>::Pair(const T& left, const U& right) : left(left), right(right)
{ }

template<class T, class U>
T& Pair<T, U>::Left() {
	return left;
}

template<class T, class U>
const T& Pair<T, U>::Left() const {
	return left;
}

template<class T, class U>
U& Pair<T, U>::Right() {
	return right;
}

template<class T, class U>
const U& Pair<T, U>::Right() const {
	return right;
}

#endif /* _PAIR */
