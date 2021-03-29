package tools;


import java.text.SimpleDateFormat;
import java.util.Date;



public class time_tool {
	
	//私有类，无法被创建
	private time_tool() {		
	}
		
	private static String gettime1(){
//		Data date = new Data();
//		SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMddHHmmssSSSS");
	String systime = "";
	Date now = new Date(); 
	SimpleDateFormat dateFormat = new SimpleDateFormat("yyyyMMddHHmmssSSSS");//可以方便地修改日期格式
	systime = dateFormat.format(now);
	return systime;
//		return sdf.format(date);
	}
	
	//生成时间
	public static String gettime2(){
		String systime = "";
		Date now = new Date(); 
		SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");//可以方便地修改日期格式
		systime = dateFormat.format(now);
		return systime;
	}
	
	//生成订单
	public static String getorder_id(){
		StringBuffer sb = new StringBuffer();
		sb.append(gettime1());//订单号
		for (int i = 0; i < 2; i++) {
			sb.append((int)(Math.random()*9));
		}
		return sb.toString();
//		String PREFIX = "DD";
//	    //订单编号后缀（核心部分）
//		long code=0;
//        code++;
//        String str = new SimpleDateFormat("yyyyMMddHHmmss").format(new Date());
//        long m = Long.parseLong((str)) * 10000;
//        m += code;
//        return PREFIX + m;
	}
}
