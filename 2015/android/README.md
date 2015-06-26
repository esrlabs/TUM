# Display a notification on the headunit

In this task you have to create an android application which will use a geofence and the current location data in order to open/close a popup on the headunit.

## Receive the current location 

Use the [android location manager](http://developer.android.com/reference/android/location/LocationManager.html) to request location updates. If the location is retrieved correctly, then the following test will pass.

```java
GeofenceAppTest.shouldReceiveTheLatestLocation()
```

## Bind to a remote service to be able to display notifications

Use the [AIDL](http://developer.android.com/guide/components/aidl.html) to allow interprocess communication between your app and another service which will allow you to display notifications. The AIDL you will use is *HeadUnit.aidl*. You are on the client side. You will need to bind to the service using a [ServiceConnection](http://developer.android.com/reference/android/content/ServiceConnection.html) object (like [here](http://developer.android.com/guide/components/aidl.html#Expose)).

```java
Intent headUnitServiceIntent = new Intent(HeadUnit.class.getName());
headUnitServiceIntent.setPackage("com.esrlabs.headunitinterface");
bindService(headUnitServiceIntent, serviceConnection_object, BIND_AUTO_CREATE);
```

## Implement a circle geofence object to tell if the current is inside a designated area or not

The first step is to implement a circle geofence. You cannot use the google API because that is part of the play API, and it is not supported by our android controller. You have included in the test suite a test class for the circle geofence to help you.

The second step is to display a popup if the current location is outside of a given geofence (alternatively to close if the location is inside). If this is correctly implemented than all the tests should be green (**Note** that unless you are going for the bonus you should disable the test in the *PolygonGeofenceTest* class).

## **Bonus** Implement a polygon geofence instead 

You can use the [Ray-casting algorithm](https://en.wikipedia.org/wiki/Point_in_polygon).

#### HINT

Use the slope of a straight line in order to tell if the ray starting from the given point and going in a fixed direction, intersects an edge of the polygon. Take care that *Math.atan()* return radians, and you will have to correct a negative angle:

```java
90 + (90 - Math.abs(angle))
```


