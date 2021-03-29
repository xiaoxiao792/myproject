package adddata;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import data.cart_data;
import dbutil.DBconn;

public class add_cart {

//  业务需求淘汰
//	 public static List<cart_data> cart = new ArrayList<>();
//	
//	 public static List<cart_data> getCart() {
//	 return cart;
//	 }
	
	//私有类，无法被创建
	private add_cart() {		
	}

	//加载购物车数据
	public static List<cart_data> addcartdata() {
		DBconn con = new DBconn();
		List<cart_data> cart = new ArrayList<>();
	    String sql = "select * from cart";
		ResultSet rs = con.execQuery(sql, new Object[] {});
		try {
			while (rs.next()) {
				cart.add(new cart_data(rs.getString(1),rs.getString(2),rs.getString(3),rs.getInt(4)));
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}finally{
			   con.closeConn();
			  }
		return cart;
	}
}
