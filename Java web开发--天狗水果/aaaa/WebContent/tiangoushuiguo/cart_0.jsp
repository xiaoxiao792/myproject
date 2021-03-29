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
					<span>|</span> <a href="#">我的订单</a>
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
<!--             <form method="post" action=""> -->
                <table class="table_list">
                <c:forEach items="${cart}" var="cart">
                    <tr class="tr">
                        <td class="checkbox"><input name="checkitems" type="checkbox" value="金龙鱼 东北大米 蟹稻共生 盘锦大米5KG"/></td>
                        <td class="name">
                            <div class="img"><a href="#"><img src="${cart.goods_img}"/></a></div>
                            <div class="p_name"><a href="#">${cart.goods_name}</a></div>
                        </td>
                        <td class="scj sp"><span id="Original_Price_1">${cart.goods_price}</span></td>
                        <td class="bgj sp"><span id="price_item_1">${cart.goods_price*0.8}</span></td>
                        <td class="sl">
                            <div class="Numbers">
                                <a onClick="setAmount.reduce('#qty_item_1')" href="javascript:void(0)" class="jian">-</a>
                                <input type="text" name="qty_item_" value="1" id="qty_item_1"
                                       onkeyup="setAmount.modify('#qty_item_1')" class="number_text">
                                <a onclick="setAmount.add('#qty_item_1')" href="javascript:void(0)" class="jia">+</a>
                            </div>
                        </td>
                        <td class="xj">
                        	<span id="total_item_1"></span>
                        	<input type="hidden" name="total_price"id="total_price" value="">
                        </td>
                        <td class="cz">
                            <p><a href="#">删除</a></p>
                        </td>
                    </tr>
                    </c:forEach>
                </table>
                <div class="sp_Operation clearfix">
                    <div class="select-all">
                        <div class="cart-checkbox"><input type="checkbox" id="CheckedAll" name="toggle-checkboxes"
                                                          class="jdcheckbox" clstag="clickcart">全选
                        </div>
                        <div class="operation"><a href="javascript:void(0);" id="send">删除选中的商品</a></div>
                    </div>
                    <!--结算-->
                    <div class="toolbar_right">
                        <ul class="Price_Info">
                            <li class="p_Total"><label class="text">商品总价：</label><span class="price sumPrice"
                                                                                       id="Total_price"></span></li>

                        </ul>
                        <div class="btn">
                            <a class="cartsubmit" href="index.jsp"></a>
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