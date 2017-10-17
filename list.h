#ifndef __LINKED_LIST__
#define __LINKED_LIST__

#include <iostream>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <stack>

template <typename T>
class linkedList
{
private:

	class node
	{
	public:
		node* next;
		T data;
		node() : next(nullptr) {}
		
		explicit node(const T& data_arg) : next(nullptr), data(data_arg) {}

		~node() {}
	};

	void removeNext(node *&head)
	{
		if(!head->next->next)
		{
			delete head->next;
			head->next = nullptr;
			return;			
		}
		node *destroy = head->next;
		head->next = destroy->next;
		delete destroy;
	}

	bool isSortedPrv(const std::function<bool (const T&, const T&)>& binaryOp) const
	{
		if(head && head->next)
		{
			register node* curr = head;
			while(curr->next)
			{
				if(binaryOp(curr->data, curr->next->data))
					return false;
				curr = curr->next;
			}
			return true;
		}
		else return true;
	}

	void copy(const linkedList<T>& rhs)
	{
		register node* curr = rhs.head;
		while(curr)
		{
			this->insert(curr->data);
			curr = curr->next;
		}
		size_list = rhs.size_list;
	}

	node* head;
	size_t size_list;

public:

	// ========================== CLASS ITERATOR ==========================

	class listIterator
	{
	private:
		node* curr;
		node* prev;

		inline void getNext()
		{
			prev = curr;
			curr = curr->next;
		}

	public:
		listIterator(const node* head_arg) : curr(const_cast<node*>(head_arg)), prev(nullptr) {}

		listIterator& operator++()
		{
			getNext();
			return *this;
		}

		listIterator& operator++(int)
		{
			getNext();
			return *this;
		}

		inline T& operator*()
		{
			return curr->data;
		}

		inline bool operator!= (void* rhs)
		{
			return curr != rhs;
		}

		inline bool operator== (const linkedList<T>::listIterator it)
		{
			return this->curr == it.curr;
		}

		void deleteThis()
		{
			node* save = curr;
			prev->next = curr->next;
			curr = curr->next;
			delete save;
		}
	};

	inline node* begin()
	{
		return head;
	}

	inline void* end()
	{
		return nullptr;
	}


	// ========================== CLASS ITERATOR ==========================


	linkedList() : head(nullptr), size_list(0) {}

	linkedList(const linkedList<T>& rhs)
	{
		head = nullptr;
		size_list = 0;
		copy(rhs);
	}

	linkedList<T>& operator=(const linkedList<T>& rhs)
	{
		if(this != &rhs)
		{
			if(head)
			{
				this->clear();
				size_list = 0;
			}
			copy(rhs);
		}
		return *this;
	}

	void insert(const T& data_arg)
	{
		if(!head)
		{
			head = new node(data_arg);
			++size_list;
			return;
		}
		register node *tmp = head;
		while(tmp->next)
			tmp = tmp->next;
		tmp->next = new node(data_arg);
		++size_list;
	}

	void insertFront(const T& data_arg)
	{
		if(!head)
		{
			head = new node(data_arg);
			++size_list;
			return;
		}
		node *newHead = new node(data_arg);
		newHead->next = head;
		head = newHead;
		++size_list;
	}


	void remove(const T& pat)
	{
		if(head)
		{
			while(head && head->data == pat)
			{
				node *newHead = head->next;
				delete head;
				head = newHead;
				--size_list;
			}
			register node *tmp = head;
			if(head)
			{
				while(tmp->next)
				{
					if(tmp->next->data == pat)
					{
						removeNext(tmp);
						--size_list;
					}
					if(tmp->next)
						tmp = tmp->next;
				}
			}
		}
	}

	void removeCurr(linkedList<T>::listIterator it)
	{
		it.deleteThis();
	}

	void clear()
	{
		register node *destroy = head;
		register node *next;
		while(destroy)
		{
			next = destroy->next;
			delete destroy;
			destroy = next;
		}
		head = nullptr;
		size_list = 0 ;
	}

	linkedList<T>::listIterator find(const T& pat)
	{
		linkedList<T>::listIterator it = begin();
		while(it != end())
		{
			if(*it == pat)
				return it;
			it++;
		}
		return it;
	}

	size_t inline size() const
	{
		return size_list;
	}

	unsigned int count(const T& pat) const
	{
		register node *tmp = head;
		register unsigned int res = 0;
		while(tmp != nullptr)
		{
			if(tmp->data == pat)
				++res;
			tmp = tmp->next;
		}
		return res;
	}

	void range(const int x, const int y)
	{
		for(register int i = x ; i <= y ; ++i)
		{
			this->insert(i);
		}
	}

	void append(const linkedList<T>& l2)
	{
		register node* tmp = l2.head;
		while(tmp != nullptr)
		{
			this->insert(tmp->data);
			tmp = tmp->next;
		}
	}

	void concat(const linkedList<T>& l1, const linkedList<T>& l2)
	{
		register node* tmp = l1.head;
		while(tmp != nullptr)
		{
			this->insert(tmp->data);
			tmp = tmp->next;
		}
		tmp = l2.head;
		while(tmp != nullptr)
		{
			this->insert(tmp->data);
			tmp = tmp->next;
		}
	}

	void map(const std::function<T (const T&)>& unaryOp)
	{
		register node* curr = head;
		while(curr != nullptr)
		{
			curr->data = unaryOp(curr->data);
			curr = curr->next;
		}
	}

	bool duplicates() const
	{
		std::unordered_map<T, unsigned int> counterMap;
		register node* curr = head;
		while(curr)
		{
			typename std::unordered_map<T, unsigned int>::iterator it(counterMap.find(curr->data));
			if(it != counterMap.end())
			{
				if(it->second >= 1)
					return true;
				else it->second++;
			}
			else
			{
				counterMap[curr->data] = 1;
			}
			curr = curr->next;
		}
		return false;
	}

	void removeDuplicates()
	{
		if(head)
		{
			std::unordered_set<T> uniques;
			register node* curr = head;
			while(curr)
			{
				uniques.insert(curr->data);
				curr = curr->next;
			}
			this->clear();
			for(auto it : uniques)
				this->insert(it);
		}
	}

	bool isSorted() const
	{
		return (isSortedPrv([](const T &x, const T &y)->bool { return (x > y); }) ||
		 		isSortedPrv([](const T &x, const T &y)->bool { return (x < y); }));
	}

	bool palindrome() const
	{
		register node* curr = head;
		std::stack<node*> st;
		while(curr){
			st.push(curr);
			curr = curr->next;
		}
		curr = head;
		for(int i = 0 ; i < size_list / 2 ; ++i)
		{
			if(curr->data != st.top()->data)
				return false;
			st.pop();
			curr = curr->next;
		}
		return true;
	}

	void reverse()
	{
		if(head)
		{
			std::stack<node*> st;
			register node* curr = head;
			while(curr)
			{
				node* tmp = curr;
				st.push(tmp);
				curr = curr->next;
			}
			curr = head;
			for(int i = 0 ; i < size_list / 2 ; ++i)
			{
				std::swap(st.top()->data, curr->data);
				curr = curr->next;
				st.pop();
			}			
		}
	}

	void printAll() const
	{
		register node *tmp = head;
		while(tmp != nullptr)
		{
			std::cout << tmp->data << " ";
			tmp = tmp->next;
		}
		std::cout << std::endl;	
	}

	~linkedList()
	{
		if(head)
		{
			this->clear();
		}
	}
};


#endif