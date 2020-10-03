#include <iostream>
#include "arrays.hpp"
#include "strings.hpp"
using namespace std;

// *********************** HEAP SORT ***********************

//SOLO PARA INT
//NO OPTIMIZADO

// ULTIMO PADRE = n/2 - 1, N = LEN-1
// HIJO = I*2 + 1, I = POS PADRE

void intercambiarValoresTrinity(int arr[], int len, int father, int fpos, int son, int spos) {
	remove<int>(arr, len, fpos);
	insert<int>(arr, len, son, fpos);

	remove<int>(arr, len, spos);
	insert<int>(arr, len, father, spos);

}

void compareTrinity(int arr[], int len, int fpos, int s1pos, int s2pos) {
	int father = arr[fpos], s1 = arr[s1pos], s2 = s2pos < len ? arr[s2pos] : NULL;

	if (father < s1 and s1 >= s2) {
		intercambiarValoresTrinity(arr, len, father, fpos, s1, s1pos);
	}
	if (s2 != 0) {
		if (father < s2 and s2 > s1) {
			intercambiarValoresTrinity(arr, len, father, fpos, s2, s2pos);
		}
	}
}

void intercambiarValoresArr(int arr[], int len, int a, int b) {
	int aux = arr[b];
	remove<int>(arr, len, b);
	add<int>(arr, len, arr[a]);

	remove<int>(arr, len, 0);
	insert<int>(arr, len, aux, 0);
}

void heapSort(int arr[], int len) {
	if (len != 0) {
		int lastFatherPos = (len) / 2 - 1;
		while (lastFatherPos >= 0) {
			//Posiciones
			int son1Pos = lastFatherPos * 2 + 1;
			int son2Pos = lastFatherPos * 2 + 2;
			compareTrinity(arr, len, lastFatherPos, son1Pos, son2Pos);

			//padre anterior
			lastFatherPos -= 1;
		}

		intercambiarValoresArr(arr, len, 0, len - 1);
		len -= 1;
		heapSort(arr, len);
	}
}

// *********************** RADIX SORT ***********************
// todos los elementos del mismo largo
// analizar segun ultimo digito
// hacer arrays de cada digito posible (0,1,...,9)
// unir los arrays
// repetir con el digito anterior hasta cubrirlos todos

// esta hecho con arrays no dinamicos, limite = 20 elemntos

void crearArraysPorDigit (int arr[], int len, int arrDigit[][30], int digito){
	arrDigit[10][len];
	for (int i = 0; i < len; i++){
		if (digitCount(arr[i])>= digito){
			switch (getDigit(arr[i], digito)){
				case 0: {
					int x =  sizeof(arrDigit[0]);
					add<int>(arrDigit[0], x, arr[i]);
					break;
				}
				case 1:{
					int x =  sizeof(arrDigit[1]);
					add<int>(arrDigit[1], x, arr[i]);
					break;
				}
				case 2:{
					int x =  sizeof(arrDigit[2]);
					add<int>(arrDigit[2], x, arr[i]);
					break;
				}
				case 3:{
					int x =  sizeof(arrDigit[3]);
					add<int>(arrDigit[3], x, arr[i]);
					break;
				}
				case 4:{
					int x =  sizeof(arrDigit[4]);
					add<int>(arrDigit[4], x, arr[i]);
					break;
				}
				case 5:{
					int x =  sizeof(arrDigit[5]);
					add<int>(arrDigit[5], x, arr[i]);
					break;
				}
				case 6:{
					int x =  sizeof(arrDigit[6]);
					add<int>(arrDigit[6], x, arr[i]);
					break;
				}
				case 7:{
					int x =  sizeof(arrDigit[7]);
					add<int>(arrDigit[7], x, arr[i]);
					break;
				}
				case 8:{
					int x =  sizeof(arrDigit[8]);
					add<int>(arrDigit[8], x, arr[i]);
					break;
				}
				case 9:{
					int x =  sizeof(arrDigit[9]);
					add<int>(arrDigit[9], x, arr[i]);
					break;
				}
			}
		}
		else {
			int x =  sizeof(arrDigit[0]);
			add<int>(arrDigit[0], x, arr[i]);
		}
	}
}


void radixSort(int arr[], int len) {

	// igualarLongitudDeElementos
	int arrDigit[10][len];

	int digito = 5;//maxdigit;
	for (int i = digito; i > 0; i--) {
		//crearArraysPorDigit (arr, len, arrDigit, digito);
		//unirArrays(arrStr, lista, len, arrLenDigit);

	}

	//getResult(arr, len, arrStr);
}
