#include<jni.h>
#include <JpgEncoder.hpp>
#include<android/bitmap.h>
#define JNIREG_CLASS "Lcom.jsdroid.jpeg.JPEG;"
#include<android/log.h>

#define TAG "jpeg-jni" // 自定义的LOG的标识 
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,TAG ,__VA_ARGS__) // 定义LOGD类型 
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__) // 定义LOGI类型 
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,TAG ,__VA_ARGS__) // 定义LOGW类型 
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__) // 定义LOGE类型 
#define LOGF(...) __android_log_print(ANDROID_LOG_FATAL,TAG ,__VA_ARGS__) // 定义LOGF类型 



#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

static JpgEncoder encoder(4, 0);
static JpegFrame frame;
//encoder.reserveData(realInfo.width, realInfo.height)

//encoder.encode(&frame, quality)
//jbyte* data =(jbyte*) encoder.getEncodedData();
//int size = encoder.getEncodedSize();


//java接口函数
//private static native int processBitmap(Bitmap bitmap);
//对应C++函数
extern "C"
JNIEXPORT jbyteArray JNICALL
Java_com_jsdroid_jpeg_JPEG_encode
(JNIEnv *env, jclass type,jobject bmpObj){
	
	AndroidBitmapInfo bmpInfo;
	memset(&bmpInfo, 0, sizeof(bmpInfo));
    if(AndroidBitmap_getInfo(env,bmpObj,&bmpInfo)<0){
		LOGE("not get info.");
		return NULL;
	}
	frame.width = bmpInfo.width;
	frame.height = bmpInfo.height;
	frame.stride = bmpInfo.width;
	frame.format = FORMAT_RGBA_8888;
	frame.bpp = 4;
	frame.size = frame.width *frame.height*4;
	
	int* dataFromBmp=NULL;
	//锁定图片数据
	if (AndroidBitmap_lockPixels(env,bmpObj,(void**)&dataFromBmp)){
		//失败
		LOGE("not get pixels.");
		return NULL;
	}
	frame.data = dataFromBmp;
	LOGE("data:%d",sizeof(*dataFromBmp));
	LOGE("width:%d",(frame.width));
	LOGE("height:%d",(frame.height));
	LOGE("stride:%d",(frame.stride));
	//编码
	if(!encoder.reserveData(frame.width, frame.height)){
		//释放图片数据
		LOGE("not get reserveData.");
		return NULL;
	}
	//获取编码内容
	encoder.encode(&frame,80);
	//获取编码大小
	size_t size = encoder.getEncodedSize();
	
	LOGE("size:%dbytes",size);
	jbyteArray bytes = 0;
	bytes = env->NewByteArray(size);
	env->SetByteArrayRegion(bytes, 0, size, (const jbyte*)encoder.getEncodedData());
	
	
	//释放图片数据
	AndroidBitmap_unlockPixels(env,bmpObj);	
	return bytes;
}




















