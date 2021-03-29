<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>    
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>

<style>
	*{
		margin:0px;
		padding:0px;
	}
	#bigAll{
		width:805px;
		/* height:900px; */
		margin:auto auto;
		/* border:1px #e0e0e0 solid; */
	}
	
	#big{
		width:400px;
        height:40px;
       /* 	border:1px #e0e0e0 solid;  */
        margin-top:20px;
        float:left;
	}
	
	.title{
        font-size:15px;
        padding-left:10px;
        float:left;
        line-height:38px;
        font-family:"宋体";
        font-weight:bold;
        color: #666; 
        }
     .big_input{
        	float:left;
        	width:280px;
        	height:40px;
        	line-height:38px;
        	/* border:1px #e0e0e0 solid;  */
        }
        .big_input input{
        	height:23px;
        	width:270px;
        	margin-left:20px;
        }
        
        #big2{
			width:800px;
        	/* height:40px; */
        	height:130px;
        	/* border:1px #e0e0e0 solid; */
        	margin-top:20px;
        	float:left;
		}
		#big2 input{
			height:23px;
        	width:670px;
        	margin-left:20px;
		}
		#big2 textarea{
/* 			height:23px;
        	width:670px; */
        	margin-left:20px;
		}
		.big_file{
			float:left;       	
        	height:40px;
        	line-height:36px;
   			border-radius: 4px;
   			margin-left:20px;
		}
		.input_file{
			
		}
		#file_all{
			width:200px;
			height:40px;
			border: 1px solid #ddd;
   			border-radius: 4px;
   			position: relative;
		}
		.a-upload {
    		padding: 4px 10px;
   	 		height: 20px;
    		line-height: 20px;
    		color: #444;
    		position: relative;
    		border: 1px solid #ddd;
    		border-radius: 4px;
    		overflow: hidden;
    		text-decoration: none;
    		line-height:40x;
    		
		}
		.a-upload  input {
   	 		position: absolute;
    		opacity: 0;
    		width:100px;
		}

		.a-upload:hover {
    		color: #444;
    		background: #eee;
    		border-color: #ccc;
    		text-decoration: none
		}
		.big_input select{
			margin-left:20px;
			height:30px;
        	width:150px;
        	font-size:16px;
		}
		 #big3{
			width:800px;
        	height:40px;
            /* border:1px #e0e0e0 solid;  */
        	margin-top:20px;
        	float:left;
		}
		.big_submit{
			margin-left:90px;
			width:120px;
			height:32px;
		}
		.big_submit input{
			width:118px;
			height:31px;
			border-radius: 4px;
			font-size:16px;
			border: 1px solid #0ae;
			outline:none;
			background:#0ae;
			color:#fff;
		}
		.big_submit input:hover{
			background: #3cf;
			border: 1px solid #3cf;
		}
		.top{
			width:100%;
			height:40px;
			background:#F2F9FD;
			margin:auto auto;
		}
		.dd{
			line-height:36px;
			font-size:14px;
			color:#775577;
			padding-left:20px;
		}
		.top{
			width:100%;
			height:40px;
			background:#F2F9FD;
			margin:auto auto;
		}				
</style>
<link href="${pageContext.request.contextPath}/tiangoushuiguo/js/jquery-1.12.4.min.js" rel="stylesheet">
<script>
</script>
</head>
<body>

	<div class="top"> <span class="dd">/商品管理/商品列表/修改商品</span> </div>	
	<form action="${pageContext.request.contextPath}/UpdateGoods" method="post" enctype="multipart/form-data">
		<div id="bigAll">
			<div id="big">
				<label class="title">商品编号</label>
				<div class="big_input">
					<input type="text" name="g_id" value="${goods.goods_id}" readonly="readonly">
				</div>
			</div>
						
			<div id="big">
				<label class="title">商品名称</label>
				<div class="big_input" >
					<input type="text" name="gname" value="${goods.goods_name}">
				</div>
			</div>
			
			<div id="big">
				<label class="title">商品价格</label>
				<div class="big_input">
					<input type="text" name="price"  value="${goods.goods_price}">
				</div>
		</div>
		
		<div id="big">
			<label class="title">商品类别</label>
				<div class="big_input">
					<select name="type">
						<option>水果酸奶</option>
						<option>休闲零食</option>
					</select>		
				</div>			
		</div>
		
		
		<div id="big3">
			<label class="title">商品图片</label>
			<div class="big_file">
				<!-- <input type="file" name="number" class="input_file">点击上传图片 -->
				<a href="javascript:;" class="a-upload">
   					<input type="file" name="url">点击上传图片
				</a>			
			</div>
		</div>
		
		<div id="big">
			<div class="big_submit">
				<input type="submit" value="确认保存">
			</div>
		</div>
				
		</div>

		
	</form>
	  
</body>
</html>