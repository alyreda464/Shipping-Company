#ifndef __NODE_H_
#define __NODE_H_
class Cargo;
template < typename T>
class Node
{
private:
	T item; // A data item
	Node<T>* next; // Pointer to next node
	int priority;
public:
	Node();
	Node(const T& r_Item);	//passing by const ref.
	Node(const T& r_Item, Node<T>* nextNodePtr);
	Node(T newItem, int pri);
	//Node(const T& r_Item, const int& pr);
	void setItem(const T& r_Item);
	void setNext(Node<T>* nextNodePtr);
	T getItem() const;
	Node<T>* getNext() const;
	void setPriority(Cargo* c);
	int getPriority() const;
	int getKey();
	//void Get_next_of();
}; // end Node


template < typename T>
Node<T>::Node()
{
	next = nullptr;
}

template < typename T>
Node<T>::Node(const T& r_Item)
{
	item = r_Item;
	next = nullptr;
}

template < typename T>
Node<T>::Node(const T& r_Item, Node<T>* nextNodePtr)
{
	item = r_Item;
	next = nextNodePtr;
}

template < typename T>
Node<T>::Node(T newItem, int pri) //non-default constructor
{
	item = newItem;
	priority = pri;
	next = nullptr;
}
template < typename T>
void Node<T>::setItem(const T& r_Item)
{
	item = r_Item;
}

template < typename T>
void Node<T>::setNext(Node<T>* nextNodePtr)
{
	next = nextNodePtr;
}

template < typename T>
T Node<T>::getItem() const
{
	return item;
}

template < typename T>
Node<T>* Node<T>::getNext() const
{
	return next;
}

template < typename T>
void Node<T>::setPriority(Cargo* c)
{
	Priority = c->getCost() / (c->getDistance() * (c->getPreparationTimeh() +( c->getPreparationTimed() * 24 )));
}


template < typename T>
int Node<T>::getPriority() const
{
	return priority;
}
template < typename T>
int Node<T>::getKey()
{
	return priority;
}

/*template < typename T>
void Node<T>::Get_next_of()
{
	if (this)
	{
		this = this->getNext();
	}
}*/

#endif