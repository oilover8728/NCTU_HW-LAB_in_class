let canvas = document.getElementById("game"); //<--視窗-->
let ctx = canvas.getContext("2d");			  //<--畫布-->

//設定時鐘半徑和中心點
let radius = Math.floor(Math.min(canvas.width,canvas.height)/2);
ctx.translate(radius, radius);

//漸層
var grd = ctx.createRadialGradient(0, 0, radius*0.9, 0, 0, radius);

//一開始先畫好一次
//畫時鐘的邊框
grd.addColorStop(0, "black");
grd.addColorStop(0.9, "gray");
grd.addColorStop(1, "black");

ctx.fillStyle = grd;
ctx.arc(0, 0,radius,0, 2*Math.PI);
ctx.fill();
draw();

//開始畫好之後每一秒重新畫來更新時鐘
function draw(){
	//時鐘的盤面
	ctx.beginPath();
	ctx.fillStyle = 'white';
	ctx.arc(0,0,radius*0.9,0,2*Math.PI);
	ctx.fill();
	
	let unit = Math.PI/6;
	//填數字
	for(let i=1;i<=12;i++){
		x = radius * 0.77 * Math.cos((-3+i)*unit);
		y = radius * 0.77 * Math.sin((-3+i)*unit);
		//ctx.beginPath();
		ctx.font= Math.floor(radius*0.15)+"px Arial";
		ctx.fillStyle = "black";
		ctx.textAlign = "center";
		ctx.fillText(i, x, y+8);
	}

	//畫針
	var now = new Date();
	var hour = now.getHours();
	var minute = now.getMinutes();
	var second = now.getSeconds();
	
	//hour
	hour = hour % 12;
	hour = Math.PI/6*(hour+minute/60+second/3600);
	drawHand(hour , radius*0.5, radius*0.055,0);
	//minute
	minute = Math.PI/30 * (minute+second/60); 
	drawHand(minute , radius*0.65, radius*0.05,0);
	//second
	second = Math.PI/30*second;
	drawHand(second, radius*0.8, radius*0.015,1);

	function drawHand(angle, length, width,color){
		if(color==1){
			ctx.strokeStyle = 'red';
		}
		else{
			ctx.strokeStyle = 'black';
		}
		ctx.beginPath();
		ctx.lineWidth = width;
		ctx.lineCap = "round";
		ctx.moveTo(0,0);
		ctx.rotate(angle);
		ctx.lineTo(0,-length);
		ctx.stroke();
		ctx.rotate(-angle);
	}
	
	//畫刻度
	for(let i=0;i<60;i++){
		count = Math.PI/30*i;
		ux = radius  *0.86* Math.cos(-Math.PI/2+i*Math.PI/30);
		uy = radius  *0.86* Math.sin(-Math.PI/2+i*Math.PI/30);
		drawCount(count, radius*0.88, radius*0.02,ux,uy,i);
	}
	
	function drawCount(angle, length, width,x,y,num){
		//5的倍數要畫粗並換顏色
		if(num%5==0){
			ctx.beginPath();
			ctx.lineWidth = width*2;
			ctx.lineCap = "round";
			ctx.moveTo(x,y);
			ctx.rotate(angle);
			ctx.lineTo(0,-length);
			ctx.strokeStyle = 'orange';
			ctx.stroke();
			ctx.rotate(-angle);
		}
		else{
			ctx.beginPath();
			ctx.lineWidth = width;
			ctx.lineCap = "round";
			ctx.moveTo(x,y);
			ctx.rotate(angle);
			ctx.lineTo(0,-length);
			ctx.strokeStyle = 'gray';
			ctx.stroke();
			ctx.rotate(-angle);
		}
	}
	
	//裝飾 3個針固定的零件
	ctx.beginPath();
	ctx.fillStyle = 'white';
	ctx.arc(0,0,radius*0.015,0,2*Math.PI);
	ctx.fill();
}

//每1秒更新一次畫布
setInterval(draw,1000);