//
//  ALBBOpenAccountSSOPluginServiceProtocol.h
//  ALBBOpenAccountSSOPluginAdapter
//
//  Created by yixiao on 16/10/13.
//  Copyright (c) 2016年 Alibaba. All rights reserved.
//



#import <Foundation/Foundation.h>

#if __has_include(<ALBBOpenAccountSDK/ALBBOpenAccountSDK.h>)
#import <ALBBOpenAccountSDK/ALBBOpenAccountSession.h>
#import <ALBBOpenAccountSDK/ALBBOpenAccountSDK.h>
#else
#import <ALBBOpenAccountCloud/ALBBOpenAccountSession.h>
#import <ALBBOpenAccountCloud/ALBBOpenAccountSDK.h>
#endif

#import <ALBBOpenAccountSSO/ALBBOpenAccountSSOLink.h>

@protocol SSODelegate <NSObject>
@optional

/**
 * 三方账号授权登录回调
 * @param error       error
 * @param session     openaccount会话
 */
- (void)openAccountOAuthError:(NSError *)error Session:(ALBBOpenAccountSession *)session;

/**
 * 绑定三方账号回调
 * @param error       error，登录态失效的error code=ALBBOpenAccountCodeSessionExpireError
 * @param session     openaccount会话
 * @param link        三方账号信息
 */
- (void)openAccountBindError:(NSError *)error Session:(ALBBOpenAccountSession *)session ThirdInfo:(ALBBOpenAccountSSOLink *)link;
@end

typedef NS_ENUM(NSInteger, OAAuthPlatformType) {
    OAAuthPlatformType_TaoBao   = 1,
    OAAuthPlatformType_WechatSession,
    OAAuthPlatformType_Sina,
    OAAuthPlatformType_QQ,
    OAAuthPlatformType_Alipay,
    OAAuthPlatformType_FaceBook = 13,
    OAAuthPlatformType_Google = 32,
    OAAuthPlatformType_Twitter = 33
};

/** 获取实例: ALBBService(ALBBOpenAccountSSOService) */
@protocol ALBBOpenAccountSSOService <NSObject>


/**
 * 初始化(微博，微信，QQ)
 * @param platform    平台类型
 * @param appKey      申请的appkey
 * @param appSecret   申请的appSecret
 * @param redirectURL 设置的redirectURL
 */
- (BOOL)setPlatform:(OAAuthPlatformType)platform
             appKey:(NSString *)appKey
          appSecret:(NSString *)appSecret
        redirectURL:(NSString *)redirectURL;

/**
 * 初始化(淘宝)
 */
- (void)setTaobaoTargetUrl:(NSString *)url;

/**
 * 初始化(支付宝)
 * @param appId     appid
 * @param pId       pid
 * @param signType  RSA(SHA256)->RSA2; RSA(SHA1)->RSA，不填默认为RSA
 * @param appScheme 回跳scheme
 */
- (void)setAlipayAppId:(NSString *)appId
                   pId:(NSString *)pId
              signType:(NSString *)signType
             appScheme:(NSString *)appScheme;


/**
 * 三方账号授权登录
 * @param sType                     平台类型
 * @param presentingController      当前VC
 * @param delegate                  回调代理
 */
- (void)oauthWithPlatForm:(OAAuthPlatformType)sType presentingVC:(UIViewController *)presentingController delegate:(id<SSODelegate>)delegate;

/**
 * application:openURL:options:回调处理
 * @return            openaccount是否处理
 */
- (BOOL)handleOpenUrl:(NSURL*) url application:(UIApplication *)app sourceApplication:(NSString *)sourceApplication annotation:(id)annotation;

/**
 * 三方自有账号授权登录
 * @param authcode    授权码
 * @param delegate    回调代理
 *
 */
- (void)oauthWithThirdParty:(NSString *)authcode
                   delegate:(id<SSODelegate>)delegate;

/**
 * 阿里云授权登录
 */
- (void)oauthWithAliyun:(NSString *)accesstoken tokenSec:(NSString *)tokenSec delegate:(id<SSODelegate>)delegate;
/**
 * 绑定三方账号（需要有openaccount登录态）
 * @param sType                     平台类型
 * @param presentingController      当前VC
 * @param delegate                  回调代理
 */
- (void)oaBindWithPlatForm:(OAAuthPlatformType)sType
              presentingVC:(UIViewController *)presentingController
                  delegate:(id<SSODelegate>)delegate;

/**
 * 获取当前openaccount绑定的三方账号信息（需要有openaccount登录态）
 * @param callback      回调,成功时返回所有绑定的三方账号信息accountLinks，失败时返回error，登录态失效的error code=ALBBOpenAccountCodeSessionExpireError
 */
- (void)getThirdBindInfoWithCallback:(void (^)(NSArray<ALBBOpenAccountSSOLink *> *accountLinks,NSError *error))callback;

/**
 * 允许oa账号可以绑定同一平台的多个账号标识（当前openaccount账号默认每个平台只能绑定一个）
 */
- (void)enableMultiBind;
@end
