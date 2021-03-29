package com.edu118.xydhouse.bean;

/**
 * author: Jimy
 * <p>
 * time: 15:11
 * <p>
 * email: 1650015040@qq.com
 */
public class DeviceBean {
    private String deviceName;
    private String deviceId;

    public DeviceBean() {
    }

    public DeviceBean(String deviceId, String deviceName) {
        this.deviceId = deviceId;
        this.deviceName = deviceName;
    }

    public String getDeviceName() {
        return deviceName;
    }

    public void setDeviceName(String deviceName) {
        this.deviceName = deviceName;
    }

    public String getDeviceId() {
        return deviceId;
    }

    public void setDeviceId(String deviceId) {
        this.deviceId = deviceId;
    }

    @Override
    public String toString() {
        return "DeviceBean{" +
                "deviceName='" + deviceName + '\'' +
                ", deviceId='" + deviceId + '\'' +
                '}';
    }
}