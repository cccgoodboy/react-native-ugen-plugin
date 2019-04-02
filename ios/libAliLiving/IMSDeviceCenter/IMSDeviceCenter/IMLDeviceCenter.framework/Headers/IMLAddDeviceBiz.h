//
//  AddDeviceBiz.h
//  IMLDeviceCenter
//  
//  Created by ZhuYongli on 2017/7/6.
//  Copyright © 2017年 ZhuYongli. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IMLCandDeviceModel.h"
#import "LKErrorDefine.h"

#define kLkAddDevBiz IMLAddDeviceBiz.sharedInstance

/**
 * 准备配网指导码
 guideCode = 1,一键配网对应页面流转：e.g 直接进入输入密码页
 guideCode = 2,手机对应页面流转：e.g 引导开启热点页-》输入密码页
 guideCode = 3,设备热点页面流转: e.g  引导切换热点页-》输入密码页
 */
typedef NS_ENUM(NSInteger, LKPUserGuideCode) {
    LKPGuideCodeOnlyInputPwd = 1,   ///<一键配网对应页面流转：直接进入输入密码页
    LKPGuideCodeWithUserGuide = 2,  ///<手机热点对应页面流转：用户引导开启热点页-》输入密码页
    LKPGuideCodeWithUserGuideForSoftAp = 3 ///设备热点页面流转: e.g  引导切换热点页-》输入密码页
};

/**
 添加设备过程中状态流转码
 */
typedef NS_ENUM(NSInteger, LKAddState) {
    LKAddStatePrechecking = 0,          ///< 前期检查入参
    LKAddStateProvisionPreparing = 1,   ///<真正配网前的准备阶段，如等待用户输入 ssid + pwd
    LKAddStateProvisioning = 2,         ///<进入配网状态
    LKAddStateProvisioningNotice = 3,   ///<进入配网中的通知
    LKAddStateProvisionOver = 4,        ///<配网结束
};

/**
 配网过程关键步骤
 */
typedef NS_ENUM(NSInteger, LKProvisonStatus) {
    LKProvisonStatusRequestAuthorization,  ///<请求授权路由器或者已配网设备的配网
    LKProvisonStatusStartAhaAP,            ///<路由器开启 Aha 热点
    LKProvisonStatusJoinedAhaAP,           ///<设备连接热点
    LKProvisonStatusGetcipher,             ///<获得 AES KEY
    LKProvisonStatusSwitchAP,              ///<配网设备切换连接到WIFI热点
    LKProvisonStatusHotspotResetNetwotk,    ///<热点配网切回之前的wifi
    LKProvisonStatusResult              ///<配网结果
};

/**
 * UI层通知者，向UI层发送事件，同步当前添加设备流转状态
 */
@protocol ILKAddDeviceNotifier <NSObject>

/**
 配网预检查配网结果回调
 
 @param success 预检查是否成功
 @param err 预检查错误信息
 */
- (void)notifyPrecheck:(BOOL)success withError:(NSError *)err; ///<通知 UI 层, precheck 结果。可以没有

/**
 通知上层 UI：配网准备--如进入输入密码页面输入 ssid 和 password，密码输入后，调用 toggleProvision 开始配网
 
 @param guideCode 配网准备引导页
 */
- (void)notifyProvisionPrepare:(LKPUserGuideCode)guideCode;

/**
 通知上层UI：正在进行配网
 */
- (void)notifyProvisioning;


/**
 通知上层UI：提示用户关闭热点并切回以前的wifi
 */
@optional
- (void)notifyProvisioningNotice;


/**
 通知上层UI：热点配网相关回掉提示
 
 @param status 状态码 1=应该切换到设备热点； 2=已经切换到设备热点 3=已发送数据（dic里面会有"token"） 4=应该切换回路由器 5=已经切换回路由器
 */
@optional
- (void)notifyProvisioningNoticeForSoftAp:(int) status withInfo:(NSDictionary *) dic;


/**
 通知上层UI：配网过程各阶段的状态

 @param provisionStatus 配网状态（各个阶段）
 @param boolSuccess 该阶段性状态的值（成功或者失败）
 */
//- (void)notifyProvisionStatus:(LKProvisonStatus)provisionStatus boolSuccess:(BOOL)boolSuccess;

/**
 通知上层UI：配网完成结果回调
 
 @param candDeviceModel 配网结果设备信息返回：配网失败时为 nil
 @param provisionError 错误信息
 */
- (void)notifyProvisionResult:(IMLCandDeviceModel *)candDeviceModel withProvisionError:(NSError *)provisionError;

@end


/**
 设备配网统一入口
 */
@interface IMLAddDeviceBiz : NSObject

/**
 * 单例
 */
+ (instancetype)sharedInstance;

/**
 设置待添加的设备属性，在 startAddDevice 调用前传入相关信息,在同一时刻只能有一个待添加设备存在
 @param dev 设备相关信息
 */
- (LKDCErrCode)setDevice:(IMLCandDeviceModel *)dev;

/**
 * 开始添加设备流程，在 setDevice 后即可调用此 API
 @param notifier UI层通知者，向UI层同步当前流程的状态，参见 'ILKAddDeviceNotifier', SDK 会 weak 引用 notifier。
 开发者需要自己持有 notifier，避免被析构.
 */
- (void)startAddDevice:(id<ILKAddDeviceNotifier>)notifier;

/**
 传入配网所需参数，UI 层在收到 ILKAddDeviceNotifier::notifyProvisionPrepare 事件，引导用户输入
 wifi 密码后，调用此 API 正式进入配网流程.
 @param ssid 路由器 wifi 名称
 @param pwd  路由器 wifi 密码
 @param timeout 配网过程超时时间，以秒为单位，默认是60s
 */
- (void)toggleProvision:(NSString *)ssid pwd:(NSString *)pwd timeout:(int)timeout;

/**
 获取当前添加配网流程的状态
 @return 参见LKAddState
 */
- (LKAddState)getProcedureState;

/**
 切换配网模式，一般配网SDK会根据 IMLCandDeviceModel 传入的属性来选择一个默认的配网模式，但是在默认配网模式失败后，提供此 API 可以切换到路由器/广播/手机热点配网模式/设备热点配网模式
 所以该 API 的 provisionMode 入参只允许传入 ForceAliLinkTypeRouterAP\ForceAliLinkTypeBroadcast\ForceAliLinkTypeHotspot\ForceAliLinkTypeSoftap
 四个值
 @param linkType 参见 'ForceAliLinkType'
 */
- (void)setAliProvisionMode:(ForceAliLinkType)linkType;

/**
 能否获取当前网络（路由器）的 wifi 强度和频段（2.5G 或者 5G）
 */
- (BOOL)canGetWifiTypeOrFreq;

/**
 中止添加设备配网流程
 */
-(void)stopAddDevice;


@end

