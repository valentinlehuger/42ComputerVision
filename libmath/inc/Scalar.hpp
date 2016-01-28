#ifndef SCALAR_HPP
#define SCALAR_HPP

#include <iostream>
#include <cmath>

namespace cv42 {
	
	template <typename T>
	class Scalar
	{
	protected:
		T			_value;

	public:
		Scalar<T>(void);
		Scalar<T>(T n);
		~Scalar<T>(void);
		Scalar<T>(Scalar<T> const & rhs);

		Scalar<T> & operator=(const Scalar<T> & rhs);

		T		getValue(void) const;
		void	setValue(T const value);

		Scalar<T> &		operator++(void);
		Scalar<T>		operator++(int);
		Scalar<T> &		operator--(void);
		Scalar<T>		operator--(int);

		Scalar<T> &		operator+=(const Scalar<T> & rhs);
		Scalar<T> &		operator-=(const Scalar<T> & rhs);
		Scalar<T> &		operator*=(const Scalar<T> & rhs);
		Scalar<T> &		operator/=(const Scalar<T> & rhs);

		Scalar<T>		operator+(const Scalar<T>& rhs);
		Scalar<T>		operator-(const Scalar<T>& rhs);
		const Scalar<T>	operator*(const Scalar<T>& rhs) const;
		Scalar<T>		operator*(const Scalar<T>& rhs);
		Scalar<T>		operator/(const Scalar<T>& rhs);
		Scalar<T>		operator%(const Scalar<T>& rhs) const;

		bool			operator==(const Scalar<T> &rhs) const;
		bool			operator!=(const Scalar<T> &rhs) const;
		bool			operator<(const Scalar<T> &rhs) const;
		bool			operator>(const Scalar<T> &rhs) const;
		bool			operator<=(const Scalar<T> &rhs) const;
		bool			operator>=(const Scalar<T> &rhs) const;
	};


	template <typename T>
	std::ostream&operator<<(std::ostream & os, Scalar<T> const & rhs)
	{
		os << rhs.getValue();
		return os;
	}

	template <typename T>
	Scalar<T> pow(Scalar<T> &num, Scalar<T> &p) {
		return Scalar<T>(std::pow(num.getValue(), p.getValue()));
	}

	template <typename T>
	Scalar<T>::Scalar(void): _value(0) {
		return ;
	}

	template <typename T>
	Scalar<T>::Scalar(T n): _value(n) {
		return ;
	}

	template <typename T>
	Scalar<T>::~Scalar(void) {
		return ;
	}

	template <typename T>
	Scalar<T>::Scalar(Scalar<T> const & rhs) {
		*this = rhs;
	}

	template <typename T>
	Scalar<T> &	Scalar<T>::operator=(const Scalar<T> & rhs) {
		this->_value = rhs.getValue();
		return *this;
	}

	template <typename T>
	T			Scalar<T>::getValue(void) const {
		return this->_value;
	}

	template <typename T>
	void		Scalar<T>::setValue(T const value) {
		_value = value;
	}

	template <typename T>
	Scalar<T> &	Scalar<T>::operator++() {
		_value += 1;
		return *this;
	}

	template <typename T>
	Scalar<T>	Scalar<T>::operator++(int) {
		_value += 1;
		return *this;
	}

	template <typename T>
	Scalar<T> &	Scalar<T>::operator--() {
		_value -= 1;
		return *this;
	}

	template <typename T>
	Scalar<T>	Scalar<T>::operator--(int) {
		_value -= 1;
		return *this;
	}

	template <typename T>
	Scalar<T> & Scalar<T>::operator+=(const Scalar<T> & rhs) {
		_value += rhs.getValue();
		return *this;
	}

	template <typename T>
	Scalar<T> & Scalar<T>::operator-=(const Scalar<T> & rhs) {
		_value -= rhs.getValue();
		return *this;
	}

	template <typename T>
	Scalar<T> & Scalar<T>::operator*=(const Scalar<T> & rhs) {
		_value *= rhs.getValue();
		return *this;
	}

	template <typename T>
	Scalar<T> & Scalar<T>::operator/=(const Scalar<T> & rhs) {
		_value /= rhs.getValue();
		return *this;
	}

	template <typename T>
	Scalar<T> Scalar<T>::operator+(const Scalar<T>& rhs) {
		return Scalar<T>(_value + rhs.getValue());
	}

	template <typename T>
	Scalar<T> Scalar<T>::operator-(const Scalar<T>& rhs) {
		return Scalar<T>(_value - rhs.getValue());
	}

	template <typename T>
	const Scalar<T> Scalar<T>::operator*(const Scalar<T>& rhs) const {
		return Scalar<T>(_value * rhs.getValue());
	}

	template <typename T>
	Scalar<T> Scalar<T>::operator*(const Scalar<T>& rhs) {
		return Scalar<T>(_value * rhs.getValue());
	}

	template <typename T>
	Scalar<T> Scalar<T>::operator/(const Scalar<T>& rhs) {
		return Scalar<T>(_value / rhs.getValue());
	}

	template <typename T>
	Scalar<T> Scalar<T>::operator%(const Scalar<T>& rhs) const {
		return Scalar<T>(static_cast<long>(_value) % static_cast<long>(rhs.getValue()));
	}

	template <typename T>
	bool Scalar<T>::operator==(const Scalar<T> &rhs) const {
		return _value == rhs.getValue();
	}

	template <typename T>
	bool Scalar<T>::operator!=(const Scalar<T> &rhs) const{
		return _value != rhs.getValue();
	}

	template <typename T>
	bool Scalar<T>::operator<(const Scalar<T> &rhs) const{
		return _value < rhs.getValue();
	}

	template <typename T>
	bool Scalar<T>::operator>(const Scalar<T> &rhs) const{
		return _value > rhs.getValue();
	}

	template <typename T>
	bool Scalar<T>::operator<=(const Scalar<T> &rhs) const{
		return _value <= rhs.getValue();
	}

	template <typename T>
	bool Scalar<T>::operator>=(const Scalar<T> &rhs) const{
		return _value >= rhs.getValue();
	}

}

#endif /*SCALAR_HPP*/
