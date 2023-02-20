#include <iostream>
#include "list.h"

ForwardList::ForwardList() : head{nullptr}, m_size{} {}

ForwardList::~ForwardList() 
{
	if (head) 
	{
		clear();
	}
}

ForwardList::ForwardList(const ForwardList& other)
{
	if (other.head == nullptr)
	{
		head = nullptr;
	}
	else
	{
		head = new Node(other.head->val);
		Node* tmp1 = head;
		Node* tmp2 = other.head->next;
		while (tmp2)
		{
			tmp1->next = new Node(tmp2->val);
			tmp1 = tmp1->next;
			tmp2 = tmp2->next;
		}
	}
}

ForwardList::ForwardList(ForwardList&& other)
{
	head = other.head;
	other.head = nullptr;
}

ForwardList& ForwardList::operator=(const ForwardList& rhs)
{
	if (this->head == rhs.head)
	{
		return *this;
	}
	head = new Node(rhs.head->val);
	Node* tmp1 = head;
	Node* tmp2 = rhs.head->next;
	while (tmp2)
	{
		tmp1->next = new Node(tmp2->val);
		tmp1 = tmp1->next;
		tmp2 = tmp2->next;
	}
	return *this;
}

ForwardList& ForwardList::operator=(ForwardList&& rhs)
{
	if (this->head == rhs.head)
	{
		return *this;
	}
	head = new Node(rhs.head->val);
	Node* tmp1 = head;
	Node* tmp2 = rhs.head->next;
	while (tmp2)
	{
		tmp1->next = new Node(tmp2->val);
		tmp1 = tmp1->next;
		tmp2 = tmp2->next;
	}
	return *this;
}

bool ForwardList::operator==(ForwardList& other)
{
	if (head == nullptr || other.head == nullptr || (this->length() != other.length()))
	{
		return false;
	}
	Node* tmp1 = this->head;
	Node* tmp2 = other.head;
	while (tmp1->next)
	{
		if (tmp1->val != tmp2->val)
		{
			return false;
		}
		tmp1 = tmp1->next;
		tmp2 = tmp2->next;
	}
	return true;
}

bool ForwardList::operator!=(ForwardList& other)
{
	if (head == nullptr || other.head == nullptr || (this->length() != other.length()))
	{
		return false;
	}
	Node* tmp1 = this->head;
	Node* tmp2 = other.head;
	while (tmp1->next)
	{
		if (tmp1->val != tmp2->val)
		{
			return true;
		}
		tmp1 = tmp1->next;
		tmp2 = tmp2->next;
	}
	return false;
}

void ForwardList::sort()
{
	for (Node* i = head; i->next != nullptr; i = i->next)
	{
		for (Node* j = i->next; j != nullptr; j = j->next)
		{
			if (i->val > j->val)
			{
				std::swap(i->val, j->val);
			}
		}
	}
}

void ForwardList::merge(ForwardList other)
{
	if (head == nullptr || other.head == nullptr)
	{
		throw std::logic_error("List is empty");
	}
	this->sort();
	other.sort();
	Node* tmp = head;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	Node* tmp2 = other.head;
	while(tmp2) 
	{
		tmp->next = new Node(tmp2->val);
		tmp2 = tmp2->next;
		tmp = tmp->next;
	}
	sort();
}

const int& ForwardList::front() const
{
	if (empty())
	{
		throw std::logic_error("List is empty");
	}
	return head->val;
}

int ForwardList::begin() const
{
	return head->val;
}

int ForwardList::end() const
{
	Node* tmp = head;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	return tmp->val;
} 

void ForwardList::clear()
{
	while (head)
	{
		Node* tmp = head;
		head = head->next;
		delete tmp;
		tmp = nullptr;
	}
	if (head) 
	{
		delete head;
	}
	head = nullptr;
}

bool ForwardList::empty() const
{
	if (head == nullptr)
	{
		return true;
	}
	return false;
}

void ForwardList::push_front(int new_value)
{
	if (head == nullptr)
	{
		head = new Node(new_value);	
		return;
	}
	Node* tmp = new Node(new_value);
	tmp->next = head;
	head = tmp;
}

void ForwardList::pop_front()
{
	if (head == nullptr)
	{
		throw std::logic_error("List is empty");
	}
	Node* tmp = head;
	head = head->next;
	delete tmp;
	tmp = nullptr;
}

void ForwardList::insert_after(int index, int new_value)
{
	if (head == nullptr)
	{
		throw std::logic_error("List is empty you can't insert a value");
	}
	if (index < 0 || index >= length())
	{
		throw std::out_of_range("Invalid index!!!");
	}	
	if (!index) 
	{
		this->push_front(new_value);
		return;
	}
	Node* tmp = this->head->next;
	Node* prev = nullptr;
	for (int i = 0; i < index; ++i) 
	{
		if (i == index - 1) 
		{
			prev = tmp;
		}
		tmp = tmp->next;
	}
	prev->next = new Node(new_value);
	prev->next->next = tmp;
}

void ForwardList::erase_after(int index)
{
	if (index < 0 || index >= length() - 1)
	{
		throw std::out_of_range("Invalid index!!!");
	}	
	if (index == 0)
	{
		pop_front();
	}
	Node* tmp = head;
	for (int i = 0; i < index; ++i)
	{
		tmp = tmp->next;
	}
	Node* del = tmp->next;
	tmp->next = tmp->next->next;
	delete del;
	del = nullptr;
}

int ForwardList::length()
{
	Node* tmp = head;
	int count = 0;
	while (tmp)
	{
		++count;
		tmp = tmp->next;
	}
	return count;
}

void ForwardList::resize(int new_size)
{
	Node* tmp = head;
	int i = length();
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	while (i < new_size)
	{
		tmp->next = new Node(0);
		++i;
	}
	tmp->next = nullptr;
}

void ForwardList::swap(ForwardList& other)
{
	Node* tmp = head;
	head = other.head;
	other.head = tmp;
}

void ForwardList::reverse()
{
	if (empty())
	{
		throw std::logic_error("List is empty");
	}
	Node* curr = head;
	Node* prev = nullptr;
	while (curr)
	{
		Node* tmp = curr->next;
		curr->next = prev;
		prev = curr;
		curr = tmp;
	}
	head = prev;
}

void ForwardList::print()
{
	Node* tmp = head;
	while (tmp)
	{
		std::cout << tmp->val << " ";
		tmp = tmp->next;
	}
	if (head) 
	{
		std::cout << std::endl;
	}
}