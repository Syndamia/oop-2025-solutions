#ifndef _TAXREPORT
#define _TAXREPORT

class TaxReport {
	unsigned long long PN; // Personal Number
	unsigned short year;
	double income;
	double taxRate;

public:
	TaxReport(unsigned long long PN, unsigned short year, double income, double taxRate);

	/* Помощни член-функции */

	// За да създадем масив се нуждаем от празен конструктор,
	// обаче отгоре дефинирахме някакъв конструктор, което
	// означава че празния по подразбиране не се създава.
	// Можем сами да си го дефинираме, но с този синтаксис
	// можем да задължим компилатора да използва този,
	// който би генерирал по принцип.
	TaxReport() = default;

	unsigned long long GetPN() const;
	unsigned short GetYear() const;
	double GetIncome() const;
	double GetTaxRate() const;
};

#endif /* _TAXREPORT */
