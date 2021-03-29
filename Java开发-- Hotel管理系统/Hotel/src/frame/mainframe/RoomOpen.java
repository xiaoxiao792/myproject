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
		setTitle("�Ƶ�-����");
		setIconImage(Toolkit.getDefaultToolkit().getImage("img/��΢.png"));
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
		
		JLabel lblNewLabel_1 = new JLabel("����");
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
		
		JLabel lblNewLabel = new JLabel("������Ϣ");
		lblNewLabel.setHorizontalAlignment(SwingConstants.CENTER);
		lblNewLabel.setOpaque(true);
		lblNewLabel.setBackground(SystemColor.controlHighlight);
		lblNewLabel.setBounds(0, 0, 320, 25);
		panel_2.add(lblNewLabel);
		
		JLabel label_1 = new JLabel("�������ͣ�");
		label_1.setHorizontalAlignment(SwingConstants.RIGHT);
		label_1.setBounds(0, 30, 160, 25);
		panel_2.add(label_1);
		
		
		
		JButton button_2 = new JButton("��ӵ�������");
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
		Vector dataTitle = new Vector();//����
		Vector data = new Vector();//��������
		
		dataTitle.add("����");
		dataTitle.add("�۸�(Ԫ)");
		
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
			for(int i = 0; i < jtable.getColumnCount(); i++) {
				jtable.getColumn(jtable.getColumnName(i)).setCellRenderer(tcr);
			}
			tcr.setHorizontalAlignment(JLabel.CENTER);//�������־�����ʾ
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
		
		jtable.addMouseListener(new MouseAdapter() {//����������
				public void mouseClicked(MouseEvent e) {
					//Ϊ����������¼�������(�����¼�)
						count1--;
					int selectRow = jtable.getSelectedRow();//��ȡ���ѡ���е�����ֵ
					count = 1;//��¼��ť�������
					if(selectRow==-1) {
						JOptionPane.showMessageDialog(null, "�Ҳ�������ֵ");
					}
					else {
						Object selectValues1 = jtable.getValueAt(selectRow, 0);//��ȡѡ��ĵ�Ԫ�������
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

		JLabel label = new JLabel("��������");
		label.setHorizontalAlignment(SwingConstants.CENTER);
		label.setOpaque(true);
		label.setBackground(SystemColor.controlHighlight);
		label.setBounds(0, 0, 320, 25);
		panel_3.add(label);
		
		JButton button_3 = new JButton("�ӿ������Ƴ�");
		button_3.setFocusPainted(false);
		
		jTable1.addMouseListener(new MouseAdapter() {//�ӿ������Ƴ�����
			public void mouseClicked(MouseEvent e) {
				int selectRow = jTable1.getSelectedRow();//��ȡ���ѡ���е�����ֵ
				count = 1;//��¼��ť�������
				if(selectRow==-1) {
					JOptionPane.showMessageDialog(null, "�Ҳ�������ֵ");
				}
				else {
				button_3.addActionListener(new ActionListener() {
					public void actionPerformed(ActionEvent e) {
						if(count == 1) {
						Object selectValues1 = jTable1.getValueAt(selectRow, 0);//��ȡѡ��ĵ�Ԫ�������
						Object selectValues2 = jTable1.getValueAt(selectRow, 1);
						data1 = selectValues1;
						data2 = selectValues2;
						Object obj[] = {data1,data2};
						
						tableModel.addRow(obj);  //���һ��
						model.removeRow(selectRow);
						count--;
						}
					}
				});
			}}
		});
		
		button_3.setBounds(0, 215, 320, 25);
		panel_3.add(button_3);
		
		String str[] = { "��׼���˷�", "��׼˫�˷�", "�������˷�", "����˫�˷�", "�����׷�","��ͳ�׷�"};
		JTextField text = new JTextField(10);
		JComboBox cbx = new JComboBox(str);
		
		
		cbx.addItemListener(new ItemListener() {
			  
			@Override
			public void itemStateChanged(ItemEvent e) {
			    if(e.getStateChange() == ItemEvent.SELECTED){
					if (cbx.getSelectedIndex() == 0) {//�x����ǘ˜ʆ��˷�			
						new Get_Data(model,tableModel,"150.0");//��ȡ����ͼ۸���Ϣ��ȥ��	
						}
					else if(cbx.getSelectedIndex()==1) {//�x����ǘ˜��p�˷�
						new Get_Data(model,tableModel,"180.0");//��ȡ����ͼ۸���Ϣ��ȥ��	
						}			
					else if(cbx.getSelectedIndex()==2) {//�x����Ǻ��A���˷�
						new Get_Data(model,tableModel,"250.0");
					}					
					else if(cbx.getSelectedIndex()==3) {//�x����Ǻ��A�p�˷�
						new Get_Data(model,tableModel,"280.0");
					}
					else if(cbx.getSelectedIndex()==4) {//�x������̄��׷�
						new Get_Data(model,tableModel,"380.0");
					}		
					else if(cbx.getSelectedIndex()==5){//�x����ǿ��y�׷�
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
		
		JLabel label_2 = new JLabel("�ͻ����֣�");
		label_2.setBounds(10, 10, 80, 25);
		panel_4.add(label_2);
		
		textField = new JTextField();
		textField.setBounds(85, 10, 100, 25);
		panel_4.add(textField);
		textField.setColumns(10);
		
		JLabel label_3 = new JLabel("�ͻ��Ա�");
		label_3.setBounds(230, 10, 80, 25);
		panel_4.add(label_3);
		
		String gender[] = {"��","Ů"};
		JComboBox com = new JComboBox(gender);
		com.setBounds(310, 10, 50, 25);
		panel_4.add(com);
		
		JLabel label_4 = new JLabel("�ͻ����䣺");
		label_4.setBounds(450, 10, 80, 25);
		panel_4.add(label_4);
		
		textField_1 = new JTextField();
		textField_1.addFocusListener(new FocusAdapter() {
			@Override
			public void focusLost(FocusEvent e) {
				ImageIcon icon = new ImageIcon("img/error.png");
				if(!limited.AgeLimited.isAge(textField_1.getText())) {
					JOptionPane.showMessageDialog(null,"�����ʽ�����������������룡", "������ʾ", JOptionPane.ERROR_MESSAGE, icon);
					textField_1.setText("");
				}
			}
		});
		textField_1.setBounds(525, 10, 100, 25);
		panel_4.add(textField_1);
		textField_1.setColumns(10);
		
		JLabel label_5 = new JLabel("֤����ţ�");
		label_5.setBounds(10, 45, 80, 25);
		panel_4.add(label_5);
		
		textField_2 = new JTextField();
		textField_2.addFocusListener(new FocusAdapter() {
			@Override
			public void focusLost(FocusEvent e) {
				ImageIcon icon = new ImageIcon("img/error.png");
				if(!limited.TestRegex02.isId(textField_2.getText())) {//���֤15λ��18λ�޶�����
					JOptionPane.showMessageDialog(null,"���֤�����ʽ�����������������룡", "������ʾ", JOptionPane.ERROR_MESSAGE, icon);
					textField_2.setText("");
				}else {
					List<Client> query = Query.clientquery(list1, textField_2.getText());
					if(!query.isEmpty())
						for(Client a :query) {
							textField.setText(a.getClientname());//ƥ������
							textField_1.setText(""+a.getClientage());//ƥ������
							textField_3.setText(a.getClientphone());//ƥ���ֻ�����
							textField_4.setText(a.getClientemail());//ƥ������
							textField_6.setText(a.getClientaddress());//ƥ���û�סַ
							com.setSelectedIndex(a.getClientsex());//ƥ���Ա�1��ʾŮ��0��ʾ�У�
							query.clear();
							break;
						}
						
//					textField.setText("");//ƥ������
//					textField_1.setText("");//ƥ������
//					textField_3.setText("");//ƥ���ֻ�����
//					textField_4.setText("");//ƥ������
//					textField_6.setText("");//ƥ���û�סַ
//					com.setSelectedIndex(1);//ƥ���Ա�1��ʾŮ��0��ʾ�У�
				}
			}
		});
		textField_2.setBounds(85, 45, 100, 25);
		panel_4.add(textField_2);
		textField_2.setColumns(10);
		
		JLabel label_6 = new JLabel("�ֻ����룺");
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
					JOptionPane.showMessageDialog(null,"�ֻ������ʽ�����������������룡", "������ʾ", JOptionPane.ERROR_MESSAGE, icon);
					textField_3.setText("");
				}
			}
		});
		panel_4.add(textField_3);
		
		JLabel label_7 = new JLabel("�����ַ��");
		label_7.setBounds(450, 45, 80, 25);
		panel_4.add(label_7);
		
		
		textField_4 = new JTextField();
		textField_4.addFocusListener(new FocusAdapter() {
			@Override
			public void focusLost(FocusEvent e) {
				ImageIcon icon = new ImageIcon("img/�����ʼ�.png");
				if(!limited.TestRegex01.isRightSytax(textField_4.getText())) {//�ж����������ʽ
					JOptionPane.showMessageDialog(null,"�����ʽ�����������������룡", "������ʾ", JOptionPane.ERROR_MESSAGE, icon);
					textField_4.setText("");
				}
			}
		});
		textField_4.setColumns(10);
		textField_4.setBounds(525, 45, 100, 25);
		panel_4.add(textField_4);
		
		JLabel label_8 = new JLabel("ס��������");
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
					JOptionPane.showMessageDialog(null,"ס��������ʽ�����������������룡", "������ʾ", JOptionPane.ERROR_MESSAGE, icon);
					textField_5.setText("");
				}
			}
		});
		panel_4.add(textField_5);
		
		JLabel label_9 = new JLabel("�ͻ���ַ��");
		label_9.setBounds(10, 115, 80, 25);
		panel_4.add(label_9);
		
		textField_6 = new JTextField();
		textField_6.setColumns(10);
		textField_6.setBounds(85, 115, 540, 25);
		panel_4.add(textField_6);
		
		JLabel label_10 = new JLabel("��ע��Ϣ��");
		label_10.setBounds(10, 150, 80, 25);
		panel_4.add(label_10);
		
		textField_7 = new JTextField();
		textField_7.setColumns(10);
		textField_7.setBounds(85, 150, 540, 25);
		panel_4.add(textField_7);
		
		JSeparator separator = new JSeparator();
		separator.setBounds(10, 185, 615, 2);
		panel_4.add(separator);
		
		JButton button = new JButton("ȷ��");
		button.setFocusPainted(false);
		button.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				int roomnum = jTable1.getColumnCount()-1;
				int pa;
				int[] roomname = new int[1];
				String clientclassname = "��ͨ�û�";
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
//					System.out.print(a+" ");//�����¼��
//					System.out.print(textField.getText()+" ");//�ͻ�����¼��
//					System.out.print(com.getSelectedIndex()+" ");//�ͻ��Ա�¼��
//					System.out.print(textField_1.getText()+" ");//�ͻ�����¼��
//					System.out.print(textField_2.getText()+" ");//֤����¼��
//					System.out.print(textField_3.getText()+" ");//�ֻ���¼��
//					System.out.print(textField_4.getText()+" ");//�����¼��
//					System.out.print(textField_5.getText()+" ");//ס������¼��
//					System.out.print(Integer.parseInt(textField_8.getText())+" ");//Ԥס����¼��
//					System.out.print(textField_6.getText()+" ");//�ͻ���ַ¼��
//					System.out.print(textField_7.getText()+" ");//��ע��Ϣ¼��
//				}


			}
		});
		button.setBounds(170, 200, 113, 27);
		panel_4.add(button);
		
		JButton button_1 = new JButton("ȡ��");
		button_1.setFocusPainted(false);
		button_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
			}
		});
		button_1.setBounds(370, 200, 113, 27);
		panel_4.add(button_1);
		
		JLabel label_11 = new JLabel("Ԥס������");
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
					JOptionPane.showMessageDialog(null,"������ʽ�����������������룡", "������ʾ", JOptionPane.ERROR_MESSAGE, icon);
					textField_4.setText("");
				}
			}
		});
		panel_4.add(textField_8);
		setVisible(true);
	}
}
