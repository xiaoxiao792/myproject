package query;

import java.util.ArrayList;
import java.util.List;
import adddata.add_cart;
import adddata.add_goods;
import adddata.add_user;
import data.cart_data;
import data.goods_data;
import data.user_data;

public class query_data {
	
	//私有类，无法被创建
	private query_data(){
	}
	
	//得到第一种类型商品
	public static List<goods_data> query1_goods(){
		List<goods_data> query = new ArrayList<>();
		List<goods_data> goods = add_goods.addgoodsdata();
		for(goods_data a:goods){
			if (a.getGoods_class()==1)
				query.add(a);
		}
		return query;
	}
	
	//得到第二种类型商品
	public static List<goods_data> query2_goods(){
		List<goods_data> query = new ArrayList<>();
		List<goods_data> goods = add_goods.addgoodsdata();
		for(goods_data a:goods){
			if (a.getGoods_class()==2)
				query.add(a);
		}
		return query;
	}
	
	//得到购物车数量
	public static int query3_cart_num(String user_name){
		String user_id = "";
		List<user_data> user = add_user.adduserdata();
		for (user_data c:user) {
			if(c.getUser_id().equals(user_name))
				user_id = c.getUser_id();
		}
		int cart_num = 0;
		List<cart_data> cart = add_cart.addcartdata();
		for(cart_data a:cart){
			if(a.getUser_id().equals(user_id))
				cart_num += 1;
		}
		return cart_num;
	}
	
	//没用，已淘汰
	public static List<String> query4_cart(String user_id){
		List<cart_data> cart = add_cart.addcartdata();
		List<String> query = new ArrayList<>();
		for (cart_data a:cart) {
			if(a.getUser_id().equals(user_id))
				query.add(a.getGoods_id());
		}
		return query;
	}
	
	//判断登录
	public static int query5_user(String name, String pwd, int state){
		List<user_data> user = add_user.adduserdata();
		for(user_data a:user){
			if(a.getUser_name().equals(name)&&a.getUser_passwd().equals(pwd)&&a.getUser_power() == state)
				return state;
		}
		return 0;
	}
	
	//没用，已淘汰
	public static List<goods_data> query6_goods(List<String> id){
		List<goods_data> query = new ArrayList<>();
		List<goods_data> goods = add_goods.addgoodsdata();
		for(goods_data a:goods){
			for(String b:id){
				if(a.getGoods_id().equals(b))
					query.add(a);
			}
		}
		return query;
	}
	
	//得到用户商品，已淘汰
	public static List<goods_data> query7_goods(String user_name){
		String user_id = "";
		List<user_data> user = add_user.adduserdata();
		for (user_data c:user) {
			if(c.getUser_id().equals(user_name))
				user_id = c.getUser_id();
		}
		List<cart_data> cart = add_cart.addcartdata();
		List<cart_data> query = new ArrayList<>();
		for(cart_data d:cart){
			if(d.getUser_id().equals(user_id))
				query.add(d);
		}
		List<goods_data> query1 = new ArrayList<>();
		List<goods_data> goods = add_goods.addgoodsdata();
		for(goods_data a:goods){
			for(cart_data e:query){
				if(a.getGoods_id().equals(e.getGoods_id()))
					query1.add(a);
			}
		}
		return query1;
	}
	
	//得到用户购物车，已淘汰
	public static List<cart_data> query8_cart(String user_name){
		String user_id = "";
		List<user_data> user = add_user.adduserdata();
		for (user_data c:user) {
			if(c.getUser_id().equals(user_name))
				user_id = c.getUser_id();
		}
		List<cart_data> cart = add_cart.addcartdata();
		List<cart_data> query = new ArrayList<>();
		for(cart_data d:cart){
			if(d.getUser_id().equals(user_id))
				query.add(d);
		}
		return query;
	}
}
