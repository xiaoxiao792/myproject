package com.edu118.xydhouse.adapter;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.support.v4.view.PagerAdapter;
import android.support.v4.view.ViewPager;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;

import com.edu118.xydhouse.MainActivity;
import com.edu118.xydhouse.activity.DeviceListActivity;

import static android.content.Context.MODE_PRIVATE;

/**
 * Created by Administrator on 2019/12/16 0016.
 */


public class GuideAdapter extends PagerAdapter {
    private final int[] mImageIds;
    private Context mContext;
    public GuideAdapter(Context context, int[] mImagelds) {
        this.mContext = context;
        this.mImageIds = mImagelds;

    }

    @Override
    public int getCount() {
        return mImageIds.length;
    }

    @Override
    public Object instantiateItem(ViewGroup container, int position) {
        ImageView imageView = new ImageView(mContext);

        ViewGroup.LayoutParams ivParams = new ViewGroup.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
        imageView.setLayoutParams(ivParams);

        imageView.setImageResource(mImageIds[position]);

        if(position == (mImageIds.length-1)){
            imageView.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    SharedPreferences setting = mContext.getSharedPreferences("smarthourse",MODE_PRIVATE);
                    SharedPreferences.Editor editor = setting.edit();
                    editor.putBoolean("first",false);
                    editor.commit();

                    Intent intent = new Intent(mContext, DeviceListActivity.class);
                    mContext.startActivity(intent);

                    ((Activity)mContext).finish();
                }
            });
        }

        container.addView(imageView);
        return imageView;
    }

    @Override
    public boolean isViewFromObject(View view, Object object) {
        return view == object;
    }

    @Override
    public void destroyItem(ViewGroup container, int position, Object object) {
        container.removeView((View) object);
    }
}
