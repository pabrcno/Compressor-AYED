/*
 * BitReader.hpp
 *
 *  Created on: Jun 25, 2020
 *      Author: PAULO ADMIN
 */

#ifndef BITREADER_HPP_
#define BITREADER_HPP_
#include <iostream>
#include "../funciones/strings.hpp"
#include "../funciones/files.hpp"
#include "../funciones/tokens.hpp"

using namespace std;

struct BitReader
{
 unsigned char ch;
 FILE* f;
 int cont;
};

BitReader bitReaderCreate(FILE* f)
{
    BitReader br;
    br.ch = 0;
    br.cont = 8;
    br.f = f;
    return br;
}

int bitReaderRead(BitReader& br){
   if (br.cont == 8){
       br.ch = read<unsigned char>(br.f);
   }
   unsigned char aux = br.ch;
   br.ch = br.ch >> br.cont;
   br.ch = br.ch & 1;

   int r = br.ch;
   br.ch = aux;
   br.cont--;
   return r;
}


#endif /* BITREADER_HPP_ */