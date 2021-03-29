package panel.roompanel;

import java.awt.Color;

import javax.swing.ImageIcon;
import javax.swing.JLabel;

public class RoomPanel_clean extends RoomPanel{

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public RoomPanel_clean() {
	}
	
	public RoomPanel_clean(String str) {
		super(str);
		setLayout(null);
		setBackground(Color.RED);
		
		JLabel label = new JLabel();
		label.setIcon(new ImageIcon("img/É¨°Ñ.png"));
		label.setBounds(50, 23, 72, 79);
		add(label);

	}
}
