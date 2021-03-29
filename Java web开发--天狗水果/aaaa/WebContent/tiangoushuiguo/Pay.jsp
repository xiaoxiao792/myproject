<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
<link href="${pageContext.request.contextPath}/css/bootstrap.css" rel="stylesheet">
<link rel="stylesheet" href="${pageContext.request.contextPath}/css/iconfont3.css" />
  <link rel="stylesheet" type="text/css" href="tiangoushuiguo/css/reset.css">
    <link rel="stylesheet" type="text/css" href="tiangoushuiguo/css/main3.css">
    <link rel="stylesheet" type="text/css" href="tiangoushuiguo/css/common.css">
    <link rel="stylesheet" type="text/css" href="tiangoushuiguo/css/style.css">
    <link rel="stylesheet" type="text/css" href="tiangoushuiguo/css/Orders.css">
<!-- <style>
	.All{
		width:900px;
		margin:50px auto;
	}
	table{
		width:900px;
		border:1px solid #ddd;
		border-collapse:collapse;
	}
	.th_class{
		height:50px;
		background:#f1f1f1;
		font-size:15px;
		font-family:"宋体";
		text-align:center;
	}
	.th_class th{
		text-align:center;
	}
	tbody tr img{
		width:90px;
		height:90px;
	}
	tbody tr td{
		padding:8px;
		text-align:center;
		border:1px solid #ddd;
		font-size:14px;
		font-family:"微软雅黑";
		color:#333;
	}
	tr{
		border:1px solid #ddd;
	}
	.button_class{
		width:70px;
		height:25px;
		background:#399FD8;
		border-radius: 3px;
		border:none;
		color:#fff;
		font-size:14px;
	}
	.foot{
		width:244px;
		margin:auto auto;
	}
	#id{
		text-decoration:none;
	}
	.top{
		width:100%;
		height:40px;
		background:#F2F9FD;
		position:fixed;
		top:0px;
	}
	.dd{
		line-height:36px;
		font-size:14px;
		color:#775577;
		padding-left:20px;
	}
	.one{
		width:300px;
		margin:60px auto;
		text-align:center;
	}
	h3{
		color:#707070;
	}		
</style> -->
</head>
<body>
    <div class="top">
    	 <span class="dd">/订单管理/订单发货</span> 
    </div>	
     <div class="r_user_style">
	<div class="Order_form_list">
	
                    <table>
                    
                        <thead>
                        <tr><td class="list_name_title0">商品</td>
                            <td class="list_name_title1">单价(元)</td>
                            <td class="list_name_title2">数量</td>
                            <td class="list_name_title4">实付款(元)</td>
                            <td class="list_name_title5">订单状态</td>
                            <td class="list_name_title6">操作</td>
                        </tr>
                        </thead>
                        
                        <c:forEach items="${order}" var="orders">
                        <tbody>
                        <tr>
                        	<td colspan="6" class="Order_form_time">${orders.orders_goods_time} ${orders.orders_goods_id}</td>
                        </tr>
                        
                        <tr>
                     
                            <td colspan="3">
                            <c:forEach items="${orders.order_goods_list}" var="order"> 
                                <table class="Order_product_style">
                                    <tbody>
                                    	<tr>
                                        	<td>
                                            	<div class="product_name clearfix">
	                                                <a href="#" class="product_img"><img src="tiangoushuiguo/images/${order.goods.goods_img}" width="80px" height="80px"/></a>
	                                                <a href="3">${order.goods.goods_name}</a>
	                                                <p class="specification">500g/份</p>
	                                            </div>
	                                        </td>
	                                        <td>${order.goods.goods_price}</td>
	                                        <td>${order.order.goods_num}</td>
	                                    </tr>
	                                     
                                    </tbody>
                            	</table>
                            	</c:forEach>
                            </td>
                            
                            <td class="split_line">${orders.orders_goods_price}</td>
                            <td class="split_line" value="${orders.orders_goods_stata}" id="goods_class">
                            <c:if test="${orders.orders_goods_stata==1}">
							未发货
						</c:if>
						<c:if test="${orders.orders_goods_stata==2}">
							已发货
						</c:if>
						<c:if test="${orders.orders_goods_stata==3}">
							已收货
						</c:if>

                                 
                               
                            </td>
                            <td class="operating">
                                
                                <c:if test="${orders.orders_goods_stata==1}">
						<a href="./fahuo?id=${orders.orders_goods_id }"> 
							<button class="button_class">发货</button>
					
						</c:if>
						 <c:if test="${orders.orders_goods_stata==2}">
						 <%-- <a href="../querenshouhuo?id=${orders.orders_goods_id }">  --%>
							<button class="button_class">提醒收货</button>
						</a>
						</c:if>
                                
                            </td>
                        </tr>
                        </tbody>
                        </c:forEach>
                                               
                    </table>
                </div>
                 </div>
       
		
		
		
		
	
	
</body>
</html>