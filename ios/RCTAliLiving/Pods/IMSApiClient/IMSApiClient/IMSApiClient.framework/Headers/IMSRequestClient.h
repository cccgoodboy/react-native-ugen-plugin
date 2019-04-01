//
//  IMSRequestClient.h
//  IMSApiClient
//
//  Created by 文季 on 2017/11/6.
//  Copyright © 2017年 Alibaba-Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <IMSApiClient/IMSDefine.h>
#import <IMSApiClient/IMSRequest.h>
#import <IMSApiClient/IMSAuthenticationDelegate.h>

NS_ASSUME_NONNULL_BEGIN

/**
 用于发送 API 通道请求
 */
@interface IMSRequestClient : NSObject

/**
 注册 API 请求的认证处理 Delegate
 
 @param delegate 认证处理 delegate
 @param authType 认证类型
 */
+ (void)registerDelegate:(id<IMSAuthenticationDelegate>)delegate forAuthenticationType:(NSString *)authType;

/**
 异步发送请求，响应会通过主线程回调
 
 @param request 请求对象
 @param responseHandler 响应回调
 */
+ (void)asyncSendRequest:(IMSRequest *)request responseHandler:(IMSResponseHandler)responseHandler;

@end

NS_ASSUME_NONNULL_END
