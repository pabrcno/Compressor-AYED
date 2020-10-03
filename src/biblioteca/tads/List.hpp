// #ifndef _TLIST_TAD_
// #define _TLIST_TAD_

// #include <iostream>
// #include "../funciones/lists.hpp"

// using namespace std;

// template<typename T>
// struct List
// {
//    T info;
//    Node<T>* p;
//    Node<T>* curr;
// };

// template<typename T>
// List<T> listCreate()
// {
//    List<T> lst;
//    lst.p = NULL;
//    lst.curr = NULL;
//    return lst;
// }

// template<typename T>
// T* listAdd(List<T>& lst,T v)
// {
//    Node<T>* aux = add<T>(lst.p,v);

//    // si agregue el primer nodo de la lista...
//    if(lst.p->sig==NULL)
//    {
//       lst.curr = lst.p;
//    }

//    return &aux->info;
// }

// template<typename T,typename K>
// void listRemove(List<T>& lst,K k, int cmpTK(T,K))
// {
//    remove<T,K>(lst.p,k,cmpTK);
// }

// template<typename T,typename K>
// T* listFind(List<T> lst,K k, int cmpTK(T,K))
// {
//    Node<T>* x=find<T,K>(lst.p,k,cmpTK);
//    return &x->info;
// }

// template<typename T>
// T* listOrderedInsert(List<T>& lst,T t,int cmpTT(T,T))
// {
//    return &orderedInsert<T>(lst.p,t,cmpTT)->info;
// }

// template<typename T>
// void listSort(List<T>& lst,int cmpTT(T,T))
// {
//    sort<T>(lst.p,cmpTT);
// }

// template<typename T>
// bool listHasNext(List<T>& lst)
// {
//    return lst.curr!=NULL;
// }

// template<typename T>
// T* listNext(List<T>& lst)
// {
//    Node<T>* aux = lst.curr;
//    lst.curr = lst.curr->sig;
//    return &aux->info;
// }

// template<typename T>
// void listReset(List<T>& lst)
// {
//    lst.curr = lst.p;
//    return;
// }

// template<typename T>
// void listFree(List<T>& lst)
// {
//    free<T>(lst.p);
//    listReset<T>(lst);
//    return;
// }

// #endif

#ifndef _TLIST_TAD_
#define _TLIST_TAD_

#include <iostream>
#include "../funciones/lists.hpp"

using namespace std;

template<typename T>
struct List
{
   Node<T>* p;
   Node<T>* current;
};

template<typename T>
List<T> listCreate()
{
   List<T> l;
   l.p = NULL;
   l.current = NULL;
   return l;
}

template<typename T>
T* listAdd(List<T>& lst,T v)
{
   Node<T>* node = add<T>(lst.p, v);
   if (lst.p->sig == NULL){
      lst.current = lst.p;
   }
   T* pointer = &(node->info);
   return pointer;
}

template<typename T,typename K>
void listRemove(List<T>& lst,K k, int cmpTK(T,K))
{
   remove<T,K>(lst.p, k, cmpTK);
}

template<typename T,typename K>
T* listFind(List<T> lst,K k, int cmpTK(T,K))
{
   Node<T>* x = find<T,K>(lst.p, k, cmpTK);
   return &(x->info);
}

template<typename T>
T* listOrderedInsert(List<T>& lst,T t,int cmpTT(T,T))
{
   Node<T>* n = orderedInsert<T>(lst.p, t, cmpTT);
   return &(n->info);
}

template<typename T>
void listSort(List<T>& lst,int cmpTT(T,T))
{
   sort<T>(lst.p, cmpTT);
}

template<typename T>
bool listIsEmpty(List<T> lst){
   return lst.p == NULL;
}

template<typename T>
int listSize(List<T> lst){
   int c = 0;
   Node<T>* curr = lst.current;
   lst.current = lst.p;
   if(!listIsEmpty<T>(lst)){
      c++;
      while(lst.current->sig != NULL){
         lst.current = lst.current->sig;
         c++;
      }
   }
   lst.current = curr;
   return c;
}

template<typename T>
void listFree(List<T>& lst)
{
   free<T>(lst.p);
}

template<typename T>
void listReset(List<T>& lst)
{
   lst.current = lst.p;
}

template<typename T>
bool listHasNext(List<T>& lst)
{
   return lst.current!=NULL;
}

template<typename T>
T* listNext(List<T>& lst)
{
   Node<T>* aux = lst.current;
   lst.current = lst.current->sig;
   return &aux->info;
}

#endif
