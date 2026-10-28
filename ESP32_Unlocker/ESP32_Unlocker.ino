#define USE_NIMBLE
#include <NimBLEDevice.h>
#include <BleKeyboard.h>

BleKeyboard bleKeyboard("ESP32 Unlocker", "ESP32", 100);
const int touchPin = 4; // GPIO 4-এ তার যুক্ত করবে
bool macroRunning = false;

void setup() {
  Serial.begin(115200);
  bleKeyboard.begin();
}

void loop() {
  if (bleKeyboard.isConnected()) {
    // টাচ ভ্যালু ৩০ এর নিচে নামলে আনলক ট্রিগার হবে
    if (touchRead(touchPin) < 30 && !macroRunning) {
      macroRunning = true;

      // ১. স্ক্রিন ওয়েক আপ করা
      bleKeyboard.write(KEY_RETURN);
      delay(1500); 

      // ২. লক স্ক্রিন থেকে পিন প্যাড আনা (অ্যান্ড্রয়েডে সোয়াইপ)
      bleKeyboard.write(KEY_RETURN);
      delay(1000);

      // ৩. পিন টাইপ করা 
      bleKeyboard.write('9');
      delay(100);
      bleKeyboard.write('0');
      delay(100);
      bleKeyboard.write('3');
      delay(100);
      bleKeyboard.write('8');
      delay(100);
      bleKeyboard.write('6');
      delay(100);
      bleKeyboard.write('7');
      delay(500);

      // ৪. পিন সাবমিট করা
      bleKeyboard.write(KEY_RETURN);

      // ভুলবশত বারবার ট্রিগার এড়াতে ৫ সেকেন্ডের কুলডাউন
      delay(5000); 
      macroRunning = false;
    }
  }
}
