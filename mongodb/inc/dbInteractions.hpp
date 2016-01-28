#ifndef DBINTERACTIONS_HPP
#define DBINTERACTIONS_HPP

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include "mongo/client/dbclient.h" // for the driver
#include <stdlib.h> /* getenv */
#include <string>
#include <exception>

#include <Matrix.hpp>
#include <Vector.hpp>

#include <SessionEig.hpp>
#include <SessionTest.hpp>
#include <NN.hpp>

class DbInteractions
{
public:
        DbInteractions(std::string dbName);
        ~DbInteractions(void);

    /*
    From a csv_path in second parameter, this functions fills the
    eignvectors, weights and meanFace fields of SessionEig instance.
    */
  bool      getSession(SessionEig &s);

   /* These functions store a session into db
   */
  bool      store(SessionEig &s);
  bool      store(SessionTest &s);
  bool      store(cv42::NN &s);
  void      clearDb(void);

private:
  mongo::DBClientConnection   *_c;
  std::string       _databaseName;


    /* These 3 functions create the corresponding dbObject, respectively
        from a cv42::Vector, a cv42::Matrix and a std::vector
    */
  template <typename T>
  bool        generateDbVector(mongo::BSONObj &dbMat, cv42::Vector<T> &vec);
  template <typename T>
  bool        generateDbMatrix(mongo::BSONObj &dbMat, cv42::Matrix<T> &mat);
  bool        generateDbArray(mongo::BSONArray &dbArr, std::vector<std::string> &arr);

    /* These 3 functions decompress the corresponding dbObject, respectively
        into a cv42::Vector, a cv42::Matrix and a std::vector
    */
  template <typename T>
  bool      decompressDbMatrix(cv42::Matrix<T> &mat, mongo::BSONObj &dbMat);
  template <typename T>
  bool      decompressDbVector(cv42::Vector<T> &vec, mongo::BSONObj &dbVec);
  bool      decompressDbArray(std::vector<std::string> &strVec, mongo::BSONObj dbStrVec);

    /* This function logs the last test session into the server file
        passed in first parameter.
     */

  void      writeLastSessionFile(std::string filePath, std::string csvPath, std::string id);

  class ObjectNotCorrectlyFormatted : std::exception
  {
  public:
    ObjectNotCorrectlyFormatted(void);
    ~ObjectNotCorrectlyFormatted(void);
    virtual const char *what() const throw()
    {
      return ("Object not well formatted.");
    }
  };

  class EmptyField : std::exception
  {
  public:
    EmptyField(void);
    ~EmptyField(void);
    virtual const char *what() const throw()
    {
      return ("There is a empty field.");
    }
  };

  class SessionAlreadyExists : public std::exception
  {
  public:
    SessionAlreadyExists(void);
    ~SessionAlreadyExists(void);
    virtual const char *what() const throw()
    {
      return ("The session already exists.");
    }
  };


};


DbInteractions::DbInteractions(std::string dbName): _c(new mongo::DBClientConnection()),
                  _databaseName(dbName)
{
  mongo::client::initialize();
  _c->connect("localhost");
  return ;
}

DbInteractions::~DbInteractions(void)
{
  return ;
}

bool  DbInteractions::getSession(SessionEig &s) {

  try {
    std::auto_ptr<mongo::DBClientCursor>  cursor = _c->query(_databaseName + ".session_training", MONGO_QUERY("csv_path" << s.getCsvPath()));
    if (cursor->more())
    {
      mongo::BSONObj p = cursor->next();

      try {
        mongo::BSONObj eigVecObj = p.getObjectField("eigenvectors");
        mongo::BSONObj meanFaceObj = p.getObjectField("mean_face");
        mongo::BSONObj weightsObj = p.getObjectField("weights");
        mongo::BSONObj pathsObj = p.getObjectField("image_paths");
        mongo::BSONObj labelsObj = p.getObjectField("labels");

        cv42::Matrix<float> *eigVec = new cv42::Matrix<float>(eigVecObj.getIntField("height"), eigVecObj.getIntField("width"));
        cv42::Matrix<float> *weights = new cv42::Matrix<float>(weightsObj.getIntField("height"), weightsObj.getIntField("width"));
        cv42::Matrix<float> *meanFace = new cv42::Matrix<float>(meanFaceObj.getIntField("height"), meanFaceObj.getIntField("width"));
        std::vector<std::string> *labels = new std::vector<std::string>();
        std::vector<std::string> *paths = new std::vector<std::string>();

        try {
          decompressDbMatrix(*eigVec, eigVecObj);
          decompressDbMatrix(*weights, weightsObj);
          decompressDbMatrix(*meanFace, meanFaceObj);
          decompressDbArray(*paths, pathsObj);
          decompressDbArray(*labels, labelsObj);

        } catch (ObjectNotCorrectlyFormatted &e) {
          std::cout << "Try to decompress a db object not well formatted." << std::endl;
          return (false);
        }

        s.setEigVectors(eigVec);
        s.setMeanFace(meanFace);
        s.setWeights(weights);
        s.setPaths(paths);
        s.setLabels(labels);

        return (true);

      } catch (EmptyField &e) {
        std::cout << "There is an empty field in the sessionEig wanted." << std::endl;
        return (false);
      }

    }
    else {
      std::cout << "This session (" << s.getCsvPath() << ") doesn't exist." << std::endl;
      return (false);
    }
  } catch (const mongo::DBException &e) {
    std::cout << "Error to get session : " << e.what() << std::endl;
    return (false);
  }
}

bool        DbInteractions::store(SessionEig &s) {

  mongo::BSONObj    eigVecObj;
  mongo::BSONObj    meanFaceObj;
  mongo::BSONObj    weightsObj;
  mongo::BSONArray  pathsObj;
  mongo::BSONArray  labelsObj;

  if (s.getEigVectors())
    generateDbMatrix(eigVecObj, *s.getEigVectors());
  if (s.getMeanFace())
    generateDbMatrix(meanFaceObj, *s.getMeanFace());
  if (s.getWeights())
    generateDbMatrix(weightsObj, *s.getWeights());
  generateDbArray(pathsObj, *s.getPaths());
  generateDbArray(labelsObj, *s.getLabels());


  try {
    std::auto_ptr<mongo::DBClientCursor>  cursor = _c->query(_databaseName + ".session_training", MONGO_QUERY("csv_path" << s.getCsvPath()));
    if (cursor->more())
    {
      throw SessionAlreadyExists();

      // mongo::BSONObj p = BSON("csv_path" << s.getCsvPath() << "image_paths" << pathsObj << "labels" << labelsObj << "eigenvectors" << eigVecObj << "mean_face" << meanFaceObj << "weights" << weightsObj);
      // _c->update(_databaseName + ".session_training", MONGO_QUERY("csv_path" << s.getCsvPath()), p);
    } else {

      mongo::BSONObj p = BSON(mongo::GENOID << "csv_path" << s.getCsvPath() << "image_paths" << pathsObj << "labels" << labelsObj << "eigenvectors" << eigVecObj << "mean_face" << meanFaceObj << "weights" << weightsObj);
      _c->insert(_databaseName + ".session_training", p);

      mongo::BSONElement oi;

      p.getObjectID(oi);

      s.setSessionId(oi.__oid().toString());

      return (true);
    }
  } catch (const mongo::DBException &e) {
    std::cout << "Error to store session : " << e.what() << std::endl;
    return (false);
  }
  return (false);
}

bool        DbInteractions::store(cv42::NN &s) {

  mongo::BSONArray  pathsObj;
  mongo::BSONArray  labelsObj;

  generateDbArray(pathsObj, *s.getPaths());
  generateDbArray(labelsObj, *s.getLabels());

  try {
    std::auto_ptr<mongo::DBClientCursor>  cursor = _c->query(_databaseName + ".session_training", MONGO_QUERY("csv_path" << s.getCsvPath()));
    if (cursor->more())
      throw SessionAlreadyExists();
    else {
      mongo::BSONObj p = BSON(mongo::GENOID << "csv_path" << s.getCsvPath() << "image_paths" << pathsObj << "labels" << labelsObj);
      _c->insert(_databaseName + ".session_training", p);

      mongo::BSONElement oi;
      p.getObjectID(oi);
      s.setSessionId(oi.__oid().toString());
      return (true);
    }
  } catch (const mongo::DBException &e) {
    std::cout << "Error to store session : " << e.what() << std::endl;
    return (false);
  }
  return (false);
}


bool    DbInteractions::store(SessionTest &s) {
  mongo::BSONArray       image_paths;
  mongo::BSONArray       result_paths;
  mongo::BSONArray       result_labels;
  mongo::BSONArray       labelsObj;

  generateDbArray(image_paths, *s.getPaths());
  generateDbArray(labelsObj, *s.getLabels());
  generateDbArray(result_paths, s.getResultPaths());
  generateDbArray(result_labels, s.getResultLabels());

  try {
    std::auto_ptr<mongo::DBClientCursor>  cursor = _c->query(_databaseName + ".session_training", MONGO_QUERY("csv_path" << s.getCsvPath()));
    if (cursor->more()) {
      throw SessionAlreadyExists();
    }
    else {
      mongo::BSONObj p = BSON(mongo::GENOID << "csv_path" << s.getCsvPath() << "session_training_id" << mongo::OID(s.getTrainingSession()->getSessionId()) << "image_paths" << image_paths << "labels" << labelsObj << "result_paths" << result_paths << "result_labels" << result_labels);

      _c->insert(_databaseName + ".session_test", p);

      mongo::BSONElement oi;
      p.getObjectID(oi);
      s.setSessionId(oi.__oid().toString());

      std::string dir_path = std::string(getenv("CV_DIR"));
      writeLastSessionFile(dir_path + "/front/lastTestSession.txt", s.getCsvPath(), s.getSessionId());

    }
  } catch (const mongo::DBException &e) {
    std::cout << "Error to store session : " << e.what() << std::endl;
    return (false);
  }


  return (true);
}


template <typename T>
bool    DbInteractions::generateDbVector(mongo::BSONObj &dbVec, cv42::Vector<T> &vec)
{
  mongo::BSONArrayBuilder b;
  mongo::BSONArray        arr;

  int size = vec.getSize();

  for (int i = 0; i < size; i++)
  {
    b.append(vec[i]);
  }

  arr = b.arr();

  dbVec = BSON("size" << size << "data" << arr);

  return (true);
}

template <typename T>
bool    DbInteractions::generateDbMatrix(mongo::BSONObj &dbMat, cv42::Matrix<T> &mat)
{
  mongo::BSONArrayBuilder b;
  mongo::BSONArray        arr;

  int height = mat.getNrows();
  int width = mat.getNcols();

  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
      b.append(mat[i][j]);
  }

  arr = b.arr();

  dbMat = BSON("height" << height << "width" << width << "data" << arr);

  return (true);
}

bool    DbInteractions::generateDbArray(mongo::BSONArray &dbArr, std::vector<std::string> &arr)
{
  mongo::BSONArrayBuilder b;

  for (int i = 0; i < arr.size(); i++)
    b.append(arr[i]);

  dbArr = b.arr();

  return (true);
}

template <typename T>
bool DbInteractions::decompressDbVector(cv42::Vector<T> &vec, mongo::BSONObj &dbVec)
{
  int size = dbVec.getIntField("size");

  if (size == 0)
    throw DbInteractions::ObjectNotCorrectlyFormatted();

  mongo::BSONArray  arr(dbVec.getObjectField("data"));

  for (int i = 0; i < size; i++) {
    vec[i] = arr[i].Double();
  }
  return (true);
}

template <typename T>
bool  DbInteractions::decompressDbMatrix(cv42::Matrix<T> &mat, mongo::BSONObj &dbMat)
{

  int height = dbMat.getIntField("height");
  int width = dbMat.getIntField("width");

  if (height == 0 || width == 0)
    throw DbInteractions::ObjectNotCorrectlyFormatted();

  mongo::BSONArray  arr(dbMat.getObjectField("data"));

  for (int i = 0; i < height * width; i++) {
    mat[i / width][ i % width] = arr[i].Double();
  }
  return (true);
}

bool  DbInteractions::decompressDbArray(std::vector<std::string> &strVec, mongo::BSONObj dbStrVec)
{
  BSONForEach(e, dbStrVec) {
    strVec.push_back(e.String());
  }


  return (true);
}


void      DbInteractions::writeLastSessionFile(std::string filePath, std::string csvPath, std::string id) {
  time_t now = time(0);

  std::ofstream logFile;
  logFile.open (filePath, std::ios_base::app);
  logFile << id << "," << csvPath << "," << std::string(ctime(&now));
  logFile.close();
}

void      DbInteractions::clearDb(void)
{
  _c->remove(_databaseName + ".session_training", mongo::Query());
  _c->remove(_databaseName + ".session_test", mongo::Query());
}

DbInteractions::ObjectNotCorrectlyFormatted::ObjectNotCorrectlyFormatted(void) : std::exception()
{
  return ;
}

DbInteractions::ObjectNotCorrectlyFormatted::~ObjectNotCorrectlyFormatted(void)
{
  return ;
}

DbInteractions::EmptyField::EmptyField(void) : std::exception()
{
  return ;
}

DbInteractions::EmptyField::~EmptyField(void)
{
  return ;
}

DbInteractions::SessionAlreadyExists::SessionAlreadyExists(void) : std::exception()
{
  return ;
}

DbInteractions::SessionAlreadyExists::~SessionAlreadyExists(void)
{
  return ;
}

#endif
