package com.esrlabs.geofence;

import static com.esrlabs.geofence.GeofenceApp.CAN_PROVIDER;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.when;
import static org.robolectric.Shadows.shadowOf;

import android.app.Service;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.location.Location;
import android.location.LocationManager;
import android.os.IBinder;
import android.os.RemoteException;
import android.test.ServiceTestCase;

import com.esrlabs.headunitinterface.HeadUnit;

import junit.framework.TestCase;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.robolectric.Robolectric;
import org.robolectric.RobolectricGradleTestRunner;
import org.robolectric.RuntimeEnvironment;
import org.robolectric.Shadows;
import org.robolectric.annotation.Config;
import org.robolectric.shadows.ShadowLocationManager;

import java.util.concurrent.atomic.AtomicBoolean;

import esrlabs.com.geofence.BuildConfig;


@RunWith(RobolectricGradleTestRunner.class)
@Config(constants = BuildConfig.class, emulateSdk = 17)
public class GeofenceAppTest extends TestCase {

    public final LocationManager locationManager = (LocationManager)
            RuntimeEnvironment.application.getSystemService(Context.LOCATION_SERVICE);
    private GeofenceApp geofenceApp;

    final AtomicBoolean notificationVisibility = new AtomicBoolean(false);
    private final Location someLocation = location(CAN_PROVIDER, 12.0, 20.0);

    @Before
    public void setUp() throws Exception {
        initHeadUnitServiceMock();
        setupMyService();
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

        Location locationOutsideTheGeofence = location(CAN_PROVIDER, 11, 11);
        simulateNewLocation(locationOutsideTheGeofence);
        assertTrue(locationOutsideTheGeofence.equals(geofenceApp.latestLocation()));
        assertTrue(notificationVisibility.get());
    }

    private void setupMyService() {
        GeofenceApp service = new GeofenceApp(locationManager);
        service.onCreate();
        geofenceApp = service;
    }

    private void initHeadUnitServiceMock() {
        IBinder headUnitStub = getHeadUnitServiceBinder();
        shadowOf(RuntimeEnvironment.application).setComponentNameAndServiceForBindService(
                new ComponentName("com.esrlabs.headunitinterface", "HeadUnit"), headUnitStub);
    }

    private IBinder getHeadUnitServiceBinder() {
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
        ShadowLocationManager shadowLocationManager = shadowOf(locationManager);
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