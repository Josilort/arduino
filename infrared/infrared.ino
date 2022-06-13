const int sendenpin = 8;
const int empfangenpin = 12;
unsigned long startmillis;

const int databitcount = 8;
const int baud = 9600; // in bit/s
float timeperbit; // in ms

// bits
const int parity = 1; // 1 => even; 0 => odd; doesn't do anything at the moment!
int bits[databitcount + 3];

void setup() {
    Serial.begin(9600);

    pinMode(sendenpin, OUTPUT);
    pinMode(empfangenpin, INPUT);

    timeperbit = 1000 / float(baud); // in the program the time a bit lasts in the transfer is used
    //Serial.println(timeperbit); // debug
}

void empfangen() {
    bits[0] = 1; // Startbit
    startmillis = millis();
    while(millis() < (startmillis + timeperbit)) {}

    for(int i = 0; i < databitcount; i++) { // for-loop in range of databits
        unsigned long milli0 = millis(); // time at the start of bit
        //Serial.println(String(milli0)); // debug

        while (millis() < (milli0 + (timeperbit / 2))) {} // wait until the middle of a bit
        bits[i + 1] = digitalRead(empfangenpin); // save the value of the bit    
        
        while(millis() < milli0 + timeperbit) {} // wait until the next bit starts
        //Serial.println(bits[i]); // debug
    }
    bits[databitcount + 1] = isparityeven(); // Paritybit
    bits[databitcount + 2] = 0; // Stoppbit

    for (int i = 0; i < databitcount + 3 ; i++) {
        Serial.print(bits[i]);
    } // debug */
    //Serial.println(""); // debug
    //Serial.println(isparityeven()); // debug
}

boolean isparityeven() {
    int count = 0;
    for (int i = 0 + 1 ; i < databitcount + 1 ; i++) {
        if (bits[i] == 1) {count++;}
    }
    //Serial.println(count); // debug

    if (count % 2) {return false;}
    else {return true;}
}

void loop() {
    if (digitalRead(empfangenpin) == HIGH) { // checking for startbit
        Serial.println("");
        empfangen();
        Serial.print("\n");
    }
}