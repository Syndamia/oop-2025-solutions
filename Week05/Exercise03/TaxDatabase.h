#ifndef _TAXDATABASE
#define _TAXDATABASE

#include "Person.h"
#include "TaxReport.h"

class TaxDatabase {
	Person* people;
	unsigned peopleCount;
	unsigned peopleAllocated;

	TaxReport* reports;
	unsigned reportsCount;
	unsigned reportsAllocated;

	void free();
	void copyFrom(const TaxDatabase& other);

	void resizePeople();
	void resizeReports();

public:
	TaxDatabase();
	~TaxDatabase();
	TaxDatabase(const TaxDatabase& other);
	TaxDatabase& operator=(const TaxDatabase& other);

	TaxDatabase(TaxDatabase&& other);
	TaxDatabase& operator=(TaxDatabase&& other);

	bool RegisterPerson(const Person& person);
	bool LogTaxReport(const TaxReport& report);

	void PersonalReports(unsigned long long PN) const;
	void YearlyReports(unsigned short year) const;

	double YearlyAvgIncome(unsigned short year) const;
	double YearlyTaxedIncome(unsigned short year) const;

	const TaxReport* GetReport(unsigned long long PN, unsigned short year) const;
	const TaxReport* GetReportByAge(unsigned long long PN, unsigned short age) const;

	// Можем да дефинираме класове в други класове, можем да достъпим
	// вътрешния клас с името "TaxDatabase::Reports".
	// Достъпността на класа следва public/protected/private, в този
	// случай класа е публичен.
	class Reports {
		TaxReport** reports;
		unsigned reportsCount;

		void copyFrom(const Reports& other);
		void free();

	public:
		Reports();
		~Reports();
		Reports(const Reports& other);
		Reports& operator=(const Reports& other);

		Reports(Reports&& other);
		Reports& operator=(Reports&& other);

		unsigned ReportsCount() const;
		const TaxReport* At(unsigned index) const;

		// Тези се използват единствено от GetReports и GetReportsByAge
		// Тоест не позволяваме на върнатата стойност да бъде изменяна
		void Allocate(unsigned size);
		TaxReport** At(unsigned index);
	};

	const Reports GetReports(unsigned long long PN, unsigned short startYear, unsigned short endYear) const;
	const Reports GetReportsByAge(unsigned long long PN, unsigned short startAge, unsigned short endAge) const;

	/* Помощни функции */

	const Person* GetPerson(unsigned long long PN) const;
};

#endif /* _TAXDATABASE */
