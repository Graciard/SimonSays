#include <Keypad.h>

int redPin = A5;
int greenPin = A4;
int bluePin = A3;

int a = 2;
bool new_test;

int password[5];
int counter;

const byte rows = 3; //three rows
const byte cols = 3; //three columns
char keys[rows][cols] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
};
byte rowPins[rows] = {2,3,4}; //connect to the row pinouts of the keypad
byte colPins[cols] = {A0, A1, A2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols ); //Set Keys

char key; //receives pressed key
int input; //converts key to int
bool failed; //fail state

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  for(int i = 2; i<13; i++)
  {
    pinMode(i, OUTPUT);
  }

  
  //ledtest
  /*
  for(int j = 5; j<=13; j++)
    {
      digitalWrite(j, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(500);                       // wait for a second
      digitalWrite(j, LOW);    // turn the LED off by making the voltage LOW
      delay(500);                       // wait for a second}
    }
  */
    
  new_test = 1;
  failed = 0;

  setColor(0,0,0);
  
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {

  //Creates new Random Pattern
  if(new_test)
  {
    Serial.println("Generating Test");
    delay(1000);
    
    // randomSeed() will then shuffle the random function.
    randomSeed(analogRead(0));
    
    for(int i = 0; i<5; i++)
    {     
      password[i] = random(5,13);
    }
        
    failed = 0;
    new_test = 0;
  }
  
  Serial.println("Start");
  delay(1000);
  //Simon Says Game
  for(int i = 0; i<5; i++)//current round
  {
    for(int j = 0; j<=i; j++) // dispaly current rounds pattern
    {
      digitalWrite(password[j], HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(1000);                       // wait
      digitalWrite(password[j], LOW);    // turn the LED off by making the voltage LOW
      if(j<i)
      {
        delay(1000);
      }
    }
      
      counter = 0;
      while (counter <= i)
      {
        key = keypad.waitForKey();
        input = key-44;
        Serial.println(input);

        if(input == password[counter])
        {
          counter++;
          digitalWrite(greenPin, HIGH);   // turn the LED on (HIGH is the voltage level)
          delay(500);                       // wait for a second
          digitalWrite(greenPin, LOW);    // turn the LED off by making the voltage LOW
        }
        else
        {
          failed = 1;
          digitalWrite(redPin, HIGH);   // turn the LED on (HIGH is the voltage level)
          delay(3000);                       // wait
          digitalWrite(redPin, LOW);    // turn the LED off by making the voltage LOW
          delay(1000);
          break;
        }
      }
      if(failed)
      {
        Serial.println("New Test");
        delay(1000);
        new_test = 1;
        break;
      }
      delay(1000);
  }
  
  while(!new_test)
  {
    int color[3]{255,255,255};

    for (int fade = 0; fade < 3; fade += 1)
    {
      setColor(0, 0, 255); // Blue
      delay(1000);
      setColor(0, 0, 0); // OFF
      delay(500);
      setColor(0, 255, 0); // Green
      delay(1000);
      setColor(0, 0, 0); // OFF
      delay(500);
      setColor(0, 255, 255); // Aqua
      delay(1000);
      setColor(0, 0, 0); // OFF
      delay(500);
      setColor(255, 0, 0); // Red
      delay(1000);
      setColor(0, 0, 0); // OFF
      delay(500);
      setColor(255, 0, 255); // Light Purple
      delay(1000);
      setColor(0, 0, 0); // OFF
      delay(500);
      setColor(255, 255, 0); // Yellow     
      delay(1000);
      setColor(0, 0, 0); // OFF
      delay(500);
      setColor(255, 255, 255); //white
      delay(1000);
      setColor(0, 0, 0); // OFF
      delay(500);
    }
  } 
}

void setColor(unsigned int red, unsigned int green, unsigned int blue)
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
 }
