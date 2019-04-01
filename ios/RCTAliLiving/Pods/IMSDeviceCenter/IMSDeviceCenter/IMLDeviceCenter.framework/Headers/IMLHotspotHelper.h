//
//  LKHotspotHelper.h
//  IMLDeviceCenter
//  热点配网工具类
//  Created by ZhuYongli on 2017/8/1.
//  Copyright © 2017年 ZhuYongli. All rights reserved.
//

#import <Foundation/Foundation.h>

#define IMSDCDeprecated_Method(_msg) __attribute__((deprecated(_msg)))
#define IMSDCDeprecated_Property(_msg) __attribute__((deprecated(_msg)))

#define kLKHotspotHelper IMLHotspotHelper.sharedHelper

/**
 可访问的设备节点
 */
@interface LKHotAccessibleItem : NSObject

/** 设备基础信息之 productKey */
@property (nonatomic, copy) NSString *productKey;

/** 设备基础信息之 deviceName */
@property (nonatomic, copy) NSString *deviceName;

/** IP */
@property (nonatomic, copy) NSString *ip;

/** random (获取秘钥时的随机数) */
@property (nonatomic, copy) NSString *random;

/** 设备支持的安全加密等级 */
@property (nonatomic, copy) NSString *cipherType;

/** 签名 */
@property (nonatomic, copy) NSString *sign;

@end

/**
 热点信息
 */
@interface LKAccessibleAccessPoint : NSObject

/** 热点 SSID */
@property (nonatomic, copy) NSString *ssid DEPRECATED_ATTRIBUTE;

/** 非 UTF-8 编码的 SSID，通过 ssid 字段获取转译成 UTF-8 编码后的 ssid */
@property (nonatomic, copy) NSString *xssid DEPRECATED_ATTRIBUTE;

/** 热点信号强度 */
@property (nonatomic, copy) NSString *rssi DEPRECATED_ATTRIBUTE;

/** 热点认证模式 */
@property (nonatomic, copy) NSString *auth DEPRECATED_ATTRIBUTE;

@end


/**
 提供热点配网的工具类
 */
@interface IMLHotspotHelper : NSObject

/**
 返回单例
 */
+ (instancetype)sharedHelper;

/**
 获取当前所连路由器名称
 */
+ (NSString *)getCurrentSsid;

/**
 是否支持起热点，检测是否为 iPhone
 
 @return YES 则支持起热点
 */
+ (BOOL)isSupportedHotspot;

/**
 发现连上热点的设备列表，有设备新增会有多次回调
 
 @param completionHandler 回调（发现的设备列表）
 */
- (void)discoverAccessibleItems:(void (^)(NSArray<LKHotAccessibleItem *> *devices, NSError *error))completionHandler;

/**
 停止发现
 */
- (void)stopDiscover;

/**
 发送单播 并 开启监听，搜索设备周边 Wi-Fi 列表，可能有多次回调
 @param access 设备信息
 @param completionHandler 回调（ WiFi 列表）
 */
- (void)searchWifiList:(LKHotAccessibleItem *)access completeBlock:(void (^)(NSArray<LKAccessibleAccessPoint *> *wifiList, NSError *error))completionHandler IMSDCDeprecated_Method("SDK version 1.2.0"); // 在SDK version 1.2.0禁用该方法




/**
 停止搜索设备周边 WiFi 列表
 */
- (void)stopSearchWifiList;

/**
 控制设备 切换热点

 @param access 设备信息
 @param ssid 待切换到的热点
 @param pwd 待切换到的热点密码
 @param completionHandler 回调
 */
- (void)switchToAccessPoint:(LKHotAccessibleItem *)access
                       ssid:(NSString *)ssid
                   password: (NSString *)pwd
                 completion:(void (^)(id result, NSError *error))completionHandler;

@end

