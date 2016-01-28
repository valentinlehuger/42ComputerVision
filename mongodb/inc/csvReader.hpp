#ifndef CSVREADER_HPP
#define CSVREADER_HPP

#include <vector>
#include <fstream>
#include <sstream>
#include <istream>
#include <string>

class CsvReader {

private:
  std::string	_path;
  std::filebuf	_fb;
  std::istream	_is;

public:
  CsvReader(void);
  CsvReader(std::string path);
  ~CsvReader(void);
  CsvReader(CsvReader const &src);
  CsvReader	&operator=(CsvReader const &rhs);

  std::vector<std::string>	getNextLine(void);
  std::string			getPath(void) const;

  class OpenCsvFail : std::exception
  {
  public:
    OpenCsvFail(void);
    ~OpenCsvFail(void);
    virtual const char *what() const throw()
    {
      return ("The csv file failed to open.");
    }
  };


};

#endif
