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
		boolean flag=true;//檢測是否找到相同項
		for(int i=0;i<tableModel.getRowCount();i++) {//將表格中的所有數據清除
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
						flag = true;//找到相同項
						break;
					} else {							
						flag = false;//未找到相同項
					}
					
				}
				if(!flag) {//插入數據與右表不同，則執行插入行語句
					tableModel.addRow(data_row);
				}
			}
			else {//右表為空，執行插入行語句
				tableModel.addRow(data_row);
			}
		}
		int row_n = tableModel.getRowCount();
		for(int i=0;i<row_n;i++) {//刪除不符合條件的行
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
