//
//  IMSCredential.h
//  IMSAccount
//
//  Created by Hager Hu on 01/11/2017.
//

#import <Foundation/Foundation.h>

/**
 IoT 统一用户身份凭证，用户身份凭证的操作请参见：`IMSCredentialManager`
 */
@interface IMSCredential : NSObject

/**
 用户身份凭证唯一标示
 */
@property (nonatomic, copy, readonly, nonnull) NSString *identityId;

/**
 iotToken，类似用户会话的作用，失效时间通常比较短（比如 24 小时），过期可通过 RefreshToken 刷新一个新的 iotToken 回来
 */
@property (nonatomic, copy, readonly, nonnull) NSString *iotToken;

/**
 RefreshToken，用于刷新 iotToken，失效时间通常比较长（比如 30 天），RefreshToken 过期时账号必须重新登录
 */
@property (nonatomic, copy, readonly, nonnull) NSString *iotRefreshToken;

/**
 @return 返回 iotToken 是否已过期
 */
- (BOOL)isIotTokenExpired;

/**
 @return 返回 RefreshToken 是否已过期
 */
- (BOOL)isIotRefreshTokenExpired;

- (instancetype _Nonnull)init NS_UNAVAILABLE;

@end
