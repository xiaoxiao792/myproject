package limited;

public class TestRegex01{//测试是否符合邮箱格式
	private static String regex = "[0-9a-zA-Z]{1,}@[0-9a-zA-Z]{1,}\\.(com|cn)";  
	public static boolean isRightSytax(String email) {
		if (null == email) {
			return false;        
			}       
		return email.matches(regex);   
		}     
}