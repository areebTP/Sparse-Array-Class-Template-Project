#pragma once

template <typename T>
class List
{
public:
		
	List(const std::vector<T>&);
	List() = default;
	List(const List&);
//---------------------------------MOVE Members
	List(List&&)noexcept;
	List& operator=(List)noexcept;
	void swap(List&)noexcept;
//---------------------------------Member Functions
	void push_back(const T&);
	void push_front(const T&);
	void clear()noexcept;
	bool empty()const noexcept;
	void pop_back();
	void pop_front();
	void printList()const;
	void RprintList()const;
	size_t size()const;

	const T& operator[](size_t index)const;
	T& operator[](size_t index);
	~List();

	class Iterator;
	Iterator getIT()const;
	Iterator getLastIT()const;


private:
	class Data
	{
	public:
		T data;// type of data stored 
		Data* m_next;
		Data* m_prev;

		Data(const T& dat)
			:data{ dat }, m_next{ nullptr }, m_prev{ nullptr }{}
		~Data() { delete m_next;  }
	};

	Data* m_head=nullptr;
	Data* m_tail=nullptr;
	size_t m_size{};

	

};

template<typename T>
class List<T>::Iterator
{
public:
	Data* getData();// getter
	Data* GetNextdata();
	Data* GetPrevdata();

private:
	Data* m_current;

	friend class List;
	explicit Iterator(Data* ptr)
		:m_current{ ptr } {}

};

//--------------------------------------------------------------Iterator design

template<typename T>
typename List<T>::Iterator List<T>::getIT() const { return List<T>::Iterator{ m_head }; }

template<typename T>
typename List<T>::Iterator List<T>::getLastIT() const { return List<T>::Iterator{ m_tail }; }

template<typename T>
typename List<T>::Data* List<T>::Iterator::getData()
{
	m_current = m_head;
	return m_current ? m_current : nullptr;
}

template<typename T>
typename List<T>::Data* List<T>::Iterator::GetNextdata()
{
	if (!m_current)                                 // If there's no current...
		return Firstdata();                         // ...return the 1st Box

	m_current = m_current->m_next;                  // Move to the next package

	return m_current ? m_current : nullptr;   // Return its box (or nullptr...).
}

		newNode->m_next = current;
		newNode->m_prev = current->m_prev;

		current->m_prev->m_next = newNode;
		current->m_prev = newNode;

		++m_size;
	}

	it.GetPrevdata();// move the iterator to the newly added object

	return it;
}

template<typename T>
typename List<T>::Data* List<T>::Iterator::GetPrevdata()
{
	if (!m_current)                                 // If there's no current...
		return Firstdata();                         // ...return the 1st Box

	m_current = m_current->m_prev;
	return m_current ? m_current : nullptr;   // Return its box (or nullptr...).
}


//-------------------------------------------------------------List functions

template<typename T>
List<T>::~List()
{
	clear();//delete manually 
}

template <typename T>
void List<T>::swap(List& b)noexcept
{
	std::swap(m_size, b.m_size);
	std::swap(m_head, b.m_head);
	std::swap(m_tail, b.m_tail);
}

template<typename T>
List<T>::List(const std::vector<T>& v)
{
	for (size_t i{}; i < v.size(); ++i)
	{
		push_back(v[i]);
	}
}

template<typename T>
List<T>::List(const List& list)
{
	for (auto it{ list.getIT() }; it.getData(); it.GetNextdata())
	{
		push_back(it.m_current->data);
	}
}


template<typename T>
const T& List<T>::operator[](size_t index)const
{
	if (index >= m_size)
	{
		throw std::out_of_range("\nOut of bound index.\n");
	}
	else
	{
		size_t count{};
		for (Data* temp{ m_head }; temp; temp = temp->m_next)
		{
			if (count == index)
			{
				return temp->data;
			}
			++count;
		}
	}

}

template<typename T>
T& List<T>::operator[](size_t index)
{
	return const_cast<T&>(std::as_const(*this)[index]);
}


template<typename T>
List<T>& List<T>::operator=(const List& list)
{
	List<T>copy{ list };// copy constructor called
	
	std::swap(m_size, copy.m_size);
	std::swap(m_head, copy.m_head);
	std::swap(m_tail, copy.m_tail);
	
	return *this;
}

template<typename T>
List<T>& List<T>::operator=(List list)noexcept//copy+move assigment operator
{
	std::vector<T>v2= v;//copy
	List<T>copy(v2);// copy constructor
//----------------------------------------swap
	std::swap(m_size, copy.m_size);
	std::swap(m_head, copy.m_head);
	std::swap(m_tail, copy.m_tail);

	return *this;
}

template<typename T>
void List<T>::push_back(const T& temp)
{
	Data* newTemp = (new Data(temp));

	if (m_tail)
	{
		m_tail->m_next = newTemp;
		newTemp->m_prev = m_tail;
	}

	else
	{
		m_head = newTemp;// for empty list make the head and tail both the new Data
	}

	m_tail = newTemp;
	++m_size;
}

template<typename T>
void List<T>::push_front(const T& temp)
{
	Data* newTemp = (new Data(temp));

	if (m_head)// check there is a head
	{
		newTemp->m_next = m_head;
		m_head->m_prev = newTemp;
	}

	else// list is empty
	{
		m_tail = newTemp;
	}

	m_head = newTemp;
	++m_size;
}

template<typename T>
bool List<T>::empty()const noexcept
{
	if (m_head)
	{
		return false;
	}

	return true;
}

template <typename T>
void List<T>::pop_front()
{
	if (!m_head)//if list is empty
	{
		throw std::runtime_error("\nEmpty list cannot be deleted\n");
	}

	//------------------------------------------------else

	if (m_head->m_next)// if there is a previous object
	{
		Data* oldHead{ m_head };
		m_head = m_head->m_next;// update the head
		m_head->m_prev = nullptr;

		oldHead->m_next = nullptr;// disconnect from the list
		delete oldHead;
	}
	else if (!m_head->m_next)// if head is the only object
	{
		delete m_head;
		m_tail = nullptr;
		m_head = nullptr;
	}
	--m_size;
}



template <typename T>
void List<T>::pop_back()
{
	if (!m_tail)//if list is empty
	{
		throw std::runtime_error("\nEmpty list cannot be deleted\n");
	}

	//------------------------------------------------else

	if (m_tail->m_prev)// if there is a previous object
	{
		Data* oldTail{ m_tail };
		m_tail = m_tail->m_prev;// update the tail
		m_tail->m_next = nullptr;

		oldTail->m_prev = nullptr;// disconnect from the list
		delete oldTail;
	}
	else if (!m_tail->m_prev)// if tail is the only object
	{
		delete m_tail;
		m_tail = nullptr;
		m_head = nullptr;
	}
	--m_size;
}

template<typename T>
void List<T>::clear()noexcept
{
	const size_t size{ m_size };
	for (size_t i{}; i < size; ++i)
	{
		pop_back();
	}

}

template<typename T>
size_t List<T>::size()const
{

	return m_size;
}

template<typename T>
void List<T>::printList()const
{
	const size_t perline{ 5 };// five words perline
	size_t counter2{};

	auto it{ getIT() };


	for (Data* dat = it.Firstdata(); dat; dat = it.GetNextdata())
	{
		std::cout << ' ' << it.m_current->data;
		if (!(++counter2 % perline)) std::cout << std::endl;
	}

	if (counter2 % perline)
	{
		std::cout << std::endl;
	}
}

template<typename T>
void List<T>::RprintList()const
{
	const size_t perline{ 5 };// five words perline
	size_t counter2{};

	for (auto it{ getLastIT() }; it.getData(); it.GetPrevdata())
	{
		std::cout << ' ' << it.m_current->data;
		if (!(++counter2 % perline)) std::cout << std::endl;
	}

	if (counter2 % perline)
	{
		std::cout << std::endl;
	}
}

