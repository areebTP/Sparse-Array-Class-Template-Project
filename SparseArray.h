#pragma once

template<typename T1>
class SparseArray
{
public:
//-----------------------------------Constructors
	SparseArray(size_t size);
	SparseArray(const SparseArray& array);
	SparseArray() = default;
//----------------------------------member functions
	T1& operator[](size_t index);
	T1& at(size_t index);
	const T1& at(size_t index)const;
	void swap(SparseArray& other)noexcept;
	SparseArray& operator=(const SparseArray& rhs);
	void insert(T1 element,int index);
	bool elementExistsAt(size_t index)const;
	

private:
	std::unique_ptr<T1[]>ptr1;
	std::vector<Pair<T1, size_t>>pairs;// unordered vector storage 
	size_t size{};
};


template<typename T1>
SparseArray<T1>::SparseArray(size_t size)
{
	this->size = size;
	ptr1 = std::unique_ptr<T1[]>(new T1[size]);

	T1 empty{};

	for (size_t i{}; i < size; ++i)
	{
		ptr1[i] = empty;//initialise all elements to null object
	}


}

template<typename T1>
SparseArray<T1>::SparseArray(const SparseArray& array)
{
	size = array.size;
	for (size_t i{}; i < size; ++i)
	{
		ptr1[i] = array.ptr1[i];
	}
}


template<typename T1>
T1& SparseArray<T1>::operator[](size_t index)
{
	for (size_t i{}; i < pairs.size(); ++i)
	{
		if (pairs[i].second == index)// found inside
		{
			return pairs[i].first;
		}
	}

	pairs.push_back({ T1{},index });
	return pairs.back().first;

	/*if (!ptr1[index])
	{
		std::unique_ptr<T1> ptr2 = std::unique_ptr<T1>(new T1);
		ptr1[index] = *ptr2;
		return ptr1[index];
	}
	else
	{
		return ptr1[index];
	}
	*/
}

template<typename T1>
const T1& SparseArray<T1>::at(size_t index)const 
{
	if (!ptr1[index])
	{
		throw std::out_of_range("Incorrect index.\n");
	}
	else
	{
		std::cout << "\nIndex: " << index << "\n";
		return ptr1[index];
	}
}


template<typename T1>
T1& SparseArray<T1>::at(size_t index)
{
	return const_cast<T1&>(std::as_const(*this).at(index));
}

template<typename T1>
void SparseArray<T1>::swap(SparseArray& other) noexcept
{
	std::swap(ptr1, other.ptr1);
	std::swap(size, other.size);
}


template<typename T1>
SparseArray<T1>& SparseArray<T1>::operator=(const SparseArray& array)
{
//-----------------------------copy and swap
	SparseArray<T1>copy{ array };
	swap(copy);
	return *this;

}

template<typename T1>
void SparseArray<T1>::insert(T1 element,int index)
{
	if (index >= size)
	{
		throw std::out_of_range("Incorrect index.\n");
	}

	ptr1[index] = element;
	
	auto pair1 = Pair<T1, int>(element, index);
	pairs.push_back(pair1);

}


template<typename T1>
bool SparseArray<T1>::elementExistsAt(size_t index)const
{
	if (ptr1[index])
	{
		return true;
	}
	else { return false; }
}
