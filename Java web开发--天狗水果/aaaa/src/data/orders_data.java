package data;

import java.util.ArrayList;
import java.util.List;

public class orders_data {
	
	private String orders_id = "";
	private String user_id = "";
	private int orders_stata = 0;
	private String orders_time = "";
	private float orders_price = 0;
	private List<order_data> orders_list = new ArrayList<>();
	
	
	public float getOrders_price() {
		return orders_price;
	}
	public String getOrders_id() {
		return orders_id;
	}
	public String getUser_id() {
		return user_id;
	}
	public int getOrders_stata() {
		return orders_stata;
	}
	public String getOrders_time() {
		return orders_time;
	}
	public List<order_data> getOrders_list() {
		return orders_list;
	}
	public void set(String orders_id,String user_id,int orders_stata,
			String orders_time,List<order_data> orders_list,float orders_price) {
		this.orders_id = orders_id;
		this.user_id = user_id;
		this.orders_stata = orders_stata;
		this.orders_time = orders_time;
		this.orders_list = orders_list;
		this.orders_price = orders_price;
	}
	
	public orders_data(){		
	}
	
	public orders_data(String orders_id,String user_id,int orders_stata,
			String orders_time,List<order_data> orders_list,float orders_price) {
		this.orders_id = orders_id;
		this.user_id = user_id;
		this.orders_stata = orders_stata;
		this.orders_time = orders_time;
		this.orders_list = orders_list;
		this.orders_price = orders_price;
	}
}
