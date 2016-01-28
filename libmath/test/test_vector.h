#ifndef TEST_VECTOR_H
#define TEST_VECTOR_H

#include <Vector.hpp>
#include <Matrix.hpp>

class TestVector : public CxxTest::TestSuite
{
	public:
		void test_norme(void)
		{
			cv42::Vector<float> vec1({1, 2, 3});
			cv42::Vector<float> vec2(vec1.normalization());
			TS_ASSERT(abs(vec1.norm() - sqrt(14)) < 0.0001);
			TS_ASSERT(abs(vec2.norm() - 1.0) < 1e-6);
			
		}

		void test_mean(void)
		{
			cv42::Vector<float> v({1,2,3,4});
			TS_ASSERT_LESS_THAN(abs(v.mean() - 2.5) , 1e-6);
		}

		void test_householder(void)
		{
			cv42::Vector<double> vec1({154.65641026, 33.08755139, -2.62377524});
			cv42::Matrix<double> expect1({cv42::Vector<double>({-0.97773662, -0.20917924, 0.01658749}), \
										 cv42::Vector<double>({-0.20917924, 0.97787574, 0.00175441}), \
										 cv42::Vector<double>({0.01658749, 0.00175441, 0.99986088})});
			cv42::Matrix<double> result1;

			result1 = vec1.householder();
			for (int row = 0; row < expect1.getNrows(); row++) {
				for (int col = 0; col < expect1.getNcols(); col++) {
					TS_ASSERT(expect1[row][col] - result1[row][col] < 0.0001);
				}
			}

			cv42::Vector<double> vec2({25, 95, -10});
			cv42::Matrix<double> expect2({cv42::Vector<double>({-0.25318484, -0.9621024, 0.10127394}), \
										  cv42::Vector<double>({-0.9621024, 0.26136912, 0.07775062}), \
										  cv42::Vector<double>({0.10127394, 0.07775062, 0.99181572})});
			cv42::Matrix<double> result2;

			result2 = vec2.householder();
			for (int row = 0; row < expect2.getNrows(); row++) {
				for (int col = 0; col < expect2.getNcols(); col++) {
					TS_ASSERT(expect2[row][col] - result2[row][col] < 0.0001);
				}
			}

			cv42::Vector<double> vec3({-3.41966750e+01, 1.26591859e-30});
			cv42::Matrix<double> expect3({cv42::Vector<double>({-1.00000000e+00, 3.70187625e-32}), \
										  cv42::Vector<double>({3.70187625e-32, 1.00000000e+00})});
			cv42::Matrix<double> result3;

			result3 = vec3.householder();
			for (int row = 0; row < expect3.getNrows(); row++) {
				for (int col = 0; col < expect3.getNcols(); col++) {
					TS_ASSERT(expect3[row][col] - result3[row][col] < 0.0001);
				}
			}
			return ;
		}
};

#endif /* !TEST_VECTOR_H */
