package dataobject;

public class OrderData {
	private int orderid;
	private String clientname = "";
	private String orderbegintime = "";
	private String clientphone = "";
	private String clientemail = "";
	private int orderdays;
	private int roomnum;
	private int[] roomname;
	private int orderstata;
	private String remark = "";
	private static int pointid= 10001;
	
	/**=======================================================================**
	 *		[## public OrderData() {} ]: 					构造函数
	 *			参数   ：无
	 *			返回值 ：无
	 *			修饰符 ：public
	 *			功能   ：无
	 **=======================================================================**
	 */
	public OrderData() {	
	}
	
	public OrderData(int orderid ,String clientname ,String orderbegintime ,String clientphone ,String clientemail ,
			int orderdays ,int roomnum ,int[] roomname ,int orderstata ,String remark) {
		this.orderid = orderid;
		this.clientname = clientname;
		this.orderbegintime = orderbegintime;
		this.clientphone = clientphone;
		this.clientemail = clientemail;
		this.orderdays = orderdays;
		this.roomnum = roomnum;
		this.roomname = roomname;
		this.orderstata = orderstata;
		this.remark = remark;
//		pointid+=1;
	}
	
	public void set(int orderid ,String clientname ,String orderbegintime ,String clientphone ,String clientemail ,
			int orderdays ,int roomnum ,int[] roomname ,int orderstata ,String remark) {
		this.orderid = orderid;
		this.clientname = clientname;
		this.orderbegintime = orderbegintime;
		this.clientphone = clientphone;
		this.clientemail = clientemail;
		this.orderdays = orderdays;
		this.roomnum = roomnum;
		this.roomname = roomname;
		this.orderstata = orderstata;
		this.remark = remark;
	}

	public void setOrderid(int orderid) {
		this.orderid = orderid;
	}

	public void setClientname(String clientname) {
		this.clientname = clientname;
	}

	public void setOrderbegintime(String orderbegintime) {
		this.orderbegintime = orderbegintime;
	}

	public void setClientphone(String clientphone) {
		this.clientphone = clientphone;
	}

	public void setClientemail(String clientemail) {
		this.clientemail = clientemail;
	}

	public void setOrderdays(int orderdays) {
		this.orderdays = orderdays;
	}

	public void setRoomnum(int roomnum) {
		this.roomnum = roomnum;
	}

	public void setRoomname(int[] roomname) {
		this.roomname = roomname;
	}

	public void setOrderstata(int orderstata) {
		this.orderstata = orderstata;
	}

	public void setRemark(String remark) {
		this.remark = remark;
	}

	public static void setPointid() {
		OrderData.pointid+=1;
	}

	public static int getPointid() {
		return pointid;
	}

	public int getOrderid() {
		return orderid;
	}

	public String getRemark() {
		return remark;
	}

	public String getClientname() {
		return clientname;
	}

	public String getOrderbegintime() {
		return orderbegintime;
	}

	public String getClientphone() {
		return clientphone;
	}

	public String getClientemail() {
		return clientemail;
	}

	public int getOrderdays() {
		return orderdays;
	}

	public int getRoomnum() {
		return roomnum;
	}

	public int[] getRoomname() {
		return roomname;
	}

	public int getOrderstata() {
		return orderstata;
	}
	
}
