
#include "M5Cardputer.h"
#include "rocket.h"
#include "brod1.h"
#include "bulet.h"
#include "ebullet.h"
#include "life.h"
#include "rover.h"
#include "earth.h"
#include "ex.h"
#include "ex2.h"
#include "ricon.h"
#include "back2.h"
#include "sens.h"
#include "buum.h"
#include "gameOver.h"


#define TFT_GREY 0x5AEB
#define lightblue 0x2D18
#define orange 0xFB60
#define purple 0xFB9B


int brojac=0;// Invoke custom library
float buletX[10]={-20,-20,-20,-20,-20,-20,-20,-20,-20,-20};
float buletY[10]={-20,-20,-20,-20,-20,-20,-20,-20,-20,-20};

float EbuletX[10]={-20,-20,-20,-20,-20,-20,-20,-20,-20,-20};
float EbuletY[10]={-20,-20,-20,-20,-20,-20,-20,-20,-20,-20};

float rocketX[10]={-20,-20,-20,-20,-20,-20,-20,-20,-20,-20};
float rocketY[10]={-20,-20,-20,-20,-20,-20,-20,-20,-20,-20};
float rocketSpeed=0.16;
int rockets=3;

int counter=0;
int rcounter=0;
int Ecounter=0;
int level=1;
float x=10;
float y=20;

float ey=18;
float ex=170;

float es=0.1;

float bx=-50;
float by=0;

int pom=0; //pressdebounce for fire
int pom2=0; //pressdebounce for rockets
float sped=0.6;
int blinkTime=0;
int eHealth=50;
int mHealth=eHealth;
int lives=4;
int ly[4]={0,0,0,0};
int ri[3]={0,0,0};
int fireTime=100;
int fireCount=0;
float EbulletSpeed=0.22;
int rDamage=8; //rocket damage
int tr=0;

int pom3=0;
bool sound=1; //sound on or off

int fase=0; //fase 0=start screen,//fase 1=playing fase //fase 3=game over
int move=0; //0= not moving, 1 is up, 2 is down, 3 is left, 4 is right

float spaceX[30];
float spaceY[30];


void setup(void) {
  
    auto cfg = M5.config();
    M5Cardputer.begin(cfg, true);
    M5Cardputer.Display.setBrightness(70);
  M5Cardputer.Display.setRotation(1);
  M5Cardputer.Display.fillScreen(TFT_BLACK);
  M5Cardputer.Display.setSwapBytes(true);
  M5Cardputer.Display.pushImage(0, 0,  240, 135, back2);
  

  for(int i=0;i<30;i++){
    spaceX[i]=random(5,235);
    spaceY[i]=random(18,132);
  }
  
  delay(3000);
    
  }

void restart()
  {
counter=0;
rcounter=0;
Ecounter=0;
level=1;
 x=10;
 y=20;
 ey=18;
 ex=170;
 es=0.1;
 bx=-50;
 by=0;

          rockets=3;
          rDamage=8;
          lives=4;
          brojac=0;
          ri[0]=0; ri[1]=0; ri[2]=0;
          ly[0]=0; ly[1]=0; ly[2]=0; ly[3]=0;
          ey=44;
          sped=0.24;
          eHealth=50;
          mHealth=eHealth;
          EbulletSpeed=0.34;
          rocketSpeed=0.16;
          
  
  for(int i=0;i<10;i++)
  {
    buletX[i]=-20;
    EbuletX[i]=-20;
    rocketX[i]=-20;
    
  }

    
   }


   void newLevel()
{
  level++;
  sped=sped+0.03;
  EbulletSpeed=EbulletSpeed+0.1;
  eHealth=50+(level*5);
  mHealth=eHealth;
  es=0.02+(0.015*level);
 
  rockets=3;
  rDamage=8+(level*2);
  rocketSpeed=0.16+(level*0.02);
  ri[0]=0; ri[1]=0; ri[2]=0;
  
  ey=44;
  
  for(int i=0;i<10;i++)
  {
    buletX[i]=-20;
    EbuletX[i]=-20;
    rocketX[i]=-20;
    
    }

   M5Cardputer.Display.fillScreen(TFT_BLACK);
   M5Cardputer.Display.setCursor(0,0,4);
        M5Cardputer.Display.print("Level "+String(level));
        M5Cardputer.Display.setCursor(0,22,2);
        
        M5Cardputer.Display.println("Enemy speed : "+String(es));
        M5Cardputer.Display.println("Enemy health : "+String(eHealth));
        M5Cardputer.Display.println("Enemy bullet speed : "+String(EbulletSpeed));
        M5Cardputer.Display.println("Remaining lives: "+String(lives));
        M5Cardputer.Display.println("My speed : "+String(sped));
        M5Cardputer.Display.println("Rocket damage : "+String(rDamage));
        M5Cardputer.Display.println("Rocket speed : "+String(rocketSpeed));

        M5Cardputer.Display.pushImage(170, 5,  55, 54, earth[level-1]); 
        M5Cardputer.Display.pushImage(170, 61,  72, 72, sens); 
        delay(2600);
        

       delay(5000);

        M5Cardputer.Display.fillScreen(TFT_BLACK);
    
 
  M5Cardputer.Display.drawLine(0,16,240,16,lightblue);
  M5Cardputer.Display.drawLine(0,134,240,134,lightblue);

  M5Cardputer.Display.setCursor(200,0,2);
        M5Cardputer.Display.print(brojac);

         M5Cardputer.Display.fillRect(120,3,70,7,TFT_GREEN);
         M5Cardputer.Display.drawRect(119,2,72,9,TFT_GREY);
  
  }



void loop() {

  if(fase==0)
  {
    restart();
    M5Cardputer.Display.fillScreen(TFT_BLACK);
    M5Cardputer.Display.setSwapBytes(true);
    M5Cardputer.Display.pushImage(0, 0,  240, 135, back2);
   
    M5Cardputer.Display.fillScreen(TFT_BLACK);
    M5Cardputer.Display.fillScreen(TFT_BLACK);
    M5Cardputer.Display.setCursor(0,0,4);
        M5Cardputer.Display.print("Level "+String(level));
        M5Cardputer.Display.setCursor(0,22,2);
        
        M5Cardputer.Display.println("Enemy speed : "+String(es));
        M5Cardputer.Display.println("Enemy health : "+String(eHealth));
        M5Cardputer.Display.println("Enemy bullet speed : "+String(EbulletSpeed));
        M5Cardputer.Display.println("Remaining lives: "+String(lives));
        M5Cardputer.Display.println("My speed : "+String(sped));
        M5Cardputer.Display.println("Rocket damage : "+String(rDamage));
        M5Cardputer.Display.println("Rocket speed : "+String(rocketSpeed));

        M5Cardputer.Display.pushImage(170, 5,  55, 54, earth[level-1]); 
        M5Cardputer.Display.pushImage(170, 61,  72, 72, sens); 
        delay(3000);
        

      

        M5Cardputer.Display.fillScreen(TFT_BLACK);
 
  M5Cardputer.Display.drawLine(0,16,240,16,lightblue);
  M5Cardputer.Display.drawLine(0,134,240,134,lightblue);

        M5Cardputer.Display.setCursor(200,0,2);
        M5Cardputer.Display.print(brojac);

         M5Cardputer.Display.fillRect(120,3,70,7,TFT_GREEN);
         M5Cardputer.Display.drawRect(119,2,72,9,TFT_GREY);
        
         
         fase=1;
    }

if(fase==1){ //playing fase
  M5Cardputer.update();

   if (M5Cardputer.Keyboard.isChange())
      if (M5Cardputer.Keyboard.isPressed()) {

           //0= not moving, 1 is up, 2 is down, 3 is left, 4 is right
         if(M5Cardputer.Keyboard.isKeyPressed('z') ) move=0;
          if(M5Cardputer.Keyboard.isKeyPressed('e') ) move=1;
           if(M5Cardputer.Keyboard.isKeyPressed('s') ) move=2;
            if(M5Cardputer.Keyboard.isKeyPressed('a') ) move=3;
             if(M5Cardputer.Keyboard.isKeyPressed('d') ) move=4;



    if(M5Cardputer.Keyboard.isKeyPressed('.') ) //fire button A button
    { 
    buletX[counter]=x+34;
    buletY[counter]=y+15;
    counter=counter+1;
    M5Cardputer.Speaker.tone(4000,20);
    }
   

    if(M5Cardputer.Keyboard.isKeyPressed('/') && rockets>0) //Rocket button B button
    { 
    rockets--;
    rocketX[rcounter]=x+34;
    rocketY[rcounter]=y+14;
    rcounter=rcounter+1;
    ri[rockets]=-100;
    M5Cardputer.Display.fillRect(70+(rockets*14),0,8,14,TFT_BLACK);
    M5Cardputer.Speaker.tone(2000,60);
   }}
   

       

           
if(move==2 and y<94) //Move down
y=y+sped;


if(move==1 and y>18) //Move up
y=y-sped;

if(move==4 and x<125) //Move right
  x=x+sped;

if(move==3 and  x>0) //Move right
     x=x-sped;

 
  
  for(int i=0;i<30;i++){ //drawStars..........................................
  M5Cardputer.Display.drawPixel(spaceX[i],spaceY[i],TFT_BLACK);
  spaceX[i]=spaceX[i]-0.5;
  M5Cardputer.Display.drawPixel(spaceX[i],spaceY[i],TFT_GREY);
  if(spaceX[i]<0){
    M5Cardputer.Display.drawPixel(spaceX[i],spaceY[i],TFT_BLACK);
  
  spaceX[i]=244;
  }}
  
  
 
  M5Cardputer.Display.pushImage(x, y,  49, 40, brod1);
  M5Cardputer.Display.pushImage(ex, ey,  55, 54, earth[level-1]); 
  
  for(int i=0;i<10;i++){ //firing buletts
  if(buletX[i]>0){
  M5Cardputer.Display.pushImage(buletX[i], buletY[i],  8, 8, bulet);
   buletX[i]=buletX[i]+0.6;
  }
  if(buletX[i]>240)
  buletX[i]=-30;
  }

  for(int i=0;i<10;i++){ //firing rockets
  if(rocketX[i]>0){
  M5Cardputer.Display.pushImage(rocketX[i], rocketY[i],  24, 12, rocket);
   rocketX[i]=rocketX[i]+rocketSpeed;
  }
  if(rocketX[i]>240)
  rocketX[i]=-30;
  }
  
  //delay(1);
  

  for(int j=0;j<10;j++) //did my bulet hit enemy
  {
    if(buletX[j]>ex+20 && buletY[j]>ey+2 && buletY[j]<ey+52 )
      {
        M5Cardputer.Display.pushImage(buletX[j], buletY[j],  12, 12, ex2);
           if(sound==1){
           M5Cardputer.Speaker.tone(5000,12);
           //noTone(BUZZER_PIN, BUZZER_CHANNEL);
           } else{delay(12);}
           M5Cardputer.Display.fillRect(buletX[j], buletY[j],12,12,TFT_BLACK);
        buletX[j]=-50;
        brojac=brojac+1;
        M5Cardputer.Display.setCursor(200,0,2);
        M5Cardputer.Display.print(brojac);
        eHealth--; 
        tr=map(eHealth,0,mHealth,0,70);
        M5Cardputer.Display.fillRect(120,3,70,7,TFT_BLACK);
        M5Cardputer.Display.fillRect(120,3,tr,7,TFT_GREEN);
         
         if(eHealth<=0){
          M5Cardputer.Display.pushImage(ex, ey,  55, 55, buum);
         M5Cardputer.Speaker.tone(2000,160);
         M5Cardputer.Speaker.tone(3000,260);
         M5Cardputer.Speaker.tone(5000,360);
         M5Cardputer.Speaker.tone(4000,260);
         M5Cardputer.Speaker.tone(100,160);
         delay(700);
         newLevel();}
        
       

         
         
        }
    
    }


      for(int j=0;j<10;j++) //did my ROCKET hit enemy
  {
    if(rocketX[j]+18>ex && rocketY[j]>ey+2 && rocketY[j]<ey+52 )
      {
        M5Cardputer.Display.pushImage(rocketX[j], rocketY[j],  24, 24, explosion);
           if(sound==1){
           M5Cardputer.Speaker.tone(2000,20);
         M5Cardputer.Speaker.tone(3000,20);
           }else {delay(40);}
         M5Cardputer.Display.fillRect(rocketX[j], rocketY[j],24,24,TFT_BLACK);
        //delay(30);
        
        rocketX[j]=-50;
        brojac=brojac+12;
        M5Cardputer.Display.setCursor(200,0,2);
        M5Cardputer.Display.print(brojac);
        eHealth=eHealth-rDamage; 
         tr=map(eHealth,0,mHealth,0,70);
        M5Cardputer.Display.fillRect(120,3,70,7,TFT_BLACK);
        M5Cardputer.Display.fillRect(120,3,tr,7,TFT_GREEN);
         
         if(eHealth<=0){
          M5Cardputer.Display.pushImage(ex, ey,  55, 55, buum);
         M5Cardputer.Speaker.tone(2000,160);
         M5Cardputer.Speaker.tone(3000,260);
         M5Cardputer.Speaker.tone(5000,360);
         M5Cardputer.Speaker.tone(4000,260);
         M5Cardputer.Speaker.tone(100,160);
         delay(700);
         newLevel();}
         

      
        }
    
    }


      for(int j=0;j<10;j++) //Am I hit
  {
    if(EbuletX[j]<x+30 && EbuletX[j]>x+4 && EbuletY[j]>y+4 && EbuletY[j]<y+36 )
      {
        EbuletX[j]=-50;
         ly[lives-1]=-40;
         M5Cardputer.Display.fillRect((lives-1)*14,0,14,14,TFT_BLACK);
         lives--;
         if(lives==0){
           M5Cardputer.Display.pushImage(x, y,  55, 55, buum);
          M5Cardputer.Speaker.tone(2000,160);
         M5Cardputer.Speaker.tone(3000,260);
         M5Cardputer.Speaker.tone(5000,360);
         M5Cardputer.Speaker.tone(4000,260);
         M5Cardputer.Speaker.tone(100,160);
         delay(500);
          M5Cardputer.Display.fillScreen(TFT_BLACK);
          fase=2;}

         
         
        
         
         
        }
    
    }

  ey=ey+es;
  if(ey>80)
  es=es*-1;

  if(ey<18)
  es=es*-1;



  if(blinkTime>0)
  blinkTime++;

  if(blinkTime>2){
  digitalWrite(25,0);
  digitalWrite(33,0);
  blinkTime=0;
  }

  for(int i=0;i<10;i++){   //enemy shoots
  if(EbuletX[i]>-10){
  M5Cardputer.Display.pushImage(EbuletX[i], EbuletY[i],  7, 7, ebullet);
   EbuletX[i]=EbuletX[i]-EbulletSpeed;
  }
  
  }

  for(int i=0;i<4;i++)  //draw lifes
  M5Cardputer.Display.pushImage(i*14, ly[i],  12, 11, life); 
  for(int i=0;i<3;i++)  //draw lifes
  M5Cardputer.Display.pushImage(70+(i*14),ri[i] ,  8, 14, ricon); 

  
  fireCount++;
  if(fireTime==fireCount)
  {
    EbuletX[Ecounter]=ex+5;
    EbuletY[Ecounter]=ey+24;
    fireCount=0;
    fireTime=random(110-(level*15),360-(level*30));
    Ecounter++;
    }
if(counter==9)
  counter=0;

  if(rcounter==3)
  rcounter=0;

if(Ecounter==9)
  Ecounter=0;
}
if(fase==2) //game over fase
{
  
       M5Cardputer.Display.fillScreen(TFT_BLACK);
       M5Cardputer.Display.pushImage(0, 0,  240, 135, gameOver);
       M5Cardputer.Display.setCursor(24,54,2);
       M5Cardputer.Display.print("Score : "+String(brojac));
       M5Cardputer.Display.setCursor(24,69,2);
       M5Cardputer.Display.print("Level : "+String(level));
       delay(4000);
       fase=0;
  }
}



  
