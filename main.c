#include <XInput.h>

// Botões
const int pinY      = 2;
const int pinB      = 3;
const int pinX      = 4;
const int pinA      = 6;
const int pinRT     = 8;
const int pinLT     = 9;
const int pinStart  = 10;
const int pinSelect = 15;

// Analógico esquerdo
const int pinLX = A3; // Eixo X esquerdo
const int pinLY = A2; // Eixo Y esquerdo

void setup() {
  // Inicia XInput
  XInput.begin();

  // Configura botões como entrada pullup
  pinMode(pinY,      INPUT_PULLUP);
  pinMode(pinB,      INPUT_PULLUP);
  pinMode(pinX,      INPUT_PULLUP);
  pinMode(pinA,      INPUT_PULLUP);
  pinMode(pinRT,     INPUT_PULLUP);
  pinMode(pinLT,     INPUT_PULLUP);
  pinMode(pinStart,  INPUT_PULLUP);
  pinMode(pinSelect, INPUT_PULLUP);
}

void loop() {
  // --- Botões principais ---
  XInput.setButton(BUTTON_Y,      digitalRead(pinY) == LOW);
  XInput.setButton(BUTTON_B,      digitalRead(pinB) == LOW);
  XInput.setButton(BUTTON_X,      digitalRead(pinX) == LOW);
  XInput.setButton(BUTTON_A,      digitalRead(pinA) == LOW);
  XInput.setButton(BUTTON_START,  digitalRead(pinStart) == LOW);
  XInput.setButton(BUTTON_BACK,   digitalRead(pinSelect) == LOW);

  // --- Gatilhos (RT/LT) ---
  XInput.setTrigger(TRIGGER_RIGHT, digitalRead(pinRT) == LOW ? 255 : 0);
  XInput.setTrigger(TRIGGER_LEFT,  digitalRead(pinLT) == LOW ? 255 : 0);

  // --- Analógico esquerdo ---
  int lx = analogRead(pinLX);
  int ly = analogRead(pinLY);

  // Normaliza de 0–1023 para -32768 até 32767
  lx = map(lx, 0, 1023, 32767, -32768);
  ly = map(ly, 0, 1023, -32768, 32767);

  // Define eixo do analógico esquerdo
  XInput.setJoystick(JOY_LEFT, lx, ly);

  // Atualiza estado
  XInput.send();
  
  delay(5);
}
