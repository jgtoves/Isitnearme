#include <ESP8266WiFi.h>

void setup() {
  // We use 115200 baud to ensure the serial buffer doesn't overflow 
  // during dense Wi-Fi scans.
  Serial.begin(115200);
  
  // Set to Station Mode but DO NOT connect to an AP.
  // This allows the radio to hop across all channels (1-11 or 1-13).
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  
  delay(100);
  Serial.println("ESP8266 Wi-Fi Radar Initialized");
}

void loop() {
  // scanNetworks(async, show_hidden, passive)
  // We use 'false' for async so the loop waits for a complete 'snapshot'
  int n = WiFi.scanNetworks(false, true);

  if (n > 0) {
    for (int i = 0; i < n; i++) {
      // Format: BSSID, SSID, RSSI
      // This matches the JavaScript 'processSignal' parser
      Serial.print(WiFi.BSSIDstr(i));
      Serial.print(",");
      Serial.print(WiFi.SSID(i));
      Serial.print(",");
      Serial.println(WiFi.RSSI(i));
    }
    // Optional: Print a separator for debugging in Serial Monitor
    // Serial.println("---SCAN_COMPLETE---");
  }
  
  // Minimal delay to prevent the chip from overheating/crashing
  // but keep the scan rate high for "real-time" detection.
  delay(50); 
}
