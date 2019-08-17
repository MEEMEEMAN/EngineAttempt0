#pragma once
#include "pch.h"

/*
* This class represents the values a pixel has.
*/
struct Pixel
{
	float R;
	float G;
	float B;
	float A;
};

/*
* Class for managing images.
* image data gets destroyed upon destructor.
*/
class Image
{
public:
	/*
	* Load an image to the memory.
	*/
	Image(std::string filepath, bool flipVertically = false)
	{
		LoadImage(filepath);
	}

	Image()
	{

	}

	/*
	* Get a specific pixel value from the image.
	*/
	Pixel GetPixel(size_t x, size_t y);

	inline size_t GetImageWidth()
	{
		return width;
	}

	inline size_t GetImageHeight()
	{
		return height;
	}

	inline size_t PixelChannels()
	{
		return nrChannels;
	}

	inline unsigned char* GetImageData()
	{
		return mData;
	}

	inline bool isFlippedVerticallu()
	{
		return mFlippedVertically;
	}

	//Dispose of heavy pixel data.
	~Image()
	{
		free(mData);
	}

private:
	
	void LoadImage(std::string filepath, bool flipVertically = false);

	/*
		two GetPixel implementations are needed for parsing different types of images.
	*/

	Pixel GetPixelAlpha(size_t x, size_t y);
	Pixel GetPixelNoAlpha(size_t x, size_t y);

	/*
	* These variables describe the width and height in pixels,
	* The nrChannels describes the amount of color channels present (jpg = 3, png = 4, etc.)
		this is important for interpreting the type of image, and parsing the values correctly.
	*/
	int width = 0, height = 0, nrChannels = 0;

	/*
	* Image data in bytes. char is used since it is the
		equivelant of 1 byte in memory size.
	*/
	unsigned char* mData = 0;

	bool mFlippedVertically = false;
};
