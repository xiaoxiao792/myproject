package dataobject;

public class PowerData {
	
	private String powerid = "";
	private String powername = "";
	private String pwd = "";
	private int islogin = 0; 
	
	/**=======================================================================**
	 *		[## public ReserveData() {} ]: 					构造函数
	 *			参数   ：无
	 *			返回值 ：无
	 *			修饰符 ：public
	 *			功能   ：无
	 **=======================================================================**
	 */
	public PowerData() {	
	}

	public PowerData(String powerid ,String powername ,String pwd) {
		this.powerid = powerid;
		this.powername = powername;
		this.pwd = pwd;
	}
	
	public void setIslogin(int islogin) {
		this.islogin = islogin;
	}

	public void set(String powerid ,String powername ,String pwd) {
		this.powerid = powerid;
		this.powername = powername;
		this.pwd = pwd;
	}

	public String getPowerid() {
		return powerid;
	}

	public String getPowername() {
		return powername;
	}

	public String getPwd() {
		return pwd;
	}

	public int getIslogin() {
		return islogin;
	}
	
}
