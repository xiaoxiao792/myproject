<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
<style>
	.left{
			border-right:1px #3CF solid;
		}
</style>
</head>

	<frameset rows="70,*" frameborder="no">
		<frame src="Management_top.jsp">
		<frameset rows="*" cols="15%,*">
		<frame src="Management_left.jsp"  class="left">
		<frame src="${pageContext.request.contextPath}/tiangoushuiguo/M_right.jsp" name="right" class="left">
	<frameset>

</html>