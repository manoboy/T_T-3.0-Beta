#pragma once

size_t MyStrLen(const char* String);

class CEncrypt
{
public:
	CEncrypt(const char* String);
	~CEncrypt();

	void XOR(char* String);
	char* TempXOR(const char* String);
	char* OnceXOR(const char* String);

protected:
	char* Key;
	int KeyLenght;
		
	char* TempResault;
};
extern CEncrypt *Encrypt;

// STRING OBFUSCATION SUPPORT:
// true:  use encrypted strings
// false: use normal strings
//
// Change the value only if you know what you are doing!
#define STRING_OBFUSCATION false

#if STRING_OBFUSCATION
#ifndef _TempXOR
#define _TempXOR(A) Encrypt->TempXOR(A ## "...\n\.\*\.")
#endif

#ifndef _OnceXOR
#define _OnceXOR(A) Encrypt->OnceXOR(A ## "...\n\.\*\.")
#endif
#else
#ifndef _TempXOR
#define _TempXOR(A) A
#endif

#ifndef _OnceXOR
#define _OnceXOR(A) A
#endif
#endif