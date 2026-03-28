#ifndef NUMSERIES
#define NUMSERIES

class NumSeries {
	double* numbers;
	unsigned allocated;
	unsigned size;

	void free();
	void copyFrom(const NumSeries& other);

	void resize();
public:
	NumSeries();
	~NumSeries();
	NumSeries(const NumSeries& other);
	NumSeries& operator=(const NumSeries& other);

	NumSeries(NumSeries&& other);
	NumSeries& operator=(NumSeries&& other);

	void Push(double element);
	double At(unsigned index) const;
	unsigned Length() const;
};

#endif /* NUMSERIES */
