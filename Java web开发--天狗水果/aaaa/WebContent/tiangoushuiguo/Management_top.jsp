<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
<style>
	body{
/* 		background:url("${pageContext.request.contextPath}/tiangoushuiguo/img/bg.png"); */
			background-color:#5d87d1
	}
	*{
		margin:0px;}
	#top{
		margin:auto;
		height:60px;
		display:table;
		position: absolute;
    	top: 0;
    	left: 30px;
    	right: 0;
    	bottom: 0;		
	}
	.h1{
		font-size:25px;
		font-family:"微软雅黑";
		color:#ffffff;
		margin-left:10px;
		float:left;
	}
	.img_logo{
		width:50px;
		height:50px;
		float:left;
	}
	span{
		display:table-cell;
		vertical-align:middle;
	}
	.button_class{
		background-color:#ED3B3B;
		border:none;
		width:93px;
		height:34px;
		color:#fff;
		border-radius:5px;
		font-size:14px;
		margin-left:10px;
	}
	.button_class2{
		background-color:#50DB89;
		border:none;
		width:93px;
		height:34px;
		color:#fff;
		border-radius:5px;
		font-size:14px;
		margin-left:10px;
	}	
	.button_class2:hover{
		background-color:#6AE09B;
	}
	.button_class:hover{
		background-color:#F55050;
	}	
</style>
</head>
<body>
	<div id="top">
			<span><img src="${pageContext.request.contextPath}/tiangoushuiguo/img/管理员 (3).png" class="img_logo"></span>
			<span><h1 class="h1">后台管理系统</h1></span>
			<span><a href="${pageContext.request.contextPath}/tiangoushuiguo/index.jsp" target="_top"><button class="button_class2">商城首页</button></a></span>
			<span><a href="Login.jsp" target="_top"><button class="button_class">退出登录</button></a></span>
	</div>
</body>
</html>