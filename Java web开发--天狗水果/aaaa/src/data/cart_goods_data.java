package data;

public class cart_goods_data {
	private cart_data cart=null;
	private goods_data goods=null;
	public cart_data getCart() {
		return cart;
	}
	public goods_data getGoods() {
		return goods;
	}
	public void set(cart_data cart,goods_data goods) {
		this.cart = cart;
		this.goods = goods;
	}
	public void setCart(cart_data cart) {
		this.cart = cart;
	}
	public void setGoods(goods_data goods) {
		this.goods = goods;
	}
	public cart_goods_data(){		
	}
	public cart_goods_data(cart_data cart,goods_data goods) {
		this.cart = cart;
		this.goods = goods;
	}
}
