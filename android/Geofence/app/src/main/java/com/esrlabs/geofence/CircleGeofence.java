package com.esrlabs.geofence;

import android.location.Location;

public class CircleGeofence implements Geofence {

    final Location center;
    final float radiusInMeters;

    public CircleGeofence(Location center, float radiusInMeters) {
        this.center = center;
        this.radiusInMeters = radiusInMeters;
    }

    /**
     * Predicate checking the {@param location} against the defined {@link CircleGeofence}
     * @param location: The location to check
     * @return true if geofence contains the location
     */
    @Override
    public boolean containsLocation(Location location) {
        // TODO: implement this function according to the docstring
        return false;
    }
}
