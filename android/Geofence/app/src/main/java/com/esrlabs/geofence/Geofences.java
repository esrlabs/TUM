package com.esrlabs.geofence;

import android.location.Location;

import static android.location.LocationManager.NETWORK_PROVIDER;

public class Geofences {

    public static Geofence getCircleGarching(){
        final int someRadiusInMeters = 25;
        final Location someCenterForTheGeofence = Utils.location(NETWORK_PROVIDER, 48.262541, 11.670033);
        return new CircleGeofence(someCenterForTheGeofence, someRadiusInMeters);
    }

    public static Geofence getCircleEsrlabs(){
        final int someRadiusInMeters = 25;
        final Location someCenterForTheGeofence = Utils.location(NETWORK_PROVIDER, 48.118920, 11.601057);
        return new CircleGeofence(someCenterForTheGeofence, someRadiusInMeters);
    }

    public static Geofence getPolygonGarching(){
        final Location testPolygonTopLeftCorner = Utils.location(NETWORK_PROVIDER, 48.263943, 669885);
        final Location testPolygonTopRightCorner = Utils.location(NETWORK_PROVIDER, 48.263574, 11.671915);
        final Location testPolygonBottomLeftCorner = Utils.location(NETWORK_PROVIDER, 48.260834, 11.666707);
        final Location testPolygonBottomRightCorner = Utils.location(NETWORK_PROVIDER, 48.260538, 11.670596);
        return new PolygonGeofence(testPolygonTopRightCorner, testPolygonTopLeftCorner,
                testPolygonBottomRightCorner, testPolygonBottomLeftCorner);
    }

    public static Geofence getPolygonEsrlabs(){
        final Location testPolygonTopLeftCorner = Utils.location(NETWORK_PROVIDER, 48.119051, 11.601966); // 48.119549, 11.602188
        final Location testPolygonTopRightCorner = Utils.location(NETWORK_PROVIDER, 48.119033, 11.601664); // 48.119718, 11.603057
        final Location testPolygonBottomLeftCorner = Utils.location(NETWORK_PROVIDER, 48.116758, 11.602743); // 48.118092, 11.603218
        final Location testPolygonBottomRightCorner = Utils.location(NETWORK_PROVIDER, 48.116726, 11.602404); // 48.118159, 11.603778
        return new PolygonGeofence(testPolygonTopRightCorner, testPolygonTopLeftCorner,
                testPolygonBottomRightCorner, testPolygonBottomLeftCorner);
    }
}
