#include "TaxReport.h"
#include <iostream>

TaxReport::TaxReport(unsigned long long PN, unsigned short year, double income, double taxRate) {
	this->PN = PN;
	this->year = year;
	this->income = income;
	this->taxRate = taxRate;
}

unsigned long long TaxReport::GetPN() const {
	return PN;
}

unsigned short TaxReport::GetYear() const {
	return year;
}

double TaxReport::GetIncome() const {
	return income;
}

double TaxReport::GetTaxRate() const {
	return taxRate;
}
