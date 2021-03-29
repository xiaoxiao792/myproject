package limited;

public class PhoneLimited {
	public static boolean isPhone(String str) {
		String regex = "^((13[0-9])|(14[5,7])|(15[0-3,5-9])|(17[0,3,5-8])|(18[0-9])|166|198|199|(147))\\d{8}$";
		if(str.matches(regex)) {
			return true;
		}else {
			return false;
		}
	}
}
