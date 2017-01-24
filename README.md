# fona-dfrobot-iot-board
This is a sample code for DFRobot's SIM808 GSM/GPRS/GPS Arduino IOT Board using the Adafruit Fona library.
The logic for the SIM808 module is in fona.ino. All of the functions can be used to the your main arduino file (in this case, main.ino)

#Prerequisites
Make sure that you have an external power supply rated 7-23V to be connected on the DC jack or a 3.7 Li-On battery. Connecting a power supply on the DC jack will automatically turn on the SIM808 module. Connecting a battery would require you to press the BOOT button or turn on the SIM808 module via software.


![logo](https://www.dfrobot.com/wiki/images/7/70/DFR0355PinOutOverall.png "SIM808 GSM/GPRS/GPS Arduino IOT Board")

Make sure that when you try to turn on the SIM808 module (the NET LED should light up to signify this), you have a good power supply. Otherwise, the GSM module will turn off. For more information, check the [SIM808 GSM/GPRS/GPS Arduino IOT Board product wiki] (https://www.dfrobot.com/wiki/index.php/SIM808_with_Leonardo_mainboard_SKU:DFR0355).


#Functions
setupFona() - initiate communication between the Arduino and the SIM808 module through Serial1. The debug logs should reveal whether the board is able to communicate to the SIM808 module. When the communication is successful, the GPS and GPRS modules are initialized. After initializing the GPS and GPRS modules, the ten (10) most recent messages saved on the SIM card are deleted. This is because the SIM808 module can only support a few saved messages on the SIM card. If we don't delete, the module behaves erratically.

deleteMessages() - delete the ten (10) recently saved messages on the SIM card.

sendSMS(number, message) - send a message on the number. NOTE: If String variables are to be passed as a parameter, use the ".c_str()" function. Example:
```
String message = "Hello"!;
sendSMS("09XXXXXXXXX", message.c_str());
```

readSMS(number) - the Adafruit Fona library has an example for getting unread messages. However it does not seem to work properly. As a work around, reading SMS is done inside the loop function (see main.ino). This means that we are polling. The readSMS function checks whether the SIM808 module has received a message from the number that was passed as a parameter. If the sender is not the same with the number supplied, then the SMS is flagged as "unauthorized". Otherwise, we get the message to be processed outside fona.ino

getGPS(latitude, longitude, speed_kph, heading, altitude) - get GPS data and store the data to the parameters. The function returns 0 when there is no GPS fix. NOTE: It is important that you use a good GPS antenna otherwise the SIM808 module won't get a 
GPS fix. 
