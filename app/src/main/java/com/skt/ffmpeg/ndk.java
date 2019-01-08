package com.skt.ffmpeg;

public class ndk {

    static {

        System.loadLibrary("ffmpeg_wrapper");
    }

    public native int merge3(String videoPath, String micPath, String bgmPath, String outPath, boolean log);

    public native int merge2(String videoPath, String micPath, String outPath, boolean log);

    public native int progress();
}
