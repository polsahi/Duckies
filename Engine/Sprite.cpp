// #include "Sprite.h"
// #include "ChiliWin.h"
// #include <cassert>
// #include <fstream>

// Sprite::Sprite(const std::string& filename) {
//     std::ifstream file(filename, std::ios::binary);
//     assert(file);
//     BITMAPFILEHEADER bmFileHeader;
//    file.read(reinterpret_cast<char*>(&bmFileHeader), sizeof(bmFileHeader));

//    BITMAPINFOHEADER bmInfoHeader;
//    file.read(reinterpret_cast<char*>(&bmInfoHeader), sizeof(bmInfoHeader));

//    assert( bmInfoHeader.biBitCount == 24);
//    //assert( bmInfoHeader.biCompression == BI_RGB);

//    width = bmInfoHeader.biWidth;
//    height = bmInfoHeader.biHeight;

//    pPixels = new Color [width*height];

//    file.seekg(bmFileHeader.bfOffBits);
//    const int padding = (4 - (width*3)%4)%4;

//    for (int y = 0; y < height; ++y) {
// //si la imatge es carrgead el reves treure el primer for per:
// //    for (int y = height - 1; y >= 0; --y) {
//        for (int x = 0; x < width; ++x) {
//          PutPixel(x, y, Color (file.get(), file.get(), file.get()));
//      }
//      file.seekg(padding, std::ios::cur);
//  }
// }


// //dimension constructor
// Sprite::Sprite(int width, int height) 
//     :
//     width(width),
//     height(height),
//     pPixels(new Color[width*height])
// {
// }

// //coping constructor
// Sprite::Sprite(const Sprite& rhs)
//     :
//     Sprite(rhs.width, rhs.height)
// {
//     const int nPixels = width*height;
//     for (int i = 0; i < nPixels; ++i) pPixels[i] = rhs.pPixels[i];
// }

// //destruction
// Sprite::~Sprite()
// {
//     delete [] pPixels;
//     pPixels = nullptr;
// }

// Sprite& Sprite::operator=( const Sprite& rhs) {
//     width = rhs.width;
//     height = rhs.height;

//     delete [] pPixels;
//     pPixels = new Color[height*width];

//     const int nPixels = width*height;
//     for (int i = 0; i < nPixels; ++i) pPixels[i] = rhs.pPixels[i];

//     return* this;
// } 

// void Sprite::PutPixel(int x, int y, Color c) {
//     assert(x >= 0);
//     assert(x < width);
//     assert(y >= 0);
//     assert(y < height);
//     pPixels[y*width + x] = c;
// }

// Color Sprite::GetPixel(int x, int y) const {
//     assert(x >= 0);
//     assert(x < width);
//     assert(y >= 0);
//     assert(y < height);
//     return pPixels[y * width + x];
// }

// int Sprite::GetWidth() const {
//     return width;
// }

// int Sprite::GetHeight() const {
//     return height;
// }