package function.add;

import java.util.List;
import dataobject.Client;
import dataobject.OrderData;
import dataobject.PowerData;
import dataobject.ReserveData;
import hotel.Main;
import readywork.AddData;
import sql.SqlStore;
import sql.SqlStore.Producer;
import sql.SqlStore.SqlQueue;
import system.GetTime;

public class AddItem {
	
	public static SqlStore sqlstore = Main.getSqlstore();
	public static SqlQueue sqlqueue = Main.getSqlqueue();
	public static Producer producer = Main.getProducer();
	
	public static List<PowerData> add0 = AddData.getList0();
	public static List<Client> add1 = AddData.getList1();
	public static List<OrderData> add3 = AddData.getList3();
	public static List<ReserveData> add4 = AddData.getList4();
	
	public AddItem() {		
	}
	
	public static void addclient(String clientname, String clientidnumber, int clientsex, int clientage, String clientphone, String clientemail,
			String clientaddress,String clientclassname) {
		int clientid = Client.getPointid();
		String arg0 = "insert into client values(0,10001,'"+clientsex+"','"+clientphone+"','"+clientaddress+"','"+clientidnumber+"','"+clientname+"','"+clientemail+"',"+clientage+")";
		add1.add(new Client(clientid,clientname,clientidnumber,clientsex,clientage,clientphone,clientemail,clientaddress,clientclassname));
		producer.addsql(arg0);
	}
	
	public static void addorderdata(String clientidnumber ,int roomnum ,int[] roomname,int orderdays,String remark) {
		int orderid = OrderData.getPointid();
		int clientid = 0;
		String powerid = "";
		String orderbegintime = new GetTime().getTime();
		int orderstata = 1;
		String clientname = "";
		String clientphone = "";
		String clientemail = "";
		for(Client e : add1) {
			if(clientidnumber.equals(e.getClientidnumber())) {
				clientid = e.getClientid();
				clientname = e.getClientname();
				clientphone = e.getClientphone();
				clientemail = e.getClientemail();
				break;
			}
		}
		for(PowerData e : add0) {
			if(e.getIslogin()==1) {
				powerid = e.getPowerid();
				break;
			}
		}
		for(int i = 0;i<roomnum;i++) {
			int roomid = roomname[i];
			String arg0 = "insert into orderdb(orderid,clientid,roomnum,roomid,orderdays,orderbegintime,orderstata,powerid,remark) values(0,"+clientid+","+(roomnum-i)+","+roomid+","+orderdays+",'"+orderbegintime+"',"+orderstata+",'"+powerid+"','"+remark+"')";
			OrderData.setPointid();
			producer.addsql(arg0);
		}
		add3.add(new OrderData(orderid ,clientname ,orderbegintime ,clientphone ,clientemail ,orderdays ,roomnum ,roomname ,orderstata ,remark));
	}
	
	public static void addreservedata(String clientidnumber ,String starttime ,int roomnum ,int[] roomname,int reservedays,String remark) {
		int reserveid = ReserveData.getPointid();
		int clientid = 0;
		String powerid = "";
		String reservetime = new GetTime().getTime();
		int reservestata = 1;
		String clientname = "";
		String clientphone = "";
		String clientemail = "";
		for(Client e : add1) {
			if(clientidnumber.equals(e.getClientidnumber())) {
				clientid = e.getClientid();
				clientname = e.getClientname();
				clientphone = e.getClientphone();
				clientemail = e.getClientemail();
				break;
			}
		}
		for(PowerData e : add0) {
			if(e.getIslogin()==1) {
				powerid = e.getPowerid();
				break;
			}
		}
		for(int i = 0;i<roomnum;i++) {
			int roomid = roomname[i];
			String arg0 = "insert into reserve(reserveid,clientid,roomnum,isroom,roomid,reservedays,reservetime,starttime,reservestata,powerid,remark) "
					+ "values(0,"+clientid+","+(roomnum-i)+","+1+","+roomid+","+reservedays+",'"+reservetime+"','"+starttime+"',"+reservestata+",'"+powerid+"','"+remark+"')";
			ReserveData.setPointid();
			producer.addsql(arg0);
		}
		add4.add(new ReserveData(reserveid ,clientname ,reservetime ,clientphone ,clientemail ,starttime ,
				reservedays ,1,roomnum ,roomname ,reservestata ,remark));
	}
	
}
