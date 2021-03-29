package frame.mainframe;

import java.util.List;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.border.LineBorder;
import java.awt.Color;
import java.awt.Component;
import java.awt.SystemColor;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.SwingConstants;
import javax.swing.JTextField;
import javax.swing.ListSelectionModel;
import javax.swing.JSeparator;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JTable;
import javax.swing.JScrollPane;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.table.DefaultTableModel;
import dataobject.Client;
import dataobject.Room;
import frame.roomopen.*;
import readywork.AddData;
import java.awt.Toolkit;
import java.util.Vector;
import java.awt.event.ItemListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.FocusAdapter;
import java.awt.event.FocusEvent;
import function.add.AddItem;
import function.query.*;
import function.updata.UpDataItem;

public class RoomOpen extends JFrame {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	public static List<Room> list = AddData.getList2();
	public static List<Client> list1 = AddData.getList1();
	private JPanel contentPane;
	private JTextField textField;
	private JTextField textField_1;
	private JTextField textField_2;
	private JTextField textField_3;
	private JTextField textField_4;
	private JTextField textField_5;
	private JTextField textField_6;
	private JTextField textField_7;
	private JTextField textField_8;
	public Object data1,data2;
	int count,count1=0;
	
	@SuppressWarnings({ "rawtypes", "unchecked", "unused" })
	public RoomOpen() {
		setVisible(true);
		setTitle("酒店-开房");
		setIconImage(Toolkit.getDefaultToolkit().getImage("img/宜微.png"));
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		setBounds(100, 100, 700, 600);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		JPanel panel = new JPanel();
		panel.setBackground(Color.ORANGE);
		panel.setBorder(new LineBorder(Color.ORANGE));
		panel.setBounds(15, 5, 120, 30);
		contentPane.add(panel);
		panel.setLayout(null);
		
		JLabel lblNewLabel_1 = new JLabel("开房");
		lblNewLabel_1.setHorizontalAlignment(SwingConstants.CENTER);
		lblNewLabel_1.setBounds(0, 0, 120, 30);
		panel.add(lblNewLabel_1);
		
		JPanel panel_1 = new JPanel();
		panel_1.setBackground(Color.WHITE);
		panel_1.setBorder(new LineBorder(Color.ORANGE));
		panel_1.setBounds(5, 35, 670, 510);
		contentPane.add(panel_1);
		panel_1.setLayout(null);
		
		JPanel panel_2 = new JPanel();
		panel_2.setBackground(Color.WHITE);
		panel_2.setBorder(new LineBorder(Color.ORANGE));
		panel_2.setBounds(10, 10, 320, 240);
		panel_1.add(panel_2);
		panel_2.setLayout(null);
		
		JLabel lblNewLabel = new JLabel("房间信息");
		lblNewLabel.setHorizontalAlignment(SwingConstants.CENTER);
		lblNewLabel.setOpaque(true);
		lblNewLabel.setBackground(SystemColor.controlHighlight);
		lblNewLabel.setBounds(0, 0, 320, 25);
		panel_2.add(lblNewLabel);
		
		JLabel label_1 = new JLabel("房间类型：");
		label_1.setHorizontalAlignment(SwingConstants.RIGHT);
		label_1.setBounds(0, 30, 160, 25);
		panel_2.add(label_1);
		
		
		
		JButton button_2 = new JButton("添加到开单区");
		button_2.setFocusPainted(false);
		button_2.setBounds(0, 215, 320, 25);
		panel_2.add(button_2);
		
		JScrollPane scrollPane = new JScrollPane();
		scrollPane.setBorder(new EmptyBorder(0, 0, 0, 0));
		scrollPane.setBounds(1, 60, 318, 155);
		panel_2.add(scrollPane);
		
		
		JPanel panel_3 = new JPanel();
		panel_3.setBackground(Color.WHITE);
		panel_3.setBorder(new LineBorder(Color.ORANGE));
		panel_3.setBounds(340, 10, 320, 240);
		panel_1.add(panel_3);
		panel_3.setLayout(null);
		JScrollPane scrollPane1 = new JScrollPane();
		scrollPane1.setBorder(new EmptyBorder(0, 0, 0, 0));
		scrollPane1.setBounds(1, 25, 318, 190);
		panel_3.add(scrollPane1);
		
		
		DefaultTableModel tableModel;
		JTable jtable;
		Vector dataTitle = new Vector();//列名
		Vector data = new Vector();//数据内容
		
		dataTitle.add("房间");
		dataTitle.add("价格(元)");
		
		for(Room a : list) {
			if(a.getRoomstata()==1) {
				Vector W = new Vector();
				W.add(a.getRoomid());
				W.add(a.getRoomprice());
				data.add(W);}
		}
		
		tableModel = new DefaultTableModel(data,dataTitle);
		jtable = new JTable(tableModel);
		jtable.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		
		try//设置背景色为双色显示
		{
			DefaultTableCellRenderer tcr = new DefaultTableCellRenderer(){
				private static final long serialVersionUID = 1L;
				@Override
				public Component getTableCellRendererComponent(JTable table,Object value, boolean isSelected, boolean hasFocus,int row, int column){
					if(row%2 == 0)
						setBackground(Color.WHITE);//设置奇数行底色
					else if(row%2 == 1)
						setBackground(new Color(220,230,241));//设置偶数行底色
					return super.getTableCellRendererComponent(table, value,isSelected, hasFocus, row, column);
				}
			};
			for(int i = 0; i < jtable.getColumnCount(); i++) {
				jtable.getColumn(jtable.getColumnName(i)).setCellRenderer(tcr);
			}
			tcr.setHorizontalAlignment(JLabel.CENTER);//设置文字居中显示
		}
		catch (Exception e){
			e.printStackTrace();
		}

		
		jtable.setBorder(new EmptyBorder(0, 0, 0, 0));
		jtable.getTableHeader().setBackground(new Color(78,78,78));
		jtable.getTableHeader().setForeground(Color.WHITE);
		jtable.setRowHeight(25);
		jtable.setRowMargin(0);
		jtable.setShowVerticalLines(false);
		jtable.setShowHorizontalLines(false);
		
		jtable.setOpaque(false);
		scrollPane.setViewportView(jtable);
	
		Vector vData = new Vector();
		DefaultTableModel model = new DefaultTableModel(vData,dataTitle);
		JTable jTable1 = new JTable(model);
		jTable1.setModel(model);
		Vector vRow1 = new Vector();
		scrollPane1.setViewportView(jTable1);
	
		DataRow dr = new DataRow();
		
		
		jTable1.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		
		jTable1.setBorder(new EmptyBorder(0, 0, 0, 0));
		jTable1.getTableHeader().setBackground(new Color(78,78,78));
		jTable1.getTableHeader().setForeground(Color.WHITE);
		jTable1.setRowHeight(25);
		jTable1.setRowMargin(0);
		jTable1.setShowVerticalLines(false);
		jTable1.setShowHorizontalLines(false);
		
		jtable.addMouseListener(new MouseAdapter() {//开单区监听
				public void mouseClicked(MouseEvent e) {
					//为表格添加鼠标事件监听器(单击事件)
						count1--;
					int selectRow = jtable.getSelectedRow();//获取鼠标选择行的索引值
					count = 1;//记录按钮点击次数
					if(selectRow==-1) {
						JOptionPane.showMessageDialog(null, "找不到索引值");
					}
					else {
						Object selectValues1 = jtable.getValueAt(selectRow, 0);//获取选择的单元格的内容
						Object selectValues2 = jtable.getValueAt(selectRow, 1);
						data1 = selectValues1;
						data2 = selectValues2;
						Object obj[] = {data1,data2};
						button_2.addActionListener(new ActionListener() {
							public void actionPerformed(ActionEvent e) {
								if(count == 1) {
									model.addRow(obj);
									tableModel.removeRow(selectRow);
									count--;
								}	
							}
						});	
					}		
			}
		});

		JLabel label = new JLabel("开单房间");
		label.setHorizontalAlignment(SwingConstants.CENTER);
		label.setOpaque(true);
		label.setBackground(SystemColor.controlHighlight);
		label.setBounds(0, 0, 320, 25);
		panel_3.add(label);
		
		JButton button_3 = new JButton("从开单区移除");
		button_3.setFocusPainted(false);
		
		jTable1.addMouseListener(new MouseAdapter() {//从开单区移除监听
			public void mouseClicked(MouseEvent e) {
				int selectRow = jTable1.getSelectedRow();//获取鼠标选择行的索引值
				count = 1;//记录按钮点击次数
				if(selectRow==-1) {
					JOptionPane.showMessageDialog(null, "找不到索引值");
				}
				else {
				button_3.addActionListener(new ActionListener() {
					public void actionPerformed(ActionEvent e) {
						if(count == 1) {
						Object selectValues1 = jTable1.getValueAt(selectRow, 0);//获取选择的单元格的内容
						Object selectValues2 = jTable1.getValueAt(selectRow, 1);
						data1 = selectValues1;
						data2 = selectValues2;
						Object obj[] = {data1,data2};
						
						tableModel.addRow(obj);  //添加一行
						model.removeRow(selectRow);
						count--;
						}
					}
				});
			}}
		});
		
		button_3.setBounds(0, 215, 320, 25);
		panel_3.add(button_3);
		
		String str[] = { "标准单人房", "标准双人房", "豪华单人房", "豪华双人房", "商务套房","总统套房"};
		JTextField text = new JTextField(10);
		JComboBox cbx = new JComboBox(str);
		
		
		cbx.addItemListener(new ItemListener() {
			  
			@Override
			public void itemStateChanged(ItemEvent e) {
			    if(e.getStateChange() == ItemEvent.SELECTED){
					if (cbx.getSelectedIndex() == 0) {//選擇的是標準單人房			
						new Get_Data(model,tableModel,"150.0");//获取房间和价格信息并去重	
						}
					else if(cbx.getSelectedIndex()==1) {//選擇的是標準雙人房
						new Get_Data(model,tableModel,"180.0");//获取房间和价格信息并去重	
						}			
					else if(cbx.getSelectedIndex()==2) {//選擇的是豪華單人房
						new Get_Data(model,tableModel,"250.0");
					}					
					else if(cbx.getSelectedIndex()==3) {//選擇的是豪華雙人房
						new Get_Data(model,tableModel,"280.0");
					}
					else if(cbx.getSelectedIndex()==4) {//選擇的是商務套房
						new Get_Data(model,tableModel,"380.0");
					}		
					else if(cbx.getSelectedIndex()==5){//選擇的是總統套房
						new Get_Data(model,tableModel,"480.0");
					}
			    }
			}
		});
		cbx.setBackground(Color.WHITE);
		cbx.setBounds(180, 30, 100, 25);
		panel_2.add(cbx);
		
		
		JPanel panel_4 = new JPanel();
		panel_4.setBackground(SystemColor.control);
		panel_4.setBorder(new LineBorder(Color.ORANGE));
		panel_4.setBounds(10, 260, 650, 240);
		panel_1.add(panel_4);
		panel_4.setLayout(null);
		
		JLabel label_2 = new JLabel("客户名字：");
		label_2.setBounds(10, 10, 80, 25);
		panel_4.add(label_2);
		
		textField = new JTextField();
		textField.setBounds(85, 10, 100, 25);
		panel_4.add(textField);
		textField.setColumns(10);
		
		JLabel label_3 = new JLabel("客户性别：");
		label_3.setBounds(230, 10, 80, 25);
		panel_4.add(label_3);
		
		String gender[] = {"男","女"};
		JComboBox com = new JComboBox(gender);
		com.setBounds(310, 10, 50, 25);
		panel_4.add(com);
		
		JLabel label_4 = new JLabel("客户年龄：");
		label_4.setBounds(450, 10, 80, 25);
		panel_4.add(label_4);
		
		textField_1 = new JTextField();
		textField_1.addFocusListener(new FocusAdapter() {
			@Override
			public void focusLost(FocusEvent e) {
				ImageIcon icon = new ImageIcon("img/error.png");
				if(!limited.AgeLimited.isAge(textField_1.getText())) {
					JOptionPane.showMessageDialog(null,"年龄格式输入有误，请重新输入！", "错误提示", JOptionPane.ERROR_MESSAGE, icon);
					textField_1.setText("");
				}
			}
		});
		textField_1.setBounds(525, 10, 100, 25);
		panel_4.add(textField_1);
		textField_1.setColumns(10);
		
		JLabel label_5 = new JLabel("证件编号：");
		label_5.setBounds(10, 45, 80, 25);
		panel_4.add(label_5);
		
		textField_2 = new JTextField();
		textField_2.addFocusListener(new FocusAdapter() {
			@Override
			public void focusLost(FocusEvent e) {
				ImageIcon icon = new ImageIcon("img/error.png");
				if(!limited.TestRegex02.isId(textField_2.getText())) {//身份证15位或18位限定输入
					JOptionPane.showMessageDialog(null,"身份证号码格式输入有误，请重新输入！", "错误提示", JOptionPane.ERROR_MESSAGE, icon);
					textField_2.setText("");
				}else {
					List<Client> query = Query.clientquery(list1, textField_2.getText());
					if(!query.isEmpty())
						for(Client a :query) {
							textField.setText(a.getClientname());//匹配名字
							textField_1.setText(""+a.getClientage());//匹配年龄
							textField_3.setText(a.getClientphone());//匹配手机号码
							textField_4.setText(a.getClientemail());//匹配邮箱
							textField_6.setText(a.getClientaddress());//匹配用户住址
							com.setSelectedIndex(a.getClientsex());//匹配性别（1表示女，0表示男）
							query.clear();
							break;
						}
						
//					textField.setText("");//匹配名字
//					textField_1.setText("");//匹配年龄
//					textField_3.setText("");//匹配手机号码
//					textField_4.setText("");//匹配邮箱
//					textField_6.setText("");//匹配用户住址
//					com.setSelectedIndex(1);//匹配性别（1表示女，0表示男）
				}
			}
		});
		textField_2.setBounds(85, 45, 100, 25);
		panel_4.add(textField_2);
		textField_2.setColumns(10);
		
		JLabel label_6 = new JLabel("手机号码：");
		label_6.setBounds(230, 45, 80, 25);
		panel_4.add(label_6);
		
		textField_3 = new JTextField();
		textField_3.setColumns(10);
		textField_3.setBounds(310, 45, 100, 25);
		textField_3.addFocusListener(new FocusAdapter() {
			@Override
			public void focusLost(FocusEvent e) {
				ImageIcon icon = new ImageIcon("img/error.png");
				if(!limited.PhoneLimited.isPhone(textField_3.getText())) {
					JOptionPane.showMessageDialog(null,"手机号码格式输入有误，请重新输入！", "错误提示", JOptionPane.ERROR_MESSAGE, icon);
					textField_3.setText("");
				}
			}
		});
		panel_4.add(textField_3);
		
		JLabel label_7 = new JLabel("邮箱地址：");
		label_7.setBounds(450, 45, 80, 25);
		panel_4.add(label_7);
		
		
		textField_4 = new JTextField();
		textField_4.addFocusListener(new FocusAdapter() {
			@Override
			public void focusLost(FocusEvent e) {
				ImageIcon icon = new ImageIcon("img/紧急邮件.png");
				if(!limited.TestRegex01.isRightSytax(textField_4.getText())) {//判断邮箱输入格式
					JOptionPane.showMessageDialog(null,"邮箱格式输入有误，请重新输入！", "错误提示", JOptionPane.ERROR_MESSAGE, icon);
					textField_4.setText("");
				}
			}
		});
		textField_4.setColumns(10);
		textField_4.setBounds(525, 45, 100, 25);
		panel_4.add(textField_4);
		
		JLabel label_8 = new JLabel("住房人数：");
		label_8.setBounds(10, 80, 80, 25);
		panel_4.add(label_8);
		
		textField_5 = new JTextField();
		textField_5.setColumns(10);
		textField_5.setBounds(85, 80, 100, 25);
		textField_5.addFocusListener(new FocusAdapter() {
			@Override
			public void focusLost(FocusEvent e) {
				ImageIcon icon = new ImageIcon("img/error.png");
				if(!limited.MemberLimited.isMember(textField_5.getText())) {
					JOptionPane.showMessageDialog(null,"住房人数格式输入有误，请重新输入！", "错误提示", JOptionPane.ERROR_MESSAGE, icon);
					textField_5.setText("");
				}
			}
		});
		panel_4.add(textField_5);
		
		JLabel label_9 = new JLabel("客户地址：");
		label_9.setBounds(10, 115, 80, 25);
		panel_4.add(label_9);
		
		textField_6 = new JTextField();
		textField_6.setColumns(10);
		textField_6.setBounds(85, 115, 540, 25);
		panel_4.add(textField_6);
		
		JLabel label_10 = new JLabel("备注信息：");
		label_10.setBounds(10, 150, 80, 25);
		panel_4.add(label_10);
		
		textField_7 = new JTextField();
		textField_7.setColumns(10);
		textField_7.setBounds(85, 150, 540, 25);
		panel_4.add(textField_7);
		
		JSeparator separator = new JSeparator();
		separator.setBounds(10, 185, 615, 2);
		panel_4.add(separator);
		
		JButton button = new JButton("确定");
		button.setFocusPainted(false);
		button.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				int roomnum = jTable1.getColumnCount()-1;
				int pa;
				int[] roomname = new int[1];
				String clientclassname = "普通用户";
				for(int i = 0; i < roomnum; i++) {
			    	pa = Integer.parseInt(""+jTable1.getValueAt(i,0));
					roomname[0] = pa;
					if(Query.clientquery(list1, textField_2.getText()).isEmpty()) {
						AddItem.addclient(textField.getText(), textField_2.getText(), com.getSelectedIndex(),Integer.parseInt(textField_1.getText()), textField_3.getText(), textField_4.getText(), textField_6.getText(), clientclassname);
						AddItem.addorderdata(textField_2.getText(), roomnum, roomname, Integer.parseInt(textField_8.getText()), textField_7.getText());
					}else {
//						System.out.println(roomname[0]);
						AddItem.addorderdata(textField_2.getText(), roomnum, roomname, Integer.parseInt(textField_8.getText()), textField_7.getText());
					}
					//System.out.println(roomname[i]);
					UpDataItem.updataroom(roomname[0], 3);
				}
				
				
//				for (int i = 0; i < jTable1.getColumnCount()-1; i++) {
//					int a = Integer.parseInt(""+jTable1.getValueAt(i,0));
//					System.out.print(a+" ");//房间号录入
//					System.out.print(textField.getText()+" ");//客户姓名录入
//					System.out.print(com.getSelectedIndex()+" ");//客户性别录入
//					System.out.print(textField_1.getText()+" ");//客户年龄录入
//					System.out.print(textField_2.getText()+" ");//证件号录入
//					System.out.print(textField_3.getText()+" ");//手机号录入
//					System.out.print(textField_4.getText()+" ");//邮箱号录入
//					System.out.print(textField_5.getText()+" ");//住房人数录入
//					System.out.print(Integer.parseInt(textField_8.getText())+" ");//预住天数录入
//					System.out.print(textField_6.getText()+" ");//客户地址录入
//					System.out.print(textField_7.getText()+" ");//备注信息录入
//				}


			}
		});
		button.setBounds(170, 200, 113, 27);
		panel_4.add(button);
		
		JButton button_1 = new JButton("取消");
		button_1.setFocusPainted(false);
		button_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
			}
		});
		button_1.setBounds(370, 200, 113, 27);
		panel_4.add(button_1);
		
		JLabel label_11 = new JLabel("预住天数：");
		label_11.setBounds(230, 80, 80, 25);
		panel_4.add(label_11);
		
		textField_8 = new JTextField();
		textField_8.setColumns(10);
		textField_8.setBounds(310, 80, 100, 25);
		textField_8.addFocusListener(new FocusAdapter() {
			@Override
			public void focusLost(FocusEvent e) {
				ImageIcon icon = new ImageIcon("img/error.png");
				if(!limited.Daylimited.isDay(textField_8.getText())) {
					JOptionPane.showMessageDialog(null,"天数格式输入有误，请重新输入！", "错误提示", JOptionPane.ERROR_MESSAGE, icon);
					textField_4.setText("");
				}
			}
		});
		panel_4.add(textField_8);
		setVisible(true);
	}
}
