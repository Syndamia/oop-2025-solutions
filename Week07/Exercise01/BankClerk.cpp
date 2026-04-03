#include "BankClerk.h"

BankClerk::BankClerk(unsigned clerkNumber) {
	this->clerkNumber = clerkNumber;
	this->staticPassword = "password";
}

BankClerk::BankClerk() : clerkNumber(0), staticPassword()
{ }

unsigned BankClerk::GetClerkNumber() const {
	return clerkNumber;
}

void BankClerk::SetPassword(const String& newPassword) {
	staticPassword = newPassword;
}

bool BankClerk::Login(unsigned clerkNumber, unsigned dynamicPassword, const String& staticPassword) {
	return (clerkNumber * dynamicPassword) % 8581 == 0 && this->staticPassword.EqualTo(staticPassword);
}
