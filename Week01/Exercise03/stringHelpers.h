#ifndef STRINGHELPERS
#define STRINGHELPERS

// Създава динамично-заделен низ по подадената дължина
char* newString(unsigned length);
// Създава динамично-заделен низ, копие на подадения низ
char* newString(const char* string);
// Слепява first и second, като поставя separator между тях (ако е валиден) и
// връща резултатния (динамичо-заделен) низ
char* concatStrings(const char* first, const char* second, const char* separator);
// Освобождава паметта на динамичо-заделен низ
void deleteString(char*& string); // Запишете nullptr в string!

#endif
