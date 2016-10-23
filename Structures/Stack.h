#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <iostream>
#include <cassert>

using namespace std;

template <typename T>
struct elem
{ 
	T inf; 
	elem<T>* link; 
};

template <typename T = int>
class stack
{
	public:
		
		stack();
		~stack();
		stack(const stack&);
		stack& operator=(const stack&);
		
		bool empty() const;
		void push(const T&);
		void pop(T&);
		void top(T&) const;

		
		void print();
		int length();
	
	private:
		elem<T> *start; 
		void copyStack(const stack&);
		void delStack();
};


template <typename T>
stack<T>::stack()
{
	start = NULL;
}

template <typename T>
stack<T>::~stack()
{
	delStack();
}

template <typename T>
stack<T>::stack(const stack<T>& r)
{
	copyStack(r);
}

template <typename T>
stack<T>& stack<T>::operator=(const stack<T>& r)
{
	if(this != &r)
	{
		delStack();
		copyStack(r);
	}
	return *this;
}


template <typename T>
void stack<T>::copyStack(const stack<T>& r)
{
	if(r.start)
	{
		elem<T> *p = r.start, *q = NULL, *s = NULL;
		
		start = new elem<T>;
		assert(start != NULL);
		start->inf = p->inf;
		start->link = q;
		
		q = start;
		p = p->link;
		while(p)
		{ 
			s = new elem<T>;
			assert(s != NULL);
			s->inf = p->inf;
			q->link = s;
			q = s;
			p = p->link;
		}
		q->link = NULL;
	}
	else start = NULL;
}


template <typename T>
void stack<T>::delStack()
{
	elem<T> *p;
	while(start)
	{
		p = start;
		start = start->link;
		delete p;
	}
}


template <typename T>
bool stack<T>::empty() const
{
	return start == NULL;
}


template <typename T>
void stack<T>::push(const T& s)
{
	elem<T>* p = start;
	start = new elem<T>;
	assert(start != NULL);
	start->inf = s;
	start->link = p;
}


template <typename T>
void stack<T>::pop(T& s)
{
	if(start)
	{
		s = start->inf;
		elem<T>* p = start;
		start = start->link;
		delete p;
	}
	else
	{
		cout << "The stack is empty.\n";
		exit(1);
	}
}


template <typename T>
void stack<T>::top(T& s)const
{
	if(start)
		s = start->inf;
	else
	{
		cout << "The stack is empty.\n";
		exit(1);
	}
}


template <typename T>
void stack<T>::print()
{
	T x;
	while(!empty())
	{
		pop(x);
		cout << x << " ";
	}
	cout << endl;
}


template <typename T>
int stack<T>::length()
{
	int n = 0;
	T x;
	while(!empty())
	{
		pop(x);
		n++;
	}
	return n;
}

#endif // STACK_H_INCLUDED
