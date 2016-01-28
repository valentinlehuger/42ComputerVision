#include <cxxtest/TestSuite.h>
#include <Scalar.hpp>

class Test1 : public CxxTest::TestSuite{
	public:
		void testIncreaseOnePostFix(void) {
			cv42::Scalar<float>		f_scalar(42);
			cv42::Scalar<double> 	d_scalar(42);
			cv42::Scalar<int>		i_scalar(42);
			cv42::Scalar<char>		c_scalar(42);

			f_scalar++; TS_ASSERT_EQUALS(f_scalar.getValue(), 42 + 1);
			d_scalar++; TS_ASSERT_EQUALS(d_scalar.getValue(), 42 + 1);
			i_scalar++; TS_ASSERT_EQUALS(i_scalar.getValue(), 42 + 1);
			c_scalar++; TS_ASSERT_EQUALS(c_scalar.getValue(), 42 + 1);
		}

		void testIncreaseOnePrefix(void) {
			cv42::Scalar<float>		f_scalar(42);
			cv42::Scalar<double> 	d_scalar(42);
			cv42::Scalar<int>		i_scalar(42);
			cv42::Scalar<char>		c_scalar(42);

			++f_scalar; TS_ASSERT_EQUALS(f_scalar.getValue(), 42 + 1);
			++d_scalar; TS_ASSERT_EQUALS(d_scalar.getValue(), 42 + 1);
			++i_scalar; TS_ASSERT_EQUALS(i_scalar.getValue(), 42 + 1);
			++c_scalar; TS_ASSERT_EQUALS(c_scalar.getValue(), 42 + 1);
		}

		void testDecreaseOne1(void) {
			cv42::Scalar<float>		f_scalar(42);
			cv42::Scalar<double> 	d_scalar(42);
			cv42::Scalar<int>		i_scalar(42);
			cv42::Scalar<char>		c_scalar(42);

			f_scalar--; TS_ASSERT_EQUALS(f_scalar.getValue(), 42 - 1);
			d_scalar--; TS_ASSERT_EQUALS(d_scalar.getValue(), 42 - 1);
			i_scalar--; TS_ASSERT_EQUALS(i_scalar.getValue(), 42 - 1);
			c_scalar--; TS_ASSERT_EQUALS(c_scalar.getValue(), 42 - 1);
		}

		void testDecreaseOne2(void) {
			cv42::Scalar<float>		f_scalar(42);
			cv42::Scalar<double> 	d_scalar(42);
			cv42::Scalar<int>		i_scalar(42);
			cv42::Scalar<char>		c_scalar(42);

			--f_scalar; TS_ASSERT_EQUALS(f_scalar.getValue(), 42 - 1);
			--d_scalar; TS_ASSERT_EQUALS(d_scalar.getValue(), 42 - 1);
			--i_scalar; TS_ASSERT_EQUALS(i_scalar.getValue(), 42 - 1);
			--c_scalar; TS_ASSERT_EQUALS(c_scalar.getValue(), 42 - 1);
		}

		void testAdditionScalarScalar1(void) {
			cv42::Scalar<float> f_scalar(4.2f);
			cv42::Scalar<float> f_scalar2(12.3f);
			cv42::Scalar<int> i_scalar(42);
			cv42::Scalar<int> i_scalar2(12);

			f_scalar += f_scalar2; TS_ASSERT_EQUALS(f_scalar.getValue(), 4.2f + 12.3f);
			i_scalar += i_scalar2; TS_ASSERT_EQUALS(i_scalar.getValue(), 42 + 12);
		}

		void testAdditionScalarScalar2(void) {
			cv42::Scalar<float> f_scalar(4.2f);
			cv42::Scalar<float> f_scalar2(12.3f);
			cv42::Scalar<int> i_scalar(42);
			cv42::Scalar<int> i_scalar2(12);
			cv42::Scalar<float> f_result;
			cv42::Scalar<int> i_result;

			f_result = f_scalar + f_scalar2; TS_ASSERT_EQUALS(f_result.getValue(), 4.2f + 12.3f);
			i_result = i_scalar + i_scalar2; TS_ASSERT_EQUALS(i_result.getValue(), 42 + 12);
		}

		void testSubstractionScalarScalar1(void) {
			cv42::Scalar<float> f_scalar(4.2f);
			cv42::Scalar<float> f_scalar2(12.3f);
			cv42::Scalar<int> i_scalar(42);
			cv42::Scalar<int> i_scalar2(12);

			f_scalar -= f_scalar2; TS_ASSERT_EQUALS(f_scalar.getValue(), 4.2f - 12.3f);
			i_scalar -= i_scalar2; TS_ASSERT_EQUALS(i_scalar.getValue(), 42 - 12);
		}

		void testSubstractionScalarScalar2(void) {
			cv42::Scalar<float> f_scalar(4.2f);
			cv42::Scalar<float> f_scalar2(12.3f);
			cv42::Scalar<int> i_scalar(42);
			cv42::Scalar<int> i_scalar2(12);
			cv42::Scalar<float> f_result;
			cv42::Scalar<int> i_result;

			f_result = f_scalar - f_scalar2; TS_ASSERT_EQUALS(f_result.getValue(), 4.2f - 12.3f);
			i_result = i_scalar - i_scalar2; TS_ASSERT_EQUALS(i_result.getValue(), 42 - 12);
		}

		void testMultiplicationScalarScalar1(void) {
			cv42::Scalar<float> f_scalar(4.2f);
			cv42::Scalar<float> f_scalar2(12.3f);
			cv42::Scalar<int> i_scalar(42);
			cv42::Scalar<int> i_scalar2(12);

			f_scalar *= f_scalar2; TS_ASSERT_EQUALS(f_scalar.getValue(), 4.2f * 12.3f);
			i_scalar *= i_scalar2; TS_ASSERT_EQUALS(i_scalar.getValue(), 42 * 12);
		}

		void testMultiplicationScalarScalar2(void) {
			cv42::Scalar<float> f_scalar(4.2f);
			cv42::Scalar<float> f_scalar2(12.3f);
			cv42::Scalar<int> i_scalar(42);
			cv42::Scalar<int> i_scalar2(12);
			cv42::Scalar<float> f_result;
			cv42::Scalar<int> i_result;

			f_result = f_scalar * f_scalar2; TS_ASSERT_EQUALS(f_result.getValue(), 4.2f * 12.3f);
			i_result = i_scalar * i_scalar2; TS_ASSERT_EQUALS(i_result.getValue(), 42 * 12);
		}

		void testDivisionScalarScalar1(void) {
			cv42::Scalar<float> f_scalar(4.2f);
			cv42::Scalar<float> f_scalar2(12.3f);
			cv42::Scalar<int> i_scalar(42);
			cv42::Scalar<int> i_scalar2(12);

			f_scalar /= f_scalar2; TS_ASSERT_EQUALS(f_scalar.getValue(), 4.2f / 12.3f);
			i_scalar /= i_scalar2; TS_ASSERT_EQUALS(i_scalar.getValue(), 42 / 12);
		}

		void testDivisionScalarScalar2(void) {
			cv42::Scalar<float> f_scalar(4.2f);
			cv42::Scalar<float> f_scalar2(12.3f);
			cv42::Scalar<int> i_scalar(42);
			cv42::Scalar<int> i_scalar2(12);
			cv42::Scalar<float> f_result;
			cv42::Scalar<int> i_result;

			f_result = f_scalar / f_scalar2; TS_ASSERT_EQUALS(f_result.getValue(), 4.2f / 12.3f);
			i_result = i_scalar / i_scalar2; TS_ASSERT_EQUALS(i_result.getValue(), 42 / 12);
		}

		void testModuloScalarScalar(void) {
			cv42::Scalar<float> f_scalar(4.2f);
			cv42::Scalar<float> f_scalar2(12.3f);
			cv42::Scalar<int> i_scalar(42);
			cv42::Scalar<int> i_scalar2(12);
			cv42::Scalar<float> f_result;
			cv42::Scalar<int> i_result;

			f_result = f_scalar2 % f_scalar; TS_ASSERT_EQUALS(f_result.getValue(), static_cast<long>(12.3f) % static_cast<long>(4.2f));
			i_result = i_scalar % i_scalar2; TS_ASSERT_EQUALS(i_result.getValue(), 42 % 12);
		}

		void testEqualityScalarScalar(void) {
			cv42::Scalar<float> f_scalar(4.2f);
			cv42::Scalar<float> f_scalar2(12.3f);
			cv42::Scalar<float> f_scalar3(4.2f);
			cv42::Scalar<int> i_scalar(42);
			cv42::Scalar<int> i_scalar2(12);
			cv42::Scalar<int> i_scalar3(42);

			TS_ASSERT(f_scalar == f_scalar3);
			TS_ASSERT(i_scalar == i_scalar3);
			TS_ASSERT(f_scalar != f_scalar2);
			TS_ASSERT(i_scalar != i_scalar2);
			TS_ASSERT(f_scalar <= f_scalar3);
			TS_ASSERT(i_scalar >= i_scalar3);
			TS_ASSERT(f_scalar < f_scalar2);
			TS_ASSERT(i_scalar > i_scalar2);
		}
};
