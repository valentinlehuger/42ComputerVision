#ifndef SESSION_HPP
#define SESSION_HPP

#include <cstdlib>
#include <string>
#include <csvReader.hpp>
#include <Matrix.hpp>
#include <Img.hpp>
#include <exception>

class Session
{
public:

	Session(void);
	Session(std::string csvPath);
	~Session(void);

	std::string&				getSessionId(void);
	std::string&				getCsvPath(void);

	/**
	 * Return a matrix where each column is an image given by _csvPath, in the same order.
	 */
	cv42::Matrix<float>			getImages(void);

	void						setSessionId(std::string s_id);
	void						setCsvPath(std::string csvPath);

	void						setPaths(std::vector<std::string> *paths);
	void						setLabels(std::vector<std::string> *labels);

	std::vector<std::string>	*getPaths(void) const;
	std::vector<std::string>	*getLabels(void) const;

  class NoEnvVar : public std::exception
  {
  public:
    NoEnvVar(void);
    ~NoEnvVar(void);
    virtual const char *what() const throw()
    {
      return ("An Environment variable needed is unset.");
    }
};

protected:

	std::string	_id;
	std::string	_csvPath;
	std::vector<std::string>			*_paths;
	std::vector<std::string>			*_labels;
	std::string							_cvDir;

	/**
	 * Core function of Session::getImages(void)
	 */
	cv42::Matrix<float>	stackImgsVector(std::vector<std::string> const & paths, int cols, int rows) const;


};

Session::Session(void) {
  return ;
}

Session::Session(std::string csvPath) : _csvPath(csvPath)
{
	if (!getenv("CV_DIR"))
		throw NoEnvVar();

	_cvDir = std::string(getenv("CV_DIR"));

	_csvPath = _cvDir + "/" + _csvPath;

	_paths = new std::vector<std::string>();
	_labels = new std::vector<std::string>();

	CsvReader cr(_csvPath);
	std::vector<std::string> result = cr.getNextLine();
	if (result[0] != "path" || result[1] != "label")
	{
	  std::cout << "Warning: wrong format of csv (" << csvPath << ")." << std::endl;
	  return ;
	}
	result = cr.getNextLine();

	if (result.empty())
		return ;

	while (!result.empty())
	{
	  _paths->push_back(result[0]);
	  _labels->push_back(result[1]);
	  result = cr.getNextLine();
	}
}

Session::~Session(void) {
  return ;
}

std::string&	Session::getSessionId(void)
{
  return _id;
}

std::string&	Session::getCsvPath(void)
{
  return _csvPath;
}

void		Session::setCsvPath(std::string csvPath)
{
  _csvPath = csvPath;
}

void		Session::setSessionId(std::string s_id)
{
  _id = s_id;
}

cv42::Matrix<float>	Session::getImages(void) { // imgPaths should be loaded via a DBI instance, using DBI.getImagePaths(id, imgPaths)
	cv42::Matrix<float>			imgzero;

	std::string pathImgZero = _cvDir + "/front/" + (*_paths)[0];
	imgzero = cv42::openImg(pathImgZero.c_str());
	return (this->stackImgsVector((*_paths), static_cast<int>((*_paths).size()), imgzero.getNrows() * imgzero.getNcols()));
}

cv42::Matrix<float>	Session::stackImgsVector(std::vector<std::string> const & paths, int cols, int rows) const
{
	cv42::Matrix<float>	mtxImgs(cols, rows);
	cv42::Matrix<float>	mtxImg;
	for(int i = 0; i != cols; ++i) {
		mtxImg = cv42::openImg((_cvDir + "/front/" + paths[i]).c_str());
		mtxImgs[i] = mtxImg.toVector();
	}
	return (mtxImgs.transpose());
}

void				Session::setPaths(std::vector<std::string> *paths) {
  _paths = paths;
}
void				Session::setLabels(std::vector<std::string> *labels) {
  _labels = labels;
}

std::vector<std::string>	*Session::getPaths(void) const {
  return _paths;
}

std::vector<std::string>	*Session::getLabels(void) const {
  return _labels;
}

Session::NoEnvVar::NoEnvVar(void) : std::exception()
{
  return ;
}

Session::NoEnvVar::~NoEnvVar(void)
{
  return ;
}


#endif
