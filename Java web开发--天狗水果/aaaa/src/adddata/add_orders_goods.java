package adddata;

import java.util.ArrayList;
import java.util.List;
import data.order_goods_data;
import data.orders_goods_data;

public class add_orders_goods {

	public static List<orders_goods_data> addorderdata(String user_name){
		List<orders_goods_data> orders = new ArrayList<>();
		List<order_goods_data> order = add_order_goods.addordergoods(user_name);
		System.out.println(order);
		for(order_goods_data b: order){
			System.out.println(b.getOrder().getOrder_top());
			if(b.getOrder().getOrder_top().equals("0")){
				List<order_goods_data> g = new ArrayList<>();
				for(order_goods_data f: order){
					if(f.getOrder().getOrder_top().equals(b.getOrder().getOrder_id())){
						g.add(f);
					}
				}
				System.out.println("g"+g);
				orders_goods_data e = new orders_goods_data(b.getOrder().getOrder_id(), b.getOrder().getUser_id(), b.getOrder().getOrder_stata(), b.getOrder().getOrser_time(),b.getOrder().getOrder_price(), g);
				orders.add(e);
			}
		}
		return orders;
	}
	
	public static List<orders_goods_data> addorderdata2(){
		List<orders_goods_data> orders = new ArrayList<>();
		List<order_goods_data> order = add_order_goods.addordergoods2();
		for(order_goods_data b: order){
			if(b.getOrder().getOrder_top().equals("0")){
				List<order_goods_data> g = new ArrayList<>();
				for(order_goods_data f: order){
					if(f.getOrder().getOrder_top().equals(b.getOrder().getOrder_id())){
						g.add(f);
					}
				}
				orders_goods_data e = new orders_goods_data(b.getOrder().getOrder_id(), b.getOrder().getUser_id(), b.getOrder().getOrder_stata(), b.getOrder().getOrser_time(),b.getOrder().getOrder_price(), g);
				orders.add(e);
			}
		}
		return orders;
	}
	
	
}
