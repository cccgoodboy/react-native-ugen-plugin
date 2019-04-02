//
//  IMSAccountUIProtocol.h
//  IMSAccount
//
//  Created by Hager Hu on 01/11/2017.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

/**
 * IMSAccountService的UI提供者必须实现IMSAccountUIProtocol协议
 */
@protocol IMSAccountUIProtocol <NSObject>

/**
 * 显示登录窗口
 * @param controller 调用登录页面的视图控制器
 * @param success 调用登录页面成功后的回调处理，返回会话信息
 * @param failure 调用登录页面失败时的回调处理，返回错误信息
 */
- (void)showLoginWithController:(UIViewController *)controller
                        success:(void (^)(NSDictionary *session))success
                        failure:(void (^)(NSError *error))failure;

@end
