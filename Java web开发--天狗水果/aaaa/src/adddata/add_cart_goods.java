package adddata;

import java.util.ArrayList;
import java.util.List;

import data.cart_data;
import data.cart_goods_data;
import data.goods_data;
import data.user_data;

public class add_cart_goods {
	
	private add_cart_goods() {		
	}
	
	public static List<cart_goods_data> addcartgoods(String user_name){
		String user_id = "";
		List<user_data> user = add_user.adduserdata();
		for (user_data c:user) {
			if(c.getUser_id().equals(user_name))
				user_id = c.getUser_id();
		}
		List<cart_goods_data> cart_goods = new ArrayList<>();
		List<cart_data> cart = add_cart.addcartdata();
		List<goods_data> goods = add_goods.addgoodsdata();
		for(cart_data a:cart){			
			if(a.getUser_id().equals(user_id)){
				for(goods_data b:goods){
					if(b.getGoods_id().equals(a.getGoods_id())){						
						cart_goods_data d = new cart_goods_data(a, b);
						cart_goods.add(d);
					}
				}
			}
		}
		return cart_goods;
	}
}
