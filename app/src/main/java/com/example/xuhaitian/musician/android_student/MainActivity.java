package com.example.xuhaitian.musician.android_student;import android.Manifest;import android.annotation.SuppressLint;import android.content.Context;import android.content.Intent;import android.content.pm.PackageManager;import android.graphics.Color;import android.provider.ContactsContract;import android.support.annotation.NonNull;import android.support.v4.app.ActivityCompat;import android.support.v4.content.ContextCompat;import android.support.v7.app.AppCompatActivity;import android.os.Bundle;import android.support.v7.widget.Toolbar;import android.text.Html;import android.util.Log;import android.view.KeyEvent;import android.view.LayoutInflater;import android.view.View;import android.widget.ArrayAdapter;import android.widget.Button;import android.widget.LinearLayout;import android.widget.ListView;import android.widget.TextView;import android.widget.Toast;import com.avos.avoscloud.AVException;import com.avos.avoscloud.AVObject;import com.avos.avoscloud.AVQuery;import com.avos.avoscloud.AVUser;import com.avos.avoscloud.FindCallback;import com.avos.avoscloud.GetCallback;import com.avos.avoscloud.im.v2.AVIMClient;import com.avos.avoscloud.im.v2.AVIMConversation;import com.avos.avoscloud.im.v2.AVIMMessage;import com.avos.avoscloud.im.v2.AVIMMessageHandler;import com.avos.avoscloud.im.v2.AVIMMessageManager;import com.avos.avoscloud.im.v2.messages.AVIMTextMessage;import com.example.xuhaitian.musician.android_student.common.SysExitUtil;import com.netease.nimlib.sdk.NIMClient;import com.netease.nimlib.sdk.RequestCallback;import com.netease.nimlib.sdk.auth.AuthService;import com.netease.nimlib.sdk.auth.LoginInfo;import org.json.JSONArray;import org.json.JSONException;import org.json.JSONObject;import java.lang.reflect.Array;import java.text.ParseException;import java.text.ParsePosition;import java.text.SimpleDateFormat;import java.util.ArrayList;import java.util.Arrays;import java.util.Calendar;import java.util.Collection;import java.util.Collections;import java.util.Comparator;import java.util.Date;import java.util.Iterator;import java.util.List;import java.util.ListIterator;import java.util.Map;import static com.avos.avoscloud.Messages.CommandType.data;import static com.netease.nimlib.sdk.StatusCode.LOGINED;import static com.netease.nimlib.sdk.msg.constant.SystemMessageStatus.init;public class MainActivity extends AppCompatActivity {    Boolean isLoginEaseSuccess = false;    String now_week_day = getWeek(new Date());//周几    ArrayList<JSONObject> allCourseArrayList;    CourseAdapter adapter;    ListView listView;    private long time = 0;    //获取时间    @SuppressLint("SimpleDateFormat")    public static String getTime(int week_code, Date date) {        SimpleDateFormat sdf = new SimpleDateFormat("yyyy年MM月dd日");        Calendar calendar = Calendar.getInstance();        calendar.setTime(date);        calendar.add(Calendar.DAY_OF_MONTH, week_code);        date = calendar.getTime();        return sdf.format(date);    }    @SuppressLint("SimpleDateFormat")    public static String getWeek(Date date) {        SimpleDateFormat week = new SimpleDateFormat("E");//设置日期格式        return week.format(date);    }    @Override    protected void onResume() {        // TODO Auto-generated method stub        super.onResume();        MyLeanCloudApp myApp = (MyLeanCloudApp) getApplication();        myApp.setAudioTeachActivity(MainActivity.this);    }    public void startLoginEase() {        if (NIMClient.getStatus() != LOGINED) {            NIMClient.getService(AuthService.class).logout();            AVUser currentUser = getCurrentUser();            if (currentUser != null) {                try {                    JSONObject netEaseUserInfo = new JSONObject(currentUser.get("netEaseUserInfo").toString());                    LoginInfo info = new LoginInfo(netEaseUserInfo.getString("accid"), netEaseUserInfo.getString("token"));                    NIMClient.getService(AuthService.class).login(info)                            .setCallback(new RequestCallback() {                                @Override                                public void onSuccess(Object param) {                                    Toast.makeText(MainActivity.this, "白板登录成功", Toast.LENGTH_SHORT);                                    Log.e("TAG", "白板登录成功");                                    isLoginEaseSuccess = true;                                }                                @Override                                public void onFailed(int code) {                                    Toast.makeText(MainActivity.this, "白板登录失败" + code, Toast.LENGTH_SHORT);                                    Log.e("TAG", "白板登录失败" + code);                                    isLoginEaseSuccess = false;                                }                                @Override                                public void onException(Throwable exception) {                                    Log.e("TAG", "login: onException");                                    Toast.makeText(MainActivity.this, "白板登录异常失败", Toast.LENGTH_SHORT);                                    isLoginEaseSuccess = false;                                }                            });                } catch (JSONException e) {                }            }        }    }    @Override    protected void onStop() {        // TODO Auto-generated method stub        super.onStop();    }    public boolean checkSelfPermission(String permission, int requestCode) {        Log.e("Tag", "checkSelfPermission " + permission + " " + requestCode);        if (ContextCompat.checkSelfPermission(this,                permission)                != PackageManager.PERMISSION_GRANTED) {            ActivityCompat.requestPermissions(this,                    new String[]{permission},                    requestCode);            return false;        }        return true;    }    @Override    protected void onCreate(Bundle savedInstanceState) {        super.onCreate(savedInstanceState);        setContentView(R.layout.activity_main);        SysExitUtil.activityList.add(MainActivity.this);        initActionBar();        setTime();        week_onclick();        init_week();        //获取课程表数据        getCourseList(new Date());        allCourseArrayList = new ArrayList<JSONObject>();        adapter = new CourseAdapter(MainActivity.this, R.layout.list_items, allCourseArrayList);        listView = (ListView) findViewById(R.id.list_view);        listView.setAdapter(adapter);        checkSelfPermission(Manifest.permission_group.STORAGE, 0);        startLoginEase();        //注册默认的消息处理逻辑//        AVIMMessageManager.registerDefaultMessageHandler(new CustomMessageHandler());    }    public void startTeaching(JSONObject courseInfo) {        Log.e("===", courseInfo.toString());        JSONObject student_info = new JSONObject();        try {            String teacher_name = courseInfo.getString("teacher_name");            String teacherID = courseInfo.getString("teacherID");            String student_id = courseInfo.getString("student_id");            String netEaseUserInfo = courseInfo.getString("netEaseUserInfo");            student_info.put("teacher_name", teacher_name);            student_info.put("teacherID", teacherID);            student_info.put("student_id", student_id);            student_info.put("netEaseUserInfo", netEaseUserInfo);        } catch (JSONException e) {        }        //传输课程信息        Intent intent = new Intent(MainActivity.this, AudioTeachActivity.class);        intent.putExtra("teacher_info", student_info.toString());        Log.e("student_info", student_info.toString());        startActivity(intent);    }    public void initActionBar() {        android.support.v7.app.ActionBar actionBar = getSupportActionBar();        if (actionBar != null) {            actionBar.setTitle("");            actionBar.setDisplayShowHomeEnabled(false);            actionBar.setDisplayShowCustomEnabled(true);            LayoutInflater inflator = (LayoutInflater) this                    .getSystemService(Context.LAYOUT_INFLATER_SERVICE);            View v = inflator.inflate(R.layout.actionbar_center, new LinearLayout(MainActivity.this), false);            android.support.v7.app.ActionBar.LayoutParams layout = new android.support.v7.app.ActionBar.LayoutParams(                    android.support.v7.app.ActionBar.LayoutParams.MATCH_PARENT, android.support.v7.app.ActionBar.LayoutParams.MATCH_PARENT);            actionBar.setCustomView(v, layout);            Toolbar parent = (Toolbar) v.getParent();            parent.setContentInsetsAbsolute(0, 0);        }        TextView actionBarTitle = (TextView) findViewById(R.id.action_bar_title);        actionBarTitle.setText("学生课程表");        Button logout_btn = (Button) findViewById(R.id.logout);        logout_btn.setOnClickListener(new View.OnClickListener() {            @Override            public void onClick(View view) {                AVUser.logOut();                startActivity(new Intent(MainActivity.this, LoginActivity.class));            }        });    }    @Override    public boolean onKeyDown(int keyCode, KeyEvent event) {        if (keyCode == KeyEvent.KEYCODE_BACK) {            if ((System.currentTimeMillis() - time > 1000)) {                Toast.makeText(this, "再按一次返回桌面", Toast.LENGTH_SHORT).show();                time = System.currentTimeMillis();            } else {                Intent intent = new Intent(Intent.ACTION_MAIN);                intent.addCategory(Intent.CATEGORY_HOME);                startActivity(intent);                NIMClient.getService(AuthService.class).logout();            }            return true;        } else {            return super.onKeyDown(keyCode, event);        }    }    public AVUser getCurrentUser() {        AVUser currentUser = AVUser.getCurrentUser();        if (currentUser != null) {            Log.e("e", "+++++=========+++++" + currentUser.get("netEaseUserInfo"));        } else {            //缓存用户对象为空时，可打开用户注册界面…            Log.e("e", "+++++=========+++++");            startActivity(new Intent(MainActivity.this, LoginActivity.class));        }        return currentUser;    }    public void setTime() {        TextView textView = (TextView) findViewById(R.id.time);        textView.setText(getTime(0, new Date()));    }    //初始显示的星期    public void init_week() {        final LinearLayout weekLinearLayout = (LinearLayout) findViewById(R.id.week);        for (int m = 0; m < weekLinearLayout.getChildCount(); m++) {            Button weekbtn = (Button) weekLinearLayout.getChildAt(m);            if (now_week_day.equals("周" + weekbtn.getText().toString())) {                weekbtn.setBackground(getResources().getDrawable(R.drawable.red_button));                weekbtn.setTextColor(Color.WHITE);            } else {                weekbtn.setBackground(getResources().getDrawable(R.drawable.white_button));                weekbtn.setTextColor(Color.BLACK);            }        }    }    public void week_onclick() {        final LinearLayout weekLinearLayout = (LinearLayout) findViewById(R.id.week);        for (int i = 0; i < weekLinearLayout.getChildCount(); i++) {            Button btn = (Button) weekLinearLayout.getChildAt(i);            btn.setOnClickListener(new View.OnClickListener() {                @Override                public void onClick(View view) {                    Button test = (Button) view;                    String week_day = "周" + test.getText().toString();                    Log.e("test", "++++++++++" + week_day);                    //修改按钮颜色                    for (int m = 0; m < weekLinearLayout.getChildCount(); m++) {                        Button weekbtn = (Button) weekLinearLayout.getChildAt(m);                        if (test.getText().toString().equals(weekbtn.getText().toString())) {                            weekbtn.setBackground(getResources().getDrawable(R.drawable.red_button));                            weekbtn.setTextColor(Color.WHITE);                        } else {                            weekbtn.setBackground(getResources().getDrawable(R.drawable.white_button));                            weekbtn.setTextColor(Color.BLACK);                        }                    }                    //更新时间                    int diff_day_number = get_now_week_code(week_day) - get_now_week_code(now_week_day);                    TextView textView = (TextView) findViewById(R.id.time);                    try {                        Date nowDate = stringToDate(textView.getText().toString());                        String showTime = getTime(diff_day_number, nowDate);                        textView.setText(showTime);                        getCourseList(stringToDate(showTime));                        now_week_day = week_day;                    } catch (ParseException err) {                    }                }            });        }        Button last_button = (Button) findViewById(R.id.last_week);        last_button.setOnClickListener(new View.OnClickListener() {            @Override            public void onClick(View view) {                TextView textView = (TextView) findViewById(R.id.time);                int code = -7;                try {                    Date nowDate = stringToDate(textView.getText().toString());                    textView.setText(getTime(code, nowDate));                    getCourseList(stringToDate(getTime(code, nowDate)));                } catch (ParseException err) {                }            }        });        Button next_button = (Button) findViewById(R.id.next_week);        next_button.setOnClickListener(new View.OnClickListener() {            @Override            public void onClick(View view) {                TextView textView = (TextView) findViewById(R.id.time);                int code = 7;                try {                    Date nowDate = stringToDate(textView.getText().toString());                    textView.setText(getTime(code, nowDate));                    getCourseList(stringToDate(getTime(code, nowDate)));                } catch (ParseException err) {                }            }        });    }    public int get_now_week_code(String day) {        Log.e("get_now_week_code", day);        if (day.equals("周一")) {            return 1;        } else if (day.equals("周二")) {            return 2;        } else if (day.equals("周三")) {            return 3;        } else if (day.equals("周四")) {            return 4;        } else if (day.equals("周五")) {            return 5;        } else if (day.equals("周六")) {            return 6;        } else {            return 7;        }    }    public Date stringToDate(String strTime) throws ParseException {        SimpleDateFormat formatter = new SimpleDateFormat("yyyy年MM月dd日");        Date date = formatter.parse(strTime);        return date;    }    public String getFormatDateStringWithMinus(Date date) {        SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd");        return formatter.format(date);    }    //获取课程表信息    public Date getDateFromStringWithMinus(String strDate) throws ParseException {        SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");        Date date = formatter.parse(strDate);        return date;    }    public Date addSecondToDate(Date date, int numberSecond) {        Calendar calendar = Calendar.getInstance();        calendar.setTime(date);        calendar.add(Calendar.SECOND, numberSecond);        return calendar.getTime();    }    public void getCourseList(Date date) {        AVUser currentUser = AVUser.getCurrentUser();        if (currentUser != null) {            final String strMinusDate = getFormatDateStringWithMinus(date);            try {                final Date startDate = getDateFromStringWithMinus(strMinusDate + " 00:00:00");                Date endDate = getDateFromStringWithMinus(strMinusDate + " 23:59:59");                final AVQuery<AVObject> startDateQuery = new AVQuery<>("Course");                startDateQuery.whereGreaterThan("startTime", startDate);                final AVQuery<AVObject> endDateQuery = new AVQuery<>("Course");                endDateQuery.whereLessThan("startTime", endDate);                final String accountID = currentUser.getObjectId();                AVQuery<AVObject> userQuery = new AVQuery<>("Course");                userQuery.whereEqualTo("student", AVObject.createWithoutData("_User", "" + accountID));                AVQuery<AVObject> query = AVQuery.and(Arrays.asList(userQuery, startDateQuery, endDateQuery));                query.include("teacher");                query.findInBackground(new FindCallback<AVObject>() {                    @Override                    public void done(List<AVObject> list, AVException e) {                        Log.e("list", "1111111111111111111111" + list);                        if (list == null) {                            Toast.makeText(MainActivity.this, "获取课程列表失败，请检查网络", Toast.LENGTH_SHORT).show();                            return;                        }                        allCourseArrayList = new ArrayList<JSONObject>();                        for (int i = 0; i < list.size(); i++) {                            AVObject objectInfo = list.get(i);                            try {                                JSONObject teacherInfo = new JSONObject(objectInfo.get("teacher").toString());                                Date startTime = new Date(objectInfo.get("startTime").toString());                                String duration = objectInfo.get("duration").toString();                                Date endDate = addSecondToDate(startTime, Integer.valueOf(duration) / 1000);                                String courseName = objectInfo.get("name").toString();                                String comment = objectInfo.get("comment").toString();                                //教师信息                                JSONObject newCourseInfo = new JSONObject();                                newCourseInfo.put("teacher_name", teacherInfo.getJSONObject("serverData").getString("username"));                                newCourseInfo.put("netEaseUserInfo", teacherInfo.getJSONObject("serverData").getString("netEaseUserInfo"));                                newCourseInfo.put("teacherID", teacherInfo.getString("objectId"));                                newCourseInfo.put("startTime", startTime);                                newCourseInfo.put("endDate", endDate);                                newCourseInfo.put("course_name", courseName);                                newCourseInfo.put("student_id", accountID);                                newCourseInfo.put("comment", comment);                                //五条上课信息                                Date noonTime = getDateFromStringWithMinus(strMinusDate + " 12:00:00");                                Date nightTime = getDateFromStringWithMinus(strMinusDate + " 18:00:00");                                if (startTime.before(noonTime)) {                                    newCourseInfo.put("type","morningCourse");                                    allCourseArrayList.add(newCourseInfo);                                }                                else if (startTime.after(nightTime)) {                                    newCourseInfo.put("type","nightCourse");                                    allCourseArrayList.add(newCourseInfo);                                } else {                                    newCourseInfo.put("type","noonCourse");                                    allCourseArrayList.add(newCourseInfo);                                }                            } catch (Exception error) {                                Log.e("JSONException", error.toString());                            }                        }                        ArrayList<JSONObject> sortCourseArrayList = new ArrayList<JSONObject>();                        int size = allCourseArrayList.size();                        try {                            for (int m = 0; m < size; m ++)                            {                                JSONObject earlistTimeCourse = allCourseArrayList.get(0);                                for (int  i = 1; i < allCourseArrayList.size(); i ++)                                {                                    Date courseTime = (Date) (allCourseArrayList.get(i).get("startTime"));                                    Date earlistTime = (Date) earlistTimeCourse.get("startTime");                                    if (earlistTime.after(courseTime))                                    {                                        earlistTimeCourse = allCourseArrayList.get(i);                                    }                                }                                sortCourseArrayList.add(earlistTimeCourse);                                allCourseArrayList.remove(earlistTimeCourse);                            }                        }catch (JSONException e1)                        {                        }                        Log.e("sort",allCourseArrayList.toString());                        adapter = new CourseAdapter(MainActivity.this, R.layout.list_items, sortCourseArrayList);                        listView.setAdapter(adapter);                    }                });            } catch (ParseException e) {            }        }    }    public static Date StrToDate(String str) {        SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");        Date date = null;        try {            date = format.parse(str);        } catch (ParseException e) {            e.printStackTrace();        }        return date;    }}