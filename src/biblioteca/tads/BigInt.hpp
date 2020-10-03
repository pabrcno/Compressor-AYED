#include <iostream>
#include "../funciones/arrays.hpp"
#include "../funciones/strings.hpp"

using namespace std;

//NO CONTEMPLA NUMEROS NEGATIVOS O RESTAS QUE DEN NEGATIVO
//YA LO HICE EN EL BIGINT ORIGINAL

struct  BigInt {
	int arr[50];
	int len;
	int carry = 0;
};

// funcion de inicializacion 
BigInt bigInt(string num) {
	BigInt b = {{},0};

	for (int i = 0; i < length(num); i++) {
		add<int>(b.arr, b.len, charToInt(num[i]));
	}

	return b;
}

// retorna una cadena que representa al numero 
string bigIntToString(BigInt b) {
	string s = "";

	for (int i = 0; i < b.len; i++) {
		s += b.arr[i];
	}

	return s;
}

// similar a la funcion de inicializacion 
BigInt bigIntFromString(string s) {
	BigInt b = bigInt(s);
	return b;
}

void igualarLen(BigInt& a, BigInt& b) {
	if (a.len > b.len) {
		for (int i = 0; a.len > b.len; i++) {
			insert<int>(b.arr, b.len, 0, 0);
		}
	}
	else if (a.len < b.len) {
		for (int i = 0; a.len < b.len; i++) {
			insert<int>(a.arr, a.len, 0, 0);
		}
	}
}

// operaciones: suma y resta 
BigInt bigIntSumar(BigInt a, BigInt b) {
	BigInt r;
	
	igualarLen(a, b);

	for (int i = a.len - 1; i >= 0; i--) {
		int sum = a.arr[i] + b.arr[i] + r.carry;
		
		if (sum > 9) {
			sum -= 10;
			r.carry = 1;
		}

		insert<int>(r.arr, r.len, sum, 0);

		if (i == 0 and r.carry != 0) {
			insert<int>(r.arr, r.len, 1, 0);
		}
		r.carry = 0;
	}
	
	return r;
}

void pedirAlDeAlLado(BigInt& a, BigInt& b) {
	for (int i = a.len-1; i >= 0; i--) {
		if (a.arr[i] < b.arr[i]) {
			a.arr[i] += 10;
			a.arr[i - 1] -= 1;
		}
	}
}

void borrarCerosALaIzq(BigInt& a) {
	for (int i = 0; a.arr[i] == 0; i++) {
		remove<int>(a.arr, a.len, 0);
	}
}

BigInt restarBigInt(BigInt a, BigInt b) {
	BigInt r;
	for (int i = a.len - 1; i >= 0; i--) {
		add<int>(r.arr, r.len, a.arr[i] - b.arr[i]);
	}
	return r;
}

BigInt complementoA10(BigInt& a) {
	BigInt x;
	BigInt r;

	add<int>(x.arr, x.len, 1);
	for (int i = 1; i < a.len; i++) {
		add<int>(x.arr, x.len, 0);
	}

	igualarLen(x, a);
	pedirAlDeAlLado(x, a);

	for (int i = x.len-1; i >= 0; i--) {
		add<int>(r.arr, r.len, (x.arr[i] - a.arr[i]));
	}
	
	r = restarBigInt(x, a);
	borrarCerosALaIzq(r);
	return r;
}

BigInt bigIntRestar(BigInt a, BigInt b) {
	igualarLen(a, b);
	complementoA10(b);
	BigInt r = bigIntSumar(a, b);
	remove<int>(r.arr, r.len, 0);
	return r;
}