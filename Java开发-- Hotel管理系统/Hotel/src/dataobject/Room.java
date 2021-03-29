package dataobject;

public class Room {

	/**=======================================================================**
	 *		��������
	 **=======================================================================**
	 */
	private int roomid;
	private int roomclassid;
	private int roomfloor;
	private int roomstata;
	private double roomprice;
	
	/**=======================================================================**
	 *		[## public Room() {} ]: 					���캯��
	 *			����   ����
	 *			����ֵ ����
	 *			���η� ��public
	 *			����   ����
	 **=======================================================================**
	 */
	public Room() {	
	}
	
	public Room(int roomid, int roomclassid, int roomfloor, int roomstata, double roomprice) {
		this.roomclassid = roomclassid;
		this.roomfloor = roomfloor;
		this.roomstata = roomstata;
		this.roomprice = roomprice;
		this.roomid = roomid;
	}
	
	public void set(int roomid,int roomclassid, int roomfloor, int roomstata, double roomprice) {	
		this.roomclassid = roomclassid;
		this.roomfloor = roomfloor;
		this.roomstata = roomstata;
		this.roomprice = roomprice;
		this.roomid = roomid;
	}

	public int getRoomclassid() {
		return roomclassid;
	}

	public int getRoomfloor() {
		return roomfloor;
	}

	public int getRoomstata() {
		return roomstata;
	}

	public double getRoomprice() {
		return roomprice;
	}

	public int getRoomid() {
		return roomid;
	}

	public void setRoomid(int roomid) {
		this.roomid = roomid;
	}

	public void setRoomclassid(int roomclassid) {
		this.roomclassid = roomclassid;
	}

	public void setRoomfloor(int roomfloor) {
		this.roomfloor = roomfloor;
	}

	public void setRoomstata(int roomstata) {
		this.roomstata = roomstata;
	}

	public void setRoomprice(double roomprice) {
		this.roomprice = roomprice;
	}
	
}
