<%@page import="updata.updata_sql"%>
<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en">
<head>
<meta http-equiv="Content-Type" content="text/html;charset=UTF-8">
	<title>天狗水果-首页</title>
	<link rel="stylesheet" type="text/css" href="css/reset.css">
		<link rel="stylesheet" type="text/css" href="css/main.css">
			<script type="text/javascript" src="js/jquery-1.12.4.min.js"></script>
			<script type="text/javascript" src="js/jquery-ui.min.js"></script>
			<script type="text/javascript" src="js/slide.js"></script>

<script>
	function check(){
		var result=confirm("是否添加商品");
		if(!result){
			//window.location="AllUser";
			window.event.returnValue = false;
		}
	}
</script>
</head>
<body>
	<!--    顶部容器-->
 	 <c:if test="${empty goods}">
		<%
			response.sendRedirect("../indexservlet");
		%>
	</c:if>  
<%-- 	<c:if test="${empty goods1}">
		<%
			response.sendRedirect("../GoodsList2");
		%>
	</c:if>
 --%>

	<div class="header_con">

		<div class="header">

			<!--			左边-->
			<div class="welcome fl">欢迎来到天狗水果!</div>

			<!--			右边-->
			<div class="fr">
				<%
					String username = (String) session.getAttribute("username");
					if (!(username == null || username == "")) {
				%>
				<div class="login_info fl" style="margin-right: 10px;">
					欢迎您：<em><%=username%></em> <span>|</span>
				</div>
				<div class="login_btn fl">
					<a href="register.jsp">注册</a>
				</div>
				<%
					} else {
				%>
				<div class="login_btn fl">
					<a href="login.jsp">登录</a> <span>|</span> <a href="register.jsp">注册</a>
				</div>
				<%
					}
				%>
				<div class="user_link fl">
					<span>|</span> <a href="#">用户中心</a>
					<span>|</span> <a href="cartTest.jsp">我的购物车</a>
					<span>|</span> <a href="ordertest.jsp">我的订单</a>
					<span>|</span> <a href="../logoutservlet">退出</a>
				</div>
			</div>

		</div>

	</div>

	<!--	搜索框，购物车容器-->
	<div class="search_bar clearfix">
		<a href="index.jsp" class="logo fl"><img src="images/logo.png"/>
				<div class="logo_text">爱 维 C 随 时 天 狗 水 果</div></a>
		<div class="search_con fl">
			<input type="text" class="input_text fl" name=""
				placeholder="搜索天狗水果商品"/> <input type="button"
				class="input_btn fr" name="" value="搜索"/>
		</div>
		<div class="guest_cart fr">
			<a href="cartTest.jsp" class="cart_name fl">我的购物车</a>
			<div class="goods_count fl" id="show_count">0</div>
		</div>
	</div>

	<!--	导航顶部-->
	<div class="navbar_con">
		<div class="navbar">
			<h1 class="fl">全部商品分类</h1>
			<ul class="navlist fl">
				<li><a href="">首页</a></li>
				<li class="interval">|</li>
				<li><a href="">企业采购</a></li>
				<li class="interval">|</li>
				<li><a href="">抽奖</a></li>
			</ul>
		</div>
	</div>

	<!--	导航框 轮播图 -->
	<div class="center_con clearfix">
		<ul class="subnav fl">
			<li><a href="#model01" class="fruit">时令水果</a></li>
			<li><a href="#model02" class="seafood">进口水果</a></li>
			<li><a href="#model03" class="meet">新鲜果切</a></li>
			<li><a href="#model04" class="egg">水果酸奶</a></li>
			<li><a href="#model05" class="vegetables">休闲零食</a></li>
			<li><a href="#model06" class="ice">冰镇果汁</a></li>
		</ul>
		<div class="slide fl">
			<ul class="slide_pics">
				<li><img src="images/slide.jpg" alt="幻灯片"/></li>
				<li><img src="images/slide02.jpg" alt="幻灯片"/></li>
				<li><img src="images/slide03.jpg" alt="幻灯片"/></li>
				<li><img src="images/slide04.jpg" alt="幻灯片"/></li>
			</ul>
			<div class="prev"></div>
			<div class="next"></div>
			<ul class="points">

			</ul>
		</div>
		<div class="adv fl">
			<a href="#"><img src="images/adv01.jpg"/></a> <a href="#">
			<img src="images/adv02.jpg"/></a>
		</div>
	</div>

	<div class="list_model">
		<div class="list_title clearfix">
			<h3 class="fl" id="model04">水果酸奶</h3>
			<div class="subtitle fl">
				<span>|</span> <a href="#">酸奶</a> <a href="#">含乳饮品</a> <a href="#">进口酸奶</a>
			</div>
			<a href="#" class="goods_more fr">查看更多 ></a>
		</div>

		<div class="goods_con clearfix">
			<div class="goods_banner fl">
				<img src="images/banner04.jpg"/>
			</div>
			<ul class="goods_list fl">
				<c:forEach items="${goods}" var="goods">
					<li>
						<h4>
							${goods.goods_name}
						</h4>
						<a href="../addcart?id=${goods.goods_id}" onclick="check()" id="id">
						<img src="images/${goods.goods_img}"/>
						</a>
						<div class="prize fl">¥${goods.goods_price}</div>
						<div class="cart_alogo fr">
							
						</div>
					</li>
				</c:forEach>
			</ul>
		</div>
	</div>

	<div class="list_model">
		<div class="list_title clearfix">
			<h3 class="fl" id="model05">休闲零食</h3>
			<div class="subtitle fl">
				<span>|</span> <a href="#">坚果</a> <a href="#">肉脯</a> <a href="#">水果干</a>
			</div>
			<a href="#" class="goods_more fr">查看更多 ></a>
		</div>

		<div class="goods_con clearfix">
			<div class="goods_banner fl">
				<img src="images/banner05.jpg"/>
			</div>
			<ul class="goods_list fl">
				<c:forEach items="${goods1}" var="goods1">
					<li>
						<h4>
							${goods1.goods_name}
						</h4>
						<a href="../addcart?id=${goods1.goods_id}" onclick="check()" id="id">
						<img src="images/${goods1.goods_img}"/>
						</a>
						<div class="prize fl">¥${goods1.goods_price}</div>
						<div class="cart_alogo fr"></div>
					</li>
				</c:forEach>
			</ul>
		</div>
	</div>

	<div class="footer">
		<div class="foot_link">
			<a href="#">关于我们</a> <span>|</span> <a href="#">联系我们</a> <span>|</span>
			<a href="#">招聘人才</a> <span>|</span> <a href="#">友情链接</a>
		</div>
		<p>CopyRight © 2019 仲恺天狗水果信息技术有限公司 All Rights Reserved</p>
		<p>电话：020-10086 京ICP备：10086号</p>
	</div>

</body>
</html>
