package esrlabs.com.geofence;

import static esrlabs.com.geofence.MyService.CAN_PROVIDER;

import android.content.Context;
import android.location.Location;
import android.location.LocationManager;
import android.test.ServiceTestCase;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.robolectric.RobolectricGradleTestRunner;
import org.robolectric.RuntimeEnvironment;
import org.robolectric.Shadows;
import org.robolectric.annotation.Config;
import org.robolectric.shadows.ShadowLocationManager;


@RunWith(RobolectricGradleTestRunner.class)
@Config(constants = BuildConfig.class, emulateSdk = 17)
public class MyServiceTest extends ServiceTestCase {

    public final LocationManager locationManager = (LocationManager)
            RuntimeEnvironment.application.getSystemService(Context.LOCATION_SERVICE);
    Location someLocation = location(CAN_PROVIDER, 12.0, 20.0);

    public MyServiceTest() {
        super(MyService.class);
    }

    @Before
    public void setUp() throws Exception { }

    @After
    public void tearDown() throws Exception { }

    @Test
    public void testLatestLocation() throws Exception {
        MyService mainService = setupMyService(locationManager);
        simulateNewLocation(locationManager);

        assertTrue(areTheLocationsEqual(someLocation, mainService.latestLocation()));
    }

    private void simulateNewLocation(LocationManager locationManager) {
        ShadowLocationManager shadowLocationManager = Shadows.shadowOf(locationManager);
        shadowLocationManager.simulateLocation(location(CAN_PROVIDER,
                someLocation.getLatitude(), someLocation.getLongitude()));
    }

    private MyService setupMyService(LocationManager locationManager) {
        MyService service = new MyService(locationManager);
        service.onCreate();
        return service;
    }

    private boolean areTheLocationsEqual(Location first, Location second) {
        // timestamp is different 
        if ( (first.getAccuracy() == second.getAccuracy()) &&
                (first.getLatitude() == second.getLatitude()) &&
                (first.getLongitude() == second.getLongitude()) &&
                (first.getAltitude() == second.getAltitude()) ) {
            return true;
        }
        return false;
    }

    private Location location(String provider, double latitude, double longitude) {
        Location location = new Location(provider);
        location.setLatitude(latitude);
        location.setLongitude(longitude);
        location.setTime(System.currentTimeMillis());
        return location;
    }
}