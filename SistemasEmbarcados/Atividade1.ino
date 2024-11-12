const int buttonOne = 2;
const int buttonTwo = 4;
const int buttonThree = 7;
const int ledOne = 8;
const int ledTwo = 12;
const int ledThree = 13;
const int buzzerPin = 6;

int buttonOneState;
int buttonTwoState;
int buttonThreeState;
int buzzerState;
int lastButtonOneState = LOW;
int lastButtonTwoState = LOW;
int lastButtonThreeState = LOW;
int lastBuzzerState = LOW;

int password[3] = {1, 2, 3};
int userInputs[3] = {0, 0, 0};
int inputIndex = 0;
int inputCount = 0;

unsigned long debounceDelay = 10;
unsigned long lastDebounceTime = 0;
unsigned long currentTime = 0;

void setup() {
  pinMode(buttonOne, INPUT);
  pinMode(buttonTwo, INPUT);
  pinMode(buttonThree, INPUT);
  pinMode(ledOne, OUTPUT);
  pinMode(ledTwo, OUTPUT);
  pinMode(ledThree, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  Serial.println("Aperte a sequência correta de botões para continuar...");
	
  inputIndex = 0;
  inputCount = 0;
  
  while (inputCount < 3) {
    readPassword();
  }

  if (!verifyPassword()) {
    Serial.println("Senha incorreta!");
  }
  else {
    Serial.println("Senha correta, bem-vindo!");
    mainMenu();
  }

}

void blinkLed(const int led) {
  digitalWrite(led, HIGH);
  currentTime = millis();
  
  while (millis() - currentTime <= 100) {
  }
  
  digitalWrite(led, LOW);
}

bool verifyPassword() {
    for (int i = 0; i < 3; i++) {
      if (userInputs[i] != password[i]) {
        return false;
      }
    }

    return true;
}

void readPassword() {
  int _btnOneStt = digitalRead(buttonOne);
  int _btnTwoStt = digitalRead(buttonTwo);
  int _btnThreeStt = digitalRead(buttonThree);

  if ((_btnOneStt != lastButtonOneState) | (_btnTwoStt != lastButtonTwoState) | (_btnThreeStt != lastButtonThreeState)) {
    lastDebounceTime = millis();
    Serial.println("Botao pressionado");
  }
	
  if (millis() - lastDebounceTime > debounceDelay) {
    if (_btnOneStt == HIGH && lastButtonOneState == LOW) {
      userInputs[inputIndex] = 1;
      inputIndex++;
      inputCount++;
      Serial.println("Botão 1 apertado.");
      blinkLed(ledOne);
    }
    else if (_btnTwoStt == HIGH && lastButtonTwoState == LOW) {
      userInputs[inputIndex] = 2;
      inputIndex++;
      inputCount++;
      Serial.println("Botão 2 apertado.");
      blinkLed(ledTwo);
    }
    else if (_btnThreeStt == HIGH && lastButtonThreeState == LOW) {
      userInputs[inputIndex] = 3;
      inputIndex++;
      inputCount++;
      Serial.println("Botão 3 apertado.");
      blinkLed(ledThree);
    }

    lastButtonOneState = _btnOneStt;
    lastButtonTwoState = _btnTwoStt;
    lastButtonThreeState = _btnThreeStt; 
  }
}

void mainMenu() {
  while(true) {
    Serial.println("Pressione (a) para alterar a senha.");
    Serial.println("Pressione (b) para visualizar a senha atual.");
    Serial.println("Pressione (c) para ligar/desligar o buzzer.");
    Serial.println("Pressione (d) para logout.");

    if (Serial.available() > 0) {
      char currentOption = Serial.read();

      switch(currentOption) {
        case 'a':
          changePassword();
          break;
        case 'b':
          showPassword();
          break;
        case 'c':
          buzzer();
          break;
        case 'd':
          return;
          break;
        default:
          break;  
      }
    }
  }
}

void changePassword() {
  inputIndex = 0;

  Serial.println("Pressione o primeiro digito da senha:");
  readPassword();
  Serial.println("Pressione o segundo digito da senha:");
  readPassword();
  Serial.println("Pressione o terceiro digito da senha:");
  readPassword();

  for (int i = 0; i < 3; i++) {
    password[i] = userInputs[i];
  }
}

void showPassword() {
  Serial.print("Senha atual: botão ");
  Serial.print(password[0]);
  Serial.print(", botão ");
  Serial.print(password[1]);
  Serial.print(", botão ");
  Serial.print(password[2]);
  Serial.print(".\n");
}

void buzzer() {
  if (buzzerState == LOW) {
    Serial.println("Buzzer ligado!");
    buzzerState = HIGH;
    digitalWrite(buzzerPin, buzzerState);
  } 
  else {
    Serial.println("Buzzer desligado!");
    buzzerState = LOW;
    digitalWrite(buzzerPin, buzzerState); 
  }
}