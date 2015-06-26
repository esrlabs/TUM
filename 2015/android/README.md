# Display a notification on the headunit

In this task you have to create an android application which will use a geofence and the current location data in order to open/close a popup on the headunit.

## Receive the current location 

Use the [android location manager](http://developer.android.com/reference/android/location/LocationManager.html) to request location updates. If the location is retrieved correctly, then the following test will pass.

```java
shouldReceiveTheLatestLocation()
```

## Bind to a remote service to be able to display notifications

Use the [AIDL](http://developer.android.com/guide/components/aidl.html) to allow interprocess communication between your app and another service which will allow you to display notifications. The AIDL you will use is **HeadUnit.aidl**. You are on the client side. You will need to bind to the service using a **ServiceConnection** object ([like here](http://developer.android.com/guide/components/aidl.html#Expose)).

```java
Intent headUnitServiceIntent = new Intent(HeadUnit.class.getName());
headUnitServiceIntent.setPackage("com.esrlabs.headunitinterface");
bindService(headUnitServiceIntent, serviceConnection_object, BIND_AUTO_CREATE);
```

## Implement a geofence object to tell if the current is inside a designated area or not


