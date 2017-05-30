/**
 * Sending OSC bundles to OSC capable devices
 * @Author            Juriaan ('Velibor')
 * @Version           1.0
 * @Last edited on    5/30/2017
 * Inspired by        fabifiess
 */
 
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <OSCBundle.h>          

char ssid[] = "performance";                      // Netwerk naam
char pass[] = "performancenetwork";              //  Netwerk wachtwoord

WiFiUDP Udp;                          
const IPAddress destIp(192,168,1,11);   // Vul hier het IP adres van je computer in.
const unsigned int destPort = 9000;    // De poort van de data die NodeMCU naar de Computer stuurt.
const unsigned int localPort = 8000;   // Lokale poort waar we naar luisteren mochten we ooit een bundle ontvangen.. (Dit example is alleen maar versturen, niet ontvangen.. Laat het even weten als je dit wel wilt.)
OSCBundle bundleOUT;

void setup() {
    Serial.begin(115200);

     // Statisch IP adres instellingen
     // 1) IP-adres
     // 2) Gateway
     // 3) Subnet
     WiFi.config(IPAddress(192,168,1,123),IPAddress(192,168,1,1), IPAddress(255,255,255,0)); 
     WiFi.mode(WIFI_STA);
     
    // Probeer connectie te maken met het Netwerk en general debug.
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    Serial.println("Starting UDP");
    Udp.begin(localPort);
    Serial.print("Local port: ");
    Serial.println(Udp.localPort());
}

void loop() {

    // Eerste OSC message
    int r1 = random(1, 100);
    bundleOUT.add("/1/").add(r1);

    // Tweede OSC message
    int r2 = random(1, 100);
    bundleOUT.add("/2/").add(r2);

    // Kopieer en plak om nog maar OSC messages te maken

    // Het versturen van de Bundles naar onze target IP en cleanup
    Udp.beginPacket(destIp, destPort);
    bundleOUT.send(Udp);
    Udp.endPacket();
    bundleOUT.empty();
    delay(100);
}
