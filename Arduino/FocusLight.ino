
int LED_R = 4;
int LED_G = 2;
int LED_B = 3;
int chr = 0; 

void setup() {
  Serial.begin(9600);
  Serial.println("FocusLight Initialization...");
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  Serial.println("FocusLight Ready");
}

void loop() {

  if (Serial.available() > 0) {
    chr = Serial.read();
    if (chr == 73) { // I : Infos
      Serial.println("FocusLight v0.1");
    }
    else if (chr == 82) { // R : Red
      setRGB(HIGH, LOW, LOW);
      Serial.println("Red");
    }
    else if (chr == 71) { // G : Green
      setRGB(LOW, HIGH, LOW);
      Serial.println("Green");
    }
    else if (chr == 66) { // B : Blue
      setRGB(LOW, LOW, HIGH);
      Serial.println("Blue");
    }
    else if (chr == 76) { // L : Light Blue
      setRGB(LOW, LOW, LOW);
      analogWrite(LED_B, 64);
      Serial.println("LightBlue");
    }
    else if (chr == 89) { // Y : Yellow
      setRGB(HIGH, HIGH, LOW);
      Serial.println("Yellow");
    }
    else if (chr == 77) { // M : Magenta
      setRGB(HIGH, LOW, HIGH);
      Serial.println("Magenta");
    }
    else if (chr == 67) { // C : Cyan
      setRGB(LOW, HIGH, HIGH);
      Serial.println("Cyan");
    }
    else if (chr == 87) { // W : White
      setRGB(HIGH, HIGH, HIGH);
      Serial.println("White");
    }
    else if (chr == 79) { // O : Off
      setRGB(LOW, LOW, LOW);
      Serial.println("Off");
    }
    else { 
      Serial.println(chr, DEC);
    }
  }
  
}

void setRGB(int red, int green, int blue) {
  digitalWrite(LED_R, red);
  digitalWrite(LED_G, green);
  digitalWrite(LED_B, blue);
}

