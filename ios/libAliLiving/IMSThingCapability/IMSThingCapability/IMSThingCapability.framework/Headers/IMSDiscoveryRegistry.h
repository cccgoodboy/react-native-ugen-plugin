//
//  IMSDiscoveryRegistry.h
//  IMSThingCapability
//
//  Created by ZhuYongli on 2018/1/17.
//  Copyright © 2018年 ZhuYongli. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IMSThingBaseDefine.h"
//#import <TBJSONModel/TBJSONModel.h>

NS_ASSUME_NONNULL_BEGIN


typedef NS_ENUM(NSInteger, IMSLocalDeviceType) {
    IMSLocalDeviceTypeAliWifi = 1, ///< 阿里云IoT Wi-Fi 设备
    IMSLocalDeviceTypeAliBreeze = 2, ///< 阿里云IoT Breeze蓝牙
    IMSLocalDeviceTypeThirdParty = 3, ///< 第三方设备，包括第三方蓝牙以及Wi-Fi
    IMSLocalDeviceTypeCloudLca = 4, ///< 从云端拉取的LCA设备
};

@protocol IMSLocalDevice <NSObject>
@property(nonatomic, copy) NSString * productKey; ///< 设备productKey
@property(nonatomic, copy) NSString * deviceName; ///< 设备deviceName，对于BLE设备，此处其实携带的是设备的MAC地址。
@property(nonatomic, copy, nullable) NSData * tslData; ///< 一般为nil
@property(nonatomic, copy, nullable) NSString * deviceSecret; ///< 一般为nil
@property(nonatomic, assign) IMSLocalDeviceType deviceType;
@property(nonatomic, strong, nullable) NSDictionary * extraBindInfos;
@end


@interface IMSThingDiscoveryRegistry : NSObject

+ (instancetype)sharedRegistry;


/**
 搜寻设备，且根据 filter 里的内容对设备进行过滤

 @param filter 过滤器，KV对. 如下所示
 可以过滤 设备类型，如 ：{"deviceType":["wifi", "breeze", "third", "cloudlca"]}，
   其中 "wifi", "breeze", "third" 分别对应 IMSLocalDeviceType 枚举中的值
 也可以过滤 productKey，形如 {"productKey":"pkxxxx"}. 说明：productKey跟deviceType是互斥的。二者只能出现一个。
 对于智能人居的开发者，filter中还需要携带房间号 "groupId":"xxxx",
 对于cloudlca设备，如果需要按网关过滤，可以在filter中增加K-V对，"gatewayIotId":"xxxx"。表示过滤某一个边缘网关发现的lca设备列表
 过滤器根据实际需要来设置
 @param didFoundBlock 发现设备的回调，参见 `ThingSdkArrayResultBlock`，其中队列中包含的对象为 id<IMSLocalDevice>
 */
- (void)startDiscoveryWithFilter:(NSDictionary *)filter
                   didFoundBlock:(ThingSdkArrayResultBlock)didFoundBlock;


/**
 中止设备发现过程

 @param completeHandler 结束时的回调
 */
- (void)stopDiscovery:(ThingSdkBooleanResultBlock __nullable)completeHandler;


@end


NS_ASSUME_NONNULL_END
