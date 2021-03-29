package updata;

import java.util.List;

import tools.time_tool;
import adddata.add_cart;
import adddata.add_user;
import data.cart_data;
import data.cart_goods_data;
import data.user_data;
import dbutil.DBconn;

public class updata_sql {
		
	//私有类，无法被创建
	private updata_sql(){
	}
	
	//注册插入
	public static boolean updateuser(String name, String pwd, String email){
		  
		  DBconn con=new DBconn();
		  String strSQL="insert into user (user_name, user_passwd,user_power, user_email) value (?, ?, ?,?);";
		  int flag =con.execOther(strSQL,new Object[]{name, pwd, 1,email});
		  try{
		   while(flag > 0){
			   return true;			   
		   }
		  } catch(Exception e){
			  e.printStackTrace();
			  return false;
		  }finally{
		   con.closeConn();
		  }
		return false;
		  
	}
	
	//购物车添加（包含重复添加判断功能）
	public static boolean updatacart(String goods_id,String user_name){
		DBconn con=new DBconn();
		String user_id = "";
		int flag = 0;
		List<user_data> user = add_user.adduserdata();
		for (user_data c:user) {
			if(c.getUser_id().equals(user_name))
				user_id = c.getUser_id();
		}
		List<cart_data> cart = add_cart.addcartdata();
		String strSQL="insert into cart (user_id, goods_id,goods_num) value (?, ?, ?);";
		String sql="update cart set goods_num = goods_num+1 where cart_id =?;";
		for(cart_data d:cart){			
			if(d.getUser_id().equals(user_id)&&d.getGoods_id().equals(goods_id)){
				flag = con.execOther(sql,new Object[]{d.getCart_id()});
			}
		}
		if(flag==0){
			flag =con.execOther(strSQL,new Object[]{user_id,goods_id, 1});
		}
		  try{
			   while(flag > 0){
				   return true;			   
			   }
			  } catch(Exception e){
				  e.printStackTrace();
				  return false;
			  }finally{
			   con.closeConn();
			  }
			return false;
	}
	
	//购物车数量显示改变判断
	public static int updata_cart_num(String goods_id,int cart_num,String user_name){
		String user_id = "";
		List<user_data> user = add_user.adduserdata();
		for (user_data c:user) {
			if(c.getUser_id().equals(user_name))
				user_id = c.getUser_id();
		}
		List<cart_data> cart = add_cart.addcartdata();
		for(cart_data d:cart){			
			if(d.getUser_id().equals(user_id)&&d.getGoods_id().equals(goods_id)){
				return cart_num;
			}
		}
		cart_num = cart_num+1;
		return cart_num;
	}
	
	//根据购物车生成订单(淘汰)
	public static boolean cart_to_order(String user_name,List<cart_data> cart){
		DBconn con=new DBconn();
		String user_id = "";
		List<user_data> user = add_user.adduserdata();
		for (user_data c:user) {
			if(c.getUser_id().equals(user_name))
				user_id = c.getUser_id();
		}
		String order_top = time_tool.getorder_id();
		String order_time = time_tool.gettime2();
		String strSQL="insert into order (order_id, user_id,order_stata,order_time) value (?, ?, ?,?);";
		int flag =con.execOther(strSQL,new Object[]{order_top,user_id, 1,order_time});
		if(flag==1){
			String sql="insert into order (order_id, user_id,goods_id,goods_num,order_stata,order_time,order_top) value (?, ?, ?,?,?,?,?);";
			for(cart_data a:cart){
				con.execOther(sql,new Object[]{time_tool.getorder_id(),user_id,a.getGoods_id(),a.getGoods_num(),1,order_time,order_top});
			}
		}
		  try{
			   while(flag > 0){
				   return true;			   
			   }
			  } catch(Exception e){
				  e.printStackTrace();
				  return false;
			  }finally{
			   con.closeConn();
			  }
		return false;
	}
	
	//修改订单状态（从未发货到已发货）
	public static boolean changeorder(String orders_id){
		DBconn con=new DBconn();
		String strSQL="update `order`set order_stata = 2 where order_id =?;";
		String sql="update `order`set order_stata = 2 where order_top =?;";
		con.execOther(strSQL,new Object[]{orders_id});
		int flag =con.execOther(sql,new Object[]{orders_id});
	    try{
			while(flag > 0){
				return true;			   
		    }
		} catch(Exception e){
			e.printStackTrace();
				return false;
		}finally{
			con.closeConn();
		}
		return false;
	}
	
	//修改订单状态（从已发货到已收货）
	public static boolean changeorder1(String orders_id){
		DBconn con=new DBconn();
		String strSQL="update `order` set order_stata = 3 where order_id =?;";
		String sql="update `order` set order_stata = 3 where order_top =?;";
		con.execOther(strSQL,new Object[]{orders_id});
		int flag =con.execOther(sql,new Object[]{orders_id});
	    try{
			while(flag > 0){
				return true;			   
		    }
		} catch(Exception e){
			e.printStackTrace();
				return false;
		}finally{
			con.closeConn();
		}
		return false;
	}
	
	//商品添加
	public static boolean addgoods(String goods_name, Float goods_price, int goods_class,String goods_img) {
		  DBconn con=new DBconn();
		  String strSQL="insert into goods (goods_name, goods_price,goods_class, goods_img) value (?, ?, ?,?);";
		  int flag =con.execOther(strSQL,new Object[]{goods_name, goods_price,goods_class, goods_img});
		  try{
		   while(flag > 0){
			   return true;			   
		   }
		  } catch(Exception e){
			  e.printStackTrace();
			  return false;
		  }finally{
		   con.closeConn();
		  }
		return false;
	}
	
	//商品修改
	public static boolean updatagoods(String goods_id,String goods_name,String goods_img,int goods_class,Float goods_price) {
		  DBconn con=new DBconn();
		  String strSQL="update goods set goods_name = ?,goods_price = ?,goods_class = ?,goods_img = ? where goods_id =?;";
		  int flag =con.execOther(strSQL,new Object[]{goods_name,goods_price,goods_class,goods_img,goods_id});
		  try{
		   while(flag > 0){
			   return true;			   
		   }
		  } catch(Exception e){
			  e.printStackTrace();
			  return false;
		  }finally{
		   con.closeConn();
		  }
		return false;
	}
	
	//商品删除
	public static boolean delgoods(String goods_id) {
		  DBconn con=new DBconn();
		  String strSQL="delete from goods where goods_id = ?;";
		  int flag =con.execOther(strSQL,new Object[]{goods_id});
		  try{
		   while(flag > 0){
			   return true;			   
		   }
		  } catch(Exception e){
			  e.printStackTrace();
			  return false;
		  }finally{
		   con.closeConn();
		  }
		return false;
	}
	
	//根据购物车生成订单
	public static boolean cart_to_order2(String user_name,List<cart_goods_data> cart){
		DBconn con=new DBconn();
		String user_id = "";
		List<user_data> user = add_user.adduserdata();
		for (user_data c:user) {
			if(c.getUser_id().equals(user_name))
				user_id = c.getUser_id();
		}
		String order_top = time_tool.getorder_id();
		String order_time = time_tool.gettime2();
		float price = 0;
		for(cart_goods_data b:cart){
			price = price+b.getGoods().getGoods_price()*b.getCart().getGoods_num();
		}
		String strSQL="insert into `order` (order_id, user_id,order_stata,order_time,order_price) value (?, ?, ?,?,?);";
		int flag =con.execOther(strSQL,new Object[]{order_top,user_id, 1,order_time,price});
		if(flag==1){
			String sql="insert into `order` (order_id, user_id,goods_id,goods_num,order_stata,order_time,order_top,order_price) value (?,?, ?, ?,?,?,?,?);";
			for(cart_goods_data a:cart){
				con.execOther(sql,new Object[]{time_tool.getorder_id(),user_id,a.getCart().getGoods_id(),
						a.getCart().getGoods_num(),1,order_time,order_top,price});
			}
		}
		  try{
			   while(flag > 0){
				   return true;			   
			   }
			  } catch(Exception e){
				  e.printStackTrace();
				  return false;
			  }finally{
			   con.closeConn();
			  }
		return false;
	}
	
	//--
	public static boolean delcart(String goods_id,String user_name){
		DBconn con=new DBconn();
		String user_id = "";
		int flag = 0;
		List<user_data> user = add_user.adduserdata();
		for (user_data c:user) {
			if(c.getUser_id().equals(user_name))
				user_id = c.getUser_id();
		}
		List<cart_data> cart = add_cart.addcartdata();
		String strSQL="insert into cart (user_id, goods_id,goods_num) value (?, ?, ?);";
		String sql="update cart set goods_num = goods_num-1 where cart_id =?;";
		for(cart_data d:cart){			
			if(d.getUser_id().equals(user_id)&&d.getGoods_id().equals(goods_id)){
				flag = con.execOther(sql,new Object[]{d.getCart_id()});
			}
		}
		if(flag==0){
			flag =con.execOther(strSQL,new Object[]{user_id,goods_id, 1});
		}
		  try{
			   while(flag > 0){
				   return true;			   
			   }
			  } catch(Exception e){
				  e.printStackTrace();
				  return false;
			  }finally{
			   con.closeConn();
			  }
			return false;
	}
	public static boolean delcart2(String goods_id,String user_name){
		DBconn con=new DBconn();
		String user_id = "";
		int flag = 0;
		List<user_data> user = add_user.adduserdata();
		for (user_data c:user) {
			if(c.getUser_id().equals(user_name))
				user_id = c.getUser_id();
		}
		List<cart_data> cart = add_cart.addcartdata();
		String sql="delete  from cart  where cart_id =?;";
		for(cart_data d:cart){			
			if(d.getUser_id().equals(user_id)&&d.getGoods_id().equals(goods_id)){
				flag = con.execOther(sql,new Object[]{d.getCart_id()});
			}
		}

		  try{
			   while(flag > 0){
				   return true;			   
			   }
			  } catch(Exception e){
				  e.printStackTrace();
				  return false;
			  }finally{
			   con.closeConn();
			  }
			return false;
	}
}
