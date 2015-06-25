#include "Encrypt.h"
#include <string>

#pragma warning(disable : 4996)
CEncrypt *Encrypt = new CEncrypt("AAAAAAAAAAAAAAAAAAAA");

size_t MyStrLen(const char* String)
{
	const char *End = String;
	while (*(++End) != 0);
	return End - String;
};

CEncrypt::CEncrypt(const char* String) : KeyLenght(MyStrLen(String)), Key(new char[KeyLenght + 1])
{
	strcpy(this->Key, String);
}

CEncrypt::~CEncrypt()
{
	if (Key)
		delete[] Key;
	if (TempResault)
		delete[] TempResault;
}

void CEncrypt::XOR(char* String)
{
	int KeyIndex = 0;
	char TmpChar;
	while (*String != 0)
	{
		TmpChar = *String ^ Key[KeyIndex++];
		if ((TmpChar == 0x0) || (TmpChar == 0x0A))
			*String = *String;
		else
			*String = TmpChar;
		if (KeyIndex == KeyLenght)
			KeyIndex = 0;
	}
}

char* CEncrypt::TempXOR(const char* String)
{
	if (TempResault)
		delete[] TempResault;

	size_t Lenght = MyStrLen(String);
	TempResault = new char[Lenght + 1];

	int KeyIndex = 0;
	char TmpChar;
	for (int i = 0; i < Lenght; i++)
	{
		TmpChar = String[i] ^ Key[KeyIndex];
		if ((TmpChar == 0x0) || (TmpChar == 0x0A))
			TempResault[i] = String[i];
		else
			TempResault[i] = TmpChar;
		KeyIndex++;
		if (KeyIndex == KeyLenght)
			KeyIndex = 0;
	}
	TempResault[Lenght] = 0;

	return TempResault;
}
char* CEncrypt::OnceXOR(const char* String)
{
	size_t Lenght = MyStrLen(String);
	char* Resault = new char[Lenght + 1];

	int KeyIndex = 0;
	char TmpChar;
	for (int i = 0; i < Lenght; i++)
	{
		TmpChar = String[i] ^ Key[KeyIndex];
		if ((TmpChar == 0x0) || (TmpChar == 0x0A))
			Resault[i] = String[i];
		else
			Resault[i] = TmpChar;
		KeyIndex++;
		if (KeyIndex == KeyLenght)
			KeyIndex = 0;
	}
	Resault[Lenght] = 0;

	return Resault;
}
