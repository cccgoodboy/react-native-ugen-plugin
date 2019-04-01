//
//  BoneBridgePlugin.h
//  BoneKit
//
//  Created by dujin on 2017/11/6.
//  Copyright © 2017年 Alibaba. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

/**
 定义 JS 调用 Objc Bridge 的回调函数类型
 
 @param errorObj Objc 运行的错误信息
 @param result Objc 运行的结果
 */
typedef  void(^BoneBridgeCallbackHandler)(NSDictionary *errorObj, NSDictionary *result);

/**
 定义 Bridge 注册到 Bone 容器的宏
 
 @param js_name Bridge 注册到 Bone 容器的名字，保持和类名相同
 */
#define BONE_PLUGIN_EXPORT_MODULE(js_name) \
+ (NSString *)moduleName { return @#js_name; } \
+ (void)load { \
    Class class = NSClassFromString(@"BoneBridgeHub"); \
    SEL sharedSel = NSSelectorFromString(@"sharedHub"); \
    if ([class respondsToSelector:sharedSel]) { \
        NSMethodSignature *sharedSign = [class methodSignatureForSelector:sharedSel]; \
        if (sharedSign) { \
            NSInvocation *sharedInvocation = [NSInvocation invocationWithMethodSignature:sharedSign]; \
            [sharedInvocation setTarget:class]; \
            [sharedInvocation setSelector:sharedSel]; \
            [sharedInvocation invoke]; \
            __unsafe_unretained id sharedInstance = nil; \
            [sharedInvocation getReturnValue:&sharedInstance]; \
            if (sharedInstance) { \
                SEL registerSel = NSSelectorFromString(@"registerModuleNameWithClass:"); \
                NSMethodSignature *registerSign = [sharedInstance methodSignatureForSelector:registerSel]; \
                if (registerSign) { \
                    NSInvocation *registerInvocation = [NSInvocation invocationWithMethodSignature:registerSign]; \
                    [registerInvocation setTarget:sharedInstance]; \
                    [registerInvocation setSelector:registerSel]; \
                    Class classSelf = self; \
                    [registerInvocation setArgument:&classSelf atIndex:2]; \
                    [registerInvocation invoke]; \
                } \
            } \
        } \
    }\
}

/**
 @brief Bone 定义容器是否需要预初始化 Bridge 的宏
 @discusstion 预初始化会在生成 Bone 容器实例后直接生成该 Bridge 实例，否则会在 JS 调用该 Bridge 时才会生成实例
 @return YES表示需要预初始化
 */
#define BONE_PLUGIN_PREINIT() \
+ (BOOL)shouldPreinit { return YES; }

/**
 定义映射 Objc 的函数到 JS 端的宏

 @param js_method JS 端调用 Objc 的方法名
 @param method Objc 端定义的方法名
 */
#define BONE_PLUGIN_REMAP_METHOD(js_method, method) \
+ (NSString *)__BONE_REMAP__##js_method { return @#method; } \
- (void)method



@class BoneBridgeNative;

/**
 定义 Bone Bridge 需实现的协议
 */
@protocol BoneBridgePluginProtocal <NSObject>

@required

/**
 Objc 和 JS 之间的通讯 Bridge
 */
@property (nonatomic, weak, readonly) BoneBridgeNative *bridge;

/**
 插件的模块名，由 BONE_PLUGIN_EXPORT_MODULE 宏自动添加

 @return 模块名
 */
+ (NSString *)moduleName;

@end


/**
 获取运行显示 plugin 插件的 UIViewController

 @param plugin 实现 BoneBridgePluginProtocal 协议的插件
 @return 运行显示 plugin 插件的 UIViewController
 */
extern UIViewController * BoneBridgePluginCurrentController(id<BoneBridgePluginProtocal>plugin);


/**
 Objc 向 plugin 插件的 JS 端发送消息

 @param plugin 实现 BoneBridgePluginProtocal 协议的插件
 @param eventName 事件名
 @param msg 用户自定义参数
 */
extern void BoneBridgePluginEmitBoneEvent(id<BoneBridgePluginProtocal>plugin, NSString *eventName, NSDictionary *msg);

























