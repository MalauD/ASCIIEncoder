#include <LiquidCrystal.h>
LiquidCrystal lcd(8,9,4,5,6,7);  
 
int keypad_pin = A0;
int keypad_value = 0;
int keypad_value_old = 0;
 
char btn_push;
 
byte mainMenuPage = 1;
byte submenupage = 1;
byte submenupageold = 1;
bool Insub = false;
byte mainMenuPageOld = 1;
byte mainMenuTotal = 2;
 
void setup()
{
    lcd.begin(16,2); 
    Serial.begin(9600);
    MainMenuDisplay();
    delay(1000);
	
}
void loop()
{
    btn_push = ReadKeypad();
   
    MainMenuBtn();
   
    if(btn_push == 'S')
    {
        WaitBtnRelease();
        Insub =true;
        switch (mainMenuPage)
        {
            case 1:
              MenuA();
              break;
            case 2:
              MenuB();
              break;

        }
          if(!Insub){
            MainMenuDisplay();
         
          }
          else{
            SubMenuDisplay();
          }
           WaitBtnRelease();
    }
   if(Insub){
     SubMenuDisplay();
   }
 
    
    delay(10);
 
}

char entry[] = {65};
int output[] = {65};
int InModif = 0;

void MenuA()
{  
    lcd.clear();
    lcd.setCursor(0,0);
    //lcd.print("String to ASCII");
   SubMenuDisplay();
    while(ReadKeypad()!= 'L')
    {
        
        //SubMenuDisplay();
        btn_push = ReadKeypad();
        MainMenuBtn();
        delay(10);

        if(btn_push == 'S'){
          lcd.clear();
          
          lcd.print(entry);
          while(ReadKeypad()!= 'S'){
            
            StringToASCII('A');
            delay(10);
          }
          Insub = false;
          return;
          
        }
       
    }
    Insub = false;
}
int ToASCII(char a){

  for(int x = 0;x <= 127;x++)
  {
    if(x == a){
      return x;
    }
  }
  
}







void StringToASCII(char Menu)
{
  
  btn_push = ReadKeypad();
  WaitBtnRelease();
  switch(btn_push){
    case 'U':
      entry[InModif]++;
      if(Menu == 'B' && entry[InModif] == 58){
        entry[InModif] == 57;
      }
      break;
    case 'D':
      entry[InModif]--;
      if(Menu == 'B' && entry[InModif] == 47){
        entry[InModif] == 48;
      }
      break;
    case 'R':
      InModif++;
      if(Menu == 'A'){
        entry[InModif] = 65;
      }
      else{
        entry[InModif] = 48;
      }
      break;
    case 'L':
      InModif--;
      //entry[InModif] = 65;
      if(InModif <  0)
        InModif = 0;
      break;
    default:
      return;
  }


  lcd.clear();


  if(Menu == 'A'){
     for(int i = 0;i < 16;i++){
    if(entry[i] != 0){
       lcd.setCursor(i*2,1);
      lcd.print(ToASCII(entry[i]));}
    }
  }
  else{
    for(int i = 0;i < 16;i++){
      if(entry[i] != 0){
        lcd.setCursor(i*2,1);
        lcd.print(char(entry[i] - '0'));
       }
    }
  }
 
    
    
    
  
  
  lcd.setCursor(0,0);
  lcd.print(entry);
  
  //lcd.print(output);
  
  //delay(1000);

  

  
}






void MenuB()
{  
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Inside Menu B");
   SubMenuDisplay();
    while(ReadKeypad()!= 'L')
    {
        //Insert Task for Menu B here
        //SubMenuDisplay();
        btn_push = ReadKeypad();
        MainMenuBtn();
        delay(10);

        if(btn_push == 'S'){
          lcd.clear();
          entry[0] = '0';
          lcd.print(entry);
          while(ReadKeypad()!= 'S'){
            
            StringToASCII('B');
            delay(10);
          }
          Insub = false;
          return;
        }
        //Serial.println(submenupage);
       
    }
    Insub = false;
}


void SubMenuDisplay(){
  lcd.clear();
    lcd.setCursor(0,0);
    switch (submenupage)
    {
        case 1:
          lcd.print("ASCII");
          break;
        case 2:
          lcd.print("MORSE");
          break;
    }
}
 
void MainMenuDisplay()
{
    lcd.clear();
    lcd.setCursor(0,0);
    switch (mainMenuPage)
    {
        case 1:
          lcd.print("Encode");
          break;
        case 2:
          lcd.print("Decode");
          break;
    }
}
 
void MainMenuBtn()
{ 
  
   Serial.println(submenupage);
    WaitBtnRelease();
    
    if(btn_push == 'U')
    { 
      if(!Insub){
        mainMenuPage--;
        if(mainMenuPage == 0)
          mainMenuPage = 1;
      }
      else{
        submenupage--;
        if(submenupage == 0)
          submenupage = 1;
      }
        
    }
    else if(btn_push == 'D')
    { if(!Insub)
      {
        mainMenuPage++;
        if(mainMenuPage > mainMenuTotal)
          mainMenuPage = mainMenuTotal;   
          
      }
      else{
        
        submenupage++;
        if(submenupage > 2)
          submenupage = 2;   
      }
    }
   
    if(mainMenuPage != mainMenuPageOld) /
    {
        MainMenuDisplay();
        mainMenuPageOld = mainMenuPage;
    }
    if(submenupage != submenupageold) 
    {
        SubMenuDisplay();
        submenupageold = submenupage;
    }
}
 
char ReadKeypad()
{

  keypad_value = analogRead(keypad_pin);
 
  if(keypad_value < 100)
    return 'R';
  else if(keypad_value < 200)
    return 'U';
  else if(keypad_value < 400)
    return 'D';
  else if(keypad_value < 600)
    return 'L';
  else if(keypad_value < 800)
    return 'S';
  else
    return 'N';
 
}
 
void WaitBtnRelease()
{
    while( analogRead(keypad_pin) < 800){}
}
