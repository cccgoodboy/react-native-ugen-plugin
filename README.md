
## 模块：react-native-ugen-fy-plugin

安装
```
npm install react-native-ugen-fy-plugin --registry=http://192.168.2.91:7001
```

#### Installation(iOS)

* 将libAliLiving.xcodeproj添加到Libraries目录下面
* 主项目target下Generral的Linked Frameworks and Libraries中添加liblibAliLiving.a
* 主项目target下Build Settings的Search Path中的Header Search Paths添加路径$(SRCROOT)/../node_modules/react-native-ugen-fy-plugin/ios/libAliLiving


#### Installation(Android)

* android/app/build.gradle中  

```
dependencies {
    ...
    // From node_modules
    implementation project(':react-native-ugen-fy-plugin')
}
defaultConfig {
    multiDexEnabled true
    ndk {
        abiFilters 'armeabi', 'x86'
    }
}
```
* android/settings.gradle中

```
include ':react-native-ugen-fy-plugin'
project(':react-native-ugen-fy-plugin').projectDir = new File(rootProject.projectDir, '../node_modules/react-native-ugen-fy-plugin/android')
```

* 在MainApplication.Java中

```
@Override
    protected List<ReactPackage> getPackages() {
      return Arrays.<ReactPackage>asList(
          new MainReactPackage(),
            new AliLivingReactPackage(getApplication()),
      );
    }
```

* 在AndroidManifest.xml中添加权限

```
<uses-permission android:name="android.permission.ACCESS_COARSE_LOCATION"/>
<uses-permission android:name="android.permission.ACCESS_FINE_LOCATION" />
```

* 在AndroidManifest.xml的application标签下添加

```
tools:replace="android:allowBackup”
```

* 组件最低适配android 5  最低sdkVersion请设置18

```
defaultConfig {
    minSdkVersion 18
    targetSdkVersion 26
}
```

### 引用
```
import AliLving from 'react-native-ugen-fy-plugin'
```


### 方法

#### 1.login  登录

参数：无 

返回值信息：  

参数名 | 参数类型| 是否必选 | 默认值 | 描述 |
----- | -----  | ------ | ----- | ---- 
mobile| String |    Y   |       |  返回的登录账号 | 


##### exmple
```
AliLving.login();
```



#### 2.logout  退出登录

参数：无
      

返回值信息：  Promise

参数名 | 参数类型| 是否必选 | 默认值 | 描述 |
----- | -----  | ------ | ----- | ---- 
state | String |    Y   |       |  "success"为退出成功 catch到error位失败 |

##### example

```
AliLving.logout();
``` 



#### 3.startScanLocalDevice  开始搜寻设备


参数：无

返回值：无

##### example

```
AliLving.startScanLocalDevice()
```


#### 4.stopScanLocalDevice  停止搜寻设备

参数：无

返回值：无

##### example 

```
AliLiving.stopScanLocalDevice()
```

#### 5.startAddDevice  添加配网设备

参数

参数名 | 参数类型| 是否必选 | 默认值 | 描述 |
----- | -----  | ------ | ----- | ---- 
productKey | String |   Y   |       |  设备pk |

返回值：无

##### example

```
AliLiving.startAddDevice("a1kM9JAZ7aQ")
```

#### 6.stopAddDevice  中止配网流程

参数：无

返回值：无

##### example 

```
AliLiving.stopAddDevice()
```

#### 7.toggleProvision  添加配网的wifi名和wifi密码

参数：

参数名 | 参数类型| 是否必选 | 默认值 | 描述 |
----- | -----  | ------ | ----- | ---- 
wifiName | String |   Y   |       |  wifi名 |
wifiPassword | String |   Y   |       |  wifi密码 |
timeout | String |   Y   |       |  超时时间（秒） |

返回值：无

##### example

```
AliLiving.toggleProvision('ugen-f','macro_scope00','60')
```

#### 8.getDeviceToken  获取设备token


参数：

参数名 | 参数类型| 是否必选 | 默认值 | 描述 |
----- | -----  | ------ | ----- | ---- 
productKey | String |   Y   |       |  设备pk |
deviceName | String |   Y   |       |  设备dn |
timeout | String |   Y   |       |  超时时间（秒） |

返回值：Promise

参数名 | 参数类型| 是否必选 | 默认值 | 描述 |
----- | -----  | ------ | ----- | ---- 
token | String |    Y   |       |  Promise返回token字符串 |

##### example

```
await AliLiving.getDeviceToken('a1z6OuFHnCS','ugen_test1')
```

#### 9.startAliSocketListener  开启飞燕长连接

参数：无


返回值：Promise

参数名 | 参数类型| 是否必选 | 默认值 | 描述 |
----- | -----  | ------ | ----- | ---- 
isSuccess | String |    Y   |       |  '1'成功，'0'失败 |

##### example

```
await AliLiving.startAliSocketListener()
```


#### 10.stopAliSocketListener  关闭飞燕长连接

参数：无

返回值：Promise

参数名 | 参数类型| 是否必选 | 默认值 | 描述 |
----- | -----  | ------ | ----- | ---- 
isSuccess | String |    Y   |       |  '1'成功，'0'失败 |
##### example

```
await AliLiving.stopAliSocketListener()
```

#### 11.getAliSocketListenerState 获取长连接状态

参数：无

返回值：Promise

参数名 | 参数类型| 是否必选 | 默认值 | 描述 |
----- | -----  | ------ | ----- | ---- 
state| String |    Y   |       |  '1'连接中，'0'断开 |
##### example
```
await AliLiving.getAliSocketListenerState()
```


#### 12.getAccountCredential  获取账户验证信息（iotToken,identifier等）


参数：无

返回值：Promise

参数名 | 参数类型| 是否必选 | 默认值 | 描述 |
----- | -----  | ------ | ----- | ---- 
iotToken| String |    Y   |       |  账号的iotToken |
identityId| String |    Y   |       |  账号的身份凭证 |
##### example
```
await AliLiving.getAccountCredential()
```

#### 13.getCurrentAccountMessage  获取账号信息

参数：无

返回值：Promise

参数名 | 参数类型| 是否必选 | 默认值 | 描述 |
----- | -----  | ------ | ----- | ---- 
mobile| String |    Y   |       |  登录账号 |
##### example
```
await AliLiving.getCurrentAccountMessage()
```

#### 14.send  发送客户端API

参数：

参数名 | 参数类型| 是否必选 | 默认值 | 描述 |
----- | -----  | ------ | ----- | ---- 
path| String |    Y   |       |  请求地址 |
params| String |    Y   |       |  请求参数的json字符串 |
version| String |    Y   |       |  API版本号（对应飞燕） |
iotAuth|Bool |    N   |    true   |  是否需要账号验证 |
success|callback |    N   |       |  请求成功回调 |
error|callback |    N   |       |  请求失败回调 |
complete|callback |    N   |       |  请求完成回调 |

返回值：Promise

参数名 | 参数类型| 是否必选 | 默认值 | 描述 |
----- | -----  | ------ | ----- | ---- 
response|object |    Y   |       |  请求结果返回 |

##### example
```
await AliNetwork.send(iot,{
            path:'/uc/listBindingByAccount',
            ver:'1.0.2',
            iotAuth:true,
            params:{
                pageNo:1,
                pageSize:20
            },
            success:(res)=>{},
            error:(err)=>{},
            complete:()=>{}
        })
``` 


### 相关文档

* [飞燕平台开发文档](https://living.aliyun.com/doc#index.html)
* [配网常见问题排查](https://living.aliyun.com/doc#yet1mi.html)
* [Android常见问题](https://living.aliyun.com/doc#app-android-faq.html)
* [iOS常见问题](https://living.aliyun.com/doc#mobile-ios-faq.html)

### 自定义错误类型

