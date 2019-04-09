//
//  IMSOpenAccount.h
//  IMSAccount
//
//  Created by Hager Hu on 01/11/2017.
//

#import <Foundation/Foundation.h>

#import <IMSAccount/IMSAccountUIProtocol.h>
#import <IMSAccount/IMSAccountProtocol.h>

@interface IMSOpenAccount : NSObject <IMSAccountProtocol, IMSAccountUIProtocol>
@property (nonatomic ,copy)void(^thirdLoginResult)(NSError *err,NSDictionary *session);
+ (instancetype)sharedInstance;
- (void)logout;
- (BOOL)isLogin;
- (void)thirdLoginWithAuthCode:(NSString *)code;
- (void)showLoginWithController:(UIViewController *)controller
                        success:(void (^)(NSDictionary *response))success
                        failure:(void (^)(NSError *error))failure;
- (void)updateAccountProfileWithNickName:(NSString *)nickName
                               avatarUrl:(NSString *)avatarUrl
                                  gender:(NSString *)gender
                                response:(void(^)(BOOL isSuccess,NSError *error))response;
- (NSDictionary *)getCurrentSession;
@end
