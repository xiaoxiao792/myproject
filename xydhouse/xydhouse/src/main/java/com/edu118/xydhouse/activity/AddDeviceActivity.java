package com.edu118.xydhouse.activity;

import android.app.Activity;
import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

import com.edu118.xydhouse.R;

public class AddDeviceActivity extends AppCompatActivity {
    private EditText mEtDeviceName;
    private EditText mEtDeviceId;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_add_device);
        initView();
    }

    private void initView() {
        mEtDeviceName = (EditText)findViewById(R.id.ac_add_device_name);
        mEtDeviceId = (EditText)findViewById(R.id.ac_add_device_id);
        //监听查看多少位数
        mEtDeviceId.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence charSequence, int i, int i1, int i2) {
                //获取焦点且文字内容改变前
            }

            @Override
            public void onTextChanged(CharSequence charSequence, int i, int i1, int i2) {
                //文字内容正在改变
            }

            @Override
            public void afterTextChanged(Editable editable) {
                //获取焦点且文字内容改变后
                String text = editable.toString().trim();
                //长度值
                int length = text.length();
                //当位数超过23时,提示用户
                if (length >= 23) {
                    Toast.makeText(AddDeviceActivity.this, "当前输入的设备ID的长度:" + length + "位!", Toast.LENGTH_SHORT).show();
                }
            }
        });

    }

    public void cancelDevice(View view) {
        Toast.makeText(this,"已取消添加，谢谢！",Toast.LENGTH_SHORT).show();

        finish();
    }

    @Override
    public void onBackPressed() {
        super.onBackPressed();
        Toast.makeText(this,"点击返回按钮，已取消添加，谢谢！",Toast.LENGTH_SHORT).show();
    }

    public void comfirmDevice(View view) {
        //对于名称,至少1个字符
        String addName = "";
        String name = mEtDeviceName.getText().toString().trim();
        if (name.length() == 0) {
            mEtDeviceName.setText("仲恺-物联网");
            addName = "仲恺-物联网";
        } else {
            addName = name;
        }

        //对于ID,输入长度24;整体长度26
        String addId = "";
        String id = mEtDeviceId.getText().toString().trim();
        if (id.length() == 0) {
            Toast.makeText(this, "注意:您的设备ID未输入任何信息,请您核对一下!", Toast.LENGTH_SHORT).show();
        } else if (0 < id.length() && id.length() < 24) {
            Toast.makeText(this, "注意:您的设备ID输入长度不足,请您核对成功后再确认!", Toast.LENGTH_SHORT).show();
        } else if (24 < id.length()) {
            Toast.makeText(this, "注意:您的设备ID输入长度超过24啦,请您核对成功后再确认!", Toast.LENGTH_SHORT).show();
        } else {
            addId = "0X" + id;
        }
        //输入正确的情况
        if (addName.length() > 0 && addId.length() == 26) {
            Toast.makeText(this, "您输入的信息满足条件,正在为您添加设备,请稍后...", Toast.LENGTH_SHORT).show();

            Intent intent = new Intent();
            //携带信息回到上一个Activity
            intent.putExtra("devicename", addName);
            intent.putExtra("deviceid", addId);
            //添加到数据库中
            //返回
            setResult(Activity.RESULT_OK, intent);
            //关闭当前页面
            finish();
        }

    }
}
