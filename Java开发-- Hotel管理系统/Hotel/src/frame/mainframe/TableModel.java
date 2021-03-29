package frame.mainframe;

import java.util.Vector;

import javax.swing.table.DefaultTableModel;

public class TableModel extends DefaultTableModel{
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	public int row,column;
	public boolean fag=false;
	@Override
	public boolean isCellEditable(int row, int column)
    {
    	this.row = row;
    	this.column = column;
        return fag;
    }
    public boolean CellEditable() {
    	fag = true;
    	return isCellEditable(row,column);
    }
    @SuppressWarnings("rawtypes")
	public TableModel(Vector data,Vector colname) {
    	super(data,colname);
    }
}
