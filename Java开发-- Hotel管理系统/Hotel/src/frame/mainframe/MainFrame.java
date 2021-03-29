package frame.mainframe;

import java.awt.Image;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import java.awt.Color;
import javax.swing.JPopupMenu;
import java.awt.Component;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.ArrayList;
import java.util.List;

import javax.swing.JButton;
import javax.swing.SwingConstants;
import java.awt.Insets;
import javax.swing.JLabel;
import javax.swing.ImageIcon;
import java.awt.SystemColor;
import javax.swing.JSeparator;
import javax.swing.border.LineBorder;

import dataobject.Room;
import readywork.AddData;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.JCheckBox;
import javax.swing.ButtonGroup;
import javax.swing.JTextArea;
import javax.swing.JScrollPane;
import javax.swing.ScrollPaneConstants;
import java.awt.Dimension;
import java.awt.Toolkit;
import system.GetTime;
import java.awt.event.ItemListener;
import java.awt.event.ItemEvent;
import java.awt.Font;

public class MainFrame extends JFrame {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private JPanel contentPane;
	@SuppressWarnings("unused")
	private final ButtonGroup buttonGroup = new ButtonGroup();
	@SuppressWarnings("unused")
	private final ButtonGroup buttonGroup_1 = new ButtonGroup();
	@SuppressWarnings("unused")
	private final ButtonGroup buttonGroup_2 = new ButtonGroup();
	@SuppressWarnings("unused")
	private final ButtonGroup buttonGroup_3 = new ButtonGroup();
	public String sys_time;
	@SuppressWarnings("unused")
	private final ButtonGroup buttonGroup_4 = new ButtonGroup();
	private final ButtonGroup buttonGroup_5 = new ButtonGroup();
	private final ButtonGroup buttonGroup_6 = new ButtonGroup();
	private final ButtonGroup buttonGroup_7 = new ButtonGroup();

	public void contentPane() {
		contentPane = new JPanel();
		contentPane.setBackground(Color.WHITE);
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
	}

	public MainFrame(String powername) {
		setResizable(false); //设置窗口不可拉伸
		setTitle("酒店客房管理系统");
		setIconImage(Toolkit.getDefaultToolkit().getImage("img/宜微.png"));
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 1200, 800);
		contentPane();//主面板设计
		
		JPanel panel = new JPanel();
		panel.setBackground(Color.GRAY);
		panel.setBounds(0, 0, 110, 729);
		contentPane.add(panel);
		panel.setLayout(null);
		
		ImageIcon icon = new ImageIcon("img/宜微.png");
		icon.setImage(icon.getImage().getScaledInstance(110,80,Image.SCALE_DEFAULT));
		JLabel label_1 = new JLabel(icon);
		label_1.setBounds(25, 44, 95, 90);
		panel.add(label_1);
		
		JPanel panel_3 = new JPanel();
		panel_3.setBorder(new EmptyBorder(0, 0, 0, 0));
		panel_3.setBounds(120, 99, 1062, 32);
		contentPane.add(panel_3);
		panel_3.setLayout(null);
		
		JLabel label = new JLabel("房型");
		label.setOpaque(true);
		label.setHorizontalAlignment(SwingConstants.CENTER);
		label.setBackground(Color.ORANGE);
		label.setBounds(4, 4, 100, 32);
		panel_3.add(label);
		
		JPanel panel_4 = new JPanel();
		panel_4.setBackground(Color.WHITE);
		panel_4.setBounds(130, 0, 1052, 90);
		contentPane.add(panel_4);
		panel_4.setLayout(null);
		
		JButton button = new JButton("开房");
		button.setFocusPainted(false);
		button.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				new RoomOpen();
			}
		});
		button.setForeground(new Color(18, 150, 219));
		button.setOpaque(false);
		button.setBorder(new EmptyBorder(0, 0, 0, 0));
		button.setBackground(Color.WHITE);
		button.setVerticalTextPosition(SwingConstants.BOTTOM);
		button.setHorizontalTextPosition(SwingConstants.CENTER);
		button.setIcon(new ImageIcon("img/审批人管理.png"));
		button.setBounds(0, 0, 90, 90);
		panel_4.add(button);
		
		JButton button_1 = new JButton("关于我们");
		button_1.setFocusPainted(false);
		button_1.setForeground(new Color(18, 150, 219));
		button_1.setOpaque(false);
		button_1.setBorder(new EmptyBorder(0, 0, 0, 0));
		button_1.setBackground(Color.WHITE);
		button_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
			}
		});
		button_1.setIcon(new ImageIcon("img/在线客服.png"));
		button_1.setVerticalTextPosition(SwingConstants.BOTTOM);
		button_1.setMargin(new Insets(0, 0, 0, 0));
		button_1.setHorizontalTextPosition(SwingConstants.CENTER);
		button_1.setBounds(704, 0, 90, 90);
		panel_4.add(button_1);
		
		JButton button_2 = new JButton("预订");
		button_2.setFocusPainted(false);
		button_2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				new Reservation();
			}
		});
		button_2.setForeground(new Color(18, 150, 219));
		button_2.setBorder(new EmptyBorder(0, 0, 0, 0));
		button_2.setBackground(Color.WHITE);
		button_2.setOpaque(false);
		button_2.setHorizontalTextPosition(SwingConstants.CENTER);
		button_2.setVerticalTextPosition(SwingConstants.BOTTOM);
		button_2.setIcon(new ImageIcon("img/预订.png"));
		button_2.setBounds(88, 0, 90, 90);
		panel_4.add(button_2);
		
		JButton button_3 = new JButton("结账");
		button_3.setFocusPainted(false);
		button_3.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				new Checkout();
			}
		});
		button_3.setForeground(new Color(18, 150, 219));
		button_3.setBackground(Color.WHITE);
		button_3.setOpaque(false);
		button_3.setBorder(new EmptyBorder(0, 0, 0, 0));
		button_3.setVerticalTextPosition(SwingConstants.BOTTOM);
		button_3.setHorizontalTextPosition(SwingConstants.CENTER);
		button_3.setIcon(new ImageIcon("img/收银.png"));
		button_3.setBounds(176, 0, 90, 90);
		panel_4.add(button_3);
		
		JButton button_4 = new JButton("客户管理");
		button_4.setFocusPainted(false);
		button_4.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				new CustomerManage();
			}
		});
		button_4.setForeground(new Color(18, 150, 219));
		button_4.setOpaque(false);
		button_4.setBorder(new EmptyBorder(0, 0, 0, 0));
		button_4.setBackground(Color.WHITE);
		button_4.setHorizontalTextPosition(SwingConstants.CENTER);
		button_4.setVerticalTextPosition(SwingConstants.BOTTOM);
		button_4.setIcon(new ImageIcon("img/团队.png"));
		button_4.setBounds(264, 0, 90, 90);
		panel_4.add(button_4);
		
		JButton button_5 = new JButton("预定管理\r\n");
		button_5.setFocusPainted(false);
		button_5.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				new BookManage();
			}
		});
		button_5.setForeground(new Color(18, 150, 219));
		button_5.setOpaque(false);
		button_5.setBorder(new EmptyBorder(0, 0, 0, 0));
		button_5.setBackground(Color.WHITE);
		button_5.setHorizontalTextPosition(SwingConstants.CENTER);
		button_5.setVerticalTextPosition(SwingConstants.BOTTOM);
		button_5.setIcon(new ImageIcon("img/夜审.png"));
		button_5.setBounds(352, 0, 90, 90);
		panel_4.add(button_5);
		
		JButton button_6 = new JButton("订单管理");
		button_6.setFocusPainted(false);
		button_6.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				new OrderManage();
			}
		});
		button_6.setForeground(new Color(18, 150, 219));
		button_6.setBorder(new EmptyBorder(0, 0, 0, 0));
		button_6.setBackground(Color.WHITE);
		button_6.setOpaque(false);
		button_6.setHorizontalTextPosition(SwingConstants.CENTER);
		button_6.setVerticalTextPosition(SwingConstants.BOTTOM);
		button_6.setIcon(new ImageIcon("img/报表.png"));
		button_6.setBounds(440, 0, 90, 90);
		panel_4.add(button_6);
		
		JButton button_7 = new JButton("班次交接");
		button_7.setFocusPainted(false);
		button_7.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
			}
		});
		button_7.setForeground(new Color(18, 150, 219));
		button_7.setOpaque(false);
		button_7.setBorder(new EmptyBorder(0, 0, 0, 0));
		button_7.setBackground(Color.WHITE);
		button_7.setHorizontalTextPosition(SwingConstants.CENTER);
		button_7.setIcon(new ImageIcon("img/更换.png"));
		button_7.setVerticalTextPosition(SwingConstants.BOTTOM);
		button_7.setBounds(528, 0, 90, 90);
		panel_4.add(button_7);
		
		JButton button_8 = new JButton("系统维护");
		button_8.setFocusPainted(false);
		button_8.setForeground(new Color(18, 150, 219));
		button_8.setBorder(new EmptyBorder(0, 0, 0, 0));
		button_8.setBackground(Color.WHITE);
		button_8.setOpaque(false);
		button_8.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
			}
		});
		button_8.setIcon(new ImageIcon("img/维修管理.png"));
		button_8.setVerticalTextPosition(SwingConstants.BOTTOM);
		button_8.setMargin(new Insets(0, 0, 0, 0));
		button_8.setHorizontalTextPosition(SwingConstants.CENTER);
		button_8.setBounds(616, 0, 90, 90);
		panel_4.add(button_8);
		
		JPanel panel_5 = new JPanel();
		panel_5.setBorder(new LineBorder(Color.ORANGE, 1, true));
		panel_5.setOpaque(false);
		panel_5.setBackground(SystemColor.menu);
		panel_5.setBounds(120, 130, 1060, 600);
		contentPane.add(panel_5);
		panel_5.setLayout(null);
		
		JScrollPane scrollPane = new JScrollPane();
		scrollPane.setBorder(new EmptyBorder(0, 0, 0, 0));
		scrollPane.setAutoscrolls(true);
		scrollPane.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_ALWAYS);
		scrollPane.setBounds(14, 82, 830, 513);
		panel_5.add(scrollPane);
		
		JPanel panel_1 = new JPanel();
		Dimension ds = new Dimension(1200, 1200);  
		panel_1.setPreferredSize(ds);
		scrollPane.setViewportView(panel_1);
		panel_1.setLayout(null);
		
		new ShowRoom(panel_1);//初始化窗口显示所有房间
		panel_1.setBorder(new LineBorder(Color.ORANGE, 1, true));
		panel_1.setBackground(Color.WHITE);
		
		JPanel panel_2 = new JPanel();
		panel_2.setForeground(Color.WHITE);
		panel_2.setAutoscrolls(true);
		panel_2.setBounds(850, 13, 200, 582);
		panel_2.setBorder(new LineBorder(Color.ORANGE, 1, true));
		panel_2.setBackground(Color.WHITE);
		panel_5.add(panel_2);
		panel_2.setLayout(null);
		
		JLabel label_2 = new JLabel("房态");
		label_2.setBounds(0, 0, 200, 30);
		label_2.setOpaque(true);
		label_2.setHorizontalAlignment(SwingConstants.CENTER);
		label_2.setBackground(Color.ORANGE);
		panel_2.add(label_2);
		
		JLabel label_3 = new JLabel("便签");
		label_3.setBounds(0, 285, 200, 30);
		label_3.setOpaque(true);
		label_3.setHorizontalAlignment(SwingConstants.CENTER);
		label_3.setBackground(Color.ORANGE);
		panel_2.add(label_3);
		
		JCheckBox checkBox_8 = new JCheckBox("空房净");
		buttonGroup_6.add(checkBox_8);
		checkBox_8.addItemListener(new ItemListener() {//监听右1
			public void itemStateChanged(ItemEvent e) {
				panel_1.removeAll();
				List<Room> query = new ArrayList<>();
				for(Room a : AddData.getList2()) {
					if(a.getRoomstata()==1)
						query.add(a);
				}
				new ShowRoom(panel_1,query);
				panel_5.updateUI();
			}
		});
		checkBox_8.setFocusPainted(false);
		checkBox_8.setBackground(Color.WHITE);
		checkBox_8.setBounds(20, 65, 80, 27);
		panel_2.add(checkBox_8);
		
		JCheckBox checkBox_9 = new JCheckBox("空房脏");
		buttonGroup_6.add(checkBox_9);
		checkBox_9.addItemListener(new ItemListener() {//监听右2
			public void itemStateChanged(ItemEvent e) {
				panel_1.removeAll();
				List<Room> query = new ArrayList<>();
				for(Room a : AddData.getList2()) {
					if(a.getRoomstata()==2)
						query.add(a);
				}
				new ShowRoom(panel_1,query);
				panel_5.updateUI();
			}
		});
		checkBox_9.setFocusPainted(false);
		checkBox_9.setBackground(Color.WHITE);
		checkBox_9.setBounds(108, 65, 80, 27);
		panel_2.add(checkBox_9);
		
		JCheckBox checkBox_10 = new JCheckBox("住人净");
		buttonGroup_6.add(checkBox_10);
		checkBox_10.addItemListener(new ItemListener() {//监听右3
			public void itemStateChanged(ItemEvent e) {
				panel_1.removeAll();
				List<Room> query = new ArrayList<>();
				for(Room a : AddData.getList2()) {
					if(a.getRoomstata()==3)
						query.add(a);
				}
				new ShowRoom(panel_1,query);
				panel_5.updateUI();
			}
		});
		checkBox_10.setFocusPainted(false);
		checkBox_10.setBackground(Color.WHITE);
		checkBox_10.setBounds(20, 90, 80, 27);
		
		panel_2.add(checkBox_10);
		
		JCheckBox checkBox_11 = new JCheckBox("住人脏");
		buttonGroup_6.add(checkBox_11);
		checkBox_11.addItemListener(new ItemListener() {//监听右4
			public void itemStateChanged(ItemEvent e) {
				panel_1.removeAll();
				List<Room> query = new ArrayList<>();
				for(Room a : AddData.getList2()) {
					if(a.getRoomstata()==4)
						query.add(a);
				}
				new ShowRoom(panel_1,query);
				panel_5.updateUI();
			}
		});
		checkBox_11.setFocusPainted(false);
		checkBox_11.setBackground(Color.WHITE);
		checkBox_11.setBounds(108, 90, 80, 27);
		panel_2.add(checkBox_11);
		
		JCheckBox checkBox_12 = new JCheckBox("维修");
		buttonGroup_6.add(checkBox_12);
		checkBox_12.addItemListener(new ItemListener() {//监听右5
			public void itemStateChanged(ItemEvent e) {
				panel_1.removeAll();
				List<Room> query = new ArrayList<>();
				for(Room a : AddData.getList2()) {
					if(a.getRoomstata()==5)
						query.add(a);
				}
				new ShowRoom(panel_1,query);
				panel_5.updateUI();
			}
		});
		checkBox_12.setFocusPainted(false);
		checkBox_12.setBackground(Color.WHITE);
		checkBox_12.setBounds(20, 115, 80, 27);
		panel_2.add(checkBox_12);
		
		JCheckBox checkBox_13 = new JCheckBox("预约");
		buttonGroup_6.add(checkBox_13);
		checkBox_13.addItemListener(new ItemListener() {//监听右6
			public void itemStateChanged(ItemEvent e) {
				panel_1.removeAll();
				List<Room> query = new ArrayList<>();
				for(Room a : AddData.getList2()) {
					if(a.getRoomstata()==6)
						query.add(a);
				}
				new ShowRoom(panel_1,query);
				panel_5.updateUI();
			}
		});
		checkBox_13.setFocusPainted(false);
		checkBox_13.setBackground(Color.WHITE);
		checkBox_13.setBounds(108, 115, 80, 27);
		panel_2.add(checkBox_13);
		
		JCheckBox checkBox_6 = new JCheckBox("单人房");
		buttonGroup_7.add(checkBox_6);
		checkBox_6.addItemListener(new ItemListener() {//监听右8
			public void itemStateChanged(ItemEvent e) {
				panel_1.removeAll();
				List<Room> query = new ArrayList<>();
				for(Room a : AddData.getList2()) {
					if(a.getRoomclassid()==10001||a.getRoomclassid()==10003)
						query.add(a);
				}
				new ShowRoom(panel_1,query);
				panel_5.updateUI();
			}
		});
		checkBox_6.setFocusPainted(false);
		checkBox_6.setBackground(Color.WHITE);
		checkBox_6.setBounds(20, 180, 110, 27);
		panel_2.add(checkBox_6);
		
		JCheckBox checkBox_7 = new JCheckBox("双人房");
		buttonGroup_7.add(checkBox_7);
		checkBox_7.addItemListener(new ItemListener() {//监听右9
			public void itemStateChanged(ItemEvent e) {
				panel_1.removeAll();
				List<Room> query = new ArrayList<>();
				for(Room a : AddData.getList2()) {
					if(a.getRoomclassid()==10002||a.getRoomclassid()==10004)
						query.add(a);
				}
				new ShowRoom(panel_1,query);
				panel_5.updateUI();
			}
		});
		checkBox_7.setFocusPainted(false);
		checkBox_7.setBackground(Color.WHITE);
		checkBox_7.setBounds(20, 205, 80, 27);
		panel_2.add(checkBox_7);
		
		JLabel label_8 = new JLabel("房态");
		label_8.setForeground(Color.ORANGE);
		label_8.setBounds(25, 40, 72, 18);
		panel_2.add(label_8);
		
		JSeparator separator_1 = new JSeparator();
		separator_1.setBackground(Color.LIGHT_GRAY);
		separator_1.setBounds(25, 60, 150, 2);
		panel_2.add(separator_1);
		
		JLabel label_9 = new JLabel("房态");
		label_9.setForeground(Color.ORANGE);
		label_9.setBounds(20, 155, 72, 18);
		panel_2.add(label_9);
		
		JSeparator separator_2 = new JSeparator();
		separator_2.setBackground(Color.LIGHT_GRAY);
		separator_2.setBounds(20, 175, 150, 2);
		panel_2.add(separator_2);
		
		JCheckBox checkBox_14 = new JCheckBox("商务套房");
		buttonGroup_7.add(checkBox_14);
		checkBox_14.addItemListener(new ItemListener() {//监听右9
			public void itemStateChanged(ItemEvent e) {
				panel_1.removeAll();
				List<Room> query = new ArrayList<>();
				for(Room a : AddData.getList2()) {
					if(a.getRoomclassid()==10005)
						query.add(a);
				}
				new ShowRoom(panel_1,query);
				panel_5.updateUI();
			}
		});
		checkBox_14.setFocusPainted(false);
		checkBox_14.setBackground(Color.WHITE);
		checkBox_14.setBounds(20, 230, 90, 27);
		panel_2.add(checkBox_14);
		
		JCheckBox checkBox_15 = new JCheckBox("总统套房");
		buttonGroup_7.add(checkBox_15);
		checkBox_15.addItemListener(new ItemListener() {//监听右10
			public void itemStateChanged(ItemEvent e) {
				panel_1.removeAll();
				List<Room> query = new ArrayList<>();
				for(Room a : AddData.getList2()) {
					if(a.getRoomclassid()==10006)
						query.add(a);
				}
				new ShowRoom(panel_1,query);
				panel_5.updateUI();
			}
		});
		checkBox_15.setFocusPainted(false);
		checkBox_15.setBackground(Color.WHITE);
		checkBox_15.setBounds(20, 255, 90, 27);
		panel_2.add(checkBox_15);
		
		JSeparator separator_3 = new JSeparator();
		separator_3.setForeground(Color.ORANGE);
		separator_3.setBackground(Color.ORANGE);
		separator_3.setBounds(0, 145, 200, 2);
		panel_2.add(separator_3);
		
		JTextArea textArea = new JTextArea();
		textArea.setForeground(Color.ORANGE);
		textArea.setLineWrap(true);
		textArea.setFont(new Font("楷体", Font.PLAIN, 20));
		textArea.setBounds(1, 315, 198, 270);
		panel_2.add(textArea);
		
		JSeparator separator = new JSeparator();
		separator.setBounds(0, 0, 1052, 2);
		panel_5.add(separator);
		separator.setForeground(Color.WHITE);
		separator.setOpaque(true);
		separator.setBackground(Color.ORANGE);
		
		JCheckBox checkBox = new JCheckBox("单人房");
		buttonGroup_5.add(checkBox);
		checkBox.setFocusPainted(false);
		checkBox.setFocusPainted(false);
		checkBox.addItemListener(new ItemListener() {//监听1
			public void itemStateChanged(ItemEvent e) {
				panel_1.removeAll();
				List<Room> query = new ArrayList<>();
				for(Room a : AddData.getList2()) {
					if(a.getRoomclassid()==10001)
						query.add(a);
				}
				new ShowRoom(panel_1,query);
				panel_5.updateUI();
			}
		});
		checkBox.setBounds(82, 13, 80, 27);
		checkBox.setBackground(Color.WHITE);
		panel_5.add(checkBox);
		JCheckBox checkBox_1 = new JCheckBox("双人房");
		buttonGroup_5.add(checkBox_1);
		checkBox_1.addItemListener(new ItemListener() {//监听2
			public void itemStateChanged(ItemEvent e) {
				panel_1.removeAll();
				List<Room> query = new ArrayList<>();
				for(Room a : AddData.getList2()) {
					if(a.getRoomclassid()==10002)
						query.add(a);
				}
				new ShowRoom(panel_1,query);
				panel_5.updateUI();
			}
		});
		checkBox_1.setFocusPainted(false);
		checkBox_1.setBounds(172, 13, 80, 27);
		checkBox_1.setBackground(Color.WHITE);
		panel_5.add(checkBox_1);
		
		JLabel label_7 = new JLabel("标准型:");
		label_7.setForeground(Color.ORANGE);
		label_7.setBackground(Color.WHITE);
		label_7.setBounds(25, 17, 60, 18);
		panel_5.add(label_7);
		
		JLabel lblNewLabel = new JLabel("豪华型:");
		lblNewLabel.setForeground(Color.ORANGE);
		lblNewLabel.setBounds(25, 51, 70, 18);
		panel_5.add(lblNewLabel);
		
		JCheckBox checkBox_4 = new JCheckBox("单人房");
		buttonGroup_5.add(checkBox_4);
		checkBox_4.addItemListener(new ItemListener() {//监听3
			public void itemStateChanged(ItemEvent e) {
				panel_1.removeAll();
				List<Room> query = new ArrayList<>();
				for(Room a : AddData.getList2()) {
					if(a.getRoomclassid()==10003)
						query.add(a);
				}
				new ShowRoom(panel_1,query);
				panel_5.updateUI();
			}
		});
		checkBox_4.setFocusPainted(false);
		checkBox_4.setBounds(82, 47, 75, 27);
		checkBox_4.setBackground(Color.WHITE);
		panel_5.add(checkBox_4);
		
		JCheckBox checkBox_5 = new JCheckBox("双人房");
		buttonGroup_5.add(checkBox_5);
		checkBox_5.addItemListener(new ItemListener() {//监听4
			public void itemStateChanged(ItemEvent e) {
				panel_1.removeAll();
				List<Room> query = new ArrayList<>();
				for(Room a : AddData.getList2()) {
					if(a.getRoomclassid()==10004)
						query.add(a);
				}
				new ShowRoom(panel_1,query);
				panel_5.updateUI();
			}
		});
		checkBox_5.setFocusPainted(false);
		checkBox_5.setBounds(173, 47, 80, 27);
		checkBox_5.setBackground(Color.WHITE);
		panel_5.add(checkBox_5);
		
		JCheckBox checkBox_2 = new JCheckBox("商务套房");
		buttonGroup_5.add(checkBox_2);
		checkBox_2.addItemListener(new ItemListener() {//监听5
			public void itemStateChanged(ItemEvent e) {
				panel_1.removeAll();
				List<Room> query = new ArrayList<>();
				for(Room a : AddData.getList2()) {
					if(a.getRoomclassid()==10005)
						query.add(a);
				}
				new ShowRoom(panel_1,query);
				panel_5.updateUI();
			}
		});
		checkBox_2.setFocusPainted(false);
		checkBox_2.setBackground(Color.WHITE);
		checkBox_2.setBounds(265, 46, 90, 27);
		panel_5.add(checkBox_2);
		
		JCheckBox checkBox_3 = new JCheckBox("总统套房");
		buttonGroup_5.add(checkBox_3);
		checkBox_3.addItemListener(new ItemListener() {//监听6
			public void itemStateChanged(ItemEvent e) {
				panel_1.removeAll();
				List<Room> query = new ArrayList<>();
				for(Room a : AddData.getList2()) {
					if(a.getRoomclassid()==10006)
						query.add(a);
				}
				new ShowRoom(panel_1,query);
				panel_5.updateUI();
			}
		});
		checkBox_3.setFocusPainted(false);
		checkBox_3.setBackground(Color.WHITE);
		checkBox_3.setBounds(376, 46, 90, 27);
		panel_5.add(checkBox_3);
		
		JCheckBox checkBox_16 = new JCheckBox("所有房间");
		buttonGroup_5.add(checkBox_16);
		checkBox_16.addItemListener(new ItemListener() {//监听6
			public void itemStateChanged(ItemEvent e) {
				panel_1.removeAll();
				List<Room> query = new ArrayList<>();
				for(Room a : AddData.getList2()) {
						query.add(a);
				}
				new ShowRoom(panel_1,query);
				panel_5.updateUI();
			}
		});
		checkBox_16.setFocusPainted(false);
		checkBox_16.setBackground(Color.WHITE);
		checkBox_16.setBounds(744, 13, 80, 27);
		panel_5.add(checkBox_16);
		
		JPanel panel_6 = new JPanel();
		panel_6.setBorder(new LineBorder(new Color(0, 0, 0)));
		panel_6.setBounds(0, 730, 1182, 23);
		contentPane.add(panel_6);
		panel_6.setLayout(null);
		
		JLabel label_4 = new JLabel("宜爱酒店客房管理系统");
		label_4.setBorder(new EmptyBorder(0, 0, 0, 0));
		label_4.setOpaque(true);
		label_4.setBackground(new Color(240, 255, 240));
		label_4.setHorizontalAlignment(SwingConstants.CENTER);
		label_4.setBounds(0, 0, 500, 23);
		panel_6.add(label_4);
		
		GetTime Time = new GetTime();
		JLabel label_5 = new JLabel("当前系统时间："+Time.getTime());
		label_5.setBorder(new EmptyBorder(0, 0, 0, 0));
		label_5.setBackground(new Color(240, 255, 240));
		label_5.setHorizontalAlignment(SwingConstants.CENTER);
		label_5.setOpaque(true);
		label_5.setBounds(500, 0, 400, 23);
		panel_6.add(label_5);
		
		JLabel label_6 = new JLabel("当前用户："+powername);
		label_6.setBorder(new EmptyBorder(0, 0, 0, 0));
		label_6.setHorizontalAlignment(SwingConstants.CENTER);
		label_6.setOpaque(true);
		label_6.setBackground(new Color(240, 255, 240));
		label_6.setBounds(899, 0, 283, 23);
		panel_6.add(label_6);
		setVisible(true);
	}
	@SuppressWarnings("unused")
	private static void addPopup(Component component, final JPopupMenu popup) {
		component.addMouseListener(new MouseAdapter() {
			public void mousePressed(MouseEvent e) {
				if (e.isPopupTrigger()) {
					showMenu(e);
				}
			}
			public void mouseReleased(MouseEvent e) {
				if (e.isPopupTrigger()) {
					showMenu(e);
				}
			}
			private void showMenu(MouseEvent e) {
				popup.show(e.getComponent(), e.getX(), e.getY());
			}
		});
	}
}
