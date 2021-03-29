package data;

public class order_data {
	
	private String order_id = "";
	private String user_id = "";
	private String goods_id = "";
	private int goods_num = 0;
	private int order_stata = 0;
	private String order_time = "";
	private String order_top = "";
	private float order_price = 0;
	
	public float getOrder_price() {
		return order_price;
	}
	public String getOrder_top() {
		return order_top;
	}
	public String getOrder_id() {
		return order_id;
	}
	public String getUser_id() {
		return user_id;
	}
	public String getGoods_id() {
		return goods_id;
	}
	public int getGoods_num() {
		return goods_num;
	}
	public int getOrder_stata() {
		return order_stata;
	}
	public String getOrser_time() {
		return order_time;
	}
	
	public void set(String order_id,String user_id,String goods_id,int goods_num,
			int order_stata,String order_time,String order_top,float order_price) {
		this.order_id = order_id;
		this.user_id = user_id;
		this.goods_id = goods_id;
		this.goods_num = goods_num;
		this.order_stata = order_stata;
		this.order_time = order_time;
		this.order_top = order_top;
		this.order_price=order_price;
	}
	
	public  order_data(){
	}
	
	public  order_data(String order_id,String user_id,String goods_id,int goods_num,
			int order_stata,String order_time,String order_top,float order_price) {
		this.order_id = order_id;
		this.user_id = user_id;
		this.goods_id = goods_id;
		this.goods_num = goods_num;
		this.order_stata = order_stata;
		this.order_time = order_time;
		this.order_top = order_top;
		this.order_price=order_price;
	}
}
