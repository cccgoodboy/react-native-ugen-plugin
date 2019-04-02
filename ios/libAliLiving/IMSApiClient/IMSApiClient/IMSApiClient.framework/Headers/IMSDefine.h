//
//  IMSDefine.h
//  IMSApiClient
//
//  Created by 文季 on 2017/11/6.
//  Copyright © 2017年 Alibaba-Inc. All rights reserved.
//

#ifndef IMSDefine_h
#define IMSDefine_h

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class IMSResponse;

FOUNDATION_EXPORT NSString * const IMSApiClientVersion;

/**
 请求响应回调
 
 @param error 错误对象，所有无法通过服务端响应的错误都通过该 error 抛出，如，网络错误，host 不可到达
 @param response 服务端响应对象
 */
typedef void(^IMSResponseHandler)(NSError * _Nullable error, IMSResponse * _Nullable response);

NS_ASSUME_NONNULL_END

#endif /* IMSDefine_h */
