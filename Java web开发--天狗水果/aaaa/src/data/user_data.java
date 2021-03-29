package data;

public class user_data {
	
	private String user_id = "";
	private String user_name = "";
	private String user_passwd = "";
	private int user_power = 0;
	private String user_email = "";
		
	
	public String getUser_email() {
		return user_email;
	}

	public String getUser_id() {
		return user_id;
	}

	public String getUser_name() {
		return user_name;
	}

	public String getUser_passwd() {
		return user_passwd;
	}

	public int getUser_power() {
		return user_power;
	}

	public void setUser_id(String user_id) {
		this.user_id = user_id;
	}

	public void setUser_name(String user_name) {
		this.user_name = user_name;
	}

	public void setUser_passwd(String user_passwd) {
		this.user_passwd = user_passwd;
	}

	public void setUser_power(int user_power) {
		this.user_power = user_power;
	}

	public void set(String user_id,String user_name,String user_passwd,int user_power,String user_email){
		this.user_id = user_id;
		this.user_name = user_name;
		this.user_passwd = user_passwd;
		this.user_power = user_power;
		this.user_email = user_email;
	}
	
	public user_data(){
	}
	
	public user_data(String user_id,String user_name,String user_passwd,int user_power,String user_email){
		this.user_id = user_id;
		this.user_name = user_name;
		this.user_passwd = user_passwd;
		this.user_power = user_power;
		this.user_email = user_email;
	}

}
