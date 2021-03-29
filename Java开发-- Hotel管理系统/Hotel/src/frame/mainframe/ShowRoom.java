package frame.mainframe;

import panel.roompanel.*;
import readywork.AddData;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.ArrayList;
import java.util.List;
import javax.swing.*;
import dataobject.Room;

public class ShowRoom {

	public static List<Room> list = new ArrayList<>();
	RoomPanel roomPanel1;
	RoomPanel roomPanel2;
	RoomPanel roomPanel3;
	RoomPanel roomPanel4;
	RoomPanel roomPanel5;
	RoomPanel roomPanel6;
	RoomPanel roomPanel7;
	RoomPanel roomPanel8;
	RoomPanel roomPanel9;
	RoomPanel roomPanel10;
	RoomPanel roomPanel11;
	RoomPanel roomPanel12;
	int col;
	int col_1 = 0;
	int col_2 = 0;
	int col_3 = 0;
	int col_4 = 0;
	int col_5 = 0;
	int col_6 = 0;
	
	public void setcol(int row) {
		switch(row) {
	    case 1:col_1+=145;break;
	    case 2:col_2+=145;break;
	    case 3:col_3+=145;break;
	    case 4:col_4+=145;break;
	    case 5:col_5+=145;break;
	    case 6:col_6+=145;break;
	    default:break;
		}
	}
	
	public int getcol(int row) {
		switch(row) {
	    case 1:return col_1;
	    case 2:return col_2;
	    case 3:return col_3;
	    case 4:return col_4;
	    case 5:return col_5;
	    case 6:return col_6;
	    default:return 0;
		}
	}
	
	public JPanel single_standard(JPanel panel_1, String name, int id) {// 标准单人间设置
		int row = id / 100;// 房间位置在第几行
		col = getcol(row);
		roomPanel1 = new RoomPanel1(name + id);
		roomPanel1.setBounds(col, (row - 1) * 105, 140, 100);
		panel_1.add(roomPanel1);
		setcol(row);
		return roomPanel1;
	}

	public JPanel couple_standard(JPanel panel_1, String name, int id) {// 标准双人间设置
		int row = id / 100;// 房间位置在第几行
		col = getcol(row);
		roomPanel2 = new RoomPanel2(name + id);
		roomPanel2.setBounds(col, (row - 1) * 105, 140, 100);
		panel_1.add(roomPanel2);
		setcol(row);
		return panel_1;
	}

	public JPanel single_luxury(JPanel panel_1, String name, int id) {// 豪华单人间设置
		int row = id / 100;// 房间位置在第几行
		col = getcol(row);
		roomPanel5 = new RoomPanel5(name + id);
		roomPanel5.setBounds(col, (row - 1) * 105, 140, 100);
		panel_1.add(roomPanel5);
		setcol(row);
		return panel_1;
	}

	public JPanel couple_luxury(JPanel panel_1, String name, int id) {// 豪华双人间设置
		int row = id / 100;// 房间位置在第几行
		col = getcol(row);
		roomPanel6 = new RoomPanel6(name + id);
		roomPanel6.setBounds(col, (row - 1) * 105, 140, 100);
		panel_1.add(roomPanel6);
		setcol(row);
		return panel_1;
	}

	public JPanel business_room(JPanel panel_1, String name, int id) {// 商务套房设置
		int row = id / 100;// 房间位置在第几行
		col = getcol(row);
		roomPanel3 = new RoomPanel3(name + id);
		roomPanel3.setBounds(col, (row - 1) * 105, 140, 100);
		panel_1.add(roomPanel3);
		setcol(row);
		return panel_1;
	}

	public JPanel pre_room(JPanel panel_1, String name, int id) {// 总统套房设置
		int row = id / 100;// 房间位置在第几行
		col = getcol(row);
		roomPanel4 = new RoomPanel4(name + id);
		roomPanel4.setBounds(col, (row - 1) * 105, 140, 100);
		panel_1.add(roomPanel4);
		setcol(row);
		return panel_1;
	}

	public JPanel dirty_room(JPanel panel_1, String name, int id) {// 脏房
		int row = id / 100;// 房间位置在第几行
		col = getcol(row);
		roomPanel9 = new RoomPanel_clean(name + id);
		roomPanel9.setBounds(col, (row - 1) * 105, 140, 100);
		panel_1.add(roomPanel9);
		setcol(row);
		return panel_1;
	}

	public JPanel mend_room(JPanel panel_1, String name, int id) {// 维修房
		int row = id / 100;// 房间位置在第几行
		col = getcol(row);
		roomPanel10 = new RoomPanel_mend(name + id);
		roomPanel10.setBounds(col, (row - 1) * 105, 140, 100);
		panel_1.add(roomPanel10);
		setcol(row);
		return panel_1;
	}
	
	public JPanel use_room(JPanel panel_1, String name, int id) {// 住人
		int row = id / 100;// 房间位置在第几行
		col = getcol(row);
		roomPanel11 = new RoomPanel_use(name + id);
		roomPanel11.setBounds(col, (row - 1) * 105, 140, 100);
		panel_1.add(roomPanel11);
		setcol(row);
		roomPanel11.addMouseListener(new MouseAdapter() {//面板监听

			@Override
			public void mouseClicked(MouseEvent e) {
				// TODO Auto-generated method stub
				String[] buttons = { "是", "否" };
				int rc = JOptionPane.showOptionDialog(null, "当前房间号为" + id + ",是否退房?", "房间提示",
						JOptionPane.WARNING_MESSAGE, 0, null, buttons, buttons[1]);

				if (rc == -1) {
				} else if (rc == 0) {
					new Checkout(id);
				} else {
				}
			}
		});
		return panel_1;
	}
	
	public JPanel reserve_room(JPanel panel_1, String name, int id) {// 住人
		int row = id / 100;// 房间位置在第几行
		col = getcol(row);
		roomPanel12 = new RoomPanel_reserve(name + id);
		roomPanel12.setBounds(col, (row - 1) * 105, 140, 100);
		panel_1.add(roomPanel12);
		setcol(row);
		return panel_1;
	}

	@SuppressWarnings("unused")
	public ShowRoom(JPanel panel_1) {
		int n,j=0;
		list = AddData.getList2();
		String p = "";
		int roomid;
		int roomstata;
		int roomclassid;
		int roomfloor;
		for(Room a : list) {
			
			roomfloor = a.getRoomfloor();
			
			if(a.getRoomclassid()==10001)
				p = "标准单人房";
			else if(a.getRoomclassid()==10002)
				p = "标准双人房";
			else if(a.getRoomclassid()==10003)
				p = "豪华单人房";
			else if(a.getRoomclassid()==10004)
				p = "豪华双人房";
			else if(a.getRoomclassid()==10005)
				p = "商务套房";
			else
				p = "总统套房";
			
			roomid = a.getRoomid();
			roomstata = a.getRoomstata();
			roomclassid = a.getRoomclassid();
			
			if(roomstata==1) {
				switch(roomclassid-10000) {
				    case 1:single_standard(panel_1,p,roomid);break;
				    case 2:couple_standard(panel_1,p,roomid);break;
				    case 3:single_luxury(panel_1,p,roomid);break;
				    case 4:couple_luxury(panel_1,p,roomid);break;
				    case 5:business_room(panel_1,p,roomid);break;
				    case 6:pre_room(panel_1,p,roomid);break;
				    default:break;
				}
			}else if(roomstata==2||roomstata==4) {
				dirty_room(panel_1,p,roomid);
			}else if(roomstata==5) {
				mend_room(panel_1,p,roomid);
			}else if(roomstata==3) {
				use_room(panel_1,p,roomid);
			}else if(roomstata==6) {
				reserve_room(panel_1,p,roomid);
			}
			
		}
	}
	
	@SuppressWarnings("unused")
	public ShowRoom(JPanel panel_1,List<Room> query) {
		int n,j=0;
		String p = "";
		int roomid;
		int roomstata;
		int roomclassid;
		int roomfloor;
		for(Room a : query) {
			
			roomfloor = a.getRoomfloor();
			
			if(a.getRoomclassid()==10001)
				p = "标准单人房";
			else if(a.getRoomclassid()==10002)
				p = "标准双人房";
			else if(a.getRoomclassid()==10003)
				p = "豪华单人房";
			else if(a.getRoomclassid()==10004)
				p = "豪华双人房";
			else if(a.getRoomclassid()==10005)
				p = "商务套房";
			else
				p = "总统套房";
			
			roomid = a.getRoomid();
			roomstata = a.getRoomstata();
			roomclassid = a.getRoomclassid();
			
			if(roomstata==1) {
				switch(roomclassid-10000) {
				    case 1:single_standard(panel_1,p,roomid);break;
				    case 2:couple_standard(panel_1,p,roomid);break;
				    case 3:single_luxury(panel_1,p,roomid);break;
				    case 4:couple_luxury(panel_1,p,roomid);break;
				    case 5:business_room(panel_1,p,roomid);break;
				    case 6:pre_room(panel_1,p,roomid);break;
				    default:break;
				}
			}else if(roomstata==2||roomstata==4) {
				dirty_room(panel_1,p,roomid);
			}else if(roomstata==5) {
				mend_room(panel_1,p,roomid);
			}else if(roomstata==3) {
				use_room(panel_1,p,roomid);
			}else if(roomstata==6) {
				reserve_room(panel_1,p,roomid);
			}
			
		}
	}
}

