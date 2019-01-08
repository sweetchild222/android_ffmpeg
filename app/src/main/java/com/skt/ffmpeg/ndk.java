package com.skt.ffmpeg;

public class ndk {

    static {

        System.loadLibrary("ffmpeg_wrapper");
    }

    public native int merge(String videoPath, String bgmPath, String micPath, String outPath, boolean log);

    public native int progress();
}
