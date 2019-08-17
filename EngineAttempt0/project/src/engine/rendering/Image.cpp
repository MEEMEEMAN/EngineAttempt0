#include "Image.h"

void Image::LoadImage(std::string filepath, bool flipVertically)
{
	{
		std::fstream fileCheck(filepath);
		if (!fileCheck.good())
		{
			conlog("[Image]: Could not load from filepath: " << filepath);
			fileCheck.close();
			return;
		}
		fileCheck.close();
	}
	mFlippedVertically = flipVertically;
	stbi_set_flip_vertically_on_load(flipVertically);
	mData = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);
}

Pixel Image::GetPixelAlpha(size_t x, size_t y)
{
	Pixel p1;
	unsigned char* p = mData + (4 * (y * width + x));
	p1.R = p[0];
	p1.G = p[1];
	p1.B = p[2];
	p1.A = p[3];

	return p1;
}

Pixel Image::GetPixelNoAlpha(size_t x, size_t y)
{
	Pixel p1;
	unsigned char* p = mData + (3 * (y * width + x));
	p1.R = p[0];
	p1.G = p[1];
	p1.B = p[2];
	p1.A = 255;

	return p1;
}

Pixel Image::GetPixel(size_t x, size_t y)
{
	if (nrChannels == 4)
	{
		return GetPixelAlpha(x, y);
	}
	else if (nrChannels == 3)
	{
		return GetPixelNoAlpha(x, y);
	}
}