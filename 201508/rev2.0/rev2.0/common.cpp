//#include "stdafx.h"
#include "common.h"
#include <iostream>
using namespace std;

//#define DEBUG TRUE
#define DEBUG FALSE
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const char *Hex2ASC(const BYTE *Hex, int Len)
{
	static char  ASC[4096 * 2];
	int    i;

	for (i = 0; i < Len; i++)
	{
		ASC[i * 2] = "0123456789abcdef"[Hex[i] >> 4];
		ASC[i * 2 + 1] = "0123456789abcdef"[Hex[i] & 0x0F];
	}
	ASC[i * 2] = 0;
	return ASC;
}


const char *md5(const char * str, int lsize)
{
	MD5_CTX ctx;
	const unsigned char * buf = reinterpret_cast<const unsigned char *>(str);
	//int len = strlen(str);
	int len = lsize;
	if(DEBUG)
	{
		cout<<"string size: "<<len<<endl;
	}
	HINSTANCE hDLL;
	PMD5Init MD5Init;
	PMD5Update MD5Update;
	PMD5Final MD5Final;
	if ( (hDLL = LoadLibraryA("advapi32.dll")) > 0 )
	{

		MD5Init = (PMD5Init)GetProcAddress(hDLL,"MD5Init");
		MD5Update = (PMD5Update)GetProcAddress(hDLL,"MD5Update");
		MD5Final = (PMD5Final)GetProcAddress(hDLL,"MD5Final");

		MD5Init(&ctx);
		MD5Update(&ctx, buf, len);
		MD5Final(&ctx);
	}
	return Hex2ASC(ctx.digest, 16);
}
