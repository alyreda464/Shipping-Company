//#pragma once
//#include <iostream>
//#include "Node.h"
//
//template <typename T>
//class PriQ
//{
//private:
//	Node<T>* Head;
//	Node<T>* backPtr;
//	Node<T>* frontPtr;
//
//public:
//	//Constructor
//	PriQ()
//	{
//		Head = NULL;
//	}
//
//	//Function that enqueues the elemtents sorted according to the key
//	template <typename T>
//	bool enqueue(T* newEntry, const int& newKey)
//	{
//		//Creating the new node to be inserted 
//		Node<T>* temp = new Node<T>(newEntry, newKey);
//		Node<T>* ptr;
//
//		//If the entry is in the first place or the list is empty
//		if (Head == NULL || (temp->getKey() < Head->getKey()))
//		{
//			temp->setNext(Head);
//			Head = temp;
//		}
//		//General Case
//		else
//		{
//			ptr = Head;
//			while (ptr->getNext() != NULL && ptr->getNext()->getKey() <= temp->getKey())
//				ptr = ptr->getNext();
//
//			temp->setNext(ptr->getNext());
//			ptr->setNext(temp);
//		}
//		return true;
//	}
//
//	//Function the takes out elements out of the queue
//	template <typename T>
//	bool dequeue(T* temp)
//	{
//		if (isEmpty())
//			return false;
//
//		temp = Head;
//		Head = Head->getNext();
//		return true;
//
//	}
//
//	//Function the checks the first element.
//	template <typename T>
//	bool peek(Node<T>*& temp)
//	{
//		if (isEmpty())
//			return false;
//
//		temp = Head;
//		return true;
//
//	}
//
//	//Function that checks whether the queue is empty or not
//	template <typename T>
//	bool isEmpty()
//	{
//		return (Head == NULL);
//	}
//  int getCount()
//{
//	int Count = 0;
//	Node<T>* P = Head;
//	while (P)
//	{
//		Count++;
//		P = P->getNext();
//	}
//	return Count;
//}
//
//
//  template <typename T>
//  bool enqueue(const T& newEntry)
//  {
//	  Node<T>* newNodePtr = new Node<T>(newEntry);
//	  // Insert the new node
//	  if (isEmpty()) // The Priorityqueue is empty
//	  {
//		  Head = newNodePtr;
//	  }
//	  else if (newNodePtr->getPriority() > Head->getPriority())  //new node has higher priority than first node
//	  {
//		  newNodePtr->setNext(Head);
//		  Head = newNodePtr;
//	  }
//	  else
//	  {
//		  Node<T>* ptr = Head;
//		  while (ptr->getNext() && ptr->getPriority() >= newNodePtr->getPriority())
//		  {
//			  if (ptr->getNext()->getPriority() < newNodePtr->getPriority())
//			  {
//				  newNodePtr->setNext(Ptr->getNext());
//				  Ptr->setNext(newNodePtr);
//			  }
//			  else
//			  {
//				  Ptr = Ptr->getNext();
//			  }
//			  return true;
//		  }
//	  }
//  } // end enqueue
//};
#ifndef __PriQ_H_
#define __PriQ_H_
#include "Node.h"

template <typename T>
class PriQ
{
private:

	Node<T>* backPtr;
	Node<T>* frontPtr;
public:
	PriQ();
	bool isEmpty() const;
	bool enqueue(const T& newEntry);
	bool enqueue(const T& newEntry, const int& newKey);
	bool dequeue(T& frntEntry);
	bool peekFront(T& frntEntry)  const;
	int getCount();
	T* toArray(int& count);	//returns array of T (array if items)
	~PriQ();
};


template <typename T>
PriQ<T>::PriQ()
{
	backPtr = nullptr;
	frontPtr = nullptr;

}


template <typename T>
bool PriQ<T>::isEmpty() const
{
	if (frontPtr == nullptr)
		return true;
	else
		return false;
}


/*Function:enqueue
Adds newEntry according to its priority.
Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/
template <typename T>
bool PriQ<T>::enqueue(const T& newEntry, const int& newKey)
{
	//Creating the new node to be inserted 
	Node<T>* temp = new Node<T>(newEntry, newKey);
	Node<T>* ptr;

	//If the entry is in the first place or the list is empty
	if (frontPtr == NULL || (temp->getKey() < frontPtr->getKey()))
	{
		temp->setNext(frontPtr);
		frontPtr = temp;
	}
	//General Case
	else
	{
		ptr = frontPtr;
		while (ptr->getNext() != NULL && ptr->getNext()->getKey() <= temp->getKey())
			ptr = ptr->getNext();

		temp->setNext(ptr->getNext());
		ptr->setNext(temp);
	}
	return true;
}

template <typename T>
bool PriQ<T>::enqueue(const T& newEntry)
{
	Node<T>* newNodePtr = new Node<T>(newEntry);
	// Insert the new node
	if (isEmpty()) // The PriQ is empty
	{
		frontPtr = newNodePtr;
		backPtr = newNodePtr;
	}
	else if (newNodePtr->getPriority() > frontPtr->getPriority())  //new node has higher priority than first node
	{
		newNodePtr->setNext(frontPtr);
		frontPtr = newNodePtr;
	}
	else
	{
		Node<T>* ptr = frontPtr;
		while (ptr->getNext() && ptr->getPriority() >= newNodePtr->getPriority())
		{
			if (ptr->getNext()->getPriority() < newNodePtr->getPriority())
			{
				newNodePtr->setNext(ptr->getNext());
				ptr->setNext(newNodePtr);
			}
			else
			{
				ptr = ptr->getNext();
			}
			return true;
		}
	}
 }
 //end enqueue


/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Function: dequeue
Removes the front of this queue. That is, removes the item that was added
earliest.
Input: None.
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool PriQ<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: one node in queue
		backPtr = nullptr;

	// Free memory reserved by the dequeued node
	delete nodeToDeletePtr;


	return true;

}

/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: peekFront
gets the front of this queue. The operation does not modify the queue.
Input: None.
Output: The front of the queue.
return: flase if Queue is empty
*/
template <typename T>
bool PriQ<T>::peekFront(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}
///////////////////////////////////////////////////////////////////////////////////

template <typename T>
PriQ<T>::~PriQ()
{
}

/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: toArray
returns an array of "T"
Output: count: the length of the returned array (zero if Queue is empty)
returns: The array of T. (nullptr if Queue is empty)
*/
template <typename T>
int PriQ<T>::getCount()
{
	int Count = 0;
	Node<T>* P = frontPtr;
	while (P)
	{
		Count++;
		P = P->getNext();
	}
	return Count;
}
template <typename T>
T* PriQ<T>::toArray(int& count)
{
	count = 0;

	if (!frontPtr)
		return nullptr;
	//counting the no. of items in the Queue
	Node<T>* p = frontPtr;
	while (p)
	{
		count++;
		p = p->getNext();
	}


	T* Arr = new T[count];
	p = frontPtr;
	for (int i = 0; i < count; i++)
	{
		Arr[i] = p->getItem();
		p = p->getNext();
	}
	return Arr;
}

#endif
