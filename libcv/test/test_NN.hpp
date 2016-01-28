#include <cxxtest/TestSuite.h>
#include <NN.hpp>
#include <vector>
#include <iostream>
#include <Img.hpp>

class testNN : public CxxTest::TestSuite{
	public:
	void test_known_image(void) {
		cv42::NN		neuralnet("front/testcsv/att00_5facestrain.csv", 100, 2, 0);

		neuralnet.train();

		SessionTest				sessionTest("front/testcsv/att00_5facesvalidation.csv", &neuralnet);
		neuralnet.predict(sessionTest);
		TS_ASSERT(true);
		}
};
