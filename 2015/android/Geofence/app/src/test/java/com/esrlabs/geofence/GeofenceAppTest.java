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
public class GeofenceAppTest extends ServiceTestCase {

    public final LocationManager locationManager = (LocationManager)
            RuntimeEnvironment.application.getSystemService(Context.LOCATION_SERVICE);
    private GeofenceApp geofenceApp;


    private final Location someLocation = location(CAN_PROVIDER, 12.0, 20.0);



    public GeofenceAppTest() {
        super(GeofenceApp.class);
    }

    @Before
    public void setUp() throws Exception {
        geofenceApp = setupMyService(locationManager);
    }

    @After
    public void tearDown() throws Exception { }

    @Test
    public void testLatestLocation() throws Exception {
        simulateNewLocation(locationManager, someLocation);
        assertTrue(someLocation.equals(geofenceApp.latestLocation()));
    }

    private GeofenceApp setupMyService(LocationManager locationManager) {
        GeofenceApp service = new GeofenceApp(locationManager);
        service.onCreate();
        return service;
    }

    private void simulateNewLocation(LocationManager locationManager, Location someLocation) {
        ShadowLocationManager shadowLocationManager = shadowOf(locationManager);
        shadowLocationManager.simulateLocation(someLocation);
    }

    @Test
    public void testThatPopupIsShownWhenTheCurrentLocationIsOutsideTheGeofence() throws Exception {
        final AtomicBoolean notificationVisibility = new AtomicBoolean(false);

        initHeadUnitServiceMock(notificationVisibility);
        GeofenceApp mainService = setupMyService(locationManager);

//        Location locationInsideTheGeofence = location(CAN_PROVIDER, 10, 10);
//        simulateNewLocation(locationManager, locationInsideTheGeofence);
//        assertTrue(locationInsideTheGeofence.equals(mainService.latestLocation()));
//        assertFalse(notificationVisibility.get());

        Location locationOutsideTheGeofence = location(CAN_PROVIDER, 11, 11);
        simulateNewLocation(locationManager, locationOutsideTheGeofence);
        assertTrue(locationOutsideTheGeofence.equals(mainService.latestLocation()));
        assertTrue(notificationVisibility.get());
    }

    private void initHeadUnitServiceMock(AtomicBoolean notificationVisibility) {
        IBinder headUnitStub = getHeadUnitServiceBinder(notificationVisibility);
        shadowOf(RuntimeEnvironment.application).setComponentNameAndServiceForBindService(
                new ComponentName("com.esrlabs.headunitinterface", "HeadUnit"), headUnitStub);
    }

    private IBinder getHeadUnitServiceBinder(final AtomicBoolean notificationVisibility) {
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


    private Location location(String provider, double latitude, double longitude) {
        Location location = new Location(provider);
        location.setLatitude(latitude);
        location.setLongitude(longitude);
        location.setTime(System.currentTimeMillis());
        return location;
    }

}