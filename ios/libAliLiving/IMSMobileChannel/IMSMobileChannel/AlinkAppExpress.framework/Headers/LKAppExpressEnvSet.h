//
//  LKAppExpressEnvSet.h
//  AlinkAppExpress
//
//  Created by ZhuYongli on 2017/11/7.
//  Copyright © 2017年 ZhuYongli. All rights reserved.
//

#import <Foundation/Foundation.h>
typedef NS_ENUM(NSInteger, LKAppExpressEnv) {
    LKAppExpressEnvDaily = 1,
    LKAppExpressEnvPrerelease = 2,
    LKAppExpressEnvRelease = 3,
};


@interface LKAppExpressEnvSet : NSObject
+(void) setRunEnv:(LKAppExpressEnv)env;
+(LKAppExpressEnv)getRunEnv;
@end
