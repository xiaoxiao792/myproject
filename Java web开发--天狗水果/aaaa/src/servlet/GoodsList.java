package servlet;

import java.io.IOException;
import java.util.List;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import adddata.add_goods;
import data.goods_data;
import data.Page;


/**
 * Servlet implementation class GoodsList
 */
@WebServlet("/GoodsList")
public class GoodsList extends HttpServlet {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;


	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String indexPageStr = request.getParameter("pageIndex");
		List<goods_data> goods= add_goods.addgoodsdata();
		Page page = new Page();
		if(indexPageStr!=null) {
			page.setPageIndex(Integer.parseInt(indexPageStr)); 
		}		
		page.setTotalpage(add_goods.getPage());
		request.setAttribute("page",page);
		goods = add_goods.getGoodspage(page.getPageIndex(),page.getPageSize());
		request.setAttribute("goods",goods);
		request.getRequestDispatcher("tiangoushuiguo/good_list.jsp").forward(request,response);
	}

	
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doGet(request, response);
	}

}
