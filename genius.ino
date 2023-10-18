#include <Wire.h> //Biblioteca Necessária para o Display LCD
#include <LiquidCrystal_I2C.h> //Biblioteca Necessária para o adaptador do Display LCD
long randNumber; // Função que gera números aleatorios 

//modulo i2c 
  LiquidCrystal_I2C lcd(0x27,20,4); //Configura o Display LCD
//--


//Define as váriaveis usadas no codigo
int reiniciar = 0;

//botões
#define botao_inicio 3
#define botao_verde 9
#define botao_vermelho 10
#define botao_amarelo 5
#define botao_azul 11

//leds
#define led_verde 12
#define led_vermelho 6
#define led_amarelo 8
#define led_azul 2

//buzer
#define buzina 7 

//Aqui configuramos cada um
void setup() {
  lcd.init();                 
  lcd.backlight();
  pinMode(led_verde, OUTPUT);
  pinMode(led_vermelho, OUTPUT);
  pinMode(led_amarelo, OUTPUT);
  pinMode(led_azul, OUTPUT);
  pinMode(botao_verde, INPUT_PULLUP);
  pinMode(botao_vermelho, INPUT_PULLUP);
  pinMode(botao_amarelo, INPUT_PULLUP);
  pinMode(botao_azul, INPUT_PULLUP);
  pinMode(botao_inicio, INPUT_PULLUP);
  pinMode(buzina,OUTPUT);
  randomSeed(analogRead(0));
}
void loop() {
  lcd.clear(); //limpa o Display
  lcd.setCursor(3,0); //Seta o lugar onde o Display irá escrever
  lcd.print("Rodada: "); //Mostra esse texto 
  int lista[20]; //Cria uma lista 
  for (int i = 0; i < 20; i++) { //inicio da programa 
    lcd.setCursor(11,0); 
    lcd.print(i+1); //Insere o número da rodada
    delay(300);
    lista[i] = random(1,5); //Adiciona a lista um número aleatorio entre 1 e 5 (não inclui o 5)
    int arraylenght = i;
    int tam = arraylenght; //A variavel tam recebe o tamanho da sequencia 
    rodaSequencia(lista, arraylenght); //Aqui rodamos a sequencia em uma funcão
    for (int l = 0; l <= tam;l++){ //Aqui verificamos se o usuario apertou no botão certo 
      while(true){
        int botaoPressionado = checarBotao();
        if (botaoPressionado != 0) {
          if (botaoPressionado == lista[l]) {
            ligaLed(botaoPressionado);
            desligaLeds();
            break;
          } else { //se clicou errado cai aqui
            lcd.setCursor(3,0);
            lcd.print("  Perdeu!   "); //mensagem de derrota no Display 
            lcd.setCursor(0,1);
            lcd.print("Tente outra vez");
            while(true){ //Aqui é onde o programa ficará "Preso" até o usuário apertar para reinciar o programa
              int reiniciar = digitalRead(botao_inicio);
              fimJogo();
              if (reiniciar ==  1){
                loop();
              }
            }          
          } 
        }
      }
    }
  }
  //Aqui é caso o usuario ganhe
  lcd.setCursor(3,0);
  lcd.print("Parabens!"); 
  lcd.setCursor(2,1);
  lcd.print("Voce Ganhou!!");
  while(true){ //Aqui é onde o programa ficará "Preso" até o usuário apertar para reinciar o programa
    ganhou();
    desligaLeds();
    int reiniciar = digitalRead(botao_inicio);
    if (reiniciar ==  1){
      loop();
    }
  }
}

int checarBotao() { //Função para verificar qual botão foi apertado
  if (digitalRead(botao_verde) == HIGH) {
    return 1;
  }
  if (digitalRead(botao_vermelho) == HIGH) {
    return 2;
  }
  if (digitalRead(botao_amarelo) == HIGH) {
    return 3;
  }
  if (digitalRead(botao_azul) == HIGH) {
    return 4;
  }
  if (digitalRead(botao_inicio) == HIGH){
    loop(); //se esse for clicado reinicia o programa 
  }
  return 0;
}

void fimJogo() { //Função quando perde
  digitalWrite(led_vermelho, HIGH);
  digitalWrite(led_verde, HIGH);
  digitalWrite(led_amarelo, HIGH);
  digitalWrite(led_azul, HIGH);
  delay(500);
  desligaLeds();  
}
void ganhou() { //Função quando ganha
  digitalWrite(led_vermelho, HIGH);
  digitalWrite(led_verde, HIGH);
  digitalWrite(led_amarelo, HIGH);
  digitalWrite(led_azul, HIGH);
}
void ligaLed(int cor){ //Função que liga e led e o som 
  if (cor == 1){
    digitalWrite(led_verde, HIGH);
    tone(buzina, 350);
    delay(300);
    desligaSom();
    desligaLeds();
  }
  if (cor == 2){
    digitalWrite(led_vermelho, HIGH);
    tone(buzina, 550);
    delay(300);
    desligaSom();
    desligaLeds();
  }
  if (cor == 3){
    digitalWrite(led_amarelo, HIGH);
    tone(buzina, 750);
    delay(300);
    desligaSom();
    desligaLeds();
  }
  if (cor == 4){
    digitalWrite(led_azul,HIGH);
    tone(buzina, 950);
    delay(300);
    desligaSom();
    desligaLeds(); 
  }
}
void desligaLeds() { //desliga as Leds
  digitalWrite(led_verde, LOW);
  digitalWrite(led_vermelho, LOW);
  digitalWrite(led_amarelo, LOW);
  digitalWrite(led_azul, LOW);
}
void desligaSom(){ //Desliga o Som 
  noTone(buzina);
}
void rodaSequencia(int lista[], int tam){ //Roda toda a sequência 
  for (int k = 0; k <= tam; k++){
    int cor = lista[k];
    if (cor == 1){
      digitalWrite(led_verde, HIGH);
      tone(buzina, 350);
    }
    if (cor == 2){
      digitalWrite(led_vermelho, HIGH);
      tone(buzina, 550);
    }
    if (cor == 3){
      digitalWrite(led_amarelo, HIGH);
      tone(buzina, 750);
    }
    if (cor == 4){
      digitalWrite(led_azul,HIGH);
      tone(buzina, 950);
    }
    delay(300);
    desligaLeds();
    desligaSom();
    delay(300);
  }
}
