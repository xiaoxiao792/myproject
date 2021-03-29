<%@page import="data.goods_data"%>
<%@page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@page import="java.util.List"%>
<%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
<link href="${pageContext.request.contextPath}/tiangoushuiguo/css/bootstrap.css" rel="stylesheet">
<!--  --><link href="${pageContext.request.contextPath}/css/bootstrap-responsive.min.css" rel="stylesheet">
<link href="${pageContext.request.contextPath}/tiangoushuiguo/css/inn.css" rel="stylesheet">
<link rel="stylesheet" href="${pageContext.request.contextPath}/tiangoushuiguo/css/iconfont1.css" />
<link rel="stylesheet" href="${pageContext.request.contextPath}/tiangoushuiguo/css/iconfont2.css" />
<link rel="stylesheet" href="${pageContext.request.contextPath}/tiangoushuiguo/css/iconfont3.css" />
<style>
*{
	margin:0;
	padding:0;
}	
	table tr td img {
		width:90px;
		height:90px;
	}
	table th {
		font-size:18px;
		text-align:center;
	}
	table tr td{
		vertical-align: middle;
	}
	#content{
		width:1000px;
		margin:50px auto;
	}
	span{
		font-size:25px;
	}
	.foot{
		width:320px;
		height:50px;
		border:1px #e0e0e0 soild;
		margin:auto auto;
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
		position:fixed;
	}	
</style>
<script type="text/javascript" src="${pageContext.request.contextPath}/tiangoushuiguo/js/jquery-1.12.4.min.js"></script>
<script type="text/javascript" src="${pageContext.request.contextPath}/tiangoushuiguo/js/bootstrap.min.js"></script>
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
				location.href="Delet?ids="+ids;
			}
		})
		//odd：匹配所有索引值为奇数的元素，从0开始计数
		//even：匹配所有索引值为偶数的元素，从0开始计数
		//$("thead").css("background-color", "#DDEBF7");
		//$("tbody tr:even").css("background-color", "#DDEBF7");
		//$("tbody tr:odd").css("background-color", "#D9E1F2"); //为单数行表格设置背颜色素 
	}
</script>
<script>
	function check(){
		var result=confirm("你确定要删除？");
		if(!result){
			//window.location="AllUser";
			window.event.returnValue = false;
		}
	}
</script>
</head>
<body>
	<div class="top">
    	 <span class="dd">/商品管理/商品列表</span> 
    </div>
	<div id="content">
	<table class="table table-hover"  style="width:1000px; border:1px solid #ddd; text-align:center">
		<thead style="width:1000px">
			<tr style="height:30px">
				<th>全选 <input type="checkbox" name="checkAll" id="checkAll" value="">  </th>
				<th>商品编号</th>
				<th>商品名称</th>
				<th>商品价格</th>
				<th>商品类别</th>
				<th>商品图片</th>
				<th>编辑</th>
				<th>下架</th>
			</tr>
		</thead>
		
		<%
			List<goods_data> users = (List<goods_data>)request.getAttribute("goods");
			for(int i =0;i<users.size();i++){
				goods_data u = users.get(i);
		
		%>
			<tbody>
			<tr>
				<td style="vertical-align: middle"><input type="checkbox" name="chk_item" value="<%=u.getGoods_id() %>"> </td>
				<td style="vertical-align: middle"><%=u.getGoods_id() %></td>
				<td style="vertical-align: middle"><%=u.getGoods_name()  %></td>
				<td style="vertical-align: middle">￥<%=u.getGoods_price() %></td>
				<td style="vertical-align: middle"><%=u.getGoods_class() %></td>
				<%  String path="${pageContext.request.contextPath}/images/";
					//path +=s;
				%>
				<td style="vertical-align: middle"><img src="${pageContext.request.contextPath}/tiangoushuiguo/images/<%=u.getGoods_img()%>"></td>
				<td style="vertical-align: middle">
					<a href="UpdateGoodsServlet?id=<%=u.getGoods_id()%>"><span class="icon iconfont">&#xe66c;</span></a>
				</td>
				<td style="vertical-align: middle">
					<a href="DeleteGoods?id=<%=u.getGoods_id()%>" onclick="check()" id="id"><span class="icon iconfont">&#xe64a;</span></a>
				</td>
			</tr>
		</tbody>
		<% 
			}
		%>	
		
	</table>


	</div>
	<div class="foot">
	<ul class="pagination">
		<li><a href="GoodsList?pageIndex=1">首页</a></li>
		<c:if test="${requestScope.page.pageIndex==1}">
			<li class="previous disabled"><a href="javascipt:;">上一页</a></li>
		</c:if>
		<c:if test="${requestScope.page.pageIndex!=1}">
			<li><a href="GoodsList?pageIndex=${requestScope.page.pageIndex-1}">上一页</a></li>
		</c:if>
		<c:if test="${requestScope.page.pageIndex==requestScope.page.totalpage}">
			<li class="previous disabled"><a href="javascipt:;">下一页</a></li>
		</c:if>
		<c:if test="${requestScope.page.pageIndex<requestScope.page.totalpage}">
			<li><a href="GoodsList?pageIndex=${requestScope.page.pageIndex+1}">下一页</a></li>
		</c:if>
		<li><a href="GoodsList?pageIndex=${requestScope.page.totalpage}">尾页</a></li>
	
	</ul>
	</div>
</body>
</html>