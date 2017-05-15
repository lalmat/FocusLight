
int LED_R = 3;
int LED_G = 5;
int LED_B = 6;
int rgb[3];
String data = ""; 

void setup() {
  Serial.begin(115200);
  Serial.println("FocusLight Initialization...");
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  Serial.println("FocusLight Ready");
  Serial.setTimeout(10);
}

void loop() {

  int i;
  int cut;
  String rs;

  if (Serial.available() > 0) {
    data = Serial.readString();
    
    for (i=0; i<2; i++) {
      rgb[i] = data.substring(0,data.indexOf(';')).toInt();
      data = data.substring(data.indexOf(';')+1);
    }
    rgb[2] = data.toInt();

    analogWrite(LED_R, rgb[0]);
    analogWrite(LED_G, rgb[1]);
    analogWrite(LED_B, rgb[2]);
  } 
}

