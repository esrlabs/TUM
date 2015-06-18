package com.esrlabs.geofence;

import static com.esrlabs.geofence.GeofenceApp.CAN_PROVIDER;
import static org.robolectric.Shadows.shadowOf;

import android.content.ComponentName;
import android.content.Context;
import android.location.Location;
import android.location.LocationManager;
import android.os.IBinder;
import android.os.RemoteException;

import junit.framework.TestCase;

import com.esrlabs.headunitinterface.HeadUnit;


import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.robolectric.RobolectricGradleTestRunner;
import org.robolectric.RuntimeEnvironment;
import org.robolectric.annotation.Config;
import org.robolectric.shadows.ShadowLocationManager;

import java.util.concurrent.atomic.AtomicBoolean;

import esrlabs.com.geofence.BuildConfig;


@RunWith(RobolectricGradleTestRunner.class)
@Config(constants = BuildConfig.class, emulateSdk = 17)
public class GeofenceAppTest extends TestCase {
    private final LocationManager locationManager = (LocationManager)
            RuntimeEnvironment.application.getSystemService(Context.LOCATION_SERVICE);
    private final ShadowLocationManager shadowLocationManager = shadowOf(locationManager);
    private final Location someLocation = location(CAN_PROVIDER, 12.0, 20.0);
    private final AtomicBoolean notificationVisibility = new AtomicBoolean(false);

    private GeofenceApp geofenceApp;

    @Before
    public void setUp() throws Exception {
        initHeadUnitServiceMock();
        setupGeofenceApp();
    }

    @After
    public void tearDown() throws Exception {
        geofenceApp.onDestroy();
    }

    @Test
    public void testLatestLocation() throws Exception {
        simulateNewLocation(someLocation);
        assertTrue(someLocation.equals(geofenceApp.latestLocation()));
    }

    @Test
    public void testThatPopupIsShownWhenTheCurrentLocationIsOutsideTheGeofence() throws Exception {
//        Location locationInsideTheGeofence = location(CAN_PROVIDER, 10, 10);
//        simulateNewLocation(locationManager, locationInsideTheGeofence);
//        assertTrue(locationInsideTheGeofence.equals(mainService.latestLocation()));
//        assertFalse(notificationVisibility.get());

        Location locationOutsideTheGeofence = location(CAN_PROVIDER, 11, 11); // todo: put real vals
        simulateNewLocation(locationOutsideTheGeofence);
        assertTrue(locationOutsideTheGeofence.equals(geofenceApp.latestLocation()));
        assertTrue(notificationVisibility.get());
    }

    private void setupGeofenceApp() {
        GeofenceApp service = new GeofenceApp(locationManager);
        service.onCreate();
        geofenceApp = service;
    }

    private void initHeadUnitServiceMock() {
        IBinder headUnitStub = newTestHeadUnitServerBinder();
        shadowOf(RuntimeEnvironment.application).setComponentNameAndServiceForBindService(
                new ComponentName("com.esrlabs.headunitinterface", "HeadUnit"), headUnitStub);
    }

    private IBinder newTestHeadUnitServerBinder() {
        return new HeadUnit.Stub() {
                @Override
                public void showNotification(String text) throws RemoteException {
                    notificationVisibility.set(true);
                }

                @Override
                public void hideAllNotifications() throws RemoteException {
                    notificationVisibility.set(false);
                }
            };
    }

    private void simulateNewLocation(Location someLocation) {
        shadowLocationManager.simulateLocation(someLocation);
    }


    private Location location(String provider, double latitude, double longitude) {
        Location location = new Location(provider);
        location.setLatitude(latitude);
        location.setLongitude(longitude);
        location.setTime(System.currentTimeMillis());
        return location;
    }

}