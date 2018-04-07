volatile bool BUTTON_state = false;

void button_pressed() {
  noInterrupts();
  BUTTON_state = true;
  interrupts();
}

void setup() {
  Serial.begin(115200);

  attachInterrupt(D3, button_pressed, FALLING); //CHANGE, RISING, FALLING Lógica inversa
}

void loop() {
  while (!BUTTON_state)
    yield();

  Serial.println("botón pulsado");  
  BUTTON_state = false;
}
