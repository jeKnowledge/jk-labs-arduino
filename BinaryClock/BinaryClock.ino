int minLEDs[2][4] = {
    {6, 7, 8, -1},
    {9, 10, 11, 12}
};

int hourLEDs[2][4] = {
    {0, 1, -1, -1},
    {2, 3, 4, 5}
};

int time[6] = {1, 9, 3, 5, 0, 3};
int max[6] = {3, 10, 6, 10, 6, 10};

void setup() {
    Serial.begin(9600);
    // initialize digital pin 13 as an output.
    for(int i = 0; i < 12; i++)
        pinMode(i, OUTPUT);
}

// the loop function runs over and over again forever
void loop(){
    draw_time();
    advance_time();
    //print_time();
    delay(1000);
}

void int_to_led(int val, int *leds){
    int bit;
    for(int i = 0; i < 4; i++){
        digitalWrite(leds[i], LOW);
        bit = val & 1;
        val = val >> 1;
        if(bit)
            digitalWrite(leds[i], HIGH);
    }
}
void advance_time(){
    if(time[0] == 2) max[1] = 4;
    else max[1] = 10;

    for(int i = 5; i >= 0; i--){
        time[i]++;

        if(time[i] != max[i])
            return;
        else
            time[i] = 0;
    }

    if(time[0] == 2 && time[1] == 4){
        time[0] = 0;
        time[1] = 0;
    }
}

void draw_time(){
    int_to_led(time[0], hourLEDs[0]);
    int_to_led(time[1], hourLEDs[1]);
    int_to_led(time[2], minLEDs[0]);
    int_to_led(time[3], minLEDs[1]);
}

void print_time(){
    for(int i = 0; i < 6; i +=2 ){
        Serial.print(time[i]);
        Serial.print(time[i+1]);
        if(i != 4)
        Serial.print(".");
    }
    Serial.println();
}
