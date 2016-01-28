#ifndef SESSIONEIG_HPP
#define SESSIONEIG_HPP

#include <Vector.hpp>
#include <Matrix.hpp>
#include <Session.hpp>

class SessionEig : public Session
{
public:

	SessionEig(void);
	SessionEig(std::string csvPath);
	~SessionEig(void);

	cv42::Matrix<float>*	getEigVectors(void) const;
	cv42::Matrix<float>*	getMeanFace(void) const;
	cv42::Matrix<float>*	getWeights(void) const;

	void					setEigVectors(cv42::Matrix<float>* eigenvectors);
	void					setEigVectors(cv42::Matrix<float> eigenvectors);
	void					setMeanFace(cv42::Matrix<float>* meanFace);
	void					setMeanFace(cv42::Matrix<float> meanFace);
	void					setWeights(cv42::Matrix<float>* weights);
	void					setWeights(cv42::Matrix<float> weights);

private:

	cv42::Matrix<float>		*_eigenvectors;
	cv42::Matrix<float>		*_meanFace;
	cv42::Matrix<float>		*_weights;
};

SessionEig::SessionEig(void) : _eigenvectors(NULL), _meanFace(NULL), _weights(NULL) {
	return ;
}

SessionEig::SessionEig(std::string csvPath)
		: Session(csvPath), _eigenvectors(), _meanFace(), _weights()
{
	_eigenvectors = new cv42::Matrix<float>();
	return ;
}

SessionEig::~SessionEig(void) {
	return ;
}

cv42::Matrix<float>*	SessionEig::getEigVectors(void) const
{
	return (this->_eigenvectors);
}

cv42::Matrix<float>*	SessionEig::getMeanFace(void) const
{
	return (this->_meanFace);
}

cv42::Matrix<float>*	SessionEig::getWeights(void) const
{
	return (this->_weights);
}

void				SessionEig::setEigVectors(cv42::Matrix<float> *eigenvectors) {
	this->_eigenvectors = eigenvectors;
	return ;
}

void				SessionEig::setEigVectors(cv42::Matrix<float> eigenvectors) {
	this->_eigenvectors = new cv42::Matrix<float>(eigenvectors);
	return ;
}

void				SessionEig::setMeanFace(cv42::Matrix<float> *meanFace) {
	this->_meanFace = meanFace;
	return ;
}

void				SessionEig::setMeanFace(cv42::Matrix<float> meanFace) {
	this->_meanFace = new cv42::Matrix<float>(meanFace);
	return ;
}

void				SessionEig::setWeights(cv42::Matrix<float> *weights) {
	this->_weights = weights;
	return ;
}

void				SessionEig::setWeights(cv42::Matrix<float> weights) {
	this->_weights = new cv42::Matrix<float>(weights);
	return ;
}

#endif
