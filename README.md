
## 模块：react-native-ugen-plugin

安装
```
npm install react-native-ugen-plugin --registry=http://192.168.2.91:7001
```

引用
```
import NativePlugin from 'react-native-ugen-plugin'
```


### 方法

#### 1.gotoTmall()  跳转天猫商城

参数：

 参数名                   | 参数类型   | 是否必选 | 默认值   | 描述
---------------------- | ------ | -------- | --------- | -----------
 shopId          |String  |Y     |           | 跳转的商铺ID
 
 返回值：无

##### exmple
```
NativePlugin.gotoTmall('62890059');

```

#### 2.getCurrentAppMessage()  获取当前App信息

参数：无

返回值：Promise

 参数名                   | 参数类型   | 是否必选 | 默认值   | 描述
---------------------- | ------ | -------- | --------- | -----------
 AppName          |String  |Y     |           | App名称
  AppVersion          |String  |Y     |           | App版本号
##### exmple
```
NativePlugin.getCurrentAppMessage();
```

#### 3.openUrlByWebBrowser()  打开某网页链接

参数：无

返回值：Promise

 参数名                   | 参数类型   | 是否必选 | 默认值   | 描述
---------------------- | ------ | -------- | --------- | -----------
isSuccess          |Bool  |Y     |           | 是否打开成功

##### exmple
```
NativePlugin.openUrlByWebBrowser('www.baidu.com');
```
#### 4.openAppStore()  打开App下载商城（iOS: AppStrore,android:应用宝）

参数：无

返回值：无

##### exmple
```
NativePlugin.openAppStore();
```
#### 5.checkPermission()  检查应用权限

参数：

 参数名                   | 参数类型   | 是否必选 | 默认值   | 描述
---------------------- | ------ | -------- | --------- | -----------
permissonArr         |Array  |Y     |           | 要打开的权限数组

返回值：Promise

 参数名                   | 参数类型   | 是否必选 | 默认值   | 描述
---------------------- | ------ | -------- | --------- | -----------
stateArr         |Array  |Y     |           | 权限结果回调数组


#### 6.showContact()  打开通讯录

参数：无

返回值：无


#### 7.getSSID()  获取当前wifi账号

参数：无

返回值：Promise

 参数名                   | 参数类型   | 是否必选 | 默认值   | 描述
---------------------- | ------ | -------- | --------- | -----------
ssid        |String  |Y     |           | wifi名

