//
//  IMLThingBaseDefine.h
//  IMLThingCapability
//
//  Created by ZhuYongli on 2018/1/16.
//  Copyright © 2018年 ZhuYongli. All rights reserved.
//


#import <Foundation/Foundation.h>


typedef void (^ThingSdkBooleanResultBlockExtra)(BOOL succeeded, NSError * _Nullable error, id _Nullable extra1);
typedef void (^ThingSdkBooleanResultBlock)(BOOL succeeded, NSError * _Nullable error);
typedef void (^ThingSdkObjectResultBlock)(NSDictionary * _Nullable object, NSError * _Nullable error);
typedef void (^ThingSdkArrayResultBlock)(NSArray * _Nullable result, NSError * _Nullable error);
typedef void (^ThingSdkEmptyBlock)(void);
