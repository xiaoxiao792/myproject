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
import dataobject.OrderData;
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
import java.awt.event.*;
import java.util.List;
import java.util.Vector;
import javax.swing.JScrollPane;
import java.awt.Toolkit;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

public class OrderManage extends JFrame{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	public static List<OrderData> list = AddData.getList3();
	private JPanel contentPane;
	private JTextField textField;
	public int count,cnt=0;
	JTable jtable;

	@SuppressWarnings({ "rawtypes", "unchecked", "unused" })
	public OrderManage() {
		setTitle("酒店-订单管理");
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
		
		JLabel label = new JLabel("订单管理");
		label.setOpaque(true);
		label.setBackground(Color.ORANGE);
		label.setHorizontalAlignment(SwingConstants.CENTER);
		label.setBounds(0, 0, 120, 30);
		panel.add(label);
		
		JPanel panel_1 = new JPanel();
		panel_1.setForeground(Color.WHITE);
		panel_1.setBorder(new LineBorder(Color.ORANGE));
		panel_1.setBackground(Color.WHITE);
		panel_1.setBounds(5, 32, 870, 515);
		contentPane.add(panel_1);
		panel_1.setLayout(null);
		
		JSeparator separator = new JSeparator();
		separator.setBounds(0, 45, 880, 2);
		panel_1.add(separator);
		
		
		
		textField = new JTextField();
		textField.setToolTipText("");
		textField.setOpaque(false);
		addWindowListener( new WindowAdapter() {
			public void windowOpened( WindowEvent e ){
				textField.requestFocus();
			}
			});
		textField.setCaretColor(textField.getBackground());
		textField.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				textField.setText("");
				textField.setCaretColor(Color.BLACK);
			}
		});
		textField.setForeground(Color.GRAY);
		textField.setBorder(new LineBorder(new Color(192, 192, 192), 1, true));
		textField.setText("  输入订单编号查询");
		textField.setBounds(10, 8, 170, 30);
		panel_1.add(textField);
		textField.setColumns(10);
		
		JButton button_1 = new JButton("修改");	
		button_1.setFocusPainted(false);
		button_1.setBorder(new EmptyBorder(0, 0, 0, 0));
		button_1.setForeground(Color.WHITE);
		button_1.setBackground(Color.ORANGE);
		button_1.setBounds(740, 12, 100, 26);
		panel_1.add(button_1);
		
		JButton button_2 = new JButton("");
		button_2.setFocusPainted(false);
		button_2.setOpaque(false);
		button_2.setIcon(new ImageIcon("img/搜索.png"));
		button_2.setForeground(Color.WHITE);
		button_2.setBorder(new LineBorder(new Color(192, 192, 192), 1, true));
		button_2.setBackground(Color.WHITE);
		button_2.setBounds(179, 8, 30, 30);
		panel_1.add(button_2);
		
		JScrollPane scrollPane = new JScrollPane();
		scrollPane.setBorder(new EmptyBorder(0, 0, 0, 0));
		scrollPane.setBounds(1, 50, 868, 460);
		panel_1.add(scrollPane);
		
		TableModel tableModel;
		
		Vector dataTitle = new Vector();//列名
		Vector data = new Vector();//数据内容
		Vector hang = new Vector();
		dataTitle.add("订单号");
		dataTitle.add("客户");
		dataTitle.add("开房时间");
		dataTitle.add("手机号码");
		dataTitle.add("邮箱地址");
		dataTitle.add("预住天数");
		dataTitle.add("间数");
		dataTitle.add("房间号");
		dataTitle.add("状态");
		dataTitle.add("备注");
		
		for(OrderData a : list) {
			String qa = "";
			for(int i = 0; i<a.getRoomnum();i++) {
				qa += a.getRoomname()[i]+" ";
			}
			Vector W = new Vector();
			W.add(a.getOrderid());
			W.add(a.getClientname());
			W.add(a.getOrderbegintime());
			W.add(a.getClientphone());
			W.add(a.getClientemail());
			W.add(a.getOrderdays());
			W.add(a.getRoomnum());
			W.add(qa);
			W.add(a.getOrderstata());
			W.add(a.getRemark());
			data.add(W);
		}
		
		tableModel = new TableModel(data,dataTitle);
		jtable = new JTable(tableModel);
		
		
		
		jtable.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		
		jtable.setBorder(new EmptyBorder(0, 0, 0, 0));
		jtable.getTableHeader().setBackground(new Color(78,78,78));
		jtable.getTableHeader().setForeground(Color.WHITE);
		jtable.setRowHeight(25);
		jtable.setRowMargin(0);
		jtable.setShowVerticalLines(false);
		jtable.setShowHorizontalLines(false);
		
		jtable.setOpaque(false);
		scrollPane.setViewportView(jtable);
		
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
		
		JButton button = new JButton("编辑");
		button.setFocusPainted(false);
		button.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				tableModel.CellEditable();
			}
		});
		button.setBorder(new EmptyBorder(0, 0, 0, 0));
		button.setBounds(600, 12, 100, 26);
		panel_1.add(button);
		button.setForeground(Color.WHITE);
		button.setBackground(Color.ORANGE);
		
		JButton button_3 = new JButton("增加");
		button_3.setForeground(Color.WHITE);
		button_3.setFocusPainted(false);
		button_3.setBorder(new EmptyBorder(0, 0, 0, 0));
		button_3.setBackground(Color.ORANGE);
		button_3.setBounds(460, 12, 100, 26);
		panel_1.add(button_3);
		
		button_2.addActionListener(new ActionListener() {//搜索监听
			
			@Override
			public void actionPerformed(ActionEvent e) {
				// TODO Auto-generated method stub
				List<OrderData> query = Query.orderquery(list, textField.getText());
				for(int i=0;i<tableModel.getRowCount();i++) {//將表格中的所有數據清除
					tableModel.removeRow(0);
					i=-1;
				}
				for(OrderData a : query) {
					String qa = "";
					for(int i = 0; i<a.getRoomnum();i++) {
						qa += a.getRoomname()[i]+" ";
					}
					Vector W = new Vector();
					W.add(a.getOrderid());
					W.add(a.getClientname());
					W.add(a.getOrderbegintime());
					W.add(a.getClientphone());
					W.add(a.getClientemail());
					W.add(a.getOrderdays());
					W.add(a.getRoomnum());
					W.add(qa);
					W.add(a.getOrderstata());
					W.add(a.getRemark());
					data.add(W);
				}
				if(query.size()!=0)
					query.clear();
			}
		});
		
		jtable.addMouseListener(new MouseAdapter() {//修改监听
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
							UpDataItem.updataorder(col+1, Integer.parseInt(""+jtable.getValueAt(selectRow, 0)), Integer.parseInt(""+jtable.getValueAt(selectRow, col)));
							count++;
						}
						if(count==2) {
							JOptionPane.showMessageDialog(null, "数据修改成功！");
							tableModel.fireTableDataChanged();
						}
					}
				});
			}}
		});
        
		
       
        
        
		setVisible(true);
	
	}
}
