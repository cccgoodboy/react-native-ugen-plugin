//
//  IMSRequest.h
//  IMSApiClient
//
//  Created by 文季 on 2017/11/6.
//  Copyright © 2017年 Alibaba-Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 API 通道请求
 */
@interface IMSRequest : NSObject

@property (nonatomic, copy, readonly) NSString *msgId;        ///< API 请求的消息标示，可用于问题排查

@property (nonatomic, copy, readonly) NSString *host;         ///< API 请求的域名
@property (nonatomic, copy, readonly) NSString *apiVersion;   ///< API 版本
@property (nonatomic, strong, readonly) NSDictionary *params; ///< API 参数

// 该接口不可用，请通过 IMSIotRequestBuilder 进行创建
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
