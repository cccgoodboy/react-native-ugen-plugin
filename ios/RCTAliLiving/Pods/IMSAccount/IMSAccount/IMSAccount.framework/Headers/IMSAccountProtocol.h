//
//  IMSAccountProtocol.h
//  IMSAccount
//
//  Created by Hager Hu on 01/11/2017.
//

#import <Foundation/Foundation.h>

#import "IMSAccountConstants.h"

/*
 IMSAccountService的UI提供者必须实现IMSAccountUIProtocol协议。
 */
@protocol IMSAccountProtocol <NSObject>

@required

/**
 * 获取账号登录成功通知名称，协议实现者在账号登录成功后需要调用 `NSNotificationCenter` 的 `postNotificationName:object:` 方法发送该通知
 * @return 登录成功通知的名称，不允许为 nil
 */
- (NSString *)accountDidLoginSuccessNotificationName;

/**
 * 获取账号登录成功通知名称，协议实现者在账号退出登录成功后需要调用 `NSNotificationCenter` 的 `postNotificationName:object:` 方法发送该通知
 * @return 退出登录成功通知的名称，不允许为 nil
 */
- (NSString *)accountDidLogoutSuccessNotificationName;

/**
 * 获取账号类型，是和 IoT 服务器约定的，如："OA_SESSION"
 * @return 退出登录成功通知的名称，不允许为 nil
 */
- (NSString *)accountType;

/**
 * 获取当前的会话信息，云端需要用户鉴权时使用的信息，如：`accountType` 为 "OA_SESSION" 时该值是 OA 的 `sessionId`
 * @return 返回当前的会话信息，没有登录则返回 nil。
 */
- (NSString *)token;

/**
 * 返回当前是否已经登录
 * @return 返回当前是否已经登录
 */
- (BOOL)isLogin;

/**
 * 退出登录
 */
- (void)logout;

/**
 * 提供当前登录的会话信息
 *
 * 当前登录的会话信息需要包括以下字段：ACCOUNT_SESSION_KEY, ACCOUNT_USER_ID_KEY, ACCOUNT_NICKNAME_KEY, ACCOUNT_AVATAR_URL_KEY
 * 分别对应当前的会话信息，用户标识，用户昵称和用户头像；除此之外，也可以提供其他扩展信息。
 *
 * @return 包含当前登录的会话信息，包括用户信息
 */
- (NSDictionary *)currentSession;

@end
