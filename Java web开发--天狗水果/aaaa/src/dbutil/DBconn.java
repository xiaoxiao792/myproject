package dbutil;
 
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;
 
public class DBconn {
 //�����ԣ��ķ���
 
 //������Ľӿ�
 private Connection conn=null;
 private PreparedStatement pstmt=null;
 private ResultSet rs=null;
 
 String driver="com.mysql.jdbc.Driver";
 String url="jdbc:mysql://localhost:3306/fruitshop";
 String user="root";
 String password="111";
 //�ĸ�����
 //method1���������ݿ������
 public void getConntion(){
  try{
   //������������
   Class.forName(driver);
   //����mysql���ݿ�
   conn=DriverManager.getConnection(url,user,password);
  } catch(ClassNotFoundException e){
   e.printStackTrace();
  } catch(SQLException e){
   e.printStackTrace();
  }
 }
 
 //method2:�ر����ݿ�����
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
 
 //method3:ר�����ڷ�����ɾ�����ķ���
 public int execOther(final String strSQL, final Object[] params){
  //����
  getConntion();
  System.out.println("SQL:>"+strSQL);
  try{
   //����statement�ӿڶ���
   pstmt=conn.prepareStatement(strSQL);
   //��̬Ϊpstmt����ֵ
   for(int i=0;i<params.length;i++){
    pstmt.setObject(i+1, params[i]);
   }
   //ʹ��Statement������SQL���
   int affectedRows=pstmt.executeUpdate();
   return affectedRows;
   
   
  } catch(SQLException e){
   e.printStackTrace();
   return -1;
  }
 }
 
 //method4:ר�����ڷ��Ͳ�ѯ���
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
 
 //method5:ר�����ڷ��Ͳ�ѯ���
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