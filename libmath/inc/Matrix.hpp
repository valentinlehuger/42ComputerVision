#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <exception>
#include <cmath>
#include <utility>
#include <Vector.hpp>
#include <sstream>

enum e_operator{
	PLUS,
	MINUS,
	MUL,
	DIV,
	MOD,
	POW
};

// template <typename T>
// Matrix<T>			matrix_wise_op(cv42::Matrix<T> mat, T const nb, e_operator op);


namespace cv42 {

template <typename T>
class Matrix{
	public:

		/**
 		 * Contructor for matrix initialize with value 0.0.
 		 */
		Matrix<T>(int i, int j);
		Matrix<T>(void);

		/**
 		 * Constructor with initialized value.
 		 */
		Matrix(const std::vector<Vector<T> > & v);
		Matrix(Matrix<T> const & m);
		Matrix<T> & operator=(Matrix<T> const & m);
		Vector<T> &			operator[](int i);
		const Vector<T> &	operator[](int i) const;

		typename std::vector<Vector<T> >::iterator begin(void);
		typename std::vector<Vector<T> >::iterator end(void);

		int						getNrows(void) const;
		int						getNcols(void) const;
		std::vector<Vector<T> > getContainer(void) const;

		Matrix<T>			transpose(void) const;


		/**
		 * Return a Vector version of this Matrix
		 */
		Vector<T>			toVector(void) const;

		/**
		 * Return a flat version of this Matrix
		 */
		Matrix<T>			flatten(void) const;

		/**
		 * Return a Vector containing the diagonal value of this Matrix.
		 * If this Matrix is not square, an InvalidMatrixSizeException is thrown.
		 */
		Vector<T>			diagonal(void) const;

		typedef T(*randomizerFunction)();

		/**
		 * This function assign a random value to every cells of the matrix.
		 * It overload previous values.
		 * If the randomizerFunction use rand(), call srand before.
		 */
		void				randomize(Matrix<T>::randomizerFunction fn);


		/**
		 * TODO
		 * Return a deep copy of the matrix given in parameter
		 */
		static Matrix<T>	newSMatrix(Matrix<T>);

		/**
		 * TODO return this matrix with each entry is the opposite
		 * aMatrix + aMatrix.opp() = aMatrixFullOfZero
		 */
		Matrix<T>			opp();

		Matrix<T>	dotProduct(Matrix<T> const & rhs) const;

		bool		operator==(const Matrix<T> & rhs) const;
		Matrix<T>	operator*(Matrix<T> const & rhs) const;
		Matrix<T>	operator+(Matrix<T> const & rhs) const;
		Matrix<T>	operator+(T const & rhs) const;
		Matrix<T>	operator-(Matrix<T> const & rhs) const;
		Matrix<T>	operator-(Vector<T> const & rhs) const;
		Matrix<T>	operator/(Matrix<T> const & rhs) const;
		Matrix<T>	operator/(T const & rhs) const;
		Matrix<T>	operator%(Matrix<T> const & rhs) const;
		Matrix<T>	operator^(Matrix<T> const & rhs) const;
		Matrix<T>	operator^(T const & rhs) const;
		Matrix<T>	mul(Matrix<T> const & rhs) const;
		Matrix<T>	mul(T const & rhs) const;

		/**
 		 * This function return a sub matrix of this matrix.
 		 *
 		 * mat:
 		 * a b c d
 		 * e f g h
 		 * i j k l
 		 * m n o p
 		 * q r s t
 		 *
 		 * mat.slice(1, 1, 2, 3):
 		 * f g
 		 * j k
 		 * n o
 		 *
 		 * @xi		the index of ligne of the sub matrix.
 		 * @yi		the index of column of the sub matrix.
 		 * @xf		the index of the first ligne not included in sub matrix.
 		 * @yf		the index of the fisrt column not included in sub matrix.
 		 */
		Matrix<T>	slice(int xi, int yi, int xf, int yf) const;

		/**
		 * Normalization of the matrix following the xaxis(0) or yaxis(1)
		 **/
		Matrix<T>	normalization(int axis) const;

		/**
		 * Mean of the matrix following the xaxis(0) or yaxis(1), return a one vector matrix
		 * dimensions to use operator methods on matrix
		 **/
		Matrix<T>	mean(int axis) const;

		/**
		 * Mean of the matrix following the xaxis(0) or yaxis(1),
		 * return a one vector matrix
		 **/
		Matrix<T>	mean2(int axis) const;

		/**
		 * This function insert the matrix mtx into this matrix at
		 * the defined row and column parameter. If mtx is too large
		 * for the insertion, an InvalidMatrixSizeException is thrown
		 */
		void		insert(Matrix<T> const & mtx, int rowDest, int colDest);

		bool		isSquare(void) const;

		T			determinant(void);
		T			trace(void);

		/**
		 * Return a one row matrix with the mean of each column (axis = 0) or
		 * each row (axis = 1)
		 */
		Matrix<T>	sum(int axis) const;

		/**
		 * Perform a QR decomposition on the calling instance.
		 * Return a pair of element where pair->first is the Q Matrix
		 * and pair-second the R Matrix.
		 * A InvalidMatrixSizeException is thrown if the calling instance of
		 * Matrix is not square.
		 */
		std::pair<Matrix<T>, Matrix<T> >	qrDecomposition(void) const;

		/**
		 * Compute the eigenvalue && eigenvector of this matrix using the qr algorithm
		 * The pair returned contain in first index a vector with the the eigenvalue computed
		 * and in second index, the corresponding eigenvector.
		 * A InvalidMatrixSizeException is thrown if the calling instance of
		 * Matrix is not square.
		 */
		std::pair<Vector<T>, Matrix<T> > eigenvv(int maxIter = 100) const;



		Matrix<T>			logistic();


		/**
		 * Exception for invalid matrix size operCation. The msg
		 * is customisable via constructor.
		 * The matrix involved can be pass to the exception to display their sizes
		 */

		class InvalidMatrixSizeException : public std::exception {
				const Matrix<T>*	_lhs;
				const Matrix<T>*	_rhs;
				const char*			_msg;

			public:
				InvalidMatrixSizeException(const char* msg = NULL, const Matrix<T>* lhs = NULL, const Matrix<T>* rhs = NULL);
				InvalidMatrixSizeException(const Matrix<T>* lhs, const Matrix<T>* rhs);

				virtual const char* what(void) const throw();
		};

		/**
 		 * Error when we request an element which at least one of the index
 		 * is out of the matrix bounds.
 		 */
		class IndexOutOfBondException;

		static Matrix<T>		identity(int size);

	protected:
		int						_nrows;
		int						_ncols;
		std::vector<Vector<T> > _container;

		// type of a matrix operation function
		typedef T  (Matrix<T>::*mat_operation)(T lhs, T rhs) const;

		/**
 		 * This is a foreach applying the mat_operation on each pair of element
		 * between "this" matrix and the rhs matrix
 		 */
		Matrix<T>	wiseOp(mat_operation operation, Matrix<T> const & rhs) const;
		Matrix<T>	wiseOp(mat_operation operation, T const & rhs) const;

		T			plusOp(T lhs, T rhs) const;
		T			minusOp(T lhs, T rhs) const;
		T			divOp(T lhs, T rhs) const;
		T			modOp(T lhs, T rhs) const;
		T			powOp(T lhs, T rhs) const;
		T			mulOp(T lhs, T rhs) const;



		/*
		   Recursive definition of determinate using expansion by minors.
		*/
		T calc_determinant(Matrix<T> &a,int n);
};

template <typename T>
std::ostream & operator<<(std::ostream & o, Matrix<T> & rhs) {
	typename std::vector<Vector<T> >::iterator it;

	for (it = rhs.begin() ; it != rhs.end() ; it++){
		o << *it << std::endl;
	}
	return o;
}

template <typename T>
Matrix<T>::Matrix(int i, int j):_nrows(i),_ncols(j),_container(i) {
		typename std::vector<Vector<T> >::iterator it;
		for (it = this->begin() ; it != this->end(); it++){
				*it = Vector<T>(j);
		}
		return ;
}

template <typename T>
Matrix<T>::Matrix(void):_nrows(1),_ncols(1),_container({Vector<T>()}) {
		return ;
}

template <typename T>
Matrix<T>::Matrix(const std::vector<Vector<T> >& v):_nrows(v.size()), _container(v){
		if (this->_nrows > 0) {
				this->_ncols = v[0].getSize();
		} else {
				this->_ncols = 0;
		}
		return ;
}

template <typename T>
Matrix<T>::Matrix(Matrix<T> const & m) {
	*this = m;
}

template <typename T>
Matrix<T> & Matrix<T>::operator=(Matrix<T> const & m){
	this->_container = m.getContainer();
	this->_nrows = m.getNrows();
	this->_ncols = m.getNcols();
	return *this;
}

template <typename T>
Vector<T> &		Matrix<T>::operator[](int i) {
		return this->_container[i];
}

template <typename T>
const Vector<T> & Matrix<T>::operator[](int i) const {
		return this->_container[i];
}

template <typename T>
typename std::vector<Vector<T> >::iterator Matrix<T>::begin(void) {
		return this->_container.begin();
}

template <typename T>
typename std::vector<Vector<T> >::iterator Matrix<T>::end(void) {
		return this->_container.end();
}

template <typename T>
int		Matrix<T>::getNrows(void) const {
		return this->_nrows ;
}

template <typename T>
int		Matrix<T>::getNcols(void) const {
		return this->_ncols ;
}

template <typename T>
std::vector<Vector<T> > Matrix<T>::getContainer(void) const {
	return this->_container;
}


template <typename T>
Matrix<T>	Matrix<T>::transpose(void) const {
		Matrix<T> M(this->_ncols, this->_nrows);
		for (int i = 0 ; i < M.getNrows() ; i++){
				for (int j = 0 ; j < M.getNcols(); j++){
						M[i][j] = this->_container[j][i];
				}
		}
		return M;
}

template <typename T>
Vector<T>	Matrix<T>::toVector(void) const {
	std::vector<T>	values(this->getNrows() * this->getNcols(), 0);
	int				row = -1;
	int				col = -1;
	int				i = 0;

	while (++row != this->getNrows()) {
		while (++col != this->getNcols()) {
			values[i] = (*this)[row][col];
			++i;
		}
		col = -1;
	}
	return Vector<T>(values);
}

template <typename T>
Matrix<T>	Matrix<T>::flatten(void) const {
	Matrix<T>	flat(1, this->getNrows() * this->getNcols());
	int			row = -1;
	int			col = -1;

	while (++row != this->getNrows()) {
		while (++col != this->getNcols()) {
			flat[0][row + col] = (*this)[row][col];
		}
		col = -1;
	}
	return flat;
}


template <typename T>
bool	Matrix<T>::operator==(const Matrix<T> & rhs)const {
		int row = -1;
		int col = -1;
		if (this->getNrows() != rhs.getNrows() ||
			this->getNcols() != rhs.getNcols())
				return (false);
		while (++row != this->getNrows()) {
				while (++col != this->getNcols()) {
						if (this->_container[row][col] != rhs[row][col])
								return (false);
				}
				col = -1;
		}
		return (true);
}

template <typename T>
Matrix<T>	Matrix<T>::dotProduct(Matrix<T> const & rhs) const {
		if (this->_ncols != rhs.getNrows()){
				throw Matrix::InvalidMatrixSizeException("Dot product invalid matrix size", this, &rhs);
		}
		Matrix<T> M(this->_nrows, rhs.getNcols());
		for (int i = 0 ; i < M.getNrows() ; i++){
				for (int j = 0 ;j < M.getNcols(); j++){
 						T sum = 0;
						for (int k = 0 ; k < this->_ncols ; k++){
 								sum += this->_container[i][k]*rhs[k][j];
						}
						M[i][j] = sum;
				}
		}
		return M;
}

template <typename T>
Matrix<T>	Matrix<T>::operator*(Matrix<T> const & rhs) const {
		return this->dotProduct(rhs);
}

template <typename T>
Matrix<T>	Matrix<T>::operator+(Matrix<T> const & rhs) const {
		return this->wiseOp(&Matrix<T>::plusOp, rhs);
}

template <typename T>
Matrix<T>	Matrix<T>::operator+(T const & rhs) const {
	// char	*cuda = getenv("CUDA");

	// if (cuda && strcmp(cuda, "YES") == 0)
	// 	return matrix_wise_op<T>(*this, rhs, PLUS);
	// else
	// {
	// 	printf("%s\n", cuda);
		return this->wiseOp(&Matrix<T>::plusOp, rhs);
	// }
}

template <typename T>
Matrix<T>	Matrix<T>::operator-(Matrix<T> const & rhs) const {
		return this->wiseOp(&Matrix<T>::minusOp, rhs);
}

template <typename T>
Matrix<T>	Matrix<T>::operator-(Vector<T> const & rhs) const
{
	Matrix<T> 		newMatrix(getNrows(), getNcols());

	for (int i = 0; i < getNrows(); i++)
		for (int j = 0; j < getNcols(); j++)
			newMatrix[i][j] = (*this)[i][j] - rhs[i];
	return (newMatrix);
}

template <typename T>
Matrix<T>	Matrix<T>::operator/(Matrix<T> const & rhs) const {
		return this->wiseOp(&Matrix<T>::divOp, rhs);
}

template <typename T>
Matrix<T>	Matrix<T>::operator/(T const & rhs) const {
		return this->wiseOp(&Matrix<T>::divOp, rhs);
}

template <typename T>
Matrix<T>	Matrix<T>::operator%(Matrix<T> const & rhs) const {
		return this->wiseOp(&Matrix<T>::modOp, rhs);
}

template <typename T>
Matrix<T>	Matrix<T>::operator^(Matrix<T> const & rhs) const {
		return this->wiseOp(&Matrix<T>::powOp, rhs);
}

template <typename T>
Matrix<T>	Matrix<T>::operator^(T const & rhs) const {
		return this->wiseOp(&Matrix<T>::powOp, rhs);
}

template <typename T>
Matrix<T>	Matrix<T>::mul(Matrix<T> const & rhs) const {
		return this->wiseOp(&Matrix<T>::mulOp, rhs);
}

template <typename T>
Matrix<T>	Matrix<T>::mul(T const & rhs) const {
		return this->wiseOp(&Matrix<T>::mulOp, rhs);
}

template <typename T>
bool		Matrix<T>::isSquare(void) const {
		return (this->_nrows == this->_ncols);
}

template <typename T>
T			Matrix<T>::determinant(void) {
		if (!this->isSquare())
				throw Matrix::InvalidMatrixSizeException("Determinant calculation invalid matrix size", this);
		return this->calc_determinant(*this, _nrows);
}

template <typename T>
T			Matrix<T>::trace(void) {
		T		ret;

		if (!this->isSquare())
				throw Matrix::InvalidMatrixSizeException("Trace calculation invalid matrix size", this);
		for (int i = 0; i < _nrows; i++)
				ret += _container[i][i];
		return ret;
}

template <typename T>
Matrix<T>	Matrix<T>::wiseOp(mat_operation operation, Matrix<T> const & rhs) const {
		int			row = -1;
		int			col = -1;
		Matrix<T>	result(this->getNrows(), this->getNcols());
		if (this->getNrows() != rhs.getNrows() || this->getNcols() != rhs.getNcols())
				throw Matrix::InvalidMatrixSizeException("Wise operation invalid matrix size", this, &rhs);
		while (++row != this->getNrows()) {
				while (++col != this->getNcols()) {
						result[row][col] =
								(this->*operation)(this->_container[row][col], rhs[row][col]);
				}
				col = -1;
		}
		return result;
}

template <typename T>
Matrix<T>	Matrix<T>::wiseOp(mat_operation operation, T const & rhs) const {
		int			row = -1;
		int			col = -1;
		Matrix<T>	result(this->getNrows(), this->getNcols());
		while (++row != this->getNrows()) {
				while (++col != this->getNcols()) {
						result[row][col] =
								(this->*operation)(this->_container[row][col], rhs);
				}
				col = -1;
		}
		return result;
}

template <typename T>
T			Matrix<T>::plusOp(T lhs, T rhs) const {
		return (lhs + rhs);
}

template <typename T>
T			Matrix<T>::minusOp(T lhs, T rhs) const {
		return (lhs - rhs);
}

template <typename T>
T			Matrix<T>::divOp(T lhs, T rhs) const {
		return (lhs / rhs);
}

template <typename T>
T			Matrix<T>::modOp(T lhs, T rhs) const {
		return (lhs % rhs);
}

template <typename T>
T			Matrix<T>::powOp(T lhs, T rhs) const {
		return (pow(lhs, rhs));
}

template <typename T>
T			Matrix<T>::mulOp(T lhs, T rhs) const {
		return (lhs * rhs);
}

template <typename T>
T			Matrix<T>::calc_determinant(Matrix<T> &a,int n) {
		int			i, j, j1, j2;
		T			det = 0;
		Matrix<T>	m(n-1, n-1);

		if (n < 1) { /* Error */}
		else if (n == 1) {det = a[0][0]; /* Shouldn't get used */}
		else if (n == 2) { det = a[0][0] * a[1][1] - a[1][0] * a[0][1];}
		else {
				det = 0;

				for (j1 = 0;j1 < n;j1++)
						{
								for (i = 1;i < n;i++)
										{
												j2 = 0;
												for (j = 0;j < n;j++)
														{
																if (j == j1)
																		continue;
																m[i-1][j2] = a[i][j];
																j2++;
														}
										}
								det += pow(-1.0,1.0+j1+1.0) * a[0][j1] * calc_determinant(m, n-1);
						}
		}
		return(det);
}

template <typename T>
Matrix<T>::InvalidMatrixSizeException::InvalidMatrixSizeException(const char* msg, const Matrix<T>* lhs, const Matrix<T>* rhs) : _msg(msg), _lhs(lhs), _rhs(rhs) {
		return ;
}

template <typename T>
Matrix<T>::InvalidMatrixSizeException::InvalidMatrixSizeException(const Matrix<T>* lhs, const Matrix<T>* rhs) : _msg(NULL), _lhs(lhs), _rhs(rhs) {
		return ;
}

template <typename T>
const char*			Matrix<T>::InvalidMatrixSizeException::what() const throw() {
		std::ostringstream	errorStream;

		if (this->_msg == NULL)
				errorStream << "Incompatible matrix size";
		else
				errorStream << this->_msg;
		if (this->_lhs != NULL && this->_rhs != NULL)
				errorStream << ": [" << this->_lhs->getNrows() << " x " << this->_lhs->getNcols() << "] vs [" << this->_rhs->getNrows() << " x " << this->_rhs->getNcols() << "]";
		else if (this->_lhs != NULL)
				errorStream << ": [" << this->_lhs->getNrows() << " x " << this->_lhs->getNcols() << "]";
	return (errorStream.str().c_str());
}

template <typename T>
Matrix<T>	Matrix<T>::identity(int size)
{
	Matrix<T>			m(size, size);

	for (int i = 0; i < size; i++)
		m[i][i] = 1;
	return m;
}

template <typename T>
Matrix<T>	Matrix<T>::slice(int xi, int yi, int xf, int yf) const
{
	Matrix<T>	to_return(xf-xi, yf-yi);

	if (xf > this->getNrows()) {
		throw new IndexOutOfBondException(xf, this->getNrows());
	}
	if (yf > this->getNcols()) {
		throw new IndexOutOfBondException(xf, this->getNcols());
	}
	for (int x = xi ; x < xf ; ++x) {
		for (int y = yi ; y < yf ; ++y) {
			to_return[x-xi][y-yi] = this->_container[x][y];
		}
	}
	return to_return;
}

template <typename T>
class Matrix<T>::IndexOutOfBondException : public std::exception {
	const int	requested;
	const int	matrix_max;

	public:
		IndexOutOfBondException (int _requested, int _matrix_max)
			: requested(_requested), matrix_max(_matrix_max)
		{}

		virtual const char* what(void) const throw()
		{
			std::stringstream ss;
			ss << "Requested index " << requested << " is out of bound " <<
				matrix_max << "for matrix.";
			return "";
		}
};

template <typename T>
void		Matrix<T>::insert(Matrix<T> const & mtx, int offrow, int offcol) {
	if (offrow + mtx.getNrows() > this->getNrows() || offcol + mtx.getNcols() > this->getNcols())
		throw Matrix::InvalidMatrixSizeException("Matrix insertion error", this, &mtx);
	for (int row = offrow; row - offrow < mtx.getNrows(); row++) {
		for (int col = offcol; col - offcol < mtx.getNcols(); col++) {
			(*this)[row][col] = mtx[row - offrow][col - offcol];
		}
	}
	return ;
}

template <typename T>
std::pair<Matrix<T>, Matrix<T> >	Matrix<T>::qrDecomposition(void) const {
	int	size = this->getNrows();
	Matrix<T>	Q = Matrix<T>::identity(size);
	Matrix<T>	R = (*this);
	Matrix<T>	H;
	Matrix<T>	hh;

	if (!this->isSquare())
		throw Matrix::InvalidMatrixSizeException("QR-Decomposition: Matrix must be square", this);
	for (int i = 0; i != size - 1; i++) {
		H = Matrix<T>::identity(size);
	    hh = R.slice(i, i, R.getNrows(), i + 1).transpose()[0].householder();
		H.insert(hh, i, i);
		Q = Q * H;
		R = H * R;
	}
	return std::make_pair(Q, R);
}

template <typename T>
Vector<T>	Matrix<T>::diagonal(void) const {
	std::vector<T>	values(this->getNrows(), 0);

	if (!this->isSquare())
		throw Matrix::InvalidMatrixSizeException("Diagonal: can't extract diagonal vector on a non-square Matrix", this);
	for (int i = 0; i != this->getNrows(); i++) {
		values[i] = (*this)[i][i];
	}
	return Vector<T>(values);
}

template <typename T>
std::pair<Vector<T>, Matrix<T> > Matrix<T>::eigenvv(int maxIter) const {
	Matrix<T>						t = *this;
	Matrix<T>						tmo;
	Matrix<T>						Q = Matrix<T>::identity(this->getNrows());
	std::pair<Matrix<T>, Matrix<T> >	qR;

	for(int k = 0; k != maxIter; k++) {
		tmo = t;
		qR = tmo.qrDecomposition();
		t = qR.second * qR.first;
		Q = Q * qR.first;
	}
	return std::make_pair(t.diagonal(), Q);
}

template <typename T>
Matrix<T> Matrix<T>::normalization(int axis) const {
	if (axis == 1){
		Matrix<T> m(*this);
		for (int i = 0 ; i < m.getNrows() ; i++) {
			m[i] = m[i].normalization();
		}
		return m;
	} else if (axis == 0) {
		Matrix<T> mt(this->transpose());
		for (int i = 0 ; i < mt.getNrows() ; i++) {
			mt[i] = mt[i].normalization();
		}
		return mt.transpose();
	} else {
		throw "ERROR";
	}
}

template <typename T>
Matrix<T> Matrix<T>::mean(int axis) const {
	if (axis == 1){
		Matrix<T> m(*this);
		for (int i = 0 ; i < m.getNrows() ; i++) {
			T mean_val = m[i].mean();
			for (int j = 0 ; j < m.getNcols() ; j++) {
				m[i][j] = mean_val;
			}
		}
		return m;
	} else if (axis == 0) {
		Matrix<T> mt(this->transpose());
		for (int i = 0 ; i < mt.getNrows() ; i++) {
			T mean_val = mt[i].mean();
			for (int j = 0 ; j < mt.getNcols() ; j++) {
				mt[i][j] = mean_val;
			}
		}
		return mt.transpose();
	} else {
		throw "ERROR";
	}
}

template <typename T>
Matrix<T>			Matrix<T>::mean2(int axis) const {
	Matrix<T>		result(1, (axis == 0 ? this->getNcols() : this->getNrows()));
	Matrix<T>		*tocompute = const_cast<Matrix<T>*>(this);

	if (axis == 0) {
		Matrix<T>	t = this->transpose();
		tocompute = &t;

		for (int row = 0; row < tocompute->getNrows(); ++row)
			result[0][row] = (*tocompute)[row].mean();
		return (result);
	}
	for (int row = 0; row < tocompute->getNrows(); ++row)
	    result[0][row] = (*tocompute)[row].mean();
	return (result);
}

template <typename T>
Matrix<T>			Matrix<T>::sum(int axis) const {
	Matrix<T>		result(1, (axis == 0 ? this->getNcols() : this->getNrows()));

	if (axis == 0) {
		for (int col = 0; col < this->getNcols(); ++col)
			for (int row = 0; row < this->getNrows(); ++row)
				result[0][col] += (*this)[row][col];
	} else {
		for (int row = 0; row < this->getNrows(); ++row)
			for (int col = 0; col < this->getNcols(); ++col)
				result[0][row] += (*this)[row][col];
	}
	return (result);
}

template <typename T>
void				Matrix<T>::randomize(Matrix<T>::randomizerFunction fn)
{
	for (int col = 0; col < this->getNcols(); ++col)
		for (int row = 0; row < this->getNrows(); ++row)
			(*this)[row][col] = fn();
}

template <typename T>
Matrix<T>			Matrix<T>::logistic(void)
{
	Matrix<T>	result = Matrix<T>(getNrows(), getNcols());

	for (int col = 0; col < this->getNcols(); ++col)
		for (int row = 0; row < this->getNrows(); ++row)
			result[row][col] = 1. / (1. + exp(- _container[row][col]));
	return result;
}

template <typename T>
Matrix<T>			Matrix<T>::opp(void)
{
	Matrix<T>	result = Matrix<T>(getNrows(), getNcols());

	for (int col = 0; col < this->getNcols(); ++col)
		for (int row = 0; row < this->getNrows(); ++row)
			result[row][col] = -(*this)[row][col];
	return result;
}


}//end of namespace cv42


#endif /*MATRIX_HPP*/
