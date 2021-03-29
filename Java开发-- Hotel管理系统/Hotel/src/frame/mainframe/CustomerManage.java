package frame.mainframe;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JSeparator;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.border.LineBorder;
import java.awt.Color;
import java.awt.Component;
import javax.swing.table.DefaultTableCellRenderer;
import dataobject.Client;
import function.query.Query;
import function.updata.UpDataItem;
import readywork.AddData;
import java.awt.SystemColor;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JButton;
import javax.swing.SwingConstants;
import javax.swing.ImageIcon;
import javax.swing.JScrollPane;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.List;
import java.util.Vector;
import java.awt.Toolkit;

public class CustomerManage extends JFrame {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	public static List<Client> list = AddData.getList1();
	private JPanel contentPane;
	private JTextField textField;
	private JTable table;
	private int count=0;
	/**
	 * Create the frame.
	 */
	@SuppressWarnings({ "rawtypes", "unchecked" })
	public CustomerManage() {
		setTitle("�Ƶ�-�ͻ�����");
		setIconImage(Toolkit.getDefaultToolkit().getImage("img/��΢.png"));
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
		
		JLabel label = new JLabel("�ͻ�����");
		label.setHorizontalAlignment(SwingConstants.CENTER);
		label.setBounds(0, 0, 120, 30);
		panel.add(label);
		
		JPanel panel_1 = new JPanel();
		panel_1.setForeground(Color.WHITE);
		panel_1.setBorder(new LineBorder(new Color(0,158,241)));
		panel_1.setBackground(Color.WHITE);
		panel_1.setBounds(5, 32, 870, 515);
		contentPane.add(panel_1);
		panel_1.setLayout(null);
		
		JSeparator separator = new JSeparator();
		separator.setBounds(0, 45, 880, 2);
		panel_1.add(separator);
		
		textField = new JTextField();
		textField.setCaretColor(textField.getBackground());
		textField.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				textField.setText("");
				textField.setCaretColor(Color.BLACK);
			}
		});
		textField.setBorder(new LineBorder(Color.LIGHT_GRAY, 1, true));
		textField.setText("  ����ͻ�������ѯ");
		textField.setBounds(10, 8, 170, 30);
		panel_1.add(textField);
		textField.setColumns(10);
		
		JButton button_1 = new JButton("����");
		button_1.setFocusPainted(false);
		
		
		button_1.setBorder(new EmptyBorder(0, 0, 0, 0));
		button_1.setForeground(Color.WHITE);
		button_1.setBackground(new Color(0,158,241));
		button_1.setBounds(740, 12, 100, 26);
		panel_1.add(button_1);
		
		
		
		Vector rowdata,colname;
		colname = new Vector();
		colname.add("�ͻ�id");
		colname.add("�ͻ�");
		colname.add("���֤���");
		colname.add("�Ա�");
		colname.add("����");
		colname.add("�ֻ�����");
		colname.add("�����ַ");
		colname.add("�û�סַ");
		colname.add("��Ա�ȼ�");
		
		rowdata = new Vector();
		for(Client a : list) {
			Vector W = new Vector();
			W.add(a.getClientid());
			W.add(a.getClientname());
			W.add(a.getClientidnumber());
			if(a.getClientsex()==0) {
				W.add("��");
			}else {
				W.add("Ů");
			}
			
			W.add(a.getClientage());
			W.add(a.getClientphone());
			W.add(a.getClientemail());
			W.add(a.getClientaddress());
			W.add(a.getClientclassname());
			rowdata.add(W);
		}
		
		TableModel tableModel = new TableModel(rowdata,colname);
		
		JScrollPane scrollPane_1 = new JScrollPane();
		scrollPane_1.setBorder(new EmptyBorder(0, 0, 0, 0));
		scrollPane_1.setBounds(1, 50, 868, 450);
		panel_1.add(scrollPane_1);
		table = new JTable(tableModel);
		tableModel.CellEditable();
		scrollPane_1.setViewportView(table);
		table.setBorder(new EmptyBorder(0, 0, 0, 0));
		table.getTableHeader().setBackground(new Color(78,78,78));//��ͷ����ɫ
		table.getTableHeader().setForeground(Color.WHITE);//��ͷǰ��ɫ
		table.setShowHorizontalLines(false);//����ʾˮƽ�߿���
		table.setShowVerticalLines(false);//����ʾ��ֱ�߿���
		table.setRowHeight(25);
		try//���ñ���ɫΪ˫ɫ��ʾ
		{
			DefaultTableCellRenderer tcr = new DefaultTableCellRenderer(){
				private static final long serialVersionUID = 1L;
				@Override
				public Component getTableCellRendererComponent(JTable table,Object value, boolean isSelected, boolean hasFocus,int row, int column){
					if(row%2 == 0)
						setBackground(Color.WHITE);//���������е�ɫ
					else if(row%2 == 1)
						setBackground(new Color(220,230,241));//����ż���е�ɫ
					return super.getTableCellRendererComponent(table, value,isSelected, hasFocus, row, column);
				}
			};
			for(int i = 0; i < table.getColumnCount(); i++) {
				table.getColumn(table.getColumnName(i)).setCellRenderer(tcr);
			}
			tcr.setHorizontalAlignment(JLabel.CENTER);//�������־�����ʾ
		}
		catch (Exception e){
			e.printStackTrace();
		}
		
		JButton button_2 = new JButton("");
		button_2.setFocusPainted(false);
		button_2.addActionListener(new ActionListener() {//��������
			public void actionPerformed(ActionEvent e) {
				List<Client> query = Query.clientquery(list, textField.getText());
				for(int i=0;i<tableModel.getRowCount();i++) {//������е����Д������
					tableModel.removeRow(0);
					i=-1;
				}
				for(Client a : query) {
					Vector W = new Vector();
					W.add(a.getClientid());
					W.add(a.getClientname());
					W.add(a.getClientidnumber());
					if(a.getClientsex()==0) {
						W.add("��");
					}else {
						W.add("Ů");
					}
					
					W.add(a.getClientage());
					W.add(a.getClientphone());
					W.add(a.getClientemail());
					W.add(a.getClientaddress());
					W.add(a.getClientclassname());
					rowdata.add(W);
				}
				if(query.size()!=0)
					query.clear();
			
			}
		});
		button_2.setIcon(new ImageIcon("img/����.png"));
		button_2.setForeground(Color.WHITE);
		button_2.setBorder(new LineBorder(new Color(192, 192, 192), 1, true));
		button_2.setBackground(Color.WHITE);
		button_2.setBounds(178, 8, 30, 30);
		panel_1.add(button_2);
		
		JButton button_3 = new JButton("����");
		button_3.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
			}
		});
		button_3.setForeground(Color.WHITE);
		button_3.setFocusPainted(false);
		button_3.setBorder(new EmptyBorder(0, 0, 0, 0));
		button_3.setBackground(new Color(0, 158, 241));
		button_3.setBounds(600, 12, 100, 26);
		panel_1.add(button_3);
		
//		table.addMouseListener(new MouseAdapter() {//ɾ�����ܼ���
//			public void mouseClicked(MouseEvent e) {
//				int selectRow = table.getSelectedRow();//��ȡ���ѡ���е�����ֵ
//				count = 1;//��¼��ť�������
//				if(selectRow==-1) {
//					JOptionPane.showMessageDialog(null, "�Ҳ�������ֵ");
//				}
//				else {
//				button.addActionListener(new ActionListener() {
//					public void actionPerformed(ActionEvent e) {
//						if(count == 1) {
//						tableModel.removeRow(selectRow);
//						count--;
//						}
//					}
//				});
//			}}
//		});
		table.addMouseListener(new MouseAdapter() {//�ӿ������Ƴ�����
			public void mouseClicked(MouseEvent e) {
				int selectRow = table.getSelectedRow();//��ȡ���ѡ���е�����ֵ
				int col = table.getSelectedColumn();
				count = 1;
				if(selectRow==-1) {
					JOptionPane.showMessageDialog(null, "��ѡ����Ҫ�޸ĵĵ�Ԫ��");
				}
				else {
				button_1.addActionListener(new ActionListener() {
					public void actionPerformed(ActionEvent e) {
							UpDataItem.updataclient(col+1, Integer.parseInt(""+table.getValueAt(selectRow, 0)), ""+table.getValueAt(selectRow, col));
							count--;
							if(count==0) {
								JOptionPane.showMessageDialog(null, "�����޸ĳɹ���");
								tableModel.fireTableDataChanged();
							}
//						}
//							UpDataItem.updataorder(col, Integer.parseInt(""+table.getValueAt(selectRow, 0)), Integer.parseInt(""+jtable.getValueAt(selectRow, col-1)));
					}
				});
			}}
		});
		button_1.addActionListener(new ActionListener() {//�������
			
			@Override
			public void actionPerformed(ActionEvent e) {

				for (int i = 0; i < table.getRowCount(); i++) {
					System.out.print(table.getValueAt(i,0)+" ");//"�ͻ�"
					System.out.print(table.getValueAt(i,1)+" "); // "���֤���"
					System.out.print(table.getValueAt(i,2)+" "); // "�Ա�"
					System.out.print(table.getValueAt(i,3)+" "); // "����"
					System.out.print(table.getValueAt(i,4)+" ");  //"�ֻ�����"
					System.out.print(table.getValueAt(i,5)+" "); // "�����ַ"
					System.out.print(table.getValueAt(i,6)+" "); // "�û�סַ"
					System.out.print(table.getValueAt(i,7)+" "); // "��Ա�ȼ�"
					System.out.println();
				}
			}
		});
		setVisible(true);
	}
}
