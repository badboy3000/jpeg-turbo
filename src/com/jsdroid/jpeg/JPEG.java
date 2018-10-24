package com.jsdroid.jpeg;

import android.graphics.Bitmap;

public class JPEG {
    static {
        System.loadLibrary("jpeg");
    }
    public static native byte[] encode(Bitmap bitmap);
}
