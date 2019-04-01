//
//  ALBBOpenAccountSDK.h
//  ALBBOpenAccountSDK
//
//  Created by yixiao on 16/10/13.
//  Copyright (c) 2016年 Alibaba. All rights reserved.
//

#import <Foundation/Foundation.h>
#if __has_include(<ALBBOpenAccountSDK/ALBBOpenAccountSDK.h>)
#import <ALBBOpenAccountSDK/ALBBOpenAccountService.h>
#import <ALBBOpenAccountSDK/ALBBOpenAccountSession.h>
#import <ALBBOpenAccountSDK/ALBBOpenAccountUser.h>
#import <ALBBOpenAccountSDK/ALBBOpenAccountDefine.h>
#else
#import <ALBBOpenAccountCloud/ALBBOpenAccountService.h>
#import <ALBBOpenAccountCloud/ALBBOpenAccountSession.h>
#import <ALBBOpenAccountCloud/ALBBOpenAccountUser.h>
#import <ALBBOpenAccountCloud/ALBBOpenAccountDefine.h>
#endif

#if __has_include(<ALBBOpenAccountUI/ALBBOpenAccountUISDK.h>)
#import <ALBBOpenAccountUI/ALBBOpenAccountUISDK.h>
#endif

#if __has_include(<ALBBOpenAccountSSO/ALBBOpenAccountSSOSDK.h>)
#import <ALBBOpenAccountSSO/ALBBOpenAccountSSOSDK.h>
#endif

#if __has_include(<ALBBOpenAccountMTOP/ALBBOpenAccountMtopSessionManager.h>)
#import <ALBBOpenAccountMTOP/ALBBOpenAccountMtopSessionManager.h>
#endif

#define ALBBOpenAccountSDKVersion @"3.4.0.27"

#ifndef ALBBService
#define ALBBService(__protocol__) \
((id<__protocol__>)([[ALBBOpenAccountSDK sharedInstance] getService:@protocol(__protocol__)]))
#endif

#ifndef ALBBOpenAccountNotificationUserLoggedIn
#define ALBBOpenAccountNotificationUserLoggedIn                  @"ALBBOA_NOTIFICATION_USER_LOGGED_IN"
#endif

#ifndef ALBBOpenAccountNotificationUserLoggedOut
#define ALBBOpenAccountNotificationUserLoggedOut                 @"ALBBOA_NOTIFICATION_USER_LOGGED_OUT"
#endif


typedef NS_ENUM(NSUInteger, TaeSDKEnvironment) {
    /** 测试环境 */
    TaeSDKEnvironmentDaily,
    /** 预发环境 */
    TaeSDKEnvironmentPreRelease,
    /** 线上环境 */
    TaeSDKEnvironmentRelease
};


#pragma mark - SDK

@interface ALBBOpenAccountSDK : NSObject

+ (instancetype)sharedInstance;

/**
 ALBBOpenAccountSDK初始化，异步执行
 @param sucessCallback 初始化成功回调
 @param failedCallback 初始化失败回调
 */
- (void)asyncInit:(void (^)(void))sucessCallback
          failure:(void (^)(NSError *error))failedCallback;

/**
 获取ALBBOpenAccountSDK的service 实例
 @param protocol service的协议
 @return service实例
 */
- (id)getService:(Protocol *)protocol;

@end


#pragma mark - option
@interface ALBBOpenAccountSDK (Options)
/**
 设置语言环境，不设置默认简体中文
 @param i18nType @"en"/@"zh-Hans"/@"zh-Hant"
 */
- (void)setI18N:(NSString *)i18nType;


//服务端多语言
- (void)setRpcLocale:(NSString *)locale;
//本地多语言
- (void)setLocale:(NSString *)locale;
//本地多语言资源bundle
- (void)setLocaleBundle:(NSBundle *)localeBundle;

/**
 打开SDK Debug日志
 */
- (void)setDebugLogOpen:(BOOL)isDebugLogOpen;

/**
 指定当前APP的版本，以便关联相关日志和crash分析信息
 @param version 版本号
 */
- (void)setAppVersion:(NSString *)version;

/**
 设置SDK发布渠道,包含渠道类型和渠道名
 */
- (void)setChannel:(NSString *)type name:(NSString *)name;

/**
 指定身份图片yw_1222.jpg的后缀,例如yw_1222_test.jpg的后缀为test
 @param postFix 后缀
 */
- (void)setSecGuardImagePostfix:(NSString *)postFix;

/**
 设置SDK 环境信息，SDK内部测试使用
 @param environmentType 见TaeSDKEnvironment
 */
- (void)setTaeSDKEnvironment:(TaeSDKEnvironment)environmentType;

/**
 设置网关host
 @param host 网关host
 */
- (void)setGwHost:(NSString *)host;

/**
 * 如果不调用，使用第三方账号授权功能时，如果没有openaccount账号绑定过此第三方账号，会创建一个openaccount账号（默认行为）
 * 设置后，使用三方授权功能时，如果没有openaccount账号绑定过此第三方账号, 会OAuth失败, 返回错误
 */
- (void)disableOAuthIfNotBind;

/**
 * 设置附加值，运行期间最多设置50个key
 * @param key   最大长度50，不能为空
 * @param value 最大长度200，不能为空
 */
- (void)addExtParamWithKey:(NSString *)key value:(NSString *)value;

- (TaeSDKEnvironment)getTaeSDKCurrentEnvironment;

#pragma mark - init
- (void)disableInitMemberSDK:(BOOL)disableInitMemberSDK;
- (void)disableInitUT:(BOOL)disableInitUT;
- (void)disableInitMtop:(BOOL)disableInitMtop;
- (void)disableInitSecurityGuard:(BOOL)disableInitSecurityGuard;

/** 重置数据 ，SDK内部测试使用*/
+ (void)reset;

- (void)demoteHttps;
@end

