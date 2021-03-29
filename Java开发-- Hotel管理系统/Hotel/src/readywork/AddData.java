package readywork;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import dataobject.*;
import sql.*;

public class AddData {
	
	public static List<PowerData> list0 = new ArrayList<>();
	public static List<Client> list1 = new ArrayList<>();
	public static List<Room> list2 = new ArrayList<>();
	public static List<OrderData> list3 = new ArrayList<>();
	public static List<ReserveData> list4 = new ArrayList<>();
	
	public static List<PowerData> getList0() {
		return list0;
	}

	public static List<Client> getList1() {
		return list1;
	}

	public static List<Room> getList2() {
		return list2;
	}

	public static List<OrderData> getList3() {
		return list3;
	}

	public static List<ReserveData> getList4() {
		return list4;
	}

	/**=======================================================================**
	 *		[## public AddData() {} ]:		构造函数
	 *			参数   ：无
	 *			返回值 ：无
	 *			修饰符 ：public
	 *			功能   ：从数据库载入数据信息
	 **=======================================================================**
	 */
	public AddData() {
		addpowerdata();
		addclientdata();
		addroomdata();
		addorderdata();
		addreservedata();
	}
	
	//从数据库获取数据
	public void addpowerdata() {
		String sql = "select * from power";
		ResultSet rs = SqlFunc.query(sql);
		try{
            while(rs.next()) {
                list0.add(new PowerData(rs.getString(1),rs.getString(2),rs.getString(3)));}
        }catch (SQLException e){
        	e.printStackTrace();
        }
	}
	
	public void addclientdata(){
		String sql = "select * from clientdata";
		ResultSet rs = SqlFunc.query(sql);
        try{
            while(rs.next()) {
                list1.add(new Client(rs.getInt(1),rs.getString(2),rs.getString(3),rs.getInt(4),rs.getInt(5),rs.getString(6),rs.getString(7),rs.getString(8),rs.getString(9)));}
        }catch (SQLException e){
        	e.printStackTrace();
        }
	}
	
	public void addroomdata(){
		String sql = "select * from roomdata";
		ResultSet rs = SqlFunc.query(sql);
        try{
            while(rs.next()) {
                list2.add(new Room(rs.getInt(1),rs.getInt(2),rs.getInt(3),rs.getInt(4),rs.getDouble(5)));}
        }catch (SQLException e){
        	e.printStackTrace();
        }
	}
	
	@SuppressWarnings("unused")
	public void addorderdata() {
		String sql = "select * from orderdata";
		ResultSet rs = SqlFunc.query(sql);
		
		int orderid;
		String clientname = "";
		String orderbegintime = "";
		String clientphone = "";
		String clientemail = "";
		int orderdays;
		int roomnum;
		int orderstata;
		String remark = "";
		
		try{
			while(rs.next()) {
				orderid = rs.getInt(1);
				clientname = rs.getString(2);
				orderbegintime = rs.getString(3);
				clientphone = rs.getString(4);
				clientemail = rs.getString(5);
				orderdays = rs.getInt(6);
				roomnum = rs.getInt(7);
				orderstata = rs.getInt(9);
				remark = rs.getString(10);
				int[] roomname = new int[roomnum];
	            for(int i=roomnum;;i--) {
	            	int j = 0;
	            	roomname[j] = rs.getInt(8);
	            	j++;
	            	if(rs.getInt(7)==1) break;
	            	rs.next();
	            	OrderData.setPointid();
	            }
	            list3.add(new OrderData(orderid,clientname,orderbegintime,clientphone,clientemail,orderdays,roomnum,roomname,orderstata,remark));
			}
        }catch (SQLException e){
        	e.printStackTrace();
        }
	}
	
	@SuppressWarnings("unused")
	public void addreservedata() {
		String sql = "select * from reservedata";
		ResultSet rs = SqlFunc.query(sql);
		
		int reserveid;
		String clientname = "";
		String reservetime = "";
		String clientphone = "";
		String clientemail = "";
		String starttime = "";
		int reservedays;
		int isroom;
		int roomnum;
		int reservestata;
		String remark = "";
		
		try{
			while(rs.next()) {
				reserveid = rs.getInt(1);
				clientname = rs.getString(2);
				reservetime = rs.getString(3);
				clientphone = rs.getString(4);
				clientemail = rs.getString(5);
				starttime = rs.getString(6);
				reservedays = rs.getInt(7);
				isroom = rs.getInt(8);
				roomnum = rs.getInt(9);
				reservestata = rs.getInt(11);
				remark = rs.getString(12);
				int[] roomname = new int[roomnum];
	            for(int i=roomnum;;i--) {
	            	int j = 0;
	            	roomname[j] = rs.getInt(10);
	            	j++;
	            	if(rs.getInt(9)==1) break;
	            	rs.next();
	            	ReserveData.setPointid();
	            }
	            list4.add(new ReserveData(reserveid,clientname,reservetime,clientphone,clientemail,starttime,
	        			reservedays,isroom ,roomnum,roomname,reservestata,remark));
			}
        }catch (SQLException e){
        	e.printStackTrace();
        }
	}

}
