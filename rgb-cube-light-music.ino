#define ANALOG_MIC_PIN A0
#define DIGITAL_MIC_PIN 4
#define BUTTON_PIN 3

//cube->layer/column->led->rgb

#define LAY_CNT 4   
#define CUB_LED_RGB_CNT 192
#define CUB_RGB_CNT 3
#define CUB_LED_CNT 64
#define CUB_LAY_LED_CNT 16
#define CUB_COL_LED_RGB_CNT 12
#define CUB_COL_LED_CNT 4
#define CUB_COL_CNT 16

byte aCube[CUB_LED_RGB_CNT];

byte bMode = 0; //0-1
byte bModeMax = 1;

// Слои снизу вверх
byte aLayBotTop1[CUB_LAY_LED_CNT];
byte aLayBotTop2[CUB_LAY_LED_CNT];
byte aLayBotTop3[CUB_LAY_LED_CNT];
byte aLayBotTop4[CUB_LAY_LED_CNT];
void setLayArr (byte *arr, byte start){
  for(byte x = 0; x < CUB_LAY_LED_CNT; x++){
    arr[x] = start;
    start = start + CUB_COL_LED_RGB_CNT;
  }
}

// Столбцы по одному
byte aColBotTop1[CUB_COL_LED_CNT];
byte aColBotTop2[CUB_COL_LED_CNT];
byte aColBotTop3[CUB_COL_LED_CNT];
byte aColBotTop4[CUB_COL_LED_CNT];
byte aColBotTop5[CUB_COL_LED_CNT];
byte aColBotTop6[CUB_COL_LED_CNT];
byte aColBotTop7[CUB_COL_LED_CNT];
byte aColBotTop8[CUB_COL_LED_CNT];
byte aColBotTop9[CUB_COL_LED_CNT];
byte aColBotTop10[CUB_COL_LED_CNT];
byte aColBotTop11[CUB_COL_LED_CNT];
byte aColBotTop12[CUB_COL_LED_CNT];
byte aColBotTop13[CUB_COL_LED_CNT];
byte aColBotTop14[CUB_COL_LED_CNT];
byte aColBotTop15[CUB_COL_LED_CNT];
byte aColBotTop16[CUB_COL_LED_CNT];
void setRowArr (byte *arr, byte start){
  for(byte x = 0; x < CUB_COL_LED_CNT; x++){
    arr[x] = start;
    start = start + CUB_RGB_CNT;
  }
}
int iCurCol1Level,  iCurCol2Level,  iCurCol3Level,  iCurCol4Level,
    iCurCol5Level,  iCurCol6Level,  iCurCol7Level,  iCurCol8Level,
    iCurCol9Level,  iCurCol10Level, iCurCol11Level, iCurCol12Level,
    iCurCol13Level, iCurCol14Level, iCurCol15Level, iCurCol16Level = 0;

void setColour(byte *arr, byte start, byte colour){
  // 0 - Черный     0   0   0
  // 1 - Красный    255 0   0
  // 2 - Зеленый    0   255 0
  // 3 - Синий      0   0   255
  // 4 - Бирюзовый  0   255 255
  // 5 - Желтый     255 255 0
  // 6 - Пурпурный  255 0   255
  // 7 - Белый      255 255 255
  // 8 - Оранжевый  255 125 0
  switch (colour) {
    case 0:
      arr[start]=0x00;
      arr[start+1]=0x00;
      arr[start+2]=0x00;
      break;
    case 1:
      arr[start]=0xff;
      arr[start+1]=0x00;
      arr[start+2]=0x00;
      break;
    case 2:
      arr[start]=0x00;
      arr[start+1]=0xff;
      arr[start+2]=0x00;
      break;
    case 3:
      arr[start]=0x00;
      arr[start+1]=0x00;
      arr[start+2]=0xff;
      break;
    case 4:
      arr[start]=0x00;
      arr[start+1]=0xff;
      arr[start+2]=0xff;
      break;
    case 5:
      arr[start]=0xff;
      arr[start+1]=0xff;
      arr[start+2]=0x00;
      break;
    case 6:
      arr[start]=0xff;
      arr[start+1]=0x00;
      arr[start+2]=0xff;
      break;
    case 7:
      arr[start]=0xff;
      arr[start+1]=0xff;
      arr[start+2]=0xff;
      break;
    case 8:
      arr[start]=0xff;
      arr[start+1]=0x7d;
      arr[start+2]=0xff;
      break;
    default:
      arr[start]=0x00;
      arr[start+1]=0x00;
      arr[start+2]=0x00;
      break;
  }
}

void setup()
{ 
  pinMode(DIGITAL_MIC_PIN, INPUT);
  pinMode(ANALOG_MIC_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  delay(1000);
  
  Serial.begin(57600);  
  for(byte i=0; i<70; i++)
  {
    Serial.write(0xAD); // Переводит куб в режим управления
  }     

  setLayArr(aLayBotTop1,0);
  setLayArr(aLayBotTop2,3);
  setLayArr(aLayBotTop3,6);
  setLayArr(aLayBotTop4,9);

  setRowArr(aColBotTop1,0);
  setRowArr(aColBotTop2,12);
  setRowArr(aColBotTop3,24);
  setRowArr(aColBotTop4,36);
  setRowArr(aColBotTop5,48);
  setRowArr(aColBotTop6,60);
  setRowArr(aColBotTop7,72);
  setRowArr(aColBotTop8,84);
  setRowArr(aColBotTop9,96);
  setRowArr(aColBotTop10,108);
  setRowArr(aColBotTop11,120);
  setRowArr(aColBotTop12,132);
  setRowArr(aColBotTop13,144);
  setRowArr(aColBotTop14,156);
  setRowArr(aColBotTop15,168);
  setRowArr(aColBotTop16,180);
  
}

void loop()
{
  /*
  if (digitalRead(DIGITAL_MIC_PIN) == HIGH)
  {
    setALL_WHI(aCube);
    printLevel(aCube);
  }
  */

  if (!digitalRead(BUTTON_PIN)){
    setALL_RED(aCube);
    printCube(aCube);
    delay(1000);
    setNextMode();
  }

  int val;
  val = analogRead(ANALOG_MIC_PIN); // 0-1024
  val = map(val, 200, 700, 0, 14);  // 200-700 - определяется опытным путем
  switch (bMode) {
    case 0:
      setCurLevel(aCube,val);
      break;
    case 1:
      setCurColLevel(aCube,val);
      break;
    default:
     
      break;
  }
  
  
  
 
}

void setNextMode(){
  bMode++;
  if (bMode > bModeMax){bMode = 0;}
}

void printLevel(byte *arr){
  printCube(arr);
  setALL_BLA(arr);
  printCube(arr);
}

void setColLevel(byte *arr,byte *arrcol, byte level){
    
    byte x;
    
    switch (level) {
    case 0:
      setColour(arr,arrcol[0],0);
      setColour(arr,arrcol[1],0);
      setColour(arr,arrcol[2],0);
      setColour(arr,arrcol[3],0);
      break;

    ///////////////////////////////////////1/////////////////////////////////// 
    case 1:
      setColour(arr,arrcol[0],2);
      break;
    case 2:
      setColour(arr,arrcol[0],3);
      break;

    ///////////////////////////////////////2/////////////////////////////////// 
    case 3:
      setColour(arr,arrcol[0],2);
      setColour(arr,arrcol[1],2);
      break;
    case 4:
      setColour(arr,arrcol[0],2);
      setColour(arr,arrcol[1],3);
      break;
    case 5:
      setColour(arr,arrcol[0],3);
      setColour(arr,arrcol[1],3);
      break;

    ///////////////////////////////////////3/////////////////////////////////// 
    case 6:
      setColour(arr,arrcol[0],3);
      setColour(arr,arrcol[1],3);
      setColour(arr,arrcol[2],3);
      break;
    case 7:
      setColour(arr,arrcol[0],3);
      setColour(arr,arrcol[1],3);
      setColour(arr,arrcol[2],1);
      break;
    case 8:
      setColour(arr,arrcol[0],3);
      setColour(arr,arrcol[1],1);
      setColour(arr,arrcol[2],1);
      break;
    case 9:
      setColour(arr,arrcol[0],1);
      setColour(arr,arrcol[1],1);
      setColour(arr,arrcol[2],1);
      break;

    ///////////////////////////////////////4/////////////////////////////////// 
    case 10:
      setColour(arr,arrcol[0],1);
      setColour(arr,arrcol[1],1);
      setColour(arr,arrcol[2],1);
      setColour(arr,arrcol[3],1);
      break;
    case 11:
      setColour(arr,arrcol[0],1);
      setColour(arr,arrcol[1],1);
      setColour(arr,arrcol[2],1);
      setColour(arr,arrcol[3],7);
      break;
    case 12:
      setColour(arr,arrcol[0],1);
      setColour(arr,arrcol[1],1);
      setColour(arr,arrcol[2],7);
      setColour(arr,arrcol[3],7);
      break;
    case 13:
      setColour(arr,arrcol[0],1);
      setColour(arr,arrcol[1],7);
      setColour(arr,arrcol[2],7);
      setColour(arr,arrcol[3],7);
      break;
    case 14:
      setColour(arr,arrcol[0],7);
      setColour(arr,arrcol[1],7);
      setColour(arr,arrcol[2],7);
      setColour(arr,arrcol[3],7);
      break;
    default:
      setColour(arr,arrcol[0],0);
      setColour(arr,arrcol[1],0);
      setColour(arr,arrcol[2],0);
      setColour(arr,arrcol[3],0);
      break;
  }
}


void setCurColLevel(byte *arr,byte level){
  
  iCurCol16Level = iCurCol15Level;
  iCurCol15Level = iCurCol14Level;
  iCurCol14Level = iCurCol13Level;
  iCurCol13Level = iCurCol12Level;
  iCurCol12Level = iCurCol11Level;
  iCurCol11Level = iCurCol10Level;
  iCurCol10Level = iCurCol9Level;
  iCurCol9Level = iCurCol8Level;
  iCurCol8Level = iCurCol7Level;
  iCurCol7Level = iCurCol6Level;
  iCurCol6Level = iCurCol5Level;
  iCurCol5Level = iCurCol4Level;
  iCurCol4Level = iCurCol3Level;
  iCurCol3Level = iCurCol2Level;
  iCurCol2Level = iCurCol1Level;
  iCurCol1Level = level;

  setColLevel(arr,aColBotTop1,iCurCol1Level);
  setColLevel(arr,aColBotTop2,iCurCol2Level);
  setColLevel(arr,aColBotTop3,iCurCol3Level);
  setColLevel(arr,aColBotTop4,iCurCol4Level);
  
  setColLevel(arr,aColBotTop8,iCurCol5Level);
  setColLevel(arr,aColBotTop7,iCurCol6Level);
  setColLevel(arr,aColBotTop6,iCurCol7Level);
  setColLevel(arr,aColBotTop5,iCurCol8Level);
  
  setColLevel(arr,aColBotTop9,iCurCol9Level);
  setColLevel(arr,aColBotTop10,iCurCol10Level);
  setColLevel(arr,aColBotTop11,iCurCol11Level);
  setColLevel(arr,aColBotTop12,iCurCol12Level);
  
  setColLevel(arr,aColBotTop16,iCurCol13Level);
  setColLevel(arr,aColBotTop15,iCurCol14Level);
  setColLevel(arr,aColBotTop14,iCurCol15Level);
  setColLevel(arr,aColBotTop13,iCurCol16Level);

  printLevel(arr);
}


void setCurLevel(byte *arr,byte level){
  byte x;
  switch (level) {
    case 0:
      setALL_BLA(arr);
      printCube(arr);
      break;

    ///////////////////////////////////////1/////////////////////////////////// 
    case 1:
      for(x = 0; x < CUB_LAY_LED_CNT; x++){ setColour(arr,aLayBotTop1[x],2);}
      printLevel(arr);
      break;
    case 2:
      for(x = 0; x < CUB_LAY_LED_CNT; x++){ setColour(arr,aLayBotTop1[x],3);}
      printLevel(arr);
      break;

    ///////////////////////////////////////2/////////////////////////////////// 
    case 3:
      for(x = 0; x < CUB_LAY_LED_CNT; x++){ setColour(arr,aLayBotTop1[x],2);}
      for(x = 0; x < CUB_LAY_LED_CNT; x++){ setColour(arr,aLayBotTop2[x],2);}
      printLevel(arr);
      break;
    case 4:
      for(x = 0; x < CUB_LAY_LED_CNT; x++){ setColour(arr,aLayBotTop1[x],2);}
      for(x = 0; x < CUB_LAY_LED_CNT; x++){ setColour(arr,aLayBotTop2[x],3);}
      printLevel(arr);
      break;
    case 5:
      for(x = 0; x < CUB_LAY_LED_CNT; x++){ setColour(arr,aLayBotTop1[x],3);}
      for(x = 0; x < CUB_LAY_LED_CNT; x++){ setColour(arr,aLayBotTop2[x],3);}
      printLevel(arr);
      break;

    ///////////////////////////////////////3/////////////////////////////////// 
    case 6:
      for(x = 0; x < CUB_LAY_LED_CNT; x++){ setColour(arr,aLayBotTop1[x],3);}
      for(x = 0; x < CUB_LAY_LED_CNT; x++){ setColour(arr,aLayBotTop2[x],3);}
      for(x = 0; x < CUB_LAY_LED_CNT; x++){ setColour(arr,aLayBotTop3[x],3);}
      printLevel(arr);
      break;
    case 7:
      for(x = 0; x < CUB_LAY_LED_CNT; x++){ setColour(arr,aLayBotTop1[x],3);}
      for(x = 0; x < CUB_LAY_LED_CNT; x++){ setColour(arr,aLayBotTop2[x],3);}
      for(x = 0; x < CUB_LAY_LED_CNT; x++){ setColour(arr,aLayBotTop3[x],1);}
      printLevel(arr);
      break;
    case 8:
      for(x = 0; x < CUB_LAY_LED_CNT; x++){ setColour(arr,aLayBotTop1[x],3);}
      for(x = 0; x < CUB_LAY_LED_CNT; x++){ setColour(arr,aLayBotTop2[x],1);}
      for(x = 0; x < CUB_LAY_LED_CNT; x++){ setColour(arr,aLayBotTop3[x],1);}
      printLevel(arr);
      break;
    case 9:
      for(x = 0; x < CUB_LAY_LED_CNT; x++){ setColour(arr,aLayBotTop1[x],1);}
      for(x = 0; x < CUB_LAY_LED_CNT; x++){ setColour(arr,aLayBotTop2[x],1);}
      for(x = 0; x < CUB_LAY_LED_CNT; x++){ setColour(arr,aLayBotTop3[x],1);}
      printLevel(arr);
      break;

    ///////////////////////////////////////4/////////////////////////////////// 
    case 10:
      for(x = 0; x < CUB_LAY_LED_CNT; x++){ setColour(arr,aLayBotTop1[x],1);}
      for(x = 0; x < CUB_LAY_LED_CNT; x++){ setColour(arr,aLayBotTop2[x],1);}
      for(x = 0; x < CUB_LAY_LED_CNT; x++){ setColour(arr,aLayBotTop3[x],1);}
      for(x = 0; x < CUB_LAY_LED_CNT; x++){ setColour(arr,aLayBotTop4[x],1);}
      break;
    case 11:
      for(x = 0; x < CUB_LAY_LED_CNT; x++){ setColour(arr,aLayBotTop1[x],1);}
      for(x = 0; x < CUB_LAY_LED_CNT; x++){ setColour(arr,aLayBotTop2[x],1);}
      for(x = 0; x < CUB_LAY_LED_CNT; x++){ setColour(arr,aLayBotTop3[x],1);}
      for(x = 0; x < CUB_LAY_LED_CNT; x++){ setColour(arr,aLayBotTop4[x],7);}
      printLevel(arr);
      break;
    case 12:
      for(x = 0; x < CUB_LAY_LED_CNT; x++){ setColour(arr,aLayBotTop1[x],1);}
      for(x = 0; x < CUB_LAY_LED_CNT; x++){ setColour(arr,aLayBotTop2[x],1);}
      for(x = 0; x < CUB_LAY_LED_CNT; x++){ setColour(arr,aLayBotTop3[x],7);}
      for(x = 0; x < CUB_LAY_LED_CNT; x++){ setColour(arr,aLayBotTop4[x],7);}
      printLevel(arr);
      break;
    case 13:
      for(x = 0; x < CUB_LAY_LED_CNT; x++){ setColour(arr,aLayBotTop1[x],1);}
      for(x = 0; x < CUB_LAY_LED_CNT; x++){ setColour(arr,aLayBotTop2[x],7);}
      for(x = 0; x < CUB_LAY_LED_CNT; x++){ setColour(arr,aLayBotTop3[x],7);}
      for(x = 0; x < CUB_LAY_LED_CNT; x++){ setColour(arr,aLayBotTop4[x],7);}
      printLevel(arr);
      break;
    case 14:
      for(x = 0; x < CUB_LAY_LED_CNT; x++){ setColour(arr,aLayBotTop1[x],7);}
      for(x = 0; x < CUB_LAY_LED_CNT; x++){ setColour(arr,aLayBotTop2[x],7);}
      for(x = 0; x < CUB_LAY_LED_CNT; x++){ setColour(arr,aLayBotTop3[x],7);}
      for(x = 0; x < CUB_LAY_LED_CNT; x++){ setColour(arr,aLayBotTop4[x],7);}
      printLevel(arr);
      break;

    default:
      setALL_BLA(arr);
      printCube(arr);
      break;
  }
}

void setALL_BLA(byte *arr){
  for(byte i=0; i<192; i++){ arr[i] = 0x00;}
}
void setALL_WHI(byte *arr){
  for(byte i=0; i<192; i++){ arr[i] = 0xff;}
}
void setALL_RED(byte *arr){
  for(byte i=0; i<192; i = i + 3){ arr[i] = 0xff;}
}

void printCube(byte *arr)
{
  Serial.write(0xEA); 
  delayMicroseconds(170);
  for(byte i=0; i<192; i++)
  {
    Serial.write(arr[i]);
    delayMicroseconds(170);
  }
  Serial.write(0xEB);
  delayMicroseconds(170);
}
