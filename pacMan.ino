#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte pac1[8] = {
	B11000,
	B11100,
	B11110,
	B10000,
	B11110,
	B11100,
	B11000,
	B00000
};

byte pac2[8] = {
	B11110,
	B11000,
	B10000,
	B10000,
	B10000,
	B11000,
	B11110,
	B00000
};

byte pac3[8] = {
	B00011,
	B00111,
	B01111,
	B00001,
	B01111,
	B00111,
	B00011,
	B00000
};

byte pac4[8] = {
	B01111,
	B00011,
	B00001,
	B00001,
	B00001,
	B00011,
	B01111,
	B00000
};

byte pac[8] = {
	B00001,
	B00011,
	B00111,
	B00111,
	B00111,
	B00011,
	B00001,
	B00000
};

byte pacR[8] = {
	B10000,
	B11000,
	B11100,
	B11100,
	B11100,
	B11000,
	B10000,
	B00000
};

const int pacB = 1;
const int pacBr = 2;
const int pacH1 = 3;
const int pacH2 = 4;
const int pacH1r = 5;
const int pacH2r = 6;

const int upB = 10;
const int downB = 9;
const int leftB = 8;
const int rightB = 7;

const bool right = true;
const bool left = false;

int X = 0;
int Y = 0;
bool state = true;
bool direction = right;

int pointX = 0;
int pointY = 0;

int score = 0;
int timer = 20;

bool game = true;

void setup() {
	lcd.begin(16, 2);

	lcd.createChar(pacH1,pac1);
	lcd.createChar(pacH2,pac2);
	lcd.createChar(pacH1r,pac3);
	lcd.createChar(pacH2r,pac4);
	lcd.createChar(pacB,pac);
	lcd.createChar(pacBr,pacR);

	setPoint();
}

void loop() {
	readButton();
	checkEat();
	animate(X,Y,direction);
	if(millis() / 1000 > timer){
		game = false;
		lcd.setCursor(0,0);
		lcd.write("Game Over,score:");
		lcd.setCursor(0,1);
		lcd.print(score);

	}
	delay(100);
}

void checkEat(){
	int faceX = direction ? X + 1 : X;
	if(pointX == faceX && pointY == Y && game){
		score++;
		setPoint();
	}
}

void setPoint() {
	do{
		pointX = random(16);
		pointY = random(2);
	}while(pointX == X && pointY == Y);

	lcd.setCursor(pointX,pointY);
	lcd.write("*");
}

void readButton() {
	lcd.setCursor(X,Y);
	if(digitalRead(upB) == HIGH && Y > 0){
		lcd.write("  ");
		Y--;
	}
	if(digitalRead(downB) == HIGH && Y < 1){
		lcd.write("  ");
		Y++;
	}
	if(digitalRead(rightB) == HIGH && X < 14){
		if(direction != right){
			direction = right;
			return;
		}
		lcd.write(" ");
		X++;
	}
	if(digitalRead(leftB) == HIGH && X > 0){
		if(direction != left){
			direction = left;
			return;
		}
		lcd.setCursor(X+1,Y);
		lcd.write(" ");
		X--;
	}

}

void animate(int x, int y, bool dir) {
	// x = x > 14 ? 14 : x;
	// x = x < 0 ? 0 : x;
	// y = y > 1 ? 1 : y;
	// y = y < 0 ? 0 : y;

	lcd.setCursor(x,y);

	if(dir){
		draw(pacB);
		draw(state ? pacH1 : pacH2);
	} else {
		draw(state ? pacH1r : pacH2r);
		draw(pacBr);
	}
	state = !state;
}

void draw(int b) { lcd.write(byte(b)); }
