//
//  RNSendToJsReact.m
//  LoginDemo
//
//  Created by 初程程 on 2018/6/15.
//  Copyright © 2018年 Facebook. All rights reserved.
//

#import "RNSendToJsReact.h"

@implementation RNSendToJsReact
RCT_EXPORT_MODULE(NativeListener);
- (NSArray<NSString *> *)supportedEvents {
  return @[@"LoginSuceess",
           @"onReady",
           kOnPreCheck,
           kOnProvisionPrepare,
           kOnProvisioning,
           kOnProvisionStatus,
           kOnProvisionedResult,
           kError,
           kScanLocationDevice,
           kListenerSuccess,
           kListenerError,
           kNotifySuccess,
           kNotifyError,
           kBLEScan,
           kSokectBack,
           kAppExpConnectStateChange
           ]; //这里返回的将是你要发送的消息名的数组。
}
- (void)startObserving
{
  [[NSNotificationCenter defaultCenter] addObserver:self
                                           selector:@selector(emitEventInternal:)
                                               name:@"LoginSuceess"
                                             object:nil];
  
  [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(onReadyEmitEventInternal:) name:@"onReady" object:nil];
  
  [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(preCheckEmitEventInternal:) name:@"onPreCheck" object:nil];
  
  [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(provisionPrepareEmitEventInternal:) name:@"onProvisionPrepare" object:nil];
  
  [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(provisionedResultEmitEventInternal:) name:@"onProvisionedResult" object:nil];
  
  [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(errorEmitEventInternal:) name:@"error" object:nil];
  
  [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(scanLocationDeviceEmitEventInternal:) name:kScanLocationDevice object:nil];
  
  [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(scanBleDeviceEmitEventInternal:) name:kBLEScan object:nil];
  
  [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(listenerSuccessEmitEventInternal:) name:kListenerSuccess object:nil];
  
  [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(socketBackEmitEventInternal:) name:kSokectBack object:nil];
  
  [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(appSocketListenerEmitEventInternal:) name:kAppExpConnectStateChange object:nil];
}
- (void)stopObserving
{
  [[NSNotificationCenter defaultCenter] removeObserver:self];
}
- (void)appSocketListenerEmitEventInternal:(NSNotification *)noti{
  [self sendEventWithName:kAppExpConnectStateChange body:noti.userInfo[@"value"]];
}
- (void)scanBleDeviceEmitEventInternal:(NSNotification *)noti{
  [self sendEventWithName:kBLEScan body:noti.userInfo[@"device"]];
}
- (void)scanLocationDeviceEmitEventInternal:(NSNotification *)noti{
  [self sendEventWithName:kScanLocationDevice body:noti.userInfo];
}
- (void)errorEmitEventInternal:(NSNotification *)noti{
  [self sendEventWithName:@"error"
                     body:noti.userInfo[@"data"]];
}
- (void)provisionedResultEmitEventInternal:(NSNotification *)noti{
  
  [self sendEventWithName:@"onProvisionedResult"
                     body:noti.userInfo[@"data"]];
}
- (void)provisionStatusEmitEventInternal:(NSNotification *)noti{
  [self sendEventWithName:@"onProvisionStatus"
                     body:noti.userInfo[@"data"]];
}
- (void)provisioningEmitEventInternal:(NSNotification *)noti{
  [self sendEventWithName:@"onProvisioning"
                     body:noti.userInfo[@"data"]];
}
- (void)provisionPrepareEmitEventInternal:(NSNotification *)noti{
  [self sendEventWithName:@"onProvisionPrepare"
                     body:noti.userInfo[@"data"]];
}
- (void)preCheckEmitEventInternal:(NSNotification *)noti{
  [self sendEventWithName:@"onPreCheck"
                     body:noti.userInfo[@"data"]];
}
- (void)onReadyEmitEventInternal:(NSNotification *)noti{
  [self sendEventWithName:@"onReady"
                     body:noti.userInfo[@"data"]];
}
- (void)listenerSuccessEmitEventInternal:(NSNotification *)notification{
  [self sendEventWithName:kListenerSuccess body:@{}];
}
- (void)socketBackEmitEventInternal:(NSNotification *)notification{
  [self sendEventWithName:kSokectBack body:notification.userInfo[@"data"]];
}
- (void)emitEventInternal:(NSNotification *)notification
{
  [self sendEventWithName:@"LoginSuceess"
                     body:notification.userInfo[@"data"]];
}
+ (void)emitEventWithName:(NSString *)name andPayload:(NSDictionary *)payload
{
  [[NSNotificationCenter defaultCenter] postNotificationName:name
                    object:self
                  userInfo:payload];
}
@end
