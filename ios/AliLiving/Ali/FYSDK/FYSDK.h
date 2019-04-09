//
//  FYSDK.h
//  HelloDemo
//
//  Created by 初程程 on 2019/3/22.
//  Copyright © 2019年 Facebook. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface FYSDK : NSObject
@property (nonatomic ,copy)void(^preCheckBlock)(BOOL success,NSError *err);
@property (nonatomic ,copy)void(^provisionPrepareBlock)(NSInteger state);
@property (nonatomic ,copy)void(^provisioningBlock)();
@property (nonatomic ,copy)void(^provisionStatusBlock)(NSDictionary *statusDict);
@property (nonatomic ,copy)void(^provisionedResultBlock)(NSDictionary *result,NSError *err);


/**
   FYSDK单例
 
   @return FYSDK实例
 */
+ (FYSDK *)sharedInstance;
/**
  启动设备发现
 */
- (void)startScanLocalDevice:(void(^)(NSDictionary *deviceDict ,NSError *err))block;
/**
  停止设备发现
 */
- (void)stopScanLocalDevice;
/**
  添加设备配网
 
  @param productKey 设备pk
 
  @return void
 */
- (void)startAddDeviceWithProductKey:(NSString *)productKey;

/**
  停止设备配网流程
 */
- (void)stopAddDevice;
/**
  添加配网的wifi名和wifi密码
 */
- (void)toggleProvisionWithName:(NSString *)wifiName
                   wifiPassword:(NSString *)wifiPassword
                        timeout:(int)timeout;
/**
   获取设备token
   @param productKey  设备pk
   @param deviceName  设备dn
   @param timeout     超时时间
 
   @return void
 */
- (void)getDeviceTokenWithProductKey:(NSString *)productKey
                          deviceName:(NSString *)deviceName
                             timeout:(NSUInteger)timeout
                               block:(void(^)(NSString *token))block;
@end

NS_ASSUME_NONNULL_END
