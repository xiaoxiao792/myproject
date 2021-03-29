package data;

public class cart_data {
	
	private String cart_id = "";
	private String user_id = "";
	private String goods_id = "";
	private int goods_num = 0;
		
	public String getCart_id() {
		return cart_id;
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

	public void setGoods_num(int goods_num) {
		this.goods_num = goods_num;
	}
	
	public void set(String cart_id,String user_id,
	String goods_id,int goods_num){
		this.cart_id = cart_id;
		this.user_id = user_id;
		this.goods_id = goods_id;
		this.goods_num = goods_num;
	}
	
	public cart_data(){
	}
	
	public cart_data(String cart_id,String user_id,
			String goods_id,int goods_num){
		this.cart_id = cart_id;
		this.user_id = user_id;
		this.goods_id = goods_id;
		this.goods_num = goods_num;
	}
}
