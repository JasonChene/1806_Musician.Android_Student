package com.example.xuhaitian.musician.android_student;

import android.Manifest;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.graphics.Path;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.net.Uri;
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
import android.view.SurfaceView;
import android.view.View;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.LinearLayout;
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
            isJoinInRoom = true;
        }
        public void onUserJoined( int uid, int elapsed )
        {
            isJoinInRoom = true;
        }
    };
//    private Handler handler = new Handler() {
//        @Override
//        public void handleMessage(Message msg) {
//            switch (msg.what) {
//                case GET_DATA_SUCCESS:
//                    Bitmap bitmap = (Bitmap) msg.obj;
//                    setImageBitmap(bitmap);
//                    break;
//                case NETWORK_ERROR:
//                    Toast.makeText(AudioTeachActivity.this, "网络连接失败", Toast.LENGTH_SHORT).show();
//                    break;
//                case SERVER_ERROR:
//                    Toast.makeText(AudioTeachActivity.this, "服务器发生错误", Toast.LENGTH_SHORT).show();
//                    break;
//            }
//        }
//    };

//    public void setImageBitmap(Bitmap bitmap) {
//        drawBackgroud.setBackground(new BitmapDrawable(getResources(), bitmap));
//        //显示清除按钮
////        Button clear_button = (Button) findViewById(R.id.clear);
////        clear_button.setVisibility(View.VISIBLE);
//    }
//
////    public void startKeepUpBoard(String sessionID, String toAccount) {
////        main_draw.sessionID = sessionID;     //参数传递
////        main_draw.toAccount = toAccount;     //参数传递
////        main_draw.setVisibility(View.VISIBLE);
////        peer_draw.sessionID = sessionID;
////        peer_draw.toAccount = toAccount;
////        peer_draw.setVisibility(View.VISIBLE);
////        drawBackgroud.setVisibility(View.VISIBLE);
////
////        //注册收到数据的监听
////        WhiteBoardManager.registerIncomingData(sessionID, true, main_draw, AudioTeachActivity.this);
////        WhiteBoardManager.registerRTSCloseObserver(sessionID, true, AudioTeachActivity.this);
////        //隐藏本地视频窗口
////        FrameLayout local_container = (FrameLayout) findViewById(R.id.local_video_view_container);
////        local_container.setVisibility(GONE);
////    }

//    public void terminateRTS(String sessionID) {
//        //注销收数据监听
//        Boolean isDataSuccess = RTSManager.getInstance().observeReceiveData(sessionID, new Observer<RTSTunData>() {
//            @Override
//            public void onEvent(RTSTunData rtsTunData) {
//            }
//        }, false);
//        Log.e("TAG", "注销收数据监听" + isDataSuccess);
//        //注销挂断监听
//        Boolean isCloseSuccess = RTSManager.getInstance().observeHangUpNotification(sessionID, new Observer<RTSCommonEvent>() {
//            @Override
//            public void onEvent(RTSCommonEvent rtsCommonEvent) {
//            }
//        }, false);
//        Log.e("TAG", "注销挂断监听" + isCloseSuccess);
//
//        drawBackgroud.setBackgroundResource(0);
//        drawBackgroud.setVisibility(GONE);
//    }
//    public void addMusicPic(String strMusicImageUrl) {
//        //设置本地图片
//        Log.i("MusicPicUrl:", "" + strMusicImageUrl);
//        setImageURL(strMusicImageUrl);
//    }

//    public void setImageURL(final String path) {
//        //开启一个线程用于联网
//        new Thread() {
//            @Override
//            public void run() {
//                try {
//                    //把传过来的路径转成URL
//                    URL url = new URL(path);
//                    //获取连接
//                    HttpURLConnection connection = (HttpURLConnection) url.openConnection();
//                    //使用GET方法访问网络
//                    connection.setRequestMethod("GET");
//                    //超时时间为10秒
//                    connection.setConnectTimeout(10000);
//                    //获取返回码
//                    int code = connection.getResponseCode();
//                    if (code == 200) {
//                        InputStream inputStream = connection.getInputStream();
//                        //使用工厂把网络的输入流生产Bitmap
//                        Bitmap bitmap = BitmapFactory.decodeStream(inputStream);
//                        //利用Message把图片发给Handler
//                        Message msg = Message.obtain();
//                        msg.obj = bitmap;
//                        msg.what = GET_DATA_SUCCESS;
//                        handler.sendMessage(msg);
//                        inputStream.close();
//                    } else {
//                        //服务启发生错误
//                        handler.sendEmptyMessage(SERVER_ERROR);
//                    }
//                } catch (IOException e) {
//                    e.printStackTrace();
//                    //网络连接错误
//                    handler.sendEmptyMessage(NETWORK_ERROR);
//                }
//            }
//        }.start();
//    }


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_audio_teach);
        SysExitUtil.activityList.add(AudioTeachActivity.this);
        initActionBar();
        myApp = (MyLeanCloudApp) getApplication();
        myApp.setAudioTeachActivity(AudioTeachActivity.this);
        main_draw = findViewById(R.id.main_draw);
        peer_draw = findViewById(R.id.peer_draw);
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
                WhiteBoardManager.close(main_draw.sessionID,AudioTeachActivity.this);
                view.setVisibility(View.GONE);
                drawBackgroud.setVisibility(View.GONE);
                main_draw.setVisibility(View.GONE);
                peer_draw.setVisibility(View.GONE);
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
                        Log.e("path",path);
                        Bitmap bitmap = BitmapFactory.decodeFile(path);
                        Log.e("bitmap",bitmap.toString());
                        drawBackgroud.setBackground(new BitmapDrawable(getResources(), bitmap));
                        uploadMusicImage(path);
                    } catch (Exception e) {
                        // TODO Auto-generatedcatch block
                        e.printStackTrace();
                    }
                }
                break;
        }
    }

    public void showMusicWhiteBoard(){
        Log.e("show","showMusicWhiteBoard");
        //打开白板
        drawBackgroud.setVisibility(View.VISIBLE);
        main_draw.setVisibility(View.VISIBLE);
        peer_draw.setVisibility(View.VISIBLE);
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
                Toast.makeText(AudioTeachActivity.this, "发起白板会话成功", Toast.LENGTH_SHORT).show();
                //注册主叫方收到被叫相应的回调
                WhiteBoardManager.registerCalleeAckNotification(rtsData.getLocalSessionId(),true,eastAccount,AudioTeachActivity.this);
                Button close_music = (Button)findViewById(R.id.close_music);
                close_music.setVisibility(View.VISIBLE);
            }

            @Override
            public void onFailed(int code) {
                Toast.makeText(AudioTeachActivity.this, "发起白板会话失败，错误码"+ code, Toast.LENGTH_SHORT).show();
            }

            @Override
            public void onException(Throwable exception) {
                Toast.makeText(AudioTeachActivity.this, "发起白板会话异常", Toast.LENGTH_SHORT).show();
            }
        });
    }

    private void uploadMusicImage(String path){
        try {
            final AVFile file = AVFile.withAbsoluteLocalPath("LeanCloud.png", path);
            file.saveInBackground(new SaveCallback() {
                @Override
                public void done(AVException e) {
                    if (e == null)
                    {
                        Log.e("uploadURL", file.getUrl());//返回一个唯一的 Url 地址
                        String sendImageData = "0:"+file.getUrl();
                        WhiteBoardManager.sendToRemote(main_draw.sessionID,main_draw.toAccount,sendImageData);
                    }

                }
            });
        }catch (FileNotFoundException err)
        {

        }

    }

    public void clearMusicPicture()
    {
        main_draw.Clear();
        peer_draw.Clear();
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
                showMusicWhiteBoard();
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
    }



    //初始化进入房间
    private void initAgoraEngineAndJoinChannel(int uid) {
        initializeAgoraEngine();     // Tutorial Step 1
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
//            if (main_draw.getVisibility() == GONE) {
                if (local_video.getVisibility() == GONE) {
                    sendMessageToTeacher("studentOffline","studentOffline");
                    this.finish();
                    startActivity(new Intent(AudioTeachActivity.this, MainActivity.class));
                } else {
                    Toast.makeText(AudioTeachActivity.this, "现在正在与老师视频", Toast.LENGTH_SHORT).show();
                    return false;
                }
//            } else {
//                Toast.makeText(AudioTeachActivity.this, "现在正在与学生教学", Toast.LENGTH_SHORT).show();
//                return false;
//            }
        }
        return super.onKeyDown(keyCode,event);
    }

    @Override
    protected void onDestroy() {
        Log.e("TAG", "onDestroy");
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
                        textview.setText("正在和"+teacher_name +"乐谱教学");
                        sendMessageToTeacher("成功收到老师上线通知","成功收到老师上线通知");

                    }
                    else if(((AVIMTextMessage) message).getText().equals("收到学生上线通知"))
                    {
                        Log.e("2", "收到学生上线通知");
                        textview.setText("正在和"+teacher_name +"乐谱教学");

                    }
                    else if(((AVIMTextMessage) message).getText().equals("老师下线"))
                    {
                        Log.e("3", "老师下线");
                        textview.setText("老师下线");

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
}
