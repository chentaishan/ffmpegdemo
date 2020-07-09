//
//  test.c
//  myApp
//
//  Created by chents on 2020/6/29.
//  Copyright © 2020 chents. All rights reserved.
//

#include "test.h"
#include <string.h>

static int rec_status=0;

void setStatus(int status){
    rec_status = status;
}

SwrContext* init(){
    
    SwrContext* swr_ctx =NULL;
    
//    channel number
    swr_ctx = swr_alloc_set_opts(swr_ctx,           //上下文
                                 AV_CH_LAYOUT_STEREO,//输出channel布局
                                 AV_SAMPLE_FMT_S16,// 输出采样格式
                                 44100,//采样率
                                  AV_CH_LAYOUT_STEREO// 输入channel布局
                                 , AV_SAMPLE_FMT_FLT  // 输入采样格式
                                 , 44100
                                 , 0,NULL);
    
    
    return swr_ctx;
    
}

void rec_audio(){
    char errors[1024] = {0, };

    int ret=0;
    AVDictionary **avdiction =NULL;
    AVFormatContext **ps=NULL;
    
    char* device_name = ":0";
    
    rec_status =1;
    
    avdevice_register_all();
    
    
    AVInputFormat *avformat=  av_find_input_format("avfoundation");
    
    if (ret=avformat_open_input(&ps, device_name, avformat, &avdiction)<0) {
        av_strerror(ret, errors, 1024);
        
        printf( "open file failed!");
        
        return;
    }
    
    char *out = "/Users/chents/Desktop/a.pcm";
    FILE* file = fopen(out, "wb+");
    
    
    SwrContext* swrContext = init();
    
    // 创建缓存区
    uint8_t** src_data = NULL;
    
    uint8_t** dst_data = NULL;
    int src_line=0;
    int dst_line=0;
    
    
    av_samples_alloc_array_and_samples(&src_data,         //输出缓冲区地址
                                       &src_line,     //缓冲区的大小
                                       2,                 //通道个数
                                       512,               //单通道采样个数
                                       AV_SAMPLE_FMT_FLT, //采样格式
                                       0);
    
    
    
    av_samples_alloc_array_and_samples(&dst_data,         //输出缓冲区地址
                                       &dst_line,     //缓冲区的大小
                                       2,                 //通道个数
                                       512,               //单通道采样个数
                                       AV_SAMPLE_FMT_S16, //采样格式
                                       0);
    AVPacket pkt;
    
    while((ret = av_read_frame(ps, &pkt)==0)&&rec_status){
        
        av_log(NULL, AV_LOG_INFO,  "packet size is %d--%p",pkt.size,pkt.data);
        
//        memcpy(&src_data, <#const void *__src#>, <#size_t __n#>)
        memcpy((void*)src_data[0], (void*)pkt.data, pkt.size);
        
        // 重采样
        
        swr_convert(swrContext, dst_data, dst_line, src_data, src_line);
        
        fwrite(dst_data[0], 1, dst_line, out);
        fflush(out);
        av_packet_unref(&pkt); //release pkt
        
    }
    
    fclose(out);
    
    if (src_data) {
        av_freep(&src_data[0]);
    }
    
    if(dst_data){
        av_freep(&dst_data[0]);
    }
    av_freep(dst_data);
    
    //释放重采样的上下文
    swr_free(&swrContext);
    
    //close device and release ctx
    avformat_close_input(&ps);
    
    av_log(NULL, AV_LOG_DEBUG, "finish!\n");
    
    
}


void hello(){
    int ret=0;
    AVPacket * avt;
    AVFormatContext *formatCtx=NULL;
    char *devicename = ":0";//音频设备0
    AVDictionary *options= NULL;
    char errors[1024];
    
    printf("hello! this is C ");
    
    avdevice_register_all();
    
    AVInputFormat *avformat=  av_find_input_format("avfoundation");
    
    
    
    if ((ret=avformat_open_input(&formatCtx,  devicename,  avformat,   &options))<0) {
        av_strerror(ret,  errors, 1024);
        
        printf("reuslt===%d",ret);
        return;
    }
    
//    哼哼唧唧就
    
    av_log_set_level(AV_LOG_DEBUG);
    av_log(NULL, AV_LOG_INFO, "hello world!");
    

    av_init_packet( avt);
    
    
    
    return;
}
