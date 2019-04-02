//
//  IMSRequestPayload.h
//  IMSApiClient
//
//  Created by 文季 on 2018/1/5.
//  Copyright © 2018年 Alibaba-Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
/*
 IoT 请求协议 payload，目前是 json 格式，详细如下：
 {
     "id": "123",
     "version": "1.0",
     "request": {
        "appKey"："",
        "apiVer": "",
        "iotToken": "" //可选，如需 IoT 统一身份鉴权时填写
     },
     "params": {
        // biz parameters
     }
 }
 */
@interface IMSRequestPayload : NSObject

@property (nonatomic, strong, nonnull) NSDictionary *request;
@property (nonatomic, strong, nonnull) NSDictionary *params;

@property (nonatomic, copy, readonly, nonnull) NSString *msgId;
@property (nonatomic, copy, readonly, nonnull) NSString *version;

- (instancetype _Nonnull)initWithMsgId:(NSString * _Nonnull)msgId version:(NSString * _Nonnull)version;

@end
