#ifndef VECTOR1_H
#define VECTOR1_H
#include <cstddef> //size_t
#include <utility> //move()
/**
 * @brief a vector class
*/
template <typename T>
class vector
{
	size_t m_size;
	size_t m_capacity;
	T *arr; //pointer to the first element
public:
	using value_type = T;
	using reference = T & ;
	using const_reference = const T &;
	using iterator = T * ;
	using const_iterator = const T *;
	using size_type = size_t;
private:
	void enough_capacity();
public:
	//constructor
	vector() : m_size(0U), m_capacity(0U), arr(nullptr) {}
	explicit vector(size_type n) : m_size(n), m_capacity(n), arr(n ? new T[n] : nullptr) {}
	vector(const vector& v) = delete; //this function is useless and dangerous for now
	vector(vector&& v) : m_size(v.m_size), m_capacity(v.m_capacity), arr(v.arr) { v.arr = nullptr; }
	//destructor
	~vector() { delete[]arr; }
	//operator=
	vector &operator=(const vector &v);

	//iterators
	iterator begin() { return arr; }
	const_iterator begin() const { return arr; }
	iterator end() { return arr + m_size; }
	const_iterator end() const { return arr + m_size; }
	const_iterator cbegin() const { return arr; }
	const_iterator cend() const { return arr + m_size; }

	//capacity
	size_type size() const { return m_size; }
	void resize(size_type n);
    void resize(size_type n, T value);
	size_type capacity() const { return m_capacity; }
	bool empty() const { return !m_size; }
	void reserve(size_type n);

	//access to the element
	reference operator[] (size_type n) { return arr[n]; }
	const_reference operator[] (size_type n) const { return arr[n]; }
	reference front() { return arr[0U]; }
	const_reference front() const { return arr[0U]; }
	reference back() { return arr[m_size - 1U]; }
	const_reference back() const { return arr[m_size - 1U]; }

	//modyfying
	void push_back(const value_type &t);
	void push_back(value_type&& val);
	void pop_back() { arr[--m_size].~T(); }
	iterator erase(const_iterator position);
	void clear();
};

template<typename T>
inline void vector<T>::enough_capacity()
{
	if (m_size >= m_capacity) {

		//Visual-like
		if (m_capacity > 3)
			reserve(m_capacity / 2U * 3U);
		else //m_capacity == 0/1/2/3
			reserve(m_capacity + 1U);

		//GCC-like
		/*if (m_capacity)
			reserve(2U * m_capacity);
		else
			reserve(1U);*/
	}
}

template<typename T>
inline vector<T>& vector<T>::operator=(const vector<T>& v)
{
	if (this != &v) {
		~vector();
		m_size = v.m_size;
		m_capacity = v.m_capacity;
		arr = new T[m_capacity];
		for (size_t i = 0U; i < m_size; ++i)
			arr[i] = v.arr[i];
	}
	return *this;
}

template<typename T>
inline void vector<T>::resize(size_type n)
{
	if (n < m_size) {
		while (n < m_size)
			pop_back();
		return;
	}
	if (n > m_capacity)
			reserve(n);
	m_size = n;

	/*while (n > m_size) //initialize?
	{
		arr[m_size++] = {};
	}*/

}
template<typename T>
inline void vector<T>::resize(size_type n, T value)
{
	if (n < m_size) {
		while (n < m_size)
			pop_back();
		return;
	}
	if (n > m_capacity)
			reserve(n);
	m_size = n;
    
    for(int i = 0; i < n; i++)
        arr[i] = value;

	/*while (n > m_size) //initialize?
	{
		arr[m_size++] = {};
	}*/

}

template<typename T>
inline void vector<T>::reserve(size_type n)
{
	if (n > m_capacity) {
		T *newbuff = new T[n];
		for (size_t i = 0U; i < m_size; ++i)
			newbuff[i] = std::move(arr[i]);
		delete[]arr;
		arr = newbuff;
		m_capacity = n;
	}
}

template<typename T>
inline void vector<T>::push_back(const value_type &t)
{
	enough_capacity();
	arr[m_size++] = t;
}

template<typename T>
inline void vector<T>::push_back(value_type && val)
{
	enough_capacity();
	arr[m_size++] = std::move(val);
}

template<typename T>
inline typename vector<T>::iterator vector<T>::erase(const_iterator position)
{
	position->~T();

	//pointer arithmetic
	for (auto i = const_cast<iterator>(position); i < end() - 1; ++i)
		(*i) = std::move(*(i + 1));

	//second option
	/*for (size_t i = position - begin(); i < m_size; ++i)
		arr[i] = std::move(arr[i + 1]);*/

	--m_size;

	return const_cast<iterator>(position);
}

template<typename T>
inline void vector<T>::clear()
{
	for (auto &i : (*this))
		i.~T();
	m_size = 0U;
}

#endif // !VECTOR1_H
