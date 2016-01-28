#include <CImg.h>
#include <Matrix.hpp>
#include <stdexcept>

namespace cv42 {

template <typename T>
void			fillMatrix(cv42::Matrix<T> & mtx, cimg_library::CImg<unsigned char> const & img, int const & width, int const & height)
{
	for(int w = 0; w != width; w++)
	{
		for (int h = 0; h != height; h++)
		{
			mtx[h][w] = static_cast<T>(img(w, h, 0, 0));
		}
	}
	return ;
}

template <typename T>
void			fillMatrixPtr(cv42::Matrix<T> & mtx, cimg_library::CImg<unsigned char> const & img, int const & width, int const & height)
{
	int			i = 0;
	int			w = 0;
	int			h = 0;
	const unsigned char	*ptr = img.data();
	while(i < width * height) {
	  mtx[h][w] = static_cast<T>(*(ptr+i));
		if (++w == width) {
		  w = 0;
		  ++h;
		}
		++i;
	}
	return ;
}

  Matrix<float>	openImg(const char* filepath)
{
	cimg_library::CImg<unsigned char>	original(filepath);
	cimg_library::CImg<unsigned char>	gray;
	int							width = original.width();
	int							height = original.height();
	int							spectrum = original.spectrum();
	cv42::Matrix<float>			convert(height, width);

	if (spectrum != 3 && spectrum != 1)
		throw std::exception();
	else if (spectrum == 3)
		gray = original.get_RGBtoYCbCr().get_channel(0);
	else
		gray = original;
	fillMatrixPtr(convert, gray, width, height);
	return (convert);
}
}
