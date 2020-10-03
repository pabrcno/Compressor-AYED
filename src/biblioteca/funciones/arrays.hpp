#ifndef _TARRAYS_T_
#define _TARRAYS_T_

#include <iostream>

template <typename T>
int cmpTT(T t, T k) {
	if (t > k) {
		return 1;
	}
	else if (t < k) {
		return -1;
	}
	return 0;
}

template <typename T> int add(T arr[], int& len, T v)
{
	arr[len] = v;
	len++;
	return len - 1;
}

template <typename T>
void insert(T arr[], int& len, T v, int pos)
{
	for (int i = len; i > pos; i--) { 
		arr[i] = arr[i - 1]; 
	} 
	arr[pos] = v; 
	len++;
}

template <typename T>
T remove(T arr[], int& len, int pos)
{
	T ret = arr[pos];
	for (int i = pos + 1; i < len; i++) {
		arr[i - 1] = arr[i];
	} 
	len--; 
	return ret;
}

template <typename T, typename K>
int find(T arr[], int len, K v, int cmpTK(T,K))
{
	for (int i = 0; i < len; i++) {
		if (cmpTK(arr[i], v) == 0) {
			return i;
		}
	}
	return -1;
}

template <typename T>
int orderedInsert(T arr[], int& len, T v, int cmpTT(T, T))
{
	int pos = 0; //MIENTRAS QUE ARR[I] SEA MAYOR QUE EL SIGUIENTE
	for (int i = 0; cmpTT(arr[i], v)==-1; i++) {
		pos++;
	}
	insert<T>(arr, len, v, pos);
	return pos;
}

template <typename T>
void sort(T arr[], int len, int cmpTT(T,T))
{
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len - 1; j++) {
			T a = arr[j];
			T b = arr[j + 1];

			if (cmpTT(a, b) > 0) {
				T aux = a;
				arr[j] = b;
				arr[j+1] = aux;
			}
		}
	}

}
#endif
