//
//  libAliLiving.m
//  libAliLiving
//
//  Created by 初程程 on 2019/4/1.
//  Copyright © 2019年 初程程. All rights reserved.
//

#import "libAliLiving.h"
#import "IMSIotAuth.h"
#import "IMSOpenAccount.h"
#import "FYSDK.h"
#import "RNSendToJsReact.h"
#import "WebSocketClient.h"
#import "IMSNetWorkServer.h"
#define kLoginError @"50001"
#define JK_IS_STR_NIL(objStr) (![objStr isKindOfClass:[NSString class]] || objStr == nil || [objStr length] <= 0)
@interface libAliLiving()<RCTBridgeModule>
@end
@implementation libAliLiving
RCT_EXPORT_MODULE(UgenAliLiving);
//登录
RCT_REMAP_METHOD(login, resolve:(RCTPromiseResolveBlock)resolve rejecter:(RCTPromiseRejectBlock)rejecter){
    UIViewController *con = (UIViewController *)[[UIApplication sharedApplication] keyWindow].rootViewController;
    
    [[IMSOpenAccount sharedInstance] showLoginWithController:con success:^(NSDictionary *response) {
        [IMSIotAuth checkToken];
        resolve(response);
    } failure:^(NSError *error) {
        rejecter(kLoginError,error.domain,error);
    }];
}
//退出登录
RCT_EXPORT_METHOD(logout:(RCTPromiseResolveBlock)resolve rejecter:(RCTPromiseRejectBlock)rejecter){
    [[IMSOpenAccount sharedInstance] logout];
    if ([[IMSOpenAccount sharedInstance] isLogin]) {
        rejecter(@"100001",@"退出登录失败",nil);
    }else{
        resolve(@"sucess");
    }
}
//登录状态判断
RCT_EXPORT_METHOD(isLogin:(RCTPromiseResolveBlock)resolve isLoginRejecter:(RCTPromiseRejectBlock)rejecter){
    BOOL result = [[IMSOpenAccount sharedInstance] isLogin];
    if(result) {
        resolve(@"");
    }else{
        rejecter(@"401",@"未登录",nil);
    }
}
//开始搜寻设备
RCT_EXPORT_METHOD(startScanLocalDevice){
    [[FYSDK sharedInstance] startScanLocalDevice:^(NSDictionary * _Nonnull deviceDict, NSError * _Nonnull err) {
        if (err) {
            [RNSendToJsReact emitEventWithName:kError andPayload:@{@"message":err.domain,@"code":@"500"}];
        }else{
            [RNSendToJsReact emitEventWithName:kScanLocationDevice andPayload:deviceDict];
        }
    }];
}
//停止查找设备
RCT_EXPORT_METHOD(stopScanLocalDevice){
    [[FYSDK sharedInstance] stopScanLocalDevice];
}
//添加配网设备
RCT_EXPORT_METHOD(startAddDevice:(NSString *)productKey){
    FYSDK *sdk = [FYSDK sharedInstance];
    
    [sdk startAddDeviceWithProductKey:productKey];
    
    sdk.provisionStatusBlock = ^(NSDictionary *statusDict) {
        [RNSendToJsReact emitEventWithName:kOnProvisionStatus andPayload:@{}];
    };
    
    sdk.provisionedResultBlock = ^(NSDictionary *result, NSError *err) {
        if (err) {
            NSString *codeStr = [NSString stringWithFormat:@"%ld",(long)err.code];
            NSDictionary *errDict = @{@"data":codeStr};
            [RNSendToJsReact emitEventWithName:kError andPayload:errDict];
        }else{
            [RNSendToJsReact emitEventWithName:kOnProvisionedResult andPayload:@{@"data":result}];
        }
    };
    sdk.provisioningBlock = ^{
        [RNSendToJsReact emitEventWithName:kOnProvisioning andPayload:@{}];
    };
    sdk.provisionPrepareBlock = ^(NSInteger state) {
        [RNSendToJsReact emitEventWithName:kOnProvisionPrepare andPayload:@{}];
    };
    sdk.preCheckBlock = ^(BOOL success, NSError *err) {
        if (err) {
            [RNSendToJsReact emitEventWithName:kError andPayload:@{}];
        }else{
            [RNSendToJsReact emitEventWithName:kOnPreCheck andPayload:@{}];
        }
    };
}
//中止添加设备配网流程
RCT_EXPORT_METHOD(stopAddDevice){
    [[FYSDK sharedInstance] stopAddDevice];
}
//添加配网的wifi名和wifi密码
RCT_REMAP_METHOD(toggleProvision,wifiName:(NSString *)wifiName wifiPassword:(NSString *)wifiPassword timeout:(int)timeout){
    [[FYSDK sharedInstance] toggleProvisionWithName:wifiName wifiPassword:wifiPassword timeout:timeout];
}
//获取设备token
RCT_REMAP_METHOD(getDeviceToken,pk:(NSString *)pk dn:(NSString *)dn timeout:(NSString *)timeout getTokenResolve:(RCTPromiseResolveBlock)resolve getTokenRejecter:(RCTPromiseRejectBlock)rejecter){
    __block BOOL isBack = NO;
    [[FYSDK sharedInstance] getDeviceTokenWithProductKey:pk deviceName:dn timeout:timeout.integerValue block:^(NSString * _Nonnull token) {
        if (!JK_IS_STR_NIL(token)) {
            if (!isBack) {
                isBack = YES;
                resolve(token);
            }
        }else{
            if (!isBack) {
                isBack = YES;
                rejecter(@"567",@"token获取失败",nil);
            }
        }
    }];
}
RCT_EXPORT_METHOD(startAliSocketListener){
    [[WebSocketClient sharedInstance] startListener];
    [WebSocketClient sharedInstance].listenerBlock = ^(NSError *err) {
        if (err) {
            [RNSendToJsReact emitEventWithName:kListenerError andPayload:@{}];
        }else{
            [RNSendToJsReact emitEventWithName:kListenerSuccess andPayload:@{}];
        }
    };
}
RCT_REMAP_METHOD(stopAliSocketListener,stopResolve:(RCTPromiseResolveBlock)resolve stopRejecter:(RCTPromiseRejectBlock)rejecter){
    [[WebSocketClient sharedInstance] stopListener:^(BOOL isSuccess) {
        resolve(isSuccess?@"1":@"0");
    }];
}
RCT_REMAP_METHOD(getAliSocketListenerState,stateResolve:(RCTPromiseResolveBlock)resolve stateRejecter:(RCTPromiseRejectBlock)rejecter){
    BOOL isOpen = [[WebSocketClient sharedInstance] connectState];
    
    resolve(isOpen?@"1":@"0");
}
RCT_REMAP_METHOD(getCurrentAccountMessage,accountResolve:(RCTPromiseResolveBlock)resolve accountRejecter:(RCTPromiseRejectBlock)rejecter){
    NSDictionary*dict = [[IMSOpenAccount sharedInstance] getCurrentSession];
    NSLog(@"%@=============",dict);
    if (dict) {
        resolve(dict);
    }else{
        resolve(@"");
    }
}
//发送网络请求
RCT_REMAP_METHOD(send, path:(NSString *)path params:(id)params version:(NSString *)version iotAuth:(BOOL)iotAuth sendResolve:(RCTPromiseResolveBlock)resolve sendRejecter:(RCTPromiseRejectBlock)rejecter){
    
    NSData *data = [params dataUsingEncoding:NSUTF8StringEncoding];
    NSDictionary *dict = [NSJSONSerialization JSONObjectWithData:data options:0 error:nil];
    
    [IMSNetWorkServer sendIotAuthRequestWithPath:path version:version params:dict handler:^(BOOL isSuccess, id response ,NSString *requestId) {
        if (isSuccess) {
            NSDictionary *dict =@{@"data":response};
            NSString *json = [self toJSONStringWithDict:dict];
            resolve(json);
        }else{
            NSError *error = (NSError *)response;
            rejecter([NSString stringWithFormat:@"%ld",(long)error.code],requestId,error);
        }
    }];
}
- (NSString *)toJSONStringWithDict:(NSDictionary *)dict {
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
- (dispatch_queue_t)methodQueue{
    return dispatch_get_main_queue();
}
- (instancetype)init
{
    self = [super init];
    if (self) {
        
    }
    return self;
}

@end
