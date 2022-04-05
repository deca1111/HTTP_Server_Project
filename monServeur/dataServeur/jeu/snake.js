let ecran = {width:1280,height:720};
let diff = 10;
let snakes=[],fruits=[];
let scoreDiv;
let createFruit = function(iOptions){
 this.draw = function(){
  stroke(this.couleur.rouge,this.couleur.vert,this.couleur.bleu);
  point(this.position.x, this.position.y);
 };
 this.updatePosition = function(iPosition){
  if(iPosition === undefined)
      iPosition = {x:floor(random(10, (ecran.width - 10) / 10))*10,y:floor(random(10, (ecran.height - 10) / 10)) * 10}   
     this.position = iPosition;
 };
 this.updatePosition(iOptions.position);
 this.couleur = iOptions.couleur; 
 return this;
};

let createSnake = function(iOptions){
 this.control = function(keyCode){
   switch (keyCode) {
  case iOptions.controler.left:
    if (this.direction !== 'right') {
   this.direction = 'left';
    }
    break;
  case iOptions.controler.right:
    if (this.direction !== 'left') {
   this.direction = 'right';
    }
    break;
  case iOptions.controler.up:
    if (this.direction !== 'down') {
   this.direction = 'up';
    }
    break;
  case iOptions.controler.down:
    if (this.direction !== 'up') {
   this.direction = 'down';
    }
    break;
   }  
 };
 this.draw = function(){
  stroke(this.couleur.rouge,this.couleur.vert,this.couleur.bleu);
  let numSegments=this.positionSnake.length;
  for (let i = 0; i <  numSegments - 1; i++) {
   this.positionSnake[i].x = this.positionSnake[i + 1].x;  
   this.positionSnake[i].y = this.positionSnake[i + 1].y; 
  }   
  var tete = this.tete();
  switch (this.direction) {
   case 'right':
    tete.x = this.positionSnake[numSegments - 2].x + diff;
    tete.y = this.positionSnake[numSegments - 2].y;
    break;
   case 'up':
    tete.x = this.positionSnake[numSegments - 2].x;
    tete.y = this.positionSnake[numSegments - 2].y - diff;
    break;
   case 'left':
    tete.x = this.positionSnake[numSegments - 2].x - diff;
    tete.y = this.positionSnake[numSegments - 2].y;
    break;
   case 'down':
    tete.x = this.positionSnake[numSegments - 2].x;
    tete.y = this.positionSnake[numSegments - 2].y + diff;
    break;
  }  
  for (let i = 0; i < this.positionSnake.length - 1; i++) {
   let positionCourante = this.positionSnake[i],
    positionSuivante = this.positionSnake[i + 1]; 
   line(positionCourante.x, positionCourante.y, positionSuivante.x, positionSuivante.y);
  }
 };
 this.tete=function(){
  return this.positionSnake[this.positionSnake.length-1];
 };
 this.update = function(iFruit,snakes){
  let checkSnakeCollision=false,
   teteSnake = this.tete();

    if(teteSnake.x > ecran.width || teteSnake.x < 0 || teteSnake.y > ecran.height || teteSnake.y < 0) 
   checkSnakeCollision=true;
  else {
   for (let i = 0; i < this.positionSnake.length - 1; i++) {
    if (this.positionSnake[i].x === teteSnake.x && this.positionSnake[i].y === teteSnake.y) {
     checkSnakeCollision=true;
    }
   }
  }
  snakes.forEach(function(unSnake){
   if(unSnake!==this){
    for (let i = 0; i < unSnake.positionSnake.length; i++) {
     if (unSnake.positionSnake[i].x === teteSnake.x && unSnake.positionSnake[i].y === teteSnake.y) {
      checkSnakeCollision=true;
     }
    } 
   }
  },this);
    if(checkSnakeCollision) {
   noLoop();
   scoreDiv.html(scoreDiv.html()+'<br> '+this.name+' a perdu');
  }  

  if (teteSnake.x === iFruit.position.x && teteSnake.y === iFruit.position.y) {
   this.score++;
   this.positionSnake.unshift({x:this.positionSnake[0].x,y:this.positionSnake[0].y});
   iFruit.updatePosition();
  } 
 };
 let numSegments = iOptions.taille || 5;
 this.positionSnake=[]
 this.couleur=iOptions.couleur;
 this.score=0;
 for (let i = 0; i < numSegments; i++) {
  this.positionSnake.push({x:iOptions.x + i * diff,
        y:iOptions.y});
 }
 this.direction = 'right'
 this.name=iOptions.name;
 return this;
}

function setup() {
  scoreDiv = createDiv('');
  scoreDiv.position(20, 20);
  scoreDiv.id = 'score';
  scoreDiv.style('color', 'yellow');

  createCanvas(ecran.width, ecran.height);
  frameRate(15);
  strokeWeight(10);
  snakes.push(new createSnake({x:0,y:100,
 couleur:{rouge:random(30, 255),
 vert:random(30, 255),
 bleu:random(30, 255)
  },controler:{left:37,
right:39,
up:38,
down:40},name:'joueur '+(snakes.length+1)}));
  snakes.push(new createSnake({x:0,y:400,
 couleur:{rouge:random(30, 255),
 vert:random(30, 255),
 bleu:random(30, 255)
  },controler:{left:81,
right:68,
up:90,
down:83},name:'joueur '+(snakes.length+1)}));
  fruits.push(new createFruit({
 couleur:{rouge:random(30, 255),
 vert:random(30, 255),
 bleu:random(30, 255)
  }
  }));
  fruits.push(new createFruit({
 couleur:{rouge:random(30, 255),
 vert:random(30, 255),
 bleu:random(30, 255)
  }
  })); 
}

function draw() {
 var joueur = 1, html = ''
 background(0);
 snakes.forEach(function(snake){
  html += snake.name + ' : ' + snake.score+'<br>';
  snake.draw();
 });
 scoreDiv.html(html);
 
 fruits.forEach(function(fruit){
  fruit.draw();
  snakes.forEach(function(snake){
   snake.update(fruit,snakes);
  });
 });  
}

function keyPressed() {
 snakes.forEach(function(snake){
  snake.control(keyCode);
 });
}
