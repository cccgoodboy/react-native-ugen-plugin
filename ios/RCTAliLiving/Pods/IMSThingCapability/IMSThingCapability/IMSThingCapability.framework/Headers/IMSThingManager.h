//
//  IMSThingManager.h
//  IMSThingCapability
//
//  Created by ZhuYongli on 2018/1/10.
//  Copyright © 2018年 ZhuYongli. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IMSThing.h"

#define kIMSThingManager [IMSThingManager sharedManager]

NS_ASSUME_NONNULL_BEGIN

/**
 在 iot 语境里，设备被抽象成为物，即 thing
物的管理者，是一个单例类
 */
@interface IMSThingManager : NSObject


/**
 返回单例

 @return 单例
 */
+ (instancetype)sharedManager;


/**
 创建 Thing 对象，该对象会被加入管理者维护的物的队列中

 @param iotId 物的唯一标识符， 该 id 是物在注册绑定时由云端颁发
 @return 返回 Thing 对象
 */
- (IMSThing *)buildThing:(NSString *)iotId;


/**
 销毁 Thing 对象，在 Thing 不再需要时调用此方法
可以将其从 管理者维护的物的队列中删除
 @param thing Thing 的对象
 */
- (void)destroyThing:(IMSThing *)thing;



/**
 创建 Thing 对象，该对象会被加入管理者维护的物的队列中
 
 @param productKey 物在iot平台注册的产品型号
 @param deviceName 物的deviceName
 @param iotId 物的iotId
 @return 返回 Thing 对象
 */
- (IMSThing*)buildThing:(NSString *)productKey
             deviceName:(NSString *)deviceName
                  iotId:(NSString *)iotId;
@end



/**
 物的操作是个抽象模型，只要开启本地加速器，就能获得本地加速，而不用修改操作的调用方法。
 
 当然也有一些注意事项：
 1）需要手动开启
 2）需要注意账号切换的的时候的缓存清除
 3）当然，如果并不需要的时候可以关闭
 */
@interface IMSThingManager (LocalAccelerator)

/**
 开启本地通信能力，需要在操作物时提前调用，可以多次调用，但必须至少调用过一次
 */
- (void)startLocalAcceleration;

/**
 关闭本地通信能力
 */
- (void)stopLocalAcceleration;


/**
 清理 SDK 中缓存的用户数据，特别是对设备的进行控制的授权信息，在用户注销账号时记得调用
 */
- (void)clearLocalCache;

/**
 返回本地发现的物
 
 @return 返回本地发现的物
 */
- (NSArray<IMSThing *> *)getLocalThings;


/**
 返回本地发现的可以进行本地控制的设备详情
 
 @return 返回本地发现的可以进行本地控制的设备详情
 */
- (NSArray<NSDictionary *> *) getLocalAuthedDeviceDataList;

@end

NS_ASSUME_NONNULL_END
