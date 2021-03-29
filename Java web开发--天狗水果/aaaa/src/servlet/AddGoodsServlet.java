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
 * Servlet implementation class AddGoodsServlet
 */
@WebServlet("/AddGoodsServlet")
public class AddGoodsServlet extends HttpServlet {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		request.setCharacterEncoding("utf-8");
		//goods_data goods = null;
		String gname =null; //goods_name
		float price = 0;//goods_price
		int type = 0;//goods_class
		String filename = "";//goods_img
		String success =null;
		boolean isMultipart = ServletFileUpload.isMultipartContent(request);
		if(isMultipart) {
			FileItemFactory factory = new DiskFileItemFactory();
			ServletFileUpload upload = new ServletFileUpload(factory);
			try {
				List<FileItem> items = upload.parseRequest(request);//�����˱�������ж���
				Iterator<FileItem> iter= items.iterator();
				while(iter.hasNext()) {
					FileItem item=iter.next();
					String itemName=item.getFieldName();
					
					if(item.isFormField()) {//�ж�����ͨ���Ի����ļ�����      //����name���ԣ��ж�item��sno,sname,sicture
						 if(itemName.equals("gname")) {
							 gname=item.getString("utf-8");
							 System.out.println(gname); //1
						 }else if(itemName.equals("price")) {
							 price=Integer.parseInt(item.getString("utf-8"));
						 }else if(itemName.equals("type")) {
							 String types=item.getString("utf-8");
							 if (types.equals("ˮ������"))
								 type = 1;
							 else if(types.equals("������ʳ"))
								 type = 2;
						 }
					}else{//�ļ��ϴ�
						filename=item.getName();//��ȡ�ļ���
						//String path = getServletContext().getRealPath("/img");
						//D:\360��ȫ���������\eclipse\eclipse-jee-luna\workspace\aaaa
						String path = "D:\\360��ȫ���������\\eclipse\\eclipse-jee-luna\\workspace\\.metadata\\.plugins\\org.eclipse.wst.server.core\\tmp0\\wtpwebapps\\aaaa\\tiangoushuiguo\\images";
						System.out.println(filename);  // �ļ���
						String p = request.getContextPath();
						System.out.println(p); // ��Ŀ��
						System.out.println(path); // ·����
						File file = new File(path,filename);
						item.write(file); 
					}
				}
			}
			 catch (FileUploadException e) {
				// TODO �Զ����ɵ� catch ��
				e.printStackTrace();
			} catch (Exception e) {
				// TODO �Զ����ɵ� catch ��
				e.printStackTrace();
			}
		}
		boolean result = updata_sql.addgoods(gname, price, type, filename);
		//goods = new Goods(g_id,gbrank,gname, price,number,type,desc,filename);
		//boolean result = goodsservice.AddGoods(goods);
		//System.out.println(result);
		if(result) {
			success="success";
			request.setAttribute("result",success);
		}
		
		request.getRequestDispatcher("/tiangoushuiguo/good_add.jsp").forward(request,response);
	}

	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
	
		doGet(request, response);
	}

}
