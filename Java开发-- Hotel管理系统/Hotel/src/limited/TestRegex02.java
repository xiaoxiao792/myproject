package limited;

public class TestRegex02 {
	public static boolean isId(String id) {
		String regex = "(^[1-9]\\d{5}(18|19|([23]\\d))\\d{2}((0[1-9])|(10|11|12))(([0-2][1-9])|10|20|30|31)\\d{3}[0-9Xx]$)|(^[1-9]\\d{5}\\d{2}((0[1-9])|(10|11|12))(([0-2][1-9])|10|20|30|31)\\d{2}[0-9Xx]$)";
		if(id.matches(regex)) {
			return true;
		}
		else {
			return false;
		}
	}
}
