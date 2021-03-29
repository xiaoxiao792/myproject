package com.edu118.xydhouse.util;

import android.util.Log;

import com.edu118.xydhouse.listener.IRequestDataListener;

import org.xutils.HttpManager;
import org.xutils.common.Callback;
import org.xutils.http.RequestParams;
import org.xutils.x;

import java.util.Map;
import java.util.Set;

/**
 * author: Jimy
 * <p>
 * time: 23:56
 * <p>
 * email: 1650015040@qq.com
 */
public class HttpUtil {
    //xUtils网络加载对象
    private HttpManager mHttpManager;

    /**
     * 单例模式
     */
    private HttpUtil() {
        /**
         * xUtils网络加载对象
         */
        mHttpManager = x.http();
    }

    //创建对象
    private static HttpUtil mHttp = null;

    //向外提供访问方法
    public static HttpUtil getInstance() {
        if (mHttp == null) {
            synchronized (HttpUtil.class) {
                //双重锁
                if (mHttp == null) {
                    mHttp = new HttpUtil();
                }
            }
        }
        return mHttp;
    }

    /**
     * xUtils下的x.http()请求--GET
     *
     * @param uri      请求的url网络地址
     * @param params   请求的参数--可为null
     *                 注：此处为Map<String,String>（key-value均为String类型）
     * @param listener 接口回调：
     *                 onRequestSuccess()请求成功； onRequestFailure()请求失败
     */
    public void doxUtilsHttpRequestByGet(String uri,
                                         Map<String, String> params,
                                         final IRequestDataListener listener) {
        //请求参数
        final RequestParams requestParams = new RequestParams(uri);
        if (params != null) {
            //处理Map集合
            Set<Map.Entry<String, String>> entries = params.entrySet();
            //遍历Set集合
            for (Map.Entry<String, String> entry : entries) {
                //key-value
                //参数名
                String key = entry.getKey();
                //参数值
                String value = entry.getValue();
                //非null处理
//                if (value != null
//                        && !value.equals("")) {
                //TODO：0611 --去掉非""
                if (value != null) {
                    //添加参数
                    requestParams.addBodyParameter(key, value);
                }
            }
        }
        Log.e("Get请求封装", "拼接网址:" + requestParams);

        //GET请求数据
        mHttpManager.get(requestParams, new Callback.CommonCallback<String>() {
            //请求成功
            @Override
            public void onSuccess(String result) {
                if (listener != null) {
                    //成功
                    listener.onRequestSuccess(result);
                }
            }

            //请求失败
            @Override
            public void onError(Throwable ex, boolean isOnCallback) {
                if (listener != null) {
                    //失败
                    listener.onRequestFailure(ex.getMessage());
                }
            }

            @Override
            public void onCancelled(CancelledException cex) {

            }

            @Override
            public void onFinished() {

            }
        });
    }

    /**
     * xUtils下的x.http()请求--POST
     *
     * @param uri      请求的url网络地址
     * @param params   请求的参数--可为null
     *                 注：此处为Map<String,String>（key-value均为String类型）
     * @param listener 接口回调：
     *                 onRequestSuccess()请求成功； onRequestFailure()请求失败
     */
    public void doxUtilsHttpRequestByPost(String uri,
                                          Map<String, String> params,
                                          final IRequestDataListener listener) {
        //请求参数
        RequestParams requestParams = new RequestParams(uri);
        if (params != null) {
            //处理Map集合
            Set<Map.Entry<String, String>> entries = params.entrySet();
            //遍历Set集合
            for (Map.Entry<String, String> entry : entries) {
                //key-value
                //参数名
                String key = entry.getKey();
                //参数值
                String value = entry.getValue();
                //非null处理
                if (value != null
                        && !value.equals("")) {
                    //添加参数
                    requestParams.addBodyParameter(key, value);
                }
            }
        }

        //GET请求数据
        mHttpManager.post(requestParams, new Callback.CommonCallback<String>() {
            //请求成功
            @Override
            public void onSuccess(String result) {
                if (listener != null) {
                    //成功
                    listener.onRequestSuccess(result);
                }
            }

            //请求失败
            @Override
            public void onError(Throwable ex, boolean isOnCallback) {
                if (listener != null) {
                    //失败
                    listener.onRequestFailure(ex.getMessage());
                }
            }

            @Override
            public void onCancelled(CancelledException cex) {

            }

            @Override
            public void onFinished() {

            }
        });
    }
}