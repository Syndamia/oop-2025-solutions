#include "Book.h"
#include <iostream>
#include <fstream>

void Book::SetTitle(const String& newTitle) {
	title = newTitle;
}

const String& Book::GetTitle() const {
	return title;
}

void Book::SetAuthor(const String& newAuthor) {
	author = newAuthor;
}

const String& Book::GetAuthor() const {
	return author;
}

void Book::SetYear(short newYear) {
	year = newYear;
}

short Book::GetYear() const {
	return year;
}

void Book::SetText(const String& newText) {
	text = newText;
}

const String& Book::GetText() const {
	return text;
}

void Book::SetPrice(double newPrice) {
	price = newPrice;
}

double Book::GetPrice() const {
	return price;
}

void Book::SetAvailableForPurchase(bool isAvailableForPurchase) {
	availableForPurchase = isAvailableForPurchase;
}

bool Book::GetAvailableForPurchase() const {
	return availableForPurchase;
}

void Book::PrintBookInfo() const {
	std::cout << GetTitle().GetStr() << ", "
		<< GetAuthor().GetStr() << ' '
		<< GetYear() << std::endl;
}

bool Book::Export(const String& fileName) {
	std::ofstream exportFile(fileName.GetStr(), std::ios::binary);

	if (!exportFile.is_open()) {
		std::cout << "Couldn't export book to file!" << std::endl;
	}
	else {
		exportFile.write(title.GetStr(), title.GetLength() + 1);
		exportFile.write(author.GetStr(), author.GetLength() + 1);
		exportFile.write((const char*)&year, sizeof(year));
		exportFile.write(text.GetStr(), text.GetLength() + 1);
	}

	return exportFile.is_open();
}

void readNullTerminated(String& readInto, std::ifstream& file) {
	readInto.Clear();
	for (char buffer = file.get(); buffer != '\0' && !file.eof(); buffer = file.get()) {
		readInto.AppendChar(buffer);
	}
}

bool Book::Import(const String& fileName) {
	std::ifstream importFile(fileName.GetStr(), std::ios::binary);

	if (!importFile.is_open()) {
		std::cout << "Couldn't import book to file!" << std::endl;
	}
	else {
		readNullTerminated(title, importFile);
		readNullTerminated(author, importFile);
		importFile.read((char*)&year, sizeof(year));
		readNullTerminated(text, importFile);
	}

	return importFile.is_open();
}
