package system;

import java.util.*;
import java.text.*;     

public class GetTime{
	@SuppressWarnings("unused")
	public String getTime(){
		String systime = "";
		Date now = new Date(); 
		Calendar c = Calendar.getInstance();//可以对每个时间域单独修改
		int year = c.get(Calendar.YEAR); 
		int month = c.get(Calendar.MONTH); 
		int date = c.get(Calendar.DATE); 
		int hour = c.get(Calendar.HOUR_OF_DAY); 
		int minute = c.get(Calendar.MINUTE); 
		int second = c.get(Calendar.SECOND); 
		SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");//可以方便地修改日期格式
		systime = dateFormat.format(now);
		return systime;
	}
}
