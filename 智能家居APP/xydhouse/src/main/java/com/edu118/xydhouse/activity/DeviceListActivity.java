package com.edu118.xydhouse.activity;


import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ListView;
import android.widget.Toast;

import com.edu118.xydhouse.R;
import com.edu118.xydhouse.adapter.DeviceAdapter;
import com.edu118.xydhouse.bean.DeviceBean;
import com.edu118.xydhouse.db.DbAccessUtil;
import com.edu118.xydhouse.listener.IRequestDataListener;
import com.edu118.xydhouse.util.HttpUtil;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class DeviceListActivity extends AppCompatActivity implements AdapterView.OnItemClickListener{
    private DbAccessUtil dbAccessUtil;
    private DeviceAdapter mAdapter;
    private List<DeviceBean> deviceDatas;
    private HttpUtil mHttpUtil;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_device_list);
        //获得 DbAccessUtil对象
       dbAccessUtil = DbAccessUtil.getInstance(this);
        //获得网络通信对象
        mHttpUtil = HttpUtil.getInstance();
        //初始化控件
        initViews();
    }

    private void initViews() {
        //三要素
        ListView mListView = (ListView) findViewById(R.id.ac_device_lv_litview);
        deviceDatas = loadDatas();
        mAdapter = new DeviceAdapter(this,deviceDatas);
        mListView.setAdapter(mAdapter);
        //绑定
        mListView.setOnItemClickListener(this);
    }

    private List<DeviceBean> loadDatas() {
        List<DeviceBean> datas = dbAccessUtil.queryAllDeviceInfo();

        return datas;
    }

    public void refreshDeviceInfo(View view) {
        Toast.makeText(this, "刷新设备", Toast.LENGTH_SHORT).show();
        //判断
        if(dbAccessUtil != null && mAdapter != null){
            //清空之前的数据
            deviceDatas.clear();
            // 添加新数据进入
            deviceDatas.addAll(dbAccessUtil.queryAllDeviceInfo());
            // 刷新页面
            mAdapter.notifyDataSetChanged();

        }
    }
//处理

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        //判断处理
        if(requestCode ==1 && resultCode == Activity.RESULT_OK){
            //获得名称
            String devicename = data.getStringExtra("devicename");
            String deviceid = data.getStringExtra("deviceid");
            //存入
            DeviceBean deviceBean = new DeviceBean(deviceid,devicename);
            dbAccessUtil.addOneData(deviceBean);

        }
    }

    public void addNewDevice(View view) {
        Toast.makeText(this, "添加一个设备", Toast.LENGTH_SHORT).show();
        Intent intent = new Intent(this,AddDeviceActivity.class);
        //startActivity(intent);
        //请求码
        startActivityForResult(intent,1);
    }

    @Override
    public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {
        //点击事件
        DeviceBean bean = deviceDatas.get(i);
        //
        String deviceName = bean.getDeviceName();
        final String deviceId = bean.getDeviceId();
//        Toast.makeText(DeviceListActivity.this,"名称:"+deviceName+"\nID值:"+deviceId,Toast.LENGTH_SHORT).show();

        //网络通信、验证成功与否：  http://134.175.80.178:8080/cgi-bin/showstatus.cgi?deviceid=0X432032213934424d066fff31
        Map<String, String> params = new HashMap<>();
        if (deviceId != null) {
            params.put("deviceid", deviceId);
        }

        mHttpUtil.doxUtilsHttpRequestByGet("http://134.175.80.178:8080/cgi-bin/showstatus.cgi", params, new IRequestDataListener() {
            @Override
            public void onRequestSuccess(String result) {
                //成功
                //成功  -->进入修改信息的页面; 通信失败  --条件判断
                if(result !=null && result.contains("设  备ID:")){
                    //成功
                    Toast.makeText(DeviceListActivity.this,"本设备能正常通信!!",Toast.LENGTH_SHORT).show();
                    //intent
                    Intent intent = new Intent(DeviceListActivity.this,OperateActivity.class);
                    //携带参数
                    intent.putExtra("deviceID",deviceId);
                    //跳转
                    startActivity(intent);
                }else{
                    Toast.makeText(DeviceListActivity.this,"本设备ID不能正常网络通信,请仔细核对!",Toast.LENGTH_SHORT).show();
                }
            }

            @Override
            public void onRequestFailure(String errorMsg) {
                //失败
            }
        });
    }
}
