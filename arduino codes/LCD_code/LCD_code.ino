//LCD code
//9:20
//2/11/23
//code 3

//importing libraries
#include<Wire.h>
#include<LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

//initialise lcd
void setup() {
  lcd.begin();
  lcd.backlight();

}

//lcd functioning
void loop() {
  //mode 1
  lcd.setCursor(0, 0);
  lcd.print("weight: ");
  lcd.clear();

  //mode 2
  lcd.setCursor(0, 0);
  lcd.print("weight: ");
  lcd.clear();

  //mode 3
  lcd.setCursor(0, 0);
  lcd.print("quantity: ");
  lcd.clear();

  //mode 4
  lcd.setCursor(0, 0);
  lcd.print("liquid: ");
  lcd.clear();

}
