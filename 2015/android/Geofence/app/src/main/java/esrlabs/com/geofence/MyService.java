package esrlabs.com.geofence;

import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Bundle;
import android.os.IBinder;

import java.util.List;

public class MyService extends Service implements LocationListener {
    public static final String CAN_PROVIDER = "CanLocationProvider";

    private LocationManager locationManager;
    private Location latestLocation;

    public MyService(LocationManager locationManager) {
        this.locationManager = locationManager;
    }

    @Override
    public void onCreate() {
        super.onCreate();

        if (locationManager == null) {
            locationManager = (LocationManager)
                    this.getSystemService(Context.LOCATION_SERVICE);
        }

        initLocationListener();
    }

    @Override
    public IBinder onBind(Intent intent) {
        throw new UnsupportedOperationException("Not yet implemented");
    }

    private void initLocationListener() {
        List<String> allProviders = locationManager.getAllProviders();
        for (String provider : allProviders) {
            locationManager.requestLocationUpdates(provider, 0, 0, this);
        }

        locationManager.requestLocationUpdates(CAN_PROVIDER, 0, 0, this);
    }

    @Override
    public void onLocationChanged(Location location) {
        latestLocation = location;
    }

    public Location latestLocation() {
        return latestLocation;
    }

    @Override
    public void onStatusChanged(String s, int i, Bundle bundle) {}
    @Override
    public void onProviderDisabled(String s) {}
    @Override
    public void onProviderEnabled(String s) {}
}