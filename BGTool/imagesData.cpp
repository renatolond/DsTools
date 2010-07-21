#include "images.h"

void imagesData::createBgMatrix(int height, int width)
{
    bgmatrix_height = height;
    bgmatrix_width = width;
    bgmatrix = new int*[bgmatrix_height];
    for ( int i = 0 ; i < bgmatrix_height ; i++ )
    {
        bgmatrix[i] = new int[bgmatrix_width];
    }
}

void imagesData::dumpBgMatrix()
{
    std::cout << "Starting dump.. " << bgmatrix_height << "x" << bgmatrix_width << std::endl;
    for ( int i = 0 ; i < bgmatrix_height ; i++ )
    {
        for ( int j = 0 ; j < bgmatrix_width ; j++ )
            std::cout << " " << bgmatrix[i][j] << " ";
        std::cout << std::endl;
    }

}

