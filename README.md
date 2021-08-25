# audiobook
Minimal audio book reader for mobile and desktop.

## requirements:
Install qt5-charts && qt5-graphicaleffects  
Install gdb && valgrind
Install gradle
Install jdk11

## android

Enable adb run command: adb devices  

## qtcreator setup

Install qt from here, dont use the aur version. Ensure you do a full install include Android arches.
wget http://download.qt.io/official_releases/qt/5.12/5.12.9/qt-opensource-linux-x64-5.12.9.run

When installing android tools, will warn no space on device, exec the following: 
```sudo mount -o remount,size=8G /tmp/```

Tools > options > Devices > Android

JDK location: /usr/lib/jvm/default
Android SDK location > point to own sdk dir > Set Up SDK

Scroll down and click SDK Manager > Update installed

Tools > Kits > Add

https://wiki.qt.io/Android

https://doc.qt.io/qtcreator/creator-developing-android.html#specifying-android-device-settings

## screenshots - qml
![ScreenShot](screenshots/main_linux.png)

## screenshots - qt5
![ScreenShot](screenshots/qt5_linux.png)