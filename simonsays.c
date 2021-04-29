// pin map

// led (OUT)
const unsigned short led_red = 9;
const unsigned short led_blue = 8;
const unsigned short led_yellow = 7;
const unsigned short led_green = 6;

// switch (IN)
const unsigned short switch_red = 4;
const unsigned short switch_blue = 0;
const unsigned short switch_yellow = 2;
const unsigned short switch_green = 3;

void setup() {

  Serial.begin(9600);
  
  pinMode(led_red, OUTPUT);
  pinMode(led_blue, OUTPUT);
  pinMode(led_yellow, OUTPUT);
  pinMode(led_green, OUTPUT);

  pinMode(switch_red, INPUT_PULLUP);
  pinMode(switch_blue, INPUT_PULLUP);
  pinMode(switch_yellow, INPUT_PULLUP);
  pinMode(switch_green, INPUT_PULLUP);

  Serial.print("Ready");

  blink(300);
  delay(500);

}

// mode 0 = plays the pattern
// mode 1 = collects input
unsigned short mode = 0;

unsigned short gameround = 1;

unsigned short positioninpattern = 0;
short lastguess = -1;

// this should be random...
unsigned short pattern[8] = {led_red, led_green, led_green, led_blue, led_red, led_yellow, led_red, led_yellow};

void loop() {

  if(mode == 0)
  {
    playPattern();  
  }

  else if(mode == 1)
  {
    short input = -1;
  
    resetLED();

    input = readInput();

    //Serial.print(input);
    if(input > -1)
    {
      digitalWrite(switchToLED(input), HIGH);
      lastguess = input;
        
      delay(300);
    }
    
    else
    {
      if(lastguess > -1)
      {
         Serial.print(lastguess);
         if(switchToLED(lastguess) == pattern[positioninpattern])
         {
          Serial.print("good!"); 
          positioninpattern++;
         }
         else
         {
          Serial.print("bad!"); 
          blink(3000);
          gameround = 1;
          mode = 0;
          positioninpattern = 0;
          delay(1500);
         }

         if(positioninpattern == gameround)
         {
            gameround++;
            mode = 0;
            positioninpattern = 0;
            delay(1000); 
         }

         if(gameround == 9)
         {
            win();
            gameround = 1; 
         }
         
         lastguess = -1;
      }

      
    }
  }

}

void playPattern()
{
  for(unsigned short i= 0 ; i < gameround; i++)
  {
    flashLED(pattern[i]);  
  }

  mode = 1;
}

int switchToLED(unsigned short swtch)
{
  switch(swtch)
  {
    case switch_red:
      return led_red;
    case switch_blue:
      return led_blue;
    case switch_yellow:
      return led_yellow;
    case switch_green:
      return led_green;
  }  
}

int readInput()
{
    short sense_red = digitalRead(switch_red);
    short sense_blue = digitalRead(switch_blue);
    short sense_yellow = digitalRead(switch_yellow);
    short sense_green = digitalRead(switch_green);

    if(sense_red == 0)
    {
      return switch_red; 
    }
    if(sense_blue == 0)
    {
      return switch_blue;
    }
    if(sense_yellow == 0)
    {
      return switch_yellow; 
    }
    if(sense_green == 0)
    {
      return switch_green; 
    }

    return -1;
}

void win()
{
  for(unsigned short i = 0; i < 4; i++)
  {
    digitalWrite(led_red, LOW);
    digitalWrite(led_blue, LOW);
    digitalWrite(led_yellow, LOW);
    digitalWrite(led_green, LOW);
    
    switch(i)
    {
      
      case 0:
        digitalWrite(led_red, HIGH);
        break;
      case 1:
        digitalWrite(led_blue, HIGH);
        break;
      case 2:
        digitalWrite(led_yellow, HIGH);
        break;
      case 3:
        digitalWrite(led_green, HIGH);
        break;
  
  
    }
    
    delay(250);
  }

  blink(250);
  blink(250);

}

void flashLED(unsigned short LED)
{
    resetLED();

    digitalWrite(LED, HIGH);

    delay(500);

    resetLED();

    delay(200);
    
}

void resetLED()
{
    digitalWrite(led_red, LOW);
    digitalWrite(led_blue, LOW);
    digitalWrite(led_yellow, LOW);
    digitalWrite(led_green, LOW);  
}

void blink(unsigned int duration)
{
    resetLED();
    
    digitalWrite(led_red, HIGH);
    digitalWrite(led_blue, HIGH);
    digitalWrite(led_yellow, HIGH);
    digitalWrite(led_green, HIGH);

    delay(duration);

    resetLED();
 
}
