//
//  NSError+IMSThing.h
//  IMLThingCapability
//
//  Created by difeng.zyl on 2017/10/31.
//
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSString *const kIMSThingErrorDomain;

/**
 错误码定义 
 */
typedef NS_ENUM(NSInteger, IMSThingExportError) {
    IMSThingExportErrorSuccess = 0,                     ///< 业务成功
    
    IMSThingExportErrorUnknownError = 3201,             ///< 客户端内部错误
    IMSThingExportErrorInvokeNetError = 3101,           ///< 网络错误
    IMSThingExportErrorServerBusinessError = 3103,      ///< 业务错误
    IMSThingExportErrorParameterError = 3104,      ///< 参数错误
    IMSThingExportErrorLocalConnectError = 3105,  ///< 设备本地连接不上
};

/**
 * IMSThingExportError 业务错误：
 * domain总是kIMSThingErrorDomain，code对应IMSThingExportError，localizedDescription对应用户感知错误msg
 */
@interface NSError (IMSThing)

+(NSError*) buildInvokeNetError:(NSError*)rawError;

+(NSError*) buildBusinessError:(id)rawData;

+(NSError*) buildParameterError:(NSString*)message;

@end

NS_ASSUME_NONNULL_END
