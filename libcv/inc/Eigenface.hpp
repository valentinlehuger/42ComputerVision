#ifndef EIGENFACE_HPP
#define EIGENFACE_HPP

#include <Matrix.hpp>
#include <Vector.hpp>
#include <vector>
#include <SessionEig.hpp>
#include <SessionTest.hpp>

namespace cv42
{

class Eigenface
{
private:

	/**
	 * computeWeight expect "img" to be a matrix where each column representing an image,
	 * "eigv" a matrix where each line is a eigenvector computed during the train and
	 * "meanFace" a single row matrix representing the mean face computed during training.
	 * It then return a matrix where each row is the weights corresponding to the given mean face
	 * and eigenvector
	 */
	cv42::Matrix<float>			computeWeight(cv42::Matrix<float> &img, cv42::Matrix<float> const & eigv, cv42::Matrix<float> const & meanface);

	/**
	 * compareWeights expect "wcandidates" and "weights" to be matrixs where each row is
	 * a set of weights. It then use Eigenfaces::cmpWeightSquaredGap to determine for each
	 * row of "wcandidates" which row in "weights" is the closest and push the corresponding
	 * index in "matchIdx"
	 */
	void						compareWeights(cv42::Matrix<float> const & wcandidates, cv42::Matrix<float> const & weights, std::vector<int> & matchIdx);

	/**
	 * return the index of the closest row to "w" in "ws" by summing the squared gap of
	 * each row in "ws" with "w"
	 */
	int							cmpWeightSquaredGap(cv42::Vector<float> const & w, cv42::Matrix<float> const & ws);

public:
	Eigenface();
	~Eigenface();

	/**
	 * Given the images return by the SessionEig::getImages(), set in "sessiontrain" the
	 * corresponding eigenvectors, mean face, and weights for each images, using respectively
	 * SessionEig::setEigVectors(cv42::Matrix<float> eigenvectors),
	 * SessionEig::setMeanFace(cv42::Matrix<float> meanFace), and
	 * SessionEig::setWeights(cv42::Matrix<float> weights)
	 */
	void						train(SessionEig & sessiontrain);

	/**
	 * Given the parameter of the SessionEig attribute of SessionTest, fill the attributes
	 * SessionTest::_resultPaths and SessionTest::_resultLabels. It then return a
	 * std::vector<int> containing the list of index used to fill the result vector in SessionTest
	 */
	std::vector<int>			predict(SessionTest & s);
};


Eigenface::Eigenface(void)
{
	return ;
}

Eigenface::~Eigenface(void)
{
	return ;
}

void						Eigenface::train(SessionEig & s)
{
	cv42::Matrix <float>	m = s.getImages();
	// Compute mean
	cv42::Matrix<float>  meanFace;
	meanFace = m.mean2(1);

	// Soustraire la moyenne Mmean sur M pour obtenir Mtld
	cv42::Matrix<float> mtld = m - meanFace[0];

	// Covariance Mtld.transpose(), Mtld
	cv42::Matrix<float> mcov = mtld.transpose() * mtld;

	// QR eigenvalues sur Cov
	std::pair<cv42::Vector<float>, cv42::Matrix<float>> eigvs = mcov.eigenvv();

	// Récupérer les vrais vecteurs propres + normalisation
	cv42::Matrix<float> eigv = mtld * eigvs.second;

	// Récupérer la matrice de poids
	cv42::Matrix<float>  w;
	w = (mtld.transpose() * eigv);
	s.setEigVectors(eigv);
	s.setMeanFace(meanFace);
	s.setWeights(w);
}

std::vector<int>			Eigenface::predict(SessionTest & s)
{
	cv42::Matrix<float>			img = s.getImages();
	std::vector<std::string>	refPaths = *(s.getTrainingSession()->getPaths());
	std::vector<std::string>	refLabels = *(s.getTrainingSession()->getLabels());
	std::vector<std::string>	resultPaths;
	std::vector<std::string>	resultLabels;
	std::vector<int>			matchIdx;
	SessionEig					*sessEig = static_cast<SessionEig*>(s.getTrainingSession());
	cv42::Matrix<float>			imgweight = this->computeWeight(img, *(sessEig->getEigVectors()), *(sessEig->getMeanFace()));

	this->compareWeights(imgweight, *(sessEig->getWeights()), matchIdx);
	for (int i = 0; i < matchIdx.size(); ++i) {
		resultPaths.push_back(refPaths[matchIdx[i]]);
		resultLabels.push_back(refLabels[matchIdx[i]]);
	}
	s.setResultPaths(resultPaths);
	s.setResultLabels(resultLabels);
	return matchIdx;
}

	cv42::Matrix<float>			Eigenface::computeWeight(cv42::Matrix<float> &img, cv42::Matrix<float> const & eigv, cv42::Matrix<float> const & mf)
{
	return (((img - mf[0]).transpose() * eigv));
}

void						Eigenface::compareWeights(cv42::Matrix<float> const & wcandidate, cv42::Matrix<float> const & weights, std::vector<int> & matchIdx)
{
	for (int i = 0; i < wcandidate.getNrows(); ++i) {
		matchIdx.push_back(cmpWeightSquaredGap(wcandidate[i], weights));
	}
	return ;
}

int							Eigenface::cmpWeightSquaredGap(cv42::Vector<float> const & w, cv42::Matrix<float> const & ws)
{
	int		minIdx = 0;
	float	minVal = ((ws[0] - w) ^ 2).sum();
	float	val;

	for (int i = 1; i < ws.getNrows(); ++i)
	{
		val = ((ws[i] - w) ^ 2).sum();
		if (val < minVal)
		{
			minIdx = i;
			minVal = val;
		}
	}
	return (minIdx);
}

}

#endif
