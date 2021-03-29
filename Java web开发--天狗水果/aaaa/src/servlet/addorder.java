package servlet;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import updata.updata_sql;
import adddata.add_cart_goods;
import data.cart_goods_data;

/**
 * Servlet implementation class addorder
 */
public class addorder extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public addorder() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		String ids = request.getParameter("ids");
		String []g_id = ids.split(","); 
		String username = (String)request.getSession().getAttribute("username");
		List<cart_goods_data> cart = add_cart_goods.addcartgoods(username);
		List<cart_goods_data> query =new ArrayList<>();
		for(String id:g_id){
			for(cart_goods_data a:cart){
				if(a.getCart().getCart_id().equals(id)){
					query.add(a);
				}
			}			
		}
		updata_sql.cart_to_order2(username, cart);
		response.sendRedirect("order");
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
	}

}
