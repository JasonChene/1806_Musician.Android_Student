//
//  Agora Rtc Engine SDK
//
//  Copyright (c) 2018 Agora.io. All rights reserved.
//

#ifndef AGORA_RTC_ENGINE_H
#define AGORA_RTC_ENGINE_H
#include "AgoraBase.h"
#include "IAgoraService.h"

namespace agora {
namespace rtc {
    typedef unsigned int uid_t;
    typedef void* view_t;
/** Maximum device ID length.
*/
enum MAX_DEVICE_ID_LENGTH_TYPE
{
  /** The maximum device ID length is 512.
  */
    MAX_DEVICE_ID_LENGTH = 512
};
/** Format of the quality report.
*/
enum QUALITY_REPORT_FORMAT_TYPE
{
  /** 0: The quality report in JSON format,
  */
    QUALITY_REPORT_JSON = 0,
    /** 1: The quality report in HTML format.
    */
    QUALITY_REPORT_HTML = 1,
};

enum MEDIA_ENGINE_EVENT_CODE_TYPE
{
    MEDIA_ENGINE_RECORDING_ERROR = 0,
    MEDIA_ENGINE_PLAYOUT_ERROR = 1,
    MEDIA_ENGINE_RECORDING_WARNING = 2,
    MEDIA_ENGINE_PLAYOUT_WARNING = 3,
    MEDIA_ENGINE_AUDIO_FILE_MIX_FINISH = 10,
    MEDIA_ENGINE_AUDIO_FAREND_MUSIC_BEGINS = 12,
    MEDIA_ENGINE_AUDIO_FAREND_MUSIC_ENDS = 13,
    // media engine role changed
    MEDIA_ENGINE_ROLE_BROADCASTER_SOLO = 20,
    MEDIA_ENGINE_ROLE_BROADCASTER_INTERACTIVE = 21,
    MEDIA_ENGINE_ROLE_AUDIENCE = 22,
    MEDIA_ENGINE_ROLE_COMM_PEER = 23,
    MEDIA_ENGINE_ROLE_GAME_PEER = 24,
    // iOS adm sample rate changed
    MEDIA_ENGINE_AUDIO_ADM_REQUIRE_RESTART = 110,
    MEDIA_ENGINE_AUDIO_ADM_SPECIAL_RESTART = 111,
};
/** Media device state.
*/
enum MEDIA_DEVICE_STATE_TYPE
{
  /** 1: The device is active.
  */
    MEDIA_DEVICE_STATE_ACTIVE = 1,
    /** 2: The device is disabled.
    */
    MEDIA_DEVICE_STATE_DISABLED = 2,
    /** 4: The device is not present.
    */
    MEDIA_DEVICE_STATE_NOT_PRESENT = 4,
    /** 8: The device is unplugged.
    */
    MEDIA_DEVICE_STATE_UNPLUGGED = 8
};

/** Media device type.
*/
enum MEDIA_DEVICE_TYPE
{
  /** -1: Unknown device type.
  */
    UNKNOWN_AUDIO_DEVICE = -1,
    /** 0: Audio playback device.
    */
    AUDIO_PLAYOUT_DEVICE = 0,
    /** 1: Audio recording device.
    */
    AUDIO_RECORDING_DEVICE = 1,
    /** 2: Video renderer
    */
    VIDEO_RENDER_DEVICE = 2,
    /** 3: Video capturer
    */
    VIDEO_CAPTURE_DEVICE = 3,
    /** 4: Application audio playback device.
    */
    AUDIO_APPLICATION_PLAYOUT_DEVICE = 4,
};

/** Audio recording quality.
*/
enum AUDIO_RECORDING_QUALITY_TYPE
{
  /** 0: Low audio recording quality.
  */
    AUDIO_RECORDING_QUALITY_LOW = 0,
    /** 1: Medium audio recording quality.
    */
    AUDIO_RECORDING_QUALITY_MEDIUM = 1,
    /** 2: High audio recording quality.
    */
    AUDIO_RECORDING_QUALITY_HIGH = 2,
};

/** Network quality. */
enum QUALITY_TYPE
{
      /** 0: The network quality is unknown. */
    QUALITY_UNKNOWN = 0,
    /**  1: The network quality is excellent. */
    QUALITY_EXCELLENT = 1,
      /** 2: The network quality is quite good, but the bitrate may be slightly lower than excellent. */
    QUALITY_GOOD = 2,
      /** 3: Users can feel the communication slightly impaired. */
    QUALITY_POOR = 3,
      /** 4: Users can communicate only not very smoothly. */
    QUALITY_BAD = 4,
     /** 5: The network is so bad that users can hardly communicate. */
    QUALITY_VBAD = 5,
       /** 6: The network is down  and users cannot communicate at all. */
    QUALITY_DOWN = 6,
    QUALITY_UNSUPPORTED = 7,
};

/** Video display mode. */
enum RENDER_MODE_TYPE
{
  /**
1: Uniformly scale the video until it fills the visible boundaries (cropped). One dimension of the video may have clipped contents.
 */
    RENDER_MODE_HIDDEN = 1,
    /**
2: Uniformly scale the video until one of its dimension fits the boundary (zoomed to fit). Areas that are not filled due to the disparity in the aspect ratio will be filled with black.
 */
    RENDER_MODE_FIT = 2,
    /** @deprecated
     3：This mode is obsolete.
     */
    RENDER_MODE_ADAPTIVE = 3,
};

/** Video mirror mode. */
enum VIDEO_MIRROR_MODE_TYPE
{
      /** 0: Default mirror mode determined by the SDK. */
    VIDEO_MIRROR_MODE_AUTO = 0,//determined by SDK
        /** 1: Enabled mirror mode */
    VIDEO_MIRROR_MODE_ENABLED = 1,//enabled mirror
        /** 2: Disabled mirror mode */
    VIDEO_MIRROR_MODE_DISABLED = 2,//disable mirror
};

/** @deprecated
 Video profile. */
enum VIDEO_PROFILE_TYPE
{
    /** 0: 160 x 120  @ 15 fps */          // res       fps
    VIDEO_PROFILE_LANDSCAPE_120P = 0,         // 160x120   15
      /** 2: 120 x 120 @ 15 fps */
    VIDEO_PROFILE_LANDSCAPE_120P_3 = 2,       // 120x120   15
        /** 10: 320 x 180 @ 15 fps */
    VIDEO_PROFILE_LANDSCAPE_180P = 10,        // 320x180   15
        /** 12: 180 x 180  @ 15 fps */
    VIDEO_PROFILE_LANDSCAPE_180P_3 = 12,      // 180x180   15
        /** 13: 240 x 180 @ 15 fps */
    VIDEO_PROFILE_LANDSCAPE_180P_4 = 13,      // 240x180   15
        /** 20: 320 x 240 @ 15 fps */
    VIDEO_PROFILE_LANDSCAPE_240P = 20,        // 320x240   15
    /** 22: 240 x 240 @ 15 fps */
    VIDEO_PROFILE_LANDSCAPE_240P_3 = 22,      // 240x240   15
      /** 23: 424 x 240 @ 15 fps */
    VIDEO_PROFILE_LANDSCAPE_240P_4 = 23,      // 424x240   15
      /** 30: 640 x 360 @ 15 fps */
    VIDEO_PROFILE_LANDSCAPE_360P = 30,        // 640x360   15
      /** 32: 360 x 360 @ 15 fps */
    VIDEO_PROFILE_LANDSCAPE_360P_3 = 32,      // 360x360   15
    /** 33: 640 x 360 @ 30 fps */
    VIDEO_PROFILE_LANDSCAPE_360P_4 = 33,      // 640x360   30
      /** 35: 360 x 360 @ 30 fps */
    VIDEO_PROFILE_LANDSCAPE_360P_6 = 35,      // 360x360   30
    /** 36: 480 x 360 @ 15 fps */
    VIDEO_PROFILE_LANDSCAPE_360P_7 = 36,      // 480x360   15
      /** 37: 480 x 360 @ 30 fps */
    VIDEO_PROFILE_LANDSCAPE_360P_8 = 37,      // 480x360   30
      /** 38: 640 x 360 @ 15 fps */
    VIDEO_PROFILE_LANDSCAPE_360P_9 = 38,      // 640x360   15
        /** 39: 640 x 360 @ 24 fps */
    VIDEO_PROFILE_LANDSCAPE_360P_10 = 39,     // 640x360   24
      /** 100: 640 x 360 @ 24 fps */
    VIDEO_PROFILE_LANDSCAPE_360P_11 = 100,    // 640x360   24
      /** 40: 640 x 480 @ 15 fps */
    VIDEO_PROFILE_LANDSCAPE_480P = 40,        // 640x480   15
    /** 42: 480 x 480 @ 15 fps */
    VIDEO_PROFILE_LANDSCAPE_480P_3 = 42,      // 480x480   15
    /** 43: 640 x 480 @ 30 fps */
    VIDEO_PROFILE_LANDSCAPE_480P_4 = 43,      // 640x480   30
       /** 45: 480 x 480 @ 30 fps */
    VIDEO_PROFILE_LANDSCAPE_480P_6 = 45,      // 480x480   30
    /** 47: 848 x 480 @ 15 fps */
    VIDEO_PROFILE_LANDSCAPE_480P_8 = 47,      // 848x480   15
        /** 48: 848 x 480 @ 30 fps */
    VIDEO_PROFILE_LANDSCAPE_480P_9 = 48,      // 848x480   30
      /** 49: 640 x 480 @ 10 fps */
    VIDEO_PROFILE_LANDSCAPE_480P_10 = 49,     // 640x480   10
      /** 50: 1280 x 720 @ 15 fps */
    VIDEO_PROFILE_LANDSCAPE_720P = 50,        // 1280x720  15
    /** 52: 1280 x 720 @ 30 fps */
    VIDEO_PROFILE_LANDSCAPE_720P_3 = 52,      // 1280x720  30
      /** 54: 960 x 720 @ 15 fps */
    VIDEO_PROFILE_LANDSCAPE_720P_5 = 54,      // 960x720   15
      /** 55: 960 x 720 @ 30 fps */
    VIDEO_PROFILE_LANDSCAPE_720P_6 = 55,      // 960x720   30
    /** 60: 1920 x 1080 @ 15 fps */
    VIDEO_PROFILE_LANDSCAPE_1080P = 60,       // 1920x1080 15
    /** 62: 1920 x 1080 @ 30 fps */
    VIDEO_PROFILE_LANDSCAPE_1080P_3 = 62,     // 1920x1080 30
    /** 64: 1920 x 1080 @ 60 fps */
    VIDEO_PROFILE_LANDSCAPE_1080P_5 = 64,     // 1920x1080 60
    /** 66: 2560 x 1440 @ 30 fps */
    VIDEO_PROFILE_LANDSCAPE_1440P = 66,       // 2560x1440 30
      /** 67: 2560 x 1440 @ 60 fps */
    VIDEO_PROFILE_LANDSCAPE_1440P_2 = 67,     // 2560x1440 60
      /** 70: 3840 x 2160 @ 30 fps */
    VIDEO_PROFILE_LANDSCAPE_4K = 70,          // 3840x2160 30
    /** 72: 3840 x 2160 @ 60 fps */
    VIDEO_PROFILE_LANDSCAPE_4K_3 = 72,        // 3840x2160 60
/** 1000: 120 x 160 @ 15 fps */
    VIDEO_PROFILE_PORTRAIT_120P = 1000,       // 120x160   15
     /** 1002: 120 x 120 @ 15 fps */
    VIDEO_PROFILE_PORTRAIT_120P_3 = 1002,     // 120x120   15
        /** 1010: 180 x 320 @ 15 fps */
    VIDEO_PROFILE_PORTRAIT_180P = 1010,       // 180x320   15
      /** 1012: 180 x 180 @ 15 fps */
    VIDEO_PROFILE_PORTRAIT_180P_3 = 1012,     // 180x180   15
      /** 1013: 180 x 240 @ 15 fps */
    VIDEO_PROFILE_PORTRAIT_180P_4 = 1013,     // 180x240   15
      /** 1020: 240 x 320 @ 15 fps */
    VIDEO_PROFILE_PORTRAIT_240P = 1020,       // 240x320   15
    /** 1022: 240 x 240 @ 15 fps */
    VIDEO_PROFILE_PORTRAIT_240P_3 = 1022,     // 240x240   15
      /** 1023: 240 x 424 @ 15 fps */
    VIDEO_PROFILE_PORTRAIT_240P_4 = 1023,     // 240x424   15
    /** 1030: 360 x 640 @ 15 fps */
    VIDEO_PROFILE_PORTRAIT_360P = 1030,       // 360x640   15
    /** 1032: 360 x 360 @ 15 fps */
    VIDEO_PROFILE_PORTRAIT_360P_3 = 1032,     // 360x360   15
    /** 1033: 360 x 640 @ 30 fps */
    VIDEO_PROFILE_PORTRAIT_360P_4 = 1033,     // 360x640   30
        /** 1035: 360 x 360 @ 30 fps */
    VIDEO_PROFILE_PORTRAIT_360P_6 = 1035,     // 360x360   30
      /** 1036: 360 x 480 @ 15 fps */
    VIDEO_PROFILE_PORTRAIT_360P_7 = 1036,     // 360x480   15
      /** 1037: 360 x 480 @ 30 fps */
    VIDEO_PROFILE_PORTRAIT_360P_8 = 1037,     // 360x480   30
        /** 1038: 360 x 640 @ 15 fps */
    VIDEO_PROFILE_PORTRAIT_360P_9 = 1038,     // 360x640   15
      /** 1039: 360 x 640 @ 24 fps */
    VIDEO_PROFILE_PORTRAIT_360P_10 = 1039,    // 360x640   24
      /** 1100: 360 x 640 @ 24 fps */
    VIDEO_PROFILE_PORTRAIT_360P_11 = 1100,    // 360x640   24
      /** 1040: 480 x 640 @ 15 fps */
    VIDEO_PROFILE_PORTRAIT_480P = 1040,       // 480x640   15
    /** 1042: 480 x 480 @ 15 fps */
    VIDEO_PROFILE_PORTRAIT_480P_3 = 1042,     // 480x480   15
    /** 1043: 480 x 640 @ 30 fps */
    VIDEO_PROFILE_PORTRAIT_480P_4 = 1043,     // 480x640   30
        /** 1045: 480 x 480 @ 30 fps */
    VIDEO_PROFILE_PORTRAIT_480P_6 = 1045,     // 480x480   30
        /** 1047: 480 x 848 @ 15 fps */
    VIDEO_PROFILE_PORTRAIT_480P_8 = 1047,     // 480x848   15
      /** 1048: 480 x 848 @ 30 fps */
    VIDEO_PROFILE_PORTRAIT_480P_9 = 1048,     // 480x848   30
    /** 1049: 480 x 640 @ 10 fps */
    VIDEO_PROFILE_PORTRAIT_480P_10 = 1049,    // 480x640   10
      /** 1050: 720 x 1280 @ 15 fps */
    VIDEO_PROFILE_PORTRAIT_720P = 1050,       // 720x1280  15
      /** 1052: 720 x 1280 @ 30 fps */
    VIDEO_PROFILE_PORTRAIT_720P_3 = 1052,     // 720x1280  30
      /** 1054: 720 x 960 @ 15 fps */
    VIDEO_PROFILE_PORTRAIT_720P_5 = 1054,     // 720x960   15
       /** 1055: 720 x 960 @ 30 fps */
    VIDEO_PROFILE_PORTRAIT_720P_6 = 1055,     // 720x960   30
      /** 1060: 1080 x 1920 @ 15 fps */
    VIDEO_PROFILE_PORTRAIT_1080P = 1060,      // 1080x1920 15
        /** 1062: 1080 x 1920 @ 30 fps */
    VIDEO_PROFILE_PORTRAIT_1080P_3 = 1062,    // 1080x1920 30
        /** 1064: 1080 x 1920 @ 60 fps */
    VIDEO_PROFILE_PORTRAIT_1080P_5 = 1064,    // 1080x1920 60
      /** 1066: 1440 x 2560 @ 30 fps */
    VIDEO_PROFILE_PORTRAIT_1440P = 1066,      // 1440x2560 30
    /** 1067: 1440 x 2560 @ 60 fps */
    VIDEO_PROFILE_PORTRAIT_1440P_2 = 1067,    // 1440x2560 60
        /** 1070: 2160 x 3840 @ 30 fps */
    VIDEO_PROFILE_PORTRAIT_4K = 1070,         // 2160x3840 30
    /** 1072: 2160 x 3840 @ 60 fps */
    VIDEO_PROFILE_PORTRAIT_4K_3 = 1072,       // 2160x3840 60
    /** Default 640 x 360 @ 15 fps */
    VIDEO_PROFILE_DEFAULT = VIDEO_PROFILE_LANDSCAPE_360P,
};

/** Audio profile.

Sets the sampling rate, bitrate, encode mode, and the number of channels:*/
enum AUDIO_PROFILE_TYPE // sample rate, bit rate, mono/stereo, speech/music codec
{
  /**
 * 0: Default audio profile. In the communication mode, the default value is 1; in the live-broadcast mode, the default value is 2.
 */
    AUDIO_PROFILE_DEFAULT = 0, // use default settings
    /**
 * 1: Sampling rate 32 kHz, audio encoding, single channel, and bitrate up to 18 kbit/s.
 */
    AUDIO_PROFILE_SPEECH_STANDARD = 1, // 32Khz, 18kbps, mono, speech
    /**
 * 2: Sampling rate 48 kHz, music encoding, single channel, and bitrate up to 48 kbit/s.
 */
    AUDIO_PROFILE_MUSIC_STANDARD = 2, // 48Khz, 48kbps, mono, music
    /**
 * 3: Sampling rate 48 kHz, music encoding, dual-channel, and bitrate up to 56 kbit/s.
 */
    AUDIO_PROFILE_MUSIC_STANDARD_STEREO = 3, // 48Khz, 56kbps, stereo, music
    /**
 * 4: Sampling rate 48 kHz, music encoding, single channel, and bitrate up to 128 kbit/s.
 */
    AUDIO_PROFILE_MUSIC_HIGH_QUALITY = 4, // 48Khz, 128kbps, mono, music
    /**
 * 5: Sampling rate 48 kHz, music encoding, dual-channel, and bitrate up to 192 kbit/s.
 */
    AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO = 5, // 48Khz, 192kbps, stereo, music
    AUDIO_PROFILE_IOT                       = 6,   // G722
    AUDIO_PROFILE_NUM = 7,
};

/** Audio application scenario.
*/
enum AUDIO_SCENARIO_TYPE // set a suitable scenario for your app type
{
      /** 0: Default */
    AUDIO_SCENARIO_DEFAULT = 0,
      /** 1: Entertainment scenario that supports voice during gameplay */
    AUDIO_SCENARIO_CHATROOM_ENTERTAINMENT = 1,
      /** 2: Education scenario that prioritizes fluency and stability */
    AUDIO_SCENARIO_EDUCATION = 2,
    /** 3: Live gaming scenario that needs to enable the gaming audio effects  in the speaker mode in a live broadcast scenario. Choose this scenario if you wish to achieve high-fidelity music playback */
    AUDIO_SCENARIO_GAME_STREAMING = 3,
    /** 4: Showroom scenario that optimizes the audio quality with professional external equipment */
    AUDIO_SCENARIO_SHOWROOM = 4,
      /** 5: Gaming scenario */
    AUDIO_SCENARIO_CHATROOM_GAMING = 5,
    AUDIO_SCENARIO_IOT = 6,
    AUDIO_SCENARIO_NUM = 7,
};

 /** Channel profile.
 */
enum CHANNEL_PROFILE_TYPE
{
  /** 0: Communication.

   This is used in one-on-one calls, where all users in the channel can talk freely.*/
	CHANNEL_PROFILE_COMMUNICATION = 0,
  /** 1: Live Broadcast.

     Host and audience roles that can be set by calling IRtcEngine::setClientRole(). The host sends and receives voice, while the audience receives voice only with the sending function disabled.*/
	CHANNEL_PROFILE_LIVE_BROADCASTING = 1,
  /** 2: Gaming.

   Any user in the channel can talk freely. This mode uses the codec with low-power consumption and low bitrate by default.*/
    CHANNEL_PROFILE_GAME = 2,
};

/** Client role in a live broadcast. */
enum CLIENT_ROLE_TYPE
{
    /** 1: Host */
    CLIENT_ROLE_BROADCASTER = 1,
        /** 2: Audience */
    CLIENT_ROLE_AUDIENCE = 2,
};

/** Reason for the user being offline. */
enum USER_OFFLINE_REASON_TYPE
{
    /** 0: A user has quit the call. */
    USER_OFFLINE_QUIT = 0,
    /** 1: The SDK timed out and the user dropped offline because it has not received any data package within a certain period of time. If a user quits the call and the message is not passed to the SDK (due to an unreliable channel), the SDK assumes the event has timed out. */
    USER_OFFLINE_DROPPED = 1,
      /** 2: User switched to an audience */
    USER_OFFLINE_BECOME_AUDIENCE = 2,
};

/** Status of importing an external video stream in a live broadcast. */
enum INJECT_STREAM_STATUS
{
    /** 0: The external video stream imported successfully. */
    INJECT_STREAM_STATUS_START_SUCCESS = 0,
    /** 1: The external video stream already exists. */
    INJECT_STREAM_STATUS_START_ALREADY_EXISTS = 1,
        /** 2: The external video stream import is unauthorized */
    INJECT_STREAM_STATUS_START_UNAUTHORIZED = 2,
    /** 3: Import external video stream timeout. */
    INJECT_STREAM_STATUS_START_TIMEDOUT = 3,
      /** 4: The external video stream failed to import. */
    INJECT_STREAM_STATUS_START_FAILED = 4,
      /** 5: The external video stream imports successfully. */
    INJECT_STREAM_STATUS_STOP_SUCCESS = 5,
    /** 6: No external video stream is found. */
    INJECT_STREAM_STATUS_STOP_NOT_FOUND = 6,
        /** 7: The external video stream is stopped from being unauthorized. */
    INJECT_STREAM_STATUS_STOP_UNAUTHORIZED = 7,
    /** 8: Importing the external video stream timeout. */
    INJECT_STREAM_STATUS_STOP_TIMEDOUT = 8,
      /** 9: Importing the external video stream failed. */
    INJECT_STREAM_STATUS_STOP_FAILED = 9,
      /** 10: The external video stream is broken. */
    INJECT_STREAM_STATUS_BROKEN = 10,
};
/** Remote video stream type. */
enum REMOTE_VIDEO_STREAM_TYPE
{
      /** 0: High-video stream */
    REMOTE_VIDEO_STREAM_HIGH = 0,
      /** 1: Low-video stream */
    REMOTE_VIDEO_STREAM_LOW = 1,
};

/** Use mode of the onRecordAudioFrame callback. */
enum RAW_AUDIO_FRAME_OP_MODE_TYPE
{
  /** 0: Read-only mode: Users only read the agora::media::IAudioFrameObserver::AudioFrame data without modifying anything. For example, when users acquire data with the Agora SDK then push the RTMP streams. */
    RAW_AUDIO_FRAME_OP_MODE_READ_ONLY = 0,
    /** 1: Write-only mode: Users replace the AudioFrame data with their own data and pass them to the SDK for encoding. For example, when users acquire data. */
    RAW_AUDIO_FRAME_OP_MODE_WRITE_ONLY = 1,
    /** 2: Read and write mode: Users read the data from AudioFrame, modify it, and then play it. For example, when users have their own sound-effect processing module and do some voice pre-processing such as a voice change. */
    RAW_AUDIO_FRAME_OP_MODE_READ_WRITE = 2,
};

/** Audio-sampling rate. */
enum AUDIO_SAMPLE_RATE_TYPE
{
    /** 32000: 32 kHz */
    AUDIO_SAMPLE_RATE_32000 = 32000,
    /** 44100: 44.1 kHz */
    AUDIO_SAMPLE_RATE_44100 = 44100,
      /** 48000: 48 kHz */
    AUDIO_SAMPLE_RATE_48000 = 48000,
};

/** Video codec profile type. */
enum VIDEO_CODEC_PROFILE_TYPE
{  /** 66: Baseline video codec profile. */
    VIDEO_CODEC_PROFILE_BASELINE = 66,
    /** 77: Main video codec profile. */
    VIDEO_CODEC_PROFILE_MAIN = 77,
      /**  100: High video codec profile (default) */
    VIDEO_CODEC_PROFILE_HIGH = 100,
};

/** Audio equalization band frequency. */
enum AUDIO_EQUALIZATION_BAND_FREQUENCY
{
    /** 0: 31 Hz */
    AUDIO_EQUALIZATION_BAND_31 = 0,
      /** 1: 62 Hz */
    AUDIO_EQUALIZATION_BAND_62 = 1,
    /** 2: 125 Hz */
    AUDIO_EQUALIZATION_BAND_125 = 2,
      /** 3: 250 Hz */
    AUDIO_EQUALIZATION_BAND_250 = 3,
      /** 4: 500 Hz */
    AUDIO_EQUALIZATION_BAND_500 = 4,
        /** 5: 1 kHz */
    AUDIO_EQUALIZATION_BAND_1K = 5,
        /** 6: 2 kHz */
    AUDIO_EQUALIZATION_BAND_2K = 6,
        /** 7: 4 kHz */
    AUDIO_EQUALIZATION_BAND_4K = 7,
        /** 8: 8 kHz */
    AUDIO_EQUALIZATION_BAND_8K = 8,
      /** 9: 16 kHz */
    AUDIO_EQUALIZATION_BAND_16K = 9,
};

/** Audio reverberation type. */
enum AUDIO_REVERB_TYPE
{
    /** 0: (dB, -20 to 10), the level of the dry signal */
    AUDIO_REVERB_DRY_LEVEL = 0, // (dB, [-20,10]), the level of the dry signal
/** 1: (dB, -20 to 10), the level of the early reflection signal (wet signal) */
    AUDIO_REVERB_WET_LEVEL = 1, // (dB, [-20,10]), the level of the early reflection signal (wet signal)
    /** 2: (0 to 100), the room size of the reflection */
    AUDIO_REVERB_ROOM_SIZE = 2, // ([0, 100]), the room size of the reflection
    /** 3: (ms, 0 to 200), the length of the initial delay of the wet signal in ms */
    AUDIO_REVERB_WET_DELAY = 3, // (ms, [0, 200]), the length of the initial delay of the wet signal in ms
    /** 3: (0 to 100), the strength of the late reverberation */
    AUDIO_REVERB_STRENGTH = 4, // ([0, 100]), the strength of the late reverberation
};

/** Remote video state. */
enum REMOTE_VIDEO_STATE
{
    // REMOTE_VIDEO_STATE_STOPPED is not used at this version. Ignore this value.
    // REMOTE_VIDEO_STATE_STOPPED = 0,  // Default state, video is started or remote user disabled/muted video stream
      /** 1: Remote video is playing. */
      REMOTE_VIDEO_STATE_RUNNING = 1,  // Running state, remote video can be displayed normally
      /** 2: Remote video is frozen. */
      REMOTE_VIDEO_STATE_FROZEN = 2,    // Remote video is frozen, probably due to network issue.
};

/** Video frame rate. */
enum FRAME_RATE
{
      /** 1: 1 fps */
    FRAME_RATE_FPS_1 = 1, // 1 frame per second
        /** 7: 7 fps */
    FRAME_RATE_FPS_7 = 7, // 7 frames per second
      /** 10: 10 fps */
    FRAME_RATE_FPS_10 = 10, // 10 frames per second
    /** 15: 15 fps */
    FRAME_RATE_FPS_15 = 15, // 15 frames per second
        /** 24: 24 fps */
    FRAME_RATE_FPS_24 = 24, // 24 frames per second
    /** 30: 30 fps */
    FRAME_RATE_FPS_30 = 30, // 30 frames per second
    /** 60: 60 fps */
    FRAME_RATE_FPS_60 = 60, // 60 frames per second @ [Platform=(WINDOWS, MacOS)]
};

/** Video output orientation mode.
 */
enum ORIENTATION_MODE {
  /** 0: Adaptive mode (Default).

   The video encoder adapts to the orientation mode of the video input device.

   - If the width of the captured video from the SDK is larger than the height, the video sent out by the encoder is in landscape mode. The encoder also sends out the rotational information of the video, and the receiving end will rotate the received video based on the rotational information.
   - When a custom video source is used, the output video from the encoder inherits the orientation of the original video. If the original video is in  portrait mode, the output video from the encoder is also in portrait mode. The encoder also sends out the rotational information of the video to the receiver.

   */
    ORIENTATION_MODE_ADAPTIVE = 0,
    /** 1: Landscape mode.

The video encoder always sends out the video in landscape mode. The original video is rotated before being sent out and the rotational information is therefore 0. This mode applies to scenarios involving CDN streaming.
   */
    ORIENTATION_MODE_FIXED_LANDSCAPE = 1,
    /** 2: Portrait mode.

The video encoder always sends out the video in portrait mopde. The original video is rotated before being sent out and the rotational information is therefore 0. This mode applies to scenarios involving CDN streaming.*/
    ORIENTATION_MODE_FIXED_PORTRAIT = 2,
};

/** Stream fallback options. */
enum STREAM_FALLBACK_OPTIONS
{
  /** 0: (Default) No fallback operation for the stream when the network condition is poor. The stream quality cannot be guaranteed. */

    STREAM_FALLBACK_OPTION_DISABLED = 0,
    /** 1: Under poor network conditions, the SDK will send or receive agora::rtc::REMOTE_VIDEO_STREAM_LOW. You can only set this option in RtcEngineParameters::setRemoteSubscribeFallbackOption. Nothing happens when you set this in RtcEngineParameters::setLocalPublishFallbackOption. */
    STREAM_FALLBACK_OPTION_VIDEO_STREAM_LOW = 1,
    /** 2: Under poor network conditions, the SDK may receive agora::rtc::REMOTE_VIDEO_STREAM_LOW first, but if the network still does not allow displaying the video, the SDK will send or receive audio only. */
    STREAM_FALLBACK_OPTION_AUDIO_ONLY = 2,
};

/** Properties of the audio volume information.
 */
struct AudioVolumeInfo
{
  /**
 User ID of the speaker.
 */
    uid_t uid;
    /**
 The volume of the speaker that ranges from 0 (lowest volume) to 255 (highest volume).
 */
    unsigned int volume; // [0,255]
};

/** Statistics of the channel.
 */
struct RtcStats
{
  /**
 Call duration (s), represented by an aggregate value.
 */
    unsigned int duration;
    /**
 Total number of bytes transmitted, represented by an aggregate value.
 */
    unsigned int txBytes;
    /**
  Total number of bytes received, represented by an aggregate value.
 */
    unsigned int rxBytes;
    /**
 Transmission bitrate (kbit/s), represented by an instantaneous value.
 */
    unsigned short txKBitRate;
    /**
 Receive bitrate (kbit/s), represented by an instantaneous value.
 */
    unsigned short rxKBitRate;
    /**
     Audio receive bitrate (kbit/s), represented by an instantaneous value.
     */
    unsigned short rxAudioKBitRate;
    /**
 Audio transmission bitrate (kbit/s), represented by an instantaneous value.
 */
    unsigned short txAudioKBitRate;
    /**
     Video receive bitrate (kbit/s), represented by an instantaneous value.
     */
    unsigned short rxVideoKBitRate;
    /**
 Video transmission bitrate (kbit/s), represented by an instantaneous value.
 */
    unsigned short txVideoKBitRate;
    /**
VOS client-server latency (ms)
 */
    unsigned short lastmileDelay;
    /**
 Number of users in the channel.
 */
    unsigned int userCount;
    /**
 Application CPU usage (%).
 */
    double cpuAppUsage;
    /**
 System CPU usage (%).
 */
    double cpuTotalUsage;
};

/** Statistics of the local video stream.
 */
struct LocalVideoStats
{
  /**
 Total bytes sent since last count.
 */
    int sentBitrate;
    /**
 Total frames sent since last count.
 */
    int sentFrameRate;
};
/** Statistics of the remote video stream.
 */
struct RemoteVideoStats
{
  /**
 User ID of the user whose video streams are received.
 */
    uid_t uid;
    /** @deprecated Time delay (ms).
 */
    int delay;
/**
 Width (pixels) of the video stream.
 */
	int width;
  /**
 Height (pixels) of the video stream.
 */
	int height;
  /**
 Data receive bitrate (kbit/s) since last count.
 */
	int receivedBitrate;
  /**
 Data receive frame rate (fps) since last count.
 */
	int receivedFrameRate;
  /**
   Remote video stream type, high- or low-video stream: agora::rtc::REMOTE_VIDEO_STREAM_TYPE

 */
    REMOTE_VIDEO_STREAM_TYPE rxStreamType;
};

/** Rtc video compositing layout.
 */
struct VideoCompositingLayout
{
    struct Region {
      /** User ID of the user whose video is to be displayed in the region.
      */
        uid_t uid;
        /** Horizontal position of the region on the screen.
        */
        double x;//[0,1]
        /** Vertical position of the region on the screen.
        */
        double y;//[0,1]
        /**
Actual width of the region.
 */
        double width;//[0,1]
        /**
Actual height of the region. */
        double height;//[0,1]
        /** 0 means the region is at the bottom, and 100 means the region is at the top.
        */
        int zOrder; //optional, [0, 100] //0 (default): bottom most, 100: top most

    /** 0 means the region is transparent, and 1 means the region is opaque. The default value is 1.0.
    */
        double alpha;

        RENDER_MODE_TYPE renderMode;//RENDER_MODE_HIDDEN: Crop, RENDER_MODE_FIT: Zoom to fit
        Region()
            :uid(0)
            , x(0)
            , y(0)
            , width(0)
            , height(0)
            , zOrder(0)
            , alpha(1.0)
            , renderMode(RENDER_MODE_HIDDEN)
        {}

    };
    /** Ignore this parameter. The width of the canvas is set by agora::rtc::IRtcEngine::configPublisher, and not by agora::rtc::VideoCompositingLayout::canvasWidth.
.
    */
    int canvasWidth;
    /** Ignore this parameter. The height of the canvas is set by agora::rtc::IRtcEngine::configPublisher, and not by agora::rtc::VideoCompositingLayout::canvasHeight.
.
    */
    int canvasHeight;
    /** Enter any of the 6-digit symbols defined in RGB.
    */
    const char* backgroundColor;//e.g. "#C0C0C0" in RGB
    /** Region array. Each host in the channel can have a region to display the video on the screen.
    */
    const Region* regions;
    /** Number of users in the channel.
    */
    int regionCount;
    /** User-defined data.
    */
    const char* appData;
    /** Length of the user-defined data.
    */
    int appDataLength;
    VideoCompositingLayout()
        :canvasWidth(0)
        ,canvasHeight(0)
        ,backgroundColor(NULL)
        ,regions(NULL)
        , regionCount(0)
        , appData(NULL)
        , appDataLength(0)
    {}
};

/**
 * Video dimensions.
 */
struct VideoDimensions {
    /**
    The width of the video.
    */
    int width;
      /** The height of the video.
          */
    int height;
    VideoDimensions()
        : width(0), height(0)
    {}
    VideoDimensions(int w, int h)
        : width(w), height(h)
    {}
};

/** The standard bitrate in agora::rtc::IRtcEngine::setVideoEncoderConfiguration.

 (Recommended) In a live broadcast, Agora recommends setting a larger bitrate to improve the video quality. When you choose STANDARD_BITRATE, the bitrate value doubles in a live broadcast mode, and remains the same as in agora::rtc::VIDEO_PROFILE_TYPE
 in a communication mode.

 */
const int STANDARD_BITRATE = 0;

/**
 *  The compatible bitrate in agora::rtc::IRtcEngine::setVideoEncoderConfiguration.

 The bitrate in both the live broadcast and communication modes remain the same as in agora::rtc::VIDEO_PROFILE_TYPE
.
 */
const int COMPATIBLE_BITRATE = -1;

struct VideoEncoderConfiguration {
    VideoDimensions dimensions;
    FRAME_RATE frameRate;
    int bitrate;
    ORIENTATION_MODE orientationMode;
    VideoEncoderConfiguration(
        const VideoDimensions& d, FRAME_RATE f,
        int b, ORIENTATION_MODE m)
        : dimensions(d), frameRate(f), bitrate(b), orientationMode(m)
    {}
    VideoEncoderConfiguration(
        int width, int height, FRAME_RATE f,
        int b, ORIENTATION_MODE m)
        : dimensions(width, height), frameRate(f), bitrate(b), orientationMode(m)
    {}
    VideoEncoderConfiguration()
        : frameRate(FRAME_RATE_FPS_30)
        , bitrate(0)
        , orientationMode(ORIENTATION_MODE_ADAPTIVE)
    {}
};

typedef struct Rect {
    int top;
    int left;
    int bottom;
    int right;

    Rect(): top(0), left(0), bottom(0), right(0) {}
    Rect(int t, int l, int b, int r): top(t), left(l), bottom(b), right(r) {}
} Rect;

/** Definition of TranscodingUsers
*/
typedef struct TranscodingUser {
  /** User ID of the CDN live.
  */
    uid_t uid;

/** Horizontal position of the top left corner of the video frame.
*/
    int x;
    /** Vertical position of the top left corner of the video frame.
    */
    int y;
    /** Width of the video frame.
    */
    int width;
    /** Height of the video frame.
    */
    int height;

    /** Layer of the video frame. Between 1 and 100:

    - 1: Default, lowest
    - 100: Highest
    */
    int zOrder;
    /**  Transparency of the video frame.
    */
    double alpha;
    /** The audio channel of the sound. The default value is 0:

    - 0: (default) Supports dual channels at most, depending on the upstream of the broadcaster
    -  1: The audio stream of the broadcaster is in the FL audio channel. If the upstream of the broadcaster uses dual sound channel, only the left sound channel will be used for streaming
    - 2: The audio stream of the broadcaster is in the FC audio channel. If the upstream of the broadcaster uses dual sound channel, only the left sound channel will be used for streaming
    - 3: The audio stream of the broadcaster is in the FR audio channel. If the upstream of the broadcaster uses dual sound channel, only the left sound channel will be used for streaming
    - 4: The audio stream of the broadcaster is in the BL audio channel. If the upstream of the broadcaster uses dual sound channel, only the left sound channel will be used for streaming
    - 5: The audio stream of the broadcaster is in the BR audio channel. If the upstream of the broadcaster uses dual sound channel, only the left sound channel will be used for streaming

    */
    int audioChannel;
    TranscodingUser()
        : uid(0)
        , x(0)
        , y(0)
        , width(0)
        , height(0)
        , zOrder(0)
        , alpha(1.0)
        , audioChannel(0)
    {}

} TranscodingUser;

/** Definition of the watermark.
*/
typedef struct RtcImage {
    RtcImage() :
       url(NULL),
       x(0),
       y(0),
       width(0),
       height(0)
    {}
      /** URL address of the watermark on the live broadcast video.
      */
    const char* url;
    /** Position of the watermark on the upper left of the live broadcast video on the horizontal axis.
    */
    int x;
    /** Position of the watermark on the upper left of the live broadcast video on the vertical axis.
    */
    int y;
    /** Width of the watermark on the live broadcast video.
        */
    int width;
    /** Height of the watermark on the live broadcast video.
    */
    int height;
} RtcImage;

/** Definition of LiveTranscoding
*/
typedef struct LiveTranscoding {
  /** Width of the video.
  */
    int width;
    /** Height of the video.
    */
    int height;
    /** Bitrate of the output data stream set for CDN live. The default value is 400 kbit/s.
    */
    int videoBitrate;
    /** Frame rate of the output data stream set for CDN live. The default value is 15 fps.
    */
    int videoFramerate;

    /**

    - TRUE: Low latency with unassured quality.
    - FALSE: （Default）High latency with assured quality.

    */
    bool lowLatency;

    /** Interval between the I frames. The default value is 2 (s).
    */
    int videoGop;
    /** Self-defined video codec profiles: agora::rtc::VIDEO_CODEC_PROFILE_TYPE
    */
    VIDEO_CODEC_PROFILE_TYPE videoCodecProfile;
    /** Enter any of the 6-digit symbols defined in RGB.
    */
    unsigned int backgroundColor;   // RGB mode
    /** The number of users in the live broadcast.
    */
    unsigned int userCount;
    /** TranscodingUser
    */
    TranscodingUser *transcodingUsers;
    /** Extra user-defined information to be sent to the CDN client. The extra info will be transmitted by SEI packets
    */
    const char *transcodingExtraInfo;
    /** This metadata to be sent to CDN client defined by rtmp or FLV metadata. 
    */
    const char *metadata;
    /** The HTTP/HTTPS URL address of the watermark image added to the CDN publishing stream. The audience of the CDN publishing stream can see the watermark.
    */
    RtcImage* watermark;
    /** The HTTP/HTTPS URL address of the background image added to the CDN publishing stream. The audience of the CDN publishing stream can see the background image.
    */
    RtcImage* backgroundImage;
    /** Self-defined audio-sampling rates: agora::rtc::AUDIO_SAMPLE_RATE_TYPE
    */
    AUDIO_SAMPLE_RATE_TYPE audioSampleRate;
    /** Bitrate of the audio-output stream set for CDN live. The highest value is 128.
    */
    int audioBitrate;
    /** Agora's self-defined audio-channel types. Agora recommends choosing 1 or 2:

     - 1: Mono (default)
     - 2: Dual-sound channels
     - 3: Three-sound channels
     - 4: Four-sound channels
     -  5: Five-sound channels
    */
    int audioChannels;

    LiveTranscoding()
        : width(360)
        , height(640)
        , videoBitrate(400)
        , videoFramerate(15)
        , lowLatency(false)
        , backgroundColor(0x000000)
        , videoGop(30)
        , videoCodecProfile(VIDEO_CODEC_PROFILE_HIGH)
        , userCount(0)
        , transcodingUsers(NULL)
        , transcodingExtraInfo(NULL)
        , watermark(NULL)
        , audioSampleRate(AUDIO_SAMPLE_RATE_48000)
        , audioBitrate(48)
        , audioChannels(1)
    {}
} LiveTranscoding;

/** Definition of InjectStreamConfig
*/
struct InjectStreamConfig {
  /** Width of the stream to be added into the broadcast. The default value is 0; same width as the original stream.
  */
    int width;
    /** Height of the stream to be added into the broadcast. The default value is 0; same height as the original stream.
    */
    int height;
    /** Video GOP of the stream to be added into the broadcast. The default value is 30.
    */
    int videoGop;
    /**  Video frame rate of the stream to be added into the broadcast. The default value is 15 fps.
    */
    int videoFramerate;
    /** Video bitrate of the stream to be added into the broadcast. The default value is 400 kbit/s.
    */
    int videoBitrate;
    /** Audio-sampling rate of the stream to be added into the broadcast: agora::rtc::AUDIO_SAMPLE_RATE_TYPE. The default value is 48000.
    */
    AUDIO_SAMPLE_RATE_TYPE audioSampleRate;
    /** Audio bitrate of the stream to be added into the broadcast. The default value is 48.
    */
    int audioBitrate;
    /** Audio channels to be added into the broadcast. The default value is 1.
    */
    int audioChannels;

    // width / height default set to 0 means pull the stream with its original resolution
    InjectStreamConfig()
        : width(0)
        , height(0)
        , videoGop(30)
        , videoFramerate(15)
        , videoBitrate(400)
        , audioSampleRate(AUDIO_SAMPLE_RATE_48000)
        , audioBitrate(48)
        , audioChannels(1)
    {}
};

/** Video stream lifecycle of CDN Live.
*/
enum RTMP_STREAM_LIFE_CYCLE_TYPE
{
  /** Bound to the channel lifecycle.
  */
	RTMP_STREAM_LIFE_CYCLE_BIND2CHANNEL = 1,
  /** Bound to the owner identity of the RTMP stream.
  */
	RTMP_STREAM_LIFE_CYCLE_BIND2OWNER = 2,
};

/** Definition of PublisherConfiguration.
*/
struct PublisherConfiguration {
  /** Width of the output data stream set for CDN Live. The default value is 360.
  */
	int width;
  /** Height of the output data stream set for CDN Live. The default value is 640.
  */
	int height;
  /** Frame rate of the output data stream set for CDN Live. The default value is 15 fps.
  */
	int framerate;
  /** Bitrate of the output data stream set for CDN Live. The default value is 500 kbit/s.
  */
	int bitrate;
  /** Default layout:

 - 0: Tile horizontally
 - 1: Layered windows
 - 2: Tile vertically

  */
	int defaultLayout;
  /** Video stream lifecycle of CDN Live: agora::rtc::RTMP_STREAM_LIFE_CYCLE_TYPE
  */
	int lifecycle;
  /** Whether the current user is the owner of the RTMP stream:

- True: Yes (default). The push-stream configuration takes effect.
- False: No. The push-stream configuration will not work.
  */
	bool owner;
  /** Width of the stream to be injected. Set it as 0.
  */
	int injectStreamWidth;
  /** Height of the stream to be injected. Set it as 0.
  */
	int injectStreamHeight;
  /** URL address of the stream to be injected to the channel.
  */
	const char* injectStreamUrl;
  /** Push-stream URL address for the picture-in-picture layouts. The default value is NULL.
  */
	const char* publishUrl;
  /** Push-stream URL address of the original stream which does not require picture-blending. The default value is NULL.
  */
	const char* rawStreamUrl;
  /** Reserved field. The default value is NULL.
  */
	const char* extraInfo;


	PublisherConfiguration()
		: width(640)
		, height(360)
		, framerate(15)
		, bitrate(500)
		, defaultLayout(1)
		, lifecycle(RTMP_STREAM_LIFE_CYCLE_BIND2CHANNEL)
		, owner(true)
		, injectStreamWidth(0)
		, injectStreamHeight(0)
		, injectStreamUrl(NULL)
		, publishUrl(NULL)
		, rawStreamUrl(NULL)
		, extraInfo(NULL)
	{}

};

#if !defined(__ANDROID__)
/** Video display settings of the VideoCanvas class.
*/
struct VideoCanvas
{
  /** Video display window (view).
  */
    view_t view;
    /** Video display mode:  agora::rtc::RENDER_MODE_TYPE.
    */
    int renderMode;
    uid_t uid;
    void *priv; // private data (underlying video engine denotes it)

    VideoCanvas()
        : view(NULL)
        , renderMode(RENDER_MODE_HIDDEN)
        , uid(0)
        , priv(NULL)
    {}
    VideoCanvas(view_t v, int m, uid_t u)
        : view(v)
        , renderMode(m)
        , uid(u)
        , priv(NULL)
    {}
};
#else
struct VideoCanvas;
#endif

    /** Definition of IPacketObserver.
     */
class IPacketObserver
{
public:
/** Definition of Packet.
 */
	struct Packet
	{
		const unsigned char* buffer;
		unsigned int size;
	};
	/** The audio packet is about to be sent to the other users.
	* @param packet  buffer *buffer points the data to be sent and the size of the buffer data to be sent
	* @return True to send out the packet. False to discard the packet.
	*/
	virtual bool onSendAudioPacket(Packet& packet) = 0;
	/** The video packet is about to be sent to the other users.
	* @param packet buffer *buffer points the data to be sent and the size of the buffer data to be sent.
	* @return True to send out the packet. False to discard the packet.
	*/
	virtual bool onSendVideoPacket(Packet& packet) = 0;
	/** The audio packet is received by the other users.
	* @param packet buffer *buffer points to the data to be sent and the size of the buffer data to be sent.
	* @return True to process the packet. False to discard the packet.
	*/
	virtual bool onReceiveAudioPacket(Packet& packet) = 0;
	/** The video packet is received by the other users.
	* @param packet buffer *buffer points the data to be sent and the size of the buffer data to be sent.
	* @return True to process the packet. False to discard the packet.
	*/
	virtual bool onReceiveVideoPacket(Packet& packet) = 0;
};


/**
The SDK uses the IRtcEngineEventHandler interface class to send callback event notifications to the application, and the application inherits the methods of this interface class to retrieve these event notifications.

All methods in this interface class have their (empty) default implementations, and the application can inherit only some of the required events instead of all of them. In the callback methods, the application should avoid time-consuming tasks or calling blocking APIs, for example, SendMessage, otherwise the SDK may not work properly.
*/
class IRtcEngineEventHandler
{
public:
    virtual ~IRtcEngineEventHandler() {}

    /** The user has successfully joined the specified
channel with an assigned channel ID and user ID.

The channel ID is assigned based on
the channel name specified in the IRtcEngine::joinChannel() API. If the user ID is not specified when joinChannel()
is called, the server assigns one automatically.

    @param channel  Channel name.
    @param  uid User ID. If the uid is specified in the joinChannel()  method, it returns the specified ID; if not, it returns an ID that is automatically assigned by the Agora server.
    @param  elapsed Time elapsed (ms) from calling joinChannel() until this event occurs.
    */
    virtual void onJoinChannelSuccess(const char* channel, uid_t uid, int elapsed) {
        (void)channel;
        (void)uid;
        (void)elapsed;
    }

    /** When the client loses connection with the server because of network problems, the SDK automatically attempts to reconnect, and triggers this callback method upon reconnection.

    @param channel Channel name.
   @param uid User ID.
    @param elapsed Time elapsed (ms) from calling IRtcEngine::joinChannel() until this event occurs.
    */
    virtual void onRejoinChannelSuccess(const char* channel, uid_t uid, int elapsed) {
        (void)channel;
        (void)uid;
        (void)elapsed;
    }

    /** A warning occurred during SDK runtime.

    In most cases, the application can ignore the warning reported by the SDK, because the SDK can usually fix the issue and resume running.

    @param warn Warning code.
    @param msg Warning message: agora::WARN_CODE_TYPE
    */
    virtual void onWarning(int warn, const char* msg) {
        (void)warn;
        (void)msg;
    }

    /** A network or media error occurred during SDK runtime.

    In most cases, reporting an error means that the SDK cannot fix the issue and resume running, and therefore requires actions from the application or simply informs the user on the issue. For instance, the SDK reports an ERR_START_CALL error when failing to initialize a call. In this case, the application informs the user that the call initialization failed and calls the IRtcEngine::leaveChannel() method to exit the channel.

    @param err Error code.
    @param msg Error message: agora::ERROR_CODE_TYPE
    */
    virtual void onError(int err, const char* msg) {
        (void)err;
        (void)msg;
    }

    /** Reports on the audio quality of the current call once every two seconds.

    @param uid User ID of the speaker.
    @param quality Quality of the user: agora::rtc::QUALITY_TYPE
    @param delay Time delay (ms).
    @param lost Audio packet loss rate (%).
    */
    virtual void onAudioQuality(uid_t uid, int quality, unsigned short delay, unsigned short lost) {
        (void)uid;
        (void)quality;
        (void)delay;
        (void)lost;
    }

    /** Indicates who is talking and the speaker’s volume.

By default the indication is disabled. If needed, use the RtcEngineParameters::enableAudioVolumeIndication method to configure it.

    @param speakers The speakers (array). Each speaker(): AudioVolumeInfo
    @param speakerNumber Total number of speakers.
    @param totalVolume Total volume after audio mixing between 0 (lowest volume) to 255 (highest volume).
    */
    virtual void onAudioVolumeIndication(const AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume) {
        (void)speakers;
        (void)speakerNumber;
        (void)totalVolume;
    }

    /** When the application calls the IRtcEngine::leaveChannel() method, the SDK uses this callback to notify
the application that the user has successfully left the channel.

With this callback function, the application retrieves information such as the call duration and
the statistics of data received or transmitted by the SDK.
    @param stats Statistics about the call: RtcStats
    */
    virtual void onLeaveChannel(const RtcStats& stats) {
        (void)stats;
    }

    /** The statistics of the current call session once every two seconds.

    @param stats RTC engine stats: RtcStats
    */
    virtual void onRtcStats(const RtcStats& stats) {
        (void)stats;
    }

    /** The audio device state has changed.

This callback notifies the application that the system’s audio device state has changed, for example, a headset is unplugged from the device.

    @param deviceId Device ID.
   @param deviceType Device type: agora::rtc::MEDIA_DEVICE_TYPE
   @param deviceState Device state: agora::rtc::MEDIA_DEVICE_STATE_TYPE
    */
    virtual void onAudioDeviceStateChanged(const char* deviceId, int deviceType, int deviceState) {
        (void)deviceId;
        (void)deviceType;
        (void)deviceState;
    }

    /** The audio mixing file playback has finished.

    This callback is triggered when the audio mixing file playback is finished after calling RtcEngineParameters::startAudioMixing().
If you failed to execute the startAudioMixing() method, it returns the error code in the IRtcEngineEventHandler::onError callback.

     */
    virtual void onAudioMixingFinished() {
    }

    /**
     * Far-end rhythm begins.
     */
    virtual void onRemoteAudioMixingBegin() {
    }
    /**
     * Far-end rhythm ends.
     */
    virtual void onRemoteAudioMixingEnd() {
    }

    /**
    * The local audio effect playback has finished.

    @param soundId ID of the audio effect. Each audio effect has a unique ID.
    */
    virtual void onAudioEffectFinished(int soundId) {
    }

    /** The video device state has changed.

    This callback notifies the application that the system's video device state has changed. On a Windows device that uses an external camera for video capturing, the video disables once the external camera is unplugged.

    @param deviceId Device ID
    @param deviceType Device type: agora::rtc::MEDIA_DEVICE_TYPE
    @param deviceState Device state: agora::rtc::MEDIA_DEVICE_STATE_TYPE
    */
    virtual void onVideoDeviceStateChanged(const char* deviceId, int deviceType, int deviceState) {
        (void)deviceId;
        (void)deviceType;
        (void)deviceState;
    }

    /** The network quality of all the users in a communication or live broadcast channel once every two seconds.

	@param uid User ID. The network quality of the user with this UID will be reported. If uid is 0, it reports the local network quality.
	@param txQuality Transmission quality of the user: agora::rtc::QUALITY_TYPE.
	@param rxQuality Receiving quality of the user: agora::rtc::QUALITY_TYPE.
	*/
    virtual void onNetworkQuality(uid_t uid, int txQuality, int rxQuality) {
		(void)uid;
		(void)txQuality;
		(void)rxQuality;
    }

    /** The last mile network quality of the local user.

    This callback is triggered once every two seconds after IRtcEngine::enableLastmileTest() is called.

When not in a call and the network test is enabled
(by calling enableLastmileTest()), this callback function is triggered
irregularly to update the application on the network connection quality of the local user.
    @param quality Network quality: agora::rtc::QUALITY_TYPE.
    */
    virtual void onLastmileQuality(int quality) {
        (void)quality;
    }

    /** The first local video frame is displayed on the video window.
    @param width Width (pixels) of the video stream.
    @param height Height (pixels) of the video stream.
    @param elapsed Time elapsed (ms) from calling IRtcEngine::joinChannel() until this callback is triggered.
    */
    virtual void onFirstLocalVideoFrame(int width, int height, int elapsed) {
        (void)width;
        (void)height;
        (void)elapsed;
    }

    /** The first remote video frame has been received and decoded.

    This callback is triggered upon receiving and successfully decoding the first frame of the remote video. The application can configure the user view settings in this callback.

    @param uid User ID of the user whose video streams are received.
    @param width Width (pixels) of the video stream.
    @param height Height (pixels) of the video stream.
    @param elapsed Time elapsed (ms) from calling IRtcEngine::joinChannel() until this callback is triggered.
    */
    virtual void onFirstRemoteVideoDecoded(uid_t uid, int width, int height, int elapsed) {
        (void)uid;
        (void)width;
        (void)height;
        (void)elapsed;
    }

    /** The video size or rotation has changed.

     @param uid User ID of the remote user or local user (0).
      @param width Nnew width of the video.
     @param height New height of the video.
     @param rotation Rotation of the video.
     */
    virtual void onVideoSizeChanged(uid_t uid, int width, int height, int rotation) {
        (void)uid;
        (void)width;
        (void)height;
        (void)rotation;
    }
/** The remote video state has changed.

@param uid ID of the user whose video state has changed.
@param state Remote video state: agora::rtc::REMOTE_VIDEO_STATE.
*/
    virtual void onRemoteVideoStateChanged(uid_t uid, REMOTE_VIDEO_STATE state) {
        (void)uid;
        (void)state;
    }

    /** The first remote video frame has been received and displayed.

    This callback is triggered upon the display of the first frame of the remote video on the user’s video window. The application can retrieve the time elapsed from a user joining the channel until the first video frame is displayed.

    @param uid User ID of the remote user whose video streams are received.
    @param width Width (pixels) of the video frame.
    @param height Height (pixels) of the video stream.
   @param elapsed Time elapsed (ms) from calling IRtcEngine::joinChannel() until this callback is triggered.
    */
    virtual void onFirstRemoteVideoFrame(uid_t uid, int width, int height, int elapsed) {
        (void)uid;
        (void)width;
        (void)height;
        (void)elapsed;
    }

    /** A remote user has joined the channel.

If there are other users in the channel when that user joins, the SDK also reports to
the application on the existing users who are already in the channel.

Note: In a live broadcast, only the hosts will receive this callback, not the audience.
    @param uid Remote user ID.
    @param elapsed Time delay (ms) from calling IRtcEngine::joinChannel() until this callback is triggered.
    */
    virtual void onUserJoined(uid_t uid, int elapsed) {
        (void)uid;
        (void)elapsed;
    }

    /** A remote user has left the channel or gone offline.

    The SDK reads the timeout data to determine if a user has left the channel (or has gone offline). If no data package is received from the user in 15 seconds, the SDK assumes the user is offline. A poor network connection may lead to false detections; therefore, use signaling for reliable offline detection.

   @param uid Remote user ID.
    @param reason Reason the remote user has gone offline: agora::rtc::USER_OFFLINE_REASON_TYPE.
    */
    virtual void onUserOffline(uid_t uid, USER_OFFLINE_REASON_TYPE reason) {
        (void)uid;
        (void)reason;
    }

    /** A remote user's audio stream has muted or unmuted.

    Note: This callback returns invalid when the number of users in a channel exceeds 20.

    @param uid Remote user ID.
    @param muted

- True: A remote user's audio has muted.
- False: A remote user's audio has unmuted.
*/
    virtual void onUserMuteAudio(uid_t uid, bool muted) {
        (void)uid;
        (void)muted;
    }

    /** A remote user's video stream has paused or resumed.

    Note: This callback returns invalid when the number of users in a channel exceeds 20.

    @param uid  Remote user ID.
    @param muted

    - True: A remote user's video has paused.
    - False: A remote user's video has resumed.  */
    virtual void onUserMuteVideo(uid_t uid, bool muted) {
        (void)uid;
        (void)muted;
    }

	/** A remote user has enabled or disabled the video function.

  Once the video function is disabled, the users cannot see any video.

  Note: This callback returns invalid when the number of users in a channel exceeds 20.


	@param uid Remote user ID.
	@param enabled

  - True: A remote user has enabled the video function.
  - False: A remote user has disabled the video function.
	*/
	virtual void onUserEnableVideo(uid_t uid, bool enabled) {
		(void)uid;
		(void)enabled;
	}

	/** A remote user has enabled or disabled the local video function.
    @param uid Remote user ID.
    @param enabled

   - True: A remote user has enabled the local video function.
   - False: A remote user has disabled the local video function.
    */
    virtual void onUserEnableLocalVideo(uid_t uid, bool enabled) {
        (void)uid;
        (void)enabled;
    }

    /** The API has been executed.

    @param api The API that the SDK executes
    @param err The error code that the SDK returns when the method call fails. If the SDK returns 0, then the method has been called successfully.
    @param result The result of calling the API.
    */
    virtual void onApiCallExecuted(int err, const char* api, const char* result) {
        (void)err;
        (void)api;
        (void)result;
    }

    /** The statistics of the uploading local video streams once every two seconds.

	@param stats Statistics of the uploading local video streams: LocalVideoStats.
    */
	virtual void onLocalVideoStats(const LocalVideoStats& stats) {
		(void)stats;
    }

    /** The statistics of the receiving remote video streams once every two seconds.

    @param stats Statistics of the receiving remote video streams: LocalVideoStats.
	*/
	virtual void onRemoteVideoStats(const RemoteVideoStats& stats) {
		(void)stats;
    }

    /** The camera is turned on and ready to capture the video.

    If the camera fails to turn on, handle the error in the IRtcEngineEventHandler::onError method.

    */
    virtual void onCameraReady() {}

/** The camera focus area has changed.

@param x x coordinate of the changed camera focus area.
@param y y coordinate of the changed camera focus area.
@param width Width of the changed camera focus area.
@param height Height of the changed camera focus area.
*/
    virtual void onCameraFocusAreaChanged(int x, int y, int width, int height) {
        (void)x;
        (void)y;
        (void)width;
        (void)height;
    }

    /** The video has stopped.

    The application can use this callback to change the configuration of the view (for example, displaying other pictures in the view) after the video stops.

    */
    virtual void onVideoStopped() {}

    /** The connection between the SDK and the server is lost.

    The onConnectionInterrupted() callback is triggered and the SDK reconnects automatically.
If the reconnection fails within a certain period (10 seconds by default),
the onConnectionLost() callback is triggered. The SDK continues to reconnect until the
application calls IRtcEngine::leaveChannel().
    */
    virtual void onConnectionLost() {}

    /** The connection is interrupted between the SDK and the server.

    Once the connection is lost, the SDK continues to reconnect until the
    application calls IRtcEngine::leaveChannel().
    */
    virtual void onConnectionInterrupted() {}

    /** Your connection is banned by the Agora Server.
     */
    virtual void onConnectionBanned() {}

    virtual void onRefreshRecordingServiceStatus(int status) {
        (void)status;
    }

//    virtual void onStreamError(int streamId, int code, int parameter, const char* message, size_t length) {}
    /** The local user has received the data stream from the peer user within five seconds.

    @param uid Peer user ID who sends the message.
    @param streamId Stream ID.
    @param data Data received by the recipients.
    @param length Length of the data in bytes.
    */
    virtual void onStreamMessage(uid_t uid, int streamId, const char* data, size_t length) {
        (void)uid;
        (void)streamId;
        (void)data;
        (void)length;
    }

	/** The local user has not received the data stream from the other user within five seconds.

  @param uid Peer user ID who sends the message.
  @param streamId Stream ID.
  @param code Error code: agora::ERROR_CODE_TYPE.
  @param missed Number of lost messages.
  @param cached Number of incoming cached messages when the data stream is interrupted.
	*
	*/
	virtual void onStreamMessageError(uid_t uid, int streamId, int code, int missed, int cached) {
        (void)uid;
        (void)streamId;
        (void)code;
        (void)missed;
        (void)cached;
    }

    virtual void onMediaEngineLoadSuccess() {
    }
    virtual void onMediaEngineStartCallSuccess() {
    }
    /** The token has expired.

    When a Token is specified by calling IRtcEngine::joinChannel(), if the SDK losses connection with the Agora server due to network issues, the Token may expire after a certain period of time and a new Token may be required to reconnect to the server.

  This callback notifies the application the need to generate a new Token, and calls IRtcEngine::renewToken() to renew the Token.
  This function was previously provided when the callback reported onError(): ERR_TOKEN_EXPIRED(-109)、ERR_INVALID_TOKEN(-110). Starting from v1.7.3,
  the old method still works, but it is recommended to use this callback.
    */
    virtual void onRequestToken() {
    }
/** The Token will expire within 30 seconds.

If the Token you specified when calling IRtcEngine::joinChannel() expires, you will become offline. This callback is triggered 30 seconds before the Token expires to remind the app to renew the Token.
Upon receiving this callback, the user needs to generate a new Token on your server and call IRtcEngine::renewToken to pass the new Token on to the SDK.

@param token The Token that will expire in 30 seconds.

*/
    virtual void onTokenPrivilegeWillExpire(const char* token) {
        (void)token;
    }

    /** The first local audio frame has been generated.

    @param elapsed Time elapsed (ms) from the remote user calling IRtcEngine::joinChannel().
    */
    virtual void onFirstLocalAudioFrame(int elapsed) {
        (void)elapsed;
    }

    /** The first remote audio frame has been received.
    @param uid Remote user ID.
    @param elapsed Time elapsed (ms) from the remote user calling IRtcEngine::joinChannel().
    */
    virtual void onFirstRemoteAudioFrame(uid_t uid, int elapsed) {
        (void)uid;
        (void)elapsed;
    }
    /* An active speaker has been detected.

    If you have used the RtcEngineParameters::enableAudioVolumeIndication API, this callback is triggered then the volume detecting unit has detected active speaker in the channel. Also returns with the uid of the active speaker.

    Note:

    - You need to call enableAudioVolumeIndication to receive this callback.
    - The active speaker means the uid of the speaker who speaks at the highest volume during a certain period of time.

    @param uid User ID of the active speaker. By default, 0 means the local user. If needed, you can also add relative functions on your application, for example, the active speaker, once detected, will have his/her head portrait zoomed in.
    */
    virtual void onActiveSpeaker(uid_t uid) {
        (void)uid;
    }

    /** The user role in a live broadcast has switched, for example, from a host to an audience or vice versa.
@param oldRole Role that you switched from: agora::rtc::CLIENT_ROLE_TYPE
@param newRole Role that you switched to: agora::rtc::CLIENT_ROLE_TYPE
    */
    virtual void onClientRoleChanged(CLIENT_ROLE_TYPE oldRole, CLIENT_ROLE_TYPE newRole) {
    }
/** The volume of the playback, microphone, or application has changed.
 
 @param deviceType agora::rtc::MEDIA_DEVICE_TYPE
 @param volume Volume, ranging from 0 to 255
 @param muted True/False
 */
    virtual void onAudioDeviceVolumeChanged(MEDIA_DEVICE_TYPE deviceType, int volume, bool muted) {
        (void)deviceType;
        (void)volume;
        (void)muted;
    }
/** A stream was published.
*/
    virtual void onStreamPublished(const char *url, int error) {
        (void)url;
        (void)error;
    }
/** A stream was unpublished.
*/
    virtual void onStreamUnpublished(const char *url) {
        (void)url;
    }
/** The publisher transcoding was updated.
*/
    virtual void onTranscodingUpdated() {
    }
/** The status of the external injected video stream.

@param URL URL address of the external injected video stream.
@param uid User ID.
@param status Status of the added stream: agora::rtc::INJECT_STREAM_STATUS.
*/
    virtual void onStreamInjectedStatus(const char* url, uid_t uid, int status) {
        (void)url;
        (void)uid;
        (void)status;
    }

/** The local published media stream fell back to an audio-only stream in poor network conditions or switched back to the video when the network conditions improved.

 If you call RtcEngineParameters::setLocalPublishFallbackOption and set *option* as agora::rtc::STREAM_FALLBACK_OPTION_AUDIO_ONLY, this callback will be triggered when the local publish stream falls back to audio-only mode due to poor uplink conditions, or when the audio stream switches back to the video when the uplink network condition improves.

 @param isFallbackOrRecover

 - True: The local publish stream fell back to audio-only due to poor network conditions.
 - False: The local publish stream switched back to the video when the network conditions improved.

 */
    virtual void onLocalPublishFallbackToAudioOnly(bool isFallbackOrRecover) {
        (void)isFallbackOrRecover;
    }

    /** The remote published media stream fell back to an audio-only stream in poor network conditions or switched back to the video when the network conditions improved.

     Once you enabled RtcEngineParameters::setRemoteSubscribeFallbackOption,
     this event will be triggered to receive audio only due to poor network conditions or resubscribes the video when the network condition improves.

      Note: Once the remote subscribe stream is switched to the low stream due to poor network conditions, you can monitor the stream switch between a high and low stream in the agora::rtc::RemoteVideoStats callback.

       @param uid    Remote user ID
     @param  isFallbackOrRecover

     - True: The remote subscribe stream fell back to audio-only due to poor network conditions.
     - False: The remote subscribe stream switched back to the video stream when the network conditions improved.
     */
    virtual void onRemoteSubscribeFallbackToAudioOnly(uid_t uid, bool isFallbackOrRecover) {
        (void)uid;
        (void)isFallbackOrRecover;
    }

    /** Statistics of the remote audio transport.

This callback is triggered every two seconds once the user has received the audio data packet sent from a remote user.

     *
     @param uid  User ID of the remote user whose audio data packet has been received.
     @param delay Time delay (ms) from the remote user to the local client.
     @param lost Packet loss rate (%).
     @param rxKBitRate  Received audio bitrate (kbit/s) of the packet from the remote user.
     */
    virtual void onRemoteAudioTransportStats(
        uid_t uid, unsigned short delay, unsigned short lost,
        unsigned short rxKBitRate) {
        (void)uid;
        (void)delay;
        (void)lost;
        (void)rxKBitRate;
    }

    /** Statistics of the remote video transport.

    This callback is triggered every two seconds once the user has received the video data packet sent from a remote user.

     *
     @param uid User ID of the remote user whose video packet has been received.
     @param delay Time delay (ms) from the remote user to the local client.
     @param lost Packet loss rate (%).
     @param rxKBitRate Received video bitrate (kbit/s) of the packet from the remote user.
     */
    virtual void onRemoteVideoTransportStats(
        uid_t uid, unsigned short delay, unsigned short lost,
        unsigned short rxKBitRate) {
        (void)uid;
        (void)delay;
        (void)lost;
        (void)rxKBitRate;
    }
};

/**
* Video device collection methods.

The IVideoDeviceCollection interface class retrieves the video device related numbers or data.

*/
class IVideoDeviceCollection
{
public:
    /** Gets the total number of the indexed video-capture devices in the system.

    @return Total number of the indexed video-capture devices.
    */
    virtual int getCount() = 0;

    /** Gets a specified piece of information about an indexed video-capture device.

    @param index An input parameter that is a specified index and must be smaller than the return value of agora::rtc::IVideoDeviceCollection::getCount.
    @param deviceName An output parameter that indicates the device name.
   @param  deviceId An output parameter that indicates the device ID.
    @return

    - 0: Success.
    - <0: Failure.
    */
    virtual int getDevice(int index, char deviceName[MAX_DEVICE_ID_LENGTH], char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;

    /** Specifies a device with the device ID.

    @param deviceId Device ID.
    @return

    - 0: Success.
    - <0: Failure.
    */
    virtual int setDevice(const char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;

    /** Releases the resource.
    */
    virtual void release() = 0;
};

/** Video device management methods.

The IVideoDeviceManager interface class tests the interfaces of the video devices. Instantiate an AVideoDeviceManager class to get an IVideoDeviceManager interface.

*/
class IVideoDeviceManager
{
public:

    /** Enumerates the video capture devices.

    This method returns an IVideoDeviceCollection object that includes all the video-capture devices in the system. With the IVideoDeviceCollection object, the application can enumerate the video-capture devices. The application must call the IVideoDeviceCollection::release() method to release the returned object after using it.

    * @return Returns an IVideoDeviceCollection object that includes all the video-capture devices in the system when the method call succeeds. Returns NULL when the method call fails.
    */
    virtual IVideoDeviceCollection* enumerateVideoDevices() = 0;

    /** Specifies a device with the device ID.
    @param deviceId Device ID of the video-capture device. You can call enumerateVideoDevices() to retrieve it. Plugging or unplugging the device does not change the device ID.
    @return

- 0: Success.
- <0: Failure.
    */
    virtual int setDevice(const char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;

    /** Gets the video-capture device that is in use.
    @param deviceId Output parameter. Device ID of the video-capture device.
    @return

    - 0: Success.
    - <0: Failure.
    */
    virtual int getDevice(char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;

    /** Starts the video capture device test.

    This method tests whether the video-capture device works properly.
Before calling this method, ensure that you have already called agora::rtc::IRtcEngine::enableVideo, and the HWND window handle of the incoming parameter is valid.

    @param hwnd Output parameter. The window handle is used to display the screen.
    @return

    - 0: Success.
    - <0: Failure.
    */
    virtual int startDeviceTest(view_t hwnd) = 0;

    /** Stops the video-capture device test.
    @return

- 0: Success.
- <0: Failure.
    */
    virtual int stopDeviceTest() = 0;

    /** Releases the resource.
    */
    virtual void release() = 0;
};

/** Audio device collection methods.

The IAudioDeviceCollection interface class retrieves device-related information.
*/
class IAudioDeviceCollection
{
public:
    /** Gets the total number of playback or recording devices.

Call agora::rtc::IAudioDeviceManager::enumeratePlaybackDevices() first, and then call this method to return the number of the audio playback devices.

@return Number of the audio devices.
    */
    virtual int getCount() = 0;

    /** Gets a specified piece of information about an audio device.
    @param index An input parameter to specify the device information to be enquired.
    @param deviceName An output parameter that indicates the device name.
    @param deviceId An output parameter that indicates the device ID.
    @return

- 0: Success.
- <0: Failure.
    */
    virtual int getDevice(int index, char deviceName[MAX_DEVICE_ID_LENGTH], char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;

    /** Specifies a device with the device ID.
    @param deviceId Device ID.
    @return

- 0: Success.
- <0: Failure.
    */
    virtual int setDevice(const char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;
/** Sets the volume of the application.

@param volume Volume, ranging from 0 to 255.

@return

- 0: Success.
- <0: Failure.
*/
    virtual int setApplicationVolume(int volume) = 0;
    /** Gets the volume of the application.

@param volume Volume, ranging from 0 to 255.

@return

- 0: Success.
- <0: Failure.
    */
    virtual int getApplicationVolume(int& volume) = 0;
    /** Mutes the application.

@param mute

- True: Mutes the application.
- False: Unmutes the application.

@return

- 0: Success.
- <0: Failure.
    */
    virtual int setApplicationMute(bool mute) = 0;
    /** Gets the mute state of the application.

@param mute

- True: The application is mute.
- False: The application is not mute.

@return

- 0: Success.
- <0: Failure.
    */
    virtual int isApplicationMute(bool& mute) = 0;
    /**
    * Releases the resource.
    */
    virtual void release() = 0;
};
/** Audio device management methods.

The IAudioDeviceManager interface class tests the interfaces of the audio devices. Instantiate an AAudioDeviceManager class to get an IAudioDeviceManager interface.

*/
class IAudioDeviceManager
{
public:
    /** Enumerates the audio playback devices.

    This method returns an IAudioDeviceCollection object that includes all the audio playback devices in the system. With the IAudioDeviceCollection object, the application can enumerate the audio playback devices. The application must call the IAudioDeviceCollection::release() method to release the returned object after using it.

    * @return Returns an IAudioDeviceCollection object that includes all the audio playback devices in the system when the method call succeeds. Returns NULL when the method call fails.
    */
    virtual IAudioDeviceCollection* enumeratePlaybackDevices() = 0;

    /** Enumerates the audio recording devices.

    This method returns an IAudioDeviceCollection object that includes all the audio recording devices in the system. With the IAudioDeviceCollection object, the application can enumerate the audio recording devices. The application needs to call the IAudioDeviceCollection::release() method to release the returned object after using it.

    * @return Returns an IAudioDeviceCollection object that includes all the audio recording devices in the system when the call succeeds. Returns NULL when the call fails.
    */
    virtual IAudioDeviceCollection* enumerateRecordingDevices() = 0;

    /** Specifies a audio playback device with the device ID.

    @param deviceId Device ID of the audio playback device. It can be retrieved by the enumeratePlaybackDevices() method. Plugging or unplugging the audio device does not change the device ID.
    @return

- 0: Success.
- <0: Failure.
    */
    virtual int setPlaybackDevice(const char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;

    /** Gets the audio playback device by the device ID.
    @param deviceId Device ID of the audio playback device.
    @return

- 0: Success.
- <0: Failure.
    */
    virtual int getPlaybackDevice(char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;

    /** Gets the audio playback device by the device ID and name.
        @param deviceId Device ID of the audio playback device.
       @param deviceName Device name of the audio playback device.
       @return

   - 0: Success.
   - <0: Failure.
         */
    virtual int getPlaybackDeviceInfo(char deviceId[MAX_DEVICE_ID_LENGTH], char deviceName[MAX_DEVICE_ID_LENGTH]) = 0;

    /** Sets the volume of the audio playback device.
    @param volume Volume of the audio playing device, ranging from 0 to 255
    @return

- 0: Success.
- <0: Failure.
    */
    virtual int setPlaybackDeviceVolume(int volume) = 0;

    /** Gets the volume of the audio playback device.
    @param volume Volume of the audio playback device, ranging from 0 to 255.
    @return

- 0: Success.
- <0: Failure.
    */
    virtual int getPlaybackDeviceVolume(int *volume) = 0;

    /** Specifies an audio recording device with the device ID.

@param deviceId Device ID of the audio recording device. It can be retrieved by the enumerateRecordingDevices() method. Plugging or unplugging the audio device does not change the device ID.
@return

- 0: Success.
- <0: Failure.
    */
    virtual int setRecordingDevice(const char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;

    /** Gets the audio recording device by the device ID.
    @param deviceId Device ID of the audio recording device.
    @return

- 0: Success.
- <0: Failure.
    */
    virtual int getRecordingDevice(char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;

    /** Gets the audio recording device by the device ID and name.

@param deviceId Device ID of the recording audio device.
@param deviceName Device name of the recording audio device.
@return

- 0: Success.
- <0: Failure.
         */
   virtual int getRecordingDeviceInfo(char deviceId[MAX_DEVICE_ID_LENGTH], char deviceName[MAX_DEVICE_ID_LENGTH]) = 0;


    /** Sets the volume of the microphone.
    @param volume Volume of the microphone, ranging from 0 to 255.
    @return

- 0: Success.
- <0: Failure.
    */
    virtual int setRecordingDeviceVolume(int volume) = 0;

    /** Gets the volume of the microphone.
    @param volume Volume of the microphone, ranging from 0 to 255.
    @return

- 0: Success.
- <0: Failure.
    */
    virtual int getRecordingDeviceVolume(int *volume) = 0;

/** Mutes the audio playback device.

@param mute

- True: Mutes the device.
- False: Unmutes the device.

@return

- 0: Success.
- <0: Failure.
*/
    virtual int setPlaybackDeviceMute(bool mute) = 0;
    /** Gets the playback device mute status.

    @param mute

    - True: The playback device is muted.
    - False: The playback device is unmuted.

    @return

    - 0: Success.
    - <0: Failure.
    */
    virtual int getPlaybackDeviceMute(bool *mute) = 0;
    /** Mutes the microphone.

    @param mute


  - True: Mutes the microphone.
  - False: Unmutes the microphone.

    @return

    - 0: Success.
    - <0: Failure.
    */
    virtual int setRecordingDeviceMute(bool mute) = 0;
    /** Gets the microphone mute status.

    @param mute

    - True: The microphone is muted.
    - False: The microphone is unmuted.

    @return

    - 0: Success.
    - <0: Failure.
    */
    virtual int getRecordingDeviceMute(bool *mute) = 0;

    /** Starts the audio playback device test.

This method tests if the playback device works properly. In the test, the SDK plays an audio file specified by the user. If the user can hear the audio, the playback device works properly.

@param testAudioFilePath File path of the audio file for the test, which is in utf8 absolute path:

- Supported file format: wav, mp3, m4a, and aac
- Supported file sampling rate: 8000, 16000, 32000, 44100, and 48000

@return Returns 0 if success and you can hear the sound of the .wav file, or returns an error code.
    */
    virtual int startPlaybackDeviceTest(const char* testAudioFilePath) = 0;

    /** Stops the audio playback device test.

@return

- 0: Success.
- <0: Failure.
    */
    virtual int stopPlaybackDeviceTest() = 0;

    /** Starts the microphone test.

    This method tests whether the microphone works properly. Once the test starts, the SDK uses the IRtcEngineEventHandler::onAudioVolumeIndication() callback to notify the application about the volume information.

    @param indicationInterval Period (ms) of the agora::rtc::IRtcEngineEventHandler::onAudioVolumeIndication callback cycle.
    @return

- 0: Success.
- <0: Failure.
    */
    virtual int startRecordingDeviceTest(int indicationInterval) = 0;

    /** Stops the microphone test.

    This method stops the microphone test. To stop the test, call this method after calling the startRecordingDeviceTest() method.

    @return

- 0: Success.
- <0: Failure.
    */
    virtual int stopRecordingDeviceTest() = 0;

    /** Releases the resource.
    */
    virtual void release() = 0;
};

/** Definition of RTCEngineContext.
*/
struct RtcEngineContext
{
    IRtcEngineEventHandler* eventHandler;
    /** App ID issued to the developers by Agora. Apply for a new one from Agora if it is missing from your kit.
    */
    const char* appId;
    RtcEngineContext()
    :eventHandler(NULL)
    ,appId(NULL)
    {}
};

/** The RtcEngine class provides the main methods that can be invoked by your application.

IRtcEngine is the basic interface class of the Agora Native SDK.
Creating an IRtcEngine object and then calling the methods of
this object enables the use of Agora Native SDK’s communication functionality.
In previous versions, this class was named IAgoraAudio, and
renamed to IRtcEngine from version 1.0.
*/
class IRtcEngine
{
public:
    /** Releases the IRtcEngine object.
    @param sync

    - True: Synchronous call. The result returns after the IRtcEngine object resources are released. The application should not call this interface in the callback generated by the SDK, otherwise the SDK must wait for the callback to return in order to recover the associated object resources, resulting in a deadlock. The SDK automatically detects the deadlock and turns it into an asynchronous call, but the test itself takes extra time.
    - False: Asynchronous call. The result returns immediately even when the IRtcEngine object resources are not released, and the SDK will release all resources. Note: Do not immediately uninstall the SDK's dynamic library after the call, otherwise it may crash because the SDK clean-up thread has not quit.

    @return

    - 0: Success.
    - <0: Failure.
  */
    virtual void release(bool sync=false) = 0;

	/** Initializes the Agora SDK service.

Enter the Agora App ID issued to start initialization.
After creating an IRtcEngine object, call this method to initialize the service before using any other methods. After initialization, the service is set to voice mode by default.
    @param context agora::rtc::RtcEngineContext
    @return

- 0: Success.
- <0: Failure.
    */
    virtual int initialize(const RtcEngineContext& context) = 0;

    /** Gets the pointer of the device manager object.
    @param iid Interface ID of the interface you want to get.
    @param inter Pointer you want to point to the DeviceManager object.
    @return

- 0: Success.
- <0: Failure.
    */
    virtual int queryInterface(INTERFACE_ID_TYPE iid, void** inter) = 0;

    /** Gets the SDK version.
    @param build Build number.
    @return SDK version number string in char format.
    */
    virtual const char* getVersion(int* build) = 0;

    /** Gets the warning or error description.
    @param code Warning or error code returned in IRtcEngineEventHandler::onWarning or IRtcEngineEventHandler::onError.
    @return Returns agora::WARN_CODE_TYPE or agora::ERROR_CODE_TYPE.
    */
    virtual const char* getErrorDescription(int code) = 0;

    /** Allows a user to join a channel.

Users in the same channel can talk to each other; and multiple users in the same channel can start a group chat.
Users using different App IDs cannot call each other.
Once in a call, the user must call the IRtcEngine::leaveChannel() method to exit the current call before entering another channel.

Note: A channel does not accept duplicate uids, such as two users with the same uid. If you set uid as 0, the system will automatically assign a uid.

  @param token A Token generated by the application. This parameter is optional if the user uses a static key, or App ID. In this case, pass NULL as the parameter value. If the user uses a channel key, Agora issues an additional App Certificate to the application developers. The developers can then generate a user key using the algorithm and App Certificate provided by Agora for user authentication on the server. In most circumstances, the static App ID will suffice. For added security, use the channel key.
    @param channelId A string providing a unique channel name for the AgoraRTC session. The length must be within 64 bytes. The following is the supported scope: a-z, A-Z, 0-9, space, ! #$%&, ()+,  -, :;<=., >? @[], ^_, {|}, ~
  @param info (Optional) Additional information about the channel that developers need to add. It can be set as a NULL string or channel related information. Other users in the channel will not receive this message.
    @param uid (Optional) User ID: A 32-bit unsigned integer ranging from 1 to (2^32-1). It must be unique. If not assigned (or set to 0), the SDK assigns one and returns it in the onJoinChannelSuccess callback. Your app must record and maintain the returned value as the SDK does not maintain it.
    @return

- 0: Success.
- <0: Failure.
    */
    virtual int joinChannel(const char* token, const char* channelId, const char* info, uid_t uid) = 0;

    /** Allows a user to leave a channel, such as hanging up or exiting a call.

After joining a channel, the user must call the leaveChannel method to end the call before joining another one.
It returns 0 if the user has successfully left the channel.
The leaveChannel method releases all resources related to the call.

The leaveChannel method is called asynchronously, and the user has not actually left the channel when the call returns. Once the user leaves the channel, the SDK triggers the IRtcEngineEventHandler::onLeaveChannel() callback.

Note: If you call release() immediately after leaveChannel, the leaveChannel process will be interrupted, and the SDK will not trigger the onLeaveChannel() callback.
    @return

- 0: Success.
- <0: Failure.
    */
    virtual int leaveChannel() = 0;

    /** Renews the Token.

The Token expires after a certain period of time once the Token schema is enabled when:

- The IRtcEngineEventHandler::onError callback reports the ERR_TOKEN_EXPIRED(-109) error, or
- The IRtcEngineEventHandler::onRequestToken callback reports the ERR_TOKEN_EXPIRED(-109) error.

The application should retrieve a new key and then call this method to
renew it. Failure to do so will result in the SDK disconnecting from the server.
    @param token The Token to renew.
    @return

- 0: Success.
- <0: Failure.
    */
    virtual int renewToken(const char* token) = 0;
/** Sets the channel profile.

The Agora RtcEngine needs to know what scenario the application is in to apply different methods for optimization.

Note:

- Only one profile can be used at the same time in the same channel.
- This method must be called and configured before a user joining a channel, because the channel profile cannot be configured when the channel is in use.
- In the communication mode, the Agora SDK supports encoding only in raw data, not in texture.

@param Channel profile: agora::rtc::CHANNEL_PROFILE_TYPE
@return

- 0: Success.
- <0: Failure.
*/
    virtual int setChannelProfile(CHANNEL_PROFILE_TYPE profile) = 0;
    /** Sets the role of the user, such as a host or an audience (default) before joining a channel.

This method also allows you to switch the user role after joining a channel.

     @param role Role of the client: agora::rtc::CLIENT_ROLE_TYPE

@return

- 0: Success.
- <0: Failure.
*/
    virtual int setClientRole(CLIENT_ROLE_TYPE role) = 0;

    /** Starts an audio call test.

    This method launches an audio call test to determine whether the audio devices (for example, headset and speaker) and the network connection are working properly. In the test, the user first speaks, and the recording is played back in 10 seconds. If the user can hear the recording in 10 seconds, it indicates that the audio devices and network connection work properly.


Note: After calling the startEchoTest() method, always call stopEchoTest() to end the test.
	Otherwise, the application cannot run the next echo test, nor can it call the @return

- 0: Success.
- <0: Failure.

@return

- 0: Success.
- <0: Failure.
    */
    virtual int startEchoTest() = 0;

    /** Stops the audio call test.
    @return

- 0: Success.
- <0: Failure.
    */
    virtual int stopEchoTest() = 0;

    /** Enables the network test.

    This method tests the quality of the user’s network connection and is disabled by default.

Before users join a channel, they can call this method to check the network quality.

Calling this method consumes extra network traffic, which may affect the communication quality.
Call disableLastmileTest() to disable it immediately once users have received the
IRtcEngineEventHandler::onLastmileQuality callback before they join the channel.

    @return

- 0: Success.
- <0: Failure.
    */
    virtual int enableLastmileTest() = 0;

    /** Disables the network connection quality test.
    @return

- 0: Success.
- <0: Failure.
    */
    virtual int disableLastmileTest() = 0;

    /** Enables the video mode.
     
     The application can call this method either before entering a channel or during a call. If it is called before entering a channel, the service starts in the video mode; if it is called during a call, it switches from the audio to video mode. To disable the video mode, call the disableVideo() method.
     
     Note: This method controls the underlying states of the Engine. It is still valid after one leaves channel.
     
     @return

      - 0: Success.
      - <0: Failure.
    */
    virtual int enableVideo() = 0;

    /** Disables the video mode.

The application can call this method either before entering a channel or during a call. If it is called before entering a channel, the service starts in the audio mode; if it is called during a call, it switches from the video to audio mode.  To enable the video mode, call the enableVideo() method.
     
Note: This method controls the underlying states of the Engine. It is still valid after one leaves channel.

@return

- 0: Success.
- <0: Failure.
    */
    virtual int disableVideo() = 0;

    /** Starts the local video preview before joining the channel.

    Before using this method, you need to:

- Call setupLocalVideo() to set up the local preview window and configure the attributes.
- Call enableVideo() to enable the video.

Once startPreview() is called to start the local video preview, if you leave the channel by calling IRtcEngine::leaveChannel(), the local video preview remains until you call stopPreview() to disable it.

@return

- 0: Success.
- <0: Failure.
    */
    virtual int startPreview() = 0;

    /** Stops the local video preview and the video.
    @return

- 0: Success.
- <0: Failure.
    */
    virtual int stopPreview() = 0;
/** Sets the video encoding profile.

Each video encoding profile includes a set of parameters, such as the resolution, frame rate, and bitrate.  When the camera device does not support the specified resolution, the SDK will automatically choose a suitable camera resolution, while the encoder resolution will still be the one specified by setVideoProfile().

Note:

- Always set the video profile after calling the enableVideo() method.
- Always set the video profile before calling the joinChannel() or startPreview() method.

@param profile Video profile: agora::rtc::VIDEO_PROFILE_TYPE.
@param swapWidthAndHeight Width and height of the output video is consistent with that of the video profile you set. This parameter sets whether to swap the width and height of the stream:

- True: Swap the width and height.
- False: (Default) Do not swap the width and height.

Since the landscape or portrait mode of the output video can be decided directly by the video profile, Agora recommends setting this parameter as default.
@return

- 0: Success.
- <0: Failure.
*/
    virtual int setVideoProfile(VIDEO_PROFILE_TYPE profile, bool swapWidthAndHeight) = 0;

    /** Sets the video encoder configuration.

    Each configuration profile corresponds to a set of video parameters, including the resolution, frame rate, bitrate, and video orientation.
The parameters specified in this method are the maximum values under ideal network conditions. If the video engine cannot render the video using the specified parameters due to poor network conditions, the parameters further down the list are considered until success.

     @param config Video encoder configuration: VideoEncoderConfiguration.
     @return

- 0: Success.
- <0: Failure.
     */
    virtual int setVideoEncoderConfiguration(
        const VideoEncoderConfiguration& config) = 0;

    /** Sets the remote video view.
     
     This method binds the remote user to the video display window, that is, sets the view for the user of the specified uid. Usually the application should specify the uid of the remote video in the method call before the user enters a channel.
     
     If the remote uid is unknown to the application, set it later when the application receives the IRtcEngineEventHandler::onUserJoined() event.
     
     If the Video Recording function is enabled, the Video Recording Service joins the channel as a dumb client, which means other clients also receive this onUserJoined() event. Your application should not bind it with the view, because it does not send any video stream. If your application cannot recognize the dumb client, bind it with the view when the IRtcEngineEventHandler::onFirstRemoteVideoDecoded event is triggered. To unbind the user with the view, set the view to null. Once the user has left the channel, the SDK unbinds the remote user.
     
     
     
     @param canvas Video canvas information: VideoCanvas
     @return

      - 0: Success.
      - <0: Failure.
    */
    virtual int setupRemoteVideo(const VideoCanvas& canvas) = 0;

    /** Sets the local video view.

    This method configures the video display settings on the local machine.
    
    The application calls this method to bind with the video window (view) of the local video streams and configure the video display settings. Call this method after initialization to configure the local video display settings before entering a channel. After leaving the channel, the bind is still valid, which means the window still displays. To unbind the view, set the view value to NULL when calling setupLocalVideo().
    
     @param canvas Video canvas information: VideoCanvas.
    @return

- 0: Success.
- <0: Failure.
    */
    virtual int setupLocalVideo(const VideoCanvas& canvas) = 0;

    /** Enables the audio mode, which is enabled by default.
     
    Note: This method controls the underlying states of the Engine. It is still valid after one leaves channel.

    @return

    - 0: Success.
    - <0: Failure.
    */
    virtual int enableAudio() = 0;

    /** Disables the audio mode.
     
     Note: This method controls the underlying states of the Engine. It is still valid after one leaves channel.
     
    @return

    - 0: Success.
    - <0: Failure.
    */
    virtual int disableAudio() = 0;

	/** Sets the audio parameters and application scenarios.

 @param  profile Sets the sampling rate, bitrate, encode mode, and the number of channels: agora::rtc::AUDIO_PROFILE_TYPE
 @param  scenario Sets the audio application scenarios: agora::rtc::AUDIO_SCENARIO_TYPE

 @return

- 0: Success.
- <0: Failure.
     */
    virtual int setAudioProfile(AUDIO_PROFILE_TYPE profile, AUDIO_SCENARIO_TYPE scenario) = 0;

#if defined(__APPLE__) || defined(_WIN32)

#if defined(__APPLE__)
  typedef unsigned int WindowIDType;
#elif defined(_WIN32)
  typedef HWND WindowIDType;
#endif
  /** Starts screen sharing.

  This method shares the whole screen, the specified window, or the specified region:

  - Share the whole screen: Set windowId as 0 and set rect as null.
  - Share the specified window: Set windowId not as 0, each window has a windowId which is not 0.
  - Share the specified region: Set windowId as 0 and set rect not as null. In this case, you can share the specified region, for example by dragging the mouse, the logic of which is implemented by yourselves.

Note: The specified region means a region on the whole screen. Currently, it does not support sharing a specified region in a specific window.
         captureFreq is the captured frame rate once the screen-sharing function is enabled, and the value (mandatory) ranges from 1 fps to 15 fps. No matter which function you have enabled, it returns 0 after successful execution, otherwise it returns an error code.

    @param windowId Screen sharing area: WindowIDType
   @param rect     This parameter is valid when windowsId is set as 0, and when you set rect as null, then the whole screen is shared

   @return

- 0: Success.
- <0: Failure.
   */
  virtual int startScreenCapture(WindowIDType windowId, int captureFreq, const Rect *rect, int bitrate) = 0;

  /** Stop screen sharing.

   @return

- 0: Success.
- <0: Failure.
   */
  virtual int stopScreenCapture() = 0;

  /** Updates the screen capture region.

@param rect  This parameter is valid when windowsId is set as 0, and when you set rect as null, then the whole screen is shared

   @return

   - 0: Success.
   - <0: Failure.
   */
  virtual int updateScreenCaptureRegion(const Rect *rect) = 0;
#endif

    /** Gets the current call ID.

    When a user joins a channel on a client,
a callId is generated to identify the call from the client.
Some methods such as rate and complain need to be called after the call ends in order to submit feedback to the SDK. These methods require assigned values of the callId parameters.
To use these feedback methods, call the getCallId() method to retrieve the callId during the call, and then pass the value as an argument in the feedback methods after the call ends.

    @param callId The current call ID.
    @return

- 0: Success.
- <0: Failure.
    */
    virtual int getCallId(agora::util::AString& callId) = 0;

/** Allows the user to rate the call.

It is usually called after the call ends.

@param callId Call ID retrieved from the getCallId() method.
@param rating  The rating of the call between 1 (lowest score) to 10 (highest score).
@param description (Optional) Description for the call with a length less than 800 bytes.

@return

- 0: Success.
- <0: Failure.
*/
    virtual int rate(const char* callId, int rating, const char* description) = 0; // 0~10

    /** Allows a user to complain about the call quality.

    It is usually called after the call ends.

    @param callId Call ID retrieved from the getCallId() method.
    @param description (Optional) Description for the call with a length less than 800 bytes.

    @return

    - 0: Success.
    - <0: Failure.

    */
    virtual int complain(const char* callId, const char* description) = 0;

    /** Register a packet observer.

    The Agora Native SDK allows your application to register a packet observer to receive events whenever a voice or video packet is transmitting.

    @param observer IPacketObserver
    @return

- 0: Success.
- <0: Failure.
    */
    virtual int registerPacketObserver(IPacketObserver* observer) = 0;

	/** Sets the built-in encryption mode.

  The Agora Native SDK supports built-in encryption, which is in AES-128-XTS mode by default.
If you want to use other modes, call this API to set the encryption mode.

All users in the same channel must use the same encryption mode and password.
Refer to information related to the AES encryption algorithm on the differences between encryption modes.

Note: Call setEncryptionSecret() to enable the built-in encryption function before calling this API.
	@param encryptionMode Encryption mode:
  - "aes-128-xts":128-bit AES encryption, XTS mode
  - "aes-128-ecb":128-bit AES encryption, ECB mode
  - "aes-256-xts": 256-bit AES encryption, XTS mode
  - "": When it is set to NUL string, the encryption is in "aes-128-xts" by default.
	@return

- 0: Success.
- <0: Failure.
	*/
	virtual int setEncryptionMode(const char* encryptionMode) = 0;
	/** Enables built-in encryption.

  Use setEncryptionSecret() to specify an encryption password to enable built-in encryption before joining a channel.
All users in a channel must set the same encryption password.
The encryption password is automatically cleared once a user has left the channel.
If the encryption password is not specified or set to empty, the encryption function will be disabled.

	@param secret Encryption password
	@return

- 0: Success.
- <0: Failure.
	*/
	virtual int setEncryptionSecret(const char* secret) = 0;
/** Creates a data stream.

Each user can only have up to five data channels at the same time.

Note: Set *reliable* and *ordered* both as True or both as False. Do not set one as *True* and the other as *False*.

@param reliable

- True: The recipients will receive data from the sender within 5 seconds. If the recipient does not receive the sent data within 5 seconds, the data channel will report an error to the application.
- False: The recipients will not receive any data, and it will not report any error upon data missing.

@param ordered

- True: The recipients will receive data in the order of the sender.
- False: The recipients will not receive data in the order of the sender.

@return

- 0: Success.
- <0: Failure.

*/
    virtual int createDataStream(int* streamId, bool reliable, bool ordered) = 0;
    /** Sends data stream messages to all users in a channel.

    Up to 30 packets can be sent per second in a channel with each packet having a maximum size of 1 kB.
The API controls the data channel transfer rate. Each client can send up to
6 kB of data per second. Each user can have up to five data channels simultaneously.

@param  streamId  Stream ID returned by createDataStream().
@param message Data to be sent.

@return

- 0: Success.
- <0: Failure.
    */
    virtual int sendStreamMessage(int streamId, const char* data, size_t length) = 0;
/** @deprecated
Sets the picture-in-picture layout.

Note: This method has been deprecated and Agora recommends you not use it. If you want to set the compositing layout in the CDN broadcast, call the setLiveTranscoding() method.

This method sets the picture-in-picture layouts for live broadcast. This method is only applicable when you
want to push streams at the Agora server. When you push stream at the server:

1. Define a canvas, its width and height (video resolution), the background color, and the number of videos you want to display in total.

2. Define the position and size of each video on the canvas, and whether it is cropped or zoomed to fit.

Note:

- Call this method after joining a channel.
- The application should only allow one user to call this method in the same channel, if more than one user calls this method, the other users must call clearVideoCompositingLayout() to remove the settings.


*/
    virtual int setVideoCompositingLayout(const VideoCompositingLayout& sei) = 0;
    /** Removes the picture-in-picture layout settings made by calling setVideoCompositingLayout().

    */
    virtual int clearVideoCompositingLayout() = 0;
    /** @deprecated
    Configures push-stream for CDN Live.

Note: This method is deprecated. You can still use it to publish to CDN Live but Agora recommends using the following methods instead:

  - addPublishStreamUrl()
  - removePublishStreamUrl()
  - setLiveTranscoding()

  This method configures the push-stream settings for the engine before joining a channel for CDN Live.

@param config Push-steam settings for CDN Live: PublisherConfiguration
    */
	virtual int configPublisher(const PublisherConfiguration& config) = 0;
/** Adds a stream URL.

This method is used for CDN live and adds the CDN URL address to which the publisher pushes the stream.

Note:

- Ensure that this API is called after you have joined the channel.
- This method only adds one stream URL each time it is called.
- Do not add special characters such as Chinese to the URL.

@param url URL to which the publisher pushes the stream.

@param  transcodingEnabled

- True: Enables transcoding
- False: Disables transcoding
*/
    virtual int addPublishStreamUrl(const char *url, bool transcodingEnabled) = 0;
/** Removes a stream URL.

This method is used for CDN live and removes a stream URL each time it is called.

Note:

- This method only removes one URL each time it is called.
- Do not add special characters such as Chinese to the URL.
*/
    virtual int removePublishStreamUrl(const char *url) = 0;
    /** Sets live transcoding.

    This method is used for CDN Live and sets the video layout and audio for CDN Live.
    */
    virtual int setLiveTranscoding(const LiveTranscoding &transcoding) = 0;
/** Adds a watermark to the local video stream.

This method adds a watermark in the PNG file format onto the local video stream so that the recording device and the audience in the channel and CDN audience can see or capture it.
To add the PNG file onto the CDN publishing stream only, see the method described in setLiveTranscoding().

@param watermark RtcImage

*/
    virtual int addVideoWatermark(const RtcImage& watermark) = 0;
    /** Removes the watermark image on the video stream added by addVideoWatermark().
    */
    virtual int clearVideoWatermarks() = 0;
/** Adds a voice or video stream URL to a live broadcast.

If successful, you can find the stream in the channel and the uid of the stream is 666.

@param url URL address to be added into the ongoing live broadcast. You can use the RTMP, HLS, and FLV protocols.
@param config   Definition of the added voice or video stream: InjectStreamConfig.
*/
    virtual int addInjectStreamUrl(const char* url, const InjectStreamConfig& config) = 0;
    /** Removes the voice or video stream URL from a live broadcast.

  @param url URL address of the added stream to be removed.
    */
    virtual int removeInjectStreamUrl(const char* url) = 0;

    virtual bool registerEventHandler(IRtcEngineEventHandler *eventHandler) = 0;
    virtual bool unregisterEventHandler(IRtcEngineEventHandler *eventHandler) = 0;
};


class IRtcEngineParameter
{
public:
    /**
    * Releases the resource.
    */
    virtual void release() = 0;

    /** Sets the bool value of the JSON.
    @param key Key name
    @param value Value
    @return

- 0: Success.
- <0: Failure.
    */
    virtual int setBool(const char* key, bool value) = 0;

    /** Set the int value of the JSON.
    @param key Key name
    @param value Value
    @return

- 0: Success.
- <0: Failure.
    */
    virtual int setInt(const char* key, int value) = 0;

    /** Sets the unsigned int value of the JSON.
    @param key Key name
    @param value Value
    @return

- 0: Success.
- <0: Failure.
    */
    virtual int setUInt(const char* key, unsigned int value) = 0;

    /** Sets the double value of the JSON.
    @param key Key name
    @param value Value
    @return

- 0: Success.
- <0: Failure.
    */
    virtual int setNumber(const char* key, double value) = 0;

    /** Sets the string value of the JSON.
    @param key Key name
    @param value Value
    @return

- 0: Success.
- <0: Failure.
    */
    virtual int setString(const char* key, const char* value) = 0;

    /** Sets the object value of the JSON.
    @param key Key name
    @param value Value
    @return

- 0: Success.
- <0: Failure.
    */
    virtual int setObject(const char* key, const char* value) = 0;

    /** Gets the bool value of the JSON.
    @param key Key name
    @param value Value
    @return

- 0: Success.
- <0: Failure.
    */
    virtual int getBool(const char* key, bool& value) = 0;

    /** Gets the int value of the JSON.
    @param key Key name
    @param value Value
    @return

- 0: Success.
- <0: Failure.
    */
    virtual int getInt(const char* key, int& value) = 0;

    /** Gets the unsigned int value of the JSON.
    @param key Key name
    @param value Value
    @return

- 0: Success.
- <0: Failure.
    */
    virtual int getUInt(const char* key, unsigned int& value) = 0;

    /** Gets the double value of the JSON.
    @param key Key name
    @param value Value
    @return

- 0: Success.
- <0: Failure.
    */
    virtual int getNumber(const char* key, double& value) = 0;

    /** Gets the string value of the JSON.
    @param key Key name
    @param value Value
    @return

- 0: Success.
- <0: Failure.
    */
    virtual int getString(const char* key, agora::util::AString& value) = 0;

    /** Gets a child object value of the JSON.
    @param key Key name
    @param value Value
    @return

- 0: Success.
- <0: Failure.
    */
    virtual int getObject(const char* key, agora::util::AString& value) = 0;

    /** Gets the array value of the JSON.
    @param key Key name
    @param value Value
    @return

- 0: Success.
- <0: Failure.
    */
    virtual int getArray(const char* key, agora::util::AString& value) = 0;

    /** Sets the parameters of the SDK or engine.
    @param parameters Parameters
    @return

- 0: Success.
- <0: Failure.
    */
    virtual int setParameters(const char* parameters) = 0;

    /** Sets the profile to control the RTC engine.
    @param profile Profile
    @param merge
     - True: Merge with the original value.
     - False: Do not merge with the orginal value.
    @return

- 0: Success.
- <0: Failure.
    */
    virtual int setProfile(const char* profile, bool merge) = 0;

	virtual int convertPath(const char* filePath, agora::util::AString& value) = 0;
};

class AAudioDeviceManager : public agora::util::AutoPtr<IAudioDeviceManager>
{
public:
    AAudioDeviceManager(IRtcEngine* engine)
    {
		queryInterface(engine, AGORA_IID_AUDIO_DEVICE_MANAGER);
    }
};

class AVideoDeviceManager : public agora::util::AutoPtr<IVideoDeviceManager>
{
public:
    AVideoDeviceManager(IRtcEngine* engine)
    {
		queryInterface(engine, AGORA_IID_VIDEO_DEVICE_MANAGER);
    }
};

class AParameter : public agora::util::AutoPtr<IRtcEngineParameter>
{
public:
    AParameter(IRtcEngine& engine) { initialize(&engine); }
    AParameter(IRtcEngine* engine) { initialize(engine); }
    AParameter(IRtcEngineParameter* p) :agora::util::AutoPtr<IRtcEngineParameter>(p) {}
private:
    bool initialize(IRtcEngine* engine)
    {
        IRtcEngineParameter* p = NULL;
        if (engine && !engine->queryInterface(AGORA_IID_RTC_ENGINE_PARAMETER, (void**)&p))
            reset(p);
        return p != NULL;
    }
};
/** The RtcEngineParameters class is an auxiliary class that sets parameters for the SDK.

*/
class RtcEngineParameters
{
public:
    RtcEngineParameters(IRtcEngine& engine)
        :m_parameter(&engine){}
    RtcEngineParameters(IRtcEngine* engine)
        :m_parameter(engine){}

    /** Mutes a local audio stream.

    This method mutes or unmutes the local audio. It enables or disables sending local audio streams to the network.

Note: This method does not disable the microphone, and thus does not affect any recording process.

@param mute

- True: Mutes the local audio.
- False: Unmutes the local audio.

@return

- 0: Success.
- <0: Failure.
    */
    int muteLocalAudioStream(bool mute) {
        return setParameters("{\"rtc.audio.mute_me\":%s,\"che.audio.mute_me\":%s}", mute ? "true" : "false", mute ? "true" : "false");
    }
    // mute/unmute all peers. unmute will clear all muted peers specified mutePeer() interface
  /** Mutes all remote users’ audio streams.

Note:  When set to True, this method mutes the audio streams without affecting the audio stream receiving process.

@param mute

- True: Mutes all received audio streams.
- False: Unmute all received audio streams.
@return

- 0: Success.
- <0: Failure.
    */
    int muteAllRemoteAudioStreams(bool mute) {
        return m_parameter ? m_parameter->setBool("rtc.audio.mute_peers", mute) : -ERR_NOT_INITIALIZED;
    }

    /** Sets the default to mute or unmute all the remote audio receiving streams.


@param mute

- True:  Mutes all the remote audio receiving streams.
- False: (Default) Unmutes all the remote audio receiving streams.
@return

- 0: Success.
- <0: Failure.
    */
    int setDefaultMuteAllRemoteAudioStreams(bool mute) {
        return m_parameter ? m_parameter->setBool("rtc.audio.set_default_mute_peers", mute) : -ERR_NOT_INITIALIZED;
    }

    /** Mutes a specified user's audio stream.

    Note: When set to True, this method mutes the audio stream
  without affecting the audio stream receiving process.

@param uid User ID of the user whose audio stream is to be muted.
@param mute

- True: Mutes the user’s audio stream.
- False: Unmutes the user’s audio stream.
@return

- 0: Success.
- <0: Failure.
    */
    int muteRemoteAudioStream(uid_t uid, bool mute) {
        return setObject("rtc.audio.mute_peer", "{\"uid\":%u,\"mute\":%s}", uid, mute?"true":"false");
    }

    /** Stops sending the local video streams to the network.

    Note:  When set to True, this method does not disable the camera, and thus does not affect the retrieval of the local video streams.

@param mute

- True: Stops sending local video streams to the network.
- False: Allows sending local video streams to the network.
@return

- 0: Success.
- <0: Failure.
    */
    int muteLocalVideoStream(bool mute) {
        return setParameters("{\"rtc.video.mute_me\":%s,\"che.video.local.send\":%s}", mute ? "true" : "false", mute ? "false" : "true");
    }

/** Disables the local video.

This method disables the local video, which is only applicable to the scenario
when the user only wants to watch the remote video without sending any video
stream to the other user. This method does not require a local camera.
 
 Note: This method controls the underlying states of the Engine. It is still valid after one leaves channel.

@param  enabled

- True: Enables the local video (default)
- False: Disables the local video

@return

- 0: Success.
- <0: Failure.

*/
	int enableLocalVideo(bool enabled) {
		return setParameters("{\"rtc.video.capture\":%s,\"che.video.local.capture\":%s,\"che.video.local.render\":%s,\"che.video.local.send\":%s}", enabled ? "true" : "false", enabled ? "true" : "false", enabled ? "true" : "false", enabled ? "true" : "false");
	}
    /** Stops playing all the received video streams from the remote users.

    Note:     When set to True, this method stops playing video streams without affecting the video stream receiving process.

@param  mute

- True: Stops playing all the received video streams from the remote users.
- False: (Default) Allows playing all the received video streams from the remote users.
@return

- 0: Success.
- <0: Failure.
    */
    int muteAllRemoteVideoStreams(bool mute) {
        return m_parameter ? m_parameter->setBool("rtc.video.mute_peers", mute) : -ERR_NOT_INITIALIZED;
    }

    /** Sets the default to stop all the received remote video streams from the remote users.

@param mute

- True: Sets the default to stop playing all the received video streams from the remote users.
- False: (Default) Sets the default to allow playing all the received video streams from the remote users.
@return

- 0: Success.
- <0: Failure.
    */
    int setDefaultMuteAllRemoteVideoStreams(bool mute) {
        return m_parameter ? m_parameter->setBool("rtc.video.set_default_mute_peers", mute) : -ERR_NOT_INITIALIZED;
    }

    /** Stops playing a specified user’s video stream.

@param uid User ID of the specified user.

@param mute

- True: Stops playing a specified user’s video stream.
- False: Allows playing a specified user’s video stream.
@return

- 0: Success.
- <0: Failure.
    */
    int muteRemoteVideoStream(uid_t uid, bool mute) {
        return setObject("rtc.video.mute_peer", "{\"uid\":%u,\"mute\":%s}", uid, mute ? "true" : "false");
    }
/** Sets the video-stream type of the remote user to be received by the local user when the remote user sends dual streams.

- If dual-stream mode is enabled by calling enableDualStreamMode(), you will receive the high-video stream by default. This method allows the application to adjust the corresponding video-stream type
  according to the size of the video window to reduce the bandwidth and resources.
- If dual-stream mode is not enabled, you will receive the high-video stream by default.

The result after calling this method will be returned in IRtcEngineEventHandler::onApiCallExecuted(). The Agora SDK
receives the high-video stream by default to reduce the bandwidth. If needed, users
can switch to the low-video stream by using this method.

The resolution of the high-video stream is 1.1, 4.3, or 16.9. By default, the aspect ratio of the low-video stream is the same as that of the high-video stream.
Once the resolution of the high-video stream is set, the system automatically sets the aspect ratio for the low-video stream.

| Resolution | Frame Rate | Keyframe Interval | Bitrate (kbit/s)|
|------------|------------|-------------------|-----------------|
| 160 x 160  | 5          | 5                 | 45              |
| 160 x 120  | 5          | 5                 | 32              |
| 160 x 90   | 5          | 5                 | 28              |

@param uid User ID
@param streamType   Video-stream size: agora::rtc::REMOTE_VIDEO_STREAM_TYPE

@return

- 0: Success.
- <0: Failure.
*/
    int setRemoteVideoStreamType(uid_t uid, REMOTE_VIDEO_STREAM_TYPE streamType) {
        return setParameters("{\"rtc.video.set_remote_video_stream\":{\"uid\":%u,\"stream\":%d}, \"che.video.setstream\":{\"uid\":%u,\"stream\":%d}}", uid, streamType, uid, streamType);
//        return setObject("rtc.video.set_remote_video_stream", "{\"uid\":%u,\"stream\":%d}", uid, streamType);
    }
    /** Sets the default video-stream type to be received by the local user when the remote user sends dual streams.

    - If dual-stream mode is enabled by calling enableDualStreamMode(), you will receive the high-video stream by default. This method allows the application to adjust the corresponding video-stream type
      according to the size of the video window to reduce the bandwidth and resources.
    - If dual-stream mode is not enabled, you will receive the high-video stream by default.

    The result after calling this method will be returned in IRtcEngineEventHandler::onApiCallExecuted(). The Agora SDK
    receives the high-video stream by default to reduce the bandwidth. If needed, users
    can switch to the low-video stream by using this method.

    The resolution of the high-video stream is 1.1, 4.3, or 16.9. By default, the aspect ratio of the low-video stream is the same as that of the high-video stream.
    Once the resolution of the high-video stream is set, the system automatically sets the aspect ratio for the low-video stream.

    | Resolution | Frame Rate | Keyframe Interval | Bitrate (kbit/s)|
    |------------|------------|-------------------|-----------------|
    | 160 x 160  | 5          | 5                 | 45              |
    | 160 x 120  | 5          | 5                 | 32              |
    | 160 x 90   | 5          | 5                 | 28              |

    @param streamType   Video-stream size: agora::rtc::REMOTE_VIDEO_STREAM_TYPE

    @return

    - 0: Success.
    - <0: Failure.
    */
    int setRemoteDefaultVideoStreamType(REMOTE_VIDEO_STREAM_TYPE streamType) {
        return m_parameter ? m_parameter->setInt("rtc.video.set_remote_default_video_stream_type", streamType) : -ERR_NOT_INITIALIZED;
    }

    /**
@deprecated Sets the playback device volume.

Use IAudioDeviceManager::setPlaybackDeviceVolume() instead.

@param volume Volume of the playing device, ranging from 0 to 255
@return

- 0: Success.
- <0: Failure.
    */
    int setPlaybackDeviceVolume(int volume) {// [0,255]
        return m_parameter ? m_parameter->setInt("che.audio.output.volume", volume) : -ERR_NOT_INITIALIZED;
    }

    /** Enables the SDK to regularly report to the application on which user is talking and the volume of the speaker.

    Once the method is enabled, the SDK returns the volume indication at the set time interval in the IRtcEngineEventHandler::onAudioVolumeIndication() callback, regardless of whether anyone is speaking in the channel

@param interval Time interval between two consecutive volume indications:

- <= 0: Disables the volume indication
- > 0: Time interval (ms) between two consecutive volume indications. Agora recommends setting it to more than 200 ms. Do not set it lower than 10 ms, or the onAudioVolumeIndication() callback will not be triggered.

@param smooth  Smoothing factor. The default value is 3.
@return

- 0: Success.
- <0: Failure.
    */
    int enableAudioVolumeIndication(int interval, int smooth) { // in ms: <= 0: disable, > 0: enable, interval in ms
        if (interval < 0)
            interval = 0;
        return setObject("che.audio.volume_indication", "{\"interval\":%d,\"smooth\":%d}", interval, smooth);
    }

    /** Starts an audio recording.

    The SDK allows recording during a call, which supports either one of the following two formats:

- *.wav*: Large file size with high sound fidelity **OR**

- *.aac*: Small file size with low sound fidelity

Ensure that the directory to save the recording file exists and is writable.
This method is usually called after the IRtcEngine::joinChannel() method.
The recording automatically stops when the IRtcEngine::leaveChannel() method is called.

    @param filePath Full file path of the recording file. The string of the file name is in UTF-8 code.
    @return

- 0: Success.
- <0: Failure.
    */
    int startAudioRecording(const char* filePath, AUDIO_RECORDING_QUALITY_TYPE quality) {
        if (!m_parameter) return -ERR_NOT_INITIALIZED;
#if defined(_WIN32)
        util::AString path;
        if (!m_parameter->convertPath(filePath, path))
            filePath = path->c_str();
        else
            return -ERR_INVALID_ARGUMENT;
#endif
        return setObject("che.audio.start_recording", "{\"filePath\":\"%s\",\"quality\":%d}", filePath, quality);
    }

    /** Stops an audio recording on the client.

Call this method before calling IRtcEngine::leaveChannel(); otherwise, the recording automatically stops when the leaveChannel() method is called.

    @return

- 0: Success.
- <0: Failure.
    */
    int stopAudioRecording() {
        return m_parameter ? m_parameter->setBool("che.audio.stop_recording", true) : -ERR_NOT_INITIALIZED;
    }

	/** Stops audio mixing.

  This method mixes the specified local audio file with the audio stream
from the microphone; or, it replaces the microphone's audio stream
with the specified local audio file. You can choose whether the other user
can hear the local audio playback and specify the number of loop playbacks.
This API also supports online music playback.

Note: Call this API when you are in a channel, otherwise it may cause issues.

	@param filePath Name and path of the local audio file to be mixed. Supported audio formats: mp3, aac, m4a, 3gp, and wav.
	@param loopback

  - True: Only the local user can hear the remix or the replaced audio stream.
  - False: Both users can hear the remix or the replaced audio stream.

	@param replace

  - True: the content of the local audio file replaces the audio stream from the microphone.
  -  False:  Local audio file mixed with the audio stream from the microphone.

	@param cycle Number of loop playbacks:
  - Positive integer: Number of loop playbacks.
  - -1: Infinite loop.

	@return

- 0: Success.
- <0: Failure.
	*/
	int startAudioMixing(const char* filePath, bool loopback, bool replace, int cycle) {
        if (!m_parameter) return -ERR_NOT_INITIALIZED;
#if defined(_WIN32)
		util::AString path;
		if (!m_parameter->convertPath(filePath, path))
			filePath = path->c_str();
		else
			return -ERR_INVALID_ARGUMENT;
#endif
		return setObject("che.audio.start_file_as_playout", "{\"filePath\":\"%s\",\"loopback\":%s,\"replace\":%s,\"cycle\":%d}",
					filePath,
					loopback?"true":"false",
					replace?"true":"false",
					cycle);
	}
	/** Stops the audio mixing.

  Call this API when you are in a channel.
	@return

- 0: Success.
- <0: Failure.
	*/
	int stopAudioMixing() {
        return m_parameter ? m_parameter->setBool("che.audio.stop_file_as_playout", true) : -ERR_NOT_INITIALIZED;
	}

/** Pauses audio mixing.

Call this API when you are in a channel.

@return

- 0: Success.
- <0: Failure.
*/
    int pauseAudioMixing() {
        return m_parameter ? m_parameter->setBool("che.audio.pause_file_as_playout", true) : -ERR_NOT_INITIALIZED;
    }
/** Resumes audio mixing.

Call this API when you are in a channel.

@return

- 0: Success.
- <0: Failure.
*/
    int resumeAudioMixing() {
        return m_parameter ? m_parameter->setBool("che.audio.pause_file_as_playout", false) : -ERR_NOT_INITIALIZED;
    }
/** Adjusts the volume during audio mixing.

Call this API when you are in a channel.

@param volume Volume ranging from 0 to 100. By default, 100 is the original volume.

@return

- 0: Success.
- <0: Failure.
*/
    int adjustAudioMixingVolume(int volume) {
        return m_parameter ? m_parameter->setInt("che.audio.set_file_as_playout_volume", volume) : -ERR_NOT_INITIALIZED;
    }

    /** Gets the duration (ms) of the audio mixing.

    Call this API when you are in a channel.
    */
    int getAudioMixingDuration() {
        int duration = 0;
        int r = m_parameter ? m_parameter->getInt("che.audio.get_mixing_file_length_ms", duration) : -ERR_NOT_INITIALIZED;
        if (r == 0)
            r = duration;
        return r;
    }

    /** Gets the playback position (ms) of the audio.

    Call this API when you are in a channel.
    */
    int getAudioMixingCurrentPosition() {
        if (!m_parameter) return -ERR_NOT_INITIALIZED;
        int pos = 0;
        int r = m_parameter->getInt("che.audio.get_mixing_file_played_ms", pos);
        if (r == 0)
            r = pos;
        return r;
    }
    /** Sets the playback position of the audio mixing file to where you want to play from instead of from the beginning.

    @param pos Integer. The position of the audio mixing file where you want to play from (ms).

    @return

    - 0: Success.
    - <0: Failure.
    */
    int setAudioMixingPosition(int pos /*in ms*/) {
        return m_parameter ? m_parameter->setInt("che.audio.mixing.file.position", pos) : -ERR_NOT_INITIALIZED;
    }

    /** Gets the volume of the audio effects from 0.0 to 100.0.

    @return

     - Audio effect volume: Success.
     - <0: Failure.
     */
    int getEffectsVolume() {
        if (!m_parameter) return -ERR_NOT_INITIALIZED;
        int volume = 0;
        int r = m_parameter->getInt("che.audio.game_get_effects_volume", volume);
        if (r == 0)
            r = volume;
        return r;
    }

    /** Sets the volume of the audio effects from 0.0 to 100.0.

     @param volume The volume ranges from 0.0 to 100.0. 100.0 is the default value.
     @return

     - 0: Success.
     - <0: Failure.
     */
    int setEffectsVolume(int volume) {
        return m_parameter ? m_parameter->setInt("che.audio.game_set_effects_volume", volume) : -ERR_NOT_INITIALIZED;
    }

    /** Sets the volume of the specified sound effect.

     @param soundId ID of the audio effect. Each audio effect has a unique ID.
     @param volume The volume ranges from 0.0 to 100.0. 100.0 is the default value.
     @return

- 0: Success.
- <0: Failure.
     */
    int setVolumeOfEffect(int soundId, int volume) {
        return setObject(
            "che.audio.game_adjust_effect_volume",
            "{\"soundId\":%d,\"gain\":%d}",
            soundId, volume);
    }

    /** Plays the specified audio effect.

  @param soundId ID of the specified audio effect. Each audio effect has a unique ID.

  Note: If you preloaded the audio effect into the memory through preloadEffect(), ensure that the soundID value is set to the same value as in preloadEffect().
  @param filePath The absolute path of the audio effect file.
  @param loopCount Set the number of times looping the audio effect:

  - 0: Play the audio effect once.
  - 1: Play the audio effect twice.
  - -1: Play the audio effect in a loop indefinitely, until stopEffect() or stopAllEffects() is called.

@param pitch Pitch of the audio effect. The range is [0.5, 2]. The default value is 1, which means no change to the pitch. The smaller the value, the lower the pitch.

@param pan Spatial position of the audio effect. The range is [-1.0, 1.0]:

- 0.0: The audio effect shows ahead.
- 1.0: The audio effect shows on the right.
- -1.0: The audio effect shows on the left.

@param gain  Volume of the audio effect. The range is [0.0, 100,0]. The default value is 100.0. The smaller the value, the lower the volume of the audio effect

@param publish Whether to publish the specified audio effect to the remote stream:

- True: The audio effect, played locally, is published to the Agora Cloud and the remote users can hear it.
- False: The audio effect, played locally, is not published to the Agora Cloud and the remote users cannot hear it.

@return

- 0: Success.
- <0: Failure.
     *
     */
    int playEffect(int soundId, const char* filePath, int loopCount, double pitch, double pan, int gain, bool publish = false) {
#if defined(_WIN32)
        util::AString path;
        if (!m_parameter->convertPath(filePath, path))
            filePath = path->c_str();
        else if (!filePath)
            filePath = "";
#endif
        return setObject(
            "che.audio.game_play_effect",
            "{\"soundId\":%d,\"filePath\":\"%s\",\"loopCount\":%d, \"pitch\":%lf,\"pan\":%lf,\"gain\":%d, \"send2far\":%d}",
            soundId, filePath, loopCount, pitch, pan, gain, publish);
    }

    /** Stops playing a specific audio effect.

     @param soundId ID of the audio effect. Each audio effect has a unique ID.
     @return

- 0: Success.
- <0: Failure.
     */
    int stopEffect(int soundId) {
        return m_parameter ? m_parameter->setInt(
            "che.audio.game_stop_effect", soundId) : -ERR_NOT_INITIALIZED;
    }

    /** Stops playing all the audio effects.

     @return

- 0: Success.
- <0: Failure.
     */
    int stopAllEffects() {
        return m_parameter ? m_parameter->setBool(
            "che.audio.game_stop_all_effects", true) : -ERR_NOT_INITIALIZED;
    }

    /** Preloads a specific audio effect file (compressed audio file) to the memory.

     @param soundId ID of the audio effect. Each audio effect has a unique ID.
     @param filepath Absolute path of the audio effect file.
     @return

- 0: Success.
- <0: Failure.
     */
    int preloadEffect(int soundId, char* filePath) {
        return setObject(
            "che.audio.game_preload_effect",
            "{\"soundId\":%d,\"filePath\":\"%s\"}",
            soundId, filePath);
    }

    /** Releases a specific preloaded audio effect from the memory.

     @param soundId ID of the audio effect. Each audio effect has a unique ID.
     @return

- 0: Success.
- <0: Failure.
     */
    int unloadEffect(int soundId) {
        return m_parameter ? m_parameter->setInt(
            "che.audio.game_unload_effect", soundId) : -ERR_NOT_INITIALIZED;
    }

    /** Pauses a specific audio effect.

     @param soundId ID of the audio effect. Each audio effect has a unique ID.
     @return

- 0: Success.
- <0: Failure.
     */
    int pauseEffect(int soundId) {
        return m_parameter ? m_parameter->setInt(
            "che.audio.game_pause_effect", soundId) : -ERR_NOT_INITIALIZED;
    }

    /** Pauses all the audio effects.

     @return

- 0: Success.
- <0: Failure.
     */
    int pauseAllEffects() {
        return m_parameter ? m_parameter->setBool(
            "che.audio.game_pause_all_effects", true) : -ERR_NOT_INITIALIZED;
    }

    /** Resumes playing a specific audio effect.

     @param soundId ID of the audio effect. Each audio effect has a unique ID.
     @return

- 0: Success.
- <0: Failure.
     */
    int resumeEffect(int soundId) {
        return m_parameter ? m_parameter->setInt(
            "che.audio.game_resume_effect", soundId) : -ERR_NOT_INITIALIZED;
    }

    /** Resumes playing all the audio effects.
     @return

- 0: Success.
- <0: Failure.
     */
    int resumeAllEffects() {
        return m_parameter ? m_parameter->setBool(
            "che.audio.game_resume_all_effects", true) : -ERR_NOT_INITIALIZED;
    }

    /** Changes the voice pitch of the local speaker.

@param pitch Voice frequency, in the range of [0.5, 2.0]. The default value is 1.0.

@return

- 0: Success.
- <0: Failure.
     */
    int setLocalVoicePitch(double pitch) {
        return m_parameter ? m_parameter->setInt(
            "che.audio.morph.pitch_shift",
            static_cast<int>(pitch * 100)) : -ERR_NOT_INITIALIZED;
    }
    /** Sets the local voice equalization effect.

    @param bandFrequency The band frequency ranging from 0 to 9, representing the respective 10-band center frequencies of the voice effects, including 31, 62, 125, 500, 1k, 2k, 4k, 8k, and 16k Hz.
    @param bandGain  Gain of each band in dB; ranging from -15 to 15.
    */
    int setLocalVoiceEqualization(AUDIO_EQUALIZATION_BAND_FREQUENCY bandFrequency, int bandGain) {
        return setObject(
            "che.audio.morph.equalization",
            "{\"index\":%d,\"gain\":%d}",
            static_cast<int>(bandFrequency), bandGain);
    }
    /**  Sets the local voice reverberation.

    @param reverbKey The reverberation key:  agora::rtc::AUDIO_REVERB_TYPE.
    @param value Value of the reverberation key.
    */
    int setLocalVoiceReverb(AUDIO_REVERB_TYPE reverbKey, int value) {
        return setObject(
            "che.audio.morph.reverb",
            "{\"key\":%d,\"value\":%d}",
            static_cast<int>(reverbKey), value);
    }
    /** Sets the volume of the in-ear monitor.

@param volume Volume of the in-ear monitor, ranging from 0 to 100. The default value is 100.

@return

- 0: Success.
- <0: Failure.
     */
    int setInEarMonitoringVolume(int volume) {
        return m_parameter ? m_parameter->setInt("che.audio.headset.monitoring.parameter", volume) : -ERR_NOT_INITIALIZED;
    }

    /** @deprecated Disables the audio function in the channel. Use IRtcEngine::disableAudio() instead.

@return

- 0: Success.
- <0: Failure.
     */
    int pauseAudio() {
        return m_parameter ? m_parameter->setBool("che.pause.audio", true) : -ERR_NOT_INITIALIZED;
    }

    /**
     * @deprecated Use IRtcEngine::enableAudio() instead.
     * Resumes the audio function in the channel.
     @return

- 0: Success.
- <0: Failure.
     */
    int resumeAudio() {
        return m_parameter ? m_parameter->setBool("che.pause.audio", false) : -ERR_NOT_INITIALIZED;
    }
/** Sets the external audio source.

@param    enabled

- True: Enables the function of using the external audio source.
- False: Disables the function of using the external audio source.

  @param sampleRate	Sampling rate of the external audio source.
  @param channels	 Number of the external audio source channels (two channels maximum).
*/
    int setExternalAudioSource(bool enabled, int sampleRate, int channels) {
        if (enabled)
            return setParameters("{\"che.audio.external_capture\":true,\"che.audio.external_capture.push\":true,\"che.audio.set_capture_raw_audio_format\":{\"sampleRate\":%d,\"channelCnt\":%d,\"mode\":%d}}", sampleRate, channels, RAW_AUDIO_FRAME_OP_MODE_TYPE::RAW_AUDIO_FRAME_OP_MODE_READ_WRITE);
        else
            return setParameters("{\"che.audio.external_capture\":false,\"che.audio.external_capture.push\":false}");
    }

    /** Specifies an SDK output log file.

The log file records all the log data of the SDK’s operation. Ensure that the directory to save the log file exists and is writable.

Note:   The default log file location is at: C:\Users\<user_name>\AppData\Local\Agora\<process_name>.


@param filePath File path of the log file. The string of the log file is in UTF-8 code.
@return

- 0: Success.
- <0: Failure.
    */
    int setLogFile(const char* filePath) {
        if (!m_parameter) return -ERR_NOT_INITIALIZED;
#if defined(_WIN32)
		util::AString path;
		if (!m_parameter->convertPath(filePath, path))
			filePath = path->c_str();
		else if (!filePath)
			filePath = "";
#endif
		return m_parameter->setString("rtc.log_file", filePath);
    }

    /** Sets the output log level of the SDK.

    You can use either one or a combination of the filters. The log level follows the sequence of *OFF*, *CRITICAL*, *ERROR*, *WARNING*, *INFO*, and *DEBUG*. Choose a level, and you can see logs that precede that level.

For example, if you set the log level as *WARNING*, then you can see logs in levels *CRITICAL*, *ERROR* and *WARNING*.


@param filter Levels of the filters: agora::LOG_FILTER_TYPE

@return

- 0: Success.
- <0: Failure.
    */
    int setLogFilter(unsigned int filter) {
        return m_parameter ? m_parameter->setUInt("rtc.log_filter", filter&LOG_FILTER_MASK) : -ERR_NOT_INITIALIZED;
    }

    /** Sets the local video display mode.

    The application can call this method multiple times during a call to change the display mode.
    @param renderMode  agora::rtc::RENDER_MODE_TYPE
    @return

- 0: Success.
- <0: Failure.
    */
    int setLocalRenderMode(RENDER_MODE_TYPE renderMode) {
        return setRemoteRenderMode(0, renderMode);
    }

    /** Sets the remote video display mode.

    The application can call this method multiple times during a call to change the display mode.

    @param renderMode  agora::rtc::RENDER_MODE_TYPE
    @return

- 0: Success.
- <0: Failure.
    */
    int setRemoteRenderMode(uid_t uid, RENDER_MODE_TYPE renderMode) {
        return setObject("che.video.render_mode", "{\"uid\":%u,\"mode\":%d}", uid, renderMode);
    }
/** Sets the local video mirror mode.

Use this method before IRtcEngine::startPreview, or it does not take effect until you reenable startPreview().

@param mirrorMode  agora::rtc::VIDEO_MIRROR_MODE_TYPE
@return

- 0: Success.
- <0: Failure.
*/
    int setLocalVideoMirrorMode(VIDEO_MIRROR_MODE_TYPE mirrorMode) {
        if (!m_parameter) return -ERR_NOT_INITIALIZED;
        const char *value;
        switch (mirrorMode) {
        case VIDEO_MIRROR_MODE_AUTO:
            value = "default";
            break;
        case VIDEO_MIRROR_MODE_ENABLED:
            value = "forceMirror";
            break;
        case VIDEO_MIRROR_MODE_DISABLED:
            value = "disableMirror";
            break;
        default:
            return -ERR_INVALID_ARGUMENT;
        }
        return m_parameter->setString("che.video.localViewMirrorSetting", value);
    }

	int startRecordingService(const char* recordingKey) {
        return m_parameter ? m_parameter->setString("rtc.api.start_recording_service", recordingKey) : -ERR_NOT_INITIALIZED;
    }

    int stopRecordingService(const char* recordingKey) {
        return m_parameter ? m_parameter->setString("rtc.api.stop_recording_service", recordingKey) : -ERR_NOT_INITIALIZED;
    }

    int refreshRecordingServiceStatus() {
        return m_parameter ? m_parameter->setBool("rtc.api.query_recording_service_status", true) : -ERR_NOT_INITIALIZED;
    }
/** Sets the stream mode (live broadcast only) to single- (default) or dual-stream mode.

@param enabled

- True: Dual-stream mode.
- False: Single-stream mode.

*/
    int enableDualStreamMode(bool enabled) {
        return setParameters("{\"rtc.dual_stream_mode\":%s,\"che.video.enableLowBitRateStream\":%d}", enabled ? "true" : "false", enabled ? 1 : 0);
    }
/** Sets the audio recording format of the agora::media::IAudioFrameObserver::onRecordAudioFrame() callback

@param sampleRate Sampling rate in the callback data returned by onRecordAudioFrame(), which can set be as 8000, 16000, 32000, 44100, or 48000.   .
@param channel Number of channels in the callback data returned by onRecordAudioFrame(), which can be set as 1 or 2:

- 1: Mono
- 2: Dual-track

@param mode Use mode of the onRecordAudioFrame() callback: agora::rtc::RAW_AUDIO_FRAME_OP_MODE_TYPE.
@param samplesPerCall Sampling points in the called data returned in onRecordAudioFrame(). For example, it is usually set as 1024 for stream pushing.

*/
    int setRecordingAudioFrameParameters(int sampleRate, int channel, RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall) {
        return setObject("che.audio.set_capture_raw_audio_format", "{\"sampleRate\":%d,\"channelCnt\":%d,\"mode\":%d,\"samplesPerCall\":%d}", sampleRate, channel, mode, samplesPerCall);
    }
    /** Sets the audio playback format of the agora::media::IAudioFrameObserver::onPlaybackAudioFrame() callback.

    @param sampleRate Sampling rate in the callback data returned by onPlaybackAudioFrame(), which can set be as 8000, 16000, 32000, 44100, or 48000.
    @param channel Number of channels in the callback data returned by onPlaybackAudioFrame(), which can be set as 1 or 2:

    - 1: Mono
    - 2: Dual-track

    @param mode Use mode of the onPlaybackAudioFrame() callback: agora::rtc::RAW_AUDIO_FRAME_OP_MODE_TYPE.
    @param samplesPerCall Sampling points in the called data returned in onPlaybackAudioFrame(). For example, it is usually set as 1024 for stream pushing.

    */
    int setPlaybackAudioFrameParameters(int sampleRate, int channel, RAW_AUDIO_FRAME_OP_MODE_TYPE mode, int samplesPerCall) {
        return setObject("che.audio.set_render_raw_audio_format", "{\"sampleRate\":%d,\"channelCnt\":%d,\"mode\":%d,\"samplesPerCall\":%d}", sampleRate, channel, mode, samplesPerCall);
    }
    /** Sets the mixed audio format of the agora::media::IAudioFrameObserver::onMixedAudioFrame() callback.

        @param sampleRate Sampling rate in the callback data returned by onMixedAudioFrame(), which can set be as 8000, 16000, 32000, 44100, or 48000.
        @param samplesPerCall Sampling points in the called data returned in onMixedAudioFrame().  For example, it is usually set as 1024 for stream pushing.

    */
    int setMixedAudioFrameParameters(int sampleRate, int samplesPerCall) {
        return setObject("che.audio.set_mixed_raw_audio_format", "{\"sampleRate\":%d,\"samplesPerCall\":%d}", sampleRate, samplesPerCall);
    }

    int muteRecordingSignal(bool enabled) {
        return setParameters("{\"che.audio.record.signal.mute\":%s}", enabled ? "true" : "false");
    }
/** Adjusts the recording volume.

@param volume Recording volume, ranges from 0 to 400:

- 0: Mute.
- 100: Original volume.
- 400: (Maximum) Four times the original volume with signal clipping protection.

@return

- 0: Success.
- <0: Failure.
*/
    int adjustRecordingSignalVolume(int volume) {//[0, 400]: e.g. 50~0.5x 100~1x 400~4x
        if (volume < 0)
            volume = 0;
        else if (volume > 400)
            volume = 400;
        return m_parameter ? m_parameter->setInt("che.audio.record.signal.volume", volume) : -ERR_NOT_INITIALIZED;
    }
    /** Adjusts the playback volume.

@param volume Playback volume, ranges from 0 to 400:

- 0: Mute.
- 100: Original volume.
- 400: (Maximum) Four times the original volume with signal clipping protection.

@return

- 0: Success.
- <0: Failure.
    */
    int adjustPlaybackSignalVolume(int volume) {//[0, 400]
        if (volume < 0)
            volume = 0;
        else if (volume > 400)
            volume = 400;
        return m_parameter ? m_parameter->setInt("che.audio.playout.signal.volume", volume) : -ERR_NOT_INITIALIZED;
    }
    /**
@deprecated Agora does not recommend using this method.

Sets the high-quality audio preferences. Call this method and set all the three modes before joining a channel.

Do not call this method again after joining a channel.

@param fullband Full-band codec (48-kHz sampling rate), not compatible with versions before v1.7.4:

- True: Enables full-band codec.
- False: Disables full-band codec.

@param  stereo Stereo codec, not compatible with versions before v1.7.4:

- True: Enables the stereo codec.
- False: Disables the stereo codec.

@param fullBitrate  High bitrate. Recommended in voice-only mode:

- True: Enables high-bitrate mode.
- False: Disables high-bitrate mode.

@return

- 0: Success.
- <0: Failure.
     */
    int setHighQualityAudioParameters(bool fullband, bool stereo, bool fullBitrate) {
        return setObject("che.audio.codec.hq", "{\"fullband\":%s,\"stereo\":%s,\"fullBitrate\":%s}", fullband ? "true" : "false", stereo ? "true" : "false", fullBitrate ? "true" : "false");
    }
    /** Enables interoperability with the Agora Web SDK.

    @param enabled

    - True: Enables interoperability with the Agora Web SDK.
    - False: Disables interoperability with the Agora Web SDK.
    */
    int enableWebSdkInteroperability(bool enabled) {//enable interoperability with zero-plugin web sdk
        return setParameters("{\"rtc.video.web_h264_interop_enable\":%s,\"che.video.web_h264_interop_enable\":%s}", enabled ? "true" : "false", enabled ? "true" : "false");
    }
    //only for live broadcast
    /** Sets the high-quality video preferences.
@param preferFrameRateOverImageQuality

- True: Frame rate over image quality
- False: Image quality over frame rate (default)

    */
    int setVideoQualityParameters(bool preferFrameRateOverImageQuality) {
        return setParameters("{\"rtc.video.prefer_frame_rate\":%s,\"che.video.prefer_frame_rate\":%s}", preferFrameRateOverImageQuality ? "true" : "false", preferFrameRateOverImageQuality ? "true" : "false");
    }

    /** Sets the local publish stream fallback option according to the network conditions.

If you set *option* as agora::rtc::STREAM_FALLBACK_OPTION_AUDIO_ONLY, the SDK will:

- Disable the upstream video when the network cannot support both video and audio.
- Reenable the video when the network condition improves.

When the local publish stream falls back to audio-only or when the audio stream switches back to the video, the IRtcEngineEventHandler::onLocalPublishFallbackToAudioOnly callback will be triggered.

Note: Agora does not recommend using this method for CDN streaming, because the remote CDN user will notice a lag when the local publish stream falls back to audio-only.

     @param  option  agora::rtc::STREAM_FALLBACK_OPTIONS
     @return

- 0: Success.
- <0: Failure.
     */
    int setLocalPublishFallbackOption(STREAM_FALLBACK_OPTIONS option) {
        return m_parameter ? m_parameter->setInt("rtc.local_publish_fallback_option", option) : -ERR_NOT_INITIALIZED;
    }

    /** Sets the remote subscribe stream fallback option according to the network conditions.

If you use this API and set *option* as agora::rtc::STREAM_FALLBACK_OPTION_AUDIO_ONLY, the SDK will automatically switch the video from a high-stream to a low-stream, or turn off the video when the downlink network condition cannot support both audio and video to guarantee the quality of the audio. In the meantime, the SDK keeps track of the network quality and restores the video stream when the network conditions improve.
Once the local publish stream falls back to audio only, or the audio stream switches back to the video stream, the IRtcEngineEventHandler::onRemoteSubscribeFallbackToAudioOnly callback will be triggered.

     @param  option  agora::rtc::STREAM_FALLBACK_OPTIONS
     @return

- 0: Success.
- <0: Failure.
     */
    int setRemoteSubscribeFallbackOption(STREAM_FALLBACK_OPTIONS option) {
        return m_parameter ? m_parameter->setInt("rtc.remote_subscribe_fallback_option", option) : -ERR_NOT_INITIALIZED;
    }

    /** Enables loopback recording.

@param enabled

- True: Enables loopback recording.
- False: Disables loopback recording.
@param deviceName Device name of the microphone.
@return

- 0: Success.
- <0: Failure.
     */
    int enableLoopbackRecording(bool enabled, const char* deviceName = NULL) {
        if (!deviceName) {
            return setParameters("{\"che.audio.loopback.recording\":%s}", enabled ? "true" : "false");
        }
        else {
            return setParameters("{\"che.audio.loopback.deviceName\":\"%s\",\"che.audio.loopback.recording\":%s}", deviceName, enabled ? "true" : "false");
        }
    }

protected:
    AParameter& parameter() {
        return m_parameter;
    }
    int setParameters(const char* format, ...) {
        char buf[512];
        va_list args;
        va_start(args, format);
        vsnprintf(buf, sizeof(buf)-1, format, args);
        va_end(args);
        return m_parameter ? m_parameter->setParameters(buf) : -ERR_NOT_INITIALIZED;
    }
    int setObject(const char* key, const char* format, ...) {
        char buf[512];
        va_list args;
        va_start(args, format);
        vsnprintf(buf, sizeof(buf)-1, format, args);
        va_end(args);
        return m_parameter ? m_parameter->setObject(key, buf) : -ERR_NOT_INITIALIZED;
    }
    int stopAllRemoteVideo() {
        return m_parameter ? m_parameter->setBool("che.video.peer.stop_render", true) : -ERR_NOT_INITIALIZED;
    }
private:
    AParameter m_parameter;
};

} //namespace rtc
} // namespace agora


/** Gets the SDK version number.

@param build Build number of Agora the SDK.
* @return String of the SDK version.
*/
#define getAgoraRtcEngineVersion getAgoraSdkVersion

/** Creates the RTC engine object and returns the pointer.

* @return Pointer of the RTC engine object.
*/
AGORA_API agora::rtc::IRtcEngine* AGORA_CALL createAgoraRtcEngine();

/** Creates the RTC engine object and returns the pointer.

 @param err Error Code.
* @return Description of the Error Code: agora::ERROR_CODE_TYPE
*/
#define getAgoraRtcEngineErrorDescription getAgoraSdkErrorDescription
#define setAgoraRtcEngineExternalSymbolLoader setAgoraSdkExternalSymbolLoader

#endif
