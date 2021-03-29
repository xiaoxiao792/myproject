package data;

public class order_goods_data {
	private goods_data goods=null;
	private order_data order=null;
	public goods_data getGoods() {
		return goods;
	}
	public order_data getOrder() {
		return order;
	}
	public void set(goods_data goods,order_data order) {
		this.goods = goods;
		this.order = order;
	}
	public void setGoods(goods_data goods) {
		this.goods = goods;
	}
	public void setOrder(order_data order) {
		this.order = order;
	}
	public order_goods_data(){		
	}
	public order_goods_data(goods_data goods,order_data order) {
		this.goods = goods;
		this.order = order;
	}	
}
