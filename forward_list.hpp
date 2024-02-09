#include "forward_list.h"

template <typename T>
ForwardList<T>::ForwardList() : head{nullptr}, m_size{} {}

template <typename T>
ForwardList<T>::~ForwardList() 
{
	if (head) 
	{
		clear();
	}
}

template <typename T>
ForwardList<T>::ForwardList(const ForwardList& other)
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

template <typename T>
ForwardList<T>::ForwardList(ForwardList&& other)
{
	head = other.head;
	m_size = other.m_size;
	other.head = nullptr;
	other.m_size = 0;
}

template <typename T>
ForwardList<T>& ForwardList<T>::operator=(const ForwardList& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}
	clear();
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

template <typename T>
ForwardList<T>& ForwardList<T>::operator=(ForwardList&& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}
	clear();
	head = rhs.head;
    m_size = rhs.m_size;
    rhs.head = nullptr;
    rhs.m_size = 0;
	return *this;
}

template <typename T>
bool ForwardList<T>::operator==(ForwardList& other)
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

template <typename T>
bool ForwardList<T>::operator!=(ForwardList& other)
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

template <typename T>
void ForwardList<T>::sort()
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

template <typename T>
void ForwardList<T>::merge(ForwardList<T> other)
{
	ForwardList<T> merged_lists;
	Node* current_this = head;
	Node* current_oth = other.head;
	while (current_this != nullptr && current_oth != nullptr)
	{
		if (current_this->val <= current_oth->val)
		{
			merged_lists.push_front(current_this->val);
			current_this = current_this->next;
		}
		else
		{	
			merged_lists.push_front(current_oth->val);
			current_oth = current_oth->next;
		}
	}
	while (current_this != nullptr)
	{
		merged_lists.push_front(current_this->val);
		current_this = current_this->next;
	}
	while (current_oth != nullptr)
	{
		merged_lists.push_front(current_oth->val);
		current_oth = current_oth->next;
	}

	clear();
	head = merged_lists.head;
	m_size = merged_lists.m_size;

	merged_lists.head = nullptr;
	merged_lists.m_size = 0;
}

template <typename T>
const T& ForwardList<T>::front() const
{
	if (empty())
	{
		throw std::logic_error("List is empty");
	}
	return head->val;
}

template <typename T>
T ForwardList<T>::begin() const
{
	return head->val;
}

template <typename T>
T ForwardList<T>::end() const
{
	Node* tmp = head;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	return tmp->val;
} 

template <typename T>
void ForwardList<T>::clear()
{
	if (head == nullptr)
	{
		std::cout << "List is empty" << std::endl;
		return;
	}
	while (head)
	{
		Node* tmp = head;
		head = head->next;
		delete tmp;
		tmp = nullptr;
	}
	head = nullptr;
}

template <typename T>
bool ForwardList<T>::empty() const
{
	return (head == nullptr);
}

template <typename T>
void ForwardList<T>::push_front(T new_value)
{
	if (head == nullptr)
	{
		head = new Node(new_value);	
		return;
	}
	Node* tmp = new Node(new_value);
	tmp->next = head;
	head = tmp;
	m_size++;
}

template <typename T>
void ForwardList<T>::pop_front()
{
	if (head == nullptr)
	{
		throw std::logic_error("List is empty");
	}
	Node* tmp = head;
	head = head->next;
	delete tmp;
	tmp = nullptr;
	m_size--;
}

template <typename T>
void ForwardList<T>::insert_after(int index, T new_value)
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
	m_size++;
}

template <typename T>
void ForwardList<T>::erase_after(int index)
{
	if (head == nullptr)
	{
		throw std::logic_error("List is empty you can't erase a value");
	}
	if (index < 0 || index >= length() - 1)
	{
		throw std::out_of_range("Invalid index!!!");
	}	
	if (index == 0)
	{
		pop_front();
		return;
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
	m_size--;
}

template <typename T>
int ForwardList<T>::length()
{
	if (head == nullptr)
	{
		return 0;
	}
	Node* tmp = head;
	int count = 0;
	while (tmp)
	{
		++count;
		tmp = tmp->next;
	}
	return count;
}

template <typename T>
void ForwardList<T>::resize(int new_size)
{
	if (new_size < 0)
    {
        throw std::invalid_argument("New size cannot be negative.");
    }
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

template <typename T>
void ForwardList<T>::swap(ForwardList<T>& other)
{
	Node* tmp_head = head;
	head = other.head;
	other.head = tmp_head;

	int tmp_size = m_size;
	m_size = other.m_size;
	other.m_size = tmp_size;
}

template <typename T>
void ForwardList<T>::reverse()
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

template <typename T>
void ForwardList<T>::print()
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
