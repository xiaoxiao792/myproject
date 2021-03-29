package servlet;

import java.io.File;
import java.io.IOException;
import java.util.Iterator;
import java.util.List;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.apache.commons.fileupload.FileItem;
import org.apache.commons.fileupload.FileItemFactory;
import org.apache.commons.fileupload.FileUploadException;
import org.apache.commons.fileupload.disk.DiskFileItemFactory;
import org.apache.commons.fileupload.servlet.ServletFileUpload;
import updata.updata_sql;


/**
 * Servlet implementation class UpdateGoods
 */
@WebServlet("/UpdateGoods")
public class UpdateGoods extends HttpServlet {



	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		request.setCharacterEncoding("utf-8");
		response.setCharacterEncoding("utf-8");
		response.setContentType("text/html;charset=utf-8");
		String g_id =null;
		String gname =null;
		float price=0;
		int type=0;
		String filename = null;
		boolean isMultipart = ServletFileUpload.isMultipartContent(request);
		if(isMultipart) {
			FileItemFactory factory = new DiskFileItemFactory();
			ServletFileUpload upload = new ServletFileUpload(factory);
			try {
				List<FileItem> items = upload.parseRequest(request);//保存了表单里的所有东西
				Iterator<FileItem> iter= items.iterator();
				while(iter.hasNext()) {
					FileItem item=iter.next();
					String itemName=item.getFieldName();
					
					if(item.isFormField()) {//判断是普通属性还是文件属性      //根据name属性，判断item是sno,sname,sicture
						 if(itemName.equals("g_id")) { 
							 g_id=item.getString("utf-8"); 
						 }else if(itemName.equals("gname")) {
							 gname=item.getString("utf-8");
						 }else if(itemName.equals("price")) {
							 price=Integer.parseInt(item.getString("utf-8"));
						 }else if(itemName.equals("type")) {
							 String types=item.getString("utf-8");
							 if (types.equals("水果酸奶"))
								 type = 1;
							 else if(types.equals("休闲零食"))
								 type = 2;
						 }
					}else{//文件上传
						filename=item.getName();//获取文件名
						String path =null;
						if(filename=="") {
							path = getServletContext().getRealPath("/img/dd");
							System.out.println("aaa");
						}
						if(filename!="") {
							 path = getServletContext().getRealPath("/img");
						}
						//String path = getServletContext().getRealPath("/img");
						//String path = "C:\\Users\\lenovo\\eclipse-workspace\\期末作业\\WebContent\\img";
						System.out.println(filename);
						if(filename!=null) {
							System.out.println("iiii");
						}
						String p = request.getContextPath();
						System.out.println(p);
						System.out.println(path);
						File file = new File(path,filename);
						item.write(file); 
					}
				}
			}
			 catch (FileUploadException e) {
				// TODO 自动生成的 catch 块
				e.printStackTrace();
			} catch (Exception e) {
				// TODO 自动生成的 catch 块
				e.printStackTrace();
			}
		}
		boolean result=false;
		
		updata_sql.updatagoods(g_id, gname, filename, type, price);
		
		//boolean result = goodsservice.UpdateGoods(goods);
		//System.out.println(result);
		if(result) {
			System.out.println("到时候成功");
		}
		
		request.getRequestDispatcher("GoodsList").forward(request,response);
	}

	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
	
		doGet(request, response);
	}

}
