/**
 *##############################################################################
 *
 *	[ ģ����      ]  : ���ݿ�����
 *	[ �ļ���      ]  : SqlFunc.java
 *	[ ����ļ�    ]  : 
 *	[ �ļ�ʵ�ֹ���]  : ���Ӽ��������ݿ�
 *	[ ����        ]  : ���ı� 
 *	[ �汾        ]  : 1.0
 *	----------------------------------------------------------------------------
 *	[ ��ע        ]  : 
 *	----------------------------------------------------------------------------
 *	[ �޸ļ�¼    ]  : 
 *
 *	[ ��  �� ]     [�汾]         [�޸���]         [�޸�����] 
 *	2019/03/19     1.0                  ���ı�                      ����
 *	
 *  ----------------------------------------------------------------------------
 *	[ ����˵��    ]  :
 *	
 *	[## private SqlFunc() {} ] :  
 *		����: ��ֹʵ����sunsql����
 *
 *  [## public static int executeUpdate(String sql) {} ] :
 *		����: ִ�ж����ݿ���ĵ�sql��������ظ�����Ӱ�������
 *
 *  [## public static ResultSet executeQuery(String sql) {} ] :
 *		����: ִ�ж����ݿ��select��ѯ���ܣ������ز�ѯ���õ��Ľ��
 *
 *	[## public static int recCount(ResultSet rs)) {} ] :
 *		����: ���ָ��������ļ�¼����
 *
 *	[## public static long getPrimaryKey() {} ] : #A
 *		����: ͨ����������ǰ��ʱ����һ������
 *
 *	[## public static void initJComboBox (JComboBox cb, String sqlCode) {} ] : #B
 *		����: ��SQL�������ݿ�ѡ��Items����JComboBox
 *
 *	[## public static void initJList (JList jt, String sqlCode) {} ] : #E
 *		����: ��SQL�������ݿ�ѡ�����ݼ���JList
 *
 *	[## public static void initDTM (DefaultTableModel fdtm, String sqlCode) {} ] : #C
 *		����: ��SQL�������ݿ��л������(�����)����ӵ�fdtm��(Ҳ����˵JTable��)
 *
 *	[## public static int runTransaction (String updateCode[]) {} ] : #D
 *		����: ���������ģʽ��updateCode�е�sql�������ݿ���и���
 *
 *
 *  [ ��������    ]  :
 *	
 *
 *##############################################################################
 */

package sql;

import java.sql.*;
import system.IniFunc;

public class SqlFunc {

	private static Statement ste = null;
	private static Connection conn = null;
	
	static {
		try {	
			String user = IniFunc.getIniKey ("UserID");
			String pwd  = IniFunc.getIniKey ("Password");
			String ip   = IniFunc.getIniKey ("IP");
			String acc  = IniFunc.getIniKey ("Access");
			String dbf  = IniFunc.getIniKey ("DBFname");
			String url  = "jdbc:mysql://" + ip + ":" + acc + "/" + dbf +"?useUnicode=true&characterEncoding=utf-8&useSSL=false";
			
			//���һ������
			conn = DriverManager.getConnection (url, user, pwd);
			//�����Զ��ύΪfalse
			conn.setAutoCommit (false);
			//�����߼�����
			ste = conn.createStatement (ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
	    }
	    catch (Exception ex) {
	    	System.out.println("���ݿ�����ʧ��...");
//	    	JOptionPane.showMessageDialog (null, "���ݿ�����ʧ��...", "����", JOptionPane.ERROR_MESSAGE);
	    	System.exit(0);
	    	//ex.printStackTrace();
	    }
	}
	
	/**=======================================================================**
	 *		[## private SqlFunc() {} ]:		���캯��
	 *			����   ����
	 *			����ֵ ����
	 *			���η� ��private
	 *			����   ����ֹʵ����SqlFunc����
	 **=======================================================================**
	 */
	private SqlFunc(){
	}
	
	/**=======================================================================**
	 *		[## public ResultSet query(String sql) {} ] :	
	 *			����   ��String ����, ��ʾ��Ҫִ�е�sql���
	 *			����ֵ ��ResultSet ��ѯ���
	 *			����   ��ִ�ж����ݿ��ѯ��sql����
	 **=======================================================================**
	 */
    public static ResultSet query(String sql) {
        ResultSet result = null;

        try
        {
            result = ste.executeQuery(sql);
        } catch (SQLException e)
        {
            e.printStackTrace();
        }

        return result;
    }
    
	/**=======================================================================**
	 *		[## public void executeSql(String sql) {} ] :	
	 *			����   ��String ����, ��ʾ��Ҫִ�е�sql���
	 *			����ֵ ����
	 *			����   ��ִ�ж����ݿ���ĵ�sql����
	 **=======================================================================**
	 */
    public static void updata(String sql) {
        try
        {
            ste.executeUpdate(sql);
            conn.commit();
        } catch (SQLException e)
        {
            e.printStackTrace();
        }
    }
    
}
