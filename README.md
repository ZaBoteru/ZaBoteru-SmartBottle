# ZaBoteru

![ZaBoteru](Assets/ZaBoteru.png)

## Table of Contents

- [Description](#description)
- [Features](#features)
- [Setup Instructions](#setup-instructions)
- [Future Hardware Considerations](#future-hardware-considerations)
- [Help & Assistance](#help--assistance)
- [Contribution](#contribution)
- [License](#license)

## Description

ZaBoteru is an innovative smart bottle that works efficiently to prevent dehydration. It monitors water intake, tracks temperature, provides heating and UV sterilization. It integrates with Firebase for remote monitoring and control by our user-friendly ZaBoteru mobile app.

## Features

:ballot_box_with_check: **Water Level Monitoring**

:ballot_box_with_check: **Temperature Monitoring and Control**

:ballot_box_with_check: **UV Water Sterilization**

:ballot_box_with_check: **Hydration Alerts with Visual Feedback via RGB LED and LCD**

## Setup Instructions

1. Clone this repository to your local machine.
2. Connect your hardware components as described in the system hardware guide provided. Click [Here](Assets/ZaBoteru_Hardware_Connection_Guide.pdf) to download ZaBoteru Hardware Connection Guide (PDF).
3. **Firebase Setup:**
   Create your Firebase project and configure the necessary parameters. Please refer to the System Architecture section [Here](https://github.com/ZaBoteru/ZaBoteru-HydrationApp/tree/main?tab=readme-ov-file#our-system-architecture) to get the required parameters.
4. Open the [source code](Source-Code/smart_water_bottle/smart_water_bottle.ino) in the Arduino IDE.
5. Install the required libraries:

```c
    ESP8266WiFi.h
    ESP8266Firebase.h
    HX711.h
    HX711_ADC.h
    LiquidCrystal_I2C.h
    OneWire.h
    DallasTemperature.h
    SoftwareSerial.h
```

6. Set up your WiFi settings in the code and replace the Firebase URL with your own Firebase project URL:

```c
Firebase firebase("https://your-firebase-project-url.firebaseio.com/");
#define _SSID "your_wifi_ssid"
#define _PASSWORD "your_wifi_password"
```

7. Upload the code to your ESP8266.
8. Open the Serial Monitor to check the debug messages and test your prototype.

**For ZaBoteru mobile app setup, please refer to [ZaBoteru-HydrationApp](https://github.com/ZaBoteru/ZaBoteru-HydrationApp) repository.**

## Future Hardware Considerations

- Design Compact Embedded System.
- Incorporate more sensors for detailed data.
- Improve the ruggedness of the hardware to withstand environmental conditions.
- Add location tracking to help users find the bottle’s location.

## Help & Assistance

If you encounter any issues or have any questions or need further assistance, feel free to reach out.

## Contribution

| <a href="https://github.com/cln-Kafka"><img src="https://avatars.githubusercontent.com/u/100665578?v=4" width="100px" alt="@Kareem Noureddine"></a> | <a href="https://github.com/Salma-me"><img src="https://avatars.githubusercontent.com/u/114951438?v=4" width="100px" alt="@Salma-me"></a> | <a href="https://github.com/SalmaAbeltawab"><img src="https://avatars.githubusercontent.com/u/112682498?v=4" width="100px" alt="@SalmaAbeltawab"></a> | <a href="https://github.com/sarah1ibrahim"><img src="https://avatars.githubusercontent.com/u/99448829?v=4" width="100px" alt="@sarah1ibrahim"></a> | <a href="https://github.com/RushingBlast"><img src="https://avatars.githubusercontent.com/u/96780345?v=4" width="100px" alt="@RushingBlast"></a> |
| :-------------------------------------------------------------------------------------------------------------------------------------------------: | :---------------------------------------------------------------------------------------------------------------------------------------: | :---------------------------------------------------------------------------------------------------------------------------------------------------: | :------------------------------------------------------------------------------------------------------------------------------------------------: | :----------------------------------------------------------------------------------------------------------------------------------------------: |
|                                                  [Kareem Noureddine](https://github.com/cln-Kafka)                                                  |                                                [Salma Ashraf](https://github.com/Salma-me)                                                |                                                [Salma Abd El-Tawab](https://github.com/SalmaAbeltawab)                                                |                                                  [Sara Ibrahim](https://github.com/sarah1ibrahim)                                                  |                                                 [Assem Hussein](https://github.com/RushingBlast)                                                 |

## License

All rights reserved © 2023 to Team 02 of the Assistive Technologies Course - Systems & Biomedical Engineering, Cairo University (Class 2025).
