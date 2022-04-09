var dimension = [document.documentElement.clientWidth, document.documentElement.clientHeight];
var canvas = document.getElementById("myCanvas");
canvas.width = dimension[0]-3;
canvas.height = dimension[1]-3;
var ctx = canvas.getContext("2d");

var x = canvas.width/3 + (Math.random()*canvas.width/3);
var y = canvas.height/3 + (Math.random()*2*canvas.height/4);
var dx = 2;
var dy = -2;

var ballRadius = 15;
var couleur = '#'+(Math.random()*0xFFFFFF<<0).toString(16);

var paddleHeight = 20;
var paddleWidth = canvas.width/7;
var paddleX = (canvas.width-paddleWidth) / 2;

var rightPressed = false;
var leftPressed = false;

var brickRowCount = 4;
var brickColumnCount = 6;
var brickWidth = canvas.width/7;
var brickHeight = canvas.height/17	;
var brickPadding = 15;
var brickOffsetTop = 30;
var brickPoint = 5;

var bricks = [];
for(var c=0; c<brickColumnCount; c++) {
    bricks[c] = [];
    for(var r=0; r<brickRowCount; r++) {
        bricks[c][r] = { x: 0, y: 0, status: 1 };
    }
}

var score = 0;


document.addEventListener("keydown", keyDownHandler, false);
document.addEventListener("keyup", keyUpHandler, false);
document.addEventListener("mousemove", mouseMoveHandler, false);

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

function mouseMoveHandler(e) {
    var relativeX = e.clientX - canvas.offsetLeft;
    if(relativeX > 0 && relativeX < canvas.width) {
        paddleX = relativeX - paddleWidth/2;
    }
}

function collisionDetection() {
    for(var c=0; c<brickColumnCount; c++) {
        for(var r=0; r<brickRowCount; r++) {
            var b = bricks[c][r];
            if(b.status == 1) {
                if(x+ballRadius > b.x && x-ballRadius < b.x+brickWidth && y+ballRadius > b.y && y-ballRadius < b.y+brickHeight) {
                    dy = -dy;
										updateColor();
                    b.status = 0;
										score+=brickPoint;
										if(score == brickRowCount*brickColumnCount*brickPoint) {
                        alert("YOU WIN, CONGRATULATIONS!");
                        document.location.reload();
                        clearInterval(interval);
                    }
                }
            }
        }
    }
}

function drawScore() {
    ctx.font = "16px Arial";
    ctx.fillStyle = "#8E44AD";
    ctx.fillText("Score: "+score, 8, 20);
}

function drawBall() {
    ctx.beginPath();
    ctx.arc(x, y, ballRadius, 0, Math.PI*2);
    ctx.fillStyle = couleur;
    ctx.fill();
    ctx.closePath();
}

function drawBricks() {
    for(var c=0; c<brickColumnCount; c++) {
        for(var r=0; r<brickRowCount; r++) {
            if(bricks[c][r].status == 1) {
                var brickX = (c*(brickWidth+brickPadding))+ (canvas.width - brickColumnCount*(brickWidth+brickPadding))/2 ;
                var brickY = (r*(brickHeight+brickPadding))+brickOffsetTop;
                bricks[c][r].x = brickX;
                bricks[c][r].y = brickY;
                ctx.beginPath();
                ctx.rect(brickX, brickY, brickWidth, brickHeight);
                ctx.fillStyle = "#8E44AD";
                ctx.fill();
                ctx.closePath();
            }
        }
    }
}

function drawPaddle() {
		if (paddleX + paddleWidth > canvas.width) {
			paddleX = canvas.width - paddleWidth;
		}
		if (paddleX < 0) {
			paddleX = 0;
		}
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
    drawBricks();
    drawBall();
    drawPaddle();
		drawScore();
    collisionDetection();


    if(x + dx > canvas.width-ballRadius || x + dx < ballRadius) {
        dx = -dx;
				updateColor()
    }
		if(y + dy < ballRadius) {
		    dy = -dy;
				updateColor()
		} else if(y > canvas.height- ballRadius) {
      alert("GAME OVER\nScore :"+ score);
      document.location.reload();
      clearInterval(interval);
		} else if(y < canvas.height-2*paddleHeight-ballRadius && x > paddleX-10 && x < paddleX + paddleWidth +10 && y+dy > canvas.height-2*paddleHeight-ballRadius) {
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
