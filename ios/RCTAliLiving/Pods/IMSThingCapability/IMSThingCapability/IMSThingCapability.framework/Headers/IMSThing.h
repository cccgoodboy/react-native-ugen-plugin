//
//  IMSThing.h
//  IMSThingCapability
//
//  Created by ZhuYongli on 2018/1/10.
//  Copyright © 2018年 ZhuYongli. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IMSThingActions.h"
#import "IMSThingProfile.h"
#import "IMSThingBaseDefine.h"

NS_ASSUME_NONNULL_BEGIN



typedef NS_ENUM(NSInteger, IMSLocalConnectionState) {
    IMSLocalConnectionStateConnected = 1,
    IMSLocalConnectionStateDisconnected = 2,
    IMSLocalConnectionStateConnecting = 3, ///< 设备连接中
};


/**
 物的状态变更、属性变更、事件触发的观察者类
 */
@protocol IMSThingObserver <NSObject>

/**
 物的状态变更回调，如上线，离线等
 @param iotId 物的 iotId
 @param params 出参，描述具体状态
 */
- (void)onStatusChange:(NSString *)iotId params:(NSDictionary *)params;


/**
物有事件触发，如提示，告警等

 @param iotId 物的 iotId
 @param params 出参，描述具体事件
 */
- (void)onEventHappen:(NSString *)iotId params:(NSDictionary *)params;


/**
物的属性发生变化

 @param iotId 物的 iotId
 @param params 出参，描述属性内容
 */
- (void)onPropertyChange:(NSString *)iotId params:(NSDictionary *)params;
@optional

/**
物的 tsl 模板解析完毕，后续可以用 [self getThingProfile] 拿到详细的 tsl 模型数据
 */
- (void)didThingTslLoad;


@optional

/**
 通告本地连接状态变化，未连接《-》已连接

 @param state 连接状态，参见 `IMSLocalConnectionState`
 */
- (void)onLocalConnectionStateChange:(IMSLocalConnectionState)state;
@end



/**
 在 IoT 语境里，所有设备都抽象成物，即 Thing
 此类为物的人机交互接口，此类管理物的对外暴露接口以及输出物的基本信息
 */
@interface IMSThing : NSObject


/**
 获取物的 iotId

 @return 返回物的 iotId
 */
- (NSString *)iotId;


/**
 获取物的 productKey
 
 @return 返回物的 productKey
 */
- (NSString *)getProductKey;


/**
 获取物的 deviceName
 
 @return 返回物的 deviceName
 */
- (NSString *)getDeviceName;

/**
 获取物的控制操作类实例，具体参见 `IMSThingActions`
 包括物的属性获取、设置；物的事件记录获取；调用物的服务
 @return 返回物的控制操作类实例
 */
- (id<IMSThingActions>)getThingActions;



/**
 注册物的状态、属性变化或者事件触发的 observer, Thing 类只会 Weak 持有此 observer，
 调用者需要自行保证 observer 的生命周期，如果 dealloc 了，将不再有效

 @param observer 观察者，具体参见 `IMSThingObserver`
 */
- (void)registerThingObserver:(id<IMSThingObserver>)observer;


/**
 反注册物的状态、属性变化或者事件触发的 observer

 @param observer 观察者，具体参见 `IMSThingObserver`
 */
- (void)unregisterThingObserver:(id<IMSThingObserver>)observer;




/**
 获取物的 Profile，在 Profile 中包含了物的模型信息； 具体参见 `IMSThingProfile`
 
 @return 返回物的模型信息，开发者可以借此来做 UI 展示
 */
- (IMSThingProfile *)getThingProfile;


@end



@interface IMSThing (LocalConnection)
@property(nonatomic, assign, readonly) IMSLocalConnectionState localConnectionState;


/**
 主动开启跟设备之间的本地连接
 
  @param resultBlock 结果回调
 */
- (void)startLocalConnect:(ThingSdkBooleanResultBlock _Nullable)resultBlock;


/**
 主动断开跟设备之间的本地连接
 */
- (void)stopLocalConnect;

@end


NS_ASSUME_NONNULL_END
