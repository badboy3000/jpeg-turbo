#ifndef MINICAP_JPG_ENCODER_HPP
#define MINICAP_JPG_ENCODER_HPP

#include <turbojpeg.h>
#define FORMAT_RGBA_8888 1
#define FORMAT_RGBX_8888 2
#define FORMAT_RGB_888 3
#define FORMAT_BGRA_8888 4

struct JpegFrame {
	void const* data;//
	int format;//FORMAT_RGBA
	uint32_t width;//bitmap.width
	uint32_t height;//bitmap.height
	uint32_t stride;//=width
	uint32_t bpp;//android::bytesPerPixel(android::PIXEL_FORMAT_RGB_888)
	unsigned int  size;//mBuffer.stride * mBuffer.height * JpegFrame->bpp
};

class JpgEncoder {
public:
  JpgEncoder(unsigned int prePadding, unsigned int postPadding);

  ~JpgEncoder();

  bool
  encode(JpegFrame* frame, unsigned int quality);

  int
  getEncodedSize();

  unsigned char*
  getEncodedData();

  bool
  reserveData(uint32_t width, uint32_t height);
 
private:
  tjhandle mTjHandle;
  int mSubsampling;
  unsigned int mPrePadding;
  unsigned int mPostPadding;
  unsigned int mMaxWidth;
  unsigned int mMaxHeight;
  unsigned char* mEncodedData;
  unsigned long mEncodedSize;

};

#endif
