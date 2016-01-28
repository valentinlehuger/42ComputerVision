#ifndef SessionTest_HPP
#define SessionTest_HPP

#include <Session.hpp>

class SessionTest : public Session
{
public:

	SessionTest(void);
	SessionTest(std::string testPath, Session *trainingSession);

	~SessionTest(void);

	std::vector<std::string>	&getResultPaths(void);
	std::vector<std::string>	&getResultLabels(void);
	Session						*getTrainingSession(void);

	void						setResultPaths(std::vector<std::string> rPaths);
	void						setResultLabels(std::vector<std::string> rLabels);

private:
	Session					*_trainingSession;
	std::vector<std::string>	_resultPaths;
	std::vector<std::string>	_resultLabels;
};


SessionTest::SessionTest(void) {
  return;
}

SessionTest::SessionTest(std::string testPath, Session *trainingSession)
		: Session(testPath), _trainingSession(trainingSession)
{
  return ;
}

SessionTest::~SessionTest(void)
{
  return ;
}

std::vector<std::string>		&SessionTest::getResultPaths(void) {
  return _resultPaths;
}

std::vector<std::string>		&SessionTest::getResultLabels(void) {
  return _resultLabels;
}

Session							*SessionTest::getTrainingSession(void) {
  return _trainingSession;
}

void							SessionTest::setResultPaths(std::vector<std::string> rPaths)
{
  _resultPaths = rPaths;
}

void							SessionTest::setResultLabels(std::vector<std::string> rLabels)
{
  _resultLabels = rLabels;
}

#endif
