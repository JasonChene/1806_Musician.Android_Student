package com.example.xuhaitian.musician.android_student;import android.content.Context;import android.util.Log;import android.view.LayoutInflater;import android.view.View;import android.view.ViewGroup;import android.widget.BaseAdapter;import android.widget.Button;import android.widget.EditText;import android.widget.ImageView;import android.widget.LinearLayout;import android.widget.TextView;import org.json.JSONArray;import org.json.JSONException;import org.json.JSONObject;import java.text.ParseException;import java.text.SimpleDateFormat;import java.util.ArrayList;import java.util.Date;import java.util.List;/** * Created by lw on 2017/4/14. */public class CourseAdapter extends BaseAdapter {    private final int resourceId;    public Context mContext;    List<JSONObject> listData;    private LayoutInflater mLayoutInflater;    public CourseAdapter(Context context, int textViewResourceId, ArrayList<JSONObject> objects) {        resourceId = textViewResourceId;        mContext = context;        listData = objects;        mLayoutInflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);    }    @Override    public int getCount() {        return listData.size();    }    @Override    public Object getItem(int position) {        return listData.get(position);    }    @Override    public long getItemId(int position) {        return position;    }    public static Date stringToDate(String strTime, String formatType)            throws ParseException {        SimpleDateFormat formatter = new SimpleDateFormat(formatType);        Date date = null;        date = formatter.parse(strTime);        return date;    }    public String getFormatTimeString(Date date)    {        SimpleDateFormat formatter = new SimpleDateFormat("HH:mm");        return formatter.format(date);    }    @Override    public View getView(int position, View convertView, ViewGroup parent) {        final JSONObject course = (JSONObject) getItem(position); // 获取当前项的Fruit实例        Log.e("course", course.toString());        View view = mLayoutInflater.inflate(resourceId, null);//实例化一个对象        TextView course_Name = (TextView) view.findViewById(R.id.course_Name);//获取该布局内的课程名视图        TextView comment = (TextView) view.findViewById(R.id.comment);//获取该布局内的评论视图        TextView teacher_Name = (TextView) view.findViewById(R.id.teacher_Name);//获取该布局内的老师名视图        Button start_teaching = (Button) view.findViewById(R.id.start_teaching);        start_teaching.setOnClickListener(new View.OnClickListener() {            @Override            public void onClick(View view) {                MainActivity mainActivity = (MainActivity) mContext;                mainActivity.startTeaching(course);            }        });        try {            String type = course.getString("type");            Log.e("course", ""+course);            String start_data = getFormatTimeString((Date)course.get("startTime"));            String end_data = getFormatTimeString((Date)course.get("endDate"));            if (type.equals("morningCourse")) {                    layoutItemWithTime(view, R.drawable.morning, R.drawable.linerlayout_shape_morning, "" + start_data, "" + end_data);                } else if (type.equals("noonCourse")) {                    layoutItemWithTime(view, R.drawable.noon, R.drawable.linerlayout_shape_noon, "" + start_data, "" + end_data);                } else if (type.equals("nightCourse")) {                    layoutItemWithTime(view, R.drawable.evening, R.drawable.linerlayout_shape_night, "" + start_data, "" + end_data);                }                String teacher_name = course.getString("teacher_name");                String courseName = course.getString("course_name");                String teacher_comment = course.getString("comment");                Date startDate = null;                Date endDate = null;                Date aStartDate = (Date) course.get("startTime");                Date aEndDate = (Date) course.get("endDate");                if (startDate == null) {                    startDate = aStartDate;                    endDate = aEndDate;                } else {                    startDate = startDate.before(aStartDate) ? startDate : aStartDate;                    endDate = endDate.after(aEndDate) ? endDate : aEndDate;                }                teacher_Name.setText(teacher_name);                course_Name.setText(courseName);                comment.setText(teacher_comment);                setTeachingAndCommentStatus(startDate, endDate, start_teaching);        } catch (JSONException e) {        }        return view;    }    public void layoutItemWithTime(View view, int imageResource, int shape_color, String str_start_time, String str_end_time) {        ImageView statusImage = (ImageView) view.findViewById(R.id.image);//获取该布局内的图片视图        statusImage.setImageResource(imageResource);        LinearLayout time_background = (LinearLayout) view.findViewById(R.id.time_background);        TextView start_time = (TextView) view.findViewById(R.id.start_time);        TextView end_time = (TextView) view.findViewById(R.id.end_time);        time_background.setBackgroundResource(shape_color);        start_time.setText(str_start_time);        end_time.setText(str_end_time);    }    public void setTeachingAndCommentStatus(Date startDate, Date endDate, Button start_teaching) {        //未开始        if (startDate.after(new Date())) {            start_teaching.setText("未开始");            start_teaching.setBackgroundResource(R.drawable.end_nostart_button);            start_teaching.setEnabled(false);        }//已结束        else if (endDate.before(new Date())) {            start_teaching.setText("已结束");            start_teaching.setBackgroundResource(R.drawable.end_nostart_button);//            start_teaching.setEnabled(false);        } else {            //正在上课            start_teaching.setText("上课中");            start_teaching.setEnabled(true);        }    }}