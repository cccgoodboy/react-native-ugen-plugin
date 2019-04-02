//
//  IMSAccountService.h
//  IMSAccount
//
//  Created by Hager Hu on 01/11/2017.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

#import "IMSAccountProtocol.h"
#import "IMSAccountUIProtocol.h"

extern NSInteger const NO_SERVICE_PROVIDER_CODE;
extern NSString *const NO_SERVICE_PROVIDER_DOMAIN;

/**
 * IMSAccountService
 * 用于支持BoneKit对账号相关的服务，如显示登录窗口，退出登录，获取账号信息。
 * 通过协议的形式支持其他账号实现对接
 */
@interface IMSAccountService : NSObject

/**
 * 账号服务使用的session提供者，用于提供会话对应的信息
 */
@property (nonatomic, weak) id<IMSAccountProtocol> sessionProvider;

/**
 * 账号服务提供登录操作的UI提供者
 * 可以自定义实现，需要实现IMSAccountUIProtocol协议。
 */
@property (nonatomic, weak) id<IMSAccountUIProtocol> accountProvider;


// 当前账号服务对应的单例
+ (instancetype)sharedService;

/**
 * 显示登录窗口
 * @param controller 当前用于显示登录窗口的视图控制器
 * @param success 登录成功后之后的会话信息
 * @param failure 登录失败的错误信息，取消登录也会有对应错误
 */
- (void)showLoginWithController:(UIViewController *)controller
                        success:(void (^)(NSDictionary *session))success
                        failure:(void (^)(NSError *error))failure;

/**
 * 登出操作，清除当前登录用户信息，失效当前会话信息
 */
- (void)logout;

/**
 * 是否已经登录
 * @return 当前登录状态则返回YES，否则返回NO
 */
- (BOOL)isLogin;

/**
 * 返回当前的会话信息，也就是sessionProvider提供的会话信息
 *
 * @return 已经登录则返回当前的会话信息，否则返回nil
 */
- (NSDictionary *)currentSession;

@end
