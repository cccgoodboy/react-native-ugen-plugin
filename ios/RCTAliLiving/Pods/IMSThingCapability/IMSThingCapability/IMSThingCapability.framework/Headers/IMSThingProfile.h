//
//  IMSThingShadow.h
//  IMLThingCapability
//
//  Created by ZhuYongli on 2018/1/31.
//  Copyright © 2018年 ZhuYongli. All rights reserved.
//

#import "IMSThingTslElement.h"


/**
 类：物的 Profile，封装物的 tsl 模型，包含物的属性、事件、服务等信息
 */
@interface IMSThingProfile : NSObject


/**
 获取物的 tsl 模型中，物的所有的属性描述，可以参见 `IMSThingTslProperty`

 @return 返回物的所有属性队列
 */
- (NSArray<IMSThingTslProperty *> *) allPropertiesOfModel;


/**
 获取物的 tsl 模型中，物的所有的服务描述，可以参见 `IMSThingTslService`

 @return 返回物的所有服务队列
 */
- (NSArray<IMSThingTslService *> *) allServicesOfModel;


/**
 获取物的 tsl 模型中，物的所有的事件描述，可以参见 `IMSThingTslEvent`

 @return  返回物的所有事件队列
 */
- (NSArray<IMSThingTslEvent *> *) allEventsOfModel;

@end
