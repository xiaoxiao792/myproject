<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en">
<head>
	<meta http-equiv="Content-Type" content="text/html;charset=UTF-8">
	<title>天天生鲜-登录页</title>
	<link rel="stylesheet" type="text/css" href="css/reset.css">
	<link rel="stylesheet" type="text/css" href="css/main2.css">

</head>
<body>

	<div class="login_header clearfix">
		<a href="index.html"><img src="images/logo.png" alt="logo" /></a>
	</div>

	<div class="login_form_con clearfix">
		
		<div class="login_form">
			<img src="images/banner_login.png" class="login_banner fl">
			<p class="slogan fl">爱维C · 随时天狗水果</p>
			<div class="form_input_con fr">
				<div class="form_title">
					<h1>会员登录</h1>
					<a href="register.jsp">立即注册</a>
				</div>

				<form action="../loginservlet?state=1" method="post">
					<div class="form_group">
						<input type="text" name="username" class="input_txt" placeholder="请输入用户名">
						<span class="error">文字提示</span>
					</div>

					<div class="form_group">
						<input type="password" name="pwd" class="input_pwd" placeholder="请输入密码">
						<span class="error">文字提示</span>
					</div>

					<div class="form_group">
						<input type="checkbox" name="remember" id="remember" class="input_check fl">
						<label for="remember" class="fl">记住用户名</label>
						<a href="#"  class="find_pass fr">忘记密码</a>
					</div>

					<input type="submit" name="" value="登 录" class="input_sub">


				</form>

			</div>
		</div>

	</div>

	<div class="footer login_footer">
		<div class="links">
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
<script> 

//取出传回来的参数error并与yes比较
  var errori ='<%=request.getParameter("error")%>';
  if(errori=='yes'){
   alert("登录失败!");
  }
</script>

