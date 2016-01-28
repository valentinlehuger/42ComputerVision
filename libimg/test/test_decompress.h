#include <cxxtest/TestSuite.h>
#include <Img.hpp>
#include <Matrix.hpp>
#include <CImg.h>

class testDecompress : public CxxTest::TestSuite{
	public:
		void	test_cimgsizemirror(void) {
			cv42::Matrix<float>	mtxA = cv42::openImg("lena.bmp");
			cimg_library::CImg<unsigned char>	originalA("lena.bmp");
			cv42::Matrix<float>	mtxB = cv42::openImg("1.png");
			cimg_library::CImg<unsigned char>	originalB("1.png");

			TS_ASSERT(mtxA.getNrows() == originalA.height());
			TS_ASSERT(mtxA.getNcols() == originalA.width());
			TS_ASSERT(mtxB.getNrows() == originalB.height());
			TS_ASSERT(mtxB.getNcols() == originalB.width());
			return ;
		}

		void	test_cimgpixelmirror(void) {		
			cv42::Matrix<float>	mtxA = cv42::openImg("lena.bmp");
			cimg_library::CImg<unsigned char>	originalA("lena.bmp");
			cv42::Matrix<float>	mtxB = cv42::openImg("1.png");
			cimg_library::CImg<unsigned char>	originalB("1.png");

			if (originalA.spectrum() == 3) {
				originalA = originalA.get_RGBtoYCbCr().get_channel(0);
			}
			if (originalB.spectrum() == 3) {
				originalB = originalB.get_RGBtoYCbCr().get_channel(0);
			}
			for(int w = 0; w != originalA.width(); w++)
			{
				for (int h = 0; h != originalA.height(); h++)
				{
					TS_ASSERT(mtxA[h][w] == static_cast<float>(originalA(w, h, 0, 0)));
				}
			}
			for(int w = 0; w != originalB.width(); w++)
			{
				for (int h = 0; h != originalB.height(); h++)
				{
					TS_ASSERT(mtxB[h][w] == static_cast<float>(originalB(w, h, 0, 0)));
				}
			}
		}
};
