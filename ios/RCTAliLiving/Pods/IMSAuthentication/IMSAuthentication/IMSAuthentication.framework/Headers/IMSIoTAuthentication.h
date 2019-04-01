//
//  IMSIoTAuthentication.h
//  IMSApiClient
//
//  Created by 文季 on 2018/1/4.
//

#import <Foundation/Foundation.h>
#import <IMSApiClient/IMSApiClient.h>
#import <IMSAuthentication/IMSCredentialManager.h>

/**
 IoT 统一身份认证类型，用于标示 `IMSIoTAuthentication` 类型
 */
extern NSString * _Nonnull const IMSAuthenticationTypeIoT;

/**
 IoT 统一身份认证委托实现，实现协议 `IMSAuthenticationDelegate`
 
 通过 `IMSRequestClient` 的 `registerDelegate:forAuthenticationType:` 方法进行注册，认证类型为 `IMSAuthenticationTypeIoT`
 */
@interface IMSIoTAuthentication : NSObject <IMSAuthenticationDelegate>

- (instancetype _Nonnull)init NS_UNAVAILABLE;

/**
 初始化方法
 @param credentialManager 用户身份凭证管理器
 @return `IMSIoTAuthentication` 实例
 */
- (instancetype _Nonnull)initWithCredentialManager:(IMSCredentialManager * _Nonnull)credentialManager NS_DESIGNATED_INITIALIZER;

@end
