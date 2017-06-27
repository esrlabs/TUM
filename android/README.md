# Android

In this task you have to create an android application which will use a geofence and the current location data in order to open/close a popup on the headunit.

## Your tasks

1. Implement the function `boolean containsLocation(Location location)` within the `CircleGeofence` class. 
- Implement a geofence solution, to notify users, when they leave the area. You will need to implement the missing functions in the Android service class `GeofenceApp`.
	- **Register** to a *locationProvider* from the Android environment.
	- **Bind** your application to a *remote service* to show notifications. The AIDL you will use is *HeadUnit.aidl*. You are on the client side.
	- Implement **geofencing** at `onLocationChanged(Location location)`  
	Implement the logic here:
		- Check the position
		- Hide/show notification
- **BONUS**: Implement the function `boolean containsLocation(Location location)` within the `PolygonGeofence` class. 

## Test your application
Validating your software is important. You have two possibilities to test, whether your software is working.
### Unit testing
Execute the unit tests of the `app`-project.
### Test within android emulator
You first have to register your now implemented service `app` as a service:
		
            <intent-filter>
                <action android:name="com.esrlabs.geofence"/>
            </intent-filter>
            
Afterwards, you install `geofence` and `headunit` service. Then you can start your service using 

		adb shell am startservice -a com.esrlabs.geofence
		
If you want to provide test locations:

		Notification shown:
		longitude: 11.601
		latitude:  48.1195
		
		Notification hidden:
		longitude: 11.601
		latitude:  48.119

## Help /Advice
If you have problems solving the tasks, here is a quick help.

### Receive the current location 

Use the [android location manager](http://developer.android.com/reference/android/location/LocationManager.html) to request location updates. If the location is retrieved correctly, then the following test will pass.

```java
GeofenceAppTest.shouldReceiveTheLatestLocation()
```

### Bind to notification service

Use the [AIDL](http://developer.android.com/guide/components/aidl.html) to allow interprocess communication between your app and another service which will allow you to display notifications. You will need to bind to the service using an intent and a [ServiceConnection](http://developer.android.com/reference/android/content/ServiceConnection.html) object (see [here](http://developer.android.com/guide/components/aidl.html#Expose)).

```java
Intent headUnitServiceIntent = new Intent(HeadUnit.class.getName());
headUnitServiceIntent.setPackage("com.esrlabs.headunitinterface");
bindService(headUnitServiceIntent, serviceConnection_object, BIND_AUTO_CREATE);
```

### Circular geofence

The first step is to implement a circle geofence. You cannot use the google API because that is part of the play API, and it is not supported by our android controller. You have included in the test suite a test class for the circle geofence to help you.

### Polygon geofence

You can use the [Ray-casting algorithm](https://en.wikipedia.org/wiki/Point_in_polygon). Use the slope of a straight line in order to tell if the ray starting from the given point and going in a fixed direction, intersects an edge of the polygon. Take care that *Math.atan()* return radians, and you will have to correct a negative angle:

```java
90 + (90 - Math.abs(angle))
```

