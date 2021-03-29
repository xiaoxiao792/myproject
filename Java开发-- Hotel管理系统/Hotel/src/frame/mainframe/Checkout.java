package frame.mainframe;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.SwingConstants;
import java.awt.Color;
import javax.swing.border.LineBorder;
import dataobject.Client;
import dataobject.OrderData;
import dataobject.Room;
import function.query.Query;
import function.updata.UpDataItem;
import readywork.AddData;
import system.GetTime;
import javax.swing.JTextField;
import javax.swing.JSeparator;
import javax.swing.JButton;
import java.awt.Toolkit;
import java.awt.event.ActionListener;
import java.text.SimpleDateFormat;
import java.util.List;
import java.awt.event.ActionEvent;
import java.util.*;

public class Checkout extends JFrame {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	public static List<OrderData> list = AddData.getList3();
	public static List<Room> list1 = AddData.getList2();
	public static List<Client> list2 = AddData.getList1();
	private JPanel contentPane;
	private final JTextField textField = new JTextField();
	private JTextField textField_1;
	String orderbegintime = "";
	int orderid;
	String clientname = "";
	double roomprice;
	String clientphone = "";
	String clientclassname = "";
	double discount;
	String orderendtime = "";
	double orderprice;
	double realprice,price;
	/**
	 * Create the frame.
	 */
	public Checkout() {
		
	}
	public Checkout(int roomid) {
		for(Room a:list1) {
			if(a.getRoomid()==roomid)
				roomprice = a.getRoomprice();
		}
		
		for(OrderData e : list) {
			for(int i=0;i<e.getRoomnum();i++) {
				if(roomid == e.getRoomname()[i]&&e.getOrderstata()==1) {
					orderbegintime = e.getOrderbegintime();
					orderid = e.getOrderid();
					clientname = e.getClientname();
					clientphone = e.getClientphone();
				}
			}
		}
		
		List<Client> query = Query.clientquery(list2, clientphone);
		for(Client c : query) {
			clientclassname = c.getClientclassname();
		}
		
		switch(clientclassname) {
		case "普通用户": discount = 1;
		case "vip1用户": discount = 0.9;
		case "vip2用户": discount = 0.85;
		case "vip3用户": discount = 0.8;
		}

		orderendtime = new GetTime().getTime();
		
		SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		try

		{

		Date d1 = dateFormat.parse(orderendtime);

		Date d2 = dateFormat.parse(orderbegintime);

		long diff = d1.getTime() - d2.getTime();//这样得到的差值是微秒级别

		long days = diff / (1000 * 60 * 60 * 24);

		long hours = (diff-days*(1000 * 60 * 60 * 24))/(1000* 60 * 60);

		long minutes = (diff-days*(1000 * 60 * 60 * 24)-hours*(1000* 60 * 60))/(1000* 60);

		if(hours != 0 || minutes != 0) {
			days+=1;
		}
		
		orderprice = roomprice * days * discount;
		price = roomprice * days;
		
		}catch(Exception e) {
			e.printStackTrace();
		}
		
		setTitle("酒店-收银结账");
		setIconImage(Toolkit.getDefaultToolkit().getImage("img/宜微.png"));
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		setBounds(100, 100, 520, 320);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		JPanel panel = new JPanel();
		panel.setBounds(15, 5, 120, 30);
		contentPane.add(panel);
		panel.setLayout(null);
		
		JLabel label = new JLabel("收银结账");
		label.setOpaque(true);
		label.setBackground(Color.ORANGE);
		label.setHorizontalAlignment(SwingConstants.CENTER);
		label.setBounds(0, 0, 120, 30);
		panel.add(label);
		
		JPanel panel_1 = new JPanel();
		panel_1.setBackground(Color.WHITE);
		panel_1.setBorder(new LineBorder(Color.ORANGE));
		panel_1.setBounds(5, 35, 490, 230);
		contentPane.add(panel_1);
		panel_1.setLayout(null);
		
		JPanel panel_2 = new JPanel();
		panel_2.setBackground(new Color(242,221,178));
		panel_2.setBorder(new LineBorder(Color.ORANGE));
		panel_2.setBounds(10, 10, 470, 80);
		panel_1.add(panel_2);
		panel_2.setLayout(null);
		
		JLabel label_1 = new JLabel("订单："+orderid);
		label_1.setBounds(10, 10, 180, 25);
		panel_2.add(label_1);
		
//		JLabel label_2 = new JLabel(""+orderid);
//		label_2.setBounds(60, 10, 130, 25);
//		panel_2.add(label_2);
		
		JLabel label_3 = new JLabel("房间："+roomid);
		label_3.setBounds(200, 10, 130, 25);
		panel_2.add(label_3);
		
//		JLabel label_4 = new JLabel("111111");
//		label_4.setBounds(250, 10, 80, 25);
//		panel_2.add(label_4);
		
		JLabel label_5 = new JLabel("姓名："+clientname);
		label_5.setBounds(340, 10, 130, 25);
		panel_2.add(label_5);
		
//		JLabel label_6 = new JLabel("诸葛卧龙");
//		label_6.setBounds(390, 10, 80, 25);
//		panel_2.add(label_6);
		
		JLabel label_7 = new JLabel("消费金额："+price);
		label_7.setBounds(10, 45, 180, 25);
		panel_2.add(label_7);
		
//		JLabel label_8 = new JLabel("1111111");
//		label_8.setBounds(90, 45, 100, 25);
//		panel_2.add(label_8);
		
		JLabel label_9 = new JLabel("应收金额(优惠)："+orderprice+"("+discount+")");
		label_9.setBounds(200, 45, 270, 25);
		panel_2.add(label_9);
		
//		JLabel label_10 = new JLabel("111111");
//		label_10.setBounds(330, 45, 140, 25);
//		panel_2.add(label_10);
		
		JPanel panel_3 = new JPanel();
		panel_3.setBackground(new Color(242,221,178));
		panel_3.setBorder(new LineBorder(Color.ORANGE));
		panel_3.setBounds(10, 100, 470, 120);
		panel_1.add(panel_3);
		panel_3.setLayout(null);
		
		JLabel label_11 = new JLabel("实收金额：");
		label_11.setBounds(10, 10, 80, 25);
		panel_3.add(label_11);
		textField.setBounds(90, 10, 100, 25);
		panel_3.add(textField);
		textField.setColumns(10);
		
		double dt = 0.0;
//		if(textField.getText()!=null) {
//			try {
//				dt = Double.parseDouble(textField.getText())-orderprice;
//			}catch(Exception e) {
//				e.printStackTrace();
//			}
//
//		}
		JLabel label_12 = new JLabel("找零："+dt);//+(Double.parseDouble(textField.getText())-orderprice)
		label_12.setBounds(220, 10, 150, 25);
		panel_3.add(label_12);
		
//		JLabel label_13 = new JLabel("1111111");
//		label_13.setBounds(270, 10, 100, 25);
//		panel_3.add(label_13);
		
		JLabel label_14 = new JLabel("备注信息：");
		label_14.setBounds(10, 45, 80, 25);
		panel_3.add(label_14);
		
		textField_1 = new JTextField();
		textField_1.setColumns(10);
		textField_1.setBounds(90, 45, 366, 25);
		panel_3.add(textField_1);
		
		JSeparator separator = new JSeparator();
		separator.setBounds(10, 80, 446, 2);
		panel_3.add(separator);
		
		JButton button = new JButton("结账");
		button.setFocusPainted(false);
		button.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				UpDataItem.updataorder(9, orderid, 2);
				UpDataItem.updataorder2(7, orderid, orderendtime);
				UpDataItem.updataorder3(8, orderid, orderprice);
				UpDataItem.updataroom(roomid, 2);
				JOptionPane.showMessageDialog(null, "结账成功！");
			}
		});
		button.setBounds(100, 88, 113, 27);
		panel_3.add(button);
		
		JButton button_1 = new JButton("取消");
		button_1.setFocusPainted(false);
		button_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
			}
		});
		button_1.setBounds(260, 88, 113, 27);
		panel_3.add(button_1);
		setVisible(true);
	}

}
