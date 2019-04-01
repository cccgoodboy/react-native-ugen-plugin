//
//  IMSThingAction.h
//  IMSThingCapability
//
//  Created by ZhuYongli on 2018/1/10.
//  Copyright © 2018年 ZhuYongli. All rights reserved.
//

#import <Foundation/Foundation.h>


NS_ASSUME_NONNULL_BEGIN


/**
 对物进行操作时的响应结果类
 */
@interface IMSThingActionsResponse : NSObject
@property(nonatomic, assign) BOOL success; ///< 响应结果，成功或者失败
@property (nonatomic, strong, nullable) id dataObject;          ///< 服务端返回的 json 的 data 字段,一般为 NSData 结构，具体格式请参见云端 '物的核心模型服务' 文档
@property (nonatomic, strong, nullable) NSError *responseError; ///< 错误，失败时才有，可以参见 NSError+IMSThing.h
@end


typedef void (^IMSThingActionsResponseHandler)(IMSThingActionsResponse * _Nullable response); ///<对物进行操作时的响应结果回调函数定义


/**
 对物进行操作的方法 protocol
 */
@protocol IMSThingActions <NSObject>


/**
 获取物的所有属性的当前值

 @param handler 结果回调函数，请参考 `IMSThingActionsResponseHandler`
 */
- (void)getPropertiesFull:(IMSThingActionsResponseHandler)handler;


/**
 设置物的属性值，可以同时设置一个或者多个属性

 @param items 属性 key-value 对， 如{"power":"on", temperature:30}
 @param handler 结果回调函数，请参考 `IMSThingActionsResponseHandler`
 */
- (void)setProperties:(NSDictionary*_Nonnull)items responseHandler:(IMSThingActionsResponseHandler _Nullable )handler;


/**
 调用物提供的服务

 @param serviceIdentifier 服务的唯一标识符
 @param params 调用服务的入参，请参考物的模型 tsl，形如 {"arg1":"val1", "arg2":"val2"}
 @param handler 结果回调函数
 */
- (void)invokeService:(NSString * _Nonnull)serviceIdentifier
               params:(NSDictionary* _Nullable)params
      responseHandler:(IMSThingActionsResponseHandler)handler;



/**
 获取云端缓存的物定义的所有事件内容，云端逻辑是：当物某个事件触发时，云端记录此事件的快照，
 当 app 端来获取时，则返回这些事件在云端的记录

 @param handler 结果回调函数
 */
- (void)getEvents:(IMSThingActionsResponseHandler)handler;



/**
 获取物的生命周期
 说明：status表示设备生命周期，目前有以下几个状态，0:未激活；1：上线；3：离线；8：禁用；

 @param handler 结果回调函数
 */
- (void)getStatus:(IMSThingActionsResponseHandler)handler;
@end


NS_ASSUME_NONNULL_END
