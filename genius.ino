long randNumber;

#define botao_verde 7
#define botao_vermelho 8
#define botao_amarelo 9
#define botao_branco 10
#define led_verde 3
#define led_vermelho 4
#define led_amarelo 5
#define led_branco 6

void setup() {
  pinMode(led_verde, OUTPUT);
  pinMode(led_vermelho, OUTPUT);
  pinMode(led_amarelo, OUTPUT);
  pinMode(led_branco, OUTPUT);
  pinMode(botao_verde, INPUT_PULLUP);
  pinMode(botao_vermelho, INPUT_PULLUP);
  pinMode(botao_amarelo, INPUT_PULLUP);
  pinMode(botao_branco, INPUT_PULLUP);
  randomSeed(analogRead(0));
}

void loop() {
  int lista[20];
  for (int i = 0; i < 20; i++) {
    int num = random(1, 5);
    lista[i] = num;
    ligaLed(num);
    delay(1500);
    desligaLeds();
    delay(500);
  }

  for (int i = 0; i < 20; i++) {
    int botaoPressionado = checarBotao();
    if (botaoPressionado != 0) {
      if (botaoPressionado == lista[i]) {
        ligaLed(botaoPressionado);
        delay(500);
        desligaLeds();
      } else {
        fimJogo();
        break;
      }
    }
  }
}

int checarBotao() {
  if (digitalRead(botao_verde) == LOW) {
    return 1;
  }
  if (digitalRead(botao_vermelho) == LOW) {
    return 2;
  }
  if (digitalRead(botao_amarelo) == LOW) {
    return 3;
  }
  if (digitalRead(botao_branco) == LOW) {
    return 4;
  }
  return 0;
}

void fimJogo() {
  digitalWrite(led_vermelho, HIGH);
  digitalWrite(led_verde, HIGH);
  digitalWrite(led_amarelo, HIGH);
  digitalWrite(led_branco, HIGH);
}

void ligaLed(int cor) {
  digitalWrite(led_verde, cor == 1 ? HIGH : LOW);
  digitalWrite(led_vermelho, cor == 2 ? HIGH : LOW);
  digitalWrite(led_amarelo, cor == 3 ? HIGH : LOW);
  digitalWrite(led_branco, cor == 4 ? HIGH : LOW);
}

void desligaLeds() {
  digitalWrite(led_verde, LOW);
  digitalWrite(led_vermelho, LOW);
  digitalWrite(led_amarelo, LOW);
  digitalWrite(led_branco, LOW);
}
