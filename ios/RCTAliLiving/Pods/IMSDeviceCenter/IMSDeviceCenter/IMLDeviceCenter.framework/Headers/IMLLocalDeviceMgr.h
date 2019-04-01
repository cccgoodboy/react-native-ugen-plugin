//
//  LKLocalDeviceMgr.h
//  IMLDeviceCenter
// 此类是一个单例类，用来发现本地设备（已配网）以及待配设备（云端拉取路由器发现待配网和已配网设备发现的待配网）
//  Created by ZhuYongli on 2017/7/7.
//  Copyright © 2017年 ZhuYongli. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LKErrorDefine.h"

@class IMLCandDeviceModel;
#define kLKLocalDeviceMgr IMLLocalDeviceMgr.sharedMgr

extern NSString * kLKLocalDevMgrErrorDomain;


/**
 提供发现本地设备（已配网）以及待配设备（云端拉取路由器发现待配网和已配网设备发现的待配网）的功能
 */
@interface IMLLocalDeviceMgr : NSObject

/**
 返回单例
 */
+ (instancetype)sharedMgr;

/**
 启动发现设备流程，包括本地发现的设备以及云端待配网设备
 @param didFoundBlock   发现设备时的回调，会调用多次
 */
- (void)startDiscovery:(void(^)(NSArray * devices, NSError * err))didFoundBlock;


/**
 启动发现设备流程，包括本地发现的设备以及根据过滤条件获取到的云端待配网设备

 @param filterParams 请求云端待配网设备的过滤条件
 @param didFoundBlock 发现设备时的回调，会调用多次
 */
- (void)startDiscoveryWithFilter:(NSDictionary *)filterParams discoverBlcok:(void(^)(NSArray * devices, NSError * err))didFoundBlock;

/**
 获取所有发现的设备：包括待配网、已配网待绑定、已绑定
 @return 设备列表，参见 'LKLANDeviceModel'
 */
- (NSArray<IMLCandDeviceModel*>*)getLanDevices;

/**
 停止发现设备流程
 */
- (void)stopDiscovery;

/**
 获取已配网设备的token，用于设备绑定

 @param productKey 产品类型
 @param deviceName 设备名称
 @param timeout 请求token超时时间
 @param resultBlock 请求结果回调block
 */
- (void)getDeviceToken:(NSString *)productKey deviceName:(NSString *)deviceName timeout:(NSUInteger)timeout resultBlock:(void(^)(NSString *token, BOOL boolSuccess))resultBlock;

/**
 轮询获取已配网设备的token，用于设备绑定

 @param productKey 产品类型
 @param deviceName 设备名称
 @param timeout 获取 token 的超时时间，单位秒。
 @param interval interval字段，每多少秒执行一次查询请求。 interval 为0 即不轮询
 @param resultBlock 请求结果回调block
 */
- (void)getDeviceToken:(NSString *)productKey deviceName:(NSString *)deviceName timeout:(NSUInteger)timeout interval:(NSUInteger)interval resultBlock:(void(^)(NSString *token, BOOL boolSuccess))resultBlock;

/**
 停止获取Token
 */

- (void)stopGetDeviceToken;

@end
