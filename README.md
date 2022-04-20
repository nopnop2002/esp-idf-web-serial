# esp-idf-web-serial

This project is a Serial Monitor for esp-idf that can be accessed remotely via a web browser.   
Webpage is stored in program memory of ESP32.   

![Web-Serial](https://user-images.githubusercontent.com/6020549/164257652-d5c52442-7168-4069-8e0b-cd04f1b2cb83.jpg)


I referred to [this](https://github.com/ayushsharma82/WebSerial).


# Software requirements
esp-idf v4.4 or later.   
This is because this version supports ESP32-C3.   


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

- Install websocket component   
I used [this](https://github.com/Molorius/esp32-websocket) component.   
This component can communicate directly with the browser.   
It's a great job.   

```
git clone https://github.com/nopnop2002/esp-idf-web-serial
cd esp-idf-web-serial/
git clone https://github.com/Molorius/esp32-websocket components/websocket
```


- Configuration of esp-idf
```
idf.py set-target {esp32/esp32s2/esp32s3/esp32c3}
idf.py menuconfig
```
![config-top](https://user-images.githubusercontent.com/6020549/164256546-da988299-c0ff-41e0-8c5a-45cdd11f9fe7.jpg)
![config-app](https://user-images.githubusercontent.com/6020549/164256573-1e6fc379-699a-4464-a93d-70160fe2a0b0.jpg)


Set the information of your access point.

![config-wifi](https://user-images.githubusercontent.com/6020549/164256660-c2def5c5-d524-483b-885a-fa8f32e9b471.jpg)


Set the information of your time zone.

![config-ntp](https://user-images.githubusercontent.com/6020549/164256796-cf851736-2a8e-400f-b809-992aa2ff867e.jpg)


Select GPIO to use with UART.

![config-uart](https://user-images.githubusercontent.com/6020549/164256738-0f59817b-0deb-41b5-a4e5-379cbe3c2574.jpg)


- Connect ESP32 and AtMega328 using wire cable.
|AtMega328||ESP32|ESP32-S2|ESP32-C3|
|:-:|:-:|:-:|:-:|:-:|
|TX|--|GPIO16|GPIO34|GPIO18|
|RX|--|GPIO17|GPIO35|GPIO19|
|GND|--|GND|GND|GND|

__You can change it to any pin using menuconfig.__   


- Flash firmware
```
idf.py flash monitor
```

- Launch a web browser 
Enter the following in the address bar of your web browser.   

```
http:://{IP of ESP32}/
or
http://esp32-server.local/
```

- You can communicate to Arduino-UNO

![Web-Serial](https://user-images.githubusercontent.com/6020549/164257652-d5c52442-7168-4069-8e0b-cd04f1b2cb83.jpg)

# WEB Page
WEB Page is stored in the html folder.   
You cam change root.html as you like.   
