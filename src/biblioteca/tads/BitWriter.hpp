#ifndef BITWRITER_HPP_
#define BITWRITER_HPP_
#include <iostream>
#include "../funciones/strings.hpp"
#include "../funciones/files.hpp"
#include "../funciones/tokens.hpp"
//#include "biblioteca/funciones/ejercicios.hpp"
using namespace std;

struct BitWriter
{
   unsigned char ch;
   FILE* f;
   int cont;
};

BitWriter bitWriterCreate(FILE* f)
{
   BitWriter a;
   a.f = f;
   a.cont = 0;
   a.ch = 0;
   return a;
}

void bitWriterWrite(BitWriter& bw, int bit)
{
	if (bw.cont<8){
		bw.ch = bw.ch << 1;
		bw.ch = bw.ch | bit;
		bw.cont++;
	}
	if (bw.cont == 8){
		write<unsigned char>(bw.f, bw.ch);
		bw.ch = 0;
		bw.cont = 0;
	}
}

void bitWriterFlush(BitWriter& bw)
{
   while (bw.cont<8 && bw.cont > 0){
		bw.ch = bw.ch << 1;
		bw.ch = bw.ch | 0;
		bw.cont++;
	}
	if (bw.cont == 8){
		write<unsigned char>(bw.f, bw.ch);
		bw.ch = 0;
		bw.cont = 0;
	}
}
#endif