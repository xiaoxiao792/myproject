package servlet;

import java.io.IOException;
import java.util.List;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import adddata.add_cart_goods;
import data.cart_goods_data;

/**
 * Servlet implementation class cart
 */
public class cartservlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public cartservlet() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

			request.setCharacterEncoding("utf-8");
			String username = (String)request.getSession().getAttribute("username");
			List<cart_goods_data> cart = add_cart_goods.addcartgoods(username);
			request.getSession().setAttribute("cart",cart);
			if(cart.size()==0){
				response.sendRedirect("tiangoushuiguo/cart_0.jsp?username=" + request.getParameter("username") + "");
			}else {
				response.sendRedirect("tiangoushuiguo/cart.jsp?username=" + request.getParameter("username") + "");
			}
			
	}	

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		doGet(request, response);
		// TODO Auto-generated method stub
	}

}
