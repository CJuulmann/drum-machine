#define LED1 34
#define LED2 36
#define LED3 38
#define LED4 40

volatile unsigned int ticks = 0;  
byte index = 0;
byte sequence[] = {LED1, LED2, LED3, LED4};

//choice of tempo
int tempo = 80;

void setup() {
  Serial.begin(9600);
  
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);


  //-------------------------------------------------- //
  //    initialize timer1 register channel A and B 
  //-------------------------------------------------- //
  
  //Start timer1 by writing to CS10 bit (clock select) with prescaling of 64
  //F0C1A: 0, F0C1B: 0, -, -, WGM12: 0, CS12: 0, CS11: 1, CS10: 1
  TCCR1B |= B00000011; 

  //Setup compare match 
  TCCR1A |= B00000000;

  //Timer/Counter interrupt mask register - enable overflow interrupt on both channels (A and B)
  TIMSK1 |= B00000001;

}
void loop() {
   
    //reset indexer
    if(index > 1){
        index = 0;
      }
      
      switch(tempo){
        case 80:
          //tempo = 80bpm
          if(ticks >= 368){  
            sequencer(index);
            index++;
          } 
        break;
        case 100:
          //tempo = 100bpm
          if(ticks == 294){
             sequencer(index);
             index++;
            }
        break;
        case 120:
          //tempo = 120bpm
          if(ticks == 245){
              sequencer(index);
              index++;
            }
        break;
        default:
        break;    
      }
}

//timer overflow triggers an interrupt which we use to increment
//the count of ticks in one cylce
ISR(TIMER1_OVF_vect) {
  ticks++;
}

//move through array
void sequencer(byte index) {
     byte *indexPtr = &sequence[index];
    
    //Serial.println(*indexPtr);      
    LEDblink(indexPtr);
    ticks = 0;                            //reset count of ticks
}
void LEDblink(byte *iPtr){
  
  //digitalWrite(*iPtr, HIGH);
  Serial.println(*iPtr);

  for(sizeof(iPtr); sizeof(iPtr) < sizeof(sequence); iPtr++){
      //digitalWrite(*iPtr, LOW);
      Serial.println(*iPtr);
    }
  /*if(sizeof(iPtr) > sizeof(sequence) ){
      iPtr--;
      //digitalWrite(*iPtr, LOW);
      Serial.println(*iPtr);

    }
    if(sizeof(iPtr) < sizeof(sequence)){
      iPtr++;
       //digitalWrite(*iPtr, LOW);
       Serial.println(*iPtr);
      }
      */
}
