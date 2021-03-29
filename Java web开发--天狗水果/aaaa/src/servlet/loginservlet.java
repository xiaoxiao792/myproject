package servlet;

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import query.query_data;

/**
 * Servlet implementation class login
 */
public class loginservlet extends HttpServlet {
	private static final long serialVersionUID = 1L;
       
    /**
     * @see HttpServlet#HttpServlet()
     */
    public loginservlet() {
        super();
        // TODO Auto-generated constructor stub
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

		request.setCharacterEncoding("utf-8");
		String username = request.getParameter("username");
		String pwd = request.getParameter("pwd");
		int state = Integer.parseInt(request.getParameter("state"));
		int  flag = query_data.query5_user(username, pwd, state);
		if (flag == 1) {
			request.getSession().setAttribute("username", username);
			response.sendRedirect("tiangoushuiguo/index.jsp");	
		} else if (flag == 2) {
			request.getSession().setAttribute("username", username);
			response.sendRedirect("tiangoushuiguo/Management_main.jsp");	
		} else {
			if (state == 1)
				response.sendRedirect("tiangoushuiguo/login.jsp?error=yes");	
			else 
				response.sendRedirect("tiangoushuiguo/adminlogin.jsp?error=yes");	
		}
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		doGet(request, response);
	}

}
