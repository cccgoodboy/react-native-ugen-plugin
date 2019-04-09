//
//  WebSocketClient.m
//  LoginDemo
//
//  Created by 初程程 on 2018/7/4.
//  Copyright © 2018年 Facebook. All rights reserved.
//

#import "WebSocketClient.h"
#import <IMSApiClient/IMSApiClient.h>
#import <AlinkAppExpress/LKAppExpress.h>
#import <IMSAccount/IMSAccountService.h>
#import <IMSAuthentication/IMSAuthentication.h>
#import "RNSendToJsReact.h"
@interface WebSocketClient()<LKAppExpConnectListener,LKAppExpDownListener>
@property (nonatomic ,assign)BOOL isConnect;
@end
@implementation WebSocketClient
+ (WebSocketClient *)sharedInstance{
  static WebSocketClient *socket;
  static dispatch_once_t onceToken;
  dispatch_once(&onceToken, ^{
    socket = [[WebSocketClient alloc] init];
  });
  return socket;
}
- (void)initConfig{
  IMSConfiguration * imsconfig = [IMSConfiguration sharedInstance];
  LKAEConnectConfig * config = [LKAEConnectConfig new];
  config.appKey = imsconfig.appKey;
  config.authCode = imsconfig.authCode;
  // 指定长连接服务器地址。 （默认不填，SDK会使用默认的地址及端口。默认为国内华东节点。不要带 "协议://"，如果置为空，底层通道会使用默认的地址）
  config.server = @"";
  // 开启动态选择Host功能。 (默认 NO，海外环境请设置为 YES。此功能前提为 config.server 不特殊指定。）
  config.autoSelectChannelHost = NO;
  [[LKAppExpress sharedInstance]startConnect:config connectListener:self];
  
  [[LKAppExpress sharedInstance]addDownStreamListener:YES listener:self];
}
- (void)onConnectState:(LKAppExpConnectState) state{
  
  self.isConnect = state==LKAppExpConnectStateConnected;
  
  NSString *tip = @"";
  
  if (self.isConnect) {
    
    tip = @"1";
    
  }else{
    
    tip = @"0";
  }
  
  [RNSendToJsReact emitEventWithName:@"AppExpConnectStateChange" andPayload:@{@"value":tip}];
  
}
- (void)rebindSocket{
  [self cancelTopic:@"/#" callback:^(BOOL isSuccess) {
    [self stopListener:^(BOOL isSuccess) {
      if (isSuccess) {
        [self startListener];
      }else{
        [self rebindSocket];
      }
    }];
  }];
}
- (void)startListener{
  IMSCredential *credential = [[IMSCredentialManager sharedManager] credential];
  
  if (credential.iotToken) {
    [[LKAppExpress sharedInstance] invokeWithTopic : @"/account/bind"  opts:nil        params:@{@"iotToken":credential.iotToken}
                                        respHandler:^(LKAppExpResponse * _Nonnull response) {
                                          if([response successed]){
                                            
                                            [self subscribeTopic:@"/#"];
                                          }else{
                                            
                                            self.listenerBlock(response.responseError);
                                          }
                                        }];
  }
}
- (void)stopListener:(void(^)(BOOL isSuccess))callback{
  [self cancelTopic:@"/#" callback:^(BOOL isSuccess) {
    [[LKAppExpress sharedInstance] invokeWithTopic:@"/account/unbind" opts:nil params:@{} respHandler:^(LKAppExpResponse * _Nonnull response) {
      if ([response successed]) {
        callback(YES);
      }else{
        callback(NO);
        //      [AlertShow showAlertWithMessage:@"长连接通道解绑失败"];
      }
    }];
  }];
}
- (void)invokeWithTopic:(NSString *)topic
                  param:(id)param{
  [[LKAppExpress sharedInstance] invokeWithTopic:topic opts:nil params:param respHandler:^(LKAppExpResponse * _Nonnull response) {
    
  }];
}
- (void)subscribeTopic:(NSString *)topic{
  [[LKAppExpress sharedInstance] subscribe:topic complete:^(NSError * _Nullable error) {
    if (error) {
      self.listenerBlock(error);
      [self cancelTopic:topic callback:^(BOOL isSuccess) {
        
      }];
    }else{
      self.listenerBlock(nil);
    }
  }];
}
- (void)cancelTopic:(NSString *)topic callback:(void(^)(BOOL isSuccess))callback{
  [[LKAppExpress sharedInstance] unsubscribe:topic complete:^(NSError * _Nullable error) {
    if (error) {
      callback(NO);
    }else{
      callback(YES);
    }
  }];
}
- (void)onDownstream:(NSString * _Nonnull)topic data:(id  _Nullable)data{

//  [AlertShow showAlertWithMessage:[NSString stringWithFormat:@"%@%@",topic,data]];
  
  [RNSendToJsReact emitEventWithName:kSokectBack andPayload:@{@"data":@{@"s1":[self toJSONString:data],@"state":topic}}];
  
}
- (NSString *)toJSONString:(NSDictionary *)dict {
  NSData *data = [NSJSONSerialization dataWithJSONObject:dict
                                                 options:NSJSONReadingMutableLeaves | NSJSONReadingAllowFragments
                                                   error:nil];
  
  if (data == nil) {
    return nil;
  }
  
  NSString *string = [[NSString alloc] initWithData:data
                                           encoding:NSUTF8StringEncoding];
  return string;
}
- (BOOL)shouldHandle:(NSString * _Nonnull)topic{
  
  return YES;
}
- (BOOL)connectState{
  return self.isConnect;
}
@end
