#ifndef IOHELPERS
#define IOHELPERS

// Прочита от потребителския вход цяло число между min и max включително,
// като предоставя prompt преди въведената стойност
// При невалидна стойност, пита пак за вход
int readInteger(const char* prompt, int min, int max);
// Прочита от потребителския вход число с плаваща запетая между min и max включително,
// като предоставя prompt преди въведената стойност
// При невалидна стойност, пита пак за вход
double readDouble(const char* prompt, double min, double max);
// Прочита от потребителския вход един ред текст,
// като предоставя prompt преди въведената стойност
// При невалидна стойност, пита пак за вход
char* readString(const char* prompt);

#endif
