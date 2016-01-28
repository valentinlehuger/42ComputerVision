#ifndef NN_HPP
# define NN_HPP

#include <Matrix.hpp>
#include <Vector.hpp>
#include <vector>
#include <algorithm>
#include <SessionTest.hpp>
#include <Session.hpp>
#include <algorithm>

namespace cv42
{

class NN : public Session
{
public:

	NN(std::string csvPath, int nbr_neurons, float alpha, float lambda);
	~NN(void);


	float						getAlpha() const;
	void						setAlpha(float &val);
	float						getLambda() const;
	void						setLambda(float &val);
	cv42::Matrix<float>			getW1() const;
	void						setW1(cv42::Matrix<float> &val);
	cv42::Matrix<float>			getW2() const;
	void						setW2(cv42::Matrix<float> &val);
	cv42::Matrix<float>			getA1() const;
	void						setA1(cv42::Matrix<float> &val);
	cv42::Matrix<float>			getA2() const;
	void						setA2(cv42::Matrix<float> &val);
	cv42::Matrix<float>			getA3() const;
	void						setA3(cv42::Matrix<float> &val);
	std::vector<std::string>	getUniqueLabels() const;
	void						setUniqueLabels(std::vector<std::string> &val);

	/**
	 * Train the neural network according to the faces in NN::getImages()
	 */
	void						train(void);

	/**
	 * Given the parameter of the NN attribute of SessionNNTest, fill the attributes
	 * SessionNNTest::_resultPaths and SessionNNTest::_resultLabels. It then return a
	 * std::vector<int> containing the list of index used to fill the result vector in SessionNNTest
	 */
	void						predict(SessionTest & s);

private:
	void	forwardPropagation();
	void	backwardPropagation();

	/**
	 * Number of neurons in hidden layers (A2)
	 */
	int					_nbr_neurons;

	/**
	 * The input layer.
	 */
	cv42::Matrix<float>	_A1;

	/**
	 * Activation layer.
	 */
	cv42::Matrix<float>	_A2;

	/**
	 * Output layer.
	 */
	cv42::Matrix<float>	_A3;

	/**
	 * Convergence coef.
	 */
	float				_alpha;

	/**
	 * Regularisation coef.
	 */
	float				_lambda;

	/**
	 * Weights for A2
	 */
	cv42::Matrix<float>	_W1;

	/**
	 * Weights for A3
	 */
	cv42::Matrix<float>	_W2;

	/**
	 * Matrix of changing weight for w1
	 */
	cv42::Matrix<float>	_C1;

	/**
	 * Matrix of changing weight for w2
	 */
	cv42::Matrix<float>	_C2;

	std::vector<std::string>	_uniqueLabels;
	std::vector<std::string>	_uniquePaths;

	/**
	 * Real output. Matrix of 0 and 1, each row corresponding to one label with
	 * a one for the right matrix.
	 */
	cv42::Matrix<float>	_output;

	/**
	 * Result of cost function
	 */
	float						_j;
};

static float randomizer()
{
	return (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) - 0.5f;
}

NN::NN(std::string csvPath, int nbr_neurons, float alpha, float lambda)
		: Session(csvPath), _nbr_neurons(nbr_neurons), _alpha(alpha), _lambda(lambda)
{
	int		seekpos = -1;

	/* Create the unqique labels */
	for (std::vector<std::string>::iterator it = (*_labels).begin() ; it != (*_labels).end(); ++it)
	{
			if(std::find(_uniqueLabels.begin(), _uniqueLabels.end(), (*it)) != _uniqueLabels.end())
				continue ;
	        else 
				_uniqueLabels.push_back(*it);

	}

	/* Create the unqique paths */
	for (std::vector<std::string>::iterator it = _uniqueLabels.begin() ; it != _uniqueLabels.end(); ++it)
	{
		seekpos = find(_labels->begin(), _labels->end(),
				*it) - _labels->begin();
		if (seekpos >= _labels->size())
			//TODO make an exception
			throw "Undefined label";
		_uniquePaths.push_back((*_paths)[seekpos]);
	}

	_nbr_neurons = nbr_neurons;
	_alpha = alpha;
	_lambda = lambda;

	srand (static_cast <unsigned> (time(0)));
	_A1 = (this->getImages()).transpose();
	_W1 = cv42::Matrix<float>(_A1.getNcols(), _nbr_neurons);
	_W1.randomize(randomizer);
	_W2 = cv42::Matrix<float>(nbr_neurons, _uniqueLabels.size());
	_W2.randomize(randomizer);

	_C1 = cv42::Matrix<float>(_A1.getNcols(), nbr_neurons);
	_C2 = cv42::Matrix<float>(nbr_neurons, _labels->size());

	// m is the matrix of 0 and one corresponding to the image labels
	_output = cv42::Matrix<float>(_labels->size(), _uniqueLabels.size());
	for (int i = 0; i < _labels->size() ; ++i){
		seekpos = find(_uniqueLabels.begin(), _uniqueLabels.end(),
				(*_labels)[i]) - _uniqueLabels.begin();
		if (seekpos >= _uniqueLabels.size())
			//TODO make an exception
			throw "Undefined label";
		_output[i][seekpos] = 1;
	}
}

NN::~NN(void)
{
	return ;
}

void NN::forwardPropagation()
{
	_A2 = _A1.dotProduct(_W1).logistic();
	_A3 = _A2.dotProduct(_W2).logistic();
}

void NN::backwardPropagation()
{
	cv42::Matrix<float>	ddelta = _A3 - (_output);
	_j = 0;

	for (int i = 0; i < ddelta.getNrows(); ++i) {
		_j += (ddelta[i] ^ 2).sum();
	}
	cv42::Matrix<float> deltaA3 = ddelta.mul(_A3.mul(_A3.opp() + 1));
	cv42::Matrix<float> deltaA2 = deltaA3.dotProduct(_W2.transpose()).mul(_A2.mul(_A2.opp() + 1));

	// TODO create https://github.com/fmarmol/nnet/blob/master/goeigenfaces/Matrix/matrix.go#L39
	cv42::Matrix<float> tmpW1(_W1);
	cv42::Matrix<float> tmpW2(_W2);
	tmpW1[0][0] = 0;
	tmpW2[0][0] = 0;

	Matrix<float>		c1 = _A1.transpose().dotProduct(deltaA2).mul(1.0 / static_cast<float>(_labels->size())) - (tmpW1.mul(_lambda));
	Matrix<float>		c2 = _A2.transpose().dotProduct(deltaA3).mul(1.0 / static_cast<float>(_labels->size())) - (tmpW2.mul(_lambda));

	_C1 = c1;
	_C2 = c2;

	_W1 = _W1 - (c1.mul(_alpha));
	_W2 = _W2 - (c2.mul(_alpha));
}

void NN::train(void)
{
	for (int i = 0; i < 100; i++)
	{
		forwardPropagation();
		backwardPropagation();
	}
}

void NN::predict(SessionTest &s)
{
	std::vector<std::string>	resultPaths;
	std::vector<std::string>	resultLabels;
	float						max = 0;
	int							index;
	Matrix<float>				A2Test = s.getImages().transpose().dotProduct(_W1).logistic();
	Matrix<float>				A3Test = A2Test.dotProduct(_W2).logistic();

	for (int i = 0; i < A3Test.getNrows(); ++i) {
		max = A3Test[i][0];
		index = 0;
		for (int j = 0; j < A3Test[i].getSize(); ++j) {
			if (A3Test[i][j] > max) {
				max = A3Test[i][j];
				index = j;
			}
		}
		resultPaths.push_back(_uniquePaths[index]);
		resultLabels.push_back(_uniqueLabels[index]);
	}
	s.setResultPaths(resultPaths);
	s.setResultLabels(resultLabels);
	return ;
}

float	NN::getAlpha() const
{
	return _alpha;
}

void	NN::setAlpha(float &val)
{
	_alpha = val;
}

float	NN::getLambda() const
{
	return _lambda;
}

void	NN::setLambda(float &val)
{
	_lambda = val;
}

cv42::Matrix<float>	NN::getW1() const
{
	return _W1;
}

void	NN::setW1(cv42::Matrix<float> &val)
{
	_W1 = val;
}

cv42::Matrix<float>	NN::getW2() const
{
	return _W2;
}

void	NN::setW2(cv42::Matrix<float> &val)
{
	_W2 = val;
}

cv42::Matrix<float>	NN::getA1() const
{
	return _A1;
}

void	NN::setA1(cv42::Matrix<float> &val)
{
	_A1 = val;
}

cv42::Matrix<float>	NN::getA2() const
{
	return _A2;
}

void	NN::setA2(cv42::Matrix<float> &val)
{
	_A2 = val;
}

std::vector<std::string>	NN::getUniqueLabels() const
{
	return _uniqueLabels;
}

void	NN::setUniqueLabels(std::vector<std::string> &val)
{
	_uniqueLabels = val;
}

} /*end of namespace cv42*/

#endif
