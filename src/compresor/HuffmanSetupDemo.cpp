
// #ifndef _MAIN
// #define _MAIN

// #include <iostream>
// #include "biblioteca/tads/Arr.hpp"
// #include "biblioteca/tads/Map.hpp"
// #include "biblioteca/tads/List.hpp"
// #include "biblioteca/tads/Stack.hpp"
// #include "biblioteca/tads/Queue.hpp"
// #include "biblioteca/funciones/strings.hpp"
// #include "biblioteca/funciones/tokens.hpp"
// #include "biblioteca/funciones/files.hpp"
// #include "HuffmanSetup.hpp"

// using namespace std;


// HuffmanTreeInfo* huffmanTreeInfo(int c, long n, HuffmanTreeInfo* left, HuffmanTreeInfo* right)
// {
//   HuffmanTreeInfo* node = new HuffmanTreeInfo();
//   node->c=c;
//   node->n=n;
//   node->left=left;
//   node->right=right;
//   return node;
// }

// HuffmanTreeInfo* crearArbolHuffman()
// {
//   // nivel 5 (ultimo nivel)
//   HuffmanTreeInfo* nS = huffmanTreeInfo('S', 1, NULL, NULL);
//   HuffmanTreeInfo* nR = huffmanTreeInfo('R', 1, NULL, NULL);
//   HuffmanTreeInfo* nN = huffmanTreeInfo('N', 1, NULL, NULL);
//   HuffmanTreeInfo* nI = huffmanTreeInfo('I', 1, NULL, NULL);

//   // nivel 4
//   HuffmanTreeInfo* a2 = huffmanTreeInfo(256+2, 2, nS, nR);

//   HuffmanTreeInfo* a1 = huffmanTreeInfo(256+1, 2, nN, nI);
//   HuffmanTreeInfo* nT = huffmanTreeInfo('T', 2, NULL, NULL);
//   HuffmanTreeInfo* nE = huffmanTreeInfo('E', 2, NULL, NULL);
//   HuffmanTreeInfo* nA = huffmanTreeInfo('A', 2, NULL, NULL);
//   HuffmanTreeInfo* nU = huffmanTreeInfo('U', 1, NULL, NULL);

//   // nivel 3
//   HuffmanTreeInfo* nC = huffmanTreeInfo('C', 7, NULL, NULL);
//   HuffmanTreeInfo* nM = huffmanTreeInfo('M', 5, NULL, NULL);
//   HuffmanTreeInfo* nESP = huffmanTreeInfo(' ', 5, NULL, NULL);
//   HuffmanTreeInfo* a5 = huffmanTreeInfo(256+5, 4, a2, a1);
//   HuffmanTreeInfo* a4 = huffmanTreeInfo(256+4, 4, nT, nE);
//   HuffmanTreeInfo* a3 = huffmanTreeInfo(256+3, 3, nA, nU);

//   // nivel 2
//   HuffmanTreeInfo* a8 = huffmanTreeInfo(256+8, 12, nC, nM);
//   HuffmanTreeInfo* nO = huffmanTreeInfo('O', 11, NULL, NULL);
//   HuffmanTreeInfo* a7 = huffmanTreeInfo(256+7, 9, nESP, a5);
//   HuffmanTreeInfo* a6 = huffmanTreeInfo(256+6, 7, a4, a3);

//   // nivel 1
//   HuffmanTreeInfo* a10 = huffmanTreeInfo(256+10, 23, a8, nO);
//   HuffmanTreeInfo* a9  = huffmanTreeInfo(256+9, 16, a7, a6);

//   // nivel 0 (raiz)
//   HuffmanTreeInfo* a11 = huffmanTreeInfo(256+11, 39, a10, a9);

//   return a11;
// }

// // PROGRAMA PRINCIPAL
// int main(int argc,char** argv)
// {
//   // obtengo el arbol
//   HuffmanTreeInfo* root = crearArbolHuffman();

//   // recorro el arbol usando TAD HuffmanTree
//   HuffmanTree ht = huffmanTree(root);

//   string cod;
//   while( huffmanTreeHasNext(ht) )
//   {
//      HuffmanTreeInfo* x = huffmanTreeNext(ht,cod);
//      cout << x->c << ", ("<<x->n <<"), " << "[" << cod <<"]" << endl;
//   }

//   return 0;
// }

// #endif
