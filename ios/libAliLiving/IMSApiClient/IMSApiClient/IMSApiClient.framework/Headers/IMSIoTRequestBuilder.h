//
//  IMSIoTRequestBuilder.h
//  IMSApiClient
//
//  Created by 文季 on 2017/11/7.
//  Copyright © 2017年 Alibaba-Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <IMSApiClient/IMSRequest.h>

NS_ASSUME_NONNULL_BEGIN

/**
 用于构建 API 通道请求对象
 */
@interface IMSIoTRequestBuilder : NSObject

- (instancetype)init NS_UNAVAILABLE;

/**
 初始化接口

 对于一个 URL https://www.example.com/index.html，scheme 为 https，host 为 www.example.com，path 为 /index.html
 
 @param path API 请求的 path 部分
 @param apiVersion API 版本
 @param params API 参数
 */
- (instancetype)initWithPath:(NSString *)path
                  apiVersion:(NSString *)apiVersion
                      params:(NSDictionary *)params NS_DESIGNATED_INITIALIZER;

/**
 根据一个已有的 request 构造一个 builder

 @param request 一个已有的 IMSRequest 实例
 */
- (instancetype _Nullable)initWithRequest:(IMSRequest *)request;

/**
 设置当前 API 请求的域名，不设置时从 `IMSConfiguration` 的 host 字段读取
 @param host API 通道请求的 host 部分
 @return 返回当前实例
 */
- (IMSIoTRequestBuilder *)setHost:(NSString *)host;

/**
 添加业务参数，是一个键值对（key:value）
 @param value   参数的value部分
 @param key     参数的key部分
 @return 返回当前实例
 */
- (IMSIoTRequestBuilder *)addParameter:(id)value forKey:(NSString *)key;

/**
 移除业务参数，是一个键值对（key:value）
 @param key 待移除参数的key部分
 @return 返回当前实例
 */
- (IMSIoTRequestBuilder *)removeParameterForKey:(NSString *)key;

/**
 默认 scheme 为 https
 @param scheme  设置当前 API 请求的 scheme，为 https 或 http
 @return 返回当前实例
 */
- (IMSIoTRequestBuilder *)setScheme:(NSString *)scheme;

/**
 往 IoT 协议 Request 字段添加一个键值对（key:value）
 @param value   参数的value部分
 @param key     参数的key部分
 @return 返回当前实例
 */
- (IMSIoTRequestBuilder *)addRequestItem:(id)value forKey:(NSString *)key;

/**
 从 IoT 协议 Request 字段移除一个键值对（key:value）
 @param value   参数的value部分
 @param key     参数的key部分
 @return 返回当前实例
 */
- (IMSIoTRequestBuilder *)removeRequestItem:(id)value forKey:(NSString *)key;

/**
 设置 API 请求认证类型，相应的类型和实现必须先在 `IMSRequestClient` 类中注册才可使用
 @param authType   指定认证类型
 @return 返回当前实例
 */
- (IMSIoTRequestBuilder *)setAuthenticationType:(NSString *)authType;

/**
 移除 API 请求认证类型
 @return 返回当前实例
 */
- (IMSIoTRequestBuilder *)removeAuthenticationType;

/**
 构建 API 通道请求对象
 @return 返回 API 通道请求对象
 */
- (IMSRequest *)build;

@end

NS_ASSUME_NONNULL_END
