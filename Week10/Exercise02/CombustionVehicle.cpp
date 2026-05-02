#include "CombustionVehicle.h"

CombustionVehicle::CombustionVehicle() : Vehicle(), cyllindersCount(), engineVolume() {
	type = 2;
}

unsigned CombustionVehicle::GetCyllindersCount() const {
	return cyllindersCount;
}

void CombustionVehicle::SetCyllindersCount(unsigned cyllindersCount) {
	this->cyllindersCount = cyllindersCount;
}

double CombustionVehicle::GetEngineVolume() const {
	return engineVolume;
}

void CombustionVehicle::SetEngineVolume(double engineVolume) {
	this->engineVolume = engineVolume;
}

std::ostream& operator<<(std::ostream& ostr, const CombustionVehicle& vehicle) {
	ostr << (const Vehicle&)vehicle
		<< "Cyllinders count: " << vehicle.cyllindersCount << std::endl
		<< "Engine volume: " << vehicle.engineVolume << std::endl;
	return ostr;
}

std::istream& operator>>(std::istream& istr, CombustionVehicle& vehicle) {
	istr >> (Vehicle&)vehicle
		>> vehicle.cyllindersCount
		>> vehicle.engineVolume;
	return istr;
}

bool CombustionVehicle::IsCombustionVehicle(const Vehicle& vehicle) {
	// Как работят конвертиранията: в C++ има няколко конвертирания, те са главно
	// const_cast, static_cast и reinterpret_cast.
	// Стандартното конвертиране със скоби "(Type)(x)", се нарича експлицитно
	// конвертиране и идва от C. Под C++, то просто пробва всички възможни
	// конвертирания, докато някое е валидно (дори и като резултат да е грешно).
	//
	// const_cast конветира между това дали тип е константен или не.
	// static_cast променя как поглеждаме посочената памет. С други думи,
	// "тези битове/байтове тук вече трябва да се зачитат за този тип".
	// reinterpret_cast прави по-сложна промяна, която цели да върне такива
	// данни, че всичко да работи коректно. На теория, може и примерно да се
	// задели нова памет в която да се пренесат данните които са ни предоставени.
	//
	// В нашия случай, CombustionVehicle има повече член-данни от vehicle, което
	// означава че ако използваме static_cast (което експлицитното конвертиране
	// ще избере), ще направим грешка.
	// Един Vehicle обект заема ~1042 байта, докато CombustionVehicle заема ~1054.
	// Това означава, че със static_cast ще зачитаме памет от 1042 байта като
	// такава от 1054 и можем да пишем/четем извън предопределените адреси памет.
	//
	// В нашия случай това няма да се случи, но коректното решение е да
	// използваме reinterpret_cast, който ще осигури че всичко от върнатата
	// стойност може да се достъпи, без проблеми.
	//
	//
	// А защо ни трябва конвертиране, нали CombustionVehicle е наследник,
	// не можем ли директно от vehicle да вземем type?
	// Еми, не можем, защото член-функция може да достъпва само член-данни и член-функции
	// на обекти от същия тип. Т.е. няма никакъв специален достъп към Vehicle обекти,
	// само всичко публично е налично, но има пълен достъп към CombustionVehicle обекти.
	return reinterpret_cast<const CombustionVehicle&>(vehicle).type == 2;
}
