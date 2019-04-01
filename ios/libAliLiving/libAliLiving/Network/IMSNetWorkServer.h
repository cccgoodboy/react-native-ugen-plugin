//
//  IMSNetWorkServer.h
//  LoginDemo
//
//  Created by 初程程 on 2018/7/3.
//  Copyright © 2018年 Facebook. All rights reserved.
//

#import <Foundation/Foundation.h>
//不需要认证
@interface IMSNetWorkServer : NSObject
+ (void)sendRequestWithPath:(NSString *)path
                    version:(NSString *)version
                     params:(id)params
                    handler:(void(^)(BOOL isSuccess,id response,NSString *requestId))handler;
//需要认证
+ (void)sendIotAuthRequestWithPath:(NSString *)path
                           version:(NSString *)version
                            params:(id)params
                           handler:(void(^)(BOOL isSuccess,id response,NSString *requestId))handler;
@end
