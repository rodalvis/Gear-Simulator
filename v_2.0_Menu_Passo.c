#include <LiquidCrystal.h>
LiquidCrystal lcd(8,9,4,5,6,7);  
 
int keypad_pin = A0;
int keypad_value = 0;
int keypad_value_old = 0;

#define motor 2 //habilita o motor
#define dir 3 //determina a direção
#define pul 4

void mais_passo();
void menos_passo();
void Motor_Estado();
void Var_a();
void Var_b();
void Direcao();
boolean a = false;
boolean b = false; 
unsigned int v_bt;
unsigned int passo = 1; //passo minimo 1mm
 
char btn_push;
 
byte mainMenuPage = 1;
byte mainMenuPageOld = 1;
byte mainMenuTotal = 4;
 
void setup()
{
    pinMode(motor, OUTPUT);
    pinMode(dir, OUTPUT);
    pinMode(pul, OUTPUT);
        
    lcd.begin(16,2);  //Initialize a 2x16 type LCD
    MainMenuDisplay();
    delay(1000);
}
void loop()
{
    mais_passo();
    menos_passo();
        
    btn_push = ReadKeypad();

    MainMenuBtn();
   
    if(btn_push == 'S')//enter selected menu
    {
        WaitBtnRelease();
        switch (mainMenuPage)
        {
            case 1:
              MenuA();
              break;
            case 2:
              MenuB();
              break;
            case 3:
              MenuC();
              break;
            case 4:
              MenuD();
              break;
        }
 
          MainMenuDisplay();
          WaitBtnRelease();
    }
   
 
 
    delay(10);
 
}//--------------- End of loop() loop ---------------------
void MenuA()
{  
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Direcao < >");
   
    while(ReadKeypad()!= 'L')
    {   
        //Insert Task for Menu A here
        Var_b();
        if(ReadKeypad() == 'R'){
        Direcao();
        delay(200);}
        
        }
       
    }
void MenuB()
{  
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Rosca Metrica");
   
    while(ReadKeypad()!= 'L')
    {
        //Insert Task for Menu B here
       
    }
}
void MenuC()
{  
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Rosca Polegada");
   
    while(ReadKeypad()!= 'L')
    {
        //Insert Task for Menu C here
       
    }
}
void MenuD()
{  
    

    while(ReadKeypad()!= 'L')
    {     
          lcd.setCursor(0,0);
          lcd.print("Passo Desejado");
          lcd.setCursor(0,1);
          lcd.print(passo);
          lcd.print(" mm");
          Var_a();          
        
        if(ReadKeypad() == 'R'){
        Motor_Estado();
        delay(200);
        }
        else if(ReadKeypad() == 'U'){ 
        mais_passo();
        delay(200);
        }
        else if(ReadKeypad() == 'D' && passo > 1){
        lcd.clear();
        menos_passo();
        delay(60);
        }
        
        
         
        
    }
}

void mais_passo(){
  passo++;
  }
void menos_passo(){
  passo--;
  }
void Var_a(){
  if(a==true){  
  lcd.setCursor(8,1);
  lcd.print("ON ");}
  else if(a != true){
   lcd.setCursor(8,1);
  lcd.print("OFF");}
  }

void Var_b(){
  if(b==true){  
  lcd.setCursor(3,1);
  lcd.print("Esquerda");}
  else if(b!= true){
   lcd.setCursor(3,1);
  lcd.print("Direita ");
  }
  }  
void Direcao(){
  switch(b){
  case true :
  digitalWrite(dir,HIGH);
  b = !b;
  break;
  case false:
  digitalWrite(dir,LOW);
  b = !b;
  break;
  }
}
void Motor_Estado(){
  switch(a){
  case true :
  digitalWrite(motor,HIGH);
  a = !a;
  break;
  case false:
  digitalWrite(motor,LOW);
  a = !a;
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
          lcd.print("Direcao < >");
          break;
        case 2:
          lcd.print("Rosca_Metrica");
          break;
        case 3:
          lcd.print("Rosca_Polegada");
          break;
        case 4:
          lcd.print("Passo_Desejado");
          break;
    }
}
 
void MainMenuBtn()
{
    WaitBtnRelease();
    if(btn_push == 'U')
    {
        mainMenuPage++;
        if(mainMenuPage > mainMenuTotal)
          mainMenuPage = 1;
    }
    else if(btn_push == 'D')
    {
        mainMenuPage--;
        if(mainMenuPage == 0)
          mainMenuPage = mainMenuTotal;    
    }
   
    if(mainMenuPage != mainMenuPageOld) //only update display when page change
    {
        MainMenuDisplay();
        mainMenuPageOld = mainMenuPage;
    }
}
 
char ReadKeypad()
{
  /* Keypad button analog Value
  no button pressed 1023
  select  741
  left    503
  down    326
  up      142
  right   0
  */
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
