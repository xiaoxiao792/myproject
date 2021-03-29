package com.edu118.xydhouse.constant;

/**
 * author: Jimy
 * <p>
 * time: 13:05
 * <p>
 * email: 1650015040@qq.com
 */
public class Constant {
    /**
     * SharedPreferences创建的xml文件名
     */
    public static final String MAIN_SETTING_FILE = "xydsmarthouse";
    /**
     * 是否是第1次使用
     */
    public static final String MAIN_IS_FIRST = "first";

    /**
     * 添加设备页面的常量值:名称
     */
    public static final String ADD_DEVICE_NAME = "devicename";
    /**
     * 添加设备页面的常量值:设备ID
     */
    public static final String ADD_DEVICE_ID = "deviceid";
    /**
     * 从AddDeviceActivity返回到DeviceListActivity的请求码
     */
    public static final int DEVICE_LIST_ACTIVITY_REQUEST_CODE = 1;

    /**
     * 设备id值
     */
    public static final String DEVICE_ID = "device_id";

    /**
     * 查看状态的URL前缀
     * 若要请求数据，还需要添加deviceid参数
     */
    //public static final String LOOK_STATUS_URL = "view-source:http://134.175.80.178:8080/cgi-bin/showstatus.cgi";
    public static final String LOOK_STATUS_URL = "http://134.175.80.178:8080/cgi-bin/showstatus.cgi";

    /**
     * 修改信息的URL前缀
     * 若要请求数据,还需要添加参数如下：
     * deviceid
     * motor_setup
     * motor
     * relay
     * color
     * ok
     */
    public static final String UPDATE_INFO_URL = "http://134.175.80.178:8080/cgi-bin/ctrl.cgi";

    /**
     * 查看状态的URL后的参数值
     * deviceid  设备id
     */
    public static final String PARAMS_DEVICE_ID = "deviceid";

    public static final String UPDATE_INFO_PARAMS_DEVICE_ID = "devid";
    /**
     * 窗帘控制
     * motor_setup
     */
    public static final String PARAMS_MOTOR_SETUP = "motor_setup";
    /**
     * 通风控制
     * motor
     */
    public static final String PARAMS_MOTOR = "motor";
    /**
     * 智能插座
     * relay
     */
    public static final String PARAMS_RELAY = "relay";
    /**
     * 颜色控制
     * color
     */
    public static final String PARAMS_COLOR = "color";
    /**
     * 确认
     * ok
     */
    public static final String PARAMS_OK = "ok";
}