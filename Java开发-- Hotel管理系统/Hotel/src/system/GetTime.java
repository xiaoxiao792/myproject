package system;

import java.util.*;
import java.text.*;     

public class GetTime{
	@SuppressWarnings("unused")
	public String getTime(){
		String systime = "";
		Date now = new Date(); 
		Calendar c = Calendar.getInstance();//���Զ�ÿ��ʱ���򵥶��޸�
		int year = c.get(Calendar.YEAR); 
		int month = c.get(Calendar.MONTH); 
		int date = c.get(Calendar.DATE); 
		int hour = c.get(Calendar.HOUR_OF_DAY); 
		int minute = c.get(Calendar.MINUTE); 
		int second = c.get(Calendar.SECOND); 
		SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");//���Է�����޸����ڸ�ʽ
		systime = dateFormat.format(now);
		return systime;
	}
}
