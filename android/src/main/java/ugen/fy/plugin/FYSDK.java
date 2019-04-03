package ugen.fy.plugin;

import android.app.Application;
import android.content.Context;
import android.text.TextUtils;
import android.util.Log;

import com.alibaba.sdk.android.openaccount.OpenAccountSDK;
import com.alibaba.sdk.android.openaccount.OpenAccountService;
import com.alibaba.sdk.android.openaccount.callback.InitResultCallback;
import com.alibaba.wireless.security.jaq.JAQException;
import com.alibaba.wireless.security.jaq.SecurityInit;
import com.aliyun.alink.business.devicecenter.api.add.AddDeviceBiz;
import com.aliyun.alink.business.devicecenter.api.add.DeviceInfo;
import com.aliyun.alink.business.devicecenter.api.add.IAddDeviceListener;
import com.aliyun.alink.business.devicecenter.api.add.LinkType;
import com.aliyun.alink.business.devicecenter.api.add.ProvisionStatus;
import com.aliyun.alink.business.devicecenter.api.discovery.DiscoveryType;
import com.aliyun.alink.business.devicecenter.api.discovery.IDeviceDiscoveryListener;
import com.aliyun.alink.business.devicecenter.api.discovery.IOnDeviceTokenGetListener;
import com.aliyun.alink.business.devicecenter.api.discovery.LocalDeviceMgr;
import com.aliyun.alink.business.devicecenter.base.DCErrorCode;
import com.aliyun.alink.linksdk.channel.core.base.AError;
import com.aliyun.alink.linksdk.channel.mobile.api.IMobileConnectListener;
import com.aliyun.alink.linksdk.channel.mobile.api.IMobileDownstreamListener;
import com.aliyun.alink.linksdk.channel.mobile.api.IMobileRequestListener;
import com.aliyun.alink.linksdk.channel.mobile.api.IMobileSubscrbieListener;
import com.aliyun.alink.linksdk.channel.mobile.api.MobileChannel;
import com.aliyun.alink.linksdk.channel.mobile.api.MobileConnectConfig;
import com.aliyun.alink.linksdk.channel.mobile.api.MobileConnectState;
import com.aliyun.alink.linksdk.tools.ALog;
import com.aliyun.iot.aep.sdk.apiclient.IoTAPIClient;
import com.aliyun.iot.aep.sdk.apiclient.IoTAPIClientFactory;
import com.aliyun.iot.aep.sdk.apiclient.IoTAPIClientImpl;
import com.aliyun.iot.aep.sdk.apiclient.adapter.APIGatewayHttpAdapterImpl;
import com.aliyun.iot.aep.sdk.apiclient.callback.IoTCallback;
import com.aliyun.iot.aep.sdk.apiclient.emuns.Env;
import com.aliyun.iot.aep.sdk.apiclient.emuns.Scheme;
import com.aliyun.iot.aep.sdk.apiclient.hook.IoTAuthProvider;
import com.aliyun.iot.aep.sdk.apiclient.request.IoTRequest;
import com.aliyun.iot.aep.sdk.apiclient.request.IoTRequestBuilder;
import com.aliyun.iot.aep.sdk.credential.IoTCredentialProviderImpl;
import com.aliyun.iot.aep.sdk.credential.IotCredentialManager.IoTCredentialListener;
import com.aliyun.iot.aep.sdk.credential.IotCredentialManager.IoTCredentialManage;
import com.aliyun.iot.aep.sdk.credential.IotCredentialManager.IoTCredentialManageError;
import com.aliyun.iot.aep.sdk.credential.IotCredentialManager.IoTCredentialManageImpl;
import com.aliyun.iot.aep.sdk.credential.data.IoTCredentialData;
import com.aliyun.iot.aep.sdk.login.ILoginCallback;
import com.aliyun.iot.aep.sdk.login.ILogoutCallback;
import com.aliyun.iot.aep.sdk.login.LoginBusiness;
import com.facebook.react.bridge.Promise;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.EnumSet;
import java.util.List;
import java.util.Map;

public class FYSDK {
    private static FYSDK mSDK;
    private Context mContext;
    public Application mApplication;
    private EventListener socketEvent;
    private IMobileConnectListener mIMobileConnectListener = new IMobileConnectListener() {
        @Override
        public void onConnectStateChange(MobileConnectState state) {
            ALog.d(TAG,"onConnectStateChange(), state = "+state.toString());
            if(state == MobileConnectState.CONNECTED){


            }
        }
    };

    public static final String TAG = FYSDK.class.getSimpleName();
    public static FYSDK getInstance(Context context,Application application){

        if (mSDK == null){
            mSDK =new FYSDK(context,application);
        }
        return mSDK;
    }

    public FYSDK(Context context,Application application){
        this.mContext = context;
        this.mApplication = application;
        //飞燕初始化
//        try {
//            SecurityInit.Initialize(this.mContext);
//        } catch (JAQException ex) {
//            Log.e(TAG, "security-sdk-initialize-failed");
//        } catch (Exception ex) {
//            Log.e(TAG, "security-sdk-initialize-failed");
//        }

        Log.d(TAG,"FYSDK init");
        // 初始化无线保镖
        try {
            SecurityInit.Initialize(this.mContext);
        } catch (JAQException ex) {
            String errorMsg = ex.getMessage();
            int errorCode = ex.getErrorCode();
            Log.e(TAG, "security-sdk-initialize-failed");
        } catch (Exception ex) {
            Log.e(TAG, "security-sdk-initialize-failed");
        }
//        InitResultCallback callback =  new InitResultCallback() {
//            @Override
//            public void onFailure(int i, String s) {
//                //从这里可以打印出失败原因
//                Log.i(TAG,"init fail   ------"+s);
//            }
//
//            @Override
//            public void onSuccess() {
//                ALog.setLevel(ALog.LEVEL_DEBUG);
//
//                Log.i(TAG,"init success");
//                // 初始化 IoTAPIClient
//                IoTAPIClientImpl.InitializeConfig config = new IoTAPIClientImpl.InitializeConfig();
//                config.host = "api.link.aliyun.com";
//                config.apiEnv = Env.RELEASE;
//                IoTAPIClientImpl impl = IoTAPIClientImpl.getInstance();
//                impl.init(mContext, config);
////                impl.registerTracker(new MainActivity.Tracker());
//
//                String appKey = APIGatewayHttpAdapterImpl.getAppKey(mContext, "114d");
//                try{
//                    //api认证通道
//                    IoTCredentialManageImpl.init(appKey);
//                    IoTAuthProvider provider = new IoTCredentialProviderImpl(IoTCredentialManageImpl.getInstance(FYSDK.this.mApplication));
//                    impl.registerIoTAuthProvider("iotAuth", provider);
//                }catch (Exception e){
//                    Log.e(TAG,e.getMessage(),e);
//                }
//
//                //长连接初始化
//                MobileConnectConfig mobileConfig = new MobileConnectConfig();
//                // 设置 appKey 和 authCode(必填)
//                mobileConfig.appkey =appKey;
//                mobileConfig.securityGuardAuthcode = "114d";
//                MobileChannel.getInstance().startConnect(mContext, mobileConfig, mIMobileConnectListener);
//            }
//        };
//
//        LoginBusiness.init(this.mContext,new OALoginAdapter(this.mContext,callback),"ONLINE");
        LoginBusiness.init(this.mContext, new OALoginAdapter(this.mContext, new InitResultCallback() {
            @Override
            public void onSuccess() {
                ALog.setLevel(ALog.LEVEL_DEBUG);

                Log.i(TAG,"init success");
                // 初始化 IoTAPIClient
                IoTAPIClientImpl.InitializeConfig config = new IoTAPIClientImpl.InitializeConfig();
                config.host = "api.link.aliyun.com";
                config.apiEnv = Env.RELEASE;
                IoTAPIClientImpl impl = IoTAPIClientImpl.getInstance();
                impl.init(mContext, config);
//                impl.registerTracker(new MainActivity.Tracker());

                String appKey = APIGatewayHttpAdapterImpl.getAppKey(mContext, "114d");
                try{
                    //api认证通道
                    IoTCredentialManageImpl.init(appKey);
                    IoTAuthProvider provider = new IoTCredentialProviderImpl(IoTCredentialManageImpl.getInstance(FYSDK.this.mApplication));
                    impl.registerIoTAuthProvider("iotAuth", provider);
                }catch (Exception e){
                    Log.e(TAG,e.getMessage(),e);
                }

                //长连接初始化
                MobileConnectConfig mobileConfig = new MobileConnectConfig();
                // 设置 appKey 和 authCode(必填)
                mobileConfig.appkey =appKey;
                mobileConfig.securityGuardAuthcode = "114d";
                MobileChannel.getInstance().startConnect(mContext, mobileConfig, mIMobileConnectListener);

            }

            @Override
            public void onFailure(int i, String s) {

                Log.d(TAG,s);
            }
        }),false,"ONLINE");
    }
    //登录
    public void login(ILoginCallback callback){
        LoginBusiness.login(callback);
    }
    //退出登录
    public void logout(ILogoutCallback callback){
        LoginBusiness.logout(callback);
    }
    //登录状态
    public boolean isLogin(){
        return LoginBusiness.isLogin();
    }
    //搜寻设备
    public void startScanLocalDevice(final EventListener event, EnumSet<DiscoveryType> enumSet){
        IDeviceDiscoveryListener listener = new IDeviceDiscoveryListener() {
            @Override
            public void onDeviceFound(DiscoveryType discoveryType, List<DeviceInfo> list) {
                Log.i(TAG,"find devices:"+list.size());
                for (int i = 0;i<list.size();i++){
                    DeviceInfo deviceInfo = list.get(i);
                    JSONObject device = new JSONObject();
                    try {
                        device.put("deviceName", deviceInfo.deviceName);
                        device.put("productKey", deviceInfo.productKey);
                        if (!TextUtils.isEmpty(deviceInfo.token)) {
                            device.put("token", deviceInfo.token);
                        }
                        device.put("by","scanLocation");
                        event.onEvent("scanLocationDevice",device);
                    }catch (JSONException e){
                        Log.e(TAG,e.getMessage());
                    }
                }
            }
        };
        LocalDeviceMgr.getInstance().startDiscovery(this.mContext,enumSet,null,listener);
    }
    //停止搜索设备
    public void stopScanLocalDevice(){
        LocalDeviceMgr.getInstance().stopDiscovery();
    }
    //添加配网设备
    public void startAddDevice(Context context, String productKey, String deviceName, final EventListener event){
        DeviceInfo deviceInfo = new DeviceInfo();
        deviceInfo.productKey = productKey; // 商家后台注册的 productKey，不可为空
        deviceInfo.deviceName = deviceName;// 设备名, 可为空
        deviceInfo.linkType = LinkType.ALI_DEFAULT.getName();
        //设置待添加设备的基本信息
        AddDeviceBiz.getInstance().setDevice(deviceInfo);
        // 设置配网模式
        AddDeviceBiz.getInstance().setAliProvisionMode(LinkType.ALI_BROADCAST.getName());
        IAddDeviceListener listener = new IAddDeviceListener() {
            @Override
            public void onPreCheck(boolean b, DCErrorCode dcErrorCode) {
                Log.i(TAG,"onPreCheck");
                JSONObject json = new JSONObject();
                try {
                    json.put("state","onPreCheck");
                    if(!b) {
                        json.put("result", dcErrorCode.code);
                        json.put("codeName",dcErrorCode.codeName);
                    }
                } catch (JSONException e) {
                    e.printStackTrace();
                }
                event.onEvent("onProvisionedResult",json);
            }

            @Override
            public void onProvisionPrepare(int i) {
                JSONObject json = new JSONObject();
                try {
                    json.put("state","onProvisionPrepare");
                    json.put("result",String.valueOf(i));
                } catch (JSONException e){
                    e.printStackTrace();
                }
                event.onEvent("onProvisionedResult",json);
            }

            @Override
            public void onProvisioning() {
                event.onEvent("onProvisionStatus",null);
            }

            @Override
            public void onProvisionStatus(ProvisionStatus provisionStatus) {
                Log.i(TAG,"onProvisionStatus");
                JSONObject json = new JSONObject();
                try {
                    json.put("result",provisionStatus.code());
                    json.put("state","onProvisionStatus");
                } catch (JSONException e) {
                    e.printStackTrace();
                }
                event.onEvent("onProvisionedResult",json);
            }

            @Override
            public void onProvisionedResult(boolean b, DeviceInfo deviceInfo, DCErrorCode dcErrorCode) {
                Log.i(TAG,"onProvisionedResult");
                JSONObject device = new JSONObject();
                try {
                    if(b) {
                        device.put("deviceName", deviceInfo.deviceName);
                        device.put("productKey", deviceInfo.productKey);
                        if (!TextUtils.isEmpty(deviceInfo.token)) {
                            device.put("token", deviceInfo.token);
                        }else {
                            device.put("token","");
                        }
                        JSONObject eventJson = new JSONObject();
                        try {
                            eventJson.put("state","onProvisionedResult");
                            eventJson.put("result",device);
                        } catch (JSONException e){
                            event.onEvent("error",null);
                        }
                        event.onEvent("onProvisionedResult",eventJson);
                    }else{
                        event.onEvent("error",device);
                    }
                } catch (JSONException e) {
                    event.onError("error", e);
                }
            }
        };
        AddDeviceBiz.getInstance().startAddDevice(context,listener);
    }
    //停止添加设备
    public void stopAddDevice(){
        AddDeviceBiz.getInstance().stopAddDevice();
    }
    //添加配网的wifi信息
    public void toggleProvision(String ssid,String password,int timeout){
        AddDeviceBiz.getInstance().toggleProvision(ssid, password, timeout);
    }
    //获取设备token
    public void getDeviceToken(String productKey, String deviceName,String timeout, final Promise promise){
        Integer time = Integer.valueOf(timeout);
        IOnDeviceTokenGetListener listener = new IOnDeviceTokenGetListener() {
            @Override
            public void onSuccess(String s) {
                promise.resolve(s);
            }
            @Override
            public void onFail(String s) {
                promise.reject("567",s);
            }
        };
        LocalDeviceMgr.getInstance().getDeviceToken(mContext,productKey,deviceName,time *1000, listener);
    }
    public void getRefreshIotToken(IoTCredentialListener listener){
        IoTCredentialManage ioTCredentialManage = IoTCredentialManageImpl.getInstance(mApplication);
        ioTCredentialManage.asyncRefreshIoTCredential(listener);
    }
    //开启长连接
    public void startAliSocketListener(final EventListener event){
        socketEvent = event;
        //token刷新callback
        IoTCredentialListener listener = new IoTCredentialListener() {
            @Override
            public void onRefreshIoTCredentialSuccess(IoTCredentialData ioTCredentialData) {

                MobileChannel.getInstance().bindAccount(ioTCredentialData.iotToken, mobileRequestListener);
            }

            @Override
            public void onRefreshIoTCredentialFailed(IoTCredentialManageError ioTCredentialManageError) {

            }
        };
        //开启长连接前需要刷新token
        this.getRefreshIotToken(listener);
    }
    final IMobileDownstreamListener mobileDownstreamListener = new IMobileDownstreamListener() {
        @Override
        public void onCommand(String s, String s1) {
            Log.d(TAG,s+"==============="+s1);
            JSONObject json = new JSONObject();
            try {
                json.put("s1",s1);
                json.put("state",s);
                socketEvent.onEvent("sokectBack",json);
            } catch (JSONException e) {
                e.printStackTrace();
            }
        }

        @Override
        public boolean shouldHandle(String s) {
            return false;
        }
    };
    final IMobileSubscrbieListener mobileSubscrbieListener = new IMobileSubscrbieListener() {
        @Override
        public void onSuccess(String s) {
            MobileChannel.getInstance().registerDownstreamListener(true,mobileDownstreamListener);
            JSONObject json = new JSONObject();
            try {
                json.put("state", "onSuccess");

                socketEvent.onEvent("listenerSuccess",json);

            } catch (JSONException e) {
                socketEvent.onError("error", e);
            }
        }

        @Override
        public void onFailed(String s, AError aError) {

        }

        @Override
        public boolean needUISafety() {
            return false;
        }
    };
    final IMobileRequestListener mobileRequestListener = new IMobileRequestListener() {
        @Override
        public void onSuccess(String s) {
            MobileChannel.getInstance().subscrbie("#",mobileSubscrbieListener);
        }

        @Override
        public void onFailure(AError aError) {

        }
    };
    //关闭长连接
    public void stopAliSocketListener(){
        MobileChannel.getInstance().unRegisterDownstreamListener(mobileDownstreamListener);
        MobileChannel.getInstance().unSubscrbie("#",mobileSubscrbieListener);
        MobileChannel.getInstance().unRegisterConnectListener(mIMobileConnectListener);
    }
    //获取长连接连接状态
    public MobileConnectState getAliSocketListenerState(){
        return MobileChannel.getInstance().getMobileConnectState();
    }
    //获取账户验证信息
    public void getAccountCredential(final Promise promise){

    }
    //获取账号信息
    public void getCurrentAccountMessage(final Promise promise) throws JSONException {
        Map<String,Object> param=new com.alibaba.fastjson.JSONObject();
        param= OpenAccountSDK.getService(OpenAccountService.class).getSession().getOtherInfo();
        Log.d(TAG,"==========----------++++"+param.get("openaccount_other_info").toString());
        Map<String,Object> userInfo = (Map<String, Object>) param.get("openaccount_other_info");
        Log.d(TAG,userInfo.toString());
        JSONObject data = new JSONObject();
        data.putOpt("mobile",userInfo.get("mobile"));
        promise.resolve(data);
    }
    public void send(String path, Map parmas,String version, boolean needAuth, IoTCallback callback){
        IoTRequestBuilder builder = new IoTRequestBuilder()
                .setScheme(Scheme.HTTPS)
                .setPath(path) // 参考业务API文档，设置path
                .setApiVersion(version)  // 参考业务API文档，设置apiVersion
                .setParams(parmas);
        if(needAuth){
            builder.setAuthType("iotAuth");
        }
        IoTRequest request = builder.build();
        // 获取Client实例，并发送请求
        IoTAPIClient ioTAPIClient = new IoTAPIClientFactory().getClient();

        ioTAPIClient.send(request, callback);
    }
}
