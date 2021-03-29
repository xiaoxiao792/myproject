package panel.roompanel;

import java.awt.Color;
import java.awt.Rectangle;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class RoomPanel extends JPanel{
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	public RoomPanel() {
	}
	
	public RoomPanel(String str) {
		setBounds(new Rectangle(0, 0, 140, 100));
		setLayout(null);
		
		JLabel lblNewLabel = new JLabel(str);
		lblNewLabel.setForeground(Color.WHITE);
		lblNewLabel.setBounds(5, 10, 130, 20);
		add(lblNewLabel);	
	}
}
