#include "IRremote.h" //Βιβλιοθήκη για το IR Receiver
#include <Servo.h> //Βιβλιοθήκη για την εισαγωγή αντικειμένου servo
Servo myservo;  // Φτιάχνει ένα αντικείμενο servo που χρησιμοποιείται για την στροφή του μηχατρονίου

int receiver = 2; //Βάζουμε το IR Receiver στο pin 2

const int trigPin1 =10; //Σταθερές μεταβλητές για τους ultrasonic αισθητήρες
const int echoPin1 =A1;
const int trigPin2 =9;
const int echoPin2 =A2;
const int trigPin3 =12;
const int echoPin3 =A3;
const int trigPin4 =13;
const int echoPin4 =A4;

const int motorA1 =5; //Δύο pins για τον έλεγχο του DC κινιτήρα 
const int motorA2 =6; //Είναι τα pins που συνδέονται με τον driver

//Μεταβλητές για την απόσταση
long distance1 ;//Μπροστά ασθητήριο
long distance2 ;//Μπροστά αριστερά ασθητήριο
long distance3 ;//Πίσω δεξιά ασθητήριο
long distance4 ;//Πίσω αισθητήριο

bool turn = LOW ;           //Μεταβλητή κατάστασης Στροφής
bool search = LOW ;         //Μεταβλητή κατάστασης αναζήτησης παρκαρίσματος
bool parking = LOW ;        //Μεταβλητή κατάστασης εκκίνησης παρκαρίσματος
bool parkingFinal = LOW ;   //Μεταβλητή κατάστασης τελικής ρύθμισης παρκαρίσματος
bool thesi = LOW;           //Μεταβλητή μνήμης εντοπισμού θέσης παρκαρίσματος

IRrecv irrecv(receiver);           
decode_results results;           


void setup() 
{ 
  
  irrecv.enableIRIn(); // Ξεκίνημα του IR Receiver
  
  pinMode(motorA1, OUTPUT);   // του DC κινητήρα
  pinMode(motorA2, OUTPUT);
  
  pinMode(trigPin1, OUTPUT);  //Τα triggers των 4 αισθητηρίων
  pinMode(trigPin2, OUTPUT);  
  pinMode(trigPin3, OUTPUT);  
  pinMode(trigPin4, OUTPUT);  
  
  pinMode(echoPin1, INPUT);   //Τα echoes των 4 αισθητηρίων
  pinMode(echoPin2, INPUT);
  pinMode(echoPin3, INPUT);
  pinMode(echoPin4, INPUT);

  myservo.attach(8);          //Βάζει τον έλεγχο του servo στο pin 8

} 

long ultrasound_distance(long trigPin,long echoPin){  //Συνάρτηση για την μέτρηση απόστασης
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(.3);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  delay(60);                //Ορισμένος χρόνος delay ώστε να μην έχουμε αλλίαση 
  return distance;
}

//Συναρτήσεις προκαθορισμένων κινήσεων


/***********************Forward****************************/
void forward(int vspeed) {
    	analogWrite(motorA1, vspeed); analogWrite(motorA2, 0);
        myservo.write(92);
}
    
/***********************Backward****************************/
void backward(int vspeed) {
    	analogWrite(motorA1, 0);   analogWrite(motorA2, vspeed);
        myservo.write(92);
    }

/***********************STOP****************************/
void STOP() {
    	analogWrite(motorA1, 0);   analogWrite(motorA2, 0); 
        myservo.write(92);
    }
   

/***********************STOPRIGHT****************************/
void STOPRIGHT() {
    	analogWrite(motorA1, 0);   analogWrite(motorA2, 0); 
        myservo.write(105);
    }
    

/***********************STOPLEFT****************************/
void STOPLEFT() {
    	analogWrite(motorA1, 0);   analogWrite(motorA2, 0); 
        myservo.write(80);
    }
    
  /**********************Forward Left************************/
void forwardleft(int vspeed) {
    	analogWrite(motorA1, vspeed); analogWrite(motorA2, 0); 
        myservo.write(80); 
 
    }
  /**********************Forward Right************************/
void forwardright(int vspeed){
      	analogWrite(motorA1, vspeed); analogWrite(motorA2, 0); 
        myservo.write(105); 
    }
      /**********************Backward Left************************/
void backwardleft(int vspeed){
    	analogWrite(motorA1, 0);   analogWrite(motorA2, vspeed); 
        myservo.write(80); 
    }
  /**********************Backward Right************************/
void backwardright(int vspeed){
    	analogWrite(motorA1, 0);   analogWrite(motorA2, vspeed); 
        myservo.write(105); 
    }
    

//~~~~~~~~~~~~~~~Συνάρτηση Διαδικασίας Παρκαρίσματος~~~~~~~~~~~~~~~

void diadikasiaparkarismatos() 
{   

//    ~~~~~~~~~~~~~~~~~~~STATE forward~~~~~~~~~~~~~~~~~~~
    
  distance1=ultrasound_distance(trigPin1, echoPin1);
  while(distance1>60 && turn==LOW && search==LOW && parking==LOW && parkingFinal==LOW){  
      forward(100);
      delay(200);
      STOP();
      delay(100);
      distance1=ultrasound_distance(trigPin1, echoPin1); 
  
      if(distance1<=60 && turn==LOW && search==LOW && parking==LOW && parkingFinal==LOW){  
        Serial.println(" STRIVEI !!!!!!!!!!!!!!!!!!!");
        forwardright(100);  
//Πριν μπει σε κατάσταση turn το αμάξι στρίβει για μισό sec ώστε να μπορέσει να μπει σε κατασταση turn 
//Προϋπόθεση κατάστασης turn distance2!=distance3, αν δεν σιγουρέψουμε σε αυτό το βήμα την εκκίνηση της στροφής
        delay(200);
        STOPRIGHT();
        delay(100);
        turn = HIGH;
      }
  }

//    ~~~~~~~~~~~~~~~~~~~STATE turn~~~~~~~~~~~~~~~~~~~
    
  distance2 = ultrasound_distance(trigPin2, echoPin2);   
  distance3 = ultrasound_distance(trigPin3, echoPin3);  
    
  while(distance2!=distance3 && turn==HIGH && search==LOW && parking==LOW && parkingFinal==LOW){ 
//Για όσο η απόσταση των δύο αισθητηρίων στο πλάι είναι διαφορετική τότε συνέχισε την στροφή
      forwardright(130);
      delay(200);
      STOPRIGHT();
      delay(100);  
      
      distance2 = ultrasound_distance(trigPin2, echoPin2);
      distance3 = ultrasound_distance(trigPin3, echoPin3);      
      
      if((abs(distance2-distance3)<2) && distance2<25 && distance3<25 &&   turn==HIGH ){  
//Αν το σφάλμα distance2-distance3 γίνει 0 τότε μπές σε κατάσταση αναζήτησης παρκαρίσματος
        forwardleft(100);
        delay(150);
        turn = LOW;
        search = HIGH;  
      }
  }   

 
//    ~~~~~~~~~~~~~~~~~~~STATE search~~~~~~~~~~~~~~~~~~~
     
  while(search=HIGH && turn==LOW && parking==LOW && parkingFinal==LOW){
//Εκκίνηση κατάστασης αναζήτησης παρκαρίσματος
      forward(100);
      delay(200);
      STOP();
      delay(100);
      
      distance2 = ultrasound_distance(trigPin2, echoPin2);    
      distance3 = ultrasound_distance(trigPin3, echoPin3);       
   
      if(distance2>25 && distance3>25 ){ 
//Όταν βρεθεί πάρκινγκ και είναι 30cm σε βάθος, το αμάξι φτάνει σε θέση παράλληλη με το μπροστά εμπόδιο (και οι 2 αισθητήρες βλέπουν το εμπόδιο)
        thesi=1;                        
//Καταχωρούμε στην μεταβλητή thesi την μνήμη οτι πέρασε από θέση που χωράει
      }
      if(search=HIGH && distance2<30 && distance3<30 && thesi==1){ 
//Αν ισχύουν όλες οι προυποθέσεις πήγαινε για 3.5 ms μπροστά και μετά μπες σε κατάσταση πάρκινγ
          forward(100);
          delay(350);
          STOP();       //Μόλις βρεθεί το πάρκινγκ, το αμάξι θα σταματήσει
          delay(1000);  //Αναμονή 1 sec μέχρι να μπει σε κατάσταση πάρκινγκ
          parking = HIGH;
          search = LOW;
      }
  }
  

//    ~~~~~~~~~~~~~~~~~~~STATE parking~~~~~~~~~~~~~~~~~~~
    
  distance2 = ultrasound_distance(trigPin2, echoPin2);
  distance3 = ultrasound_distance(trigPin3, echoPin3); 
  distance4 = ultrasound_distance(trigPin4, echoPin4); 
 
  while(parking==HIGH && turn==LOW && search==LOW && parkingFinal==LOW){ //Ξεκινάει το παρκάρισμα
      while(distance4>60){      
// Για όσο η απόσταση του distance 4 είναι μεγαλύτερη των 60 cm κάνε πίσω αριστερά
        backwardleft(100);
        delay(300);
        STOPLEFT();
        delay(100);
        distance4 = ultrasound_distance(trigPin4, echoPin4);
      }
      
      backwardright(100); 
//Μόλις βγεί απο την while πάει να πει ότι πρέπει να κάνει πίσω δεξιά
      delay(300);
      
      while(abs(distance2-distance3)>=2){ 
//Το παραπάνω βήμα έγινε για να μη βρεί κατευθείαν την απόλυτη τιμή του σφάλματος μεγαλύτερο ή ίσο του 2 γιατί έχει αρχίσει να κάνει πίσω δεξιά
        backwardright(100); 
        delay(200);
        STOPRIGHT();
        delay(100);
        distance2 = ultrasound_distance(trigPin2, echoPin2);
        distance3 = ultrasound_distance(trigPin3, echoPin3); 
      }  
//Αφότου βγεί από τις while πάει να πει ότι είναι έτοιμο για το τελικό στάδιο ευθυγράμμισης   
  parkingFinal=HIGH;
  parking=LOW;
  
  distance2 = ultrasound_distance(trigPin2, echoPin2);
  distance3 = ultrasound_distance(trigPin3, echoPin3); 
  distance4 = ultrasound_distance(trigPin4, echoPin4); 
  
}    
      distance1 = ultrasound_distance(trigPin1, echoPin1);
      distance2 = ultrasound_distance(trigPin2, echoPin2);
      distance3 = ultrasound_distance(trigPin3, echoPin3); 
      distance4 = ultrasound_distance(trigPin4, echoPin4);

//    ~~~~~~~~~~~~~~~~~~~STATE parkingFinal~~~~~~~~~~~~~~~~~~~
  
  while(parkingFinal==HIGH && parking==LOW && turn==LOW && search==LOW){
//Τελική ευθηγράμμιση
      while(distance1 > (distance4 +2 )){
        forward(100);
        delay(200);
        STOP();
        delay(100);
        distance1 = ultrasound_distance(trigPin1, echoPin1);
        distance4 = ultrasound_distance(trigPin4, echoPin4);
      }
      while(distance1 +2 < distance4){
        backward(100);
        delay(200);
        STOP();
        delay(100);
        distance1 = ultrasound_distance(trigPin1, echoPin1);
        distance4 = ultrasound_distance(trigPin4, echoPin4);
      }
      while(abs(distance1-distance4)<5){ 
//Όταν ευθηγραμμιστούνε τότε κάνω όλες τις μνήμες στων State=1 ώστε να μην κάνει καμία διεργασία
        STOP();
        Serial.println("TELOS");
        parkingFinal= HIGH; 
        parking= HIGH; 
        turn= HIGH; 
        search= HIGH;
       }
  }
  while(parkingFinal==HIGH && parking==HIGH && turn==HIGH && search==HIGH){
      STOP();
      delay(500000000);
  }
  }

//----------------------------------------VOID LOOP---------------------------------------
void loop()
{
  if (irrecv.decode(&results)) // Αν δώσουμε σήμα 

  {
    translateIR(); // Κάνε μετάφραση του σήματος
    irrecv.resume(); // Διάβασε το επόμενο σήμα
  }  
}

void translateIR() //Συνάρτηση για την αποκωδικοποίηση του κουμπιού του πομπού
{
  switch(results.value)
  
  {
    case 0xFFC23D:  //Αν πατηθεί το κουμπί Start/Pause
    diadikasiaparkarismatos(); //Ξεκινάει την διαδικασία παρκαρίσματος
    break;
  }
  
  delay(500);
}
  

