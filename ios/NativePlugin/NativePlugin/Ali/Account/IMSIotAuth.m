//
//  IMSIotAuth.m
//  LoginDemo
//
//  Created by 初程程 on 2018/7/3.
//  Copyright © 2018年 Facebook. All rights reserved.
//

#import "IMSIotAuth.h"
#import <IMSAccount/IMSAccountService.h>
#import <IMSAuthentication/IMSAuthentication.h>
#define JK_IS_STR_NIL(objStr) (![objStr isKindOfClass:[NSString class]] || objStr == nil || [objStr length] <= 0)
@implementation IMSIotAuth
+ (void)auth{
  IMSAccountService *accountService = [IMSAccountService sharedService];
  [IMSCredentialManager initWithAccountProtocol:accountService.sessionProvider];
  IMSIoTAuthentication *iotAuthDelegate = [[IMSIoTAuthentication alloc] initWithCredentialManager:IMSCredentialManager.sharedManager];
  [IMSRequestClient registerDelegate:iotAuthDelegate forAuthenticationType:IMSAuthenticationTypeIoT];
}
+ (void)reloadIotAuth{
  [[IMSCredentialManager sharedManager] asyncRefreshCredential:^(NSError * _Nullable error, IMSCredential * _Nullable credential) {
    if (error) {
      //刷新出错，参考错误码 IMSCredentialManagerErrorCode 处理
    } else {
//      NSString *identityId = credential.identityId;
//      NSString *iotToken = credential.iotToken;
    }
  }];
}
+ (void)checkToken{
  IMSCredential *credential = [IMSCredentialManager sharedManager].credential;
  NSString *identityId = credential.identityId;
  NSString *iotToken = credential.iotToken;
  NSLog(@"%@=====%@",identityId,iotToken);
  if (JK_IS_STR_NIL(iotToken)) {
    [IMSIotAuth reloadIotAuth];
  }
}
@end
