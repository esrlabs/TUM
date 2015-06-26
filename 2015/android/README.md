# Display a notification on the headunit

In this task you have to create an android application which will use a geofence and the current location data in order to open/close a popup on the headunit.

## Receive the current location 

Use the [Android]

- The controller responsible for what is displayed on the headunit runs a custom android OS. Your task is to create an android application which will use a geofence and the vehicle’s current location data in order to inform the user that he or she has just driven outside of the free parking area. You will receive the data to build the geofence prior to the development. The current
location data will come from the application developed by your fellow teammates, on the other controller of the system. In order to display a popup on the headunit you will have to implement an AIDL. To help the development process you will use a test framework which will give you fake location data and will test that you have displayed or hidden the popup accordingly. You will also have the possibility to check this in the android simulator by observing a notification in the task bar when the “current” location will be outside of the given geofence.
