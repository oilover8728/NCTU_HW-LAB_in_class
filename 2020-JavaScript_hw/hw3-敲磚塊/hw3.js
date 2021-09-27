function Paddle(){
	this.node = document.createElement("div");
	this.node.className = "paddle"
	this.node.style.width = "100px";
	this.node.style.height = "10px";
	this.node.style.backgroundColor = "white";
	this.node.style.top = "589px";
	this.node.style.left = "351px";
}

/*Paddle.prototype.move = function () {
	let x = parseInt(this.node.style.left);
	let y = parseInt(this.node.style.top);
	this.node.style.left =  Math.max(0,Math.min(701,x+this.offset.x))+"px";	
}*/


function Ball(){
	this.radius = 10;
	this.offset = {x:2, y:-2};	//球在x y軸上的速度 是一個物件
	this.node = document.createElement("div");
	this.node.className = "ball"
	this.node.style.width = 2 * this.radius + "px";
	this.node.style.height = 2 * this.radius + "px";
	this.node.style.backgroundColor = "orange";
	this.node.style.top = 521 + 'px';
    this.node.style.left = 401 + 'px';
	this.node.score = 0;
}

function Brick(){
	this.node = document.createElement("div");
	this.node.state = randint(1, 5);
	this.node.className = "brick"
	this.node.style.width = "100px";
	this.node.style.height = "20px";
	this.node.alive = true;
	//this.node.style.backgroundColor = ['#F6CECE', '#F78181', '#FE2E2E', '#DF0101', '#8A0808'][this.node.state-1];
	this.node.style.backgroundColor = ["red","yellow","green","blue","purple"][this.node.state-1];
	
}

var gameover=0;
Ball.prototype.move = function (paddle,bricks) {
	let x = parseInt(this.node.style.left);
	let y = parseInt(this.node.style.top);
	let py = parseInt(paddle.node.style.top);
	let px = parseInt(paddle.node.style.left);
	let pw = parseInt(paddle.node.style.width);
	
	let x_zone = x + 2*this.radius;
	let y_zone = y + 2*this.radius;
	//Game over
	if (y_zone >= 600 && gameover==0) {
    	this.offset.x = 0;
    	this.offset.y = 0;
		gameover=1;
    }
    else if (x+this.radius>=px && x <= px+pw && y_zone>= py) this.offset.y = -(Math.sign(this.offset.y)*randint(2, 3));//撞到棒子
    else if (y <= 1) this.offset.y = -(Math.sign(this.offset.y)*randint(2, 3));//撞到上邊界
	else if (x_zone >= 799 || x <= 1) this.offset.x = -(Math.sign(this.offset.x)*randint(2, 3));//撞到左右邊界
	//brick collision
	var live_number=0;
	for (let i = 0; i < bricks.length; i++) {
		if(bricks[i].node.alive){
			live_number++;
		}
    	let by = parseInt(bricks[i].node.style.top);
    	let bx = parseInt(bricks[i].node.style.left);
    	let bw = parseInt(bricks[i].node.style.width);
    	let bh = parseInt(bricks[i].node.style.height);
		let distance;
		//撞到磚塊左邊
		if(x_zone == bx && y_zone >= by && y <= by+bh){
			distance = bx - x_zone;
			if(distance <=10 && bricks[i].node.alive){
				console.log("left");
				this.node.score++;
				this.offset.x = -(Math.sign(this.offset.x)*randint(2, 3));
				if (bricks[i].node.state == 1) {
					bricks[i].node.style.display = 'none';
					bricks[i].node.alive=false;
				}
				else{
					bricks[i].node.state = bricks[i].node.state -1 ;
					bricks[i].node.style.backgroundColor = ["red","yellow","green","blue","purple"][bricks[i].node.state-1];
				}
			}
		}
		else if(x_zone >= bx && x <= bx+bw && y <= by+bh){//撞到磚塊下面
			distance = y - by - bh;
			if(distance <=10 && bricks[i].node.alive){
				console.log("down");
				this.node.score++;
				this.offset.x = -(Math.sign(this.offset.x)*randint(2, 3));
				this.offset.y = -(Math.sign(this.offset.y)*randint(2, 3));
				if (bricks[i].node.state == 1) {
					bricks[i].node.style.display = 'none';
					bricks[i].node.alive=false;
				}
				else{
					bricks[i].node.state = bricks[i].node.state -1 ;
					bricks[i].node.style.backgroundColor = ["red","yellow","green","blue","purple"][bricks[i].node.state-1];
				}
			}
		}
		else if (x == bx + bw && y_zone >= by && y_zone <= by+bh){//撞到磚塊右邊
			distance = x_zone - bx -bw;
			if(distance <= 10 && bricks[i].node.alive){
				console.log("right");
				this.node.score++;
				this.offset.x = -(Math.sign(this.offset.x)*randint(2, 3));
				if (bricks[i].node.state == 1) {
					bricks[i].node.style.display = 'none';
					bricks[i].node.alive=false;
				}
				else{
					bricks[i].node.state = bricks[i].node.state -1 ;
					bricks[i].node.style.backgroundColor = ["red","yellow","green","blue","purple"][bricks[i].node.state-1];
				}
			}
		}
		else if (x_zone > bx && x <= bx + bw && y_zone <= by){//撞到磚塊上面
			distance = by-y_zone;
			if(distance <= 10 && bricks[i].node.alive){
				console.log("up");
				this.node.score++;
				this.offset.y = -(Math.sign(this.offset.y)*randint(2, 3));
				if (bricks[i].node.state == 1) {
					bricks[i].node.style.display = 'none';
					bricks[i].node.alive=false;
				}
				else{
					bricks[i].node.state = bricks[i].node.state -1 ;
					bricks[i].node.style.backgroundColor = ["red","yellow","green","blue","purple"][bricks[i].node.state-1];
				}
			}
		}
		else if(x_zone <= bx && y > by+bh){
			distance = Math.sqrt(Math.pow(x_zone - bx) + Math.pow(y_zone - (by+bh)));
			if(distance <=10 && bricks[i].node.alive){
				console.log("5");
				this.node.score++;
				this.offset.x = -(Math.sign(this.offset.x)*randint(2, 3));
    			this.offset.y = -(Math.sign(this.offset.y)*randint(2, 3));
				if (bricks[i].node.state == 1) {
					bricks[i].node.style.display = 'none';
					bricks[i].node.alive=false;
				}
				else{
					bricks[i].node.state = bricks[i].node.state -1 ;
					bricks[i].node.style.backgroundColor = ["red","yellow","green","blue","purple"][bricks[i].node.state-1];
				}
			}
		}
		else if (x_zone > bx + bw && y_zone > by + bh){
			distance = Math.sqrt(Math.pow(x_zone-bx-bw)+Math.pow(y_zone-by-bh));
			if(distance <= 10 && bricks[i].node.alive){
				console.log("6");
				this.node.score++;
				this.offset.x = -(Math.sign(this.offset.x)*randint(2, 3));
    			this.offset.y = -(Math.sign(this.offset.y)*randint(2, 3));
				if (bricks[i].node.state == 1) {
					bricks[i].node.style.display = 'none';
					bricks[i].node.alive=false;
				}
				else{
					bricks[i].node.state = bricks[i].node.state -1 ;
					bricks[i].node.style.backgroundColor = ["red","yellow","green","blue","purple"][bricks[i].node.state-1];
				}
			}
		}
		else if (x_zone > bx+bw && y_zone <= by){
			distance = Math.sqrt(Math.pow(x_zone-bx-bw)+Math.pow(y_zone-by));
			if(distance <= 10 && bricks[i].node.alive){
				console.log("7");
				this.node.score++;
				this.offset.x = -(Math.sign(this.offset.x)*randint(2, 3));
    			this.offset.y = -(Math.sign(this.offset.y)*randint(2, 3));
				if (bricks[i].node.state == 1) {
					bricks[i].node.style.display = 'none';
					bricks[i].node.alive=false;
				}
				else{
					bricks[i].node.state = bricks[i].node.state -1 ;
					bricks[i].node.style.backgroundColor = ["red","yellow","green","blue","purple"][bricks[i].node.state-1];
				}
			}
		}
		else if(x_zone <= bx && y_zone <= by){
			distance = Math.sqrt(Math.pow(x_zone - bx) + Math.pow(y_zone - by));
			if(distance <= 10 && bricks[i].node.alive){
				console.log("8");
				this.node.score++;
				this.offset.x = -(Math.sign(this.offset.x)*randint(2, 3));
    			this.offset.y = -(Math.sign(this.offset.y)*randint(2, 3));
				if (bricks[i].node.state == 1) {
					bricks[i].node.style.display = 'none';
					bricks[i].node.alive=false;
				}
				else{
					bricks[i].node.state = bricks[i].node.state -1 ;
					bricks[i].node.style.backgroundColor = ["red","yellow","green","blue","purple"][bricks[i].node.state-1];
				}
			}
		}
		
	}
	if(live_number==0){
		gameover=1;
	}
	if(gameover==1){
		alert("Score: "+this.node.score+"   "+"Game Over! Press F5 to reset the game");
		gameover=2;
	}
	document.getElementById("score").font_ = "32px";
	document.getElementById("score").textContent = ("Score: "+this.node.score);
	this.node.style.top =  y + this.offset.y + "px";
	this.node.style.left =  x + this.offset.x + "px";	
	
	for (let i = 0; i < bricks.length; i++) {
		let by = parseInt(bricks[i].node.style.top);
    	let bx = parseInt(bricks[i].node.style.left);
    	let bw = parseInt(bricks[i].node.style.width);
    	let bh = parseInt(bricks[i].node.style.height);
	}
}

function randint(start, end) {
    return Math.floor(Math.random() * (end-start+1) + start);
}
/*function randint(start,end){
		var number= Math.floor(Math.random()*(end-start+1))+start;
		while ( Math.abs(number) < 5 ){ //產生一個大於5的亂數
			number = Math.floor(Math.random()*(end-start+1))+start;
		}
		return number;
}*/

function GameStart() {
	document.getElementById("btn1").style.display='none';
//window.addEventListener("load",function() {
	const Ball_Number = 1;
	var containter = document.getElementById("container");
	var aBall = [];
	for (let i=0;i<Ball_Number; i++){
		aBall[i]= new Ball();
		container.appendChild(aBall[i].node);
	}
	var aPaddle = [];
	for (let i=0;i<1; i++){
		aPaddle[i]= new Paddle();
		container.appendChild(aPaddle[i].node);
	}
	var aBrick = [];
	for (let i=0;i<18; i++){
		aBrick[i]= new Brick();
		container.appendChild(aBrick[i].node);
		aBrick[i].node.style.left = 50+(i%6)*120+"px";
		aBrick[i].node.style.top = 30+Math.floor(i/6)*30+"px";
	}
	
	var id = setInterval(function(){
		for( let i=0;i<Ball_Number;i++){
			aBall[i].move(aPaddle[0], aBrick);
		}
	}, 10);
	
	//setTimeout(clearInterval, 10000, id);
	container.addEventListener("mousemove", function(e){	
		aPaddle[0].node.style.left = Math.max(0,Math.min(750,e.offsetX)-50)+"px";
	});
	
	document.body.addEventListener("keydown", function(e){
		e = e || window.event;
		switch(e.key){
		case "ArrowLeft":
			aPaddle[0].node.style.left = Math.max(0,parseInt(aPaddle[0].node.style.left)-50)+"px";
			break;
		case "ArrowRight":
			aPaddle[0].node.style.left = Math.min(700,parseInt(aPaddle[0].node.style.left)+50)+"px";
			break;
		}
	});
}
//});




/*var id = setInterval(frame, 10);			//100ms會跑一次frame這個函數
setTimeout( "clearInterval(id)", 10000);		//5秒後 執行clearInterval(id)	定義一個匿名函數 裡面執行clearInterval(id)
//等同setTimeout(function(){ clearInterval(id);}
//如果程式碼很長，則必須用上面這種形式^


//setTimeout ( clearInterval, 10000) 這樣只有傳 clearInterval這個函數 不會執行
//setTimeout ( clearInterval, 10000 , id) 這樣才有傳id給clearInterval用

function frame() {
	for (let i = 0; i < Ball_Number; i++){
		aBall[i].move();
	} 
}*/
