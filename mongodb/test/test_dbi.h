#include <cxxtest/TestSuite.h>
#include <SessionEig.hpp>
#include <Eigenface.hpp>
#include <SessionTest.hpp>
#include <dbInteractions.hpp>
#include <vector>
#include <iostream>

class testSession : public CxxTest::TestSuite{
	public:
		void	test_DBI_store_get_sessionEig(void) {

			DbInteractions				DBI("test");
			DBI.clearDb();
			SessionEig					sessionEig0("front/testcsv/att00_5facestrain.csv");
			SessionEig					sessionEig1("front/testcsv/att00_5facestrain.csv");
			cv42::Matrix<float>			eigvFake({
					cv42::Vector<float>({1.5,	2,	3,	4}),
					cv42::Vector<float>({5,	6,	7,	8}),
					cv42::Vector<float>({9,	10,	11,	12}),
					cv42::Vector<float>({13,	14.6,	15,	16}),
					cv42::Vector<float>({17,	18,	19,	20})
					});
			cv42::Matrix<float>			mfFake({
					cv42::Vector<float>({21,	22,	23,	24, 25}),
					});
			cv42::Matrix<float>			weightFake({
					cv42::Vector<float>({26,	-27,	28,	29}),
					cv42::Vector<float>({30,	31,	32,	33}),
					cv42::Vector<float>({34,	35,	36.3,	37}),
					cv42::Vector<float>({38,	39,	40,	41}),
					});

			sessionEig0.setEigVectors(eigvFake);
			sessionEig0.setMeanFace(mfFake);
			sessionEig0.setWeights(weightFake);
			DBI.store(sessionEig0);

			DBI.getSession(sessionEig1);

			TS_ASSERT(*(sessionEig0.getEigVectors()) == *(sessionEig1.getEigVectors()));
			TS_ASSERT(*(sessionEig0.getMeanFace()) == *(sessionEig1.getMeanFace()));
			TS_ASSERT(*(sessionEig0.getWeights()) == *(sessionEig1.getWeights()));

			std::vector<std::string>	*path0 = sessionEig0.getPaths();
			std::vector<std::string>	*path1 = sessionEig1.getPaths();
			std::vector<std::string>	*label0 = sessionEig0.getLabels();
			std::vector<std::string>	*label1 = sessionEig1.getLabels();

			TS_ASSERT(path0->size() == label0->size());
			TS_ASSERT(path0->size() == label1->size());

			DBI.clearDb();
			return ;
		}
};
