// #ifndef _TSTACK_TAD_
// #define _TSTACK_TAD_

// #include <iostream>
// #include "../funciones/lists.hpp"

// using namespace std;

// template<typename T>
// struct Stack
// {
//    Node<T>* p;
// };

// template<typename T>
// Stack<T> stackCreate()
// {
//    Stack<T> st;
//    st.p = NULL;
//    return st;
// }

// template<typename T>
// void stackPush(Stack<T>& st,T v)
// {
//    Node<T>* nuevo = new Node<T>();
//    nuevo->info=v;
//    nuevo->sig=st.p;
//    st.p = nuevo;
//    return;
// }

// template<typename T>
// T stackPop(Stack<T>& st)
// {
//    Node<T>* aux = st.p;
//    T t = aux->info;
//    st.p = aux->sig;
//    delete aux;
//    return t;
// }

// template<typename T>
// bool stackIsEmpty(Stack<T> st)
// {
//    return st.p==NULL;
// }

// template<typename T>
// int stackSize(Stack<T> s)
// {
//    return 0;
// }


// #endif

#ifndef _TSTACK_TAD_
#define _TSTACK_TAD_

#include <iostream>
#include "../funciones/lists.hpp"

using namespace std;

template<typename T>
struct Stack
{
   Node<T>* p;
};

template<typename T>
Stack<T> stack()
{
   return {NULL};
}

template<typename T>
void stackPush(Stack<T>& st,T v)
{
   push<T>(st.p, v);
}

template<typename T>
T stackPop(Stack<T>& st)
{
   T t = pop<T>(st.p);
   return t;
}

template<typename T>
bool stackIsEmpty(Stack<T> st)
{
   return st.p == NULL;
}

template<typename T>
int stackSize(Stack<T> s)
{
   int c = 0;
   if(s.p != NULL){
      c++;
      Node<T>* aux = s.p;
      while(aux->sig != NULL){
         aux = aux->sig;
         c++;
      }
   }
   return c;
}

#endif
