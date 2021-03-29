package limited;

public class Daylimited {
	public static boolean isDay(String str) {
		String regex = "^\\d{1,3}$";
		if(str.matches(regex)) {
			return true;
		}else {
			return false;
		}
	}
}
