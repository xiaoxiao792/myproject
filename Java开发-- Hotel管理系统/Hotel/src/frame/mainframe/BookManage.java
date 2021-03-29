package frame.mainframe;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JSeparator;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.ListSelectionModel;
import javax.swing.border.LineBorder;
import java.awt.Color;
import java.awt.Component;
import javax.swing.table.DefaultTableCellRenderer;
import dataobject.ReserveData;
import function.query.Query;
import function.updata.UpDataItem;
import readywork.AddData;
import java.awt.SystemColor;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JButton;
import javax.swing.SwingConstants;
import javax.swing.ImageIcon;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.List;
import java.util.Vector;
import javax.swing.JScrollPane;
import java.awt.Toolkit;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

public class BookManage extends JFrame {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	public static List<ReserveData> list = AddData.getList4();
	private JPanel contentPane;
	private JTextField textField;
	private JTable jtable;
	private TableModel tableModel;
	@SuppressWarnings("unused")
	private int count;
	public static void main(String[] args) {
		new BookManage().setVisible(true);
	}
	/**
	 * Create the frame.
	 */
	@SuppressWarnings({ "unchecked", "rawtypes", "unused" })
	public BookManage() {
		setTitle("酒店-预订管理");
		setIconImage(Toolkit.getDefaultToolkit().getImage("img/宜微.png"));
		setForeground(SystemColor.control);
		setBackground(Color.LIGHT_GRAY);
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		setBounds(100, 100, 900, 600);
		contentPane = new JPanel();
		contentPane.setBackground(Color.WHITE);
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		JPanel panel = new JPanel();
		panel.setBackground(new Color(0,158,241));
		panel.setBounds(10, 2, 120, 30);
		contentPane.add(panel);
		panel.setLayout(null);
		
		JLabel label = new JLabel("预订管理");
		label.setOpaque(true);
		label.setBackground(Color.GREEN);
		label.setHorizontalAlignment(SwingConstants.CENTER);
		label.setBounds(0, 0, 120, 30);
		panel.add(label);
		
		JPanel panel_1 = new JPanel();
		panel_1.setForeground(Color.WHITE);
		panel_1.setBorder(new LineBorder(Color.GREEN));
		panel_1.setBackground(Color.WHITE);
		panel_1.setBounds(5, 32, 870, 515);
		contentPane.add(panel_1);
		panel_1.setLayout(null);
		
		JSeparator separator = new JSeparator();
		separator.setBounds(0, 45, 880, 2);
		panel_1.add(separator);
		
//		JButton button = new JButton("删除");
//		button.setFocusPainted(false);
//		button.setBorder(new EmptyBorder(0, 0, 0, 0));
//		button.setBounds(600, 12, 100, 26);
//		panel_1.add(button);
//		button.setForeground(Color.WHITE);
//		button.setBackground(Color.GREEN);
		
		textField = new JTextField();
		textField.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				textField.setText("");
				textField.setForeground(Color.BLACK);
			}
		});
		textField.setForeground(Color.GRAY);
		textField.setBorder(new LineBorder(Color.LIGHT_GRAY, 1, true));
		textField.setText("  输入订单编号查询");
		textField.setBounds(10, 8, 170, 30);
		panel_1.add(textField);
		textField.setColumns(10);
		
		JButton button_1 = new JButton("保存");
		button_1.setFocusPainted(false);
		button_1.setBorder(new EmptyBorder(0, 0, 0, 0));
		button_1.setForeground(Color.WHITE);
		button_1.setBackground(Color.GREEN);
		button_1.setBounds(740, 12, 100, 26);
		panel_1.add(button_1);
		
		JButton button_3 = new JButton("");
		button_3.setFocusPainted(false);
		button_3.setBorder(new LineBorder(new Color(192, 192, 192), 1, true));
		button_3.setBackground(Color.WHITE);
		button_3.setIcon(new ImageIcon("img/搜索.png"));
		button_3.setBounds(179, 8, 30, 30);
		panel_1.add(button_3);
		
		JScrollPane scrollPane = new JScrollPane();
		scrollPane.setBorder(new EmptyBorder(0, 0, 0, 0));
		scrollPane.setBounds(1, 50, 868, 460);
		panel_1.add(scrollPane);
		



		Vector dataTitle = new Vector();//列名
		Vector data = new Vector();//数据内容
		Vector hang = new Vector();
		dataTitle.add("预定订单");
		dataTitle.add("预定人");
		dataTitle.add("预定时间");
		dataTitle.add("手机号");
		dataTitle.add("邮箱地址");
		dataTitle.add("抵达日期");
		dataTitle.add("预住天数");
		dataTitle.add("排房");
		dataTitle.add("间数");
		dataTitle.add("房间号");
		dataTitle.add("状态");
		dataTitle.add("备注");

		for(ReserveData a : list) {
			String qa = "";
			for(int i = 0; i<a.getRoomnum();i++) {
				qa += a.getRoomname()[i]+" ";
			}
			Vector W = new Vector();
			W.add(a.getReserveid());
			W.add(a.getClientname());
			W.add(a.getReservetime());
			W.add(a.getClientphone());
			W.add(a.getClientemail());
			W.add(a.getStarttime());
			W.add(a.getReservedays());
			W.add(a.getIsroom());
			W.add(a.getRoomnum());
			W.add(qa);
			W.add(a.getReservestata());
			W.add(a.getRemark());
			data.add(W);
		}
		
		tableModel = new TableModel(data,dataTitle);
		jtable = new JTable(tableModel);
		tableModel.CellEditable();
		jtable.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		
		jtable.setBorder(new EmptyBorder(0, 0, 0, 0));
		jtable.getTableHeader().setBackground(new Color(78,78,78));
		jtable.getTableHeader().setForeground(Color.WHITE);
		jtable.setRowHeight(25);
		jtable.setRowMargin(0);
		jtable.setShowVerticalLines(false);
		jtable.setShowHorizontalLines(false);
		jtable.setOpaque(false);
		
		try//设置背景色为双色显示
		{
			DefaultTableCellRenderer tcr = new DefaultTableCellRenderer(){
				private static final long serialVersionUID = 1L;
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
		scrollPane.setViewportView(jtable);
		
		JButton button_4 = new JButton("增加");
		button_4.setForeground(Color.WHITE);
		button_4.setFocusPainted(false);
		button_4.setBorder(new EmptyBorder(0, 0, 0, 0));
		button_4.setBackground(Color.GREEN);
		button_4.setBounds(600, 12, 100, 26);
		panel_1.add(button_4);
		
		button_3.addActionListener(new ActionListener() {//搜索
			public void actionPerformed(ActionEvent e) {
				List<ReserveData> query = Query.reservequery(list, textField.getText());
				for(int i=0;i<tableModel.getRowCount();i++) {//將表格中的所有數據清除
					tableModel.removeRow(0);
					i=-1;
				}
				for(ReserveData a : query) {
					String qa = "";
					for(int i = 0; i<a.getRoomnum();i++) {
						qa += a.getRoomname()[i]+" ";
					}
					Vector W = new Vector();
					W.add(a.getReserveid());
					W.add(a.getClientname());
					W.add(a.getReservetime());
					W.add(a.getClientphone());
					W.add(a.getClientemail());
					W.add(a.getStarttime());
					W.add(a.getReservedays());
					W.add(a.getIsroom());
					W.add(a.getRoomnum());
					W.add(qa);
					W.add(a.getReservestata());
					W.add(a.getRemark());
					data.add(W);
				}
				query.clear();
			
			}
		});
		
//		jtable.addMouseListener(new MouseAdapter() {//删除功能监听
//			public void mouseClicked(MouseEvent e) {
//				int selectRow = jtable.getSelectedRow();//获取鼠标选择行的索引值
//				int col = jtable.getSelectedColumn();
//				count = 1;//记录按钮点击次数
//				if(selectRow==-1) {
//					JOptionPane.showMessageDialog(null, "找不到索引值");
//				}
//				else {
//				button.addActionListener(new ActionListener() {
//					public void actionPerformed(ActionEvent e) {
////						if(col==6)
////							UpDataItem.updataorder(col+1, Integer.parseInt(""+jtable.getValueAt(selectRow, 0)), Integer.parseInt(""+jtable.getValueAt(selectRow, col)));
//						
//
//					}
//				});
//			}}
//		});
		jtable.addMouseListener(new MouseAdapter() {//保存监听
			public void mouseClicked(MouseEvent e) {
				int selectRow = jtable.getSelectedRow();//获取鼠标选择行的索引值
				int col = jtable.getSelectedColumn();
				count = 1;//记录按钮点击次数
				if(selectRow==-1) {
					JOptionPane.showMessageDialog(null, "请选择需要修改的单元格");
				}
				else {
				button_1.addActionListener(new ActionListener() {
					public void actionPerformed(ActionEvent e) {
						if(col==5) {
							UpDataItem.updatareserve(col+1, Integer.parseInt(""+jtable.getValueAt(selectRow, 0)), ""+jtable.getValueAt(selectRow, col));
						}	
						if (col==6||col==10) {
							UpDataItem.updatareserve1(col+1, Integer.parseInt(""+jtable.getValueAt(selectRow, 0)), Integer.parseInt(""+jtable.getValueAt(selectRow, col)));
						}
					}
				});
			}}
		});
//		button_1.addActionListener(new ActionListener() {//保存监听
//			public void actionPerformed(ActionEvent e) {
//				UpDataItem.updatareserve(col, reserveid, newvalue, newnum)
//				for (int i = 0; i < jtable.getRowCount(); i++) {              
//					System.out.print(jtable.getValueAt(i,0)+" ");//"("预定人");  
//					System.out.print(jtable.getValueAt(i,1)+" "); //("预定时间"); 
//					System.out.print(jtable.getValueAt(i,2)+" "); //("手机号");  
//					System.out.print(jtable.getValueAt(i,3)+" "); //("邮箱地址"); 
//					System.out.print(jtable.getValueAt(i,4)+" ");  //("抵达日期"); 
//					System.out.print(jtable.getValueAt(i,5)+" "); //("预住天数"); 
//					System.out.print(jtable.getValueAt(i,6)+" "); //("排房");   
//					System.out.print(jtable.getValueAt(i,7)+" "); //("间数");   
//					System.out.print(jtable.getValueAt(i,8)+" ");    //  ("房间号");  
//					System.out.print(jtable.getValueAt(i,9)+" ");// ("状态"); 
//				}                                                    
//			}
//		});
		setVisible(true);
	}

}
