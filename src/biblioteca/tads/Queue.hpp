// #ifndef _TQUEUE_TAD_
// #define _TQUEUE_TAD_

// #include <iostream>
// #include "../funciones/lists.hpp"

// using namespace std;

// template<typename T>
// struct Queue
// {
//    Node<T>* p;
//    Node<T>* q;
// };

// template<typename T>
// Queue<T> queueCreate()
// {
//    Queue<T> q;
//    q.p = NULL;
//    q.q = NULL;
//    return q;
// }

// template<typename T>
// void queueEnqueue(Queue<T>& q,T v)
// {
//    add<T>(q.q,v);
//    if( q.p==NULL )
//    {
//       q.p = q.q;
//    }
//    else
//    {
//       q.q = q.q->sig;
//    }

//    return;
// }

// template<typename T>
// T queueDequeue(Queue<T>& q)
// {
//    T t = removeFirst<T>(q.p);
//    if(q.p==NULL)
//    {
//       q.q=NULL;
//    }

//    return t;
// }

// template<typename T>
// bool queueIsEmpty(Queue<T> q)
// {
//    return q.p==NULL;
// }

// template<typename T>
// void queueUndequeue(Queue<T> q)
// {
// }

// template<typename T>
// int queueSize(Queue<T> q)
// {
//    return 0;
// }


// #endif

#ifndef _TQUEUE_TAD_
#define _TQUEUE_TAD_

#include <iostream>
#include "../funciones/lists.hpp"

using namespace std;

template<typename T>
struct Queue
{
   Node<T>* p;
   Node<T>* q;
};

template<typename T>
Queue<T> queue()
{
   return {NULL, NULL};
}

template<typename T>
void queueEnqueue(Queue<T>& q,T v)
{
   enqueue<T>(q.p, q.q, v);
}

template<typename T>
T queueDequeue(Queue<T>& q)
{
   T t = dequeue<T>(q.p, q.q);
   return t;
}

template<typename T>
bool queueIsEmpty(Queue<T> q)
{
   return q.p == NULL;
}

template<typename T>
void queueUndequeue(Queue<T> q)
{
   // ???
}

template<typename T>
int queueSize(Queue<T> q) // sirve para circular tambien
{
   int c = 0;
   if(q.p != NULL){
      Node<T>* aux = q.p;
      while (aux != q.q){
         c++;
         aux = aux->sig;
      }
   }
   return c;
}

#endif
