#ifndef _TARR_TAD_
#define _TARR_TAD_

#include <iostream>
#include <stdlib.h>
#include "../funciones/arrays.hpp"

using namespace std;

int cmpInt(int a,int b){ return a-b; }

template<typename T>
struct Arr
{
   T* pointer;
   int length;
   int capacity;
};

template<typename T>
Arr<T> arr(int size)
{
   return {new T[size], 0, size};
}

template<typename T>
Arr<T> arr()
{
   return {new T[20], 0, 20};
}

template<typename T>
int arrAdd(Arr<T>& a,T v)
{
   if (a.capacity==a.length){
      Arr<T> b = arr<T>(a.capacity*2);
      for (int i = 0; i < a.length; i++){
         arrAdd<T>(b, a.pointer[i]);
      }
      a = b;
   }
   add<T>(a.pointer, a.length, v);
   return 0;
}

template<typename T>
T* arrGet(Arr<T> a,int p)
{
   return &(a.pointer[p]);
}

template<typename T>
void arrSet(Arr<T>& a,int p,T t)
{
   a.pointer[p] = t;
}

template<typename T>
void arrInsert(Arr<T>& a,T v,int p)
{
   insert<T>(a.pointer, a.length, v, p);
}

template<typename T>
int arrLength(Arr<T> a)
{
   return a.length;
}

template<typename T>
int arrCapacity(Arr<T> a)
{
   return a.capacity;
}

template<typename T>
T arrRemove(Arr<T>& a,int p)
{
   return remove<T>(a.pointer, a.length, p);
}

template<typename T>
void arrRemoveAll(Arr<T>& a)
{
   a.length = 0;
}

template<typename T,typename K>
int arrFind(Arr<T>& a,K k, int cmpTK(T,K))
{
   int p = -1;
   for (int i = 0; i < a.length; i++){
      int z = *(a.pointer+i);
      cmpTK(*(a.pointer+i), k) == 0? p = i : 0;
   }
   return p;
}

template<typename T>
int arrOrderedInsert(Arr<T>& a,T t,int cmpTT(T,T))
{
   int i = 0;
   while (cmpTT (*(a.pointer+i), t) < 0) { i++; }
   arrInsert<T>(a, t, i);
   return i;
}

template<typename T>
void arrSort(Arr<T>& z,int cmpTT(T,T))
{
   for (int i = 0; i < z.length; i++) {
		for (int j = 0; j < z.length - 1; j++) {
			T a = *(z.pointer + j);
			T b = *(z.pointer + j + 1);

			if (cmpTT(a, b) > 0) {
				T aux = a;
				*(z.pointer + j) = b;
				*(z.pointer + j + 1) = aux;
			}
		}
	}
}

#endif
