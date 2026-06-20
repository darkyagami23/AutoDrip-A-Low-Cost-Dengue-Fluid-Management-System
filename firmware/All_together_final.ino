  #include <Arduino.h>
  #include "A4988.h"
  #include <LiquidCrystal_I2C.h>
 
  // Define pins for the stepper motor
  int Step = 3;  // Step pin
  int Sleep = 4;
  int Dire = 2;  // Direction pin
  int MS1 = 7;   // Microstep pin MS1
  int MS2 = 6;   // Microstep pin MS2
  int MS3 = 5;   // Microstep pin MS3

  // Motor specifications
  const int spr = 200;  // Steps per revolution (200 for full-step mode)
  int RPM = 25;         // Motor speed in RPM
  int Microsteps = 3;   // Full-step mode

  // Initialize stepper motor with A4988 driver
  A4988 stepper(spr, Dire, Step, MS1, MS2, MS3);

  // Binary search variables
  int low = 0;          // Initial lower range
  int high = 450;       // Upper range (200 steps per revolution)
  int count = 0;        // Iteration count
  int currentStep = 0;  // Current step position
  int prevGuess = 0;    // Previous guess

  double Stab_duration=30.0;     //stabilization duration

  LiquidCrystal_I2C lcd(0x27, 16, 2);
  // IR sensor variables
  volatile unsigned long time_begin;
  volatile unsigned long time_end;
  volatile int EFR;
  volatile int duration_sec;
  volatile int state;
  volatile int x =0;
  volatile double flow_rate = 0;
  volatile int prev = 0;

  void setup() {

    Serial.begin(9600);
    //Serial.println("Started");
    pinMode(Step, OUTPUT);    //Step pin as output
    pinMode(Dire, OUTPUT);    //Direcction pin as output
    pinMode(Sleep, OUTPUT);   //Set Sleep OUTPUT Control button as output
    digitalWrite(Step, LOW);  // Currently no stepper motor movement
    digitalWrite(Dire, HIGH);
    digitalWrite(Sleep, HIGH);  //A logic high allows normal operation of the A4988 by removing from sleep
    delay(1000);                //Wait 1000 milliseconds (1 second) proceeding
    // Set target motor RPM to and microstepping setting
    stepper.begin(RPM, Microsteps);
    //Serial.println("Outof setup");
  }

  // Function for measuring flowrate using IR that returns up or down or stop
  int measureFlowRate(float efr) {
    time_begin = micros();

    //Serial.println("flow rate loop");
    while (duration_sec <= Stab_duration) {
      //Serial.println("inside while loop  ");
      int counter = digitalRead(A0);
      if (state == 0) {
        switch (counter) {
          case 1:
            state = 1;
            x = x + 1;      
            //Serial.println("Drop count increased  ");
            break;
          case 0:
            state = 0;
            break;
        }
      }

      if (counter == LOW) {
        state = 0;
      }
      time_end = micros();
      //duration=time_end - time_begin;
      duration_sec = (time_end - time_begin) / 1000000.0;
    }
    flow_rate = (x / Stab_duration)*60;
    //Serial.println("flow rate changed");
    time_begin = time_end;
    x = 0;
    duration_sec = 0;

    if (efr < flow_rate) {
      return 1;
    } else if (efr > flow_rate) {
      return 2;
    } else if (efr == flow_rate) {
      return 3;
    }
  }

  // BInary search Function
  int binsearch(int low, int high) {
    // Perform binary search
    int guess = (low + high) / 2;
    int stepsToMove = (guess - currentStep);  // Calculate the difference in steps

    stepper.move(stepsToMove);                 // Move the motor by the calculated steps          // Update the current position

    delay(500);  // Allow time for the motor to stabilize
    // Serial.print("Current guess: ");
    // Serial.println(guess);
    // Serial.print("Steps to Move: ");
    // Serial.println(stepsToMove);

    return guess;
  }


  void loop() {
    // put your main code here, to run repeatedly:
    
    // Serial Input
    //Serial.println("Provide expected Flowrate : ");
    // int userInput = Serial.parseInt();
    // while (Serial.available() > 0) {
    //   Serial.read();  // Clear serial buffer
    // }

    Serial.println("In the loop");
    while(true) { // Check if data is available to read
      if(Serial.available()>0){
        //Serial.println("In the condition");
        String receivedData = Serial.readStringUntil('\n'); // Read until newline character
        EFR = receivedData.toInt(); // Convert the received data to an integer
        Serial.print("Received Number: ");
        Serial.println(EFR); // Print the received number
        break;
      }
    }
    //Serial.println("Out of the loop");
    // EFR = receivedNumber;
    // Inner loop to stabilize flowrate
    // Serial.print("EFR: ");
    // Serial.println(EFR); // Print the received number
    while (count<=8) {
      int flag = measureFlowRate(EFR);
      int currentGuess;
      if (flag == 1) {
        high = currentStep;
        currentStep = binsearch(low, high);
      } 
      else if (flag == 2) {
        low = currentStep;
        currentStep = binsearch(low, high); 
      }

      count++;

      // Serial.print("Iteration ");
      // Serial.print(count);
      // Serial.print(": Current step position approximation is ");
      // Serial.println(currentGuess);

      // Check if the approximation is within an acceptable range
  
      prevGuess = currentGuess;
    }

  }
