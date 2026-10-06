// 7-segment display pins
int a = 7;
int b = 6;
int c = 5;
int d = 11;
int e = 10;
int f = 8;
int g = 9;
int dp = 4;

// Turn all segments off
void clearDisplay() {
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
  digitalWrite(dp, LOW);
}

// Display a number from 0-9
void displayNumber(int number) {
  clearDisplay();

  switch (number) {

    case 0:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      break;

    case 1:
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      break;

    case 2:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(g, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(d, HIGH);
      break;

    case 3:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(g, HIGH);
      break;

    case 4:
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      break;

    case 5:
      digitalWrite(a, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      break;

    case 6:
      digitalWrite(a, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(c, HIGH);
      break;

    case 7:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      break;

    case 8:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(e, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;

    case 9:
      digitalWrite(a, HIGH);
      digitalWrite(b, HIGH);
      digitalWrite(c, HIGH);
      digitalWrite(d, HIGH);
      digitalWrite(f, HIGH);
      digitalWrite(g, HIGH);
      break;
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(dp, OUTPUT);

  clearDisplay();
}

void loop() {

  if (Serial.available() > 0) {

    String message = Serial.readStringUntil('\n');
    message.trim();

    Serial.print("Received: ");
    Serial.println(message);

    if (message == "0") {
      displayNumber(0);
    }
    else if (message == "1") {
      displayNumber(1);
    }
    else if (message == "2") {
      displayNumber(2);
    }
    else if (message == "3") {
      displayNumber(3);
    }
    else if (message == "4") {
      displayNumber(4);
    }
    else if (message == "5") {
      displayNumber(5);
    }
    else if (message == "6") {
      displayNumber(6);
    }
    else if (message == "7") {
      displayNumber(7);
    }
    else if (message == "8") {
      displayNumber(8);
    }
    else if (message == "9") {
      displayNumber(9);
    }
    else if (message == "off") {
      clearDisplay();
    }
  }
}
