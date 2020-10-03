
#ifndef _TMAP_TAD_
#define _TMAP_TAD_

#include <iostream>
#include "Arr.hpp"

using namespace std;
// ******************* PROFE *******************

/*
template<typename K,typename T>
struct Map
{
   Arr<K> keys;
   Arr<T> values;
   int curr;
};

template<typename K,typename T>
Map<K,T> mapCreate()
{
   int dSize=10;
   Map<K,T> m;
   m.keys = arrCreate<K>(dSize);
   m.values=arrCreate<T>(dSize);
   m.curr=0;
   return m;
}

template<typename K>
int cmpKK(K a,K b)
{
   return a<b?-1:a==b?0:1;
}


template<typename K,typename T>
bool mapContains(Map<K,T>& m,K k)
{
   return mapGet(m,k)!=NULL;
}

template<typename K,typename T>
T* mapGet(Map<K,T>& m,K k)
{
   int p = arrFind<K,K>(m.keys,k,cmpKK);
   return p>=0?arrGet<T>(m.values,p):NULL;
}
template<typename K,typename T>
T* mapPut(Map<K,T>& m,K k, T v)
{
   int p = arrFind<K,K>(m.keys,k,cmpKK);
   if( p<0 )
   {
      arrAdd<K>(m.keys,k);
      arrAdd<T>(m.values,v);
   }
   else
   {
      arrSet<T>(m.values,v,p);
   }

   return mapGet<K,T>(m,k);
}

template<typename K,typename T>
void mapRemove(Map<K,T>& m,K k)
{
   int p = arrFind<T,K>(k.keks,k,cmpKK);
   arrRemove<K>(m.keys,p);
   arrRemove<T>(m.values,p);
   return;
}

template<typename K,typename T> void mapReset(Map<K,T>& m)
{
   m.curr=0;
}

template<typename K,typename T> bool mapHasNext(Map<K,T>& m)
{
   return m.curr<arrLength(m.keys);
}

template<typename K,typename T> T* mapNextValue(Map<K,T>& m)
{
   return arrGet(m.values,m.curr++);
}

template<typename K,typename T> K mapNextKey(Map<K,T>& m)
{
   return *arrGet(m.keys,m.curr++);
}

template<typename K,typename T> void mapSortByKeys(Map<K,T>& m,int cmpKK(K,K))
{
}

template<typename K,typename T> void mapSortByValues(Map<K,T>& m,int cmpTT(T,T))
{
}
*/

template<typename K,typename T>
struct Map
{
   Arr<K> keys;
   Arr<T> values;
   int count;
};

template<typename K,typename T>
Map<K,T> map()
{
   return {arr<K>(), arr<T>(), -1};
}

template<typename K,typename T>
int mapFindKey (Map<K,T>& m,K k) {
    int p;
   for (int i = 0; i < m.values.length; i++){
      if (m.keys.pointer[i] == k){ p=i; break;}
   }
   return p;
}

template<typename K,typename T>
T* mapGet(Map<K,T>& m,K k)
{
   T* x = NULL;
   for(int i = 0; i < arrLength(m.keys); i++){
      if(k == *(m.keys.pointer + i)){
         x = m.values.pointer + i;
      }
   }
   return x;
}

template<typename K,typename T>
T* mapPut(Map<K,T>& m,K k,T v)
{
   T* value = mapGet<K,T>(m, k);

   if (value == NULL) {
      arrAdd<K>(m.keys, k);
      arrAdd<T>(m.values, v);
   }
   else {
      T* t = mapGet<K,T>(m, k);
      *t = v;
   }

   return value;
}

template<typename K,typename T>
bool mapContains(Map<K,T>& m,K k)
{
   bool r = false;
   for (int i = 0; i < m.keys.length ; i++){
      if (m.keys.pointer[i] == k){ r = true;}
   }
   return r;
}

template<typename K,typename T>
T mapRemove(Map<K,T>& m,K k)
{
   int p = mapFindKey(m,k);
   arrRemove<K>(m,p);
   return arrRemove<T>(m,p);
}

template<typename K,typename T>
void mapRemoveAll(Map<K,T>& m)
{
   arrRemoveAll<K>(m.keys);
   arrRemoveAll<T>(m.values);
}

template<typename K,typename T>
int mapSize(Map<K,T> m)
{
   return arrLength(m.keys);
}

template<typename K,typename T> bool mapHasNext(Map<K,T>& m)
{
   return m.count < arrLength(m.keys) - 1;
}

template<typename K,typename T> K mapNextKey(Map<K,T>& m)
{
   K r = *(arrGet<K>(m.keys, m.count+1));
   m.count +=1;
   return r;
}

template<typename K,typename T> T* mapNextValue(Map<K,T>& m)
{
   T* r = arrGet<T>(m.values, m.count+1);
   m.count +=1;
   return r;
}


template<typename K,typename T> void mapReset(Map<K,T>& m)
{
   m.count = -1;
}

template<typename K,typename T> void mapSortByKeys(Map<K,T>& m,int cmpKK(K,K))
{
   for (int i = 0; i < m.keys.length; i++) {
		for (int j = 0; j < m.keys.length - 1; j++) {
			K kA = *(m.keys.pointer + j);
			K kB = *(m.keys.pointer + j + 1);

         T vA = *(m.values.pointer + j);
			T vB = *(m.values.pointer + j + 1);

			if (cmpKK(kA, kB) > 0) {
				K kAux = kA;
				*(m.keys.pointer + j) = kB;
				*(m.keys.pointer + j + 1) =kAux;

            T vAux = vA;
            *(m.values.pointer + j) = vB;
				*(m.values.pointer + j + 1) =vAux;
			}
		}
	}
}

template<typename K,typename T> void mapSortByValues(Map<K,T>& m,int cmpTT(T,T))
{
   for (int i = 0; i < m.values.length; i++) {
		for (int j = 0; j < m.values.length - 1; j++) {
			K kA = *(m.keys.pointer + j);
			K kB = *(m.keys.pointer + j + 1);

         T vA = *(m.values.pointer + j);
			T vB = *(m.values.pointer + j + 1);

			if (cmpTT(vA, vB) > 0) {
				K kAux = kA;
				*(m.keys.pointer + j) = kB;
				*(m.keys.pointer + j + 1) =kAux;

            T vAux = vA;
            *(m.values.pointer + j) = vB;
				*(m.values.pointer + j + 1) =vAux;
			}
		}
	}
}


#endif
