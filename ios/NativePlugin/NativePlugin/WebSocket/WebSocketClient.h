//
//  WebSocketClient.h
//  LoginDemo
//
//  Created by 初程程 on 2018/7/4.
//  Copyright © 2018年 Facebook. All rights reserved.
//

#import <Foundation/Foundation.h>
//#import "ReactiveCocoa.h"
@interface WebSocketClient : NSObject
@property (nonatomic ,assign ,readonly)BOOL canUse;
@property (nonatomic ,copy)void(^listenerBlock)(NSError *err);

+ (WebSocketClient *)sharedInstance;
- (void)initConfig;
- (void)subscribeTopic:(NSString *)topic;
- (void)invokeWithTopic:(NSString *)topic
                  param:(id)param;
- (void)startListener;
- (void)stopListener:(void(^)(BOOL isSuccess))callback;
- (BOOL)connectState;
- (void)rebindSocket;
@end
