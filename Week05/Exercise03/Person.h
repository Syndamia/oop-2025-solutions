#ifndef _PERSON
#define _PERSON

#include "String.h"

class Person {
	String firstName;
	String middleName;
	String lastName;
	unsigned long long phoneNumber;
	String email;
	unsigned short birthYear;
	unsigned long long PN; // Personal Number

public:
	Person(const String& firstName, const String& middleName, const String& lastName, unsigned long long phoneNumber, const String& email, unsigned short birthYear, unsigned long long PN);

	/* Помощни член-функции */

	// За да създадем масив се нуждаем от празен конструктор,
	// обаче отгоре дефинирахме някакъв конструктор, което
	// означава че празния по подразбиране не се създава.
	// Можем сами да си го дефинираме, но с този синтаксис
	// можем да задължим компилатора да използва този,
	// който би генерирал по принцип.
	Person() = default;

	const String& GetFirstName() const;
	const String& GetMiddleName() const;
	const String& GetLastName() const;
	unsigned long long GetPhoneNumber() const;
	const String& GetEmail() const;
	unsigned short GetBirthYear() const;
	unsigned long long GetPN() const;
};

#endif /* _PERSON */
