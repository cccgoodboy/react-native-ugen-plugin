package com.hotata.keyoolot.RNModule.AliLiving;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.content.Context;
import android.os.Build;
import android.support.v4.app.NotificationCompat;
import android.util.Log;

import com.alibaba.sdk.android.push.MessageReceiver;
import com.alibaba.sdk.android.push.notification.CPushMessage;
import com.facebook.react.bridge.ReactApplicationContext;
import com.hotata.keyoolot.R;

import java.util.Map;

import static android.content.Context.NOTIFICATION_SERVICE;

public class AliMessageReceiver extends MessageReceiver {
    public static final String REC_TAG = "receiver";
    private EventListener mEvent;
    private ReactApplicationContext mContext;
    private FYSDK sdk;
    @Override
    public void onNotification(Context context, String title, String summary, Map<String, String> extraMap) {

        // TODO 处理推送通知
        Log.e("MyMessageReceiver", "Receive notification, title: " + title + ", summary: " + summary + ", extraMap: " + extraMap);
    }
    @Override
    public void onMessage(Context context, CPushMessage cPushMessage) {

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O){
            String id = "123";
            String name= "好太太智联推送";
            NotificationManager notificationManager = (NotificationManager) context.getApplicationContext().getSystemService(NOTIFICATION_SERVICE);
            Notification notification = null;
//        Intent intent = new Intent(context.getApplicationContext(), RNMainActivity.class);//点击之后进入MainActivity
//        PendingIntent pendingIntent = PendingIntent.getActivity(context.getApplicationContext(), 0, intent, PendingIntent.FLAG_UPDATE_CURRENT);
            android.support.v4.app.NotificationCompat.BigTextStyle style = new android.support.v4.app.NotificationCompat.BigTextStyle();
            style.bigText(cPushMessage.getContent());
            style.setBigContentTitle(cPushMessage.getTitle());

            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
                Notification.BigTextStyle bigStyle = new Notification.BigTextStyle();
                bigStyle.bigText(cPushMessage.getContent());
                bigStyle.setBigContentTitle(cPushMessage.getTitle());
                NotificationChannel mChannel = new NotificationChannel(id, name, NotificationManager.IMPORTANCE_LOW);
                Log.i("2222", mChannel.toString());
                notificationManager.createNotificationChannel(mChannel);
                notification = new Notification.Builder(context.getApplicationContext(),id)
                        .setChannelId(id)
                        .setContentTitle(cPushMessage.getTitle())
                        .setContentText(cPushMessage.getContent())
                        .setWhen(System.currentTimeMillis())
                        .setShowWhen(true)
                        .setStyle(bigStyle)
                        .setAutoCancel(true)//点击后消失

//                    .setContentIntent(pendingIntent)//设置意图
                        .setSmallIcon(R.drawable.ic_app_icon).build();
            } else {
                NotificationCompat.Builder notificationBuilder = new NotificationCompat.Builder(context.getApplicationContext(),id)
                        .setContentTitle(cPushMessage.getTitle())
                        .setContentText(cPushMessage.getContent())
                        .setSmallIcon(R.drawable.ic_app_icon)
                        .setAutoCancel(true)//点击后消失
                        .setStyle(style)
//                    .setContentIntent(pendingIntent)//设置意图
                        .setOngoing(false).setChannelId(id).setWhen(System.currentTimeMillis()).setShowWhen(true);
                notification = notificationBuilder.build();
            }
            notificationManager.notify(111123, notification);
        }
//        JSONObject json = new JSONObject();
//        try {
//
//            json.put("messageId", cPushMessage.getMessageId());
//            json.put("title", cPushMessage.getTitle());
//            json.put("content", cPushMessage.getContent());
//            mContext = (ReactApplicationContext) context;
//            mContext.getJSModule(DeviceEventManagerModule.RCTDeviceEventEmitter.class)
//                    .emit("PushNotifyAndroid",JsonConvert.jsonToReact(json));
//
//        } catch (JSONException e) {
//            mEvent.onError("error", e);
//        }

        Log.e("MyMessageReceiver", "onMessage, messageId: " + cPushMessage.getMessageId() + ", title: " + cPushMessage.getTitle() + ", content:" + cPushMessage.getContent() + "content" + context.toString());
    }
    @Override
    public void onNotificationOpened(Context context, String title, String summary, String extraMap) {
        Log.e("MyMessageReceiver", "onNotificationOpened, title: " + title + ", summary: " + summary + ", extraMap:" + extraMap);
    }
    @Override
    protected void onNotificationClickedWithNoAction(Context context, String title, String summary, String extraMap) {
        Log.e("MyMessageReceiver", "onNotificationClickedWithNoAction, title: " + title + ", summary: " + summary + ", extraMap:" + extraMap);
    }
    @Override
    protected void onNotificationReceivedInApp(Context context, String title, String summary, Map<String, String> extraMap, int openType, String openActivity, String openUrl) {
        Log.e("MyMessageReceiver", "onNotificationReceivedInApp, title: " + title + ", summary: " + summary + ", extraMap:" + extraMap + ", openType:" + openType + ", openActivity:" + openActivity + ", openUrl:" + openUrl);
    }
    @Override
    protected void onNotificationRemoved(Context context, String messageId) {
        Log.e("MyMessageReceiver", "onNotificationRemoved");
    }
}
