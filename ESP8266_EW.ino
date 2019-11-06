/*
 * ESP8266 AT
 * http://www.electronicwings.com
 */ 
 #include <SoftwareSerial.h>
 #include "ESP8266_AT.h"
// #include <dht.h>
 #include <SPI.h>
 #include <MFRC522.h>

#define dht_apin A0 // Analog Pin sensor is connected to
 


#define SS_PIN 10
#define RST_PIN 9
 
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key; 

// Init array that will store new NUID 
byte nuidPICC[4];

 

 /* Select Demo */
//#define RECEIVE_DEMO        /* Define RECEIVE demo */
#define SEND_DEMO         /* Define SEND demo */

/* Define Required fields shown below */
#define DOMAIN        "api.thingspeak.com"
#define PORT        "80"
#define API_WRITE_KEY   "BM2HPN0I9GQTXGE9"
#define CHANNEL_ID      "901575"

#define SSID        "zzzzzz"
#define PASSWORD    "xxxxxx"


int smokeA0 = A1;
#define Soil A2
int soilValue = 0; 
 


char _buffer[150];
uint8_t Connect_Status;
#ifdef SEND_DEMO
uint8_t Sample = 0;
#endif

char dh[8]; 
char gas[8];

//Variables
int chk;
uint8_t hum;  //Stores humidity value
uint8_t temp; //Stores temperature value

void setup() 
{
  Serial.begin(115200);
 

 
  while(!ESP8266_Begin());
  ESP8266_WIFIMode(BOTH_STATION_AND_ACCESPOINT);/* 3 = Both (AP and STA) */
  ESP8266_ConnectionMode(SINGLE);     /* 0 = Single; 1 = Multi */
  ESP8266_ApplicationMode(NORMAL);    /* 0 = Normal Mode; 1 = Transperant Mode */
  if(ESP8266_connected() == ESP8266_NOT_CONNECTED_TO_AP)	/*Check WIFI connection*/
  ESP8266_JoinAccessPoint(SSID, PASSWORD);		/*Connect to WIFI*/
  ESP8266_Start(0, DOMAIN, PORT);	

   SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 
}

void loop() 
{
      Connect_Status = ESP8266_connected();
      if(Connect_Status == ESP8266_NOT_CONNECTED_TO_AP)		/*Again check connection to WIFI*/
      ESP8266_JoinAccessPoint(SSID, PASSWORD);		/*Connect to WIFI*/
      if(Connect_Status == ESP8266_TRANSMISSION_DISCONNECTED)
      ESP8266_Start(0, DOMAIN, PORT);		/*Connect to TCP port*/


 
    uint8_t BP = analogRead(A1);
 


    // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;

 String content= "";
 int cardid = 0;

  if (rfid.uid.uidByte[0] != nuidPICC[0] || 
    rfid.uid.uidByte[1] != nuidPICC[1] || 
    rfid.uid.uidByte[2] != nuidPICC[2] || 
    rfid.uid.uidByte[3] != nuidPICC[3] ) {
    Serial.println(F("A new card has been detected."));

    // Store NUID into nuidPICC array
    for (byte i = 0; i < rfid.uid.size; i++) {
      nuidPICC[i] = rfid.uid.uidByte[i];
      Serial.println(nuidPICC[i] < 0x10 ? " 0" : " ");
      Serial.print(nuidPICC[i], HEX);
      content.concat(String(nuidPICC[i] < 0x10 ? " 0" : " "));
      content.concat(String(nuidPICC[i], HEX));
      
    }
    


     content.toUpperCase();
    if (content.substring(1) == "C5 18 DF 52"){
       Serial.println("reading for tag...");
       cardid = 1; // tag
    }
    else
    {
       Serial.println("reading for card...");
       cardid = 2; // card
     }
       
       
    Serial.println(cardid);
   

     #ifdef SEND_DEMO
     memset(_buffer, 0, 300);
     //sprintf(_buffer, "GET /update?api_key=%s&field1=%d&field2=%d", API_WRITE_KEY,BP, printDec(rfid.uid.uidByte, rfid.uid.size));   /*connect to thingspeak server to post data using your API_WRITE_KEY*/
     
     sprintf(_buffer, "GET /update?api_key=%s&field1=%d&field2=%d", API_WRITE_KEY,BP,cardid);   /*connect to thingspeak server to post data using your API_WRITE_KEY*/
     
     ESP8266_Send(_buffer);
     delay(1000); /* Thingspeak server delay */
     #endif
   
  }
 
    #ifdef RECEIVE_DEMO
    memset(_buffer, 0, 150);
    sprintf(_buffer, "GET /channels/%s/feeds/last.txt", CHANNEL_ID); /*Connect to thingspeak server to get data using your channel ID*/
    ESP8266_Send(_buffer);
    Read_Data(_buffer);
    delay(600);
    #endif
  }



  /**
 * Helper routine to dump a byte array as hex values to Serial. 
 */
void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

/**
 * Helper routine to dump a byte array as dec values to Serial.
 */
int printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }

  return buffer;
}
