#include <cxxtest/TestSuite.h>
#include <Eigenface.hpp>
#include <vector>
#include <iostream>
#include <Img.hpp>

class testEigenface : public CxxTest::TestSuite{
	public:
		void test_known_image(void) {
			SessionEig					sessionEig("front/testcsv/att00_5facestrain.csv");
			cv42::Eigenface				eigenface;

			eigenface.train(sessionEig);

			SessionTest				sessionTest("front/testcsv/att00_5facestrain.csv", &sessionEig);

			eigenface.predict(sessionTest);

			std::vector<std::string>	result = sessionTest.getResultLabels();
			std::vector<std::string>	*expect = sessionTest.getLabels();

			for (int i = 0; i < result.size(); ++i)
				TS_ASSERT((*expect)[i] == result[i]);
			return ;
		}

		void test_unknown_image(void) {
			SessionEig					sessionEig("front/testcsv/att00_5facestrain.csv");
			cv42::Eigenface				eigenface;

			eigenface.train(sessionEig);

			SessionTest				sessionTest("front/testcsv/att00_5facesvalidation.csv", &sessionEig);

			eigenface.predict(sessionTest);

			std::vector<std::string>	result = sessionTest.getResultLabels();
			std::vector<std::string>	*expect = sessionTest.getLabels();

			for (int i = 0; i < result.size(); ++i)
				TS_ASSERT((*expect)[i] == result[i]);
			return ;
		}
};
