#include "TaxDatabase.h"
#include "TaxReport.h"
#include <iostream>

// Силно препоръчително е да тествате големи програми,
// дори да не ви се иска по условие
int main() {
	TaxDatabase td;

	td.RegisterPerson(Person("Petur", "Ivanov", "Dimitrov", 888500600, "pid@mail.com", 1989, 384));
	td.RegisterPerson(Person("Konstantin", "Filiopv", "Abrahildraganovichevich", 887111000, "k@mail.com", 1992, 591));

	td.LogTaxReport(TaxReport(384, 2009, 10000, 0.1));
	td.LogTaxReport(TaxReport(384, 2010, 15000, 0.1));
	td.LogTaxReport(TaxReport(384, 2011, 20000, 0.1));
	td.LogTaxReport(TaxReport(384, 2012, 30000, 0.1));
	td.LogTaxReport(TaxReport(384, 2013, 70000, 0.2));
	td.LogTaxReport(TaxReport(384, 2014, 100000, 0.2));

	td.LogTaxReport(TaxReport(591, 2012, 3900, 0.1));
	td.LogTaxReport(TaxReport(591, 2013, 40000, 0.2));
	td.LogTaxReport(TaxReport(591, 2014, 45000, 0.2));
	td.LogTaxReport(TaxReport(591, 2015, 50000, 0.15));

	td.PersonalReports(384);
	td.PersonalReports(591);

	std::cout << std::endl;

	td.YearlyReports(2014);
	td.YearlyReports(2015);

	std::cout << std::endl;

	std::cout << td.YearlyAvgIncome(2011) << ' '
		<< td.YearlyAvgIncome(2014) << ' '
		<< td.YearlyAvgIncome(2015) << std::endl;

	std::cout << std::endl;

	std::cout << td.YearlyTaxedIncome(2011) << ' '
		<< td.YearlyTaxedIncome(2014) << ' '
		<< td.YearlyTaxedIncome(2015) << std::endl;

	std::cout << std::endl;

	const TaxReport* r;

	r = td.GetReport(384, 2013);
	if (r == nullptr)
		std::cout << "No report for 2013" << std::endl;
	else
		std::cout << r->GetYear() << ' ' << r->GetPN() << ' ' << r->GetIncome() << ' ' << r->GetTaxRate() << std::endl;

	r = td.GetReport(384, 2015);
	if (r == nullptr)
		std::cout << "No report for 2015" << std::endl;
	else
		std::cout << r->GetYear() << ' ' << r->GetPN() << ' ' << r->GetIncome() << ' ' << r->GetTaxRate() << std::endl;

	r = td.GetReport(591, 2015);
	if (r == nullptr)
		std::cout << "No report for 2015" << std::endl;
	else
		std::cout << r->GetYear() << ' ' << r->GetPN() << ' ' << r->GetIncome() << ' ' << r->GetTaxRate() << std::endl;

	std::cout << std::endl;

	r = td.GetReportByAge(384, 20);
	if (r == nullptr)
		std::cout << "No report at 20" << std::endl;
	else
		std::cout << r->GetYear() << ' ' << r->GetPN() << ' ' << r->GetIncome() << ' ' << r->GetTaxRate() << std::endl;

	r = td.GetReportByAge(384, 21);
	if (r == nullptr)
		std::cout << "No report at 21" << std::endl;
	else
		std::cout << r->GetYear() << ' ' << r->GetPN() << ' ' << r->GetIncome() << ' ' << r->GetTaxRate() << std::endl;

	r = td.GetReportByAge(591, 23);
	if (r == nullptr)
		std::cout << "No report at 23" << std::endl;
	else
		std::cout << r->GetYear() << ' ' << r->GetPN() << ' ' << r->GetIncome() << ' ' << r->GetTaxRate() << std::endl;

	std::cout << std::endl;

	const TaxDatabase::Reports reports1 = td.GetReports(591, 2005, 2015);
	for (unsigned i = 0; i < reports1.ReportsCount(); ++i)
		std::cout << reports1.At(i)->GetPN() << ' ' << reports1.At(i)->GetYear() << std::endl;

	std::cout << std::endl;

	const TaxDatabase::Reports reports2 = td.GetReportsByAge(384, 20, 25);
	for (unsigned i = 0; i < reports2.ReportsCount(); ++i)
		std::cout << reports2.At(i)->GetPN() << ' ' << reports2.At(i)->GetYear() << std::endl;

	return 0;
}
