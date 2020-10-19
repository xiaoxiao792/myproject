package com.edu118.xydhouse;

import android.content.Intent;
import android.content.SharedPreferences;
import android.net.Uri;
import android.os.Handler;
import android.os.Message;
import android.support.v4.view.ViewPager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

import com.edu118.xydhouse.activity.DeviceListActivity;
import com.edu118.xydhouse.adapter.GuideAdapter;
import com.google.android.gms.appindexing.Action;
import com.google.android.gms.appindexing.AppIndex;
import com.google.android.gms.appindexing.Thing;
import com.google.android.gms.common.api.GoogleApiClient;

public class MainActivity extends AppCompatActivity {

    /**
     * ATTENTION: This was auto-generated to implement the App Indexing API.
     * See https://g.co/AppIndexing/AndroidStudio for more information.
     */
    private GoogleApiClient client;
    private Handler mHandler = new Handler(){
        @Override
        public void handleMessage(Message msg) {
            Intent intent = new Intent(MainActivity.this, DeviceListActivity.class);
            startActivity(intent);

            finish();
        }
    } ;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        boolean isFirst = isUseFirst();
        if(isFirst) {
            //显示界面
            setContentView(R.layout.activity_main);
            //封装 --方法
            initViews();
        }else{
            setContentView(R.layout.layout_welcome);
            mHandler.sendEmptyMessageDelayed(1,3000);
        }
        // ATTENTION: This was auto-generated to implement the App Indexing API.
        // See https://g.co/AppIndexing/AndroidStudio for more information.
        client = new GoogleApiClient.Builder(this).addApi(AppIndex.API).build();
    }

    private void initViews() {
        ViewPager mvpPager = (ViewPager) findViewById(R.id.main_vp_pager);

        int[] mImagelds = {R.mipmap.main_sliding1, R.mipmap.main_sliding2, R.mipmap.main_sliding3,
                R.mipmap.main_sliding4};

        GuideAdapter adapter = new GuideAdapter(this,mImagelds);

        mvpPager.setAdapter(adapter);//Null

    }

    public void JumpToNext(View view) {

        Toast.makeText(this, "欢迎你", Toast.LENGTH_SHORT).show();

        SharedPreferences setting = getSharedPreferences("smarthourse",MODE_PRIVATE);
        SharedPreferences.Editor editor = setting.edit();
        editor.putBoolean("first",false);
        editor.commit();

        Intent intent = new Intent(this, DeviceListActivity.class);
        startActivity(intent);

        finish();
    }

    /**
     * ATTENTION: This was auto-generated to implement the App Indexing API.
     * See https://g.co/AppIndexing/AndroidStudio for more information.
     */
    public Action getIndexApiAction() {
        Thing object = new Thing.Builder()
                .setName("Main Page") // TODO: Define a title for the content shown.
                // TODO: Make sure this auto-generated URL is correct.
                .setUrl(Uri.parse("http://[ENTER-YOUR-URL-HERE]"))
                .build();
        return new Action.Builder(Action.TYPE_VIEW)
                .setObject(object)
                .setActionStatus(Action.STATUS_TYPE_COMPLETED)
                .build();
    }

    @Override
    public void onStart() {
        super.onStart();

        // ATTENTION: This was auto-generated to implement the App Indexing API.
        // See https://g.co/AppIndexing/AndroidStudio for more information.
        client.connect();
        AppIndex.AppIndexApi.start(client, getIndexApiAction());
    }

    @Override
    public void onStop() {
        super.onStop();

        // ATTENTION: This was auto-generated to implement the App Indexing API.
        // See https://g.co/AppIndexing/AndroidStudio for more information.
        AppIndex.AppIndexApi.end(client, getIndexApiAction());
        client.disconnect();
    }

    public boolean isUseFirst() {
        SharedPreferences setting = getSharedPreferences("smarthourse",MODE_PRIVATE);
        boolean first = setting.getBoolean("first",true);
        return first;
    }
}
