package frame.roomopen;

import java.util.List;
import java.util.Vector;
import javax.swing.table.DefaultTableModel;
import dataobject.Room;
import readywork.AddData;

public class Get_Data {
	public static List<Room> list = AddData.getList2();
	
	@SuppressWarnings({ "rawtypes", "unchecked" })
	public Get_Data(DefaultTableModel model,DefaultTableModel tableModel,String str){
		boolean flag=true;//�z�y�Ƿ��ҵ���ͬ�
		for(int i=0;i<tableModel.getRowCount();i++) {//������е����Д������
			tableModel.removeRow(0);
			i=-1;
		}
		for(Room a : list) {
			if(a.getRoomstata()==1) {
			Vector V = new Vector();
			V.add(a.getRoomid());
			V.add(a.getRoomprice());
			Object data_row[] = {V.elementAt(0),V.elementAt(1)};
			if (model.getRowCount() != 0) {
				for (int i = 0; i < model.getRowCount(); i++) {
					
					if (V.elementAt(0).equals(model.getValueAt(i, 0))) {
						flag = true;//�ҵ���ͬ�
						break;
					} else {							
						flag = false;//δ�ҵ���ͬ�
					}
					
				}
				if(!flag) {//���딵���c�ұ�ͬ���t���в������Z��
					tableModel.addRow(data_row);
				}
			}
			else {//�ұ��գ����в������Z��
				tableModel.addRow(data_row);
			}
		}
		int row_n = tableModel.getRowCount();
		for(int i=0;i<row_n;i++) {//�h�������ϗl������
			if (tableModel.getValueAt(i, 1).toString().equals(str)) {
		}else {
			row_n-=1;
			tableModel.removeRow(i);
			i=-1;
		}
		}
		}
	}
}
