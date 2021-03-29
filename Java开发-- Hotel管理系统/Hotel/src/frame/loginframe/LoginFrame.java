package frame.loginframe;

import java.awt.Image;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import java.awt.Color;
import java.awt.Font;
import javax.swing.JTextField;
import javax.swing.*;
import javax.swing.SwingConstants;
import javax.swing.border.LineBorder;
import dataobject.PowerData;
import frame.mainframe.MainFrame;
import readywork.AddData;
import javax.swing.ImageIcon;
import java.awt.SystemColor;
import javax.swing.JCheckBox;
import javax.swing.JButton;
import java.awt.event.ActionListener;
import java.awt.event.FocusAdapter;
import java.awt.event.FocusEvent;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.ActionEvent;
import javax.swing.JSeparator;
import java.awt.Toolkit;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.ArrayList;
import java.util.List;

public class LoginFrame extends JFrame {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public static List<PowerData> list = new ArrayList<>();
	
	private JPanel contentPane;
	private JTextField textField;
	private JPasswordField textField_1;
	private boolean flag = false;//�ж��Ƿ����������
	public static String powername;
	
	public LoginFrame() {
		setResizable(false); //���ô��ڲ�������
		setTitle("�Ƶ�");
		setIconImage(Toolkit.getDefaultToolkit().getImage("img/��΢.png"));
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		setBounds(500, 300, 386, 428);
		contentPane = new JPanel();
		contentPane.setBackground(Color.WHITE);
		contentPane.setOpaque(false);
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		JPanel panel = new JPanel();
		panel.setBackground(Color.WHITE);
		panel.setBounds(0, 0, 370, 380);
		contentPane.add(panel);
		
		JButton button = new JButton("��¼");
		button.setBorder(new LineBorder(Color.WHITE, 2, true));
		button.setFont(new Font("Microsoft JhengHei UI", Font.BOLD, 22));
		button.setForeground(Color.WHITE);
		panel.setLayout(null);
		button.setBackground(new Color(0,132,255));
		panel.add(button);
		button.setBounds(30, 280, 309, 43);
		button.addActionListener(new ActionListener() {
			@SuppressWarnings("deprecation")
			public void actionPerformed(ActionEvent e) {
				list = AddData.getList0();
				for(PowerData a : list) {
					if(textField.getText().equals(a.getPowerid())&&textField_1.getText().equals(a.getPwd())) {
	                	flag = true;
	                	dispose();
	                	powername = a.getPowername();
	                	a.setIslogin(1);
	                	new MainFrame(powername);
	                }
				}
				if(flag == false)
            		JOptionPane.showMessageDialog(null,"�˺Ż������������");
			}
		});
		
		
		JLabel lblNewLabel = new JLabel("���Ƶ����ϵͳ");
		lblNewLabel.setBounds(120, 32, 182, 42);
		lblNewLabel.setHorizontalAlignment(SwingConstants.TRAILING);
		lblNewLabel.setFont(new Font("Microsoft YaHei UI", Font.PLAIN, 26));
		lblNewLabel.setForeground(new Color(0, 132, 255));
		panel.add(lblNewLabel);
		
		textField = new JTextField(" �������˺�");
		textField.setCaretColor(textField.getBackground());
		textField.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				textField.setText("");
				textField.setForeground(Color.BLACK);
				textField.setCaretColor(Color.BLACK);
			}
		});
		textField.setOpaque(false);
		textField.setBounds(30, 95, 309, 43);
		textField.setBorder(new LineBorder(new Color(171, 173, 179), 2, true));
		textField.setForeground(new Color(180,180,180));
		textField.setFont(new Font("����", Font.PLAIN, 16));
		panel.add(textField);
		textField.setColumns(10);
		
		
		ImageIcon image = new ImageIcon("img/��.png");
		image.setImage(image.getImage().getScaledInstance(72,52,Image.SCALE_DEFAULT));
		JLabel label = new JLabel(image);
		label.setBounds(54, 18, 66, 59);
		panel.add(label);
		
		textField_1 = new JPasswordField(" ����������");
		textField_1.setEchoChar((char)0);
		textField_1.addFocusListener(new FocusAdapter() {
			@Override
			public void focusGained(FocusEvent e) {
				textField_1.setText("");
				textField_1.setEchoChar('*');
				textField_1.setForeground(Color.BLACK);
			}
		});
		textField_1.setOpaque(false);
		textField_1.setBounds(30, 165, 309, 43);
		textField_1.setForeground(SystemColor.activeCaptionBorder);
		textField_1.setFont(new Font("����", Font.PLAIN, 16));
		textField_1.setColumns(10);
		textField_1.setBorder(new LineBorder(new Color(171, 173, 179), 2, true));
		
		textField_1.addKeyListener(new KeyAdapter() {
			@SuppressWarnings("deprecation")
			@Override
			public void keyPressed(KeyEvent e) {
				if(e.getKeyChar() == KeyEvent.VK_ENTER) {
					list = AddData.getList0();
					for(PowerData a : list) {
						if(textField.getText().equals(a.getPowerid())&&textField_1.getText().equals(a.getPwd())) {
		                	flag = true;
		                	dispose();
		                	powername = a.getPowername();
		                	a.setIslogin(1);
		                	new MainFrame(powername);
		                }
					}
					if(flag == false)
	            		JOptionPane.showMessageDialog(null,"�˺Ż������������");
				}
			}
		});
		
		panel.add(textField_1);
		
		JCheckBox checkBox = new JCheckBox("��ס����");
		checkBox.setOpaque(false);
		checkBox.setBackground(Color.WHITE);
		checkBox.setBounds(30, 220, 95, 33);
		panel.add(checkBox);
		
		JSeparator separator = new JSeparator();
		separator.setBounds(30, 78, 309, 2);
		panel.add(separator);
		
		ImageIcon img = new ImageIcon("img/�û�.png");
		img.setImage(img.getImage().getScaledInstance(50,50,Image.SCALE_DEFAULT));
		JLabel label_1 = new JLabel(img);
		label_1.setBounds(277, 100, 72, 31);
		panel.add(label_1);
		
		ImageIcon img_pwd = new ImageIcon("img/��.png");
		img_pwd.setImage(img_pwd.getImage().getScaledInstance(50,50,Image.SCALE_DEFAULT));
		JLabel label_2 = new JLabel(img_pwd);
		label_2.setBounds(282, 175, 72, 33);
		panel.add(label_2);
		setVisible(true);
	}
	
}
