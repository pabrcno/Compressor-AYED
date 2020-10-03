// #ifndef _TLIST_T_
// #define _TLIST_T_

// #include <iostream>
// #include <stdio.h>

// template <typename T> struct Node
// {
//    T info;       // valor que contiene el nodo
//    Node<T>* sig; // puntero al siguiente nodo
// };

// template <typename T> Node<T>* add(Node<T>*& p, T x)
// {
//    // creo un nodo nuevo
//    Node<T>* nuevo = new Node<T>();
//    nuevo->info = x;
//    nuevo->sig = NULL;

//    if( p==NULL )
//    {
//       p = nuevo;
//    }
//    else
//    {
//       Node<T>* aux = p;
//       while( aux->sig!=NULL )
//       {
//          aux = aux->sig;
//       }

//       aux->sig = nuevo;
//    }

//    return nuevo;
// }

// template <typename T> void free(Node<T>*& p)
// {
//    Node<T>* sig;
//    while( p!=NULL )
//    {
//       sig = p->sig;
//       delete p;
//       p = sig;
//    }
// }

// template <typename T, typename K>
// Node<T>* find(Node<T>* p, K v, int cmpTK(T,K) )
// {
//    Node<T>* aux = p;
//    while( aux!=NULL && cmpTK(aux->info,v)!=0 )
//    {
//       aux = aux->sig;
//    }

//    return aux;
// }

// template <typename T, typename K>
// void remove(Node<T>*& p, K v, int cmpTK(T,K))
// {
//    Node<T>* aux = p;
//    Node<T>* ant = NULL;

//    while( aux!=NULL && cmpTK(aux->info,v)!=0 )
//    {
//       ant = aux;
//       aux = aux->sig;
//    }

//    if( ant!=NULL )
//    {
//       ant->sig = aux->sig;
//    }
//    else
//    {
//       p = aux->sig;
//    }

//    delete aux;
// }

// template <typename T>
// T removeFirst(Node<T>*& p)
// {
//    T ret = p->info;
//    Node<T>* aux = p->sig;

//    delete p;
//    p = aux;

//    return ret;
// }

// template <typename T>
// void insertFirst(Node<T>*& p, T v)
// {
//    Node<T>* nuevo = new Node<T>();
//    nuevo->info = v;
//    nuevo->sig = p;
//    p = nuevo;
// }

// template <typename T>
// Node<T>* orderedInsert(Node<T>*& p, T v, int cmpTT(T,T) )
// {
//    Node<T>* nuevo = new Node<T>();
//    nuevo->info = v;
//    nuevo->sig = NULL;

//    Node<T>* aux = p;
//    Node<T>* ant = NULL;
//    while( aux!=NULL && cmpTT(aux->info,v)<=0 )
//    {
//       ant = aux;
//       aux = aux->sig;
//    }

//    if( ant==NULL )
//    {
//       p = nuevo;
//    }
//    else
//    {
//       ant->sig = nuevo;
//    }

//    nuevo->sig = aux;

//    return nuevo;
// }

// template <typename T>
// void sort(Node<T>*& p, int cmpTT(T,T))
// {
//    Node<T>* q = NULL;
//    while( p!=NULL )
//    {
//       T v = removeFirst<T>(p);
//       orderedInsert<T>(q,v,cmpTT);
//    }

//    p = q;
// }

// template <typename T>
// Node<T>* searchAndInsert(Node<T>*& p,T v,bool& enc,int cmpTT(T,T))
// {
//    Node<T>* x = find<T,T>(p,v,cmpTT);
//    enc = x!=NULL;

//    if( !enc )
//    {
//       x = orderedInsert<T>(p,v,cmpTT);
//    }

//    return x;
// }

// template <typename T> bool isEmpty(Node<T>* p)
// {
//    return p==NULL;
// }

// template <typename T> void push(Node<T>*& p, T v)
// {
//    // se resuelve insertando un nodo al inicio de la lista
//    insertFirst<T>(p,v);
// }

// template <typename T> T pop(Node<T>*& p)
// {
//    // se resuelve eliminando el primer nodo de la lista y retornando su valor
//    return removeFirst(p);
// }

// template <typename T>
// void enqueue(Node<T>*& p, Node<T>*& q, T v)
// {
//    add<T>(q,v);
//    if( p==NULL )
//    {
//       p = q;
//    }
//    else
//    {
//       q = q->sig;
//    }
// }

// template <typename T>
// T dequeue(Node<T>*& p, Node<T>*& q)
// {
//    T v = removeFirst<T>(p);

//    if( p==NULL )
//    {
//       q = NULL;
//    }

//    return v;
// }

// #endif

#ifndef _TLIST_T_
#define _TLIST_T_

#include <iostream>
#include <stdio.h>

template <typename T>
struct Node
{
   T info;
   Node<T> *sig;
};

template <typename T>
Node<T> *add(Node<T> *&p, T x)
{
   Node<T> *newNode = new Node<T>();
   newNode->info = x;
   newNode->sig = NULL;

   Node<T> *aux = p;
   if (p != NULL)
   {
      while (aux->sig != NULL)
      {
         aux = aux->sig;
      }
      aux->sig = newNode;
   }
   else
   {
      p = newNode;
   }
   return newNode;
}

template <typename T>
void free(Node<T> *&p)
{
   while (p != NULL)
   {
      Node<T> *aux = p->sig;
      delete p;
      p = aux;
   }
}

template <typename T, typename K>
Node<T> *find(Node<T> *p, K v, int cmpTK(T, K))
{
   Node<T> *aux = p;
   while (cmpTK(aux->info, v)!= 0 && aux != NULL)
   {
      aux = aux->sig;
   }
   return aux;
}

template <typename T, typename K>
T remove(Node<T> *&p, K v, int cmpTK(T, K))
{
   Node<T> *aux = p;
   Node<T> *ant = NULL;
   while (cmpTK(aux->info, v) != 0 and aux != NULL)
   {
      ant = aux;
      aux = aux->sig;
   }
   if (ant == NULL)
   {
      p = aux;
   }
   else
   {
      ant->sig = aux->sig;
   }
   T x = aux->info;
   delete aux;
   return x;
}

template <typename T>
T removeFirst(Node<T>*& p)
{
   Node<T> *aux = p;
   p = aux->sig;
   T t = aux->info;
   delete aux;
   return t;
}

template <typename T>
void addFirst(Node<T> *&p, T v)
{
   Node<T> *f = new Node<T>();
   f->info = v;
   f->sig = p;
   p = f;
}

template <typename T>
Node<T> *orderedInsert(Node<T> *&p, T v, int cmpTT(T, T))
{
 Node<T> *nuevo = new Node<T>();
   nuevo->info = v;
   nuevo->sig = NULL;

   Node<T> *aux = p;
   Node<T> *ant = NULL;
   while (aux != NULL && cmpTT(aux->info, v) < 0)
   {
      ant = aux;
      aux = aux->sig;
   }

   if (ant == NULL)
   {
      p = nuevo;
   }
   else
   {
      ant->sig = nuevo;
   }

   nuevo->sig = aux;

   return nuevo;
}

template <typename T>
void sort(Node<T> *&p, int cmpTT(T, T))
{
   Node<T>* nuevo = NULL;
   while (p!=NULL){
      T value = removeFirst<T>(p);
      orderedInsert(nuevo, value, cmpTT);
   }
   free<T>(p);
   p = nuevo;
}

template <typename T> Node<T>* searchAndInsert(Node<T>*& p, T e, bool& enc, int cmpTT(T,T)){
   //si estaba true
   Node<T>* pos = find<T,T>(p, e, cmpTT);
   if (pos == NULL){
      enc = false;
      pos = orderedInsert<T>(p, e, cmpTT);
   }
   else{
      enc = true;
   }

   return pos;
}

template <typename T>
bool isEmpty(Node<T> *p)
{
   return p==NULL;
}

template <typename T>
void push(Node<T> *&p, T v)
{
   addFirst(p,v);
}

template <typename T>
T pop(Node<T> *&p)
{
   T t = removeFirst<T>(p);
   return t;
}

template <typename T>
void enqueue(Node<T> *&p, Node<T> *&q, T v)
{
   Node<T>* x = add<T>(p, v);
   q->sig = x;
}

template <typename T>
Node<T>* enqueue(Node<T>*& q,T e){ // circular
   Node<T>* nuevo = new Node<T>();
   nuevo->info = e;
   nuevo->sig = q->sig;
   q->sig = nuevo;
   return nuevo;
}

template <typename T>
T dequeue(Node<T> *&p, Node<T> *&q)
{
   Node<T>* aux = p;
   p = p->sig;
   T t = aux->info;
   delete aux;
   p==NULL? q = NULL : 0;

   return t;
}

template <typename T>
T dequeue(Node<T>*& q){ // circular
   Node<T>* aux = q->sig;
   q->sig = q->sig->sig;
   T t = aux->info;
   delete aux;
   return t;
}


#endif
