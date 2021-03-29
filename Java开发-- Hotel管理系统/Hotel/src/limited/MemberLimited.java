package limited;

public class MemberLimited {
	public static boolean isMember(String str) {
		String regex = "^\\d{1,2}$";
		if(str.matches(regex)) {
			return true;
		}else {
			return false;
		}
	}
}
