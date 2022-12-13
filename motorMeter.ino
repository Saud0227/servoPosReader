// Carl Johan Ståhl & Emil "Henrik" Bergman 2B
// Servo Pos Reader

// https://github.com/users/Saud0227/projects/1

#include <Keyboard.h>

#define PIEZO_PORT 7

int readPins[8] = {A0, A1, A2, A3, A4, A5, 3, 5};

// <Rick roll section>

volatile int beatLength = 100; // determines tempo
float beatSeparationConstant = 0.3;

#define a4f 415 // 415 Hz
#define b4f 466 // 466 Hz
#define c5 523  // 523 Hz
#define c5s 554 // 554 Hz
#define e5f 622 // 622 Hz
#define f5 698  // 698 Hz
#define a5f 831 // 831 Hz
#define rest -1

int songNotes[] =
    {b4f, b4f, a4f, a4f,
     f5, f5, e5f, b4f, b4f, a4f, a4f, e5f, e5f, c5s, c5, b4f,
     c5s, c5s, c5s, c5s,
     c5s, e5f, c5, b4f, a4f, a4f, a4f, e5f, c5s,
     b4f, b4f, a4f, a4f,
     f5, f5, e5f, b4f, b4f, a4f, a4f, a5f, c5, c5s, c5, b4f,
     c5s, c5s, c5s, c5s,
     c5s, e5f, c5, b4f, a4f, rest, a4f, e5f, c5s, rest};

int songTime[] =
    {1, 1, 1, 1,
     3, 3, 6, 1, 1, 1, 1, 3, 3, 3, 1, 2,
     1, 1, 1, 1,
     3, 3, 3, 1, 2, 2, 2, 4, 8,
     1, 1, 1, 1,
     3, 3, 6, 1, 1, 1, 1, 3, 3, 3, 1, 2,
     1, 1, 1, 1,
     3, 3, 3, 1, 2, 2, 2, 4, 8, 4};

// <!Rick roll section>

int button_IN = 4;

void setup(){
    pinMode(PIEZO_PORT, 1);
    Serial.begin(12500);
    delay(1000);
    // pinMode(13, 1);
    Keyboard.begin();
}

bool buttonPressed(){
    // kollar om knappen trycks ned
    return digitalRead(button_IN) == 1;
}

bool readVal(int iToRead){
    int Value = analogRead(readPins[iToRead]);
    // Serial.print("Analog read: ");
    // Serial.println(Value);
    return (Value < 500);
}

int getPos(){
    // IN:  No params in the function but uses the length of the global array in addition as the helper function readVal.
    // OUT: Integer between 0-255-
    // DO:  Reads every part of the greycode like an binary number and generates an val
    byte outCode = 0;
    for (byte i = 0; i < 8; i++){
        byte iVal = readVal(i) * 1;
        // Serial.print(iVal);
        outCode += pow(2, 7 - i) * iVal;
    }



    delay(200);
    return (outCode);
}

void writeOut(int toWrite){
    // IN:  String to type in the computer.
    // OUT: Nothing, void function.
    // DO:  Writes the string 
    Keyboard.print(toWrite);
}

void rick(){
    // IN:  Nothing
    // OUT: Nothing, void function.
    // DO:  Halts execution to rick roll everyone


    int cTime = 0;
    // Serial.print("!");
    while (cTime <= sizeof(songNotes) / sizeof(int)){
        // Serial.print(cTime);

        int noteLength = beatLength * songTime[cTime];
        // chorus

        if (songNotes[cTime] > 0){
            tone(PIEZO_PORT, songNotes[cTime], noteLength);
        }
        delay(noteLength);
        noTone(PIEZO_PORT);
        delay(noteLength * beatSeparationConstant);
        cTime++;
    }
}



void loop(){
    while (true){

        if (!buttonPressed()){
            break;
        }

        Serial.print(getPos());

        tone(PIEZO_PORT, 1000);
        delay(250);
        noTone(PIEZO_PORT);
        delay(250);
    }
    // delay(500);
    // writeOut(1020);
    // delay(500);


    // rick();
}
