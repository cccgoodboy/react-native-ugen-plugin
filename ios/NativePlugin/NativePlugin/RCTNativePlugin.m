//
//  RCTNativePlugin.m
//  RCTNativePlugin
//
//  Created by 初程程 on 2018/6/27.
//  Copyright © 2018年 初程程. All rights reserved.
//

#import "RCTNativePlugin.h"
#import "JumpSystemPlugin.h"
#import <CoreTelephony/CTCellularData.h>
#import <UserNotifications/UserNotifications.h>

@interface RCTNativePlugin()
@property (nonatomic ,copy)RCTPromiseResolveBlock resolve;
@property (nonatomic ,copy)RCTPromiseRejectBlock rejecter;
@end
@implementation RCTNativePlugin
RCT_EXPORT_MODULE(AliLiving);

- (dispatch_queue_t)methodQueue{
    return dispatch_get_main_queue();
}
@end
