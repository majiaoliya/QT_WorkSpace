///********
//*本代码参考自雷神博客
//*
//**********/
//#ifdef __cplusplus
//extern "C"
//{
//#endif
//#include <libavcodec/avcodec.h>
//#include <libavformat/avformat.h>
//#include <libavdevice/avdevice.h>
//#include<libswresample/swresample.h>
//#include <libavutil/pixfmt.h>
//#include <libswscale/swscale.h>
//#include <gtk/gtk.h>
//#ifdef __cplusplus
//};
//#endif

//#define MAX_AUDIO_FRAME_SIZE  192000
//#define SAMPLE_PRT(fmt...)   \
//    do {\
//        printf("[%s]-%d: ", __FUNCTION__, __LINE__);\
//        printf(fmt);\
//       }while(0)

////'1': Use H.264 Bitstream Filter
//#define USE_H264BSF 1

//void save_pnm(AVFrame *pFrame, int w, int h,int index)
//{

//  FILE *fl;
//  char szFilename[32];
//  int  y;

//  // Open file
//  sprintf(szFilename, "%d.pnm", index);
//  fl=fopen(szFilename, "wb");

//  if(fl==NULL)
//    return;

//  fprintf(fl, "P6\n%d %d\n255\n", w, h); // 加入pnm文件头
//  // Write pixel data
//  for(y=0; y<h; y++)
//  {
//    fwrite(pFrame->data[0]+y*pFrame->linesize[0], 1, w*3, fl);
//  }

//  // Close file
//  fclose(fl);

//}


//int main(int argc, char *argv[]) {
//    char *file_path = "/home/majiao/桌面/ffmpeg_hello/12.mp4";

//    AVFormatContext *pFormatCtx;
//    AVCodecContext *pCodecCtx;
//    AVCodec *pCodec;
//    AVFrame *pFrame, *pFrameRGB;
//    AVPacket *packet;
//    uint8_t *out_buffer;

//    static struct SwsContext *img_convert_ctx;

//    int videoStream, i, numBytes;
//    int ret, got_picture;

//    av_register_all(); //初始化FFMPEG  调用了这个才能正常适用编码器和解码器

//    //Allocate an AVFormatContext.
//    pFormatCtx = avformat_alloc_context();

//    if (avformat_open_input(&pFormatCtx, file_path, NULL, NULL) != 0) {
//        SAMPLE_PRT("open file error\n");
//        return -1;
//    }

//    if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
//        SAMPLE_PRT("Could't find stream infomation\n");
//        return -1;
//    }

//    videoStream = -1;

//    for (i = 0; i < pFormatCtx->nb_streams; i++) {
//        if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
//            videoStream = i;
//        }
//    }

//    if (videoStream == -1) {
//        SAMPLE_PRT("no find vedio_stream");
//        return -1;
//    }

//    ///查找解码器
//    pCodecCtx = pFormatCtx->streams[videoStream]->codec;
//    pCodec = avcodec_find_decoder(pCodecCtx->codec_id);

//    if (pCodec == NULL) {
//        SAMPLE_PRT(" not found decodec.\n");
//        return -1;
//    }

//    ///打开解码器
//    if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
//        SAMPLE_PRT("Could not open decodec.");
//        return -1;
//    }

//    pFrame = av_frame_alloc();
//    pFrameRGB = av_frame_alloc();

//    img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height,
//            pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height,
//            AV_PIX_FMT_RGB24, SWS_BICUBIC, NULL, NULL, NULL);

//    numBytes = avpicture_get_size(AV_PIX_FMT_RGB24, pCodecCtx->width,pCodecCtx->height);

//    out_buffer = (uint8_t *) av_malloc(numBytes * sizeof(uint8_t));
//    avpicture_fill((AVPicture *) pFrameRGB, out_buffer, AV_PIX_FMT_RGB24,
//            pCodecCtx->width, pCodecCtx->height);

//    int y_size = pCodecCtx->width * pCodecCtx->height;

//    packet = (AVPacket *) malloc(sizeof(AVPacket)); //分配一个packet
//    av_new_packet(packet, y_size); //分配packet的数据

//    av_dump_format(pFormatCtx, 0, file_path, 0); //输出视频信息

//    int index = 0;
//    av_seek_frame(pFormatCtx, -1, 25 * AV_TIME_BASE, AVSEEK_FLAG_BACKWARD);



//    cairo_surface_t* image;
//    image = cairo_image_surface_create_for_data()


//    while (av_read_frame(pFormatCtx, packet) >=0){
//        if (packet->stream_index == videoStream) {
//            ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture,packet);
//            long long int dur = packet->duration, idx = packet->stream_index, pst = packet->pts;
//            printf("%lld idx:%lld pst:%lld\n", dur, idx, pst);
//            if (ret < 0) {
//                SAMPLE_PRT("decode error.");
//                return -1;
//            }

//            if (got_picture) {
//                sws_scale(img_convert_ctx,
//                        (uint8_t const * const *) pFrame->data,
//                        pFrame->linesize, 0, pCodecCtx->height, pFrameRGB->data,
//                        pFrameRGB->linesize);

//                save_pnm(pFrameRGB, pCodecCtx->width,pCodecCtx->height,index++); //保存图片
//                if (index > 100) return 0; //100张
//            }
//        }
//        av_free_packet(packet);
//    }
//    av_free(out_buffer);
//    av_free(pFrameRGB);
//    avcodec_close(pCodecCtx);
//    avformat_close_input(&pFormatCtx);

//    return 0;
//}
















#include "goat-audio-video-frame.h"


typedef struct _GoatAudioVideoFramePrivate
{
    GMutex cond_mutex;
    GCond cond;
    guint timer;
    gpointer ringbuffer;
    cairo_surface_t next_frame_surf;
} GoatAudioVideoFramePrivate;


G_DEFINE_TYPE_WITH_PRIVATE (GoatAudioVideoFrame, goat_audio_video_frame, GTK_TYPE_DRAWING_AREA)


static void
goat_audio_video_frame_finalize (GObject *object)
{
    G_OBJECT_CLASS (goat_audio_video_frame_parent_class)->finalize (object);
}


static void
goat_audio_video_frame_class_init (GoatAudioVideoFrameClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS (klass);

    object_class->finalize = goat_audio_video_frame_finalize;
}


static void
goat_audio_video_frame_init (GoatAudioVideoFrame *self)
{
    gtk_widget_set_size_request (drawing_area, 100, 100);
    g_signal_connect (G_OBJECT (self), "draw", G_CALLBACK (draw_callback), NULL);

    //FIXME ringbuffer would be nicer
    GoatAudioVideoFramePrivate *priv = GOAT_AUDIO_VIDEO_FRAME_GET_PRIVATE (self);

    g_mutex_init (&priv->cond_mutex);
    g_cond_init (&priv->cond);
    priv->next_frame_surf = NULL;
    priv->timer = 0;
    priv->ringbuffer = ...; //TODO
}


GoatAudioVideoFrame *
goat_audio_video_frame_new ()
{
    return g_object_new (GOAT_TYPE_AUDIO_VIDEO_FRAME, NULL);
}


/**
 * cyclic drawing
 */
gboolean
timer_callback (GSource *source, gpointer data)
{
    g_mutex_lock (&priv->cond_mutex);
    g_cond_signal (&priv->cond_mutex);

    cairo_surface_t *nfs = ring_buffer_pop();
    if (priv->next_frame_surf) {
        cairo_surface_destroy (priv->next_frame_surf);
    }
    priv->next_frame_surf = nfs;
    g_mutex_unlock (&priv->cond_mutex);

    if (nfs) {
        gtk_widget_queue_draw (GTK_WIDGET (data));
    }
    return G_SOURCE_CONTINUE;
}


gboolean
realize_callback (GtkWidget *widget, gpointer data)
{

}


gboolean
draw_callback (GtkWidget *widget, cairo_t *cr, gpointer data)
{
    guint width, height;
    GdkRGBA color;

    width = gtk_widget_get_allocated_width (widget);
    height = gtk_widget_get_allocated_height (widget);

    if (priv->next_frame_surf!=NULL) {
        cairo_set_source_surface (cr, priv->next_frame_surf);
    } else {
        cairo_arc (cr,
                 width / 2.0, height / 2.0,
                 MIN (width, height) / 2.0,
                 0, 2 * G_PI);

        gtk_style_context_get_color (gtk_widget_get_style_context (widget),
                                     0,
                                     &color);
        gdk_cairo_set_source_rgba (cr, &color);

    }

    cairo_fill (cr);

    return FALSE;
}



/**
 * virtual func
 */
cairo_surface_t *
goat_decode_single_frame (GoatAudioVideoFrame *self) {
    return NULL; //FIXME TODO
}


/**
 * a thread
 */
gpointer
decoder_thread (gpointer user_data)
{
    GoatAudioVideoFrame *self = user_data;
    GoatAudioVideoFramePrivate *priv = GOAT_AUDIO_VIDEO_FRAME_GET_PRIVATE (self);

    while (priv->game_over==TRUE || priv->eof==TRUE) {
        while (goat_ring_buffer_is_full (ringbuffer)==TRUE || ring_buffer_length (priv->ringbuffer) > 120)
            g_mutex_lock (&priv->cond_mutex);
            g_cond_wait (&priv->cond, &priv->cond_mutex);
            g_mutex_unlock (&priv->cond_mutex);
        }
        cairo_surface_t *frame_surf = decode_single_frame ();
        if (frame_surf) {
            goat_ring_buffer_append (priv->ringbuffer, frame_surf);
        }
    }
    return NULL;
}


gboolean
goat_audio_video_frame_pause ()
{
    if (priv->timer!=0) {
        g_source_remove_by_id (priv->timer);
        priv->timer = 0;
    }
}

gboolean
goat_audio_video_frame_unpause ()
{
    if (priv->timer == 0) {
        priv->timer = g_timeout_add ((GSourceFunc)timer_callback);
    }
}














