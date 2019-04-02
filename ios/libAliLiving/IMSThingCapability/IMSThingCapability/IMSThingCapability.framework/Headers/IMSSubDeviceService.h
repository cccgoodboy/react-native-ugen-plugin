//
//  IMSSubDeviceService.h
//  IMSThingCapability
//
//  Created by 朱永利 on 2018/10/10.
//  Copyright © 2018年 ZhuYongli. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IMSThingBaseDefine.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, IMSSubDeviceServiceError) {
    IMSSubDeviceServiceErrorSuccess = 0,                     ///< 业务成功
    IMSSubDeviceServiceErrorUnknown = 4101,             ///< 客户端内部错误
    IMSSubDeviceServiceErrorInvalidInput = 4102,           ///< 入参错误
    IMSSubDeviceServiceErrorDeviceNotFound = 4103,      ///< 本地搜索时没有发现此设备
    IMSSubDeviceServiceErrorDeviceDisconnected = 4104,      ///< 设备无法连接
    IMSSubDeviceServiceErrorDeviceLoginFailed = 4105,      ///< 设备无法上线
};

@interface IMSSubDeviceService : NSObject



/**
 子设备借助app的长连接通道去云端login

 @param deviceInfo 设备信息，应包含 {"productKey":"pkxxxx", "deviceName":"dnyyy"},
          其中对于ble设备，deviceName其实是ble的MAC地址切记不要传真实的deviceName。
 @param resultBlock 结果回调，如果成功,会返回设备信息，如{"productKey":"pkxxxx", "deviceName":"dnyyy"},
        其中deviceName是设备真实的deviceName,而并非MAC地址，此与入参deviceInfo中的信息不一致。
        假如失败，错误值请参见 `IMSSubDeviceServiceError`
 */
+ (void)subDeviceAuthenLogin:(NSDictionary *)deviceInfo
                resultBlock:(ThingSdkObjectResultBlock)resultBlock;



/**
 当子设备被绑定成功时，调用此API通知SDK，SDK内部需要做一些逻辑

 @param deviceInfo 设备信息，应包含 {"iotId":"",
                "productKey":"pkxxxx", "deviceName":"dnyyy"},
 其中对于ble设备，deviceName其实是ble的MAC地址切记不要传真实的deviceName。
 */
+ (void)notifySubDeviceBinded:(NSDictionary *)deviceInfo;
@end

NS_ASSUME_NONNULL_END
