#include "TaxDatabase.h"
#include <iostream>

void TaxDatabase::free() {
	delete[] people;
	delete[] reports;
}

void TaxDatabase::copyFrom(const TaxDatabase& other) {
	peopleCount = other.peopleCount;
	peopleAllocated = other.peopleAllocated;

	people = new Person[peopleAllocated];
	for (unsigned i = 0; i < peopleCount; ++i)
		people[i] = other.people[i];

	reportsCount = other.reportsCount;
	reportsAllocated = other.reportsAllocated;

	reports = new TaxReport[reportsAllocated];
	for (unsigned i = 0; i < reportsCount; ++i)
		reports[i] = other.reports[i];
}

void TaxDatabase::resizePeople() {
	unsigned newAllocated = peopleAllocated == 0 ? 8 : peopleAllocated * 2;
	Person* newPeople = new Person[newAllocated];

	for (unsigned i = 0; i < peopleCount; ++i)
		newPeople[i] = people[i];

	delete[] people;
	people = newPeople;
	peopleAllocated = newAllocated;
}

void TaxDatabase::resizeReports() {
	unsigned newAllocated = reportsAllocated == 0 ? 8 : reportsAllocated * 2;
	TaxReport* newReports = new TaxReport[newAllocated];

	for (unsigned i = 0; i < reportsCount; ++i)
		newReports[i] = reports[i];

	delete[] reports;
	reports = newReports;
	reportsAllocated = newAllocated;
}

TaxDatabase::TaxDatabase() {
	people = nullptr;
	reports = nullptr;
	peopleCount = peopleAllocated = reportsCount = reportsAllocated = 0;
}

TaxDatabase::~TaxDatabase() {
	free();
}

TaxDatabase::TaxDatabase(const TaxDatabase& other) {
	copyFrom(other);
}

TaxDatabase& TaxDatabase::operator=(const TaxDatabase& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

TaxDatabase::TaxDatabase(TaxDatabase&& other) {
	people = other.people;
	peopleCount = other.peopleCount;
	peopleAllocated = other.peopleAllocated;

	reports = other.reports;
	reportsCount = other.reportsCount;
	reportsAllocated = other.reportsAllocated;

	other.people = nullptr;
	other.reports = nullptr;
	other.peopleCount = other.peopleAllocated = other.reportsCount = other.reportsAllocated = 0;
}

TaxDatabase& TaxDatabase::operator=(TaxDatabase&& other) {
	if (this != &other) {
		free();

		people = other.people;
		peopleCount = other.peopleCount;
		peopleAllocated = other.peopleAllocated;

		reports = other.reports;
		reportsCount = other.reportsCount;
		reportsAllocated = other.reportsAllocated;

		other.people = nullptr;
		other.reports = nullptr;
		other.peopleCount = other.peopleAllocated = other.reportsCount = other.reportsAllocated = 0;
	}
	return *this;
}

bool TaxDatabase::RegisterPerson(const Person& person) {
	for (unsigned i = 0; i < peopleCount; ++i) {
		if (people[i].GetPN() == person.GetPN() ||
			people[i].GetPhoneNumber() == person.GetPhoneNumber() ||
			people[i].GetEmail().IsTheSameAs(person.GetEmail()))
		{
			return false;
		}
	}

	if (peopleCount >= peopleAllocated)
		resizePeople();
	people[peopleCount++] = person;

	return true;
}

bool TaxDatabase::LogTaxReport(const TaxReport& report) {
	for (unsigned i = 0; i < reportsCount; ++i) {
		if (reports[i].GetPN() == report.GetPN() &&
			reports[i].GetYear() == report.GetYear())
		{
			return false;
		}
	}

	if (reportsCount >= reportsAllocated)
		resizeReports();
	reports[reportsCount++] = report;

	return true;
}

void TaxDatabase::PersonalReports(unsigned long long PN) const {
	const Person* p = GetPerson(PN);
	if (p == nullptr) {
		std::cout << "Person not in database!" << std::endl;
		return;
	}

	std::cout << p->GetFirstName().GetStr() << ' ' << p->GetMiddleName().GetStr() << ' ' << p->GetLastName().GetStr() << std::endl
	          << "Personal No: " << p->GetPN() << " Born: " << p->GetBirthYear() << std::endl
	          << "Tel: " << p->GetPhoneNumber() << " Email: " << p->GetEmail().GetStr() << std::endl;

	for (unsigned i = 0; i < reportsCount; ++i) {
		if (reports[i].GetPN() == PN) {
			std::cout << reports[i].GetYear()
				<< " Income: " << reports[i].GetIncome()
				<< " Tax rate: " << reports[i].GetTaxRate() << std::endl;
		}
	}
}

void TaxDatabase::YearlyReports(unsigned short year) const {
	for (unsigned i = 0; i < reportsCount; ++i) {
		if (reports[i].GetYear() != year)
			continue;

		const Person* p = GetPerson(reports[i].GetPN());
		if (p != nullptr) {
			std::cout << p->GetFirstName().GetStr() << ' ' << p->GetLastName().GetStr()
				<< " Age: " << (year - p->GetBirthYear())
				<< " Income: " << reports[i].GetIncome()
				<< " Tax rate: " << reports[i].GetTaxRate() << std::endl;
		}
	}
}

double TaxDatabase::YearlyAvgIncome(unsigned short year) const {
	double incomeSum = 0.0;
	unsigned reportsInYear = 0;

	for (unsigned i = 0; i < reportsCount; ++i) {
		if (reports[i].GetYear() != year)
			continue;

		incomeSum += reports[i].GetIncome();
		++reportsInYear;
	}

	return incomeSum / reportsInYear;
}

double TaxDatabase::YearlyTaxedIncome(unsigned short year) const {
	double profits = 0.0;

	for (unsigned i = 0; i < reportsCount; ++i) {
		if (reports[i].GetYear() != year)
			continue;

		profits += reports[i].GetIncome() * reports[i].GetTaxRate();
	}

	return profits;
}

const TaxReport* TaxDatabase::GetReport(unsigned long long PN, unsigned short year) const {
	for (unsigned i = 0; i < reportsCount; ++i) {
		if (reports[i].GetPN() == PN && reports[i].GetYear() == year)
			return reports + i;
	}
	return nullptr;
}

const TaxReport* TaxDatabase::GetReportByAge(unsigned long long PN, unsigned short age) const {
	const Person* p = GetPerson(PN);

	if (p == nullptr)
		return nullptr;

	return GetReport(PN, p->GetBirthYear() + age);
}

void TaxDatabase::Reports::copyFrom(const Reports& other) {
	reportsCount = other.reportsCount;

	reports = new TaxReport*[reportsCount];
	for (unsigned i = 0; i < reportsCount; ++i)
		reports[i] = other.reports[i];
}

void TaxDatabase::Reports::free() {
	delete[] reports;
}

TaxDatabase::Reports::Reports() {
	reports = nullptr;
	reportsCount = 0;
}

TaxDatabase::Reports::~Reports() {
	free();
}

TaxDatabase::Reports::Reports(const Reports& other) {
	copyFrom(other);
}

TaxDatabase::Reports& TaxDatabase::Reports::operator=(const Reports& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

TaxDatabase::Reports::Reports(Reports&& other) {
	reports = other.reports;
	reportsCount = other.reportsCount;

	other.reports = nullptr;
	other.reportsCount = 0;
}

TaxDatabase::Reports& TaxDatabase::Reports::operator=(Reports&& other) {
	if (this != &other) {
		free();

		reports = other.reports;
		reportsCount = other.reportsCount;

		other.reports = nullptr;
		other.reportsCount = 0;
	}
	return *this;
}

unsigned TaxDatabase::Reports::ReportsCount() const {
	return reportsCount;
}

const TaxReport* TaxDatabase::Reports::At(unsigned index) const {
	if (index >= reportsCount)
		return nullptr;

	return reports[index];
}

void TaxDatabase::Reports::Allocate(unsigned size) {
	reportsCount = size;
	if (reports != nullptr)
		delete[] reports;
	reports = new TaxReport*[size];
}

TaxReport** TaxDatabase::Reports::At(unsigned index) {
	if (index >= reportsCount)
		return nullptr;

	return reports + index;
}

const TaxDatabase::Reports TaxDatabase::GetReports(unsigned long long PN, unsigned short startYear, unsigned short endYear) const {
	unsigned countReports = 0;

	for (unsigned i = 0; i < reportsCount; ++i) {
		if (reports[i].GetPN() == PN && startYear <= reports[i].GetYear() && reports[i].GetYear() <= endYear)
			++countReports;
	}

	Reports result;
	result.Allocate(countReports);

	unsigned reportIndex = 0;
	for (unsigned i = 0; i < reportsCount; ++i) {
		if (reports[i].GetPN() == PN && startYear <= reports[i].GetYear() && reports[i].GetYear() <= endYear) {
			*result.At(reportIndex++) = reports + i;
		}
	}

	return result;
}

const TaxDatabase::Reports TaxDatabase::GetReportsByAge(unsigned long long PN, unsigned short startAge, unsigned short endAge) const {
	const Person* p = GetPerson(PN);

	if (p == nullptr)
		return Reports();

	return GetReports(PN, p->GetBirthYear() + startAge, p->GetBirthYear() + endAge);
}

const Person* TaxDatabase::GetPerson(unsigned long long PN) const {
	for (unsigned i = 0; i < peopleCount; ++i) {
		if (people[i].GetPN() == PN) {
			return people + i;
		}
	}
	return nullptr;
}
