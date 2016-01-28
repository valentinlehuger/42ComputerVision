#ifndef	IMG_HPP
# define IMG_HPP

# include <Matrix.hpp>

namespace cv42 {

	/**
	 * Return a Matrix<float> representing the image given by filepath.
	 * Use CImg to decompress the image
	 */
	cv42::Matrix<float>	openImg(const char* filepath);

}

#endif /* IMG_HPP */
