#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include <iostream>
#include <exception>

template <typename T>
class ForwardList
{
public:
	ForwardList();
	~ForwardList();
	ForwardList(const ForwardList<T>&);
	ForwardList(ForwardList<T>&&);
public:
	ForwardList& operator=(const ForwardList<T>&);
	ForwardList& operator=(ForwardList<T>&&);
	bool operator==(ForwardList<T>&);
	bool operator!=(ForwardList<T>&);
public:
	void sort();
	void merge(ForwardList<T>);
public:
	const T& front() const;
	int length();
	T begin() const;
	T end() const;
	bool empty() const;
	void clear();
	void push_front(T);
	void pop_front();
	void insert_after(int, T);
	void erase_after(int);
	void resize(int);
	void swap(ForwardList<T>&);
	void reverse();
	void print();
private:
	struct Node
	{
		T val;
		Node* next;
		Node() : val{}, next{nullptr} {}
		Node(const T& rhs) : val{rhs}, next{nullptr} {}
	}*head;
	int m_size;
};
#endif // FORWARD_LIST_H
