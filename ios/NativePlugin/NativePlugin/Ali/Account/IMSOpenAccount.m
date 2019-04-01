//
//  IMSOpenAccount.m
//  IMSAccount
//
//  Created by Hager Hu on 01/11/2017.
//

#import "IMSOpenAccount.h"

#import <ALBBOpenAccountCloud/ALBBOpenAccountSDK.h>
#import <ALBBOpenAccountCloud/ALBBOpenAccountUser.h>

#import <IMSApiClient/IMSConfiguration.h>
#import <IMSAccount/IMSAccountService.h>
#define JK_IS_STR_NIL(objStr) (![objStr isKindOfClass:[NSString class]] || objStr == nil || [objStr length] <= 0)
NSString * _Nonnull const IMSNotificationAccountLogin = @"IMSNotificationAccountLogin";
NSString * _Nonnull const IMSNotificationAccountLogout = @"IMSNotificationAccountLogout";
@interface IMSOpenAccount()<SSODelegate>
@end
@implementation IMSOpenAccount

#pragma mark - IMSAccountProtocol

+ (instancetype)sharedInstance {
    static IMSOpenAccount *account;
    
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        account = [[[self class] alloc] init];
    });
    
    return account;
}

- (id)init {
    if (self = [super init]) {
        // TODO: AEP平台对外只暴露线上环境，此处环境设置联调完成后需要更改
        //[[ALBBOpenAccountSDK sharedInstance] setDebugLogOpen:YES];
        IMSConfiguration *configuration = [IMSConfiguration sharedInstance];
        
        //设置安全图片
        [[ALBBOpenAccountSDK sharedInstance] setSecGuardImagePostfix:configuration.authCode];
        
        //设置环境
        TaeSDKEnvironment taeEnv = TaeSDKEnvironmentRelease;
        if (configuration.serverEnv == IMSServerDaily) {
            taeEnv = TaeSDKEnvironmentDaily;
        } else if (configuration.serverEnv == IMSServerPreRelease) {
            taeEnv = TaeSDKEnvironmentPreRelease;
        }
        //IMSAccountLogInfo(@"IMSConfiguration env:%d Account env:%d", configuration.serverEnv, taeEnv);
        [[ALBBOpenAccountSDK sharedInstance] setTaeSDKEnvironment:taeEnv];
        
        // 与 @一宵 沟通，不存在初始化失败的情况，所以不需要抛到外层处理
        dispatch_semaphore_t semaphore = dispatch_semaphore_create(0);
        [[ALBBOpenAccountSDK sharedInstance] asyncInit:^{
            //IMSAccountLogInfo(@"accountSDK success");
            dispatch_semaphore_signal(semaphore);
        } failure:^(NSError *error) {
            //IMSAccountLogInfo(@"accountSDK error:%@", error);
            dispatch_semaphore_signal(semaphore);
        }];
        
        dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER);
    }
    
    return self;
}

- (NSString *)accountDidLoginSuccessNotificationName {
    return IMSNotificationAccountLogin;
}

- (NSString *)accountDidLogoutSuccessNotificationName {
    return IMSNotificationAccountLogout;
}

- (NSString *)accountType {
    return @"OA_SESSION";
}

- (NSString *)token {
    return [ALBBOpenAccountSession sharedInstance].sessionID;
}

- (BOOL)isLogin {
    return [[ALBBOpenAccountSession sharedInstance] isLogin];
}

- (void)logout {
    [[NSNotificationCenter defaultCenter] postNotificationName:IMSNotificationAccountLogout object:nil];
    return [[ALBBOpenAccountSession sharedInstance] logout];
}

- (NSDictionary *)currentSession {
    NSMutableDictionary *info = [@{} mutableCopy];
    
    ALBBOpenAccountSession *session = [ALBBOpenAccountSession sharedInstance];
    if ([session isLogin]) {
        [info addEntriesFromDictionary:@{
                                         ACCOUNT_SESSION_KEY: session.sessionID ? :@"",
                                         }];
        
        ALBBOpenAccountUser *user = [ALBBOpenAccountSession sharedInstance].getUser;
        NSString *nickName = user.displayName;
        if (!nickName || [nickName length] == 0) {
            nickName = @"";
        }
        [info addEntriesFromDictionary:@{
                                             ACCOUNT_USER_ID_KEY: user.accountId ? :@"",
                                             ACCOUNT_NICKNAME_KEY: nickName ? :@"",
                                             ACCOUNT_AVATAR_URL_KEY: user.avatarUrl ? :@"",
                                             @"mobile":user.mobile ? :@""
                                             }];
    }
    
    return info;
}
- (NSDictionary *)getCurrentSession{
  return [self currentSession];
}
- (void)updateAccountProfileWithNickName:(NSString *)nickName
                               avatarUrl:(NSString *)avatarUrl
                                  gender:(NSString *)gender
                                response:(void(^)(BOOL isSuccess,NSError *error))response{
  id<ALBBOpenAccountService> accountService = ALBBService(ALBBOpenAccountService);
  
  NSMutableDictionary *accountProfile = [NSMutableDictionary dictionary];
  
  if (JK_IS_STR_NIL(nickName)) {
    [accountProfile setObject:nickName forKey:@"displayName"];
  }
  if (JK_IS_STR_NIL(avatarUrl)) {
    [accountProfile setObject:avatarUrl forKey:@"avatarUrl"];
  }
  if (JK_IS_STR_NIL(gender)) {
    [accountProfile setObject:gender forKey:@"gender"];
  }
  
  [accountService updateAccountProfile:accountProfile.copy Callback:^(NSError *error) {
      response(error==nil,error);
  }];
  
}

#pragma mark - IMSAccountUIProtocol

- (void)showLoginWithController:(UIViewController *)controller
                        success:(void (^)(NSDictionary *response))success
                        failure:(void (^)(NSError *error))failure {
  
    id<ALBBOpenAccountUIService> uiService = ALBBService(ALBBOpenAccountUIService);
    
    [uiService presentLoginViewController:controller success:^(ALBBOpenAccountSession *currentSession) {
        //登录成功回调
        
        if (success) {
            success([self currentSession]);
            [[NSNotificationCenter defaultCenter] postNotificationName:IMSNotificationAccountLogin object:nil];
        }
        
    } failure:^(NSError *error) {
        //登录失败回调
        if (failure) {
            failure(error);
        }
    }];
}
- (void)thirdLoginWithAuthCode:(NSString *)code{
    id<ALBBOpenAccountSSOService> ssoService = ALBBService(ALBBOpenAccountSSOService);
    [ssoService oauthWithThirdParty:code delegate:self];
}
- (void)openAccountOAuthError:(NSError *)error Session:(ALBBOpenAccountSession *)session{
  NSLog(@"%@",session);
  NSLog(@"%@",error);
}
@end
