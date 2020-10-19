package com.edu118.xydhouse.db;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

/**
 * author: Jimy
 * <p>
 * time: 14:52
 * <p>
 * email: 1650015040@qq.com
 */
public class MySqliteOpenHelper extends SQLiteOpenHelper {
    public MySqliteOpenHelper(Context context) {
        /**
         * @param context 上下文对象
         * @param name  数据库的名字，以.db结尾
         * @param factory  游标工厂 ,一般使用默认的即可：null
         * @param version  数据的版本,第一次运行可以设置为 1
         */
        super(context, DbConstant.DB_NAME, null, 1);
    }

    @Override
    public void onCreate(SQLiteDatabase sqLiteDatabase) {
        //执行表的操作
        //_id为自动增长int、devicename为varchar、deviceid为varchar

        String sql = "create table " + DbConstant.TABLE_NAME + "(" +
                DbConstant.COLUMN_ID + " integer primary key autoincrement, " +
                DbConstant.COLUMN_DEVICE_NAME + " varchar(20), " +
                DbConstant.COLUMN_DEVICE_ID + " varchar(30)" +
                ")";
        sqLiteDatabase.execSQL(sql);

        //添加一条默认的数据
        String defaultSql = "insert into " + DbConstant.TABLE_NAME
                + "(" + DbConstant.COLUMN_DEVICE_NAME + "," + DbConstant.COLUMN_DEVICE_ID + ") "
                + "values('默认ID','0X432032213934424d066fff31')";
        sqLiteDatabase.execSQL(defaultSql);
    }

    @Override
    public void onUpgrade(SQLiteDatabase sqLiteDatabase, int i, int i1) {
        //数据库更新时的操作
    }
}