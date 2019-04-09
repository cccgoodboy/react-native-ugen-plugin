//
//  AliLiving.m
//  AliLiving
//
//  Created by 初程程 on 2019/4/9.
//  Copyright © 2019年 初程程. All rights reserved.
//

#import "AliLiving.h"


@interface AliLiving()<RCTBridgeModule>
@end
@implementation AliLiving
RCT_EXPORT_MODULE(UgenAliLiving);
//初始化
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
