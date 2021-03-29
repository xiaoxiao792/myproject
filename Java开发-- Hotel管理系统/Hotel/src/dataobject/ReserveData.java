package dataobject;

public class ReserveData {
	private int reserveid;
	private String clientname = "";
	private String reservetime = "";
	private String clientphone = "";
	private String clientemail = "";
	private String starttime = "";
	private int reservedays;
	private int isroom;
	private int roomnum;
	private int[] roomname;
	private int reservestata;
	private String remark = "";
	private static int pointid= 10001;
	
	/**=======================================================================**
	 *		[## public ReserveData() {} ]: 					构造函数
	 *			参数   ：无
	 *			返回值 ：无
	 *			修饰符 ：public
	 *			功能   ：无
	 **=======================================================================**
	 */
	public ReserveData() {	
	}
	
	public ReserveData(int reserveid ,String clientname ,String reservetime ,String clientphone ,String clientemail ,String starttime ,
			int reservedays ,int isroom ,int roomnum ,int[] roomname ,int reservestata ,String remark) {
		this.reserveid = reserveid;
		this.remark = remark;
		this.clientname = clientname;
		this.reservetime = reservetime;
		this.clientphone = clientphone;
		this.clientemail = clientemail;
		this.starttime = starttime;
		this.reservedays = reservedays;
		this.isroom = isroom;
		this.roomnum = roomnum;
		this.roomname = roomname;
		this.reservestata = reservestata;
	}
	
	public void set(int reserveid ,String clientname ,String reservetime ,String clientphone ,String clientemail ,String starttime ,
			int resevedays ,int isroom ,int roomnum ,int[] roomname ,int reservestata ,String remark) {
		this.reserveid = reserveid;
		this.remark = remark;
		this.clientname = clientname;
		this.reservetime = reservetime;
		this.clientphone = clientphone;
		this.clientemail = clientemail;
		this.starttime = starttime;
		this.reservedays = resevedays;
		this.isroom = isroom;
		this.roomnum = roomnum;
		this.roomname = roomname;
		this.reservestata = reservestata;
	}

	public void setReserveid(int reserveid) {
		this.reserveid = reserveid;
	}

	public void setClientname(String clientname) {
		this.clientname = clientname;
	}

	public void setReservetime(String reservetime) {
		this.reservetime = reservetime;
	}

	public void setClientphone(String clientphone) {
		this.clientphone = clientphone;
	}

	public void setClientemail(String clientemail) {
		this.clientemail = clientemail;
	}

	public void setStarttime(String starttime) {
		this.starttime = starttime;
	}

	public void setReservedays(int reservedays) {
		this.reservedays = reservedays;
	}

	public void setIsroom(int isroom) {
		this.isroom = isroom;
	}

	public void setRoomnum(int roomnum) {
		this.roomnum = roomnum;
	}

	public void setRoomname(int[] roomname) {
		this.roomname = roomname;
	}

	public void setReservestata(int reservestata) {
		this.reservestata = reservestata;
	}

	public void setRemark(String remark) {
		this.remark = remark;
	}

	public static void setPointid() {
		ReserveData.pointid+=1;
	}

	public static int getPointid() {
		return pointid;
	}
	
	public int getReserveid() {
		return reserveid;
	}

	public String getRemark() {
		return remark;
	}

	public String getClientname() {
		return clientname;
	}

	public String getReservetime() {
		return reservetime;
	}

	public String getClientphone() {
		return clientphone;
	}

	public String getClientemail() {
		return clientemail;
	}

	public String getStarttime() {
		return starttime;
	}

	public int getReservedays() {
		return reservedays;
	}

	public int getIsroom() {
		return isroom;
	}

	public int getRoomnum() {
		return roomnum;
	}

	public int[] getRoomname() {
		return roomname;
	}

	public int getReservestata() {
		return reservestata;
	}
	
}
