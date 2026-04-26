#ifndef _LOCOMOTIVE
#define _LOCOMOTIVE

#include <fstream>

const unsigned MAX_LEN = 1024;

class Locomotive {
	unsigned ID;
	char manufacturer[MAX_LEN];
	char model[MAX_LEN];
	int yearOfManufacture;
	double length;
	unsigned short cyllinders;
	bool supportsMultipleWorking;

public:
	unsigned GetID() const;
	void SetID(unsigned ID);

	const char* GetManufacturer() const;
	void SetManufacturer(const char manufacturer[MAX_LEN]);

	const char* GetModel() const;
	void SetModel(const char model[MAX_LEN]);

	int GetYearOfManufacture() const;
	void SetYearOfManufacture(int yearOfManufacture);

	double GetLength() const;
	void SetLength(double length);

	unsigned short GetCyllinders() const;
	void SetCyllinders(unsigned short cyllinders);

	bool GetSupportsMultipleWorking() const;
	void SetSupportsMultipleWorking(bool supportsMultipleWorking);

	friend std::ofstream& operator<<(std::ofstream& ostr, const Locomotive& loc);
	friend std::ifstream& operator>>(std::ifstream& istr, Locomotive& loc);
};

#endif /* _LOCOMOTIVE */
