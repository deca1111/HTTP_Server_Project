var dimension = [document.documentElement.clientWidth, document.documentElement.clientHeight];
var canvas = document.getElementById("myCanvas");
canvas.width = dimension[0];
canvas.height = dimension[1];
var ctx = canvas.getContext("2d");
var x = canvas.width/2;
var y = canvas.height-30;
var dx = 2;
var dy = -2;

var ballRadius = 15;
var couleurs = ["#8E44AD","#3498DB","#229954","#34495E","#E74C3C"];
var index_c = 0;
var couleur = couleurs[index_c];

function drawBall() {
    ctx.beginPath();
    ctx.arc(x, y, ballRadius, 0, Math.PI*2);
    ctx.fillStyle = couleur;
    ctx.fill();
    ctx.closePath();
}

function draw() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    drawBall();

    if(x + dx > canvas.width-ballRadius || x + dx < ballRadius) {
        dx = -dx;
				index_c = (index_c + 1 )%5;
				couleur = couleurs[index_c];
    }
    if(y + dy > canvas.height-ballRadius || y + dy < ballRadius) {
        dy = -dy;
				index_c = (index_c + 1 )%5;
				couleur = couleurs[index_c];
    }

    x += dx;
    y += dy;
}

setInterval(draw, 10);
