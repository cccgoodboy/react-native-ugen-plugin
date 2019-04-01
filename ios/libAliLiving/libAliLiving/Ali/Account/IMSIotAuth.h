//
//  IMSIotAuth.h
//  LoginDemo
//
//  Created by 初程程 on 2018/7/3.
//  Copyright © 2018年 Facebook. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface IMSIotAuth : NSObject
+ (void)auth;
+ (void)reloadIotAuth;
+ (void)checkToken;
@end
