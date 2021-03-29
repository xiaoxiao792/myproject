package adddata;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;
import java.util.ArrayList;
import data.user_data;
import dbutil.DBconn;

public class add_user {
	
	//私有类，无法被创建
	private add_user() {		
	}
	
	//加载用户数据
	public static  List<user_data > adduserdata(){
		DBconn con = new DBconn();
		 List<user_data> user = new ArrayList<>();
		String sql = "select * from user";
		ResultSet rs = con.execQuery(sql, new Object[]{});
		try{
            while(rs.next()) {
                user.add(new user_data(rs.getString(1),rs.getString(2),rs.getString(3),rs.getInt(4),rs.getString(5)));}
        }catch (SQLException e){
        	e.printStackTrace();
        }finally{
 		   con.closeConn();
 		  }
		return user;
	}
	
}
