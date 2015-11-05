
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,10,9,8,7);

SoftwareSerial BT (5,6);

int led1=3;
int led2=2;
char cadena[16]="";
int i=0;
int pos=-1;
char usuario1[8]="alvaro";
char contrasena1[8]="chato";
char usuario2[8]="jose";
char contrasena2[8]="perro";

char user3[16]="";
char user3pass[16]="";
char user4[16]="";
char user4pass[16]="";
char user5[16]="";
char user5pass[16]="";
char user6[16]="";
char user6pass[16]="";

char cmdLed1On[16]="led1on";
char cmdLed1Off[16]="led1off";
char cmdLed2On[16]="led2on";
char cmdLed2Off[16]="led2off";


int valida_usuario=0;
int numero_usuario;

boolean sesion= false;

void setup(){
  BT.begin(9600);
  Serial.begin(9600);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Bienvenido");
  delay(2000);
  lcd.clear();
  BT.print("Inicializado\n");
}

void loop(){
  
  if(valida_usuario==0){
   if(BT.available()){
      char dato=(char)BT.read();
      cadena[i++]=dato;
      pos++;
      lcd.setCursor(pos,0);
      lcd.print(dato);
 
      if(dato=='/')   {
        pos=-1;          
        if(strstr(cadena,usuario1)!=0 ) {
          valida_usuario=1;
          numero_usuario=1;
          delay(2000);
          clean();
        }
        if(strstr(cadena,usuario2)!= 0 ) {
          valida_usuario=1;
          numero_usuario=2;
          delay(2000);
          clean();
        }


        if(strstr(cadena,user3)!= 0 ) {
          valida_usuario=1;
          numero_usuario=3;
          delay(2000);
          clean();
        }
        if(strstr(cadena,user4)!= 0 ) {
          valida_usuario=1;
          numero_usuario=4;
          delay(2000);
          clean();
        }
        if(strstr(cadena,user5)!= 0 ) {
          valida_usuario=1;
          numero_usuario=5;
          delay(2000);
          clean();
        }
        if(strstr(cadena,user6)!= 0 ) {
          valida_usuario=1;
          numero_usuario=6;
          delay(2000);
          clean();
        }



        if(valida_usuario==0) {
          valida_usuario=1;
          numero_usuario=0;
          sesion=false;
          delay(2000);
          clean();
        }
      }


      if(dato=='*'){
        pos=-1;          
        numero_usuario= saveUser();
        valida_usuario=1;
        delay(2000);
        clean();
      }

      if(dato=='-'){
        if(strstr(cadena,cmdLed1On)!=0){
          digitalWrite(led1,HIGH);
          delay(2000);
          BT.print('led1on\n');
          clean();
        }
        if(strstr(cadena,cmdLed1Off)!=0 ){
          digitalWrite(led1,LOW);
          delay(2000);
          BT.print('led1off\n');
          clean();
        }
        if(strstr(cadena,cmdLed2On)!=0){
          digitalWrite(led2,HIGH);
          delay(2000);
          BT.print('led2on\n');
          clean();
        }
        if(strstr(cadena,cmdLed2Off)!=0){
          digitalWrite(led2,LOW);
          delay(2000);
          BT.print('led2off\n');
          clean();
        }
      }

    }
  }
  if(valida_usuario==1) {
    if(BT.available()){
      char dato=(char) BT.read();
      cadena[i++]=dato;
      delay(100);
      pos++;
      lcd.setCursor(pos,1);
      lcd.print(dato);
     
      if(dato=='/')  {
        pos=-1;
        switch (numero_usuario){
          case 1:
            if(strstr(cadena, contrasena1) !=0){
              lcd.clear();
              //digitalWrite(led1,HIGH);
              lcd.setCursor(0,0);
              lcd.print("LogIn Correcto");
              BT.print("loginok\n");
              delay(2000);
              clean();
              valida_usuario=0;
              sesion=true;
            }
            break;
          case 2:
            if(strstr(cadena,contrasena2)!=0){
              lcd.clear();
              //digitalWrite(led2,HIGH);
              lcd.setCursor(0,0);
              lcd.print("LogIn Correcto");
              BT.print("loginok\n");
              delay(2000);
              clean();
              valida_usuario=0;
              sesion=true;
            }
            break;



          case 3:
            if(strstr(cadena,user3pass)!=0){
              lcd.clear();
              //digitalWrite(led2,HIGH);
              lcd.setCursor(0,0);
              lcd.print("LogIn Correcto");
              BT.print("loginok\n");
              delay(2000);
              clean();
              valida_usuario=0;
              sesion=true;
            }
            break;
          case 4:
            if(strstr(cadena,user4pass)!=0){
              lcd.clear();
              //digitalWrite(led2,HIGH);
              lcd.setCursor(0,0);
              lcd.print("LogIn Correcto");
              BT.print("loginok\n");
              delay(2000);
              clean();
              valida_usuario=0;
              sesion=true;
            }
            break;
          case 5:
            if(strstr(cadena,user5pass)!=0){
              lcd.clear();
              //digitalWrite(led2,HIGH);
              lcd.setCursor(0,0);
              lcd.print("LogIn Correcto");
              BT.print("loginok\n");
              delay(2000);
              clean();
              valida_usuario=0;
              sesion=true;
            }
            break;
          case 6:
            if(strstr(cadena,user6pass)!=0){
              lcd.clear();
              //digitalWrite(led2,HIGH);
              lcd.setCursor(0,0);
              lcd.print("LogIn Correcto");
              BT.print("loginok\n");
              delay(2000);
              clean();
              valida_usuario=0;
              sesion=true;
            }
            break;

          default:
            lcd.clear();
            //digitalWrite(led1,LOW);
            lcd.setCursor(0,0);
            lcd.print("LogIn Incorrecto");
            BT.print("loginerror\n");
            delay(2000);
            clean();
            valida_usuario=0;
            sesion=false;
        }
      }


      if(dato=='*'){
        pos=-1;
        switch (numero_usuario){
          case 3:
            strncpy(user3pass, cadena, 16);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Usuario creado!");
            BT.print("crearok\n");
            delay(2000);
            clean();
            valida_usuario=0;
            sesion=true;
            break;
          case 4:
            strncpy(user4pass, cadena, 16);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Usuario creado!");
            BT.print("crearok\n");
            delay(2000);
            clean();
            valida_usuario=0;
            sesion=true;
            break;
          case 5:
            strncpy(user5pass, cadena, 16);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Usuario creado!");
            BT.print("crearok\n");
            delay(2000);
            clean();
            valida_usuario=0;
            sesion=true;
            break;
          case 6:
            strncpy(user6pass, cadena, 16);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Usuario creado!");
            BT.print("crearok\n");
            delay(2000);
            clean();
            valida_usuario=0;
            sesion=true;
            break;
          default:
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Usuarios ya completos.");
            BT.print("Usuarios ya están completos.\n");
            delay(2000);
            clean();
            valida_usuario=0;
            sesion=false;
        }
      }

    }
  }
  
}
void clean(){
  for(int cl=0; cl<=i; cl++){
    cadena [cl]=0;
  }
  i=0;
  pos=-1;
  lcd.clear();
}


int saveUser(){
  if(strlen(user3) == 0){
    strncpy(user3, cadena, 16);
    //user3==c;
    return 3;
  }
  if(strlen(user4) == 0){
    strncpy(user4, cadena, 16);
    return 4;
  }
  if(strlen(user5) == 0){
    strncpy(user5, cadena, 16);
    return 5;
  }
  if(strlen(user6) == 0){
    strncpy(user6, cadena, 16);
    return 6;
  }
  return 0;
}
