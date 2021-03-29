package data;

public class goods_data {
	
	private String goods_id = "";
	private String goods_name = "";
	private float goods_price = 0;
	private int goods_class = 0;
	private String goods_img = "";
	public String getGoods_id() {
		return goods_id;
	}
	public String getGoods_name() {
		return goods_name;
	}
	public float getGoods_price() {
		return goods_price;
	}
	public int getGoods_class() {
		return goods_class;
	}
	public String getGoods_img() {
		return goods_img;
	}
	public void setGoods_id(String goods_id) {
		this.goods_id = goods_id;
	}
	
	public void set(String goods_id,String goods_name,
			float goods_price,int goods_class,
			String goods_img){
		this.goods_id = goods_id;
		this.goods_name = goods_name;
		this.goods_price = goods_price;
		this.goods_class = goods_class;
		this.goods_img = goods_img;
	}
	
	public goods_data(){
	}
	
	public goods_data(String goods_id,String goods_name,
			float goods_price,int goods_class,
			String goods_img){
		this.goods_id = goods_id;
		this.goods_name = goods_name;
		this.goods_price = goods_price;
		this.goods_class = goods_class;
		this.goods_img = goods_img;
	}
	
	
}
