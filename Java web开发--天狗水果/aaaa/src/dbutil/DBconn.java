package dbutil;
 
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;
 
public class DBconn {
 //三属性，四方法
 
 //三大核心接口
 private Connection conn=null;
 private PreparedStatement pstmt=null;
 private ResultSet rs=null;
 
 String driver="com.mysql.jdbc.Driver";
 String url="jdbc:mysql://localhost:3306/fruitshop";
 String user="root";
 String password="111";
 //四个方法
 //method1：创建数据库的连接
 public void getConntion(){
  try{
   //加载连接驱动
   Class.forName(driver);
   //连接mysql数据库
   conn=DriverManager.getConnection(url,user,password);
  } catch(ClassNotFoundException e){
   e.printStackTrace();
  } catch(SQLException e){
   e.printStackTrace();
  }
 }
 
 //method2:关闭数据库连接
 public void closeConn(){
  if(rs!=null){
   try{
    rs.close();
   } catch(SQLException e){
    e.printStackTrace();
   }
  }
  if(pstmt!=null){
   try{
    pstmt.close();
    
   } catch(SQLException e){
    e.printStackTrace();
   }
  }
  if(conn!=null){
   try{
    conn.close();
   } catch(SQLException e){
    e.printStackTrace();
   }
  }
  
 }
 
 //method3:专门用于发送增删改语句的方法
 public int execOther(final String strSQL, final Object[] params){
  //连接
  getConntion();
  System.out.println("SQL:>"+strSQL);
  try{
   //创建statement接口对象
   pstmt=conn.prepareStatement(strSQL);
   //动态为pstmt对象赋值
   for(int i=0;i<params.length;i++){
    pstmt.setObject(i+1, params[i]);
   }
   //使用Statement对象发送SQL语句
   int affectedRows=pstmt.executeUpdate();
   return affectedRows;
   
   
  } catch(SQLException e){
   e.printStackTrace();
   return -1;
  }
 }
 
 //method4:专门用于发送查询语句
 public ResultSet execQuery(final String strSQL,final Object[] params){
  getConntion();
  try{
	  
   pstmt=conn.prepareStatement(strSQL);
   for(int i=0;i<params.length;i++){
    pstmt.setObject(i+1, params[i]);
   }
   rs=pstmt.executeQuery();
   return rs;
  } catch(SQLException e){
   e.printStackTrace();
   return null;
  }
 }
 
 //method5:专门用于发送查询语句
 public ResultSet execQuery(final String strSQL,final List<String> params){
  getConntion();
  try{
	  
   pstmt=conn.prepareStatement(strSQL);
   for(int i=0;i<params.size();i++){
    pstmt.setString(i+1, params.get(i));
   }
   rs=pstmt.executeQuery();
   return rs;
  } catch(SQLException e){
   e.printStackTrace();
   return null;
  }
 }
}