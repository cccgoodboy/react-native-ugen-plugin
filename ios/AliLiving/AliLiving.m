//
//  AliLiving.m
//  AliLiving
//
//  Created by 初程程 on 2019/4/9.
//  Copyright © 2019年 初程程. All rights reserved.
//

#import "AliLiving.h"
#import "IMSIotAuth.h"
#import "IMSOpenAccount.h"
#import "FYSDK.h"
#import "RNSendToJsReact.h"
#import "WebSocketClient.h"
#import "IMSNetWorkServer.h"
#import <React/RCTBridge.h>
#import <IMSApiClient/IMSConfiguration.h>
#import <IMSAccount/IMSAccountService.h>
#import <IMSAuthentication/IMSAuthentication.h>
#define kLoginError @"50001"
#define JK_IS_STR_NIL(objStr) (![objStr isKindOfClass:[NSString class]] || objStr == nil || [objStr length] <= 0)

@interface AliLiving()<RCTBridgeModule>
@end
@implementation AliLiving
RCT_EXPORT_MODULE(UgenAliLiving);
//初始化
RCT_EXPORT_METHOD(instanceSDK){
    if (![IMSAccountService sharedService].accountProvider) {
        [IMSConfiguration initWithHost:@"api.link.aliyun.com" serverEnv:IMSServerRelease];
        
        IMSOpenAccount *openAccount = [IMSOpenAccount sharedInstance];
        
        [IMSAccountService sharedService].accountProvider = openAccount;
        
        [IMSAccountService sharedService].sessionProvider = openAccount;
        
        [IMSIotAuth auth];
    }
}
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
//自有登录
RCT_REMAP_METHOD(ssoLogin,authCode:(NSString *)authCode ssoResolve:(RCTPromiseResolveBlock)resolve ssoRejecter:(RCTPromiseRejectBlock)rejecter){
    
    [IMSOpenAccount sharedInstance].thirdLoginResult = ^(NSError *err, NSDictionary *session) {
        if (err) {
            rejecter(kLoginError,err.domain,err);
        }else{
            resolve(session);
        }
    };
    
    [[IMSOpenAccount sharedInstance] thirdLoginWithAuthCode:authCode];
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
    
    sdk.provisionStatusBlock = ^(NSDictionary *statusDict) {
        [RNSendToJsReact emitEventWithName:kOnProvisionedResult andPayload:@{@"data":@{@"state":kOnProvisionStatus,@"result":@""}}];
    };
    
    sdk.provisionedResultBlock = ^(NSDictionary *result, NSError *err) {
        if (err) {
            NSString *codeStr = [NSString stringWithFormat:@"%ld",(long)err.code];
            NSDictionary *errDict = @{@"data":codeStr};
            [RNSendToJsReact emitEventWithName:kError andPayload:errDict];
        }else{
            [RNSendToJsReact emitEventWithName:kOnProvisionedResult andPayload:@{@"data":@{@"state":kOnProvisionedResult,@"result":result}}];
        }
    };
    sdk.provisioningBlock = ^{
        [RNSendToJsReact emitEventWithName:kOnProvisionedResult andPayload:@{@"data":@{@"state":kOnProvisioning,@"result":@""}}];
    };
    
    sdk.provisionPrepareBlock = ^(NSInteger state) {
        [RNSendToJsReact emitEventWithName:kOnProvisionedResult andPayload:@{@"data":@{@"state":kOnProvisionPrepare,@"result":[NSString stringWithFormat:@"%ld",state]}}];
    };
    sdk.preCheckBlock = ^(BOOL success, NSError *err) {
        if (err) {
            [RNSendToJsReact emitEventWithName:kError andPayload:@{}];
        }else{
            [RNSendToJsReact emitEventWithName:kOnProvisionedResult andPayload:@{@"data":@{@"state":kOnPreCheck,@"result":@""}}];
        }
    };
    
    [sdk startAddDeviceWithProductKey:productKey];
}
//中止添加设备配网流程
RCT_EXPORT_METHOD(stopAddDevice){
    [[FYSDK sharedInstance] stopAddDevice];
}
//添加配网的wifi名和wifi密码
RCT_REMAP_METHOD(toggleProvision,wifiName:(NSString *)wifiName wifiPassword:(NSString *)wifiPassword timeout:(NSString *)timeout){
    [[FYSDK sharedInstance] toggleProvisionWithName:wifiName wifiPassword:wifiPassword timeout:[timeout intValue]];
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
RCT_REMAP_METHOD(getAccountCredential,getAccountResolve:(RCTPromiseResolveBlock)resolve getAccountRejecter:(RCTPromiseRejectBlock)rejecter){
    IMSCredential *credential = [IMSCredentialManager sharedManager].credential;
    
    NSDictionary *credentialDict = @{
                                     @"identityId":credential.identityId,
                                     @"iotToken":credential.iotToken,
                                     @"iotRefreshToken":credential.iotRefreshToken
                                     };
    
    resolve(credentialDict);
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
//isWifi5G
RCT_REMAP_METHOD(isWifi5G,isFiveWifiResolve:(RCTPromiseResolveBlock)resolve isFiveWifiRejecter:(RCTPromiseRejectBlock)rejecter){
    //    resolve(YES);
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
//RCT_REMAP_METHOD(getWifiState,wifiResolve:(RCTPromiseResolveBlock)resolve wifiRejecter:(RCTPromiseRejectBlock)rejecter){
//    resolve([self getSignalStrengthBar]);
//}
//- (NSString *)getSignalStrengthBar {
//    if (![self whetherConnectedNetwork]) return @"";
//    UIApplication *app = [UIApplication sharedApplication];
//    NSArray *subviews = [[[app valueForKey:@"statusBar"] valueForKey:@"foregroundView"] subviews];
//    NSString *dataNetworkItemView = nil;
//    NSString *signalStrengthBars = @"";
//    for (id subview in subviews) {
//        if([subview isKindOfClass:[NSClassFromString(@"UIStatusBarDataNetworkItemView") class]] && [[self getNetworkType] isEqualToString:@"WIFI"] && ![[self getNetworkType] isEqualToString:@"NONE"]) {
//            dataNetworkItemView = subview;
//            signalStrengthBars = [NSString stringWithFormat:@"0%@",[dataNetworkItemView valueForKey:@"_wifiStrengthBars"]];
//            break;
//        }
//        if ([subview isKindOfClass:[NSClassFromString(@"UIStatusBarSignalStrengthItemView") class]] && ![[self getNetworkType] isEqualToString:@"WIFI"] && ![[self getNetworkType] isEqualToString:@"NONE"]) {
//            dataNetworkItemView = subview;
//            signalStrengthBars = [NSString stringWithFormat:@"1%@",[dataNetworkItemView valueForKey:@"_signalStrengthBars"]];
//            break;
//        }
//    }
//    return signalStrengthBars;
//}
//- (NSString *)getNetworkType {
//    if (![self whetherConnectedNetwork]) return @"NONE";
//    UIApplication *app = [UIApplication sharedApplication];
//    NSArray *subviews = [[[app valueForKeyPath:@"statusBar"] valueForKeyPath:@"foregroundView"] subviews];
//    NSString *type = @"NONE";
//    for (id subview in subviews) {
//        if ([subview isKindOfClass:NSClassFromString(@"UIStatusBarDataNetworkItemView")]) {
//            int networkType = [[subview valueForKeyPath:@"dataNetworkType"] intValue];
//            switch (networkType) {
//                case 0:
//                    type = @"NONE";
//                    break;
//                case 1:
//                    type = @"2G";
//                    break;
//                case 2:
//                    type = @"3G";
//                    break;
//                case 3:
//                    type = @"4G";
//                    break;
//                case 5:
//                    type = @"WIFI";
//                    break;
//            }
//        }
//    }
//    return type;
//}
//- (BOOL)whetherConnectedNetwork
//{
//    //创建零地址，0.0.0.0的地址表示查询本机的网络连接状态
//
//    struct sockaddr_storage zeroAddress;//IP地址
//
//    bzero(&zeroAddress, sizeof(zeroAddress));//将地址转换为0.0.0.0
//    zeroAddress.ss_len = sizeof(zeroAddress);//地址长度
//    zeroAddress.ss_family = AF_INET;//地址类型为UDP, TCP, etc.
//
//    // Recover reachability flags
//    SCNetworkReachabilityRef defaultRouteReachability = SCNetworkReachabilityCreateWithAddress(NULL, (struct sockaddr *)&zeroAddress);
//    SCNetworkReachabilityFlags flags;
//
//    //获得连接的标志
//    BOOL didRetrieveFlags = SCNetworkReachabilityGetFlags(defaultRouteReachability, &flags);
//    CFRelease(defaultRouteReachability);
//
//    //如果不能获取连接标志，则不能连接网络，直接返回
//    if (!didRetrieveFlags)
//    {
//        return NO;
//    }
//    //根据获得的连接标志进行判断
//
//    BOOL isReachable = flags & kSCNetworkFlagsReachable;
//    BOOL needsConnection = flags & kSCNetworkFlagsConnectionRequired;
//    return (isReachable&&!needsConnection) ? YES : NO;
//}
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
