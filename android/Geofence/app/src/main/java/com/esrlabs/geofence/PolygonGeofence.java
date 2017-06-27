package com.esrlabs.geofence;

import android.location.Location;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class PolygonGeofence implements Geofence {

    final List<Location> polygonPoints;

    public PolygonGeofence(Location... locations) {
        polygonPoints = new ArrayList<Location>(Arrays.asList(locations));
    }

    /**
     * It implements the Ray casting algorithm, with the convention that the line is horizontal and
     * goes from left to right.
     * @param location The point to be checked if is inside the defined polygon shaped geofence
     * @return True if the location is inside the defined polygon.
     */
    @Override
    public boolean containsLocation(Location location) {
        int numberOfCorners = polygonPoints.size();

        //adding the first corner at the end so that we can count the edge between last and first corners too
        List<Location> corners = new ArrayList<Location>(polygonPoints);
        corners.add(polygonPoints.get(0));
        // TODO: implement this function according to the docstring
        return false;
    }
}
