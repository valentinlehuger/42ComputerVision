#include <cxxtest/TestSuite.h>
#include <Matrix.hpp>
#include <Scalar.hpp>

#define Si cv42::Scalar<int>
#define Sf cv42::Scalar<float>

class testWiseOp : public CxxTest::TestSuite{
	public:
		/**************************BASIC44**************************/
		void test_equal_basic44(void) {
			/* std::cout << std::endl << "Operator == test basic44" << std::endl; */
			cv42::Matrix<int> m1(2,2);
			cv42::Matrix<int> m2(2,2);

			m1[0][0] = 1;
			m1[0][1] = 2;
			m1[1][0] = 3;
			m1[1][1] = 4;
			m2[0][0] = 1;
			m2[0][1] = 2;
			m2[1][0] = 3;
			m2[1][1] = 4;
			TS_ASSERT(m1 == m2);
			return ;
		}

		void test_plus_basic44(void) {
			/* std::cout << std::endl << "Operator + test basic44" << std::endl; */
			cv42::Matrix<int> m1(2,2);
			cv42::Matrix<int> m2(2,2);
			cv42::Matrix<int> m3(2,2);

			m1[0][0] = 1;
			m1[0][1] = 2;
			m1[1][0] = 3;
			m1[1][1] = 4;

			m2[0][0] = 2;
			m2[0][1] = 0;
			m2[1][0] = -1;
			m2[1][1] = 1;

			m3[0][0] = 3;
			m3[0][1] = 2;
			m3[1][0] = 2;
			m3[1][1] = 5;

			//std::cout << m1 << " + " << m2 << " should result in" << m3 << std::endl;
			TS_ASSERT((m1 + m2) == m3);
			return ;
		}
		
		void test_minus_basic44(void) {
			/* std::cout << std::endl << "Operator - test basic44" << std::endl; */
			cv42::Matrix<int> m1(2,2);
			cv42::Matrix<int> m2(2,2);
			cv42::Matrix<int> m3(2,2);

			m1[0][0] = 1;
			m1[0][1] = 2;
			m1[1][0] = 3;
			m1[1][1] = 4;

			m2[0][0] = 2;
			m2[0][1] = 0;
			m2[1][0] = -1;
			m2[1][1] = 1;

			m3[0][0] = -1;
			m3[0][1] = 2;
			m3[1][0] = 4;
			m3[1][1] = 3;

			//std::cout << m1 << " + " << m2 << " should result in" << m3 << std::endl;
			TS_ASSERT((m1 - m2) == m3);
			return ;
		}

		void test_div_basic44(void) {
			/* std::cout << std::endl << "Operator / test basic44" << std::endl; */
			cv42::Matrix<float> m1(2,2);
			cv42::Matrix<float> m2(2,2);
			cv42::Matrix<float> m3(2,2);

			m1[0][0] = 1;
			m1[0][1] = 2;
			m1[1][0] = 3;
			m1[1][1] = 4;

			m2[0][0] = 2;
			m2[0][1] = 4;
			m2[1][0] = -1;
			m2[1][1] = 1;

			m3[0][0] = m1[0][0] / m2[0][0];
			m3[0][1] = m1[0][1] / m2[0][1];
			m3[1][0] = m1[1][0] / m2[1][0];
			m3[1][1] = m1[1][1] / m2[1][1];

			//std::cout << m1 << " / " << m2 << " should result in" << m3 << std::endl;
			TS_ASSERT((m1 / m2) == m3);
			return ;
		}

		void test_mod_basic44(void) {
			/* std::cout << std::endl << "Operator % test basic44" << std::endl; */
			cv42::Matrix<int> m1(2,2);
			cv42::Matrix<int> m2(2,2);
			cv42::Matrix<int> m3(2,2);

			m1[0][0] = 1;
			m1[0][1] = 2;
			m1[1][0] = 3;
			m1[1][1] = 4;

			m2[0][0] = 2;
			m2[0][1] = 4;
			m2[1][0] = -1;
			m2[1][1] = 1;

			m3[0][0] = m1[0][0] % m2[0][0];
			m3[0][1] = m1[0][1] % m2[0][1];
			m3[1][0] = m1[1][0] % m2[1][0];
			m3[1][1] = m1[1][1] % m2[1][1];

			//std::cout << m1 << " % " << m2 << " should result in" << m3 << std::endl;
			TS_ASSERT((m1 % m2) == m3);
			return ;
		}

		void test_pow_basic44(void) {
			/* std::cout << std::endl << "Operator ^ test basic44" << std::endl; */
			cv42::Matrix<int> m1(2,2);
			cv42::Matrix<int> m2(2,2);
			cv42::Matrix<int> m3(2,2);

			m1[0][0] = 1;
			m1[0][1] = 2;
			m1[1][0] = 3;
			m1[1][1] = 4;

			m2[0][0] = 2;
			m2[0][1] = 4;
			m2[1][0] = -1;
			m2[1][1] = 1;

			m3[0][0] = pow(m1[0][0], m2[0][0]);
			m3[0][1] = pow(m1[0][1], m2[0][1]);
			m3[1][0] = pow(m1[1][0], m2[1][0]);
			m3[1][1] = pow(m1[1][1], m2[1][1]);

			//std::cout << m1 << " ^ " << m2 << " should result in" << m3 << std::endl;
			TS_ASSERT((m1 ^ m2) == m3);
			return ;
		}

		void test_mul_basic44(void) {
			/* std::cout << std::endl << "Mul method (wise product) test basic44" << std::endl; */
			cv42::Matrix<int> m1(2,2);
			cv42::Matrix<int> m2(2,2);
			cv42::Matrix<int> m3(2,2);

			m1[0][0] = 1;
			m1[0][1] = 2;
			m1[1][0] = 3;
			m1[1][1] = 4;

			m2[0][0] = 2;
			m2[0][1] = 4;
			m2[1][0] = -1;
			m2[1][1] = 1;

			m3[0][0] = m1[0][0] * m2[0][0];
			m3[0][1] = m1[0][1] * m2[0][1];
			m3[1][0] = m1[1][0] * m2[1][0];
			m3[1][1] = m1[1][1] * m2[1][1];

			//std::cout << m1 << " .* " << m2 << " should result in" << m3 << std::endl;
			TS_ASSERT(m1.mul(m2) == m3);
			return ;
		}
		/**************************!!!BASIC44!!!**************************/


		/**************************NULL44**************************/
		void test_equal_null44(void) {
			/* std::cout << std::endl << "Operator == test null44" << std::endl; */
			cv42::Matrix<int> m1(2,2);
			cv42::Matrix<int> m2(2,2);

			m1[0][0] = 0;
			m1[0][1] = 0;
			m1[1][0] = 0;
			m1[1][1] = 0;
			m2[0][0] = 0;
			m2[0][1] = 0;
			m2[1][0] = 0;
			m2[1][1] = 0;
			TS_ASSERT(m1 == m2);
			return ;
		}

		void test_plus_null44(void) {
			/* std::cout << std::endl << "Operator + test null44" << std::endl; */
			cv42::Matrix<int> m1(2,2);
			cv42::Matrix<int> m2(2,2);
			cv42::Matrix<int> m3(2,2);

			m1[0][0] = 0;
			m1[0][1] = 0;
			m1[1][0] = 0;
			m1[1][1] = 0;

			m2[0][0] = 0;
			m2[0][1] = 0;
			m2[1][0] = 0;
			m2[1][1] = 0;

			m3[0][0] = 0;
			m3[0][1] = 0;
			m3[1][0] = 0;
			m3[1][1] = 0;

			//std::cout << m1 << " + " << m2 << " should result in" << m3 << std::endl;
			TS_ASSERT((m1 + m2) == m3);
			return ;
		}

		void test_minus_null44(void) {
			/* std::cout << std::endl << "Operator - test null44" << std::endl; */
			cv42::Matrix<int> m1(2,2);
			cv42::Matrix<int> m2(2,2);
			cv42::Matrix<int> m3(2,2);

			m1[0][0] = 0;
			m1[0][1] = 0;
			m1[1][0] = 0;
			m1[1][1] = 0;

			m2[0][0] = 0;
			m2[0][1] = 0;
			m2[1][0] = 0;
			m2[1][1] = 0;

			m3[0][0] = 0;
			m3[0][1] = 0;
			m3[1][0] = 0;
			m3[1][1] = 0;

			//std::cout << m1 << " + " << m2 << " should result in" << m3 << std::endl;
			TS_ASSERT((m1 - m2) == m3);
			return ;
		}

		void test_div_null44(void) {
			/* std::cout << std::endl << "Operator / test null44" << std::endl; */
			cv42::Matrix<float> m1(2,2);
			cv42::Matrix<float> m2(2,2);
			cv42::Matrix<float> m3(2,2);

			m1[0][0] = 0;
			m1[0][1] = 0;
			m1[1][0] = 0;
			m1[1][1] = 0;

			m2[0][0] = 2;
			m2[0][1] = 4;
			m2[1][0] = -1;
			m2[1][1] = 1;

			m3[0][0] = m1[0][0] / m2[0][0];
			m3[0][1] = m1[0][1] / m2[0][1];
			m3[1][0] = m1[1][0] / m2[1][0];
			m3[1][1] = m1[1][1] / m2[1][1];

			//std::cout << m1 << " / " << m2 << " should result in" << m3 << std::endl;
			TS_ASSERT((m1 / m2) == m3);
			return ;
		}

		void test_mod_null44(void) {
			/* std::cout << std::endl << "Operator % test null44" << std::endl; */
			cv42::Matrix<int> m1(2,2);
			cv42::Matrix<int> m2(2,2);
			cv42::Matrix<int> m3(2,2);

			m1[0][0] = 0;
			m1[0][1] = 0;
			m1[1][0] = 0;
			m1[1][1] = 0;

			m2[0][0] = 2;
			m2[0][1] = 4;
			m2[1][0] = -1;
			m2[1][1] = 1;

			m3[0][0] = m1[0][0] % m2[0][0];
			m3[0][1] = m1[0][1] % m2[0][1];
			m3[1][0] = m1[1][0] % m2[1][0];
			m3[1][1] = m1[1][1] % m2[1][1];

			//std::cout << m1 << " % " << m2 << " should result in" << m3 << std::endl;
			TS_ASSERT((m1 % m2) == m3);
			return ;
		}

		void test_pow_null44(void) {
			/* std::cout << std::endl << "Operator ^ test null44" << std::endl; */
			cv42::Matrix<int> m1(2,2);
			cv42::Matrix<int> m2(2,2);
			cv42::Matrix<int> m3(2,2);

			m1[0][0] = 1;
			m1[0][1] = 2;
			m1[1][0] = 3;
			m1[1][1] = 4;

			m2[0][0] = 0;
			m2[0][1] = 0;
			m2[1][0] = 0;
			m2[1][1] = 0;

			m3[0][0] = pow(m1[0][0], m2[0][0]);
			m3[0][1] = pow(m1[0][1], m2[0][1]);
			m3[1][0] = pow(m1[1][0], m2[1][0]);
			m3[1][1] = pow(m1[1][1], m2[1][1]);

			//std::cout << m1 << " ^ " << m2 << " should result in" << m3 << std::endl;
			TS_ASSERT((m1 ^ m2) == m3);
			return ;
		}

		void test_mul_null44(void) {
			/* std::cout << std::endl << "Mul method (wise product) test null44" << std::endl; */
			cv42::Matrix<int> m1(2,2);
			cv42::Matrix<int> m2(2,2);
			cv42::Matrix<int> m3(2,2);

			m1[0][0] = 0;
			m1[0][1] = 0;
			m1[1][0] = 0;
			m1[1][1] = 0;

			m2[0][0] = 0;
			m2[0][1] = 0;
			m2[1][0] = 0;
			m2[1][1] = 0;

			m3[0][0] = m1[0][0] * m2[0][0];
			m3[0][1] = m1[0][1] * m2[0][1];
			m3[1][0] = m1[1][0] * m2[1][0];
			m3[1][1] = m1[1][1] * m2[1][1];

			//std::cout << m1 << " .* " << m2 << " should result in" << m3 << std::endl;
			TS_ASSERT(m1.mul(m2) == m3);
			return ;
		}

		void test_equal_basic44_scalar(void) {
			/* std::cout << std::endl << "Operator == test basic44" << std::endl; */
			cv42::Matrix<Si> m1(2,2);
			cv42::Matrix<Si> m2(2,2);

			m1[0][0] = Si(1);
			m1[0][1] = Si(2);
			m1[1][0] = Si(3);
			m1[1][1] = Si(4);
			m2[0][0] = Si(1);
			m2[0][1] = Si(2);
			m2[1][0] = Si(3);
			m2[1][1] = Si(4);
			TS_ASSERT(m1 == m2);
			return ;
		}

		void test_plus_basic44_scalar(void) {
			/* std::cout << std::endl << "Operator + test basic44" << std::endl; */
			cv42::Matrix<Sf> m1(2,2);
			cv42::Matrix<Sf> m2(2,2);
			cv42::Matrix<Sf> m3(2,2);

			m1[0][0] = Sf(1);
			m1[0][1] = Sf(2);
			m1[1][0] = Sf(3);
			m1[1][1] = Sf(4);

			m2[0][0] = Sf(2);
			m2[0][1] = Sf(0);
			m2[1][0] = Sf(-1);
			m2[1][1] = Sf(1);

			m3[0][0] = Sf(3);
			m3[0][1] = Sf(2);
			m3[1][0] = Sf(2);
			m3[1][1] = Sf(5);

			//std::cout << m1 << " + " << m2 << " should result in" << m3 << std::endl;
			TS_ASSERT((m1 + m2) == m3);
			return ;
		}

		void test_minus_basic44_scalar(void) {
			/* std::cout << std::endl << "Operator - test basic44" << std::endl; */
			cv42::Matrix<Sf> m1(2,2);
			cv42::Matrix<Sf> m2(2,2);
			cv42::Matrix<Sf> m3(2,2);

			m1[0][0] = Sf(1);
			m1[0][1] = Sf(2);
			m1[1][0] = Sf(3);
			m1[1][1] = Sf(4);

			m2[0][0] = Sf(2);
			m2[0][1] = Sf(0);
			m2[1][0] = Sf(-1);
			m2[1][1] = Sf(1);

			m3[0][0] = Sf(-1);
			m3[0][1] = Sf(2);
			m3[1][0] = Sf(4);
			m3[1][1] = Sf(3);

			//std::cout << m1 << " + " << m2 << " should result in" << m3 << std::endl;
			TS_ASSERT((m1 - m2) == m3);
			return ;
		}

		void test_div_basic44_scalar(void) {
			/* std::cout << std::endl << "Operator / test basic44" << std::endl; */
			cv42::Matrix<Sf> m1(2,2);
			cv42::Matrix<Sf> m2(2,2);
			cv42::Matrix<Sf> m3(2,2);

			m1[0][0] = Sf(1);
			m1[0][1] = Sf(2);
			m1[1][0] = Sf(3);
			m1[1][1] = Sf(4);

			m2[0][0] = Sf(2);
			m2[0][1] = Sf(4);
			m2[1][0] = Sf(-1);
			m2[1][1] = Sf(1);

			m3[0][0] = Sf(m1[0][0] / m2[0][0]);
			m3[0][1] = Sf(m1[0][1] / m2[0][1]);
			m3[1][0] = Sf(m1[1][0] / m2[1][0]);
			m3[1][1] = Sf(m1[1][1] / m2[1][1]);

			//std::cout << m1 << " / " << m2 << " should result in" << m3 << std::endl;
			TS_ASSERT((m1 / m2) == m3);
			return ;
		}

		void test_mod_basic44_scalar(void) {
			/* std::cout << std::endl << "Operator % test basic44" << std::endl; */
			cv42::Matrix<Si> m1(2,2);
			cv42::Matrix<Si> m2(2,2);
			cv42::Matrix<Si> m3(2,2);

			m1[0][0] = Si(1);
			m1[0][1] = Si(2);
			m1[1][0] = Si(3);
			m1[1][1] = Si(4);

			m2[0][0] = Si(2);
			m2[0][1] = Si(4);
			m2[1][0] = Si(-1);
			m2[1][1] = Si(1);

			m3[0][0] = Si(m1[0][0] % m2[0][0]);
			m3[0][1] = Si(m1[0][1] % m2[0][1]);
			m3[1][0] = Si(m1[1][0] % m2[1][0]);
			m3[1][1] = Si(m1[1][1] % m2[1][1]);

			//std::cout << m1 << " % " << m2 << " should result in" << m3 << std::endl;
			TS_ASSERT((m1 % m2) == m3);
			return ;
		}

		void test_pow_basic44_scalar(void) {
			/* std::cout << std::endl << "Operator ^ test basic44" << std::endl; */
			cv42::Matrix<Sf> m1(2,2);
			cv42::Matrix<Sf> m2(2,2);
			cv42::Matrix<Sf> m3(2,2);

			m1[0][0] = Sf(1);
			m1[0][1] = Sf(2);
			m1[1][0] = Sf(3);
			m1[1][1] = Sf(4);

			m2[0][0] = Sf(2);
			m2[0][1] = Sf(4);
			m2[1][0] = Sf(-1);
			m2[1][1] = Sf(1);

			m3[0][0] = Sf(pow(m1[0][0], m2[0][0]));
			m3[0][1] = Sf(pow(m1[0][1], m2[0][1]));
			m3[1][0] = Sf(pow(m1[1][0], m2[1][0]));
			m3[1][1] = Sf(pow(m1[1][1], m2[1][1]));

			//std::cout << m1 << " ^ " << m2 << " should result in" << m3 << std::endl;
			TS_ASSERT((m1 ^ m2) == m3);
			return ;
		}

		void test_mul_basic44_scalar(void) {
			/* std::cout << std::endl << "Mul method (wise product) test basic44" << std::endl; */
			cv42::Matrix<Si> m1(2,2);
			cv42::Matrix<Si> m2(2,2);
			cv42::Matrix<Si> m3(2,2);

			m1[0][0] = Si(1);
			m1[0][1] = Si(2);
			m1[1][0] = Si(3);
			m1[1][1] = Si(4);

			m2[0][0] = Si(2);
			m2[0][1] = Si(4);
			m2[1][0] = Si(-1);
			m2[1][1] = Si(1);

			m3[0][0] = Si(m1[0][0] * m2[0][0]);
			m3[0][1] = Si(m1[0][1] * m2[0][1]);
			m3[1][0] = Si(m1[1][0] * m2[1][0]);
			m3[1][1] = Si(m1[1][1] * m2[1][1]);

			//std::cout << m1 << " .* " << m2 << " should result in" << m3 << std::endl;
			TS_ASSERT(m1.mul(m2) == m3);
			return ;
		}

/**************************!!!NULL44!!!**************************/
};