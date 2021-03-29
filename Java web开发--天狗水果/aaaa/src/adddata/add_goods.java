package adddata;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import data.Page;
import data.goods_data;
import dbutil.DBconn;

public class add_goods {

	//私有类，无法被创建	
	private add_goods() {		
	}
		
	//加载商品数据
	public static List<goods_data> addgoodsdata(){
		DBconn con=new DBconn();
		List<goods_data> goods = new ArrayList<>();
		String sql = "select * from goods";
		 ResultSet rs=con.execQuery(sql,new Object[]{});
		 try{
	            while(rs.next()) {
	                goods.add(new goods_data(rs.getString(1),rs.getString(2),rs.getFloat(3),rs.getInt(4),rs.getString(5)));}
	        }catch (SQLException e){
	        	e.printStackTrace();
	        }finally{
		   con.closeConn();
		  }
		 return goods;
	}
	
	//查询有多少页
	public static int getPage() {
		Page page =new Page();
		int count = totalpage();
		int pageSize = page.getPageSize();
		int total = count%pageSize==0?count/pageSize:count/pageSize+1;
		//page.setTotalpage(total);
		return total;
	}
	
	//分页显示
	public static List<goods_data> getGoodspage(int pageIndex,int pageSize){
		int startPage = pageSize*(pageIndex-1);
		List<goods_data> goods = new ArrayList<>();
		DBconn con=new DBconn();
		String sql ="select * from goods order by goods_id desc limit ?,?";
		try {
			ResultSet rs=con.execQuery(sql,new Object[]{startPage,pageSize});
			 while(rs.next()) {
	                goods.add(new goods_data(rs.getString(1),rs.getString(2),rs.getFloat(3),rs.getInt(4),rs.getString(5)));}
		}catch (SQLException e){
        	e.printStackTrace();
        }finally{
	   con.closeConn();
	  }
		return goods;
	}
	
	//返回商品总数
	public static int totalpage() {
		DBconn conn =new DBconn();
		ResultSet rs = null;
		int count = 0;
		String sql ="select count(*) from goods";
		try {
			rs=conn.execQuery(sql,new Object[]{});
			if(rs.next()) {
				count=rs.getInt(1);
			}
		}catch (SQLException e){
        	e.printStackTrace();
        }finally{
	   conn.closeConn();
	  }

		return count;		
	}
}
