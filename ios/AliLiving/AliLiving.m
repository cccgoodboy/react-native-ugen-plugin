//
//  AliLiving.m
//  AliLiving
//
//  Created by 初程程 on 2019/4/9.
//  Copyright © 2019年 初程程. All rights reserved.
//

#import "AliLiving.h"


@interface AliLiving()<RCTBridgeModule>
@end
@implementation AliLiving
RCT_EXPORT_MODULE(UgenAliLiving);
//初始化
- (dispatch_queue_t)methodQueue{
    return dispatch_get_main_queue();
}
- (instancetype)init
{
    self = [super init];
    if (self) {
        
    }
    return self;
}

@end
