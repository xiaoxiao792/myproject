<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>管理员管理</title> 
<style>
	*{
		padding:0;
		margin:0;
	}
	body{
		background-color:#F2F9FD;
	}
	.menu_list {
		width: 100%;
		margin: 0;
	}
	 
	.menu_head {
		height: 40px;
		text-align:center;
		line-height: 40px;
		padding:auto auto;
		font-size: 15px;
		color: #525252;
		cursor: pointer;
		/* //border-top: 1px solid #ddd; */
		border-bottom: 1px solid #ddd;
		position: relative;
		margin: 0px auto;
		font-weight: bold;
		background: #F2F9FD;
	}
	 
	.menu_list .current {
		background: #F2F9FD;
	}
	 
	.menu_nva {
		line-height: 40px;
		backguound: #fff;
		/* border-right: 1px solid #51a9f18c; */
	}
	 
	.menu_nva a {
		display: block;
		height: 40px;
		line-height: 40px;
		text-align:center;;
		color: #777777;
		background: #fff;
		text-decoration: none;
		text-align:center;
		border-bottom: 1px solid #ddd;
	}
	 
	.menu_nva a:hover {
		text-decoration: none;
	}
	.head{
		height: 40px;
		text-align:center;
		line-height: 40px;
		padding:auto auto;
		font-size: 17px;
		background: #628CD4;
		color:#fff;		
	}
	a{
		text-decoration:none;
	}
</style>
</head>
 
<body>
 
	<div id="firstpaneDiv" class="menu_list">
		<h3 class="head">菜单列表</h3>
		
		<%-- <a href="${pageContext.request.contextPath}/getUserServlet" target="right"><h3 class="menu_head current">用户管理</h3></a> --%>
<!-- 		<div style="display:block" class="menu_nva">
			<a href="#">用户列表</a>
		</div> -->
		<h3 class="menu_head">商品管理</h3>
		<div style="display:none" class="menu_nva">
			<a href="${pageContext.request.contextPath}/GoodsList" target="right">商品列表</a>
			<a href="${pageContext.request.contextPath}/tiangoushuiguo/good_add.jsp" target="right">商品上架</a>
		</div>
		<h3 class="menu_head">订单管理</h3>
		<div style="display:none" class="menu_nva">
			<%-- <a href="${pageContext.request.contextPath}/AllOrder?state=state" target="right">订单列表</a> --%>
			<a href="${pageContext.request.contextPath}/Pay?state=0" target="right">订单发货</a>
			<%-- <a href="${pageContext.request.contextPath}/Fa?state=1" target="right">已发货订单</a>
			<a href="${pageContext.request.contextPath}/Shou?state=2" target="right">已收货订单</a> --%>
		</div>
    </div>
 
<script src="${pageContext.request.contextPath}/tiangoushuiguo/js/jquery-1.12.4.min.js"></script>
<script>
		$(document).ready(function(){
		/* 	$("#firstpaneDiv .menu_nva:eq(0)").show(); */
			$("#firstpaneDiv h3.menu_head").click(function(){
				$(this).addClass("current").next("div.menu_nva").slideToggle(200).siblings("div.menu_nva").slideUp("slow");
				$(this).siblings().removeClass("current");
			});
			$("#secondpane .menu_nva:eq(0)").show();
			$("#secondpane h3.menu_head").mouseover(function(){
				$(this).addClass("current").next("div.menu_nva").slideDown(400).siblings("div.menu_nva").slideUp("slow");
				$(this).siblings().removeClass("current");
			});
		});
</script>
</body>
 
</html>
