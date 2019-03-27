package ugen.fy.plugin;

import android.app.Application;
import android.util.Log;

import com.aliyun.alink.business.devicecenter.api.discovery.DiscoveryType;
import com.aliyun.iot.aep.sdk.apiclient.callback.IoTCallback;
import com.aliyun.iot.aep.sdk.apiclient.callback.IoTResponse;
import com.aliyun.iot.aep.sdk.apiclient.request.IoTRequest;
import com.aliyun.iot.aep.sdk.credential.IotCredentialManager.IoTCredentialListener;
import com.aliyun.iot.aep.sdk.login.ILoginCallback;
import com.aliyun.iot.aep.sdk.login.ILogoutCallback;
import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.WritableMap;
import com.facebook.react.modules.core.DeviceEventManagerModule;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.EnumSet;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class AliLiving extends ReactContextBaseJavaModule {
    public static final String TAG = AliLiving.class.getSimpleName();
    private ReactApplicationContext mContext;
    private FYSDK sdk;
    public AliLiving(ReactApplicationContext reactContext,Application application) {
        super(reactContext);
        mContext = reactContext;
        this.sdk = FYSDK.getInstance(reactContext, application);
        this.mContext = reactContext;
    }
    @Override
    public String getName() {
        return "AliLiving";
    }
    @ReactMethod
    public void login(final Promise promise){
        ILoginCallback var = new ILoginCallback() {
            @Override
            public void onLoginSuccess() {
                promise.resolve("success");
            }
            @Override
            public void onLoginFailed(int i, String s) {
                promise.reject(String.valueOf(i),s);
            }
        };
        this.sdk.login(var);
    }
    @ReactMethod
    public void logout(final Promise promise){
        ILogoutCallback callback = new ILogoutCallback() {
            @Override
            public void onLogoutSuccess() {
                promise.resolve("success");
            }

            @Override
            public void onLogoutFailed(int i, String s) {
                promise.reject(String.valueOf(i),s);
            }
        };
        this.sdk.logout(callback);
    }
    @ReactMethod
    public void isLogin(Promise promise){
        if (this.sdk.isLogin()){
            promise.resolve(this.sdk.isLogin());
        }else {
            promise.reject("401","未登录");
        }
    }
    @ReactMethod
    public void startScanLocalDevice(){

        try{
            EventListener listener = new EventListener() {
                @Override
                void onEvent(String event, JSONObject json) {
                    Log.i(TAG,event);
                    try {
                        if(json != null)
                            sendEvent(event,JsonConvert.jsonToReact(json));
                        else
                            sendEvent(event);
                    } catch (JSONException e) {
                        sendErrorEvent(e.getMessage());
                    }
                }
            };
            Log.i(TAG,"startAddDevice:"+listener);
            EnumSet<DiscoveryType> enumSet = EnumSet.allOf(DiscoveryType.class);
            this.sdk.startScanLocalDevice(listener, enumSet);
        }catch (Exception e){
            sendErrorEvent(e.getMessage());
        }
    }
    @ReactMethod
    public void stopScanLocalDevice(){
        this.sdk.stopScanLocalDevice();
    }
    @ReactMethod
    public void startAddDevice(String productKey){
        Log.i(TAG,"startAddDevice");
        try{
            EventListener listener = new EventListener() {
                @Override
                void onEvent(String event, JSONObject json) {
                    Log.i(TAG,event);
                    try {
                        if(json != null)
                            sendEvent(event,JsonConvert.jsonToReact(json));
                        else
                            sendEvent(event);
                    } catch (JSONException e) {
                        sendErrorEvent(e.getMessage());
                    }
                }
            };
            Log.i(TAG,"startAddDevice:"+listener);
            this.sdk.startAddDevice(mContext, productKey,"",listener);
        }catch (Exception e){
            sendErrorEvent(e.getMessage());
        }
    }
    @ReactMethod
    public void stopAddDevice(){
        this.sdk.stopAddDevice();
    }

    @ReactMethod
    public void toggleProvision(String ssid,String password,int timeout){
        Log.d(TAG,"toggleProvision:"+ssid+"-"+password+"-"+timeout);
        this.sdk.toggleProvision(ssid,password,timeout);
    }
    @ReactMethod
    public void getDeviceToken(String productKey,String deviceName,String timeout,final Promise promise){
        this.sdk.getDeviceToken(productKey,deviceName,timeout,promise);
    }
    @ReactMethod
    public void startAliSocketListener(){

        try {
            EventListener listener = new EventListener() {
                @Override
                void onEvent(String event, JSONObject json) {
                    Log.i(TAG,event);
                    try {
                        if(json != null)
                            sendEvent(event,JsonConvert.jsonToReact(json));
                        else
                            sendEvent(event);
                    } catch (JSONException e) {
                        sendErrorEvent(e.getMessage());
                    }
                }
            };
            this.sdk.startAliSocketListener(listener);
        }catch (Exception e){
            sendErrorEvent(e.getMessage());
        }
    }
    @ReactMethod
    public void stopAliSocketListener(){
        this.sdk.stopAliSocketListener();
    }
    @ReactMethod
    public void getAliSocketListenerState(final Promise promise){
        promise.resolve(this.sdk.getAliSocketListenerState());
    }
    @ReactMethod
    public void getCurrentAccountMessage(final Promise promise) throws JSONException {
        this.sdk.getCurrentAccountMessage(promise);
    }
    @ReactMethod
    public void send(String path, String params, String version, boolean needAuth, final Promise promise){
        Map<String, Object> json = this.parseJSONString(params);
        if(json.isEmpty()){
            json = new HashMap<String, Object>();
        }

        this.sdk.send(path, json, version, needAuth, new IoTCallback() {
            @Override
            public void onFailure(IoTRequest ioTRequest, Exception e) {
                promise.reject(e.getMessage(),e);
            }

            @Override
            public void onResponse(IoTRequest ioTRequest, IoTResponse ioTResponse) {
                int code = ioTResponse.getCode();

                // 200 代表成功
                if(200 != code){
                    String message = ioTResponse.getMessage();
                    promise.reject(String.valueOf(code),message);
                    return;
                }
                Object dataJson = ioTResponse.getData();
                Log.d(TAG,"------========="+dataJson.toString());
                if (AliLiving.isEmpty(dataJson)){
                    promise.resolve(ioTResponse.getData());
                }else {
                    JSONObject data = new JSONObject();
//                    JSONObject data = (JSONObject) dataJson;
                    try {
                        data.put("data",dataJson);
                        promise.resolve(data.toString());
                    } catch (JSONException e) {
                        promise.resolve("");
                        e.printStackTrace();
                    }
                }
            }
        });
    }
    public static HashMap<String, Object> parseJSONString(String json) {
        JSONObject obj;
        try{
            obj =new JSONObject(json);
            return parseJSONObject(obj);
        }catch(JSONException e) {
            e.printStackTrace();
        }
        return new HashMap<String, Object>();
    }
    public static HashMap<String, Object> parseJSONObject(JSONObject jsonobj){
        JSONArray a_name = jsonobj.names();
        HashMap<String, Object> map =new HashMap<String, Object>();
        if(a_name !=null) {
            int i =0;
            while(i < a_name.length()) {
                String key;
                try{
                    key = a_name.getString(i);
                    Object obj = jsonobj.get(key);
                    map.put(key,parseUnknowObjectToJson(obj));
                }catch(JSONException e) {
                    e.printStackTrace();
                }
                i++;
            }
        }
        return map;
    }
    private static Object parseUnknowObjectToJson(Object o) {
        if(o instanceof JSONObject) {
            return parseJSONObject((JSONObject)o);
        }
        else if (o instanceof JSONArray) {
            return parseJSONArray((JSONArray)o);
        }
        return o;
    }

    public static ArrayList<Object> parseJSONArray(JSONArray jsonarr) {
        ArrayList<Object> list =new ArrayList<Object>();
        int len = jsonarr.length();
        for(int i =0; i < len; i++) {
            Object o;
            try{
                o = jsonarr.get(i);
                list.add(parseUnknowObjectToJson(o));
            }catch(JSONException e) {
                e.printStackTrace();
            }
        }
        return list;
    }
    public static boolean isEmpty(Object obj)
    {
        if (obj == null)
        {
            return true;
        }
        if ((obj instanceof List))
        {
            return ((List) obj).size() == 0;
        }
        if ((obj instanceof String))
        {
            return ((String) obj).trim().equals("");
        }
        return false;
    }
    private void sendErrorEvent(String str){
        sendEvent("error",str);
    }

    private void sendEvent(String eventName,WritableMap params) {
        this.mContext
                .getJSModule(DeviceEventManagerModule.RCTDeviceEventEmitter.class)
                .emit(eventName, params);
    }

    private void sendEvent(String eventName,String str) {
        this.mContext
                .getJSModule(DeviceEventManagerModule.RCTDeviceEventEmitter.class)
                .emit(eventName,str);
    }

    private void sendEvent(String eventName) {
        this.sendEvent(eventName,"");
    }
}
