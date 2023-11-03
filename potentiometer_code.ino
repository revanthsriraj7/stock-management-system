//potentiometer code
//7:30
//2/11/23
//code 1

void setup() {
  pinMode(A0, INPUT); // potpin connected to A0 pin
}

void loop() {
  int counter = analogRead(A0);  // taking analog input from pot
  //mode 1 based on pot value
  if (counter >= 50 && counter <= 299)
  {
      Serial.println("MODE 1");
  }
  //mode 2
  else if (counter >= 300 && counter <= 599)
  {
      Seral.println("MODE 2");
  }
  // mode 3
  else if (counter >= 600 && counter <= 899)
  {
      Serial.println("MODE 3");
  }
  //mode 4
  else if (counter >= 900 && counter <= 1204)
  {
      Serial.println("MODE 4");
  }

}
