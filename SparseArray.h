#pragma once

template<typename T1>
class SparseArray
{
public:
	//----------------------------------member functions
	T1& operator[](size_t index);
	T1& at(size_t index);
	const T1& at(size_t index)const;
	bool elementExistsAt(size_t index)const;


private:
	std::vector<Pair<T1, size_t>>pairs;// unordered vector storage 
	const T1* finder(size_t index)const;// helper functions for the member functions	
	T1* finder(size_t index);
};

template<typename T1>
const T1* SparseArray<T1>::finder(size_t index)const
{
	for (size_t i{}; i < pairs.size(); ++i)
	{
		if (pairs[i].second == index)
		{
			return &pairs[i].first;
		}
	}
	return nullptr;// return nothing if element not found 
}

template<typename T1>
T1* SparseArray<T1>::finder(size_t index)
{
	return const_cast<T1*>(std::as_const(*this).finder(index));
}


template<typename T1>
T1& SparseArray<T1>::operator[](size_t index)
{

	if (finder(index) != nullptr)
	{
		return *finder(index);
	}
	else
	{
		pairs.push_back({ T1{},index });
		return pairs.back().first;
	}

}

template<typename T1>
const T1& SparseArray<T1>::at(size_t index)const
{
	if (!finder(index))
	{
		throw std::out_of_range("\nElement does not exist\n");
	}
	else
	{
		std::cout << "\nIndex: " << index << "\n";
		return *finder(index);
	}
}


template<typename T1>
T1& SparseArray<T1>::at(size_t index)
{
	return const_cast<T1&>(std::as_const(*this).at(index));
}


template<typename T1>
bool SparseArray<T1>::elementExistsAt(size_t index)const
{
	if (finder(index))
	{
		return true;
	}
	else { return false; }
}
