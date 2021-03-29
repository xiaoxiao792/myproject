package adddata;

import java.util.ArrayList;
import java.util.List;
import data.order_data;
import data.orders_data;
import data.user_data;

public class add_orders {
	
	//私有类，无法被创建
	private add_orders() {		
	}
	
	//加载订单数据（与java同步）
	public List<orders_data> addorderdata(String user_name){
		String user_id = "";
		List<user_data> user = add_user.adduserdata();
		for (user_data c:user) {
			if(c.getUser_id().equals(user_name))
				user_id = c.getUser_id();
		}
		List<orders_data> orders = new ArrayList<>();
		List<order_data> order = add_order.addorderdata();
		List<order_data> user_order = new ArrayList<>();
		for(order_data a:order){
			if(a.getUser_id().equals(user_id))
				user_order.add(a);
		}
		for(order_data b: user_order){
			if(b.getOrder_top().isEmpty()){
				List<order_data> g = new ArrayList<>();
				for(order_data f: user_order){
					if(f.getOrder_top().equals(b.getOrder_id())){
						g.add(f);
					}
				}
				orders_data e = new orders_data(b.getOrder_id(), b.getUser_id(), b.getOrder_stata(), b.getOrser_time(), g,1);
				orders.add(e);
			}
		}
		return orders;
	}
	
	//加载订单数据管理页面（与java同步）
	public List<orders_data> addorderdata2(){
		List<orders_data> orders = new ArrayList<>();
		List<order_data> order = add_order.addorderdata();
		for(order_data b: order){
			if(b.getOrder_top().isEmpty()){
				List<order_data> g = new ArrayList<>();
				for(order_data f: order){
					if(f.getOrder_top().equals(b.getOrder_id())){
						g.add(f);
					}
				}
				orders_data e = new orders_data(b.getOrder_id(), b.getUser_id(), b.getOrder_stata(), b.getOrser_time(), g,1);
				orders.add(e);
			}
		}
		return orders;
	}
}
