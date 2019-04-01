//
//  IMSAuthenticationDelegate.h
//  IMSApiClient
//
//  Created by 文季 on 2018/1/4.
//

#import <Foundation/Foundation.h>
#import <IMSApiCLient/IMSRequestPayload.h>

@class IMSResponse;
@class IMSRequestPayload;

/*
 API 通道请求认证委托，主要作用如下：
 1）可在请求发送前对 IoT 协议 payload 进行补全
 2）在请求的服务器响应回来后做一遍认证错误消除
 
 NOTE：该 Delegate 有可能被多线程访问，各接口需要保证线程安全
 */
@protocol IMSAuthenticationDelegate <NSObject>

@required

/*
 该事件在请求发送前触发，可在此对 IoT 协议 payload 进行补全，
 补全结果通过 `completionHandler` 异步回调，回调会有三个参数，这三个字段必选其一，成功则输入补全的 payload，失败分两种情况：
 1）需要模拟一个服务器认证错误响应 `IMSResponse` 对象进行返回，如，创建认证信息时账号未登录
 2）其他错误（如，网络错误），直接通过 `NSError` 返回
 @param request 原始 API 请求对象
 @param payload 请求 payload
 @param completionHandler 异步处理回调
 - *error*: 错误对象，如，网络错误
 - *mockResponse*: 模拟服务器认证错误响应对象，如，IoT 统一身份认证错误 401
 - *newPayload*: 待发送的 payload
 */
- (void)handleRequestBeforeSend:(IMSRequest * _Nonnull)request
                        payload:(IMSRequestPayload * _Nonnull)payload
                     completion:(void (^ _Nonnull)(NSError * _Nullable error,
                                                   IMSResponse *_Nullable mockResponse,
                                                   IMSRequestPayload * _Nullable newPayload))completionHandler;


/*
 该事件在服务器响应到达时触发，可在此处理鉴权相关错误
 比如：
 1）如果服务器返回认证错误，该回调可以重建请求，补全认证信息后重放请求，然后把重放后的服务器响应透传回调
 2）其他情况可以直接把服务器响应透传回调
 @param response 服务器响应对象
 @param completionHandler 异步事件处理回调，成功则输入 response，失败则输入 NSError 类型的错误，这两个字段必选其一
 - *error*: 错误对象，如，重放请求的错误
 - *response*: 当前服务器响应，或者重放的服务器响应
 */
- (void)handleResponse:(IMSResponse * _Nonnull)response
            completion:(void (^ _Nonnull)(NSError * _Nullable error, IMSResponse * _Nullable response))completionHandler;

@end
