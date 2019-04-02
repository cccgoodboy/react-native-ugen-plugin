//
//  FYSDK.m
//  HelloDemo
//
//  Created by 初程程 on 2019/3/22.
//  Copyright © 2019年 Facebook. All rights reserved.
//

#import "FYSDK.h"
#import <IMSApiClient/IMSApiClient.h>
#import <IMLDeviceCenter/IMLDeviceCenter.h>
#define JK_IS_STR_NIL(objStr) (![objStr isKindOfClass:[NSString class]] || objStr == nil || [objStr length] <= 0)
@interface FYSDK()<ILKAddDeviceNotifier>
@end
@implementation FYSDK
+ (FYSDK *)sharedInstance{
    static FYSDK *manager;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        manager = [[FYSDK alloc] init];
    });
    return manager;
}
- (instancetype)init
{
    self = [super init];
    if (self) {
      
    }
    return self;
}
//启动设备发现
- (void)startScanLocalDevice:(void(^)(NSDictionary *deviceDict ,NSError *err))block{
    [kLKLocalDeviceMgr startDiscovery:^(NSArray *devices, NSError *err) {
        if (devices && devices.count > 0) {
          for (IMLCandDeviceModel *device in devices){
            
            NSDictionary *deviceDict = @{@"deviceName":device.deviceName,
                                         @"productKey":device.productKey,
                                         @"token":JK_IS_STR_NIL(device.token)?@"":device.token
                                         };
            
            block(deviceDict,nil);
          }
        }
        if (err) {
          
        }
    }];
}
//停止设备发现
- (void)stopScanLocalDevice{
    [kLKLocalDeviceMgr stopDiscovery];
}
//添加配网设备
- (void)startAddDeviceWithProductKey:(NSString *)productKey{
    IMLCandDeviceModel *model = [[IMLCandDeviceModel alloc] init];
  
    model.productKey = productKey;
  
    NSInteger errorIndex = [kLkAddDevBiz setDevice:model];
  
    if (errorIndex == 0) {
        [kLkAddDevBiz setAliProvisionMode:ForceAliLinkTypeNone];
      
        [kLkAddDevBiz startAddDevice:self];
    }else{
        NSError *error = [NSError errorWithDomain:@"kSetDeviceError" code:511 userInfo:@{NSLocalizedDescriptionKey:[NSString stringWithFormat:@"error code %ld",(long)errorIndex]}];
      
        [kLkAddDevBiz stopAddDevice];
      
//        self.provisionedResultBlock(@{}, error);
    }
}
//添加配网的wifi名和wifi密码
- (void)toggleProvisionWithName:(NSString *)wifiName
                   wifiPassword:(NSString *)wifiPassword
                        timeout:(int)timeout{
  
  [kLkAddDevBiz toggleProvision:wifiName pwd:wifiPassword timeout:timeout];
  
}
//停止设备配网流程
- (void)stopAddDevice{
    [kLkAddDevBiz stopAddDevice];
  
}
//获取设备token
- (void)getDeviceTokenWithProductKey:(NSString *)productKey
                          deviceName:(NSString *)deviceName
                             timeout:(NSUInteger)timeout
                               block:(void(^)(NSString *token))block{
    [[IMLLocalDeviceMgr sharedMgr] getDeviceToken:productKey deviceName:deviceName timeout:timeout resultBlock:^(NSString *token, BOOL boolSuccess) {
        if (boolSuccess) {
            block(token);
        }else{
            block(@"");
        }
    }];
}



//配网流程代理回调
#pragma mark - ILKAddDeviceNotifier
//预配网结果回调
- (void)notifyPrecheck:(BOOL)success withError:(NSError *)err
{
  self.preCheckBlock(success, err);
}
//配网准备
- (void)notifyProvisionPrepare:(LKPUserGuideCode)guideCode{
  self.provisionPrepareBlock(guideCode);
}
//配网中。。。
-(void)notifyProvisioning
{
  self.provisioningBlock();
}
//阶段性配网状态回调
- (void)notifyProvisionStatus:(LKProvisonStatus)provisionStatus boolSuccess:(BOOL)boolSuccess;
{
  self.provisionStatusBlock(@{@"provisionStatus":@(provisionStatus),@"boolSuccess":@(boolSuccess)});
}
//配网结果回调
- (void)notifyProvisionResult:(IMLCandDeviceModel *)candDeviceModel withProvisionError:(NSError *)provisionError
{
  if (provisionError) {
    self.provisionedResultBlock(@{}, provisionError);
  }else{
    self.provisionedResultBlock(@{@"deviceName":candDeviceModel.deviceName,@"productKey":candDeviceModel.productKey,@"token":JK_IS_STR_NIL(candDeviceModel.token)?@"":candDeviceModel.token}, provisionError);
  }
}

@end
