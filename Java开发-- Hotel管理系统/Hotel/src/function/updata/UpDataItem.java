package function.updata;

import java.util.List;
import dataobject.Client;
import dataobject.OrderData;
import dataobject.ReserveData;
import dataobject.Room;
import function.add.AddItem;
import hotel.Main;
import readywork.AddData;
import sql.SqlStore;
import sql.SqlStore.Producer;
import sql.SqlStore.SqlQueue;

public class UpDataItem {
	
	public static SqlStore sqlstore = Main.getSqlstore();
	public static SqlQueue sqlqueue = Main.getSqlqueue();
	public static Producer producer = Main.getProducer();
	
	public static List<Client> updata1 = AddData.getList1();
	public static List<Room> updata2 = AddData.getList2();
	public static List<OrderData> updata3 = AddData.getList3();
	public static List<ReserveData> updata4 = AddData.getList4();
	
	
	public UpDataItem() {
	}
	
	public static int updataroom(int roomid ,int newvalue) {
		String colname = "roomstata";
		String arg0 = "update room set "+colname+"="+newvalue+" where roomid = "+roomid;
		for(Room a:updata2 ) {
			if(a.getRoomid()==roomid)
				a.setRoomstata(newvalue);
		}
		producer.addsql(arg0);
		return 1;
	}
	
	public static int updataclient(int col ,int clientid ,String newvalue) {
		
		String colname = "";
		String arg0 = "";
		int clientclassid=10001;
		switch(col) {
	    case 1:return 0;
	    case 2:colname = "clientname";arg0 = "update client set "+colname+"='"+newvalue+"' where clientid = "+clientid;break;
	    case 3:return 0;
	    case 4:return 0;
	    case 5:return 0;
	    case 6:colname = "clientphone";arg0 = "update client set "+colname+"='"+newvalue+"' where clientid = "+clientid;break;
	    case 7:colname = "clientemail";arg0 = "update client set "+colname+"='"+newvalue+"' where clientid = "+clientid;break;
	    case 8:colname = "clientaddress";arg0 = "update client set "+colname+"='"+newvalue+"' where clientid = "+clientid;break;
	    case 9:
	    	colname = "clientclassid";
	    	switch(newvalue) {
	    	case "普通用户" : clientclassid = 10001;break;
	    	case "vip1用户" : clientclassid = 10002;break;
	    	case "vip2用户" : clientclassid = 10003;break;
	    	case "vip3用户" : clientclassid = 10004;break;
	    	default:break;
	    	}
	    	arg0 = "update client set "+colname+"="+clientclassid+" where clientid = "+clientid;
	    	break;
	    default:break;
		}
		for(Client a:updata1 ) {
			if(a.getClientid()==clientid) {
				switch(col) {
			    case 2:a.setClientname(newvalue);break;
			    case 6:a.setClientphone(newvalue);break;
			    case 7:a.setClientemail(newvalue);break;
			    case 8:a.setClientaddress(newvalue);break;
			    case 9:a.setClientclassname(newvalue);break;
			    default:break;
				}
			}
		}
		producer.addsql(arg0);
		return 1;
	}
	
	public static int updataorder(int col ,int orderid ,int newvalue) {
		
		String colname = "orderdays";
		String arg0 = "";
		switch(col) {
	    case 6:arg0 = "update orderdb set "+colname+"="+newvalue+" where orderid = "+orderid;break;
	    case 9:colname = "orderstata";arg0 = "update orderdb set "+colname+"="+newvalue+" where orderid = "+orderid;break;
	    default:return 0;
		}
		for(OrderData a:updata3 ) {
			if(a.getOrderid()==orderid) {
				switch(col) {
			    case 6:a.setOrderdays(newvalue);break;
			    case 9:a.setOrderstata(newvalue);break;
			    default:break;
				}
			}
		}
		producer.addsql(arg0);
		return 1;
	}
	
	public static int updataorder2(int col ,int orderid ,String newvalue) {
		
		String colname = "orderendtime";
		String arg0 = "";
		switch(col) {
	    case 7:arg0 = "update orderdb set "+colname+"='"+newvalue+"' where orderid = "+orderid;break;
	    default:return 0;
		}
		producer.addsql(arg0);
		return 1;
	}
	
	public static int updataorder3(int col ,int orderid ,double newvalue) {
		
		String colname = "orderprices";
		String arg0 = "";
		switch(col) {
	    case 8:arg0 = "update orderdb set "+colname+"="+newvalue+" where orderid = "+orderid;break;
	    default:return 0;
		}
		producer.addsql(arg0);
		return 1;
	}
	
	public static int updatareserve(int col ,int reserveid ,String newvalue) {
		
		String colname = "";
		String arg0 = "";
		switch(col) {
	    case 6:colname = "starttime";arg0 = "update reserve set "+colname+"='"+newvalue+"' where reserveid = "+reserveid;break;
//	    case 6:colname = "reservedays";arg0 = "update reserve set "+colname+"="+newnum+" where reserveid = "+reserveid;break;
//	    case 10:colname = "reservestata";arg0 = "update reserve set "+colname+"="+newnum+" where reserveid = "+reserveid;break;
	    default:return 0;
		}
		for(ReserveData a:updata4 ) {
			if(a.getReserveid()==reserveid) {
				switch(col) {
				case 6:a.setStarttime(newvalue);break;
//				case 6:a.setReservedays(newnum);break;
//			    case 10:
//			    	a.setReservestata(newnum);
//			    	if(newnum == 3)
//			    		AddItem.addorderdata(a.getClientname(), a.getRoomnum(), a.getRoomname(), a.getReservedays(), a.getRemark());
//			    	break;
			    default:break;
				}
			}
		}
		producer.addsql(arg0);
		return 1;
	}
	
	@SuppressWarnings("unused")
	public static int updatareserve1(int col ,int reserveid ,int newnum) {
		
		String colname = "";
		String arg0 = "";
		int clientnumberid;
		switch(col) {
//	    case 5:colname = "starttime";arg0 = "update reserve set "+colname+"='"+newvalue+"' where reserveid = "+reserveid;break;
	    case 7:colname = "reservedays";arg0 = "update reserve set "+colname+"="+newnum+" where reserveid = "+reserveid;break;
	    case 11:colname = "reservestata";arg0 = "update reserve set "+colname+"="+newnum+" where reserveid = "+reserveid;break;
	    default:return 0;
		}
		for(ReserveData a:updata4 ) {
			if(a.getReserveid()==reserveid) {
				switch(col) {
//				case 5:a.setStarttime(newvalue);break;
				case 7:a.setReservedays(newnum);break;
			    case 11:
			    	a.setReservestata(newnum);
			    	if(newnum == 3) {
			    		UpDataItem.updataroom(a.getRoomname()[0], 3);
			    	}
			    	for(Client e : updata1) {
						if(a.getClientphone().equals(e.getClientphone())) {
							AddItem.addorderdata(e.getClientidnumber(), a.getRoomnum(), a.getRoomname(), a.getReservedays(), a.getRemark());
						}
					}
		    		
			    		break;
			    default:break;
				}
			}
		}
		producer.addsql(arg0);
		return 1;
	}
}
