package com.edu118.xydhouse.fragment;

import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.RadioGroup;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import com.edu118.xydhouse.R;
import com.edu118.xydhouse.listener.IRequestDataListener;
import com.edu118.xydhouse.util.HttpUtil;
import com.edu118.xydhouse.view.ColorPickView;
import com.xw.repo.BubbleSeekBar;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class UpdateInfoFragment extends Fragment {

    private String deviceId;
    private String windowValue;
    private String windValue;
    private String mRelay;
    private String colorStr;
    private HttpUtil mHttpUtil;

    @Override
    public void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        //获得Id
        Intent intent = getActivity().getIntent();
        //设备ID
        deviceId = intent.getStringExtra("deviceID");
        mHttpUtil = HttpUtil.getInstance();
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        return inflater.inflate(R.layout.fragment_update_info, container, false);
    }

    @Override
    public void onViewCreated(View view, @Nullable Bundle savedInstanceState) {
        //super.onViewCreated(view, savedInstanceState);
        initView();

    }

    private void initView() {
        //获得控件
        TextView tvDeviceId = (TextView) getActivity().findViewById(R.id.fg_update_tv_deviceid);
        //设置ID
        tvDeviceId.setText(deviceId);

        //设置窗帘控制
        Spinner spinnerWindow = (Spinner) getActivity().findViewById(R.id.fg_update_spinner_window);
//数据
        final List<String> windowDatas = loadWindowDatas();
//设置适配器
        WindowCtrolAdapter adapter = new WindowCtrolAdapter(getActivity(),windowDatas);
        spinnerWindow.setAdapter(adapter);
//选中事件
        spinnerWindow.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> adapterView, View view, int i, long l) {
                //选中item项
                Toast.makeText(getActivity(),"选中item项:"+windowDatas.get(i),Toast.LENGTH_SHORT).show();
                windowValue = windowDatas.get(i);
            }

            @Override
            public void onNothingSelected(AdapterView<?> adapterView) {
                //什么都没选中
            }
        });

        //设置通风控制
        BubbleSeekBar seekBar = (BubbleSeekBar) getActivity().findViewById(R.id.fg_update_wind_bsb_bar);
        final TextView tvWind = (TextView) getActivity().findViewById(R.id.fg_update_wind_tv_value);
//选中进度
        seekBar.setOnProgressChangedListener(new BubbleSeekBar.OnProgressChangedListener() {
            @Override
            public void onProgressChanged(BubbleSeekBar bubbleSeekBar, int progress, float progressFloat, boolean fromUser) {
                //改变后
                tvWind.setText(progress+"");
                //
                windValue = progress+"";
            }

            @Override
            public void getProgressOnActionUp(BubbleSeekBar bubbleSeekBar, int progress, float progressFloat) {

            }

            @Override
            public void getProgressOnFinally(BubbleSeekBar bubbleSeekBar, int progress, float progressFloat, boolean fromUser) {

            }
        });

        //智能插座
        RadioGroup group = (RadioGroup) getActivity().findViewById(R.id.fg_update_rg_group);
//监听事件
        group.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(RadioGroup radioGroup, int i) {
                //判断id
                switch (i){
                    case R.id.fg_update_rb_01:
                        mRelay = "";
                        break;
                    case R.id.fg_update_rb_02:
                        mRelay = "1";
                        break;
                    case R.id.fg_update_rb_03:
                        mRelay = "0";
                        break;
                    default:
                        mRelay = "";
                        break;
                }
            }
        });

        //颜色控制
        final EditText etColor = (EditText) getActivity().findViewById(R.id.fg_updata_et_color);
        final ColorPickView colorPickView = (ColorPickView) getActivity().findViewById(R.id.fg_update_color_picker_view);
        colorPickView.setOnColorBackListener(new ColorPickView.OnColorBackListener() {
            @Override
            public void onColorBack(int a, int r, int g, int b) {
//                etColorChoose.setText("R：" + r + "\nG：" + g + "\nB：" + b + "\n" + colorDisk.getColorStr());
                etColor.setText(colorPickView.getColorStr());
//                tv.setTextColor(Color.argb(a, r, g, b));
                //TODO 颜色控制
                colorStr = colorPickView.getColorStr();
            }
        });

        Button btnConfirm = (Button) getActivity().findViewById(R.id.fg_update_btn_comfirm_update);
        //http://134.175.80.178:8080/cgi-bin/ctrl.cgi?devid=0X87192010484884480667ff54&motor_setup=1&motor=20&relay=1&color=%23561214&ok=%E7%A1%AE%E5%AE%9A
        btnConfirm.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //网络请求
                Map<String,String> params = new HashMap<String, String>();
                //devid=0X87192010484884480667ff54
                if(deviceId != null){
                    params.put("devid",deviceId);
                }
                // &motor_setup=1
                if(windowValue != null){
                    params.put("motor_setup",windowValue);
                }else{
                    params.put("motor_setup","");
                }
                // &motor=20
                if(windValue != null){
                    params.put("motor",windValue);
                }else{
                    params.put("motor","");
                }
                // &relay=1
                if(mRelay != null){
                    params.put("relay",mRelay);
                }
                // &color=%23561214
                if(colorStr != null){
                    params.put("color",colorStr);
                }
                // &ok=%E7%A1%AE%E5%AE%9A
                params.put("ok","确定");

                mHttpUtil.doxUtilsHttpRequestByGet("http://134.175.80.178:8080/cgi-bin/ctrl.cgi",
                        params,
                        new IRequestDataListener() {
                            @Override
                            public void onRequestSuccess(String result) {
                                //弹出对话框
                                Toast.makeText(getActivity(),"正在修改设备的状态信息,请稍后...",Toast.LENGTH_SHORT).show();
                            }

                            @Override
                            public void onRequestFailure(String errorMsg) {

                            }
                        });
            }
        });

    }

    private class WindowCtrolAdapter extends BaseAdapter {
        private final Context mContext;
        private final List<String> mDatas;

        public WindowCtrolAdapter(Context context, List<String> windowDatas) {
            this.mContext = context;
            this.mDatas = windowDatas;
        }

        @Override
        public int getCount() {
            return mDatas.size();
        }

        @Override
        public Object getItem(int i) {
            return mDatas.get(i);
        }

        @Override
        public long getItemId(int i) {
            return i;
        }

        @Override
        public View getView(int i, View view, ViewGroup viewGroup) {
            ViewHolder viewHolder = null;
            if(view == null){
                view = LayoutInflater.from(mContext).inflate(R.layout.layout_fg_update_spinner_item,viewGroup,false);
                viewHolder = new ViewHolder();
                viewHolder.tvName= (TextView) view.findViewById(R.id.fg_upate_spinner_item_name);
                view.setTag(viewHolder);
            }
            viewHolder = (ViewHolder) view.getTag();
            String name = (String) getItem(i);
            viewHolder.tvName.setText(name);
            return view;
        }
        //ViewHolder
        private class ViewHolder{
            private TextView tvName;
        }
    }

    private List<String> loadWindowDatas() {
        List<String> datas = new ArrayList<>();
        datas.add("保持原态");
        datas.add("00");
        datas.add("01");
        datas.add("02");
        datas.add("03");
        datas.add("04");
        datas.add("05");
        datas.add("06");
        datas.add("07");
        datas.add("08");
        datas.add("08");
        datas.add("10");
        return datas;
    }
}
