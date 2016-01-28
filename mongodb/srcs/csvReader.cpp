#include <csvReader.hpp>
#include <iostream>

CsvReader::CsvReader(void): _is(NULL)
{
  return ;
}

CsvReader::CsvReader(std::string path): _path(path), _is(NULL)
{
  if (_fb.open (_path.c_str(),std::ios::in))
    _is.rdbuf(&_fb);
  else
  {
    std::cout << "File doesn't open correctly." << std::endl;
    throw CsvReader::OpenCsvFail();
  }
  return ;
}

CsvReader::~CsvReader(void)
{
  _fb.close();
  return ;
}

CsvReader::CsvReader(CsvReader const &src): _is(NULL)
{
  *this = src;
  return ;
}

CsvReader	&CsvReader::operator=(CsvReader const &rhs)
{
  _path = rhs.getPath();
  return *this;
}

std::vector<std::string>	CsvReader::getNextLine(void)
{
  std::vector<std::string>	result;
  std::string			line;
  std::getline(_is, line);

  std::stringstream		lineStream(line);
  std::string			cell;

  while(std::getline(lineStream, cell, ',')) {
    result.push_back(cell);
  }

  return (result);
}

std::string			CsvReader::getPath(void) const
{
  return _path;
}

CsvReader::OpenCsvFail::OpenCsvFail(void) : std::exception()
{
  return ;
}

CsvReader::OpenCsvFail::~OpenCsvFail(void)
{
  return ;
}
