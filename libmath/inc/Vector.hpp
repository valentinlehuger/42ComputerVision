#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <vector>
#include <iostream>
#include <math.h>
#include <cmath>
#include <exception>

namespace cv42
{
template <typename T>
class Matrix;

template <typename T>
class Vector{
	public:
		Vector<T>(void);
		Vector<T>(int n);
		Vector<T>(std::vector<T> v);
		~Vector<T>(void);
		Vector<T>(Vector<T> const & rhs);

		Vector<T> &		operator=(Vector<T> const & rhs);

		T &				operator[](int i);
		const T &		operator[](int i) const;

		Vector<T>		operator-(Vector<T> const & rhs) const;
		Vector<T>		operator^(T const & rhs) const;

		int				getSize(void) const;
		std::vector<T>	getContainer(void) const;

		T				norm(void) const;
		T				mean(void) const;
		Vector<T>		normalization(void) const;
		Vector<T>		abs(void) const;
		Matrix<T>		householder(void) const;
		T				sum(void) const;

		typename std::vector<T>::const_iterator begin(void) const;
		typename std::vector<T>::const_iterator end(void) const;

	protected:
		int				_size;
		std::vector<T>	_container;
};

template <typename T>
std::ostream & operator<<(std::ostream & o, Vector<T> const & rhs) {
	typename std::vector<T>::const_iterator it;
	o << "[ ";
	for (it = rhs.begin() ; it != rhs.end() ; it++){
		o << *it << " " ;
	}
	o << "]";
	return o;
}

template <typename T>
Vector<T>::Vector(void):_size(1),_container(std::vector<T>(1)) {
		return ;
}

template <typename T>
Vector<T>::Vector(int n):_size(n),_container(std::vector<T>(n, 0)) {
		return ;
}

template <typename T>
Vector<T>::Vector(std::vector<T> v):_size(v.size()),_container(v) {
		return ;
}

template <typename T>
Vector<T>::~Vector(void) {
		return ;
}

template <typename T>
Vector<T>::Vector(Vector<T> const & rhs){
		*this = rhs;
}

template <typename T>
Vector<T> & Vector<T>::operator=(Vector<T> const & rhs) {
		this->_container = rhs.getContainer();
		this->_size = rhs.getSize();
		return *this;
}

template <typename T>
T &			Vector<T>::operator[](int i) {
		return this->_container[i];
}

template <typename T>
const T &	Vector<T>::operator[](int i) const {
		return this->_container[i];
}

template <typename T>
Vector<T>	Vector<T>::operator-(Vector<T> const & rhs) const {
		if (this->getSize() != rhs.getSize())
			throw std::exception();
		Vector<T>	result(this->getSize());

		for (int i = 0; i < this->getSize(); ++i)
			result[i] = (*this)[i] - rhs[i];
		return (result);
}

template <typename T>
Vector<T>	Vector<T>::operator^(T const & rhs) const {
	Vector<T>	result(this->getSize());

		for (int i = 0; i < this->getSize(); ++i)
			result[i] = pow((*this)[i], rhs);
		return (result);
}

template <typename T>
int			Vector<T>::getSize(void) const {
		return this->_size ;
}

template <typename T>
std::vector<T>	Vector<T>::getContainer(void) const {
		return this->_container;
}

template <typename T>
typename std::vector<T>::const_iterator Vector<T>::begin(void) const {
		return this->_container.begin();
}

template <typename T>
typename std::vector<T>::const_iterator Vector<T>::end(void) const {
		return this->_container.end();
}

template <typename T>
T Vector<T>::norm(void) const {
	typename std::vector<T>::const_iterator it;
	T ttl_square = 0;
	for (it = _container.begin() ; it != _container.end() ; ++it){
		ttl_square += *it * *it;
	}
	return sqrt(ttl_square);
}

template <typename T>
Vector<T>	Vector<T>::normalization(void) const{
	typename std::vector<T>::iterator it;
	Vector<T> v(*this);
	T n(this->norm());

	if (n== 0 || v.getSize() == 1){
		return v;
	}
	for (int i = 0 ; i < v.getSize(); i++) {
		v[i] = v[i] / n;
	}
	return v;
}

template <typename T>
Vector<T>	Vector<T>::abs(void) const {
		Vector<T>	result(this->getSize());

		for (int i = 0; i < this->getSize(); ++i)
			result[i] = ((*this)[i] > 0 ? (*this)[i] : -(*this)[i]);
		return result;
}

template <typename T>
T Vector<T>::mean(void) const {
	typename std::vector<T>::const_iterator it;
	T ret = 0;
	for (it = _container.begin() ; it != _container.end() ; ++it){
		ret += *it;
	}
	return ret / static_cast<float>(this->getSize());
}

template <typename T>
Matrix<T>	Vector<T>::householder(void) const {
		T				norm = this->norm();
		T				beta;
		cv42::Matrix<T>	u({*this});
		cv42::Matrix<T>	v({*this});
		cv42::Matrix<T>	vtv;
		cv42::Matrix<T>	H = cv42::Matrix<T>::identity(this->getSize());

		if ((this[0][0] < 0 && norm > 0) || (this[0][0] > 0 && norm < 0))
			norm = 0 - norm;
		u = u + norm;
		v = v / u[0][0];
		v[0][0] = 1;
		vtv = v.transpose() * v;
		beta = 2 / (v * v.transpose())[0][0];
		H = H - vtv.mul(beta);
		return H;
}

template <typename T>
T			Vector<T>::sum(void) const {
	typename std::vector<T>::const_iterator it;
	T ret = 0;

	for (it = _container.begin() ; it != _container.end() ; ++it){
		ret += *it;
	}
	return (ret);
}
}

#endif
