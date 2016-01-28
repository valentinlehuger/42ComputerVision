#include <iostream>
#include <fstream>
#include <cxxtest/TestSuite.h>
#include <Matrix.hpp>
#include <Scalar.hpp>
#include <Vector.hpp>

#define Si cv42::Scalar<int>
#define Sf cv42::Scalar<float>
#define Vf cv42::Vector<Sf>

class Test_Normalization : public CxxTest::TestSuite {
	public:
		void test1(void) {
			cv42::Matrix<float> m({
				cv42::Vector<float>({1,2,3}),
				cv42::Vector<float>({2,-1,0})
				});
			cv42::Matrix<float> m2(m.normalization(1));
			cv42::Matrix<float> m3(m.normalization(0));
			m3 = m3.transpose();
			for (int i = 0 ; i < m2.getNrows() ; i++) {
				float n = m2[i].norm();
				TS_ASSERT_LESS_THAN(abs(n-1), 1e-6);
			}
			for (int i = 0 ; i < m3.getNrows() ; i++) {
				float n = m3[i].norm();
				TS_ASSERT_LESS_THAN(abs(n-1), 1e-6);
			}
		}
};

class Test_Mean : public CxxTest::TestSuite {
	public:
		void test1(void) {
			cv42::Matrix<float> m({
					cv42::Vector<float>({1,2,3}),
						cv42::Vector<float>({2,-1,0})
						});
			cv42::Matrix<float> mbis(m.transpose());
			cv42::Matrix<float> m2(m.mean(1));
			cv42::Matrix<float> m3(m.mean(0));
			cv42::Matrix<float> m4(m-m2);
			cv42::Matrix<float> m5(m-m3);
			for (int i = 0 ; i < m.getNrows() ; i++) {
				float n = m[i].mean();
				for (int j = 0 ; j < m.getNcols();j++) {
					TS_ASSERT_LESS_THAN(abs(m4[i][j]-(m[i][j]-n)), 1e-6);
				}
			}
			for (int i = 0 ; i < mbis.getNrows() ; i++) {
				float n = mbis[i].mean();
				for (int j = 0 ; j < mbis.getNcols();j++) {
					TS_ASSERT_LESS_THAN(abs(m5[j][i]-(mbis[i][j]-n)), 1e-6);
				}
			}
		}

		void test2(void) {
			cv42::Matrix<float> m({
					cv42::Vector<float>({1, 2, 3}),
					cv42::Vector<float>({2, -1, 0})
					});
			cv42::Matrix<float> mean0(m.mean2(0));
			cv42::Matrix<float> mean1(m.mean2(1));
			cv42::Matrix<float> mean0expect({
					cv42::Vector<float>({1.5, 0.5, 1.5}),
					});
			cv42::Matrix<float> mean1expect({
					cv42::Vector<float>({2, 1 / 3. }),
					});

			TS_ASSERT(mean0 == mean0expect);
			TS_ASSERT(mean1 == mean1expect);
		}
};

class Test_Transpose : public CxxTest::TestSuite{
	public:
		void test1(void) {
			cv42::Matrix<Sf> m2(1,1);
			cv42::Matrix<Sf> m3(1,42);
			cv42::Matrix<Sf> m4(42,1);
			cv42::Matrix<Sf> m5(24,42);
			cv42::Matrix<Sf> m2t = m2.transpose();
			cv42::Matrix<Sf> m3t = m3.transpose();
			cv42::Matrix<Sf> m4t = m4.transpose();
			cv42::Matrix<Sf> m5t = m5.transpose();

			TS_ASSERT_EQUALS(m2.getNrows(),m2t.getNcols());
			TS_ASSERT_EQUALS(m2.getNcols(),m2t.getNrows());
			TS_ASSERT_EQUALS(m3.getNrows(),m3t.getNcols());
			TS_ASSERT_EQUALS(m3.getNcols(),m3t.getNrows());
			TS_ASSERT_EQUALS(m4.getNrows(),m4t.getNcols());
			TS_ASSERT_EQUALS(m4.getNcols(),m4t.getNrows());
			TS_ASSERT_EQUALS(m5.getNrows(),m5t.getNcols());
			TS_ASSERT_EQUALS(m5.getNcols(),m5t.getNrows());
		}

		void test2(void) {
			cv42::Matrix<Sf> m1({Vf({1,2,3}),Vf({4,5,6})}); //[[1,2,3],[4,5,6]]
			cv42::Matrix<Sf> m2({Vf({1,4}),Vf({2,5}),Vf({3,6})}); //[[1,4],[2,5],[3,6]]

			cv42::Matrix<Sf> m1t = m1.transpose();
			TS_ASSERT_EQUALS(m1t,m2);
		}
};

class Test_DotProduct : public CxxTest::TestSuite{
	public:
		void test1(void){
			cv42::Matrix<Sf> m1(1,42);
			cv42::Matrix<Sf> m2(42,24);
			cv42::Matrix<Sf> m3 = m1*m2;

			TS_ASSERT_EQUALS(m3.getNrows(),m1.getNrows());
			TS_ASSERT_EQUALS(m3.getNcols(),m2.getNcols());
		}
		void test2(void) {
			cv42::Matrix<Sf> m1({Vf({1,2}),Vf({3,4})}); //[[1,2],[3,4]]
			cv42::Matrix<Sf> id({Vf({1,0}),Vf({0,1})}); //[[1,0],[0,1]]

			cv42::Matrix<Sf> m2 = m1*id;
			cv42::Matrix<Sf> m3 = id*m1;

			TS_ASSERT_EQUALS(m2,m1);
			TS_ASSERT_EQUALS(m3,m1);
		}
		void test3(void) {
			cv42::Matrix<Sf> m1({Vf({1,-1,0}),Vf({3,2,1})}); //[[1,-1,0],[3,2,1]]
			cv42::Matrix<Sf> m2({Vf({1,-2}),Vf({3,0}),Vf({1,2})}); //[[1,-2],[3,0],[1,2]]
			cv42::Matrix<Sf> m3({Vf({-2,-2}),Vf({10,-4})}); //[[-2,-2],[10,-4]]

			cv42::Matrix<Sf> m4 = m1*m2;
			TS_ASSERT_EQUALS(m3,m4);
			TS_ASSERT_EQUALS(m1,m1);
			TS_ASSERT_EQUALS(m2,m2);
		}
};


class Test_isSquare : public CxxTest::TestSuite {
public:
	void test1(void){
			cv42::Matrix<Sf> m1({Vf({1,2,3}),Vf({4,5,6})}); //[[1,2,3],[4,5,6]]
			cv42::Matrix<Sf> m2({Vf({1,4}),Vf({2,5})}); //[[1,4],[2,5]]

			TS_ASSERT_EQUALS(m1.isSquare(), false);
			TS_ASSERT_EQUALS(m2.isSquare(), true);
	}
};

class Test_trace : public CxxTest::TestSuite {
public:
	void test1(void){
			cv42::Matrix<Sf> m1({Vf({1,2,3}),Vf({4,5,6}), Vf({7,8,9})});
			cv42::Matrix<Sf> m2({Vf({1,4}),Vf({2,5})});

			TS_ASSERT_EQUALS(m1.trace(), 15);
			TS_ASSERT_EQUALS(m2.trace(), 6);
	}
};

class Test_identity : public CxxTest::TestSuite {
public:
	void test1(void){
		cv42::Matrix<int> m1 = cv42::Matrix<int>::identity(5);

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (i == j)
				{
					TS_ASSERT_EQUALS(m1[i][j], 1);
				}
				else
				{
					TS_ASSERT_EQUALS(m1[i][j], 0);
				}
			}
		}
	}

};

class TestSlice : public CxxTest::TestSuite {
public:
	void test1(void){
		cv42::Matrix<int> m1({
				cv42::Vector<int>({1,	2,	3,	4}),
				cv42::Vector<int>({5,	6,	7,	8}),
				cv42::Vector<int>({9,	10,	11,	12}),
				cv42::Vector<int>({13,	14,	15,	16}),
				cv42::Vector<int>({17,	18,	19,	20})
		});
		cv42::Matrix<int> m2({
				cv42::Vector<int>({6,	7}),
				cv42::Vector<int>({10,	11}),
				cv42::Vector<int>({14,	15}),
		});
		cv42::Matrix<int> test = m1.slice(1, 1, 4, 3);
		std::ofstream myfile;
		TS_ASSERT_EQUALS(test, m2);
	}

	void test2(){
		cv42::Matrix<int> m({
				cv42::Vector<int>({6,	7}),
				cv42::Vector<int>({10,	11}),
				cv42::Vector<int>({14,	15}),
		});
		m.slice(1, 2, 1, 1);
		TS_ASSERT_THROWS_ANYTHING(m.slice(1, 1, 3, 3));
		TS_ASSERT_THROWS_ANYTHING(m.slice(1, 1, 1, 3));
	}
};

class TestInsert : public CxxTest::TestSuite {
public:
	void test1(void){
		cv42::Matrix<int> m1({
				cv42::Vector<int>({1,	2,	3,	4}),
				cv42::Vector<int>({5,	0,	0,	8}),
				cv42::Vector<int>({9,	0,	0,	12}),
				cv42::Vector<int>({13,	0,	0,	16}),
				cv42::Vector<int>({17,	18,	19,	20})
		});
		cv42::Matrix<int> m1Sub({
				cv42::Vector<int>({6,	7}),
				cv42::Vector<int>({10,	11}),
				cv42::Vector<int>({14,	15}),
		});
		cv42::Matrix<int> expect1({
				cv42::Vector<int>({1,	2,	3,	4}),
				cv42::Vector<int>({5,	6,	7,	8}),
				cv42::Vector<int>({9,	10,	11,	12}),
				cv42::Vector<int>({13,	14,	15,	16}),
				cv42::Vector<int>({17,	18,	19,	20})
		});
	    m1.insert(m1Sub, 1, 1);
		TS_ASSERT_EQUALS(m1, expect1);
	}

	void test2(void){
		cv42::Matrix<int> m1({
				cv42::Vector<int>({1,	2,	0,	0}),
		});
		cv42::Matrix<int> m1Sub({
				cv42::Vector<int>({3,	4}),
		});
		cv42::Matrix<int> expect1({
				cv42::Vector<int>({1,	2,	3,	4}),
		});
	    m1.insert(m1Sub, 0, 2);
		TS_ASSERT_EQUALS(m1, expect1);
	}

	void test3(void){
		cv42::Matrix<int> m1({
				cv42::Vector<int>({0,	2,	3,	4}),
		});
		cv42::Matrix<int> m1Sub(1, 1);
		cv42::Matrix<int> expect1({
				cv42::Vector<int>({1,	2,	3,	4}),
		});

		m1Sub[0][0] = 1;
	    m1.insert(m1Sub, 0, 0);
		TS_ASSERT_EQUALS(m1, expect1);
	}

	void test4(void){
		cv42::Matrix<int> m1({
				cv42::Vector<int>({1,	2,	3,	4}),
				cv42::Vector<int>({5,	6,	7,	8}),
				cv42::Vector<int>({9,	10,	11,	12}),
				cv42::Vector<int>({13,	14,	15,	16}),
				cv42::Vector<int>({17,	18,	19,	20})
		});
		cv42::Matrix<int> m1Sub(5, 1);
		cv42::Matrix<int> expect1({
				cv42::Vector<int>({0,	2,	3,	4}),
				cv42::Vector<int>({0,	6,	7,	8}),
				cv42::Vector<int>({0,	10,	11,	12}),
				cv42::Vector<int>({0,	14,	15,	16}),
				cv42::Vector<int>({0,	18,	19,	20})
		});
	    m1.insert(m1Sub, 0, 0);
		TS_ASSERT_EQUALS(m1, expect1);
	}

	void test5(void){
		cv42::Matrix<int> m1({
				cv42::Vector<int>({1,	2,	3,	4}),
				cv42::Vector<int>({5,	6,	7,	8}),
				cv42::Vector<int>({9,	10,	11,	12}),
				cv42::Vector<int>({13,	14,	15,	16}),
				cv42::Vector<int>({17,	18,	19,	20})
		});
		cv42::Matrix<int> m1Sub(1, 4);
		cv42::Matrix<int> expect1({
				cv42::Vector<int>({1,	2,	3,	4}),
				cv42::Vector<int>({5,	6,	7,	8}),
				cv42::Vector<int>({9,	10,	11,	12}),
				cv42::Vector<int>({13,	14,	15,	16}),
				cv42::Vector<int>({0,	0,	0,	0})
		});

	    m1.insert(m1Sub, 4, 0);
		TS_ASSERT_EQUALS(m1, expect1);
	}
};

class Test_qrDecompose : public CxxTest::TestSuite {
public:
	void test1(void) {
		cv42::Matrix<double> mat1({
				cv42::Vector<double>({25, 11.04, 9.28}),
					cv42::Vector<double>({95, 146, 72}),
					cv42::Vector<double>({-10, 6, -33})});
		cv42::Matrix<double> Qexpect({
				cv42::Vector<double>({-0.25318484,  0.74815077,  0.61332525}),
					cv42::Vector<double>({-0.9621024, -0.26109241, -0.07867483}),
					cv42::Vector<double>({0.10127394, -0.61000097,  0.78590229}),
		});
		cv42::Matrix<double> Rexpect({
				cv42::Vector<double>({-9.87420883e+01,  -1.42654467e+02,  -7.49629680e+01}),
					cv42::Vector<double>({1.02958583e-14,  -3.35199131e+01,   8.27421764e+00}),
					cv42::Vector<double>({6.77224864e-15,   3.55271368e-15,  -2.59077046e+01}),
		});
		cv42::Matrix<double>	Q;
		cv42::Matrix<double>	R;
		std::pair<cv42::Matrix<double>, cv42::Matrix<double>> QR;


		QR = mat1.qrDecomposition();
		Q = QR.first;
		R = QR.second;
		for (int row = 0; row < Qexpect.getNrows(); row++) {
			for (int col = 0; col < Qexpect.getNcols(); col++) {
				TS_ASSERT(Qexpect[row][col] - Q[row][col] < 0.0001);
			}
		}
		for (int row = 0; row < Rexpect.getNrows(); row++) {
			for (int col = 0; col < Rexpect.getNcols(); col++) {
				TS_ASSERT(Rexpect[row][col] - R[row][col] < 0.0001);
			}
		}
	}

	void test2(void) {
		cv42::Matrix<float> mat1({
				cv42::Vector<float>({12, -51, 4}),
					cv42::Vector<float>({6, 167, -68}),
					cv42::Vector<float>({-4, 24, -41})});
		cv42::Matrix<float> Qexpect({
						cv42::Vector<float>({-0.85714286,  0.39428571,  0.33142857}),
								cv42::Vector<float>({-0.42857143, -0.90285714, -0.03428571}),
								cv42::Vector<float>({0.28571429, -0.17142857,  0.94285714}),
		});
		cv42::Matrix<float> Rexpect({
						cv42::Vector<float>({-1.40000000e+01,  -2.10000000e+01,   1.40000000e+01}),
								cv42::Vector<float>({5.97812398e-18,  -1.75000000e+02,   7.00000000e+01}),
								cv42::Vector<float>({4.47505281e-16,   0.00000000e+00,  -3.50000000e+01}),
		});
		cv42::Matrix<float>	Q;
		cv42::Matrix<float>	R;
		std::pair<cv42::Matrix<float>, cv42::Matrix<float>> QR;


		QR = mat1.qrDecomposition();
		Q = QR.first;
		R = QR.second;
		for (int row = 0; row < Qexpect.getNrows(); row++) {
			for (int col = 0; col < Qexpect.getNcols(); col++) {
				TS_ASSERT(Qexpect[row][col] - Q[row][col] < 0.0001);
			}
		}
		for (int row = 0; row < Rexpect.getNrows(); row++) {
			for (int col = 0; col < Rexpect.getNcols(); col++) {
				TS_ASSERT(Rexpect[row][col] - R[row][col] < 0.0001);
			}
		}
	}

	void test3(void) {
		cv42::Matrix<float> mat1({
						cv42::Vector<float>({1.56136684e+02,  -6.22705050e+01,  -8.74603501e+01}),
								cv42::Vector<float>({5.00764219e-45,  -3.41966750e+01,  -1.58136450e+01}),
								cv42::Vector<float>({-4.14582390e-68,   1.96374982e-21,   1.60599909e+01})});
		cv42::Matrix<float> Qexpect({
						cv42::Vector<float>({-1.00000000e+00,   3.20721695e-47,  -1.57622444e-69}),
								cv42::Vector<float>({-3.20721695e-47,  -1.00000000e+00,   5.74251683e-23}),
								cv42::Vector<float>({2.65525295e-70,   5.74251683e-23,   1.00000000e+00}),
		});
		cv42::Matrix<float> Rexpect({
						cv42::Vector<float>({-1.56136684e+002,   6.22705050e+001,   8.74603501e+001}),
								cv42::Vector<float>({1.76528607e-184,   3.41966750e+001,   1.58136450e+001}),
								cv42::Vector<float>({-1.01371850e-206,   0.00000000e+000,   1.60599909e+001}),
		});
		cv42::Matrix<float>	Q;
		cv42::Matrix<float>	R;
		std::pair<cv42::Matrix<float>, cv42::Matrix<float>> QR;


		QR = mat1.qrDecomposition();
		Q = QR.first;
		R = QR.second;
		for (int row = 0; row < Qexpect.getNrows(); row++) {
			for (int col = 0; col < Qexpect.getNcols(); col++) {
				TS_ASSERT(Qexpect[row][col] - Q[row][col] < 0.0001);
			}
		}
		for (int row = 0; row < Rexpect.getNrows(); row++) {
			for (int col = 0; col < Rexpect.getNcols(); col++) {
				TS_ASSERT(Rexpect[row][col] - R[row][col] < 0.0001);
			}
		}
	}

	void test4(void) {
		cv42::Matrix<float> mat1({
				cv42::Vector<float>({0.90542234,  0.36255072,  0.50210071}),
					cv42::Vector<float>({0.23021998,  0.98682605,  0.76863985}),
					cv42::Vector<float>({0.75589648,  0.711475,    0.03224202})});
		cv42::Matrix<float> Qexpect({
				cv42::Vector<float>({-0.75342842,  0.36466705, -0.54714127}),
					cv42::Vector<float>({-0.19157278, -0.91775772, -0.34788021}),
					cv42::Vector<float>({-0.62900357, -0.15728547,  0.76132502}),
		});
		cv42::Matrix<float> Rexpect({
				cv42::Vector<float>({-1.20173638e+00,  -9.09725340e-01,  -5.45827758e-01}),
					cv42::Vector<float>({-4.52750795e-17,  -8.85361599e-01,  -5.27396775e-01}),
					cv42::Vector<float>({1.02316723e-16,   0.00000000e+00,  -5.17567959e-01}),
		});
		cv42::Matrix<float>	Q;
		cv42::Matrix<float>	R;
		std::pair<cv42::Matrix<float>, cv42::Matrix<float>> QR;


		QR = mat1.qrDecomposition();
		Q = QR.first;
		R = QR.second;
		for (int row = 0; row < Qexpect.getNrows(); row++) {
			for (int col = 0; col < Qexpect.getNcols(); col++) {
				TS_ASSERT(Qexpect[row][col] - Q[row][col] < 0.0001);
			}
		}
		for (int row = 0; row < Rexpect.getNrows(); row++) {
			for (int col = 0; col < Rexpect.getNcols(); col++) {
				TS_ASSERT(Rexpect[row][col] - R[row][col] < 0.0001);
			}
		}
	}
};

class Test_diagonal : public CxxTest::TestSuite {
public:
		void	test1(void) {
			cv42::Matrix<int> mat1({
					 cv42::Vector<int>({1, 2, 3}),
					 cv42::Vector<int>({4, 5, 6}),
					 cv42::Vector<int>({7, 8, 9}),
			});
			cv42::Vector<int> expect1({1, 5, 9});
			cv42::Vector<int> result1 = mat1.diagonal();

			for (int i = 0; i != expect1.getSize(); i++) {
				TS_ASSERT(expect1[i] == result1[i]);
			}
		}

		void	test2(void) {
			cv42::Matrix<int> mat1({
					 cv42::Vector<int>({1, 2}),
					 cv42::Vector<int>({4, 5}),
			});
			cv42::Vector<int> expect1({1, 5});
			cv42::Vector<int> result1 = mat1.diagonal();

			for (int i = 0; i != expect1.getSize(); i++) {
				TS_ASSERT(expect1[i] == result1[i]);
			}
		}

		void	test3(void) {
			cv42::Matrix<int> mat1({
					 cv42::Vector<int>({1}),
			});
			cv42::Vector<int> expect1({1});
			cv42::Vector<int> result1 = mat1.diagonal();

			for (int i = 0; i != expect1.getSize(); i++) {
				TS_ASSERT(expect1[i] == result1[i]);
			}
		}
};

class Test_eigenvv : public CxxTest::TestSuite {
public:
	void test1(void) {
		cv42::Matrix<double>	mat1({
				cv42::Vector<double>({12, -51, 4}),
					cv42::Vector<double>({6, 167, -68}),
					cv42::Vector<double>({-4, 24, -41})
					});
		cv42::Vector<double>	expectVal1({156.13668406, -34.196675, 16.05999094});
		cv42::Matrix<double>	expectVec1({
				cv42::Vector<double>({-0.32814742,  0.37540398,  0.86682819}),
					cv42::Vector<double>({0.93688136,  0.01207139,  0.34943898}),
					cv42::Vector<double>({0.12071697,  0.92678268, -0.35567019})
					});
		std::pair<cv42::Vector<double>, cv42::Matrix<double>>	res1;

		res1 = mat1.eigenvv();
		for (int i = 0; i != expectVal1.getSize(); i++) {
			TS_ASSERT(expectVal1[i] - res1.first[i] < 0.0001);
		}
		for (int row = 0; row < expectVec1.getNrows(); row++) {
			for (int col = 0; col < expectVec1.getNcols(); col++) {
				TS_ASSERT(expectVec1[row][col] - res1.second[row][col] < 0.0001);
			}
		}
	}

	void test2(void) {
		cv42::Matrix<double>	mat1({
				cv42::Vector<double>({0.07668438,  0.92884711,  0.13838446,  0.20187216}),
					cv42::Vector<double>({0.70580206,  0.87015099,  0.53071387,  0.7265993}),
					cv42::Vector<double>({0.61849123,  0.86678731,  0.93676834,  0.21665075}),
					cv42::Vector<double>({0.56966804,  0.99020624,  0.48546493,  0.46543131})
					});
		cv42::Vector<double>	expectVal1({2.40620279,  0.42988698, -0.39674108, -0.09031368});
		cv42::Matrix<double>	expectVec1({
				cv42::Vector<double>({0.30796258, -0.40268395,  0.82634268, -0.24528036}),
					cv42::Vector<double>({0.57741801, -0.32575628, -0.53067982, -0.5280627}),
					cv42::Vector<double>({0.54717277,  0.81579932,  0.17087004, -0.07666063}),
					cv42::Vector<double>({0.5218711,  -0.2572935,  -0.07962498,  0.80938895})
					});
		std::pair<cv42::Vector<double>, cv42::Matrix<double>>	res1;

		res1 = mat1.eigenvv();
		for (int i = 0; i != expectVal1.getSize(); i++) {
			TS_ASSERT(expectVal1[i] - res1.first[i] < 0.0001);
		}
		for (int row = 0; row < expectVec1.getNrows(); row++) {
			for (int col = 0; col < expectVec1.getNcols(); col++) {
				TS_ASSERT(expectVec1[row][col] - res1.second[row][col] < 0.0001);
			}
		}
	}

	void test3(void) {
		cv42::Matrix<double>	mat1({
				cv42::Vector<double>({0.24468338,  0.59295935,  0.28996482}),
					cv42::Vector<double>({0.70326734,  0.60698089,  0.27852599}),
					cv42::Vector<double>({0.81461656,  0.80844495,  0.82651163})
					});
		cv42::Vector<double>	expectVal1({1.64944834,  0.28556648, -0.25683892});
		cv42::Matrix<double>	expectVec1({
				cv42::Vector<double>({0.36173099,  0.35353342, -0.86264988}),
					cv42::Vector<double>({0.46059461,  0.73672445,  0.49506534}),
					cv42::Vector<double>({0.8105574,  -0.57641236,  0.10366047})
					});
		std::pair<cv42::Vector<double>, cv42::Matrix<double>>	res1;

		res1 = mat1.eigenvv();
		for (int i = 0; i != expectVal1.getSize(); i++) {
			TS_ASSERT(expectVal1[i] - res1.first[i] < 0.0001);
		}
		for (int row = 0; row < expectVec1.getNrows(); row++) {
			for (int col = 0; col < expectVec1.getNcols(); col++) {
				TS_ASSERT(expectVec1[row][col] - res1.second[row][col] < 0.0001);
			}
		}
	}
};

class Test_Sum : public CxxTest::TestSuite {
	public:
		void test1(void) {
			cv42::Matrix<float> m({
					cv42::Vector<float>({1, 2, 3}),
					cv42::Vector<float>({2, -1, 0})
					});
			cv42::Matrix<float> sum0(m.sum(0));
			cv42::Matrix<float> sum1(m.sum(1));
			cv42::Matrix<float> sum0expect({
					cv42::Vector<float>({3, 1, 3}),
					});
			cv42::Matrix<float> sum1expect({
					cv42::Vector<float>({6, 1}),
					});

			TS_ASSERT(sum0 == sum0expect);
			TS_ASSERT(sum1 == sum1expect);
		}
};

float randomizer()
{
	return (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) - 0.5f;
}

class TestRandomize : public CxxTest::TestSuite {
	public:
		void test1(void) {
			cv42::Matrix<float> m(2, 5);
			srand (static_cast <unsigned> (time(0)));
			m.randomize(randomizer);
			// std::cout << m << std::endl;
			// TS_ASSERT(1 == 0);
		}
};

// class Test_determinant : public CxxTest::TestSuite {
// public:
// 	void test3x3(void){
// 		cv42::Matrix<float> m1({cv42::Vector<float>({1,2,0}),cv42::Vector<float>({-1,1,1}), cv42::Vector<float>({1,2,3})});
// 		TS_ASSERT_EQUALS(m1.determinant(), 9.0f);
// 	}


// 	void test5x5(void){
// 		cv42::Matrix<float> m1({
// 			cv42::Vector<float>({1,  3,  1, -1,  7}),
// 			cv42::Vector<float>({ 2,  2,  2,  0,  2}),
// 			cv42::Vector<float>({ 3,  1,  3, -8,  1}),
// 			cv42::Vector<float>({ 3,  2,  4,  1,  3}),
// 			cv42::Vector<float>({ 5,  2,  5,  2,  2})});
// 		TS_ASSERT_EQUALS(m1.determinant(), -224.0f);
// 	}

// 	void test9x9(void){
// 		cv42::Matrix<float> m1({
// 			cv42::Vector<float>({1,  3,  1, -1,  7, 4, -3, 9, 1}),
// 			cv42::Vector<float>({2,  2,  2,  0,  2, -6, 3, -2, 7}),
// 			cv42::Vector<float>({3,  1,  3, -8,  1, -8, -1, 4, 13}),
// 			cv42::Vector<float>({3,  2,  4,  1,  3, -9, 4, -5, 7}),
// 			cv42::Vector<float>({5,  2,  5,  2,  2,  2,  0, -2, -5}),
// 			cv42::Vector<float>({1, -2,  3, -4,  2, 1,  0, -1,  1}),
// 			cv42::Vector<float>({11, 0, 17, 4,  7, 6, 1, 8, 2}),
// 			cv42::Vector<float>({-5, -5, -5, 5, -5, 5, -6, 6, 6}),
// 			cv42::Vector<float>({2, 3, 4, 5, -6, -7, 8, -9, 10})});
// 		TS_ASSERT_EQUALS(m1.determinant(), 26920584.0f);
// 	}

// };
