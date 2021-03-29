package panel.roompanel;

import java.awt.Color;
import javax.swing.ImageIcon;
import javax.swing.JLabel;

public class RoomPanel2 extends RoomPanel{

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public RoomPanel2() {
	}
	
	public RoomPanel2(String str) {
		super(str);
		setLayout(null);
		setBackground(new Color(18,150,219));
		
		JLabel label = new JLabel();
		label.setIcon(new ImageIcon("img/2-Bed Room.png"));
		label.setBounds(50, 23, 72, 79);
		add(label);

	}
}
