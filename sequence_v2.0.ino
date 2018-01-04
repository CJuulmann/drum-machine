
volatile unsigned int ticks = 0;  
byte index = 0;
byte sequence[] = {0, 0, 0, 0};        //sequence for tempo to loop through
byte stepSequence1[] = {1, 0, 0, 0};   //specified step sequence to mask with
byte stepSequence2[] = {5, 6, 4, 1};   //specified step sequence to mask with


//choice of tempo
int tempo = 80;

void setup() {
  Serial.begin(9600);

  DDRL = B11111111;       //set port L as output LEDs: 42, 43, 44, 45


  //-------------------------------------------------- //
  //    initialize timer1 register channel A and B 
  //-------------------------------------------------- //
  
  //Start timer1 and set CS10, CS11: 1 (prescale 64) and WGM12: 0 (normal port operation)
  TCCR1B |= B00000011; 

  //Setup compare match 
  TCCR1A |= B00000000;

  //Timer/Counter interrupt mask register - enable overflow interrupt on both channels (A and B)
  TIMSK1 |= B00000001;

}
void loop() {
   
    //reset indexer
    if(index > 3){
        index = 0;
      }
      
      switch(tempo){
        case 80:
          //tempo = 80bpm
          if(ticks >= 368){  
            sequencer(stepSequence1);
            index++;
          } 
        break;
        case 100:
          //tempo = 100bpm
          if(ticks == 294){
              sequencer(stepSequence1);
             index++;
            }
        break;
        case 120:
          //tempo = 120bpm
          if(ticks == 245){
              sequencer(stepSequence1);
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
void sequencer(byte *stepArr){

    for(int i = 0; i < 4; i++){            
        sequence[i] = *stepArr;             //assign values of specified step sequence
        stepArr++;
      }
      //Serial.println(sequence[index]);    //test print
      ticks = 0;                            //reset count of ticks
      
      LEDblink();
}

void LEDblink(){
   // PORTL &= B00000000;                   //initialize port
    
  for(int i = 0; i < 4; i++){
      PORTL |= sequence[i];                 //set corrsponding pins HIGH
      Serial.println(PORTL);
      
      //5 -10ms delay with millis()
      PORTL &= B00000000;                   //reset port
    }
}
