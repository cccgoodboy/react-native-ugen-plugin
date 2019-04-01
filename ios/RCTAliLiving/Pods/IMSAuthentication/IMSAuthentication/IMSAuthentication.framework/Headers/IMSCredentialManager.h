//
//  IMSCredentialManager.h
//  IMSAuthentication
//
//  Created by 文季 on 2018/1/9.
//

#import <Foundation/Foundation.h>
#import <IMSAccount/IMSAccountProtocol.h>
#import <IMSAuthentication/IMSCredential.h>

/**
 刷新用户身份凭证的错误都通过该 Domain 返回，如果有下一级错误详情，
 则通过 - [NSError userInfo] 的 detail 字段透传，
 透传 detail 的类型有可能有 NSError 或 IMSResponse，
 比如，网络请求错误会通过 NSError 类型的 detail 字段返回（Domain 为 NSURLErrorDomain），
 服务器错误，会通过 IMSResponse 类型的 detail 字段返回
 */
extern NSString * _Nonnull const IMSCredentialManagerErrorDomain;

/**
 IMSCredentialManagerErrorDomain 错误码
 */
typedef NS_ENUM(NSInteger, IMSCredentialManagerErrorCode) {
    IMSCredentialManagerErrorCodeNotLogin = 1,          ///< 账号未登录，需要登录
    IMSCredentialManagerErrorCodeAccountTypeInvalid,    ///< 账号类型错误，`IMSAccountProtocol` 中的  `accountType` 需要和服务端指定的保持一致
    IMSCredentialManagerErrorCodeAuthCodeInvalid,       ///< 账号 token 无效，无法创建用户身份凭证，需要在刷新前确保 `IMSAccountProtocol` 中的 `token` 有效
    IMSCredentialManagerErrorCodeRefreshTokenInvalid,   ///< 服务器返回 RefreshToken 过期或无效，需要重新登录
    IMSCredentialManagerErrorCodeWrongResponseFormat,   ///< 服务器响应的报文格式异常
    IMSCredentialManagerErrorCodeOther = -1,            ///< 其他错误，如，网络错误或服务器返回的错误，会把原始错误信息通过 userInfo.detail 透传
};

/**
 用于管理和刷新用户身份凭证，
 该类下的 `credential` 和 `asyncRefreshCredential:` 两个方法是线程安全的
 */
@interface IMSCredentialManager : NSObject

/**
 初始化 `IMSCredentialManager` 有且仅有调用一次
 
 通过账号抽象协议来初始化，IMSCredentialManager 会监听账号登录和登出通知
 1）在账号登录的时候根据 accountType 和 token 创建用户身份凭证 `IMSCredential`
 2）在账号登出的时候清除用户身份凭证
 
 @param accountProtocol 账号抽象协议
 @return 成功返回 YES，失败返回 NO
 */
+ (BOOL)initWithAccountProtocol:(id<IMSAccountProtocol> _Nonnull)accountProtocol;

/**
 单例
 
 获取该单例前请先调用 `initWithAccountProtocol:` 来初始化 `IMSCredentialManager`，否则会抛出异常
 */
+ (instancetype _Nonnull)sharedManager;

- (instancetype _Nonnull)init NS_UNAVAILABLE;

/**
 同步获取 IoT 用户身份凭证，用户成功登录后会生成该凭证并持久化，用户退出登录后清除
 @return 成功返回 `IMSCredential` 实例，失败返回 nil
 */
@property (atomic, strong, readonly, nullable) IMSCredential *credential;

/**
 异步刷新用户身份凭证
 
 总是会发起网络请求，有两种场景需要用到该接口：
 1）`credential` 同步接口返回为空，通过该接口来刷新一个凭证（前提是用户账号已经登录）
 2）`IMSCredential` 中的 `iotToken` 过期时间比较短，比如 24小时，在 iotToken 过期的时候需要调用该接口刷新一个新的 `iotToken`，刷新失败请参考 `IMSCredentialManagerErrorDomain` 下的错误码列表 `IMSCredentialManagerErrorCode` 来处理错误。
 @param completionHandler 刷新回调
 */
- (void)asyncRefreshCredential:(void (^ _Nonnull)(NSError * _Nullable error, IMSCredential * _Nullable credential))completionHandler;

@end
