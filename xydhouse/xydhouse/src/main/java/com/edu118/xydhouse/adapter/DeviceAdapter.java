package com.edu118.xydhouse.adapter;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

import com.edu118.xydhouse.R;

import com.edu118.xydhouse.bean.DeviceBean;

import java.util.List;

/**
 * Created by Administrator on 2019/12/17 0017.
 */

public class DeviceAdapter extends BaseAdapter{

    private final Context context;
    private final List<DeviceBean> deviceDatas;

    public DeviceAdapter(Context context, List<DeviceBean> deviceDatas) {
        this.context = context;
        this.deviceDatas = deviceDatas;
    }
//item个数
    @Override
    public int getCount() {
        return deviceDatas.size();
    }
//item对象
    @Override
    public Object getItem(int i) {
        return deviceDatas.get(i);
    }
//当前的位置id
    @Override
    public long getItemId(int i) {
        return i;
    }
    //item布局视图
    @Override
    public View getView(int i, View view, ViewGroup viewGroup) {
        ViewHolder viewHolder = null;
        //判断
        if(view == null){
            view = LayoutInflater.from(context).inflate(R.layout.layout_lv_list_item,viewGroup,false);
            viewHolder = new ViewHolder();
            viewHolder.tvName = (TextView) view.findViewById(R.id.device_list_lv_item_name);
            viewHolder.tvId = (TextView) view.findViewById(R.id.device_list_lv_item_id);
            view.setTag(viewHolder);
        }
        //获得值
        viewHolder = (ViewHolder) view.getTag();
        //获得item对象
        DeviceBean bean = (DeviceBean) getItem(i);

        viewHolder.tvName.setText(bean.getDeviceName());
        viewHolder.tvId.setText(bean.getDeviceId());

        return view;
    }
    //第3方的类  ViewHolder
    private class ViewHolder{
        //名称   findView...()
        private TextView tvName;
        //id
        private TextView tvId;
    }


}
