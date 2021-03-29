<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
    <%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
        "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en">
<head>
    <meta http-equiv="Content-Type" content="text/html;charset=UTF-8">
    <title>天狗水果-购物车</title>
    <link rel="stylesheet" type="text/css" href="css/reset.css">
    <link rel="stylesheet" type="text/css" href="css/main.css">
    <link rel="stylesheet" type="text/css" href="css/common.css">
    <link rel="stylesheet" type="text/css" href="css/style.css">
    <link rel="stylesheet" type="text/css" href="css/Orders.css">
    <script type="text/javascript" src="js/jquery-1.12.4.min.js"></script>
    <script type="text/javascript" src="js/jquery-ui.min.js"></script>
    <script type="text/javascript" src="js/slide.js"></script>
    <!-- <script type="text/javascript" src="js/payfor.js"></script> -->
<script type="text/javascript">
	window.onload=function (){
		$(document).on('click','#checkAll',function() {  
			    var flag = $("#checkAll").is(':checked');  
			    $("input[name='chk_item']:checkbox").each(function() {  
			        $(this).prop("checked", flag);  
			    });  
			}); 
		
			$("#delAll").click(function(){
				//alert("9090");
				var arr = $(":checkbox:not('#checkAll'):checked").length;
				if(arr>0){
					var ids="";
					var a = $(":checkbox:not('#checkAll'):checked");
					for(var i=0;i<arr;i++){
						ids += a[i].value+",";
					}
					ids = ids.substring(0,ids.length-1);
					alert(ids);
					location.href="DeleteCartServlet?ids="+ids;
				}
			})	
			
			
			
		$("#All").click(function(){
			//alert("9090");
			var arr = $(":checkbox:not('#checkAll'):checked").length;
			if(arr>0){
				var ids="";
				var a = $(":checkbox:not('#checkAll'):checked");
				for(var i=0;i<arr;i++){
					ids += a[i].value+",";
				}
												
				ids = ids.substring(0,ids.length-1);
				
				location.href="${pageContext.request.contextPath}/addorder?ids="+ids;
			}
		})
	}
	
	
</script>
</head>
<body>
	
<!--    顶部容器-->
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
				<div class="login_info fl">
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
    <a href="index.jsp" class="logo fl"><img src="images/logo.png">
        <div class="logo_text">
            爱 维 C 随 时 天 狗 水 果
        </div>
    </a>
    <div class="cart_text fl">购物车</div>
</div>
<div class="cart_con">
    <div class="Shopping_list">
        <div class="title_name">
            <ul>
                <li class="checkbox"></li>
                <li class="name">商品名称</li>
                <li class="scj">原价</li>
                <li class="bdj">现价</li>
                <li class="sl">购买数量</li>
                <li class="xj">小计</li>
                <li class="cz">操作</li>
            </ul>
        </div>
        <div class="shopping">
            <form method="post" action="">
                <table class="table_list">
                <c:forEach items="${cart}" var="cart">
                    <tr class="tr">
                        <td class="checkbox"><input type="checkbox" name="chk_item" value="${cart.goods.goods_id }"></td>
                        <td class="name">
                            <div class="img"><a href="#"><img src="images/${cart.goods.goods_img}"/></a></div>
                            <div class="p_name"><a href="#">${cart.goods.goods_name}</a></div>
                        </td>
                        <td class="scj sp"><span id="Original_Price_1">${cart.goods.goods_price}</span></td>
                        <td class="bgj sp"><span id="price_item_1">${cart.goods.goods_price*1}</span></td>
                        <td class="sl">
                            <div class="Numbers">
                                <a href="../delgood?id=${cart.goods.goods_id }" class="jian">-</a>
                                <input type="text" name="qty_item_" value="${cart.cart.goods_num}" id="qty_item_1"
                                       onkeyup="setAmount.modify('#qty_item_1')" class="number_text">
                                <a href="../addgood?id=${cart.goods.goods_id }" class="jia">+</a>
                            </div>
                        </td>
                        <td class="xj">
                        	<span id="total_item_1">${cart.goods.goods_price*cart.cart.goods_num}</span>
                        	<input type="hidden" name="total_price"id="total_price" value="">
                        </td>
                        <td class="cz">
                            <p><a href="../delcart?id=${cart.goods.goods_id }">删除</a></p>
                        </td>
                    </tr>
                    </c:forEach>
                </table>
                <div class="sp_Operation clearfix">
                    <div class="select-all">
                        <div class="cart-checkbox"><input type="checkbox" name="checkAll" id="checkAll"  
                                                          class="jdcheckbox">全选
                        </div>
                        
                    </div>
                    <!--结算-->
                    <div class="toolbar_right">
                        <ul class="Price_Info">
                            <!-- <li class="p_Total"><label class="text">商品总价：</label><span class="price sumPrice"
                                                                                       id="Total_price"></span></li> -->

                        </ul>
                        <div class="btn">
                            <a class="cartsubmit"  id ="All"></a>
                            <a class="continueFind" href="index.jsp"></a>
                         </div>
                    </div>
                </div>
            </form>
        </div>
    </div>
</div>

<div class="footer">
    <div class="foot_link">
        <a href="#">关于我们</a>
        <span>|</span>
        <a href="#">联系我们</a>
        <span>|</span>
        <a href="#">招聘人才</a>
        <span>|</span>
        <a href="#">友情链接</a>
    </div>
    <p>CopyRight © 2019 仲恺天狗水果信息技术有限公司 All Rights Reserved</p>
    <p>电话：020-10086    京ICP备：10086号</p>
</div>
</body>
</html>