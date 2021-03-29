package dataobject;

public class Client {

	/**=======================================================================**
	 *		定义属性
	 **=======================================================================**
	 */
	private int clientid;
	private String clientname = "";
	private String clientidnumber = "";
	private int clientsex;
	private int clientage;
	private String clientphone = "";
	private String clientemail = "";
	private String clientaddress = "";
	private String clientclassname = "";
	private static int pointid= 10001;
	
	public void set(int clientid,String clientname, String clientidnumber, int clientsex, int clientage, String clientphone, String clientemail,
			String clientaddress,String clientclassname) {
		this.clientid = clientid;
		this.clientsex = clientsex;
		this.clientphone = clientphone;
		this.clientaddress = clientaddress;
		this.clientidnumber = clientidnumber;
		this.clientname = clientname;
		this.clientemail = clientemail;
		this.clientage = clientage;
		this.clientclassname = clientclassname;
	}

	public static int getPointid() {
		return pointid;
	}

	public int getClientid() {
		int point = this.clientid;
		return point;
	}

	public int getClientsex() {
		return clientsex;
	}

	public String getClientphone() {
		return clientphone;
	}

	public String getClientaddress() {
		return clientaddress;
	}

	public String getClientidnumber() {
		return clientidnumber;
	}

	public String getClientname() {
		return clientname;
	}

	public String getClientemail() {
		return clientemail;
	}

	public int getClientage() {
		return clientage;
	}

	public String getClientclassname() {
		return clientclassname;
	}

	public void setClientid(int clientid) {
		this.clientid = clientid;
	}

	public void setClientname(String clientname) {
		this.clientname = clientname;
	}

	public void setClientidnumber(String clientidnumber) {
		this.clientidnumber = clientidnumber;
	}

	public void setClientsex(int clientsex) {
		this.clientsex = clientsex;
	}

	public void setClientage(int clientage) {
		this.clientage = clientage;
	}

	public void setClientphone(String clientphone) {
		this.clientphone = clientphone;
	}

	public void setClientemail(String clientemail) {
		this.clientemail = clientemail;
	}

	public void setClientaddress(String clientaddress) {
		this.clientaddress = clientaddress;
	}

	public void setClientclassname(String clientclassname) {
		this.clientclassname = clientclassname;
	}

	public static void setPointid(int pointid) {
		Client.pointid = pointid;
	}

	/**=======================================================================**
	 *		[## public Client() {} ]: 					构造函数
	 *			参数   ：无
	 *			返回值 ：无
	 *			修饰符 ：public
	 *			功能   ：无
	 **=======================================================================**
	 */
	public Client() {	
	}
	
	public Client(int clientid,String clientname, String clientidnumber, int clientsex, int clientage, String clientphone, String clientemail,
			String clientaddress,String clientclassname) {	
		this.clientid = clientid;
		this.clientsex = clientsex;
		this.clientphone = clientphone;
		this.clientaddress = clientaddress;
		this.clientidnumber = clientidnumber;
		this.clientname = clientname;
		this.clientemail = clientemail;
		this.clientage = clientage;
		this.clientclassname = clientclassname;
		pointid+=1;
	}
}
