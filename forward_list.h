#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

class ForwardList
{
public:
	ForwardList();
	~ForwardList();
	ForwardList(const ForwardList&);
	ForwardList(ForwardList&&);
public:
	ForwardList& operator=(const ForwardList&);
	ForwardList& operator=(ForwardList&&);
	bool operator==(ForwardList&);
	bool operator!=(ForwardList&);
public:
	void sort();
	void merge(ForwardList);
public:
	const int& front() const;
	int length();
	int begin() const;
	int end() const;
	bool empty() const;
	void clear();
	void push_front(int);
	void pop_front();
	void insert_after(int, int);
	void erase_after(int);
	void resize(int);
	void swap(ForwardList&);
	void reverse();
	void print();
private:
	struct Node
	{
		int val;
		Node* next;
		Node() : val{}, next{nullptr} {}
		Node(const int& rhs) : val{rhs}, next{nullptr} {}
	}*head;
	int m_size;
};
#endif // FORWARD_LIST_H
