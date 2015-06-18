package com.esrlabs.geofence;

import android.app.Service;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Bundle;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;

import com.esrlabs.headunitinterface.HeadUnit;

import java.util.List;

/**
 * Steps:
 * - register to the location provider
 * - connect to the HeadUnitService
 * - build geofence object
 * - implement the exercise logic (when the user is outside of the geofence show popup; hide it otherwise)
 *
 * See:
 * - that tests are green
 * - that the notification appears in the emulator
 */
public class GeofenceApp extends Service implements LocationListener {

    public static final String TAG = "GeofenceApp";
    public static final String CAN_PROVIDER = "CanLocationProvider";


}