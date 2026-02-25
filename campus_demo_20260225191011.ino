int crowd = 0;
int capacity = 15;
unsigned long lastDetect = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("=== CROWD MONITOR ===");
}

void loop() {
  unsigned long now = millis();
  
  // Simulate person detection every 2-4 seconds
  if (now - lastDetect > random(2000, 4000)) {
    crowd++;
    Serial.println(" PERSON DETECTED +1");
    lastDetect = now;
  }
  
  // Print crowd status every 2 seconds
  if (now % 2000 < 100) {
    int percentage = (crowd * 100) / capacity;
    int level = (crowd * 3) / capacity; // 0=GREEN,1=BLUE,2=RED
    
    Serial.printf(" Crowd: %d/15 → ", crowd);
    if (level == 0) Serial.println("🟢 GREEN (" + String(percentage) + "%)");
    else if (level == 1) Serial.println("🔵 BLUE (" + String(percentage) + "%)");
    else Serial.println("🔴 RED (" + String(percentage) + "%)");
    
    // JSON dashboard output
    Serial.printf(" {\"count\":%d,\"level\":%d,\"status\":\"%s\"}\n", 
                  crowd, level, 
                  level==0 ? "LOW" : level==1 ? "MEDIUM" : "HIGH");
    
    if (crowd >= 13) {
      Serial.println("🚨 DASHBOARD ALERT: LIBRARY FULL!");
      crowd = 0; // Reset for demo loop
    }
  }
  
  delay(100);
}