#include <Servo.h>

// تعريف المحركات الأربعة
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

// متغيرات للتحكم بالوقت والزاوية
unsigned long previousMillis = 0;
int pos = 0;         // الزاوية الابتدائية
int increment = 2;   // سرعة حركة الـ Sweep
bool isSweeping = true;

void setup() {
  // ربط المحركات بالمنافذ المحددة اللي شبكناها
  servo1.attach(3);
  servo2.attach(5);
  servo3.attach(6);
  servo4.attach(9);
}

void loop() {
  // التحقق مما إذا كان الوقت المار أقل من ثانيتين (2000 ملي ثانية)
  if (millis() < 2000) {
    unsigned long currentMillis = millis();
    
    // حركة Sweep بدون استخدام delay لإبقاء حساب الوقت دقيقاً
    if (currentMillis - previousMillis >= 5) { 
      previousMillis = currentMillis;
      pos += increment;
      
      // عكس الاتجاه عند الوصول للحدود (0 أو 180 درجة)
      if (pos >= 180 || pos <= 0) {
        increment = -increment; 
      }
      
      // تحريك جميع المحركات معاً
      servo1.write(pos);
      servo2.write(pos);
      servo3.write(pos);
      servo4.write(pos);
    }
  } 
  else {
    // بعد مرور الثانيتين، تتوقف المحركات وتثبت عند 90 درجة
    if (isSweeping) {
      servo1.write(90);
      servo2.write(90);
      servo3.write(90);
      servo4.write(90);
      
      isSweeping = false; // إيقاف التحديث المستمر لتثبيت المحركات
    }
  }
}