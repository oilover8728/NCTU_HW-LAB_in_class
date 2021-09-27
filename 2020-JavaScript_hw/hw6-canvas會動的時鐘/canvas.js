/*
//畫線段
ctx.strokeStyle = 'green';
ctx.moveTo(50,20);
ctx.lineTo(250,120);
ctx.stroke();

ctx.beginPath();	//居別不銅線段的屬性
ctx.strokeStyle = 'red';
ctx.moveTo(250,20);
ctx.lineTo(50,120);
ctx.stroke();
*/

/*
//畫長方形
ctx.fillStyle = 'green';
ctx.fillRect(50,20,200,100);
*/

/*
//畫圓弧 arc(x,y,r,startangle,endangle) x y 指圓心
ctx.beginPath();
ctx.arc(95, 50, 40, 0, 2 * Math.PI);
ctx.stroke();
*/

/*
//畫漸層
//Create gradient
var grd = ctx.createLinearGradient(0,0,200,0);
grd.addColorStop(0, "red");
grd.addColorStop(1, "white");

//Fill with gradient
ctx.fillStyle = grd;
ctx.fillRect(10,10,150,80);
*/

/*
//畫漸層 輻射狀
//Create gradient
var grd = ctx.createRadialGradient(75, 50, 5, 90, 60, 100);
grd.addColorStop(0, "red");
grd.addColorStop(1, "white");

//Fill with gradient
ctx.fillStyle = grd;
ctx.fillRect(10,10,150,80);
*/

/*
//畫實心文字
ctx.beginPath();
ctx.font="30px Arial";
ctx.fillText("Hello World", 10, 50);
//畫空心文字
ctx.textAlign = "center";
ctx.strokeText("Hello World", 300, 50);
*/

/*
//畫圖
window.onload = function(){
	var img = document.getElementById("screm");
	ctx.drawImage(img,10,10);
}
*/