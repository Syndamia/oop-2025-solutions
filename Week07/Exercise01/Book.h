#ifndef _BOOK
#define _BOOK

#include "String.h"

class Book {
	String title;
	String author;
	short year;
	String text;
	double price;
	bool availableForPurchase;

public:
	void SetTitle(const String& newTitle);
	const String& GetTitle() const;

	void SetAuthor(const String& newAuthor);
	const String& GetAuthor() const;

	void SetYear(short newYear);
	short GetYear() const;

	void SetText(const String& newText);
	const String& GetText() const;

	void SetPrice(double newPrice);
	double GetPrice() const;

	void SetAvailableForPurchase(bool isAvailableForPurchase);
	bool GetAvailableForPurchase() const;

	void PrintBookInfo() const;

	bool Export(const String& fileName);
	bool Import(const String& fileName);
};

#endif /* _BOOK */
