//
//  IMSResponse.h
//  IMSApiClient
//
//  Created by 文季 on 2017/11/9.
//

#import <Foundation/Foundation.h>
#import <IMSApiClient/IMSRequest.h>

/**
 API 通道请求的响应对象
 */
@interface IMSResponse : NSObject

- (NSInteger)code;                          ///< 服务器返回的 code，其中 200 为成功，其他情况为失败
- (id _Nullable)data;                       ///< 服务器返回 json 的 data 字段
- (NSString * _Nullable)message;            ///< 服务器返回的错误原因详情，可用于开发排查问题
- (NSString * _Nullable)localizedMsg;       ///< 服务器返回的用户可读的错误信息

// 下面的方法仅用于 Debug 用途
- (IMSRequest * _Nonnull)request;           ///< 该响应对应的请求对象
- (id _Nullable)rawData;                    ///< 服务器应答的原始报文

@end
