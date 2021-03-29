package com.edu118.xydhouse.activity;

import android.os.Bundle;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.support.v7.app.AppCompatActivity;
import android.widget.RadioGroup;
import android.widget.Toast;

import com.edu118.xydhouse.R;
import com.edu118.xydhouse.fragment.LookStatusFragment;
import com.edu118.xydhouse.fragment.UpdateInfoFragment;

public class OperateActivity extends AppCompatActivity {
    private RadioGroup mRgGroup;
    private FragmentManager fragmentManager;

    private static final String[] FRAGMENT_TAG = {"UpdateInfo", "LookStatus"};
    private UpdateInfoFragment updateInfoFragment;//修改信息
    private LookStatusFragment lookStatusFragment;//查看状态

    private final int show_updateInfo = 0;//修改信息
    private final int show_lookStatus = 1;//查看状态

    private int mrIndex = show_updateInfo;//默认选中首页

    private int index = -100;// 记录当前的选项
    /**
     * 上一次界面 onSaveInstanceState 之前的tab被选中的状态 key 和 value
     */
    private static final String PRV_SELINDEX = "PREV_SELINDEX";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_operate);
        //测试
        //test();
        fragmentManager = getSupportFragmentManager();
        //防止app闪退后fragment重叠
        if (savedInstanceState != null) {
            //读取上一次界面Save的时候tab选中的状态
            mrIndex = savedInstanceState.getInt(PRV_SELINDEX, mrIndex);

            updateInfoFragment = (UpdateInfoFragment) fragmentManager.findFragmentByTag(FRAGMENT_TAG[0]);
            lookStatusFragment = (LookStatusFragment) fragmentManager.findFragmentByTag(FRAGMENT_TAG[1]);
        }

        //初始化
        initView();
    }

    @Override
    protected void onSaveInstanceState(Bundle outState) {
        outState.putInt(PRV_SELINDEX, mrIndex);
        super.onSaveInstanceState(outState);
    }

    protected void initView() {
        //获得RadioGroup控件
        mRgGroup = (RadioGroup) findViewById(R.id.operate_rg_group);
        //选择设置Fragment
        setTabSelection(show_updateInfo);
        //点击事件
        mRgGroup.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(RadioGroup radioGroup, int checkedId) {
                switch (checkedId) {
                    case R.id.operate_rb_info://修改信息
                        setTabSelection(show_updateInfo);
                        break;
                    case R.id.operate_rb_status://查看状态
                        setTabSelection(show_lookStatus);
                        break;
                    default:
                        Toast.makeText(OperateActivity.this, "RadioButton is not found. Ths. ", Toast.LENGTH_SHORT).show();
                        break;
                }
            }
        });
    }

    /**
     * 根据传入的index参数来设置选中的tab页。
     *
     * @param id 传入的选择的fragment
     */
    private void setTabSelection(int id) {
        if (id == index) {
            return;
        }
        index = id;
        // 开启一个Fragment事务
        FragmentTransaction transaction = fragmentManager.beginTransaction();

        // 设置切换动画
        transaction.setTransition(FragmentTransaction.TRANSIT_FRAGMENT_FADE);
        // 先隐藏掉所有的Fragment，以防止有多个Fragment显示在界面上的情况
        hideFragments(transaction);
        switch (index) {
            case show_updateInfo://修改信息的fragment
                mRgGroup.check(R.id.operate_rb_info);
                if (updateInfoFragment == null) {
                    updateInfoFragment = new UpdateInfoFragment();
                    transaction.add(R.id.operate_gl_containter, updateInfoFragment, FRAGMENT_TAG[index]);
                } else {
                    transaction.show(updateInfoFragment);
                }
                transaction.commit();
                break;
            case show_lookStatus://查看状态的fragment
                mRgGroup.check(R.id.operate_rb_status);
                if (lookStatusFragment == null) {
                    lookStatusFragment = new LookStatusFragment();
                    transaction.add(R.id.operate_gl_containter, lookStatusFragment, FRAGMENT_TAG[index]);
                } else {
                    transaction.show(lookStatusFragment);
                }
                transaction.commit();
                break;
            default:
                Toast.makeText(OperateActivity.this, "Changed was wrong. Ths. ", Toast.LENGTH_SHORT).show();
                break;
        }
    }

    /**
     * 隐藏fragment
     *
     * @param transaction
     */
    private void hideFragments(FragmentTransaction transaction) {
        if (updateInfoFragment != null) {
            transaction.hide(updateInfoFragment);
        }
        if (lookStatusFragment != null) {
            transaction.hide(lookStatusFragment);
        }
    }
}
