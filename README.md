# esp-idf-web-serial

This project is a Serial Monitor for esp-idf that can be accessed remotely via a web browser.   
I used [this](https://github.com/Molorius/esp32-websocket) component.   
This component can communicate directly with the browser.   
It's a great job.   
I referred to [this](https://github.com/ayushsharma82/WebSerial).   
![Image](https://github.com/user-attachments/assets/d4f0dfc9-2784-4b46-937a-c1276d1a897a)

![Web-Serial](https://user-images.githubusercontent.com/6020549/204442158-0e8e1b11-caa8-4937-b830-99d331ca3fa6.jpg)



# Software requirements
ESP-IDF V5.0 or later.   
ESP-IDF V4.4 release branch reached EOL in July 2024.   
ESP-IDF V5.1 is required when using ESP32-C6.   


# How to Install

- Write this sketch on Arduino Uno.   
You can use any AtMega328 microcontroller.   

```
unsigned long lastMillis = 0;

void setup() {
  Serial.begin(115200);
}

void loop() {
  while (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    Serial.println(command);
  }

  if(lastMillis + 1000 <= millis()){
    Serial.print("Hello World ");
    Serial.println(millis());
    lastMillis += 1000;
  }

  delay(1);
}
```

- Configuration of esp-idf
```
idf.py set-target {esp32/esp32s2/esp32s3/esp32c2/esp32c3}
idf.py menuconfig
```
![config-top](https://user-images.githubusercontent.com/6020549/164256546-da988299-c0ff-41e0-8c5a-45cdd11f9fe7.jpg)
![config-app](https://user-images.githubusercontent.com/6020549/164256573-1e6fc379-699a-4464-a93d-70160fe2a0b0.jpg)


Set the information of your access point.   
![config-wifi](https://user-images.githubusercontent.com/6020549/164256660-c2def5c5-d524-483b-885a-fa8f32e9b471.jpg)


Set the information of your time zone.   
![config-ntp](https://user-images.githubusercontent.com/6020549/164256796-cf851736-2a8e-400f-b809-992aa2ff867e.jpg)


Set GPIO to use with UART.   
![config-uart](https://user-images.githubusercontent.com/6020549/164256738-0f59817b-0deb-41b5-a4e5-379cbe3c2574.jpg)


- Connect ESP32 and AtMega328 using wire cable   

|AtMega328||ESP32|ESP32-S2/S3|ESP32-C2/C3|
|:-:|:-:|:-:|:-:|:-:|
|TX|--|GPIO16|GPIO34|GPIO0|
|RX|--|GPIO17|GPIO35|GPIO1|
|GND|--|GND|GND|GND|

__You can change it to any pin using menuconfig.__   


- Flash firmware
```
idf.py flash monitor
```

- Launch a web browser   
Enter the following in the address bar of your web browser.   
You can communicate to Arduino-UNO using browser.   
The Change button changes the number of lines displayed.   
The Copy button copies the received data to the clipboard.   
```
http:://{IP of ESP32}/
or
http://esp32-server.local/
```

![Web-Serial](https://user-images.githubusercontent.com/6020549/204442158-0e8e1b11-caa8-4937-b830-99d331ca3fa6.jpg)

# WEB Pages
WEB Pages are stored in the html folder.   
You cam change root.html as you like.   

# References

https://github.com/nopnop2002/esp-idf-uart2bt

https://github.com/nopnop2002/esp-idf-uart2udp

https://github.com/nopnop2002/esp-idf-uart2mqtt
