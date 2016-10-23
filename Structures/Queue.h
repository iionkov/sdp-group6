#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <iostream>
#include <cmath>
#include <cassert>

using namespace std;

template <typename T = int>
struct elem_q
{ 
	T inf; // информационна част
	elem_q<T>* link; // адресна част
};

template <typename T = int>
class queue
{ 
	public:
		// канонично представяне
		queue();
		~queue();
		queue(const queue&);
		queue& operator=(const queue&);
		
		// основни функции
		bool empty() const;
		void push(const T&);
		void pop(T&);
		void head(T&) const;
		
		// променят опашката
		void print();
		int length();

	private:
		elem_q<T> *front, // указател към началото
				  *rear; // указател към края
		// помощни функции
		void copyQueue(const queue&);
		void deleteQueue();
};

// канонично представяне
template <typename T>
queue<T>::queue()
{ 
	front = rear = NULL;
}

template <typename T>
queue<T>::~queue()
{ 
	deleteQueue();
}

template <typename T>
queue<T>::queue(const queue<T>& r)
{ 
	copyQueue(r);
}

template <typename T>
queue<T>& queue<T>::operator=(const queue<T>& r)
{ 
	if (this != &r)
	{ 
		deleteQueue();
		copyQueue(r);
	}
	
	return *this;
}

template <typename T>
void queue<T>::copyQueue(const queue<T>& r)
{ 
	front = rear = NULL;
	elem_q<T> *p = r.front;
	while (p)
	{ 
		push(p->inf);
		p = p->link;
	}
}

template <typename T>
void queue<T>::deleteQueue()
{ 
	T x;
	while (!empty())
		pop(x);
}

template <typename T>
bool queue<T>::empty() const
{ 
	return rear == NULL;
}

template <typename T>
void queue<T>::push(const T& x)
{ 
	elem_q<T> *p = new elem_q<T>;
	assert(p != NULL);
	p->inf = x;
	p->link = NULL;
	
	if (rear) 
		rear->link = p;
	else front = p;
	
	rear = p;
}

template <typename T>
void queue<T>::pop(T& x)
{ 
	if (empty())
	{ 
		cout << "The queue is empty.\n";
		exit(1);
	}
	else
	{ 
		elem_q<T> *p = front;
		x = p->inf;
		
		if (p == rear)
		{ 
			rear = NULL;
			front = NULL;
		}
		else front = p->link;
		
		delete p;
	}
}

template <typename T>
void queue<T>::head(T& x) const
{ 
	if (empty())
	{ 
		cout << "The queue is empty.\n";
		exit(1);
	}
	else
		x = front->inf;
}

template <typename T>
void queue<T>::print()
{ 
	T x;
	while (!empty())
	{ 
		pop(x);
		cout << x << " ";
	}
	cout << endl;
}

template <typename T>
int queue<T>::length()
{ 
	T x; int n = 0;
	while (!empty())
	{ 
		pop(x);
		n++;
	}
	return n;
}

#endif // QUEUE_H_INCLUDED