#include <NN.hpp>

class testNN : public CxxTest::TestSuite{
	public:
		void test_compilation(void) {
			cv42::NN blop("", 5, 1, 1);
		}
};
