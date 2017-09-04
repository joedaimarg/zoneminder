#ifndef ZM_FFMPEG_INPUT_H
#define ZM_FFMPEG_INPUT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "libavformat/avformat.h"
#include "libavformat/avio.h"
#include "libavcodec/avcodec.h"

#ifdef __cplusplus
}
#endif

class FFmpeg_Input {

  public:
    FFmpeg_Input();
    ~FFmpeg_Input();

    int Open( const char *filename );
    int Close();
    AVFrame *get_frame( int stream_id=-1 );
    int get_video_stream_id() {
      return video_stream_id;
    }
    int get_audio_stream_id() {
      return audio_stream_id;
    }

    AVPacket *  read_packet();
    int         read_packet( AVPacket *packet );
    AVFrame *   decode_packet( AVPacket *packet );
    int         decode_packet( AVPacket *packet, AVFrame *frame );

  private:
    typedef struct {
        AVCodecContext *context;
        AVCodec *codec;
        int frame_count;
    } stream;

    stream streams[2];
    int video_stream_id;
    int audio_stream_id;
    AVFormatContext *input_format_context;
};

#endif
