/**
 *##############################################################################
 *
 *	[ 模块名      ]  : 数据库连接
 *	[ 文件名      ]  : SqlFunc.java
 *	[ 相关文件    ]  : 
 *	[ 文件实现功能]  : 连接及操作数据库
 *	[ 作者        ]  : 邵文炳 
 *	[ 版本        ]  : 1.0
 *	----------------------------------------------------------------------------
 *	[ 备注        ]  : 
 *	----------------------------------------------------------------------------
 *	[ 修改记录    ]  : 
 *
 *	[ 日  期 ]     [版本]         [修改人]         [修改内容] 
 *	2019/03/19     1.0                  邵文炳                      创建
 *	
 *  ----------------------------------------------------------------------------
 *	[ 函数说明    ]  :
 *	
 *	[## private SqlFunc() {} ] :  
 *		功能: 防止实例化sunsql对象
 *
 *  [## public static int executeUpdate(String sql) {} ] :
 *		功能: 执行对数据库更改的sql命令，并返回更改所影响的行数
 *
 *  [## public static ResultSet executeQuery(String sql) {} ] :
 *		功能: 执行对数据库的select查询功能，并返回查询所得到的结果
 *
 *	[## public static int recCount(ResultSet rs)) {} ] :
 *		功能: 获得指定结果集的记录数量
 *
 *	[## public static long getPrimaryKey() {} ] : #A
 *		功能: 通过服务器当前的时间获得一个主键
 *
 *	[## public static void initJComboBox (JComboBox cb, String sqlCode) {} ] : #B
 *		功能: 按SQL语句从数据库选出Items加入JComboBox
 *
 *	[## public static void initJList (JList jt, String sqlCode) {} ] : #E
 *		功能: 按SQL语句从数据库选出数据加入JList
 *
 *	[## public static void initDTM (DefaultTableModel fdtm, String sqlCode) {} ] : #C
 *		功能: 按SQL语句从数据库中获得数据(结果集)，添加到fdtm中(也可以说JTable中)
 *
 *	[## public static int runTransaction (String updateCode[]) {} ] : #D
 *		功能: 利用事务的模式以updateCode中的sql语句对数据库进行更新
 *
 *
 *  [ 遗留问题    ]  :
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
			
			//获得一个连接
			conn = DriverManager.getConnection (url, user, pwd);
			//设置自动提交为false
			conn.setAutoCommit (false);
			//建立高级载体
			ste = conn.createStatement (ResultSet.TYPE_SCROLL_SENSITIVE, ResultSet.CONCUR_UPDATABLE);
	    }
	    catch (Exception ex) {
	    	System.out.println("数据库连接失败...");
//	    	JOptionPane.showMessageDialog (null, "数据库连接失败...", "错误", JOptionPane.ERROR_MESSAGE);
	    	System.exit(0);
	    	//ex.printStackTrace();
	    }
	}
	
	/**=======================================================================**
	 *		[## private SqlFunc() {} ]:		构造函数
	 *			参数   ：无
	 *			返回值 ：无
	 *			修饰符 ：private
	 *			功能   ：防止实例化SqlFunc对象
	 **=======================================================================**
	 */
	private SqlFunc(){
	}
	
	/**=======================================================================**
	 *		[## public ResultSet query(String sql) {} ] :	
	 *			参数   ：String 对象, 表示需要执行的sql语句
	 *			返回值 ：ResultSet 查询结果
	 *			功能   ：执行对数据库查询的sql命令
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
	 *			参数   ：String 对象, 表示需要执行的sql语句
	 *			返回值 ：无
	 *			功能   ：执行对数据库更改的sql命令
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
