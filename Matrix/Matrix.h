#pragma once
#include <stdexcept>
#include <vector>
#include <functional>
#include <thread>
#include <iostream>

template <class T>
class _matrix_iterator {
private:
	T* ptr;
public:
	_matrix_iterator operator++();
	_matrix_iterator operator--();
	_matrix_iterator operator++(int);
	_matrix_iterator operator--(int);
	T& operator*();
	bool operator==(const _matrix_iterator& rhs);
	bool operator!=(const _matrix_iterator& rhs);
	_matrix_iterator(T* pointer);
};


template <class T>
class _matrix_reversed_iterator {
private:
	T* ptr;
public:
	_matrix_reversed_iterator operator++();
	_matrix_reversed_iterator operator--();
	_matrix_reversed_iterator operator++(int);
	_matrix_reversed_iterator operator--(int);
	T& operator*();
	bool operator==(const _matrix_reversed_iterator& rhs);
	bool operator!=(const _matrix_reversed_iterator& rhs);
	_matrix_reversed_iterator(T* pointer);
};

template <class T>
class Matrix
{
private:
	T* arr;
	int n;
	int m;
	class _Help {
	private:
		T* harr;
		int hn;
		int hm;
		int hi;
	public:
		_Help(T* aarr, int nn, int mm, int ii) {
			harr = aarr;
			hn = nn;
			hm = mm;
			hi = ii;
		}
		T& operator[](int j) {
			if (j < 0 || j >= hm) throw std::runtime_error("invalid second index");
			return harr[hm * hi + j];
		}
		const T& operator[](int j) const {
			if (j < 0 || j >= m) throw std::runtime_error("invalid second index");
			return harr[hm * hi + j];
		}
	};
public:
	_Help operator[](int i) {
		if (i < 0 || i >= n) throw std::runtime_error("invalid first index");
		return _Help(arr, n, m, i);
	}
	const _Help operator[](int i) const {
		if (i < 0 || i >= n) throw std::runtime_error("invalid first index");
		return _Help(arr, n, m, i);
	}
	/*!
	\brief Matrix resizer
	\details All the data will be deleted
	\param[in] newheight New height of matrix
	\param[in] newwidth New width of matrix
	\throw invalid_argument In case of negative parameters
	*/
	Matrix<T>& resize(int newheight, int newwidth);
	/*!
	\brief Move operator assignment
	\details Moves one object's fields to another.
	\param[in] rhs Object to move
	\code
	*/
	Matrix<T>& operator=(Matrix&& rhs) noexcept;
	/*!
	\brief Copy operator assignment
	\details Copies one object's fields to another.
	\param[in] rhs Object to copy
	*/
	Matrix<T>& operator=(const Matrix& rhs);
	/*!
	\brief Simple height getter
	\return The height of matrix
	*/
	int height() const;
	/*!
	\brief Simple width getter
	\return The width of matrix
	*/
	int width() const;
	/*!
	\brief Basic class constructor
	\param[in] height Height of matrix
	\param[in] width Width of matrix
	\throw invalid_argument In case of negative parameters
	*/
	Matrix(int height = 0, int width = 0);
	/*!
	\brief Copy class constructor
	\details Copies one object to another.
	\param[in] rhs Object to copy
	*/
	Matrix(const Matrix& rhs);
	/*!
	\brief Move class constructor
	\details Moves one object's fields to another.
	\param[in] rhs Object to move
	*/
	Matrix(Matrix&& rhs) noexcept;
	/*!
	\brief Basic class destructer
	*/
	~Matrix();
	/*!
	\brief Begin iterator
	\return iterator to the first element
	*/
	_matrix_iterator<T> begin() const;
	/*!
	\brief End iterator
	\return iterator to the last element not in matrix
	*/
	_matrix_iterator<T> end() const;
	/*!
	\brief Rbegin iterator
	\return iterator to the last element
	*/
	_matrix_reversed_iterator<T> rbegin() const;
	/*!
	\brief Rend iterator
	\return iterator to the first element not in matrix
	*/
	_matrix_reversed_iterator<T> rend() const;
	/*!
	\brief Checking for equality
	\return true if objects are equal, flase in opposite case
	*/
	bool operator==(const Matrix& rhs) const;
	/*!
	\brief Checking for non-equality
	\return true if objects are not equal, flase in opposite case
	*/
	bool operator!=(const Matrix& rhs) const;

	template <typename R>
	std::vector<R> calc(R r0, std::function<R(R, const T&)>) const;

	template <typename R>
	std::vector<R> calcnothreads(R r0, std::function<R(R, const T&)>) const;
};



template<class T>
inline Matrix<T>& Matrix<T>::resize(int newheight, int newwidth)
{
	delete[] arr;
	n = newheight;
	m = newwidth;
	arr = new T[n * m];
	return *this;
}

template<class T>
inline Matrix<T>& Matrix<T>::operator=(Matrix&& rhs) noexcept
{
	if (&rhs == this) return *this;
	n = rhs.n;
	m = rhs.m;
	delete[] arr;
	arr = rhs.arr;
	rhs.arr = 0;
	rhs.n = 0;
	rhs.m = 0;
	return *this;
}

template<class T>
inline Matrix<T>& Matrix<T>::operator=(const Matrix& rhs)
{
	if (&rhs == this) return *this;
	n = rhs.n;
	m = rhs.m;
	delete[] arr;
	arr = new T[n * m];
	std::copy(rhs.arr, rhs.arr + n * m, arr);
	return *this;
}

template<class T>
inline Matrix<T>::Matrix(const Matrix& rhs)
{
	n = rhs.n;
	m = rhs.m;
	arr = new T[n * m];
	std::copy(rhs.arr, rhs.arr + n * m, arr);
}

template<class T>
inline Matrix<T>::Matrix(Matrix&& rhs) noexcept
{
	n = rhs.n;
	m = rhs.m;
	arr = rhs.arr;
	rhs.arr = 0;
	rhs.n = 0;
	rhs.m = 0;
}

template<class T>
inline int Matrix<T>::height() const
{
	return n;
}

template<class T>
inline int Matrix<T>::width() const
{
	return m;
}

template<class T>
inline Matrix<T>::Matrix(int height, int width)
{
	n = height;
	m = width;
	arr = new T[n * m];
}

template<class T>
inline Matrix<T>::~Matrix()
{
	delete[] arr;
}

template<class T>
inline _matrix_iterator<T> Matrix<T>::begin() const
{
	return _matrix_iterator<T>(arr);
}

template<class T>
inline _matrix_iterator<T> Matrix<T>::end() const
{
	return _matrix_iterator<T>(arr + n * m);
}

template<class T>
inline _matrix_reversed_iterator<T> Matrix<T>::rbegin() const
{
	return _matrix_reversed_iterator<T>(arr + n * m - 1);
}

template<class T>
inline _matrix_reversed_iterator<T> Matrix<T>::rend() const
{
	return _matrix_reversed_iterator<T>(arr - 1);
}

template<class T>
inline bool Matrix<T>::operator==(const Matrix& rhs) const
{
	if (n != rhs.n || m != rhs.m) return 0;
	int z = n * m;
	for (int i = 0; i < z; i++) {
		if (arr[i] != rhs.arr[i]) return 0;
	}
	return 1;
}

template<class T>
inline bool Matrix<T>::operator!=(const Matrix& rhs) const
{
	return !(*this == rhs);
}

template<class T>
inline _matrix_iterator<T> _matrix_iterator<T>::operator++()
{
	ptr++;
	return *this;
}

template<class T>
inline _matrix_iterator<T> _matrix_iterator<T>::operator--()
{
	ptr--;
	return *this;
}

template<class T>
inline _matrix_iterator<T> _matrix_iterator<T>::operator++(int)
{
	T* temp = ptr;
	ptr++;
	return _matrix_iterator<T>(temp);
}

template<class T>
inline _matrix_iterator<T> _matrix_iterator<T>::operator--(int)
{
	T* temp = ptr;
	ptr--;
	return _matrix_iterator<T>(temp);
}

template<class T>
inline T& _matrix_iterator<T>::operator*()
{
	return *ptr;
}

template<class T>
inline bool _matrix_iterator<T>::operator==(const _matrix_iterator& rhs)
{
	return ptr == rhs.ptr;
}

template<class T>
inline bool _matrix_iterator<T>::operator!=(const _matrix_iterator& rhs)
{
	return ptr != rhs.ptr;
}

template<class T>
inline _matrix_iterator<T>::_matrix_iterator(T* pointer)
{
	ptr = pointer;
}

template<class T>
inline _matrix_reversed_iterator<T> _matrix_reversed_iterator<T>::operator++()
{
	ptr--;
	return *this;
}

template<class T>
inline _matrix_reversed_iterator<T> _matrix_reversed_iterator<T>::operator--()
{
	ptr++;
	return *this;
}

template<class T>
inline _matrix_reversed_iterator<T> _matrix_reversed_iterator<T>::operator++(int)
{
	T* temp = ptr;
	ptr--;
	return _matrix_reversed_iterator<T>(temp);
}

template<class T>
inline _matrix_reversed_iterator<T> _matrix_reversed_iterator<T>::operator--(int)
{
	T* temp = ptr;
	ptr++;
	return _matrix_reversed_iterator<T>(temp);
}

template<class T>
inline T& _matrix_reversed_iterator<T>::operator*()
{
	return *ptr;
}

template<class T>
inline bool _matrix_reversed_iterator<T>::operator==(const _matrix_reversed_iterator& rhs)
{
	return ptr == rhs.ptr;
}

template<class T>
inline bool _matrix_reversed_iterator<T>::operator!=(const _matrix_reversed_iterator& rhs)
{
	return ptr != rhs.ptr;
}

template<class T>
inline _matrix_reversed_iterator<T>::_matrix_reversed_iterator(T* pointer)
{
	ptr = pointer;
}


template<class R, class T>
void countstring(R r0, T* ptr, int m, std::function<R(R, const T&)>func, int i, std::vector<R>& arr) {
	for (int j = 0; j < m; j++, ptr++) {
		r0 = func(r0, *ptr);
	}
	arr[i] = r0;
}

template<class R, class T>
void countstringthread(R r0, T* ptr, int m, std::function<R(R, const T&)>func, int imin, int imax, std::vector<R>& arr) {
	R r1 = r0;
	for (int i = imin; i < imax; i++) {
		for (int j = 0; j < m; j++, ptr++) {
			r0 = func(r0, *ptr);
		}
		arr[i] = r0;
		r0 = r1;
	}
}

template<class T>
template<class R>
inline std::vector<R> Matrix<T>::calc(R r0, std::function<R(R, const T&)>func) const
{
	int maxthreads = std::thread::hardware_concurrency();
	std::vector<std::thread> threads(maxthreads);
	std::vector<R> ret(n);
	if (n <= maxthreads) {
		for (int i = 0; i < n; i++) {
			threads[i] = std::thread
			(countstring<R, T>, r0, arr + i * m, m, func, i, std::ref(ret));
		}
		for (auto& now : threads) {
			if (now.joinable()) now.join();
		}
		return ret;
	}
	int maxlines = n / maxthreads, istart = 0;
	for (int i = 1; i < maxthreads; i++) {
		threads[i] = std::thread
		(countstringthread<R, T>, r0, arr + istart * m, m, func, istart, istart + maxlines, std::ref(ret));
		istart += maxlines;
	}
	threads[0] = std::thread
	(countstringthread<R, T>, r0, arr + istart * m, m, func, istart, n, std::ref(ret));
	for (auto& now : threads) {
		if (now.joinable()) now.join();
	}
	return ret;
}

template<class T>
template<typename R>
inline std::vector<R> Matrix<T>::calcnothreads(R r0, std::function<R(R, const T&)>func) const
{
	std::vector<R> ret(n);
	for (int i = 0; i < n; i++) {
		countstring<R, T>(r0, arr + i * m, m, func, i, std::ref(ret));
	}
	return ret;
}
