package com.esrlabs.geofence;

import android.location.Location;

import static android.location.LocationManager.NETWORK_PROVIDER;

public class Utils {

    public static Location location(String provider, double latitude, double longitude) {
        Location location = new Location(provider);
        location.setLatitude(latitude);
        location.setLongitude(longitude);
        location.setTime(System.currentTimeMillis());
        return location;
    }

    public static Geofence getGarchingGeofence(){
        final Location testPolygonTopLeftCorner = location(NETWORK_PROVIDER, 48.263943, 669885);
        final Location testPolygonTopRightCorner = location(NETWORK_PROVIDER, 48.263574, 11.671915);
        final Location testPolygonBottomLeftCorner = location(NETWORK_PROVIDER, 48.260834, 11.666707);
        final Location testPolygonBottomRightCorner = location(NETWORK_PROVIDER, 48.260538, 11.670596);
        return new PolygonGeofence(testPolygonTopRightCorner, testPolygonTopLeftCorner,
                testPolygonBottomRightCorner, testPolygonBottomLeftCorner);
    }

    public static Geofence getEsrlabsGeofence(){
        final Location testPolygonTopLeftCorner = location(NETWORK_PROVIDER, 48.119051, 11.601966); // 48.119549, 11.602188
        final Location testPolygonTopRightCorner = location(NETWORK_PROVIDER, 48.119033, 11.601664); // 48.119718, 11.603057
        final Location testPolygonBottomLeftCorner = location(NETWORK_PROVIDER, 48.116758, 11.602743); // 48.118092, 11.603218
        final Location testPolygonBottomRightCorner = location(NETWORK_PROVIDER, 48.116726, 11.602404); // 48.118159, 11.603778
        return new PolygonGeofence(testPolygonTopRightCorner, testPolygonTopLeftCorner,
                testPolygonBottomRightCorner, testPolygonBottomLeftCorner);
    }
}
