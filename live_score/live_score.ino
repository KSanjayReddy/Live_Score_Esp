#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <ESP8266WiFi.h>
String score=" ";
const char* ssid     = "Redmi";
const char* password = "12345678";
const char* host = "cricscore-api.appspot.com"; 

// ESP8266 Software SPI (slower updates, more flexible pin options):
// pin 14 - Serial clock out (SCLK)
// pin 13 - Serial data out (DIN)
// pin 12 - Data/Command select (D/C)
// pin 5 - LCD chip select (CS)
// pin 4 - LCD reset (RST)
//Adafruit_PCD8544 display = Adafruit_PCD8544(14, 13, 12, 5, 4);      // use this
Adafruit_PCD8544 display = Adafruit_PCD8544(2,0,4,5,16);


#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16

static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

void setup()   {
  Serial.begin(115200);
  delay(100);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }

  //Serial.println(" ");
  //Serial.println("WiFi connected");
  //Serial.println("IP address: ");
  //Serial.println(WiFi.localIP());
  Serial.println("WiFi  OK");
  
  display.begin();
  // init done

  // you can change the contrast around to adapt the display
  // for the best viewing!
  display.setContrast(40);
  display.clearDisplay();   // clears the screen and buffer

  // draw the first ~12 characters in the font
  

  // text display tests
  


 
}


void loop() {
  delay(5000);
    WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // We now create a URI for the request
  
  String url = "/csa?id=1022373"; 
  Serial.print("Requesting URL: ");
  Serial.println(url);
 // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  delay(1000);

  // Read all the lines of the reply from server and print them to Serial
  String line;
  while (client.available()) {

    line = client.readStringUntil('\r');
    delay(100);
    line.trim();
    if(line[0]=='['){
      line.trim();
      Serial.println(line);
      int i = line.indexOf('(');
      String overs = "";
      for(int j=i+1;j<i+5;j++){
        overs = overs+line[j];
      }
      overs.trim();
      Serial.println(overs);
      String score="";
      for(int j = i-6;j<i;j++){
        score = score+line[j];
      }
      score.trim();
      Serial.println(score);
      delay(500);
      display.setTextSize(0.5);
      display.setTextColor(BLACK);
      display.setCursor(0,0);
       display.println("IND vs BAN");
        //display.setTextColor(WHITE, BLACK); // 'inverted' text
       //display.println(3.141592);
       display.setTextSize(2);
       display.setTextColor(BLACK);
      display.println(score); 
       display.setTextSize(1);
       display.print("Overs: ");
       display.println(overs);
       display.println("");
       display.println("Ban-264/7 (50) "); 
       display.display();
       delay(2000);
    }
    
  
}
}
void testdrawchar(void) {
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);

  for (uint8_t i=0; i < 168; i++) {
    if (i == '\n') continue;
    display.write(i);
    //if ((i > 0) && (i % 14 == 0))
      //display.println();
  }    
  display.display();
}


