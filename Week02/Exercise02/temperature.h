#ifndef _TEMPERATURE
#define _TEMPERATURE

struct Temperature {
	double C;
	double F;
	double K;

	void fromCelsius(double C);
	void fromFahrenheit(double F);
	void fromKelvin(double K);

	Temperature Sum(const Temperature& other);
};

#endif
