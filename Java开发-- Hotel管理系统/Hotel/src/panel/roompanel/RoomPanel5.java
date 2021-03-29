package panel.roompanel;

import java.awt.Color;
import javax.swing.ImageIcon;
import javax.swing.JLabel;


public class RoomPanel5 extends RoomPanel {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	/**
	 * Create the panel.
	 */
	public RoomPanel5() {

	}

	public RoomPanel5(String str) {
		super(str);
		setLayout(null);
		setBackground(new Color(18,150,219));
		
		JLabel label = new JLabel();
		label.setIcon(new ImageIcon("img/µ•»À¥≤.png"));
		label.setBounds(50, 23, 72, 79);
		add(label);
	}
}
