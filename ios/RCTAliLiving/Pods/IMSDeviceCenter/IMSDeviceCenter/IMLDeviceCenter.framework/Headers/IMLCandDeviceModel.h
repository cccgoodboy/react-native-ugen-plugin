//
//  LKCandDeviceModel.h
//  IMLDeviceCenter
//
//  Created by ZhuYongli on 2017/7/7.
//  Copyright © 2017年 ZhuYongli. All rights reserved.
//

#import <Foundation/Foundation.h>
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnon-modular-include-in-framework-module"
#import <TBJSONModel/TBJSONModel.h>
#pragma clang diagnostic pop

/**
 * 候选设备类型
 */
typedef NS_ENUM(NSInteger, LKDeviceType) {
    LKDeviceTypeWifi = 1,       ///< WIFI 设备
    LKDeviceTypeBle = 2,        ///< 蓝牙
    LKDeviceType433 = 3,        ///< RF433设备
    LKDeviceTypeZigbee = 4,     ///< Zigbee设备
};

/**
 * 强制选择配网类型枚举值
 */
typedef NS_ENUM(NSUInteger, ForceAliLinkType) {
    ForceAliLinkTypeNone,       ///< 由native SDK自行决定在广播配网，热点配网，路由器配网，路由器配网中选择最优的配网方案；
    ForceAliLinkTypeRouterAP,   ///< 设备路由器配网方案,在一般配网方案失败后，可切换到路由器方案
    ForceAliLinkTypeBroadcast,  ///< 设备广播配网方案,在一般配网方案失败后，可切换到广播配网方案
    ForceAliLinkTypeHotspot,    ///< 手机热点配网方案，在一般配网方案失败后，可切换到手机热点方案
    ForceAliLinkTypeSoftap      ///< 设备热点配网方案
};

/**
 * 候选设备数据模型
 */
@interface IMLCandDeviceModel : TBJSONModel

/** 设备productKey */
@property (nonatomic, copy) NSString *productKey;

/** 设备名称 */
@property (nonatomic, copy) NSString *deviceName;

/** 待配网设备联网类型：0代表wifi设备；1代表ethernet设备（网线连接）：2代表路由器 */
@property (nonatomic, copy) NSString *devType;

/** 设备配网完成后得到的token，用于下一步绑定用 */
@property (nonatomic, copy) NSString *token;

/** 指定配网方式 */
@property (nonatomic, assign) ForceAliLinkType linkType;

/** 发现待配网设备的设备的productKey：可选， */
@property (nonatomic, copy) NSString *regProductKey;

/** 发现待配网设备的设备的productNeme：可选， */
@property (nonatomic, copy) NSString *regDeviceName;

/** 云端返回待配网设备来源：“ROUTER”--代表路由器发现，“ZERO_DEVICE”代表零配发现 */
@property (nonatomic, copy) NSString *addDeviceFrom;

/** 产品加密密钥 */
@property (nonatomic, copy) NSString *productEncryptKey;

@end

