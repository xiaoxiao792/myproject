package com.edu118.xydhouse.base;

import android.app.Application;

import com.edu118.xydhouse.util.HttpUtil;

import org.xutils.x;

/**
 * author: Jimy
 * <p>
 * time: 23:55
 * <p>
 * email: 1650015040@qq.com
 */
public class BaseApplication extends Application {

    private static HttpUtil httpUtil;

    @Override
    public void onCreate() {
        super.onCreate();

        /**
         * 初始化xUtils框架
         */
        x.Ext.init(this);
        /**
         * 也可以设置Debug为true
         */
        x.Ext.setDebug(true);

        //获取HttpUtil对象
        httpUtil = HttpUtil.getInstance();
    }

    /**
     * 获取HttpUtil对象
     *
     * @return
     */
    public static HttpUtil getHttpUtil() {
        return httpUtil;
    }
}