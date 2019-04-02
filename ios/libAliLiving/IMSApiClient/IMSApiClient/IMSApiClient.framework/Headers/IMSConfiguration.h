//
//  IMSConfiguration.h
//  IMSApiClient
//
//  Created by 文季 on 2017/11/6.
//  Copyright © 2017年 Alibaba-Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 API 通道服务器环境
 */
typedef NS_ENUM(NSInteger, IMSServerEnviroment) {
    IMSServerDaily = 0,           ///< 日常，供内部调试使用，外部开发者只能用 IMSServerRelease
    IMSServerPreRelease = 1,      ///< 预发，供内部调试使用，外部开发者只能用 IMSServerRelease
    IMSServerRelease = 2,         ///< 线上
};

/**
 API 通道配置信息
 */
@interface IMSConfiguration : NSObject

/**
 安全图片的 authCode，不指定时默认为 "07e8"；
 该值必须和安全图片 yw_1222_xxx.jpg 的 xxx 部分一致
 */
@property (nonatomic, copy) NSString *authCode;

/**
 移动应用 appKey，该值自动从安全图片中读取
 */
@property (nonatomic, copy, readonly) NSString *appKey;

/**
 API 通道官方服务器域名
 */
@property (nonatomic, copy, readonly) NSString *host;

/**
 API 通道请求支持的语言，格式标准为：[language designator]-[region designator]，当前支持：en-US，zh-CN，未指定默认使用 zh-CN
 */
@property (nonatomic, copy) NSString *language;

/**
 API 通道服务器环境，不指定时默认为线上
 */
@property (nonatomic, assign, readonly) IMSServerEnviroment serverEnv;

/**
 初始化 API 通道配置信息
 @param host 指定 API 通道服务器域名
 @param serverEnv 指定 API 通道服务器环境
 */
+ (void)initWithHost:(NSString *)host serverEnv:(IMSServerEnviroment)serverEnv;

/**
 获取 API 通道配置信息单例，需要先调用方法 `initWithHost:serverEnv:` 进行初始化
 
 @return API 通道配置信息实例
 */
+ (instancetype)sharedInstance;

@end

NS_ASSUME_NONNULL_END
