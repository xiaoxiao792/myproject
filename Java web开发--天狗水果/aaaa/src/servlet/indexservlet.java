package servlet;

import java.io.IOException;
import java.util.List;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import query.query_data;
import data.goods_data;

/**
 * Servlet implementation class GoodsList
 */
@WebServlet("/indexservlet")
public class indexservlet extends HttpServlet {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;


	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
 
		List<goods_data> goods = query_data.query1_goods();
		List<goods_data> goods1 = query_data.query2_goods();
		request.getSession().setAttribute("goods",goods);
		request.getSession().setAttribute("goods1",goods1);
		response.sendRedirect("./tiangoushuiguo/index.jsp");		
	}

	
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doGet(request, response);
	}

}
