package com.example.xuhaitian.musician.android_student;

import android.Manifest;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.graphics.Matrix;
import android.graphics.Path;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.media.ExifInterface;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.provider.MediaStore;
import android.support.annotation.NonNull;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.SurfaceView;
import android.view.View;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;

import com.avos.avoscloud.AVException;
import com.avos.avoscloud.AVFile;
import com.avos.avoscloud.SaveCallback;
import com.avos.avoscloud.im.v2.AVIMClient;
import com.avos.avoscloud.im.v2.AVIMConversation;
import com.avos.avoscloud.im.v2.AVIMException;
import com.avos.avoscloud.im.v2.AVIMMessage;
import com.avos.avoscloud.im.v2.AVIMMessageHandler;
import com.avos.avoscloud.im.v2.AVIMMessageManager;
import com.avos.avoscloud.im.v2.callback.AVIMClientCallback;
import com.avos.avoscloud.im.v2.callback.AVIMConversationCallback;
import com.avos.avoscloud.im.v2.callback.AVIMConversationCreatedCallback;
import com.avos.avoscloud.im.v2.messages.AVIMTextMessage;
import com.example.xuhaitian.musician.android_student.CustomView.Draw;
import com.example.xuhaitian.musician.android_student.common.SysExitUtil;
import com.netease.nimlib.sdk.Observer;
import com.netease.nimlib.sdk.rts.RTSManager;
import com.netease.nimlib.sdk.rts.model.RTSCommonEvent;
import com.netease.nimlib.sdk.rts.model.RTSTunData;
import com.netease.nimlib.sdk.rts.constant.RTSTunnelType;
import com.netease.nimlib.sdk.rts.RTSCallback;
import com.netease.nimlib.sdk.rts.model.RTSData;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Date;
import java.util.List;

import io.agora.rtc.Constants;
import io.agora.rtc.IRtcEngineEventHandler;
import io.agora.rtc.RtcEngine;
import io.agora.rtc.video.VideoCanvas;

import static android.app.Activity.RESULT_OK;
import static android.view.View.GONE;
import static io.agora.rtc.Constants.AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO;
import static io.agora.rtc.Constants.AUDIO_SCENARIO_SHOWROOM;

public class AudioTeachActivity extends AppCompatActivity {
    public static final int GET_DATA_SUCCESS = 1;
    public static final int NETWORK_ERROR = 2;
    public static final int SERVER_ERROR = 3;
    private static final int PERMISSION_REQ_ID_RECORD_AUDIO = 22;
    private static final int PERMISSION_REQ_ID_CAMERA = PERMISSION_REQ_ID_RECORD_AUDIO + 1;
    private static final String LOG_TAG = "LOG_TAG";
    private static final int IMAGE_REQUEST_CODE = 1001;
    RtcEngine mRtcEngine = null;
    Draw main_draw;
    View drawBackgroud;
    Draw peer_draw;
    String teacher_name;
    String Channel_name = "";
    MyLeanCloudApp myApp;
    JSONObject mCourseInfo;
    Boolean isJoinInRoom = false;
    private CustomMessageHandler customMessageHandler;
    RelativeLayout wholeView;
    TextView teacher_pause;

    List<String> mPeerDataList = new ArrayList<String>();
    List<String> mDrawDataList = new ArrayList<String>();
    public String mImagePath = "";
    private IRtcEngineEventHandler mRtcEventHandler = new IRtcEngineEventHandler() {
        @Override
        public void onJoinChannelSuccess(String channel, int uid, int elapsed) {
            super.onJoinChannelSuccess(channel, uid, elapsed);
            Log.e(LOG_TAG, uid + ":onJoinChannelSuccess" + Channel_name);
        }

        @Override
        public void onFirstRemoteVideoDecoded(final int uid, int width, int height, int elapsed) { // Tutorial Step 5
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    setupRemoteVideo(uid);
//                    setupLocalVideo(uid);
                    Log.e(LOG_TAG, uid + ":onFirstRemoteVideoDecoded");
                }
            });
        }
        @Override
        public void onUserEnableVideo(int uid, boolean enabled){
            final boolean video =enabled;
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    if ( true==video ){
                        open_Video();
                    }
                    else {
                        close_Video();
                    }

                }
            });


        }
        public void onUserOffline(int uid, int reason)
        {
            isJoinInRoom = false;
            final int status = reason;
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    Log.e("REASON", "" + status);
                    if (status == 0) {
                        close_Video();
                    }
                }
            });
        }
        public void onUserJoined( int uid, int elapsed )
        {
            isJoinInRoom = true;
        }
    };
    public void addPeerData(String data)
    {
        mPeerDataList.add(data);
    }
    public void addDrawData(String data)
    {
        mDrawDataList.add(data);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_audio_teach);
        SysExitUtil.activityList.add(AudioTeachActivity.this);
        initActionBar();
        wholeView = (RelativeLayout)findViewById(R.id.wholeView);
        wholeView.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                wholeView.setBackgroundColor(Color.WHITE);
                teacher_pause.setVisibility(GONE);
                return true;
            }
        });
        teacher_pause = (TextView)findViewById(R.id.teacher_pause);
        teacher_pause.setVisibility(GONE);


        wholeView.setBackgroundColor(Color.WHITE);
        myApp = (MyLeanCloudApp) getApplication();
        myApp.setAudioTeachActivity(AudioTeachActivity.this);
        main_draw = findViewById(R.id.main_draw);
        peer_draw = findViewById(R.id.peer_draw);

        main_draw.setContext(AudioTeachActivity.this);
        peer_draw.setContext(AudioTeachActivity.this);

        //接受传过来的课程信息
        Intent intent = getIntent();
        String teacher_info = intent.getStringExtra("teacher_info");
        Log.e("teacher_info", "" + teacher_info);
        try {
            mCourseInfo = new JSONObject(teacher_info);
        } catch (JSONException error) {
            Log.e("error", "错误信息" + error);
        }
        try {
            Channel_name = mCourseInfo.getString("student_id");
            teacher_name = mCourseInfo.getString("teacher_name");
            Log.e("id", "" + teacher_name);

        } catch (JSONException e) {
            Log.e("error", "错误信息" + e);
        }
        drawBackgroud = findViewById(R.id.drawBackgroud);
        if (mRtcEngine == null && checkSelfPermission(Manifest.permission.RECORD_AUDIO, PERMISSION_REQ_ID_RECORD_AUDIO)) {

            initAgoraEngineAndJoinChannel(9999);
            mRtcEngine.enableVideo();
            mRtcEngine.setEnableSpeakerphone(true);
            FrameLayout local_video_view_container = (FrameLayout) findViewById(R.id.local_video_view_container);
            local_video_view_container.setVisibility(View.GONE);
            FrameLayout remote_video_view_container = (FrameLayout) findViewById(R.id.remote_video_view_container);
            remote_video_view_container.setVisibility(View.GONE);
            sendMessageToTeacher("studentOnline", "studentOnline");
            //注册默认的消息处理逻辑
            AVIMMessageManager.registerDefaultMessageHandler(new AudioTeachActivity.CustomMessageHandler());
            customMessageHandler = new CustomMessageHandler();
            customMessageHandler.setIsOpen(true);
            AVIMMessageManager.registerMessageHandler(AVIMMessage.class, customMessageHandler);
        }
        Button handup_button = (Button) findViewById(R.id.hands_up_button);
        handup_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                sendMessageToTeacher("HandUp","HandUp");
                Toast.makeText(AudioTeachActivity.this, "举手成功", Toast.LENGTH_SHORT).show();

            }
        });

        Button openMusicBtn = (Button)findViewById(R.id.open_whiteboard_button);
        openMusicBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                openMusicWhiteBoard();
            }
        });

        Button close_music = (Button)findViewById(R.id.close_music);
        close_music.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                closeMusicTeach();
            }
        });
    }
    public void closeMusicTeach()
    {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                WhiteBoardManager.close(main_draw.sessionID,AudioTeachActivity.this);
                Button close_music = (Button)findViewById(R.id.close_music);
                close_music.setVisibility(GONE);
                drawBackgroud.setVisibility(View.GONE);
                drawBackgroud.setBackgroundResource(0);
                main_draw.setVisibility(View.GONE);
                peer_draw.setVisibility(View.GONE);
                main_draw.Clear();
                peer_draw.Clear();
                showMusicPicture();
                TextView textview = (TextView) findViewById(R.id.who_be_teach);
                textview.setText("正在和"+teacher_name +"语音教学");
            }
        });
    }


    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {

        super.onActivityResult(requestCode, resultCode, data);
        Log.e(":",requestCode +":"+resultCode+":" +data);
        //在相册里面选择好相片之后调回到现在的这个activity中
        switch (requestCode) {
            case IMAGE_REQUEST_CODE://这里的requestCode是我自己设置的，就是确定返回到那个Activity的标志
                if (resultCode == RESULT_OK) {//resultcode是setResult里面设置的code值
                    try {
                        Uri selectedImage = data.getData(); //获取系统返回的照片的Uri
                        String[] filePathColumn = {MediaStore.Images.Media.DATA};
                        Cursor cursor = getContentResolver().query(selectedImage,
                                filePathColumn, null, null, null);//从系统表中查询指定Uri对应的照片
                        cursor.moveToFirst();
                        int columnIndex = cursor.getColumnIndex(filePathColumn[0]);
                        String path = cursor.getString(columnIndex);  //获取照片路径
                        cursor.close();
                        showMusicWhiteBoard(path);
                    } catch (Exception e) {
                        // TODO Auto-generatedcatch block
                        e.printStackTrace();
                    }
                }
                break;
        }
    }
    public void showMusicWhiteBoard(final String path){
        List<RTSTunnelType> types = new ArrayList<>(1);
        types.add(RTSTunnelType.DATA);
        String teacherID = "";
        try {
            teacherID = mCourseInfo.getString("teacherID");
        }
        catch (JSONException e){

        }
        final String eastAccount = teacherID;
        String sessionId = RTSManager.getInstance().start(eastAccount, types, null, null, new RTSCallback<RTSData>() {
            @Override
            public void onSuccess(RTSData rtsData) {
//                Toast.makeText(AudioTeachActivity.this, "发起白板会话成功", Toast.LENGTH_SHORT).show();
                //注册主叫方收到被叫相应的回调
                WhiteBoardManager.registerCalleeAckNotification(rtsData.getLocalSessionId(),true,eastAccount,AudioTeachActivity.this);
                Button close_music = (Button)findViewById(R.id.close_music);
                close_music.setVisibility(View.VISIBLE);
                uploadMusicImage(path);
            }

            @Override
            public void onFailed(int code) {
                Toast.makeText(AudioTeachActivity.this, "发起白板会话失败", Toast.LENGTH_SHORT).show();
            }

            @Override
            public void onException(Throwable exception) {
//                Toast.makeText(AudioTeachActivity.this, "发起白板会话异常", Toast.LENGTH_SHORT).show();
            }
        });
    }

    public byte[] Bitmap2Bytes(Bitmap bm){
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        bm.compress(Bitmap.CompressFormat.PNG, 100, baos);
        return baos.toByteArray();
    }

    /**
     * 读取图片属性：旋转的角度
     * @param path 图片绝对路径
     * @return degree旋转的角度
     */
    public static int readPictureDegree(String path) {
        int degree  = 0;
        try {
            ExifInterface exifInterface = new ExifInterface(path);
            int orientation = exifInterface.getAttributeInt(ExifInterface.TAG_ORIENTATION, ExifInterface.ORIENTATION_NORMAL);
            switch (orientation) {
                case ExifInterface.ORIENTATION_ROTATE_90:
                    degree = 90;
                    break;
                case ExifInterface.ORIENTATION_ROTATE_180:
                    degree = 180;
                    break;
                case ExifInterface.ORIENTATION_ROTATE_270:
                    degree = 270;
                    break;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return degree;
    }

    /**
     * 旋转图片
     * @param angle
     * @param bitmap
     * @return Bitmap
     */
    public static Bitmap rotaingImageView(int angle , Bitmap bitmap) {
        //旋转图片 动作
        Matrix matrix = new Matrix();;
        matrix.postRotate(angle);
        // 创建新的图片
        Bitmap resizedBitmap = Bitmap.createBitmap(bitmap, 0, 0,
                bitmap.getWidth(), bitmap.getHeight(), matrix, true);
        return resizedBitmap;
    }

    private void uploadMusicImage(final String path){
        new Thread() {
            @Override
            public void run() {
                Bitmap bitmap = BitmapFactory.decodeFile(path);
                byte[] imageBytes = compressImage(rotaingImageView(readPictureDegree(path),bitmap),500);
                Log.e("count",imageBytes.length+"");
                final AVFile file = new AVFile("LeanCloud.png",imageBytes);
                file.saveInBackground(new SaveCallback() {
                    @Override
                    public void done(AVException e) {
                        if (e == null)
                        {
                            String sendImageData = "0:"+file.getUrl()+":"+path;
                            WhiteBoardManager.sendToRemote(main_draw.sessionID,main_draw.toAccount,sendImageData);
                            Log.e("uploadURL", sendImageData);//返回一个唯一的 Url 地址
                            Bitmap bitmap = BitmapFactory.decodeFile(path);
                            drawBackgroud.setBackground(new BitmapDrawable(getResources(), bitmap));
                            //打开白板
                            drawBackgroud.setVisibility(View.VISIBLE);
                            main_draw.setVisibility(View.VISIBLE);
                            peer_draw.setVisibility(View.VISIBLE);
                            hideMusicPicture();

                            if (mImagePath.equals(path))
                            {
                                for (int m = 0; m < mDrawDataList.size(); m ++)
                                {
                                    main_draw.dataPaint(mDrawDataList.get(m));
                                }
                                for (int n = 0; n < mPeerDataList.size(); n ++)
                                {
                                    peer_draw.dataPaint(mPeerDataList.get(n));
                                }
                            }else {
                                mImagePath = path;
                                mDrawDataList.clear();
                                mPeerDataList.clear();
                            }
                        }

                    }
                });

            }
        }.start();
    }

    public void clearMusicPicture()
    {
        main_draw.Clear();
        peer_draw.Clear();
        mDrawDataList.clear();
        mPeerDataList.clear();
    }

    public void openMusicWhiteBoard()
    {
        Log.e("Tag","打开白板");
        if (isJoinInRoom == true) {

            if (ActivityCompat.checkSelfPermission(AudioTeachActivity.this, Manifest.permission.WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED) {
                ActivityCompat.requestPermissions(AudioTeachActivity.this, new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE},1);
            }
            else
            {
                Intent intent = new Intent(
                        Intent.ACTION_PICK,
                        android.provider.MediaStore.Images.Media.EXTERNAL_CONTENT_URI);
                startActivityForResult(intent, IMAGE_REQUEST_CODE);
            }
        }
        else {
            Toast.makeText(AudioTeachActivity.this,"打开乐谱失败，请确认老师是否接受你的乐谱教学请求...",Toast.LENGTH_SHORT).show();
        }
    }

    public void startKeepUpBoard(String sessionID, String toAccount) {
        main_draw.sessionID = sessionID;     //参数传递
        main_draw.toAccount = toAccount;     //参数传递
        main_draw.setVisibility(View.VISIBLE);
        peer_draw.sessionID = sessionID;
        peer_draw.toAccount = toAccount;
        peer_draw.setVisibility(View.VISIBLE);
        drawBackgroud.setVisibility(View.VISIBLE);


        //注册收到数据的监听
        WhiteBoardManager.registerIncomingData(sessionID, true, main_draw, AudioTeachActivity.this);
//        WhiteBoardManager.registerRTSCloseObserver(sessionID, true, AudioTeachActivity.this);
        //隐藏本地视频窗口
        FrameLayout local_container = (FrameLayout) findViewById(R.id.local_video_view_container);
        local_container.setVisibility(GONE);
        TextView textview = (TextView) findViewById(R.id.who_be_teach);
        textview.setText("正在和"+teacher_name +"乐谱教学");
    }



    //初始化进入房间
    private void initAgoraEngineAndJoinChannel(int uid) {
        initializeAgoraEngine();     // Tutorial Step 1
        mRtcEngine.setAudioProfile(AUDIO_PROFILE_MUSIC_HIGH_QUALITY_STEREO,AUDIO_SCENARIO_SHOWROOM);
        setupVideoProfile();
        setupLocalVideo(uid);
        joinChannel(uid);
    }

    private void initializeAgoraEngine() {
        try {
            mRtcEngine = RtcEngine.create(getBaseContext(), getString(R.string.agora_app_id), mRtcEventHandler);
        } catch (Exception e) {
            Log.e(LOG_TAG, Log.getStackTraceString(e));

            throw new RuntimeException("NEED TO check rtc sdk init fatal error\n" + Log.getStackTraceString(e));
        }
    }

    // Tutorial Step 2
    private void setupVideoProfile() {
        mRtcEngine.enableVideo();
        mRtcEngine.setVideoProfile(Constants.VIDEO_PROFILE_360P, false);
    }


    //设置导航栏
    public void initActionBar() {
        android.support.v7.app.ActionBar actionBar = getSupportActionBar();
        if (actionBar != null) {
            actionBar.setTitle("");
            actionBar.setDisplayShowHomeEnabled(false);
            actionBar.setDisplayShowCustomEnabled(true);
            LayoutInflater inflator = (LayoutInflater) this
                    .getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            View v = inflator.inflate(R.layout.actionbar_audio_teach, new LinearLayout(AudioTeachActivity.this), false);
            android.support.v7.app.ActionBar.LayoutParams layout = new android.support.v7.app.ActionBar.LayoutParams(
                    android.support.v7.app.ActionBar.LayoutParams.MATCH_PARENT, android.support.v7.app.ActionBar.LayoutParams.MATCH_PARENT);
            actionBar.setCustomView(v, layout);
            Toolbar parent = (Toolbar) v.getParent();
            parent.setContentInsetsAbsolute(0, 0);
        }
        //顶部返回按键
        Button back_button = (Button) findViewById(R.id.back_button);
        back_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
//                if (main_draw.getVisibility() == GONE) {
                final FrameLayout remote_video = findViewById(R.id.remote_video_view_container);
                if (remote_video.getVisibility() == GONE) {
                    sendMessageToTeacher("studentOffline","studentOffline");
                    leaveChannel();
                    finish();
                    startActivity(new Intent(AudioTeachActivity.this, MainActivity.class));
                } else {
                    Toast.makeText(AudioTeachActivity.this, "现在正在与学生教学", Toast.LENGTH_SHORT).show();
                }
//                } else {
//                    Toast.makeText(AudioTeachActivity.this, "现在正在与学生教学", Toast.LENGTH_SHORT).show();
//                }

            }
        });
        TextView actionBarTitle = (TextView) findViewById(R.id.action_bar_title);
        actionBarTitle.setText("学生线上教室");
    }

    private void joinChannel(int uid) {
        mRtcEngine.joinChannel(null, "" + Channel_name, null, uid); // if you do not specify the uid, we will generate the uid for you
    }

    private void leaveChannel() {
        mRtcEngine.leaveChannel();
    }

    public boolean checkSelfPermission(String permission, int requestCode) {
        Log.e(LOG_TAG, "checkSelfPermission " + permission + " " + requestCode);
        if (ContextCompat.checkSelfPermission(this,
                permission)
                != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this,
                    new String[]{permission},
                    requestCode);
            return false;
        }
        return true;
    }

    private void setupRemoteVideo(int uid) {
        FrameLayout container = (FrameLayout) findViewById(R.id.remote_video_view_container);
        if (container.getChildCount() >= 1) {
            container.removeAllViews();
        }
        container.setVisibility(View.VISIBLE);
        SurfaceView surfaceView = RtcEngine.CreateRendererView(getBaseContext());
        container.addView(surfaceView);
        mRtcEngine.setupRemoteVideo(new VideoCanvas(surfaceView, VideoCanvas.RENDER_MODE_HIDDEN, uid));
        surfaceView.setTag(uid); // for mark purpose
    }

    private void close_Video() {
        if (checkSelfPermission(Manifest.permission.CAMERA, PERMISSION_REQ_ID_CAMERA)) {
            showMusicPicture();
            mRtcEngine.disableVideo();
            FrameLayout container_local = (FrameLayout) findViewById(R.id.local_video_view_container);
            container_local.setVisibility(View.GONE);
            FrameLayout container_remote = (FrameLayout) findViewById(R.id.remote_video_view_container);
            container_remote.setVisibility(View.GONE);
            Button handup_button = (Button) findViewById(R.id.hands_up_button);
            handup_button.setVisibility(View.VISIBLE);
            Button openMusicBtn = (Button)findViewById(R.id.open_whiteboard_button);
            openMusicBtn.setVisibility(View.VISIBLE);
        }
    }
    private void open_Video() {
        if (checkSelfPermission(Manifest.permission.CAMERA, PERMISSION_REQ_ID_CAMERA)) {
            hideMusicPicture();
            mRtcEngine.enableVideo();
            FrameLayout container_local = (FrameLayout) findViewById(R.id.local_video_view_container);
            container_local.setVisibility(View.VISIBLE);
            FrameLayout container_remote = (FrameLayout) findViewById(R.id.remote_video_view_container);
            container_remote.setVisibility(View.VISIBLE);
            Button handup_button = (Button) findViewById(R.id.hands_up_button);
            handup_button.setVisibility(View.GONE);
            Button openMusicBtn = (Button)findViewById(R.id.open_whiteboard_button);
            openMusicBtn.setVisibility(GONE);
        }
    }
    private void setupLocalVideo(int uid) {
        FrameLayout container = (FrameLayout) findViewById(R.id.local_video_view_container);
        container.setVisibility(View.VISIBLE);
        SurfaceView surfaceView = RtcEngine.CreateRendererView(getBaseContext());
        surfaceView.setZOrderMediaOverlay(true);
        container.addView(surfaceView);
        mRtcEngine.setupLocalVideo(new VideoCanvas(surfaceView, VideoCanvas.RENDER_MODE_HIDDEN, uid));
        surfaceView.setTag(uid); // for mark purpose
    }

    private void hideMusicPicture() {
        View MusicPicture = (View) findViewById(R.id.music_picture);
        MusicPicture.setVisibility(GONE);
    }

    private void showMusicPicture() {
        View MusicPicture = (View) findViewById(R.id.music_picture);
        MusicPicture.setVisibility(View.VISIBLE);
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        switch (requestCode) {//根据请求码判断是哪一次申请的权限
            case PERMISSION_REQ_ID_RECORD_AUDIO:
                if (grantResults.length > 0) {//grantResults 数组中存放的是授权结果
                    if (grantResults[0] == PackageManager.PERMISSION_GRANTED) {//同意授权
                        //授权后做一些你想做的事情，即原来不需要动态授权时做的操作
                        checkSelfPermission(Manifest.permission.CAMERA, PERMISSION_REQ_ID_CAMERA);
                    } else {//用户拒绝授权
                        //可以简单提示用户
                        Toast.makeText(AudioTeachActivity.this, "没有授权继续操作", Toast.LENGTH_SHORT).show();
                    }
                }
                break;
            case PERMISSION_REQ_ID_CAMERA:
                if (grantResults.length > 0) {//grantResults 数组中存放的是授权结果
                    if (grantResults[0] == PackageManager.PERMISSION_GRANTED) {//同意授权
                        //授权后做一些你想做的事情，即原来不需要动态授权时做的操作
                        initAgoraEngineAndJoinChannel(9999);
                        mRtcEngine.disableVideo();
                        FrameLayout container = (FrameLayout) findViewById(R.id.local_video_view_container);
                        container.setVisibility(GONE);
                        //注册默认的消息处理逻辑
                        customMessageHandler = new CustomMessageHandler();
                        customMessageHandler.setIsOpen(true);
                        AVIMMessageManager.registerMessageHandler(AVIMMessage.class, customMessageHandler);
//                        //通知学生老师上线
                        sendMessageToTeacher("studentOnline", "studentOnline");
                    } else {//用户拒绝授权
                        //可以简单提示用户
                        Toast.makeText(AudioTeachActivity.this, "没有授权继续操作", Toast.LENGTH_SHORT).show();
                    }
                }
                break;
            default:
                super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        }
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        final FrameLayout local_video = findViewById(R.id.local_video_view_container);
        /* 返回键 */
        if (keyCode == KeyEvent.KEYCODE_BACK) {
                if (local_video.getVisibility() == GONE) {
                    sendMessageToTeacher("studentOffline","studentOffline");
                    this.finish();
                    startActivity(new Intent(AudioTeachActivity.this, MainActivity.class));
                } else {
                    Toast.makeText(AudioTeachActivity.this, "现在正在与老师视频", Toast.LENGTH_SHORT).show();
                    return false;
                }
        }
        return super.onKeyDown(keyCode,event);
    }

    @Override
    protected void onDestroy() {
        leaveChannel();
        mRtcEngine.destroy();
        sendMessageToTeacher("通知老师学生下线","学生下线");
        customMessageHandler.setIsOpen(false);
        AVIMMessageManager.unregisterMessageHandler(AVIMMessage.class, customMessageHandler);
        super.onDestroy();
    }

    public class CustomMessageHandler extends AVIMMessageHandler {
        //即时通讯
        //接收到消息后的处理逻辑

        public Boolean mIsOpen;

        public void setIsOpen(Boolean isOpen) {
            mIsOpen = isOpen;
        }
            @Override
            public void onMessage(AVIMMessage message, AVIMConversation conversation, AVIMClient client) {
                if (mIsOpen == false) {
                    Log.e("Tom & Jerry", " 失败");
                    return;
                }
                if (message instanceof AVIMTextMessage) {
                    TextView textview = (TextView) findViewById(R.id.who_be_teach);

                    Log.e("Tom & Jerry", "消息接听:" + ((AVIMTextMessage) message).getText());
                    if (((AVIMTextMessage) message).getText().equals("老师上线"))
                    {
                        Log.e("1", " 老师上线");
                        textview.setText("正在和"+teacher_name +"语音教学");
                        sendMessageToTeacher("成功收到老师上线通知","成功收到老师上线通知");

                    }
                    else if(((AVIMTextMessage) message).getText().equals("收到学生上线通知"))
                    {
                        Log.e("2", "收到学生上线通知");
                        textview.setText("正在和"+teacher_name +"语音教学");

                    }
                    else if(((AVIMTextMessage) message).getText().equals("老师下线"))
                    {
                        textview.setText("老师下线");
                    }
                    else if (((AVIMTextMessage) message).getText().equals("pausePlaying")){
                        wholeView.setBackgroundColor(Color.rgb(223,137,49));
                        teacher_pause.setVisibility(View.VISIBLE);
                    }

                }
            }

        public void onMessageReceipt(AVIMMessage message, AVIMConversation conversation, AVIMClient client) {

        }
    }
    //发送上线通知给老师
    public void sendMessageToTeacher(final String msgName, final String msgtext) {
        try {
            List<String> list = new ArrayList();
            list.add(mCourseInfo.getString("teacherID"));
            myApp.client.createConversation(list, msgName, null,
                    new AVIMConversationCreatedCallback() {
                        @Override
                        public void done(AVIMConversation conversation, AVIMException e) {
                            if (e == null) {
                                AVIMTextMessage msg = new AVIMTextMessage();
                                msg.setText(msgtext);
                                // 发送消息
                                conversation.sendMessage(msg, new AVIMConversationCallback() {
                                    @Override
                                    public void done(AVIMException e) {
                                        if (e == null) {
                                            Log.e(msgtext, ""+msgName);
                                        }
                                    }
                                });
                            }
                        }
                    });
        } catch (JSONException e) {

        }
    }

    public static byte[] compressImage(Bitmap image, int maxSize) {
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        image.compress(Bitmap.CompressFormat.JPEG, 100, baos);// 质量压缩方法，这里100表示不压缩，把压缩后的数据存放到baos中
        int options = 100;
        while (baos.toByteArray().length / 1024 > maxSize) { // 循环判断如果压缩后图片是否大于100kb,大于继续压缩
            options = options/2;
            baos.reset(); // 重置baos即清空baos
            image.compress(Bitmap.CompressFormat.JPEG, options, baos);// 这里压缩options%，把压缩后的数据存放到baos中
//            Log.e("compressImage","while"+options);
        }
        return baos.toByteArray();
    }


    public class UpdateAsyncTask extends AsyncTask<Integer, Integer, Integer> {
        private Bitmap image;
        private int maxSize;
        public UpdateAsyncTask(Bitmap image,int maxSize) {
            super();
            this.image = image;
            this.maxSize = maxSize;
        }

        @Override
        protected Integer doInBackground(Integer... integers) {
            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            image.compress(Bitmap.CompressFormat.JPEG, 100, baos);//质量压缩方法，这里100表示不压缩，把压缩后的数据存放到baos中
            int options = 100;
            while ( baos.toByteArray().length / 1024>maxSize) {  //循环判断如果压缩后图片是否大于100kb,大于继续压缩
                baos.reset();//重置baos即清空baos
                image.compress(Bitmap.CompressFormat.JPEG, options, baos);//这里压缩options%，把压缩后的数据存放到baos中
                options -= 10;//每次都减少10
            }
            ByteArrayInputStream isBm = new ByteArrayInputStream(baos.toByteArray());//把压缩后的数据baos存放到ByteArrayInputStream中
            Bitmap bitmap = BitmapFactory.decodeStream(isBm, null, null);//把ByteArrayInputStream数据生成图片
            image = bitmap;
            return 1;
        }

        protected void onPreExecute() {
            Log.d("tag", "开始执行");
        }

        protected void onProgressUpdate(Integer... values) {
        }

        protected void onPostExecute(Integer result) {
        }
    }

}
