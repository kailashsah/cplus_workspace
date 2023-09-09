#include <iostream>
using namespace std;

// curiously recurring template pattern
class Dimension {
public:
	Dimension(int _X, int _Y)
	{
		mX = _X;
		mY = _Y;
	}

private:
	int mX, mY;
};

template <class T>
class Image {
public:
	void Draw()
	{
		cout << "base::Draw() called" << endl;
		// Dispatch call to exact type
		static_cast<T*>(this)->Draw();
	}
	Dimension GetDimensionInPixels()
	{
		// Dispatch call to exact type
		static_cast<T*>(this)->GetDimensionInPixels();
	}

protected:
	int dimensionX, dimensionY;
};

// For Tiff Images
class TiffImage : public Image<TiffImage> {
public:
	void Draw()
	{
		// Uncomment this to check method dispatch
		cout << "TiffImage::Draw() called" << endl;
	}
	Dimension GetDimensionInPixels()
	{
		return Dimension(dimensionX, dimensionY);
	}

	// driver code
	//Image<TiffImage>* pImage = new TiffImage;
	//pImage->Draw();
};