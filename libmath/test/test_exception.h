#include <cxxtest/TestSuite.h>
#include <Matrix.hpp>
#include <Scalar.hpp>
#include <iostream>
#include <cstring>

class testException : public CxxTest::TestSuite{
	public:
		void test_invalidMatrixSize(void) {
			cv42::Matrix<int> m1(1,2);
			cv42::Matrix<int> m2(3,4);

			TS_ASSERT_THROWS(m1 + m2, cv42::Matrix<int>::InvalidMatrixSizeException);
			TS_ASSERT_THROWS(m1 - m2, cv42::Matrix<int>::InvalidMatrixSizeException);
			TS_ASSERT_THROWS(m1 % m2, cv42::Matrix<int>::InvalidMatrixSizeException);
			TS_ASSERT_THROWS(m1 / m2, cv42::Matrix<int>::InvalidMatrixSizeException);
			TS_ASSERT_THROWS(m1 ^ m2, cv42::Matrix<int>::InvalidMatrixSizeException);
			TS_ASSERT_THROWS(m1.mul(m2), cv42::Matrix<int>::InvalidMatrixSizeException);
			TS_ASSERT_THROWS(m1 * m2, cv42::Matrix<int>::InvalidMatrixSizeException);
			try {
				m1 + m2;
			} catch (std::exception & e) {
				TS_ASSERT(strcmp("Wise operation invalid matrix size: [1 x 2] vs [3 x 4]", e.what()) == 0);
			}
			try {
				m1.determinant();
			} catch (std::exception & e) {
				TS_ASSERT(strcmp("Determinant calculation: [1 x 2]", e.what()) == 0);
			}
			try {
				m1.trace();
			} catch (std::exception & e) {
				TS_ASSERT(strcmp("Trace calculation: [1 x 2]", e.what()) == 0);
			}
			return ;
		}
};
