package com.esrlabs.headunitservicemock;

import android.app.Notification;
import android.app.NotificationManager;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.os.IBinder;
import android.os.RemoteException;

import com.esrlabs.headunitinterface.HeadUnit;

/**
 * A test implementation of the HeadUnit interface
 *
 * Provides a way to run against the interface without the presence of a real headunit
 *
 * Will use the Android UI instead
 */
public class HeadUnitService extends Service {
    public HeadUnitService() {
    }

    @Override
    public IBinder onBind(Intent intent) {
        return binder;
    }

    private final HeadUnit.Stub binder = new HeadUnit.Stub() {
        @Override
        public void showNotification(String text) throws RemoteException {
            Notification.Builder builder = new Notification.Builder(getBaseContext()).setContentText(text).setSmallIcon(R.drawable.tum_logo);
            notificationService().notify(0,builder.build());
        }

        @Override
        public void hideAllNotifications() throws RemoteException {
            notificationService().cancelAll();
        }
    };

    private NotificationManager notificationService() {
        return (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);
    }
}
