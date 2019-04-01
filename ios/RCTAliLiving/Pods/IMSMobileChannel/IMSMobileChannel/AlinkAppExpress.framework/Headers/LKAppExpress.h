//
//  LKNecsExpress.h
//  AlinkNecsChannel
//
//  Created by ZhuYongli on 2017/10/31.
//  Copyright © 2017年 ZhuYongli. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 长连接通道连接状态枚举
 */
typedef NS_ENUM (NSInteger, LKAppExpConnectState){
    LKAppExpConnectStateConnected = 1,///<通道已连接
    LKAppExpConnectStateDisconnected = 2,///<通道连接断开
    LKAppExpConnectStateConnecting = 3,///<通道正在尝试连接
};

/**
 长连接通道连接状态侦听者
 */
@protocol LKAppExpConnectListener<NSObject>
/** 通道连接状况改变
 @param state 参见枚举 `LKExpConnectState`
 */
-(void)onConnectState:(LKAppExpConnectState) state;
@end

/**
 长连接通道连接配置项目
 */
@interface LKAEConnectConfig : NSObject
@property(nonatomic, copy) NSString * appKey;///<  应用 appkey，在 IoT 平台创建应用时生成
@property(nonatomic, copy)  NSString * authCode;///< 无线保镖 authCode， 该值必须和安全图片 yw_1222_xxx.jpg 的 xxx 部分一致

@property(nonatomic, copy, nullable) NSString * server;///< 长连通道连接的服务器地址，不要带 "协议://"，如果置为空，底层通道会使用默认的地址，
@property(nonatomic, assign) int port; ///< 通道连接的服务器端口，不传会使用默认端口
@property (nonatomic, assign) BOOL autoSelectChannelHost; ///<当 `server` 不指定时，且是在中国大陆以外地区使用，请将此值设置为 YES, 如果是在中国大陆使用时，请将此值设置为NO
@property(nonatomic, copy, nullable) NSString * cerPath; ///< TLS 文件绝对路径，如果为空，会使用默认的证书
@end

@protocol LKAppExpDownListener<NSObject>
/**
 下推数据方法
 
 @param topic 下推 Topic 的业务部分，由具体业务确定，下行的完整 Topic 形如：
 /sys/${productKey}/${deviceName}/app/down/properties/post
 其中App 端下推 Topic 协议前缀：/sys/${productKey}/${deviceName}/app/down 在 sdk 中会自动去除。
 所以开发者看到的是完整 Topic 的业务部分，如上例中的 /properties/post
 @param data 消息内容。可能是 NSString 或者 NSDictionary
 */
-(void)onDownstream:(NSString *) topic data: (id _Nullable) data;

/**
 数据使用 `onDownstream:data:` 上抛时，可以先过滤一遍，返回 NO，则不上抛；返回 YES，则会使用 `onDownstream:data:` 上抛
 
 @param topic 下推 Topic 的业务部分，由具体业务确定，下行的完整 Topic 形如：
 /sys/${productKey}/${deviceName}/app/down/properties/post
 其中App 端下推 Topic 协议前缀：/sys/${productKey}/${deviceName}/app/down 在 sdk 中会自动去除。
 所以开发者看到的是完整 Topic 的业务部分，如上例中的 /properties/post
 @return 返回 NO，则不上抛；返回 YES，则会使用 `onDownstream:data:` 上抛
 */
-(BOOL)shouldHandle:(NSString *)topic;
@end

/**
 RPC请求回执内容
 */
@interface LKAppExpResponse : NSObject
@property (nonatomic, assign) BOOL successed;                   ///< 是否成功
@property (nonatomic, strong, nullable) id dataObject;          ///< 服务端返回的 json 的 data 字段
@property (nonatomic, strong, nullable) NSError *responseError; ///< 错误详情
@end


//回调函数定义如下
typedef void(^LKAppExpResponseHandler)(LKAppExpResponse *response);

/**
 提供一条双工的长连接通道
 */
@interface LKAppExpress : NSObject
/**
 * 单例
 */
+(instancetype)sharedInstance;

/**
 长连接通道启动接口，应用起来时调用一次
 @param config app 长连接通道配置项
 @param listener 通道连接状态侦听者
 */
-(void)startConnect:(LKAEConnectConfig *)config connectListener:(id<LKAppExpConnectListener>)listener;


/**
 增加通道连接状态变化 listener
 @param listener 通道连接状态侦听者
 */
-(void) addConnectListener:(id<LKAppExpConnectListener>)listener;


/**
 增加通道连接状态变化 listener
 @param listener 通道连接状态侦听者
 */
-(void) removeConnectListener:(id<LKAppExpConnectListener>)listener;


/**
 RPC请求接口，封装了业务的上行 request 以及下行 response。
 @param topic rpc请求的 topic，由具体业务确定，上行的完整 topic 形如：
      /sys/${productKey}/${deviceName}/app/up/properties/set,
      其中App 端 Topic 订阅协议前缀：/sys/${productKey}/${deviceName}/app/up 在 sdk 中会自动补齐。
      所以开发者只需要传完整 topic 的业务部分，如上例中的 /properties/set 即可。
 @param opts 可选配置项，可空，预留
 @param params 业务参数。
 @param responseHandler 业务服务器响应回调接口，参见 `LKExpResponse`
 */
-(void)invokeWithTopic:(NSString *)topic opts:(NSDictionary* _Nullable)opts
            params:(NSDictionary*)params respHandler:(LKAppExpResponseHandler)responseHandler;


/**
 发布消息接口，不同于 `invokeWithMethod:opts:params:respHandler:` 。这个接口不会有业务回执。
 @param topic rpc 请求的 topic，由具体业务确定，上行的完整 topic 形如：
 /sys/${productKey}/${deviceName}/app/up/properties/set
 其中App 端 Topic 订阅协议前缀：/sys/${productKey}/${deviceName}/app/up 在 sdk 中会自动补齐。
 所以开发者只需要传完整 topic 的业务部分，如上例中的 /properties/set 即可。
 也可以使用通配符 如 /properties/#.
 @param params 业务参数。
 @param completeCallback 业务服务器响应回调接口，参见 `LKExpResponse`
 */
-(void)publish:(NSString *)topic params:(NSDictionary *)params complete:(void(^)(NSError* _Nullable))completeCallback;


/**
 设置通道的下推侦听者，如果不需要用的时候，记得调用 `removeDownStreamListener:` 。
 `LKAppExpress` 收到云端下推的处理逻辑如下所示:
 
 if ([downListener shouldHandle:topic] == YES) {
    [downListener onDownstream:topic data:data];
 } else {
    NSLog(@"message will ignored");
 }
 
 @param uiSafety 是否要在UI线程里回调，建议为 YES
 @param downListener 侦听下推消息，参见 `LKExpDownListener`
 */
- (void)addDownStreamListener:(BOOL)uiSafety listener:(id<LKAppExpDownListener>)downListener;

/**
 取消通道的某个下推侦听者
 @param downListener 侦听下推消息，参见 `LKExpDownListener`
 */
-(void)removeDownStreamListener:(id<LKAppExpDownListener>)downListener;



/**
 app 向云端订阅 topic 的接口。SDK 启动时会默认向云端订阅 app 相关的所有下行消息。即自动 subscribe topic:@"/#"。
 所以默认情况下无需再订阅。
 @param topic 订阅的消息的 topic，由具体业务确定，只需要传业务方的区段，公用区段不需要传.
 下行的完整 topic 形如：
 /sys/${productKey}/${deviceName}/app/down/properties/post
 其中App 端 Topic 订阅协议前缀：/sys/${productKey}/${deviceName}/app/down 在 sdk 中会自动补齐。
 所以开发者只需要传完整topic的业务部分，如上例中的 /properties/post 即可。
 也可以使用通配符 如 /properties/#.
 @param completionHandler 订阅流程完成的 callback，如果 error 为空表示订阅成功，否则订阅失败
 */
- (void)subscribe : (NSString *)topic complete: (void (^)(NSError  * _Nullable error))completionHandler;


/**
 app向云端取消订阅 topic 的接口。SDK 启动时会默认向云端订阅 app 相关的所有下行消息。即主动 [subscribe topic:@"/#"]。
 如果应用层不希望订阅所有下行，可以先[unsubscrbie topic:@"/#"]取消所有下行的订阅。再subscribe自己感兴趣的 topic.
 @param topic 取消订阅的消息的 topic，由具体业务确定，只需要传业务方的区段，公用区段不需要传.
 下行的完整 topic 形如：
 /sys/${productKey}/${deviceName}/app/down/properties/post
 其中 Ap p端 Topic 订阅协议前缀：/sys/${productKey}/${deviceName}/app/down 在 sdk 中会自动补齐。
 所以开发者只需要传完整 topic 的业务部分，如上例中的 /properties/post 即可。
 也可以使用通配符 如 /properties/#.
 @param completionHandler 取消订阅流程完成的 callback，如果 error 为空表示订阅成功，否则订阅失败
 */
- (void)unsubscribe : (NSString *)topic complete: (void (^)(NSError  * _Nullable error))completionHandler;


/**
 获取当前长连通道的 clientId
 */
- (NSString *)getClientId;

@end


NS_ASSUME_NONNULL_END
