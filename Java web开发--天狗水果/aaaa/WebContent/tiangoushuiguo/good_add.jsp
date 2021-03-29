<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>商品上架</title>
<link href="${pageContext.request.contextPath}/jquery/jquery-3.4.1.js" rel="stylesheet">
<link rel="stylesheet" href="${pageContext.request.contextPath}/css/iconfont4.css"/>
<script>

</script>

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
</style>
<script type="text/javascript" src="${pageContext.request.contextPath}/jquery/jquery-3.4.1.js"></script>
<script type="text/javascript" src="${pageContext.request.contextPath}/jquery/uploadify/jquery.uploadify.min.js"></script>

<!-- <script type="text/javascript">
<!-- 		$(function() {
			
			$('#file_upload').uploadify({
				'queueID'  : 'queue',//上传进度展示
				'buttonText': 'selectFile..',
				'langFile':'uploadifyLang_zh.js',
				'swf': 'uploadify.swf',
				'formData': {
					'pid' : 'portal',
					'token': 'portal',
					'filedesc':''
				},
				'method':'Post',
				'scriptAccess' : 'always' ,
				'uploader' : 'http://10.**.23.***:8821/mgr/voice/file/v1/upload',
				 'auto': true,
				 'onUploadStart' : function(file) {
					alert('Starting to upload ' + file.name);
				},
				'onUploadSuccess' : function(file, data, response) {
					alert('The file ' + file.name + ' was successfully uploaded with a response of ' + response + ':' + data);
				},
				'onUploadError' : function(file, errorCode, errorMsg, errorString) {
					alert('The file ' + file.name + ' could not be uploaded: ' + errorString);
				},
				onComplete: function (evt, queueID, fileObj, response, data) {
						alert(response);
			//	$('<li></li>').appendTo('#fileContent'+id).html(response);
			}
 
			});
		});
	</script> -->

</head>
<body>
	<% 	
		request.setCharacterEncoding("utf-8");
		response.setCharacterEncoding("utf-8");
		response.setContentType("text/html;charset=utf-8");
		String result = (String)request.getAttribute("result");
		if(result!=null){ 
	%>  		
    	<script type="text/javascript" language="javascript">
			alert("增加成功");
		</script> 
    <%
		}	
    %>
    <div class="top">
    	 <span class="dd">/商品管理/商品上架</span> 
    </div>	
	<form action="${pageContext.request.contextPath}/AddGoodsServlet" method="post" enctype="multipart/form-data">
		
			
		
			
			<div id="big">
				<label class="title">商品名称</label>
				<div class="big_input">
					<input type="text" name="gname">
				</div>
			</div>
			
			<div id="big">
				<label class="title">商品价格</label>
				<div class="big_input">
					<input type="text" name="price">
				</div>
		</div>

	
		
		<div id="big">
			<label class="title">商品类别</label>
			<div class="big_input">
				<!-- <input type="text" name="type"> -->
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
			<!-- <input type="submit" value="gfg"> -->			
		</div>
	<!-- 	
		<textarea name="desc"></textarea>
		商品编号<input type="text" name="g_id"><br>
		
		商品品牌<input type="text" name="brand"><br>
		
		商品名称<input type="text" name="gname"><br>
		
		商品价格<input type="text" name="price"><br>
		
		商品数量<input type="text" name="number"><br>
		
		商品类别<input type="text" name="type"><br>
		
		商品描述<input type="text" name="desc"><br>
		<div id="file_all">
			<p>点击上传图片</p><input type="file" name="url" class="file_hidden">
		</div> -->
		
	</form>
	  
</body>
</html>