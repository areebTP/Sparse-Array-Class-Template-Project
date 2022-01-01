#pragma once


template <typename T1,typename T2>
struct Pair
{
	Pair(const T1& p1, const T2& p2);
	Pair() = default;

	//std::partial_ordering operator<=>(const Pair& rhs) const = default;
	//auto operator<=>(const Pair& other) const = default;

	
	bool operator==(const Pair& rhs)const;
	bool operator<(const Pair& rhs)const;
	bool operator>(const Pair& rhs)const;
	bool operator>=(const Pair& rhs)const;
	bool operator<=(const Pair& rhs)const;
	bool operator!=(const Pair& rhs)const;
	

	T1 first;
	T2 second;
};

template <typename T1, typename T2>
Pair<T1, T2>::Pair(const T1& p1, const T2& p2)
	:first{ p1 }, second{ p2 }
{}


template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& output, const Pair<T1,T2>& pair)
{
	output << "Value: " << pair.first
		<< " Index: " << pair.second << "\n";
	return output;
}




template <typename T1, typename T2>
bool Pair<T1, T2>::operator==(const Pair& rhs)const
{
	return first == rhs.first
		&& second == rhs.second;
}

template <typename T1, typename T2>
bool Pair<T1, T2>::operator<(const Pair& rhs) const {
	return first < rhs.first ||
		first == rhs.first && second < rhs.second;
}

template <typename T1, typename T2>
bool Pair<T1, T2>::operator>(const Pair& rhs) const {
	return first > rhs.first ||
		first == rhs.first && second > rhs.second;
}

template <typename T1, typename T2>
bool Pair<T1, T2>::operator>=(const Pair& rhs) const {
	return first >= rhs.first ||
		first == rhs.first && second >= rhs.second;
}

template <typename T1, typename T2>
bool Pair<T1, T2>::operator<=(const Pair& rhs) const {
	return first <= rhs.first ||
		first == rhs.first && second <= rhs.second;
}

template <typename T1, typename T2>
bool Pair<T1, T2>::operator!=(const Pair& rhs)const
{
	return first != rhs.first ||
		first == rhs.first && second != rhs.second;
}



