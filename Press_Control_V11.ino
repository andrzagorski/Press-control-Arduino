#include <Stepper.h>
int limit_1;
int limit_2;
const int stepsPerRevolution=200;
const int RPM=100;
int dir_mov=1;
int active=1;
bool end=0;
Stepper myStepper = Stepper(stepsPerRevolution,8,9,10,11);

void setup() {
  myStepper.setSpeed(RPM);
  Serial.begin(9600);
  
  pinMode(5,INPUT_PULLUP); // Activator Switch
  pinMode(6,INPUT_PULLUP);  // LIM_1
  pinMode(7,INPUT_PULLUP); // LIM_2
}

 void   motion() {
    myStepper.step(50*dir_mov);
  }
  
void change_dir() {
  dir_mov*=-1;
 }

void loop() {


  limit_1=digitalRead(6);
  limit_2=digitalRead(7);
  active=digitalRead(5);
  end=active;
  if(active==0) {
  while(end==0) {

     if(limit_1==0&&limit_2==1) {  // aktywna krancowka port 6 // gorna
      while(limit_2==1) { // krec dopoki nie aktywuje sie krancowka 7
        motion();
          limit_1=digitalRead(6);
          limit_2=digitalRead(7);
      }
       change_dir(); // po aktywacji krancowki 7 zmien kierunek obrotu
       delay(3000);
  }
  
       if(limit_1==1&&limit_2==0) {  // aktywna krancowka port 7
   // change_dir(); // zmien kierunek
      while(limit_1==1) { // krec dopoki nie aktywuje sie krancowka 6
        motion();
          limit_1=digitalRead(6);
          limit_2=digitalRead(7);
      }
      end=1;
  }

  }
  }
}
