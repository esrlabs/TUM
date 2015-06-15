package esrlabs.com.geofence;

import android.test.ServiceTestCase;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.*;


public class MyServiceTest extends ServiceTestCase {


    public MyServiceTest() {
        super(MyService.class);
    }

    @Before
    public void setUp() throws Exception {

    }

    @After
    public void tearDown() throws Exception {

    }

    @Test
    public void testLatestLocation() throws Exception {
        assert(false);
    }
}