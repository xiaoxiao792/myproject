<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
 <%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
        "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en">
<head>
    <meta http-equiv="Content-Type" content="text/html;charset=UTF-8">
    <title>天狗水果-我的订单</title>
    <link rel="stylesheet" type="text/css" href="css/reset.css">
    <link rel="stylesheet" type="text/css" href="css/main3.css">
    <link rel="stylesheet" type="text/css" href="css/common.css">
    <link rel="stylesheet" type="text/css" href="css/style.css">
    <link rel="stylesheet" type="text/css" href="css/Orders.css">
    <script type="text/javascript" src="js/jquery-1.12.4.min.js"></script>
    <script type="text/javascript" src="js/jquery-ui.min.js"></script>
    <script type="text/javascript" src="js/slide.js"></script>
    <script type="text/javascript" src="js/payfor.js"></script>
    
        
        
    <script type="text/javascript">
        $(document).ready(function () {
            //全选
            $("#CheckedAll").click(function () {
                if (this.checked) {                 //如果当前点击的多选框被选中
                    $('input[type=checkbox][name=checkitems]').attr("checked", true);
                } else {
                    $('input[type=checkbox][name=checkitems]').attr("checked", false);
                }
            });
            $('input[type=checkbox][name=checkitems]').click(function () {
                var flag = true;
                $('input[type=checkbox][name=checkitems]').each(function () {
                    if (!this.checked) {
                        flag = false;
                    }
                });

                if (flag) {
                    $('#CheckedAll').attr('checked', true);
                } else {
                    $('#CheckedAll').attr('checked', false);
                }
            });
            //输出值
            $("#send").click(function () {
                if ($("input[type='checkbox'][name='checkitems']:checked").attr("checked")) {
                    var str = "你是否要删除选中的商品：\r\n";
                    $('input[type=checkbox][name=checkitems]:checked').each(function () {
                        str += $(this).val() + "\r\n";
                    })
                    alert(str);
                } else {
                    var str = "你未选中任何商品，请选择后在操作！";
                    alert(str);
                }

            });
        })
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
                欢迎您：<em><%=username%></em><span>|</span>
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
                <span>|</span>
                <a href="#">用户中心</a>
                <!--					<a href="user_center_info.html">用户中心</a>-->
                <span>|</span>
                <a href="cart.jsp">我的购物车</a>
                <!--					<a href="cart.html">我的购物车</a>-->
                <span>|</span>
               
                <!--					<a href="user_center_order.html">我的订单</a>-->
            </div>
        </div>

    </div>

</div>

<!--	搜索框，购物车容器-->
<div class="search_bar clearfix">
    <a href="index.jsp" class="logo fl"><img src="images/logo.png"/>
        <div class="logo_text">
            爱 维 C 随 时 天 狗 水 果
        </div>
    </a>
    <div class="cart_text fl">我的订单</div>
</div>
<div class="order_con">
    <div class="r_user_style">
        <div class="Order_form">
            <div class="user_Borders">
                <div class="order_title_name">
                    <span class="order_name">我的订单</span>
                    <a class="fr" href="#">更多订单&gt;&gt;</a>
                </div>
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
	                                                <a href="#" class="product_img"><img src="images/${order.goods.goods_img}" width="80px" height="80px"/></a>
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
						<%-- <a href="../addgood?id=${orders.orders_goods_id }"> --%>
							<button class="button_class">提醒发货</button>
						</a>
						</c:if>
						 <c:if test="${orders.orders_goods_stata==2}">
						 <a href="../querenshouhuo?id=${orders.orders_goods_id }"> 
							<button class="button_class">确认收货</button>
						</a>
						</c:if>
                                
                            </td>
                        </tr>
                        </tbody>
                        </c:forEach>
                                               
                    </table>
                </div>
            </div>
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
