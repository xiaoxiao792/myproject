package tools;


import java.text.SimpleDateFormat;
import java.util.Date;



public class time_tool {
	
	//˽���࣬�޷�������
	private time_tool() {		
	}
		
	private static String gettime1(){
//		Data date = new Data();
//		SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMddHHmmssSSSS");
	String systime = "";
	Date now = new Date(); 
	SimpleDateFormat dateFormat = new SimpleDateFormat("yyyyMMddHHmmssSSSS");//���Է�����޸����ڸ�ʽ
	systime = dateFormat.format(now);
	return systime;
//		return sdf.format(date);
	}
	
	//����ʱ��
	public static String gettime2(){
		String systime = "";
		Date now = new Date(); 
		SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");//���Է�����޸����ڸ�ʽ
		systime = dateFormat.format(now);
		return systime;
	}
	
	//���ɶ���
	public static String getorder_id(){
		StringBuffer sb = new StringBuffer();
		sb.append(gettime1());//������
		for (int i = 0; i < 2; i++) {
			sb.append((int)(Math.random()*9));
		}
		return sb.toString();
//		String PREFIX = "DD";
//	    //������ź�׺�����Ĳ��֣�
//		long code=0;
//        code++;
//        String str = new SimpleDateFormat("yyyyMMddHHmmss").format(new Date());
//        long m = Long.parseLong((str)) * 10000;
//        m += code;
//        return PREFIX + m;
	}
}
