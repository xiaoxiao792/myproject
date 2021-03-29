package data;

import java.util.ArrayList;
import java.util.List;

public class orders_goods_data {
	
	private String orders_goods_id = "";
	private String user_id = "";
	private int orders_goods_stata = 0;
	private String orders_goods_time = "";
	private float orders_goods_price = 0;
	private List<order_goods_data> order_goods_list = new ArrayList<>();
	public String getOrders_goods_id() {
		return orders_goods_id;
	}
	public String getUser_id() {
		return user_id;
	}
	public int getOrders_goods_stata() {
		return orders_goods_stata;
	}
	public String getOrders_goods_time() {
		return orders_goods_time;
	}
	public float getOrders_goods_price() {
		return orders_goods_price;
	}
	public List<order_goods_data> getOrder_goods_list() {
		return order_goods_list;
	}
	
	public void setOrders_goods_id(String orders_goods_id,String user_id,
			int orders_goods_stata,String orders_goods_time,float orders_goods_price,
			List<order_goods_data> order_goods_list) {
		this.orders_goods_id = orders_goods_id;
		this.user_id = user_id;
		this.orders_goods_stata = orders_goods_stata;
		this.orders_goods_time = orders_goods_time;
		this.orders_goods_price = orders_goods_price;
		this.order_goods_list = order_goods_list;
	}
	
	public orders_goods_data(String orders_goods_id,String user_id,
			int orders_goods_stata,String orders_goods_time,float orders_goods_price,
			List<order_goods_data> order_goods_list) {
		this.orders_goods_id = orders_goods_id;
		this.user_id = user_id;
		this.orders_goods_stata = orders_goods_stata;
		this.orders_goods_time = orders_goods_time;
		this.orders_goods_price = orders_goods_price;
		this.order_goods_list = order_goods_list;
	}
	
	public orders_goods_data(){		
	}
	
}
