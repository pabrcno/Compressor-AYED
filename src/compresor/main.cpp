//
//#ifndef _MAIN
//#define _MAIN
//
//#include <iostream>
//#include "biblioteca/tads/Arr.hpp"
//#include "biblioteca/tads/Map.hpp"
//#include "biblioteca/tads/List.hpp"
//#include "biblioteca/tads/Stack.hpp"
//#include "biblioteca/tads/Queue.hpp"
//#include "biblioteca/funciones/strings.hpp"
//#include "biblioteca/funciones/tokens.hpp"
//#include "biblioteca/funciones/files.hpp"
//#include "HuffmanTree.hpp"
//
//using namespace std;
//
//
//HuffmanTreeInfo* treeInfo(int c, long n, HuffmanTreeInfo* left, HuffmanTreeInfo* right)
//{
//   HuffmanTreeInfo* node = new HuffmanTreeInfo();
//   node->c=c;
//   node->n=n;
//   node->left=left;
//   node->right=right;
//   return node;
//}
//
//HuffmanTreeInfo* createTree()
//{
//   // nivel 5 (ultimo nivel)
//   HuffmanTreeInfo* nS = treeInfo('S', 1, NULL, NULL);
//   HuffmanTreeInfo* nR = treeInfo('R', 1, NULL, NULL);
//   HuffmanTreeInfo* nN = treeInfo('N', 1, NULL, NULL);
//   HuffmanTreeInfo* nI = treeInfo('I', 1, NULL, NULL);
//
//   // nivel 4
//   HuffmanTreeInfo* a2 = treeInfo(256+2, 2, nS, nR);
//
//   HuffmanTreeInfo* a1 = treeInfo(256+1, 2, nN, nI);
//   HuffmanTreeInfo* nT = treeInfo('T', 2, NULL, NULL);
//   HuffmanTreeInfo* nE = treeInfo('E', 2, NULL, NULL);
//   HuffmanTreeInfo* nA = treeInfo('A', 2, NULL, NULL);
//   HuffmanTreeInfo* nU = treeInfo('U', 1, NULL, NULL);
//
//   // nivel 3
//   HuffmanTreeInfo* nC = treeInfo('C', 7, NULL, NULL);
//   HuffmanTreeInfo* nM = treeInfo('M', 5, NULL, NULL);
//   HuffmanTreeInfo* nESP = treeInfo(' ', 5, NULL, NULL);
//   HuffmanTreeInfo* a5 = treeInfo(256+5, 4, a2, a1);
//   HuffmanTreeInfo* a4 = treeInfo(256+4, 4, nT, nE);
//   HuffmanTreeInfo* a3 = treeInfo(256+3, 3, nA, nU);
//
//   // nivel 2
//   HuffmanTreeInfo* a8 = treeInfo(256+8, 12, nC, nM);
//   HuffmanTreeInfo* nO = treeInfo('O', 11, NULL, NULL);
//   HuffmanTreeInfo* a7 = treeInfo(256+7, 9, nESP, a5);
//   HuffmanTreeInfo* a6 = treeInfo(256+6, 7, a4, a3);
//
//   // nivel 1
//   HuffmanTreeInfo* a10 = treeInfo(256+10, 23, a8, nO);
//   HuffmanTreeInfo* a9  = treeInfo(256+9, 16, a7, a6);
//
//   // nivel 0 (raiz)
//   HuffmanTreeInfo* a11 = treeInfo(256+11, 39, a10, a9);
//
//   return a11;
//}
//
//// PROGRAMA PRINCIPAL
//int main(int argc,char** argv)
//{
//   // obtengo el arbol
//   HuffmanTreeInfo* root = createTree();
//
//   // recorro el arbol
//   HuffmanTree tu = huffmanTree(root);
//
//   string cod;
//   HuffmanTreeInfo* x = treeUtilNext(tu,cod);
//   while( x!=NULL )
//   {
//      cout << x->c << ", ("<<x->n <<"), " << "[" << cod <<"]" << endl;
//      x = treeUtilNext(tu,cod);
//   }
//
//   return 0;
//}
//
//
//
//
//
//#endif



#ifndef _MAIN
#define _MAIN

#include <iostream>
#include <conio.h>
#include <string.h>
#include "../biblioteca/tads/Arr.hpp"
#include "../biblioteca/tads/Map.hpp"
#include "../biblioteca/tads/List.hpp"
#include "../biblioteca/tads/Stack.hpp"
#include "../biblioteca/tads/Queue.hpp"
#include "../biblioteca/funciones/strings.hpp"
#include "../biblioteca/funciones/tokens.hpp"
#include "../biblioteca/funciones/files.hpp"
#include "../biblioteca/funciones/arrays.hpp"
#include "../biblioteca/funciones/sort.hpp"
#include "../biblioteca/funciones/lists.hpp"

#include "../biblioteca/tads/BitWriter.hpp"
#include "../biblioteca/tads/BitReader.hpp"
#include "HuffmanSetup.hpp"

using namespace std;

struct HuffmanTable
{
   unsigned int n = 0;
   string code;
};

void contarOcurrencias(string fName,HuffmanTable tabla[])
{
   FILE* f = fopen(fName.c_str(), "r+b"); // !!!

   char ch = read<char>(f);
   while(!feof(f)){
      HuffmanTable* celdaAModificar = &(tabla[ch]);
      if (celdaAModificar->n == 0){
         celdaAModificar->code = ch;
      }
      celdaAModificar->n++;

      ch = read<char>(f);
   }

   fclose(f);
}

void crearLista(List<HuffmanTreeInfo>& lista,HuffmanTable tabla[])
{
   HuffmanTreeInfo hTreeInfo;
   for(int i= 0; i < 256 ; i++ ){
      HuffmanTable hTable = tabla[i];
      if (hTable.n > 0){
         hTreeInfo.c = stringToChar(hTable.code);
         hTreeInfo.n = hTable.n;
         hTreeInfo.left = NULL;
         hTreeInfo.right = NULL;

         listAdd<HuffmanTreeInfo>(lista, hTreeInfo);
      }
   }

   listSort<HuffmanTreeInfo>(lista, cmpHuffmanTreeInfo);
}

void branchCreate(List<HuffmanTreeInfo>& lista, HuffmanTreeInfo*& root, int& fatherCode){
   HuffmanTreeInfo* leftChild = listNext<HuffmanTreeInfo>(lista);
   HuffmanTreeInfo* rightChild = listNext<HuffmanTreeInfo>(lista);

   HuffmanTreeInfo father;
   father.left = leftChild;
   father.right = rightChild;
   father.n = leftChild->n + rightChild->n;
   father.c = fatherCode;

   root = listOrderedInsert<HuffmanTreeInfo>(lista, father, cmpHuffmanTreeInfo);
   fatherCode++;
}

HuffmanTreeInfo* crearArbol(List<HuffmanTreeInfo> lista)
{
   HuffmanTreeInfo* root;
   listReset<HuffmanTreeInfo>(lista);
   int fatherCode = 257;
   while(lista.current->sig->sig){
      branchCreate(lista, root, fatherCode);
   }
   branchCreate(lista, root, fatherCode);

   listReset<HuffmanTreeInfo>(lista);
   return root;
}

void cargarCodigosEnTabla(HuffmanTreeInfo* raiz,HuffmanTable tabla[])
{
   HuffmanTree tree = huffmanTree(raiz);
   string cod;
   while(huffmanTreeHasNext(tree)){
      HuffmanTreeInfo* hInfo = huffmanTreeNext(tree, cod);
      HuffmanTable* celdaAModificar = &(tabla[hInfo->c]);
      celdaAModificar->code = cod;
   }
}

unsigned char calcularHojas(HuffmanTable tabla[]){
   int hojas = 0;
   for (int i = 0; i < 256 ; i++){
      HuffmanTable hTable = tabla[i];
      if (hTable.n > 0){
         hojas++;
      }
   }
   return hojas;
}

void grabarArchivoComprimido(string fName,HuffmanTable tabla[])
{
   unsigned char hojas = calcularHojas(tabla);

   string s = fName + ".huf";
   FILE* fComprimido = fopen(s.c_str(), "w+b");
   FILE* fOriginal = fopen(fName.c_str(), "r+b");

   write<unsigned char>(fComprimido, hojas);

   BitWriter bw = bitWriterCreate(fComprimido);
   char ch = read<char>(fOriginal);
   while(!feof(fOriginal)){
      HuffmanTable hTableCell = tabla[ch];
      string codigo = hTableCell.code;

      for(int i = 0; i < length(codigo); i++){
         bitWriterWrite(bw, charToInt(codigo[i]));

      }

      ch = read<char>(fOriginal);
   }
   bitWriterFlush(bw);

   fclose(fOriginal);
   fclose(fComprimido);
}

void comprimir(string fName)
{
   // paso 1
   HuffmanTable tabla[256];
   contarOcurrencias(fName,tabla);

   // paso 2
   List<HuffmanTreeInfo> lista = listCreate<HuffmanTreeInfo>();
   crearLista(lista,tabla);

   // paso 3
   HuffmanTreeInfo* raiz = crearArbol(lista);

   // Recorro el arbol para obtener los codigos
   cargarCodigosEnTabla(raiz,tabla);

   // Grabo el archivo comprimido
   grabarArchivoComprimido(fName,tabla);
}

void descomprimir(string fName)
{
}

// PROGRAMA PRINCIPAL
int main()
{
   string fName = "C:\\Users\\agus_\\Documents\\Programming\\C++\\AYED2C\\PRUEBA.txt";
   if( !endsWith(fName,".huf") )
   {
      comprimir(fName);
   }
   else
   {
      descomprimir(fName);
   }

   return 0;
}

#endif
