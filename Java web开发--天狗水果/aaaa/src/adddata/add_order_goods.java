package adddata;

import java.util.ArrayList;
import java.util.List;
import data.goods_data;
import data.order_data;
import data.order_goods_data;
import data.user_data;

public class add_order_goods {

	private add_order_goods() {		
	}
	
	//
	public static List<order_goods_data> addordergoods(String user_name){
		String user_id = "";
		List<user_data> user = add_user.adduserdata();
		for (user_data c:user) {
			if(c.getUser_id().equals(user_name))
				user_id = c.getUser_id();
		}
		List<order_goods_data> order_goods = new ArrayList<>();
		List<order_data> cart = add_order.addorderdata();
		List<goods_data> goods = add_goods.addgoodsdata();
		for(order_data a:cart){			
			if(a.getUser_id().equals(user_id)){
				for(goods_data b:goods){
					if(b.getGoods_id().equals(a.getGoods_id())){						
						order_goods_data d = new order_goods_data(b,a);
						order_goods.add(d);
					}
				}
			}
		}
		return order_goods;
	}
	
	//
	public static List<order_goods_data> addordergoods2(){
		List<order_goods_data> order_goods = new ArrayList<>();
		List<order_data> cart = add_order.addorderdata();
		List<goods_data> goods = add_goods.addgoodsdata();
		for(order_data a:cart){			
			for(goods_data b:goods){
				if(b.getGoods_id().equals(a.getGoods_id())){						
					order_goods_data d = new order_goods_data(b,a);
					order_goods.add(d);
				}
			}
		}
		return order_goods;
	}
}
