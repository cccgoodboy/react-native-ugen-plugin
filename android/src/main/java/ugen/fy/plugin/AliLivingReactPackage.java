package ugen.fy.plugin;

import android.app.Application;

import com.facebook.react.ReactPackage;
import com.facebook.react.bridge.NativeModule;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.uimanager.ViewManager;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class AliLivingReactPackage implements ReactPackage {
    private Application mActivity;
    public AliLivingReactPackage(Application application){
        super();
        this.mActivity = application;
    }
    @Override
    public List<NativeModule> createNativeModules(ReactApplicationContext reactContext) {
        List<NativeModule>modules = new ArrayList<>();
        modules.add(new AliLiving(reactContext,mActivity));
        return modules;
    }

    @Override
    public List<ViewManager> createViewManagers(ReactApplicationContext reactContext) {
        return  Collections.emptyList();
    }
}
