function Brick() {
    this.node = document.createElement('div');
    this.node.state = randint(1, 5);
    this.node.className = 'brick';
    this.node.style.width = '100px';
    this.node.style.height = '30px';
    this.node.style.backgroundColor = ['#F6CECE', '#F78181', '#FE2E2E', '#DF0101', '#8A0808'][this.node.state-1];
}

function paddle() {
    // this.node.offset = {x:randint(5, 5), y:randint(5, 5)};
    this.node = document.createElement('div');
    this.node.className = 'paddle';
    this.node.style.width = '120px';
    this.node.style.height = '10px';
    this.node.style.backgroundColor = '#D6EAF8';
    this.node.style.top = '551px';
    this.node.style.left = '441px';
}

function ball() {
    this.radius = 10;
    this.node = document.createElement('div');
    this.node.offset = {x:2, y:-2};
    this.node.className = 'ball';
    this.node.style.width = 2*this.radius + 'px';
    this.node.style.height = 2*this.radius + 'px';
    this.node.style.backgroundColor = '#F39C12';
    this.node.style.top = 521 + 'px';
    this.node.style.left = 491 + 'px';
    this.node.score = 0;
}

ball.prototype.move = function(paddle, bricks) {
    let y = parseInt(this.node.style.top);
    let x = parseInt(this.node.style.left);
    let xc = x + this.radius;
    let yc = y + this.radius;
    let py = parseInt(paddle.node.style.top);
    let px = parseInt(paddle.node.style.left);
    let pw = parseInt(paddle.node.style.width);
    if (y >= 580) {
    	this.node.offset.x = 0;
    	this.node.offset.y = 0;
    }
    else if (x+this.radius >= px && x+this.radius <= px+pw && y+2*this.radius >= py && y+2*this.radius <= py+5) this.node.offset.y = -(Math.sign(this.node.offset.y)*randint(2, 2));
    else if (y <= 0) this.node.offset.y = -(Math.sign(this.node.offset.y)*randint(2, 2));
    else if (x+2*this.radius >= 1000 || x <= 0) this.node.offset.x = -(Math.sign(this.node.offset.x)*randint(2, 2));
    for (let i = 0; i < bricks.length; i++) {
    	let by = parseInt(bricks[i].node.style.top);
    	let bx = parseInt(bricks[i].node.style.left);
    	let bw = parseInt(bricks[i].node.style.width);
    	let bh = parseInt(bricks[i].node.style.height);
    	let distance;
    	if (xc <= bx && yc > by && yc <= by+bh) {  
    		distance = bx - xc;
    		if (distance <= 10) {
    			if (bricks[i].node.state > 0) {
    				this.node.offset.x = -(Math.sign(this.node.offset.x)*randint(2, 2));
    				bricks[i].node.state--;
    				this.node.score++;
    			}
    			if (bricks[i].node.state == 0) bricks[i].node.style.display = 'none';
    			else bricks[i].node.style.backgroundColor = ['#F6CECE', '#F78181', '#FE2E2E', '#DF0101', '#8A0808'][bricks[i].node.state-1];
    		}
    	} 
    	else if (xc <= bx && y > by+bh) {
    		distance = Math.sqrt(Math.pow(xc - bx) + Math.pow(yc - (by+bh)));
    		if (distance <= 10) {
    			if (bricks[i].node.state > 0) {
    				this.node.offset.x = -(Math.sign(this.node.offset.x)*randint(2, 2));
    				this.node.offset.y = -(Math.sign(this.node.offset.y)*randint(2, 2));
    				bricks[i].node.state--;
    				this.node.score++;
    			}
    			if (bricks[i].node.state == 0) bricks[i].node.style.display = 'none';
    			else bricks[i].node.style.backgroundColor = ['#F6CECE', '#F78181', '#FE2E2E', '#DF0101', '#8A0808'][bricks[i].node.state-1];
    		}
    	}
    	else if (xc > bx && xc <= bx+bw && yc > by+bh) {
    		distance = yc - (by+bh);
    		if (distance <= 10 && bricks[i].node.state > 0) {
    			if (bricks[i].node.state > 0) {
    				this.node.offset.y = -(Math.sign(this.node.offset.y)*randint(2, 2));
    				bricks[i].node.state--;
    				this.node.score++;
    			}
    			if (bricks[i].node.state == 0) bricks[i].node.style.display = 'none';
    			else bricks[i].node.style.backgroundColor = ['#F6CECE', '#F78181', '#FE2E2E', '#DF0101', '#8A0808'][bricks[i].node.state-1];
    		}
    	}
    	else if (xc > bx+bw && yc > by+bh) {
    		distance = Math.sqrt(Math.pow(xc - (bx+bw)) + Math.pow(yc - (by+bh)));
    		if (distance <= 10 && bricks[i].node.state > 0) {
    			if (bricks[i].node.state > 0) {
    				this.node.offset.x = -(Math.sign(this.node.offset.x)*randint(2, 2));
    				this.node.offset.y = -(Math.sign(this.node.offset.y)*randint(2, 2));
    				bricks[i].node.state--;
    				this.node.score++;
    			}
    			if (bricks[i].node.state == 0) bricks[i].node.style.display = 'none';
    			else bricks[i].node.style.backgroundColor = ['#F6CECE', '#F78181', '#FE2E2E', '#DF0101', '#8A0808'][bricks[i].node.state-1];
    		}
    	}
    	else if (xc > bx+bw && yc > by && yc <= by+bh) {
    		distance = xc - (bx+bw);
    		if (distance <= 10 && bricks[i].node.state > 0) {
    			if (bricks[i].node.state > 0) {
    				this.node.offset.x = -(Math.sign(this.node.offset.x)*randint(2, 2));
    				bricks[i].node.state--;
    				this.node.score++;
    			}
    			if (bricks[i].node.state == 0) bricks[i].node.style.display = 'none';
    			else bricks[i].node.style.backgroundColor = ['#F6CECE', '#F78181', '#FE2E2E', '#DF0101', '#8A0808'][bricks[i].node.state-1];
    		}
    	}
    	else if (xc > bx+bw && yc <= by) { 
    		distance = Math.sqrt(Math.pow(xc - (bx+bw)) + Math.pow(yc - by));
    		if (distance <= 10 && bricks[i].node.state > 0) {
    			if (bricks[i].node.state > 0) {
    				this.node.offset.x = -(Math.sign(this.node.offset.x)*randint(2, 2));
    				this.node.offset.y = -(Math.sign(this.node.offset.y)*randint(2, 2));
    				bricks[i].node.state--;
    				this.node.score++;
    			}
    			if (bricks[i].node.state == 0) bricks[i].node.style.display = 'none';
    			else bricks[i].node.style.backgroundColor = ['#F6CECE', '#F78181', '#FE2E2E', '#DF0101', '#8A0808'][bricks[i].node.state-1];
    		}
    	}
    	else if (xc > bx && xc <= bx+bw && yc <= by) {
    		distance = by - yc;
    		if (distance <= 10 && bricks[i].node.state > 0) {
    			if (bricks[i].node.state > 0) {
    				this.node.offset.y = -(Math.sign(this.node.offset.y)*randint(2, 2));
    				bricks[i].node.state--;
    				this.node.score++;
    			}
				if (bricks[i].node.state == 0) bricks[i].node.style.display = 'none';
    			else bricks[i].node.style.backgroundColor = ['#F6CECE', '#F78181', '#FE2E2E', '#DF0101', '#8A0808'][bricks[i].node.state-1];    		}
    	}
    	else if (xc <= bx && yc <= by) {
    		distance = Math.sqrt(Math.pow(xc - bx) + Math.pow(yc - by));
    		if (distance <= 10 && bricks[i].node.state > 0) {
    			if (bricks[i].node.state > 0) {
    				this.node.offset.x = -(Math.sign(this.node.offset.x)*randint(2, 2));
    				this.node.offset.y = -(Math.sign(this.node.offset.y)*randint(2, 2));
    				bricks[i].node.state--;
    				this.node.score++;
    			}
    			if (bricks[i].node.state == 0) bricks[i].node.style.display = 'none';
    			else bricks[i].node.style.backgroundColor = ['#F6CECE', '#F78181', '#FE2E2E', '#DF0101', '#8A0808'][bricks[i].node.state-1];
    		}
    	}
    	// if (this.node.score > 0) document.write('111');
    }
    this.node.style.top = Math.max(0, Math.min(600-2*this.radius, y+this.node.offset.y)) + 'px';
    this.node.style.left = Math.max(0, Math.min(1000-2*this.radius, x+this.node.offset.x)) + 'px';
}

function randint(start, end) {
    return Math.floor(Math.random() * (end-start+1) + start);
}

function click2start() {
    var x = document.getElementById("startClick");
    x.style.display = "none";
    var x = document.getElementById("container");
    x.style.display = "block";
	var balls = [];
	var score;
//window.addEventListener('click', function(e) {
	var container = document.getElementById('container');
	while (container.lastElementChild) {
    	container.removeChild(container.lastElementChild);
  	}
	const ball_num = 1;
	balls[0] = new ball();
	container.appendChild(balls[0].node);
	var paddles = [];
	paddles[0] = new paddle();
	container.appendChild(paddles[0].node);
	var bricks = [];
	for (let i = 0; i < 18; i++) {
		bricks[i] = new Brick();
		container.appendChild(bricks[i].node);
		bricks[i].node.style.left = 100 + (i%6)*140 + 'px';
		bricks[i].node.style.top = 50 + Math.floor(i/6)*50 + 'px';
		// bricks[i].node.style.left = 200 + 'px';
		// bricks[i].node.style.top = 500 + 'px';
	}
	var id = setInterval(function() {
	    balls[0].move(paddles[0], bricks);
	    //if (balls[0].node.score > 0) document.write('111');
	    let flag = 1;
	    for (let i = 0; i < 18; i++) {
	    	if (bricks[i].node.state > 0) flag = 0;
	    }
	    if (balls[0].node.offset.x == 0 && balls[0].node.offset.y == 0 && !flag) {
	    	var x = document.getElementById("gameover");
	    	x.style.display = 'block';
	    	clearInterval(id);
	    }
	    else {
	    	var x = document.getElementById("gameover");
	    	x.style.display = 'none';
	    }
	    if (flag) {
	    	var x = document.getElementById("youwin");
	    	x.style.display = 'block';
	    	balls[0].node.offset.x = 0;
	    	balls[0].node.offset.y = 0;
	    	balls[0].node.style.display = 'none';
	    	paddles[0].node.style.display = 'none';
	    	clearInterval(id);
	    }
	    else {
	    	var x = document.getElementById("youwin");
	    	x.style.display = 'none';
	    }
	    var canvas = document.getElementById("score");
		var ctx = canvas.getContext("2d");
		canvas.height = canvas.height;
		ctx.font = "32px Arial";
  		ctx.fillStyle = '#D6EAF8';
  		ctx.fillText("Score: " + balls[0].node.score, 20, 40);
	    ctx.font = "32px Arial";
  		ctx.fillStyle = "#273746";
  		ctx.fillText("Score: " + balls[0].node.score, 20, 40);
	}, 1);

	//setTimeout(clearInterval, 100000, id);

	//window.addEventListener

	container.addEventListener('mousemove', function(e) {
		//e = e || window.event;
		let flag = 1;
	    for (let i = 0; i < 18; i++) {
	    	if (bricks[i].node.state > 0) flag = 0;
	    }
	    for (let i = 0; i < 1; i++) {
	    	if (balls[0].node.offset.x != 0 && balls[0].node.offset.y != 0 || flag) paddles[i].node.style.left = Math.max(0, Math.min(881, e.offsetX-60)) + 'px';
	    }
	});

	document.body.addEventListener('keydown', function(e) {
		e = e || window.event;
		let flag = 1;
	    for (let i = 0; i < 18; i++) {
	    	if (bricks[i].node.state > 0) flag = 0;
	    }
		if (balls[0].node.offset.x != 0 && balls[0].node.offset.y != 0 || flag) {
			switch (e.key) {
				case 'ArrowLeft':
					paddles[0].node.style.left = Math.max(0, Math.min(881, parseInt(paddles[0].node.style.left)-64)) + 'px';
					break;
				case 'ArrowRight':
					paddles[0].node.style.left = Math.max(0, Math.min(881, parseInt(paddles[0].node.style.left)+64)) + 'px';
					break;
			}
		}
	});
//});
}

// function click2start() {
//     var x = document.getElementById("startClick");
//     x.style.display = "none";
// }

function gameOver() {
	var x = document.getElementById("gameover");
    //x.style.display = "none";
    if (balls[0].node.offset.x == 0 && balls[0].node.offset.y == 0) document.write('111');
    x.style.display = 'block';
}