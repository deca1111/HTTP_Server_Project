var dimension = [document.documentElement.clientWidth, document.documentElement.clientHeight];
var canvas = document.getElementById("myCanvas");
canvas.width = dimension[0];
canvas.height = dimension[1];
var ctx = canvas.getContext("2d");
var x = canvas.width/2;
var y = canvas.height/3;
var dx = 2;
var dy = -2;

var ballRadius = 15;
var couleur = '#'+(Math.random()*0xFFFFFF<<0).toString(16);

var paddleHeight = 20;
var paddleWidth = canvas.width/7;
var paddleX = (canvas.width-paddleWidth) / 2;

var rightPressed = false;
var leftPressed = false;

document.addEventListener("keydown", keyDownHandler, false);
document.addEventListener("keyup", keyUpHandler, false);

function keyDownHandler(e) {
    if(e.key == "Right" || e.key == "ArrowRight") {
        rightPressed = true;
    }
    else if(e.key == "Left" || e.key == "ArrowLeft") {
        leftPressed = true;
    }
}

function keyUpHandler(e) {
    if(e.key == "Right" || e.key == "ArrowRight") {
        rightPressed = false;
    }
    else if(e.key == "Left" || e.key == "ArrowLeft") {
        leftPressed = false;
    }
}

function drawBall() {
    ctx.beginPath();
    ctx.arc(x, y, ballRadius, 0, Math.PI*2);
    ctx.fillStyle = couleur;
    ctx.fill();
    ctx.closePath();
}

function drawPaddle() {
    ctx.beginPath();
    ctx.rect(paddleX, canvas.height-2*paddleHeight, paddleWidth, paddleHeight);
    ctx.fillStyle = "#8E44AD";
    ctx.fill();
    ctx.closePath();
}

function updateColor(){
	couleur = '#'+(Math.random()*0xFFFFFF<<0).toString(16);
}

function draw() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    drawBall();
		drawPaddle();

    if(x + dx > canvas.width-ballRadius || x + dx < ballRadius) {
        dx = -dx;
				updateColor()
    }
		if(y + dy < ballRadius) {
		    dy = -dy;
				updateColor()
		} else if(y > canvas.height- ballRadius) {
      alert("GAME OVER");
      document.location.reload();
      clearInterval(interval);
		} else if(y > canvas.height-2*paddleHeight-ballRadius && x > paddleX && x < paddleX + paddleWidth) {
			dy = -dy;
			updateColor()
		}

		if(rightPressed) {
        paddleX += 7;
        if (paddleX + paddleWidth > canvas.width){
            paddleX = canvas.width - paddleWidth;
        }
    }
    else if(leftPressed) {
        paddleX -= 7;
        if (paddleX < 0){
            paddleX = 0;
        }
    }

    x += dx;
    y += dy;
}

var interval = setInterval(draw, 10);
