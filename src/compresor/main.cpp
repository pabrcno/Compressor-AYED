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

struct PathInfo {
   char ch;
   string path;
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
   HuffmanTreeInfo* rightChild = listNext<HuffmanTreeInfo>(lista);
   HuffmanTreeInfo* leftChild = listNext<HuffmanTreeInfo>(lista);
   HuffmanTreeInfo father;
   father.left = leftChild;
   father.right = rightChild;
   father.n = leftChild->n + rightChild->n;
   father.c = fatherCode;

   // listRemove<HuffmanTreeInfo>(lista, *leftChild, cmpHuffmanTreeInfo);
   // listRemove<HuffmanTreeInfo>(lista, *rightChild, cmpHuffmanTreeInfo);

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
      cout << "["<<hInfo->c << "] ocurrencias: "<< hInfo->n << ", codigo: "<< cod<<endl;
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

   unsigned long long int charCounter = 0;
   for (int i = 0; i < 256; i++){
      if( tabla[i].n > 0){
         charCounter += tabla[i].n;
         write<char>(fComprimido, i);
         write<unsigned char>(fComprimido, length(tabla[i].code));
         for(int j = 0; j < length(tabla[i].code); j++){
            bitWriterWrite(bw, charToInt(tabla[i].code[j]));
         }
         bitWriterFlush(bw);
      }
   }

   write<unsigned long long int>(fComprimido, charCounter);

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

// -----------------------------------------------------------------------------------------

void rebuildTree (HuffmanTreeInfo*& root, PathInfo pathInfo[], unsigned char hojas){
   for(int i = 0; i < hojas ; i++){
      PathInfo info = pathInfo[i];

      HuffmanTreeInfo* position;
      for(int j = 0; j < length(info.path) ; j++){
         if (j==0){
            position = root;
         }

         char bit = info.path[j];
         if(bit == '0'){
            if(position->left != NULL){
               position = position->left;
            }
            else{
               HuffmanTreeInfo* child = new HuffmanTreeInfo();
               child->left = NULL;
               child->right = NULL;
               position->left = child;
               position = child;
               if (j == length(info.path)-1){
                  position->c = info.ch;
               }
            }
         }
         else{
            if(position->right != NULL){
               position = position->right;
            }
            else{
               HuffmanTreeInfo* child = new HuffmanTreeInfo();
               child->left = NULL;
               child->right = NULL;
               position->right = child;
               position = child;
               if (j == length(info.path)-1){
                  position->c = info.ch;
               }
            }

         }
      }
   }
}

void readAndDecode (string fName, FILE* f, HuffmanTreeInfo* root){
   string newFileName = substring(fName, 0, length(fName)-4);
   FILE* newF = fopen(newFileName.c_str(), "w+b");

   BitReader br = bitReaderCreate(f);
   BitWriter bw = bitWriterCreate(newF);

   HuffmanTreeInfo* current = root;
   unsigned long long int longCodificada = read<unsigned long long int>(f);
   for(int i = 0; i < longCodificada; i=i){
      int bit = bitReaderRead(br);
      if (bit == 0){
            current = current->left;
            if(current->left == NULL){
               unsigned char ch = current->c;
               write<unsigned char>(newF, ch);
               i++;
               current = root;
            }
         }
      else{
         current = current->right;
         if (current->right == NULL){
            unsigned char ch = current->c;
            write<unsigned char>(newF, ch);
            i++;
            current = root;
         }
      }
   }

   fclose(newF);
}

void descomprimir(string fName)
{
   FILE* f = fopen (fName.c_str(), "r+b");

   // leer primer byte (cant. hojas)
   unsigned char hojas = read<unsigned char>(f);

   //crear arbol
   HuffmanTreeInfo* root = new HuffmanTreeInfo();
   root->left = NULL;
   root->right = NULL;
   // iterar por esa cantidad, obteniendo cada registro
   int cantHojas = hojas;
   PathInfo pathInfo[cantHojas];
   for(int i = 0; i < hojas; i++){
      BitReader br = bitReaderCreate(f);
      char ch = read<char>(f);
      unsigned char codeLength = read<unsigned char>(f);

      string path = "";
      for (int children = 0; children < codeLength; children++){
         int bit = bitReaderRead(br);
         path += intToString(bit);
      }
      pathInfo[i] = {ch, path};
   }

   rebuildTree(root, pathInfo, hojas);
   // D:<

   readAndDecode(fName, f, root);

   fclose(f);
}

// -------------------------------------------------------------------------------------------

// PROGRAMA PRINCIPAL
int main(int argc,char** argv){
   string fName = argv[1];
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
