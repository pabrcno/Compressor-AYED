// #ifndef _TFILES_T_
// #define _TFILES_T_

// #include <iostream>
// #include <stdio.h>

// template<typename T> T read(FILE* f)
// {
//    T buff;
//    fread(&buff, sizeof(T), 1, f);
//    return buff;
// }

// template<typename T> void write(FILE* f, T v)
// {
//    fwrite(&v, sizeof(T), 1, f);
// }

// template<typename T> void seek(FILE* f, int n)
// {
//    fseek(f,n*sizeof(T),SEEK_SET);
// }

// template<typename T> long fileSize(FILE* f)
// {
//    // tomo la posicion actual
//    long curr=ftell(f);
//    // muevo el puntero al final del archivo

// 	fseek(f,0,SEEK_END);  // SEEK_END hace referencia al final del archivo

// 	// tomo la posicion actual (ubicado al final)
//    long ultimo=ftell(f);

//    // vuelvo a donde estaba al principio
//  	fseek(f,curr,SEEK_SET);

//    return ultimo/sizeof(T);
// }

// template<typename T> long filePos(FILE* f)
// {
//    return ftell(f)/sizeof(T);
// }

// #endif

#ifndef _TFILES_T_
#define _TFILES_T_

#include "strings.hpp"
#include "tokens.hpp"
#include <iostream>
#include <stdio.h>

template<typename T> T read(FILE* f)
{
	T y;
	fread(&y,sizeof(T), 1, f);
	return y;
}

template<typename T> void write(FILE* f, T v)
{
	fwrite(&v, sizeof(T), 1, f);
}

template<typename T> void seek(FILE* f, int n)
{
	n = n * sizeof(T);
	fseek(f, n, SEEK_SET);
}

template<typename T> long fileSize(FILE* f)
{
	int pos = ftell(f);
	fseek(f, 0, SEEK_END);
	int x = ftell(f);
	fseek(f, pos, SEEK_SET);
	return x/sizeof(T);
}

template<typename T> long fileSizeBits(FILE* f)
{
	int pos = ftell(f);
	fseek(f, 0, SEEK_END);
	int x = ftell(f);
	fseek(f, pos, SEEK_SET);
	return x;
}

template<typename T> long filePos(FILE* f)
{
	long x = ftell(f) / sizeof(T);
	return x-1;
}

bool finalF(FILE* f) {
	int pos = ftell(f);
	fseek(f, 0, SEEK_END);
	int posF = ftell(f);
	if (pos == posF) {
		fseek(f, pos, SEEK_SET);
		return true;
	}
	fseek(f, pos, SEEK_SET);
	return false;
}

#endif
#pragma once
