package adddata;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import data.order_data;
import dbutil.DBconn;

public class add_order {
	
	//私有类，无法被创建
	private add_order() {		
	}
	
	//加载订单数据（与数据库同步）
	public static List<order_data> addorderdata(){
		DBconn con = new DBconn();
		List<order_data> order = new ArrayList<>();
		String sql = "SELECT * FROM `order`;";
		ResultSet rs = con.execQuery(sql, new Object[]{});
		System.out.println(rs);
		try{
            while(rs.next()) {
            	//String order_id,String user_id,String goods_id,int goods_num,
    			//int order_stata,String order_time,String order_top,float order_price
                order.add(new order_data(rs.getString(1),rs.getString(2),rs.getString(3),rs.getInt(4),rs.getInt(5),rs.getString(6),rs.getString(7),rs.getFloat(8)));}
        }catch (SQLException e){
        	e.printStackTrace();
        }finally{
 		   con.closeConn();
 		  }
		return order;
	}
}
