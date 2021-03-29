package limited;

public class AgeLimited {
	public static boolean isAge(String str) {
		String regex = "^[1-9]\\d?$|^1[0-4]\\d$|^0$|^150$";
		if(str.matches(regex)) {
			return true;
		}
		else {
			return false;
		}
	}
}
