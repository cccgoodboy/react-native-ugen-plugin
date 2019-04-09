//
//  RNSendToJsReact.h
//  LoginDemo
//
//  Created by 初程程 on 2018/6/15.
//  Copyright © 2018年 Facebook. All rights reserved.
//

#import <React/RCTEventEmitter.h>
#define kOnPreCheck           @"onPreCheck"
#define kOnProvisionPrepare   @"onProvisionPrepare"
#define kOnProvisioning       @"onProvisioning"
#define kOnProvisionStatus    @"onProvisionStatus"
#define kOnProvisionedResult  @"onProvisionedResult"
#define kError                @"error"
#define kScanLocationDevice   @"scanLocationDevice"
#define kListenerSuccess      @"listenerSuccess"
#define kListenerError        @"listenerError"
#define kNotifySuccess        @"kNotifySuccess"
#define kNotifyError          @"kNotifyError"
#define kBLEScan              @"kBLEScan"
#define kSokectBack           @"sokectBack"
#define kAppExpConnectStateChange @"AppExpConnectStateChange"
@interface RNSendToJsReact : RCTEventEmitter<RCTBridgeModule>
+ (void)emitEventWithName:(NSString *)name andPayload:(NSDictionary *)payload;
@end
