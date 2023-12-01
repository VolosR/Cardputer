#include "M5Cardputer.h"
#include "res.h"

const int pwmFreq = 5000;
const int pwmResolution = 8;
const int pwmLedChannelTFT = 0;


int tt[4]={1,2,5,10};
int cT[4]={TFT_BROWN,TFT_RED,TFT_GOLD,TFT_SILVER};
int colors[12]={TFT_BLACK,TFT_BROWN,TFT_RED,TFT_ORANGE,TFT_YELLOW,TFT_GREEN,TFT_BLUE,TFT_VIOLET,TFT_LIGHTGREY, TFT_WHITE, TFT_GOLD,TFT_SILVER };
double multis[12]={1,10,100,1000,10000,100000,1000000,10000000,100000000,100000000,0.1,0.01};
String mm[12]={"x1","x10","x100","x1K","x10K","x100K","x1M","x10M","x100M","x1G","x0.1","x0.01"};
int band=0;
int color=0;

int first=1;
int secon=2;
int multiplier=1;
int tolerance=2;
int deb1=0;
int deb2=0;

int x=56;
int y=24;
int w=126;
int h=20;

int bPos[4]={86,98,110,138};

void setup() {

    auto cfg = M5.config();
    M5Cardputer.begin(cfg, true);
  
  M5Cardputer.Display.setBrightness(76);
  M5Cardputer.Display.setSwapBytes(true);
  M5Cardputer.Display.setRotation(1);
  
  M5Cardputer.Display.fillScreen(TFT_BLACK);
  M5Cardputer.Display.drawString("Resistor CALC",x,0,2);
  M5Cardputer.Display.pushImage(x,y,120,26,resistor);

  M5Cardputer.Display.fillRect(x+30,y,6,26,colors[first]);
  M5Cardputer.Display.fillRect(x+42,y+3,6,20,colors[secon]);
  M5Cardputer.Display.fillRect(x+54,y+3,6,20,colors[multiplier]);
  M5Cardputer.Display.fillRect(x+82,y,6,26,cT[tolerance]);

  M5Cardputer.Display.fillCircle(bPos[band]+2,58,2,TFT_WHITE);

   for(int i=0;i<12;i++)
   {
    
    if(i<10  ){
    M5Cardputer.Display.fillRect(0,i*13,11,13,colors[i]);
    M5Cardputer.Display.fillRect(22,i*13,11,13,colors[i]);

    if(i==0)
    M5Cardputer.Display.setTextColor(TFT_WHITE,colors[i]);
    else
    M5Cardputer.Display.setTextColor(TFT_BLACK,colors[i]);
    
    M5Cardputer.Display.drawString(String(i),3,(i*13)+2);
    M5Cardputer.Display.drawString(String(i),25,(i*13)+2);
    M5Cardputer.Display.setTextColor(TFT_WHITE,TFT_BLACK);
    }
    if(i==0)
    M5Cardputer.Display.drawCircle(235,(i*11)+5,4,TFT_WHITE);
    else
    M5Cardputer.Display.fillCircle(235,(i*11)+5,4,colors[i]);

    M5Cardputer.Display.drawString(mm[i],194,(i*11)+1);
    
   }

    /*
    M5Cardputer.Display.drawString("<",14,(first*13)+2);
    M5Cardputer.Display.drawString("<",36,(secon*13)+2);
     */

     M5Cardputer.Display.fillCircle(16,(first*13)+5,2,TFT_WHITE);
     M5Cardputer.Display.fillCircle(38,(secon*13)+5,2,TFT_WHITE);
     M5Cardputer.Display.fillCircle(188,(multiplier*11)+5,2,TFT_WHITE);
    

    for(int i=0;i<4;i++){
    M5Cardputer.Display.fillRect(44+(i*34),117,34,11,cT[i]);
    M5Cardputer.Display.setTextColor(TFT_BLACK,cT[i]);
    M5Cardputer.Display.drawString(String(tt[i])+"%",54+(i*34),119);
    }
    M5Cardputer.Display.fillCircle(61+(tolerance*34),133,2,TFT_WHITE);
   M5Cardputer.Display.setTextColor(TFT_WHITE,TFT_BLACK); 
}

void loop() {
 
   M5Cardputer.update();

   if (M5Cardputer.Keyboard.isChange())
      if (M5Cardputer.Keyboard.isPressed()) {
            if (M5Cardputer.Keyboard.isKeyPressed('/')) 
   {
      M5Cardputer.Speaker.tone(4000,50);
      M5Cardputer.Display.fillCircle(bPos[band]+2,58,2,TFT_BLACK);
     
     band++;
     if(band>3)
     band=0; 
     M5Cardputer.Display.fillCircle(bPos[band]+2,58,2,TFT_WHITE);
    }

             if (M5Cardputer.Keyboard.isKeyPressed(',')) 
   {
      M5Cardputer.Speaker.tone(4000,50);
      M5Cardputer.Display.fillCircle(bPos[band]+2,58,2,TFT_BLACK);
     
     band--;
     if(band<0)
     band=3; 
     M5Cardputer.Display.fillCircle(bPos[band]+2,58,2,TFT_WHITE);
    }
    

     if (M5Cardputer.Keyboard.isKeyPressed('.')) 
     {
     M5Cardputer.Speaker.tone(3600,50);
     if(band==0)
      {
         M5Cardputer.Display.fillCircle(16,(first*13)+5,2,TFT_BLACK);
      first++;
      if(first>9)
      first=0;
      M5Cardputer.Display.fillRect(x+30,y,6,26,colors[first]);
       M5Cardputer.Display.fillCircle(16,(first*13)+5,2,TFT_WHITE);
      }
          if(band==1)
            {
              M5Cardputer.Display.fillCircle(38,(secon*13)+5,2,TFT_BLACK);
         secon++;
         if(secon>9)
         secon=0;
         M5Cardputer.Display.fillCircle(38,(secon*13)+5,2,TFT_WHITE);
         M5Cardputer.Display.fillRect(x+42,y+3,6,20,colors[secon]);
            }

             if(band==2)
            {
              M5Cardputer.Display.fillCircle(188,(multiplier*11)+5,2,TFT_BLACK);
          multiplier++;
          if(multiplier>11)
          multiplier=0;
          M5Cardputer.Display.fillCircle(188,(multiplier*11)+5,2,TFT_WHITE);
          M5Cardputer.Display.fillRect(x+54,y+3,6,20,colors[multiplier]);
            }

                if(band==3)
            {
              M5Cardputer.Display.fillCircle(61+(tolerance*34),133,2,TFT_BLACK);
          tolerance++;
          if(tolerance>3)
          tolerance=0;
          M5Cardputer.Display.fillCircle(61+(tolerance*34),133,2,TFT_WHITE);
          M5Cardputer.Display.fillRect(x+82,y,6,26,cT[tolerance]);
            }

     double res=((first*10)+secon)*multis[multiplier];
     M5Cardputer.Display.fillRect(44,70,136,46,0x00A5);
     double maxx=res+(res*(tt[tolerance]/100.00));
     double minn=res-(res*(tt[tolerance]/100.00));
     M5Cardputer.Display.setTextColor(TFT_WHITE,0x00A5); 

     if(res>=1000 && res<1000000){
     M5Cardputer.Display.drawString(String(first)+String(secon)+"x10 ="+String(res/1000)+" K",48,76,2);
     M5Cardputer.Display.drawString(String(multiplier),85,72);
     M5Cardputer.Display.drawString("MAX:"+String(maxx),48,94);
     M5Cardputer.Display.drawString("MIN:"+String(minn),48,106);
     }
     
      else if(res>=1000000)
     {
     M5Cardputer.Display.drawString(String(first)+String(secon)+"x10 ="+String(res/100000)+" M",48,76,2);
     M5Cardputer.Display.drawString(String(multiplier),85,72);
     M5Cardputer.Display.drawString("MAX:"+String(maxx),48,94);
     M5Cardputer.Display.drawString("MIN:"+String(minn),48,106);
     }
     
     else
     {
     M5Cardputer.Display.drawString(String(first)+String(secon)+"x10 ="+String(res)+" ohm",48,76,2);
     M5Cardputer.Display.drawString(String(multiplier),85,72);
     M5Cardputer.Display.drawString("MAX:"+String(maxx),48,94);
     M5Cardputer.Display.drawString("MIN:"+String(minn),48,106);
     }

     M5Cardputer.Display.setTextColor(TFT_WHITE,TFT_BLACK); 
     
    }
    
      }
 
}
