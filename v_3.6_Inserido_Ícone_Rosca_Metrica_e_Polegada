#include <LiquidCrystal.h>
LiquidCrystal lcd(8,9,4,5,6,7);  
   
volatile short int count = 0;
  //Pinagem do Motor e Encoder
#define motor A5 // EN habilita o motor
#define dir A4 // DIR determina a direção
#define pul 13 // PUL envia pulsos
#define enca 2 // Fio A encoder
#define encb 3 // Fio B encoder

  //Prototipagem das Funções
void Motor_Estado();
void V_On_Off();
void V_Dir_Esq();
void Direcao();
void gira();
void ai0();
void int2pul();
void WaitBtnRelease();
char ReadKeypad();
void MainMenuBtn();
int arred_ii(float n);
int arred_mm(float n);
int calc_rosc_ii(int rosca);
int calc_rosc_mm(int rosca);
boolean rosca=false;

  //Variaveis Globais
short int intervalo = 100; //--------------------------------------------------------------------------------------
unsigned short int rosca_i= 5;
double rosca_mm= 0.5;
unsigned int v_bt;
float passo = 0.10; //passo minimo 1mm
boolean pulso = LOW; 
char btn_push;
boolean a = LOW;
boolean b = LOW; 
int keypad_pin = A0;
int keypad_value = 0;
int keypad_value_old = 0;
byte mainMenuPage = 1;
byte mainMenuPageOld = 1;
byte mainMenuTotal = 4;
void MainMenuDisplay();

byte parafuso[8] = {
  B11111,
  B11111,
  B01100,
  B00110,
  B01100,
  B00110,
  B01100,
  B00100
};

byte nao[8] = {
  B10001,
  B11011,
  B01110,
  B00100,
  B00100,
  B01110,
  B11011,
  B10001
};

 
void setup()
{      
  pinMode(enca, INPUT_PULLUP); // internal pullup input pin 2 
  pinMode(encb, INPUT_PULLUP); // internal pullup input pin 3
 
  attachInterrupt(0, ai0, RISING); //"cadastra" a função ai0 para função a ser executada caso o pino 2 tenha o estado mudado de HIGH ou LOW(qualquer interação no pino será executado a função ai0)
  attachInterrupt(1, ai1 , RISING); //"cadastra" a função ai1 para função a ser executada caso o pino 3 tenha o estado mudado de HIGH ou LOW(qualquer interação no pino será executado a função ai1) 
  
    pinMode(motor, OUTPUT);
    pinMode(dir, OUTPUT);
    pinMode(pul, OUTPUT);

Serial.begin(9600);
        
    lcd.begin(16,2);  //Initialize a 2x16 type LCD
    lcd.createChar(1,parafuso);
    lcd.createChar(2,nao);
    MainMenuDisplay();
    
}
void loop()
{
    // Serial.println(count); -------------------------------------------
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
 
}//--------------- End of loop() loop ---------------------
void MenuA()                            //Função de Menu de Direção
{  
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Direcao < >");
    
    while(ReadKeypad()!= 'L')
    {   
        //Insert Task for Menu A here
        V_Dir_Esq();
        if(ReadKeypad() == 'R'){
        Direcao();
        delay(150);}
        
        }    
    }
void MenuB()                              //Função de Menu da Rosca Metrica
{     
    while(ReadKeypad()!= 'L')
    {
    lcd.setCursor(0,0);
    lcd.print("Rosca Metrica");  
      
        lcd.setCursor(1,1);
        lcd.print(rosca_mm);
        lcd.print("MM");
        V_On_Off();
        calc_rosc_mm(rosca_mm);          
        if(ReadKeypad() == 'R' && !(intervalo==0)){
        delay(200);     //Delay de Segurança NÃO RETIRAR.
        rosca = !rosca;
        Motor_Estado();
        V_On_Off();
        int2pul();    //envia pulsos a cada N intervalos  
        delay(200);
        }
        else if(ReadKeypad() == 'U' && rosca_mm <= 9.0){ 
        rosca_mm+=0.5;
        delay(200);
        }
        else if(ReadKeypad() == 'D' && rosca_mm >= 0.5){
        lcd.clear();
        rosca_mm-=0.5;
        delay(200);
    }
}
}
void MenuC(){                                       //Função de Menu da Rosca Polegada
    while(ReadKeypad()!= 'L'){   
    lcd.setCursor(0,0);
    lcd.print("Rosca Polegada");
        lcd.setCursor(1,1);
        lcd.print(rosca_i);
        lcd.print("TPI");
        V_On_Off();
        calc_rosc_ii(rosca_i);        
        if(ReadKeypad() == 'R' && !(intervalo==0)){
        delay(200);     //Delay de Segurança NÃO RETIRAR.
        rosca = !rosca;
        Motor_Estado();
        V_On_Off();
        int2pul();    //envia pulsos a cada N intervalos  
        delay(200);
        }
        else if(ReadKeypad() == 'U' && rosca_i <= 50){ 
        rosca_i++;
        delay(200);
        }
        else if(ReadKeypad() == 'D' && rosca_i >= 5){
        lcd.clear();
        rosca_i--;
        delay(200);}
}
}
void MenuD(){                     //Função de Menu do Passo Desejado
    while(ReadKeypad()!= 'L'){     
          lcd.setCursor(0,0);
          lcd.print("Passo Desejado");
          lcd.setCursor(0,1);
          lcd.print(passo);
          lcd.print(" mm");
          V_On_Off();          
          gira(); 
        if(ReadKeypad() == 'R'){
        Motor_Estado();
        delay(200);
        }
        else if(ReadKeypad() == 'U' && passo <= 9.9){ 
        passo+=0.1;
        delay(200);
        }
        else if(ReadKeypad() == 'D' && passo >= 0.1){
        lcd.clear();
        passo-=0.1;
        delay(200);
        }     
        
    }
}

void V_On_Off(){                        //printa na tela lcd o estado do motor
  lcd.setCursor(8,1);
  a ? lcd.print("ON ") : lcd.print("OFF ");
  }

void V_Dir_Esq(){                       //printa na tela lcd o sentido de giro do motor
  lcd.setCursor(3,1);
 b ? lcd.print("Esquerda") : lcd.print("Direita ");
 }  
 
void Direcao(){                     //muda o sentido de giro do motor. De direita para esquerda ou esquerda para direita
  switch(b){
  case true :
 //digitalWrite(dir,LOW);
  analogWrite(dir,LOW);
  b = !b;
  break;
  case false:
  //digitalWrite(dir,HIGH);
 analogWrite(dir,HIGH);
  b = !b;
  break;
  }
}
void Motor_Estado(){                  //muda o estado do motor. De ligado para desligado ou desligado para ligado
  switch(a){
  case true :
  analogWrite(motor,HIGH);
  a = !a;
  break;
  case false:
  analogWrite(motor,LOW);
  a = !a;
  break; 
    } 
}
void gira(){                                  //Função para gerar pulsos para o motor girar.Usada na função passo desejado  
  while(a){
   pulso = !pulso; //inverte o estado da variável
  digitalWrite(pul, pulso); //atribui o novo estado à porta
  delay(10/passo);
  //delayMicroseconds(900); 
  if(ReadKeypad() == 'R'){
    Motor_Estado();
    delay(200);}
           }
  }

int calc_rosc_mm(int rosca){                              //Função de calculo para o numero de rosca metrica
    intervalo=arred_mm((1200/(200/3.18*rosca)));
    Serial.println("Calculo intervalo MM:");
    Serial.println(intervalo);
    lcd.setCursor(12,1);
    (intervalo==0) ? lcd.write(byte(2)): lcd.write(byte(1)) ;
    if(intervalo>=0){return intervalo; } 
    else {return 0 ;}
  }

int calc_rosc_ii(int rosca){                            //Função de calculo para o numero de rosca fios por polegada
    intervalo=arred_ii((1200/(200/3.18*(25.4/rosca))));
    Serial.println("Calculo intervalo II:");
    Serial.println(intervalo);
    lcd.setCursor(12,1);
    (intervalo==0) ? lcd.write(byte(2)): lcd.write(byte(1)) ;
    if(intervalo>=0){return intervalo; } 
    else {return 0 ;}
  }

int arred_mm(float n){            //Função de arredondamento do intervalo para rosca metrica
  int n_int = n;
    if(n - n_int <= 0.40){return n_int;}
    else if(n - n_int >=0.60){return n_int;}
    else return 0; 
  }
int arred_ii(float n){            //Função de arredondamento do intervalo para rosca fios por polegada
  int n_int = n;
    if(n - n_int <= 0.30){return n_int;}
    else if(n - n_int >=0.85){return n_int;}
    else return 0; 
  }
void int2pul(){
  while(a){   
  
 if(ReadKeypad() == 'R'){
    rosca = !rosca;
    Motor_Estado();
    delay(200);}
  }     
}

void ai0()
{ 
  if(count>=intervalo && rosca){  
    count = 0;
    digitalWrite(pul,HIGH);
    delay(intervalo);
    digitalWrite(pul,LOW); }
  if (digitalRead(3) == LOW)
  {  count++; }
  else
  {  count--; }
}

void ai1()
{
 if(count>=intervalo && rosca){  
    count = 0;
    digitalWrite(pul,HIGH);
    delay(intervalo);
    digitalWrite(pul,LOW); }
  if (digitalRead(2) == LOW)
  {  count--; }
  else
  {  count++; }
}

void MainMenuDisplay(){
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
