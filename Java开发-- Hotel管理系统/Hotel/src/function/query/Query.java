package function.query;

import java.util.ArrayList;
import java.util.List;
import dataobject.Client;
import dataobject.OrderData;
import dataobject.ReserveData;
import dataobject.Room;
import java.util.regex.Pattern;

public class Query {
	
	public static List<Client> query1 = new ArrayList<>();
	public static List<Room> query2 = new ArrayList<>();
	public static List<OrderData> query3 = new ArrayList<>();
	public static List<ReserveData> query4 = new ArrayList<>();
	
	public static boolean stringmatch(String restr,String str) {
		boolean result = false;
		if(str != null && restr != null) {
			result = Pattern.matches(restr, str);
		}
		return result;
	}
	
	public Query() {
	}
	
	public static List<Client> clientquery(List<Client> list , String str) {
		String restr = "^(.*"+str+".*)$";
		for(Client e:list) {
			if(stringmatch(restr,e.getClientname())||stringmatch(restr,e.getClientidnumber())||stringmatch(restr,e.getClientphone())) {
				query1.add(e);
			}
		}
		return query1;
	}
	
	public static List<Room> roomquery(List<Room> list , String str) {
		String restr = "^(.*"+str+".*)$";
		for(Room e:list) {
			if(stringmatch(restr,""+e.getRoomclassid())||stringmatch(restr,""+e.getRoomstata())) {
				query2.add(e);
			}
		}
		return query2;
	}
	
	public static List<OrderData> orderquery(List<OrderData> list , String str) {
		String restr = "^(.*"+str+".*)$";
		for(OrderData e:list) {
			if(stringmatch(restr,""+e.getOrderid())||stringmatch(restr,e.getClientname())||stringmatch(restr,e.getClientphone())||stringmatch(restr,""+e.getRoomname()[0])) {
				query3.add(e);
			}
		}
		return query3;
	}
	
	public static List<ReserveData> reservequery(List<ReserveData> list , String str) {
		String restr = "^(.*"+str+".*)$";
		for(ReserveData e:list) {
			if(stringmatch(restr,""+e.getReserveid())||stringmatch(restr,e.getClientname())||stringmatch(restr,e.getClientphone())||stringmatch(restr,""+e.getRoomname()[0])) {
				query4.add(e);
			}
		}
		return query4;
	}
}
