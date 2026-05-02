#ifndef _VEHICLE
#define _VEHICLE

#include <istream>
#include <ostream>

const unsigned MODEL_LENGTH = 1024;

class Vehicle {
	char model[MODEL_LENGTH];
	unsigned yearOfManufacture;
	double mileage;
	unsigned short ecoCategory;
	double weight;
	double horsePower;


public:
	Vehicle();

	const char* GetModel() const;
	void SetModel(char model[MODEL_LENGTH]);

	unsigned GetYearOfManufacture() const;
	void SetYearOfManufacture(unsigned yearOfManufacture);

	double GetMileage() const;
	void SetMileage(double mileage);

	unsigned short GetEcoCategory() const;
	void SetEcoCategory(unsigned short ecoCategory);

	double GetWeight() const;
	void SetWeight(double weight);

	double GetHorsePower() const;
	void SetHorsePower(double horsePower);

	// Имаме всички нужни селектори и мутатори, за да не се нуждаем
	// от това операторите да са friend. Но въпреки това ще го
	// имплементираме така.

	friend std::ostream& operator<<(std::ostream& ostr, const Vehicle& vehicle);
	friend std::istream& operator>>(std::istream& istr, Vehicle& vehicle);

	// След като създадем динамично-заделен обект от
	// клас наследник, можем да конвертираме указателя към
	// базовия клас (т.е. CombustionVehicle* да стане Vehicle*).
	// В този случай, ще имаме налични само нещата, които са
	// достъпни във Vehicle, включително деструктора.
	//
	// Но CombustionVehicle има още член-данни, как ще разберем,
	// че Vehicle* е всъщност CombustionVehicle*?
	// Коректното решение, като стигнем до там, е да използваме
	// виртуални деструктури.
	//
	// Текущото решение, което можем да направим, е да запазваме
	// някаква допълнителна стойност, която е различна спрямо
	// конкретния клас (наследник). След това ще правим проверки по
	// нея, дали съответства на тази на даден клас, и ако да, конвертираме.
protected:
	unsigned type;
};


#endif /* _VEHICLE */
