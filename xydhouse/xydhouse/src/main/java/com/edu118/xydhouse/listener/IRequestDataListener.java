package com.edu118.xydhouse.listener;

/**
 * author: Jimy
 * <p>
 * time: 23:59
 * <p>
 * email: 1650015040@qq.com
 */
public interface IRequestDataListener {
    //请求成功
    void onRequestSuccess(String result);

    //请求失败
    void onRequestFailure(String errorMsg);
}