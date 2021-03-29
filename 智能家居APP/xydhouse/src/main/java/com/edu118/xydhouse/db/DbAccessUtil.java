package com.edu118.xydhouse.db;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;


import com.edu118.xydhouse.bean.DeviceBean;

import java.util.ArrayList;
import java.util.List;

import static android.R.attr.id;

/**
 * author: Jimy
 * <p>
 * time: 15:10
 * <p>
 * email: 1650015040@qq.com
 */
public class DbAccessUtil {
    //单例模式
    private static DbAccessUtil dbAccess;
    private final MySqliteOpenHelper mySqliteOpenHelper;

    private DbAccessUtil(Context context) {
        //创建帮助类
        mySqliteOpenHelper = new MySqliteOpenHelper(context);
    }

    public static DbAccessUtil getInstance(Context context) {
        if (dbAccess == null) {
            synchronized (DbAccessUtil.class) {
                if (dbAccess == null) {
                    dbAccess = new DbAccessUtil(context);
                }
            }
        }
        return dbAccess;
    }

    //添加数据
    public void addOneData(DeviceBean deviceBean) {
        //获取一个数据库对象
        SQLiteDatabase db = mySqliteOpenHelper.getReadableDatabase();
        //ContentValues对象
        ContentValues values = new ContentValues();
        //设置值
        values.put(DbConstant.COLUMN_DEVICE_NAME, deviceBean.getDeviceName());
        values.put(DbConstant.COLUMN_DEVICE_ID, deviceBean.getDeviceId());

        //插入数据
        db.insert(DbConstant.TABLE_NAME, null, values);
        //关闭数据库
        db.close();
    }

    //删除一条deviceId为?的数据
    public void deleteDeviceById(String deviceId) {
        SQLiteDatabase db = mySqliteOpenHelper.getReadableDatabase();
        //删除deviceId为?的数据
        db.delete(DbConstant.TABLE_NAME, DbConstant.COLUMN_DEVICE_ID + " = ?", new String[]{deviceId + ""});
        db.close();
    }

    //查询所有
    public List<DeviceBean> queryAllDeviceInfo() {
        SQLiteDatabase db = mySqliteOpenHelper.getReadableDatabase();
        //查询数据库里的所有数据
        Cursor cursor = db.query(DbConstant.TABLE_NAME, null, null, null, null, null, null);
        //创建集合
        List<DeviceBean> devices = new ArrayList<>();
        //查看是否存在下一个
        while (cursor.moveToNext()) {
            //创建对象
            DeviceBean device = new DeviceBean();
            //设置name值
            device.setDeviceName(cursor.getString(cursor.getColumnIndex(DbConstant.COLUMN_DEVICE_NAME)));

            //设置id值
            device.setDeviceId(cursor.getString(cursor.getColumnIndex(DbConstant.COLUMN_DEVICE_ID)));

            //添加到集合中
            devices.add(device);
        }
        //游标和数据库对象都必须close
        //关闭Cursor
        cursor.close();
        db.close();
        return devices;
    }
}