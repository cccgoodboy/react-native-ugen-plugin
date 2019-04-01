//
//  LKErrorDefine.h
//  IMLDeviceCenter
//
//  Created by ZhuYongli on 2017/8/29.
//  Copyright © 2017年 ZhuYongli. All rights reserved.
//

#ifndef LKErrorDefine_h
#define LKErrorDefine_h

/**
 对外错误码定义
 */
typedef NS_ENUM(NSInteger, LKDCErrCode) {
    LKDCErrCodeNoError = 0,              ///<没有错误
    LKDCErrCodeSystemErr = 101600,          ///<系统错误
    LKDCErrCodeEnvironmentErr  = 101601,///< 环境错误
    LKDCErrCodeParamErr = 101602,           ///< 参数错误
    LKDCErrCodeUnknownErr = 101603,     ///< 未知错误
    LKDCErrCodeSdkErr = 101604,         ///<SDK内部错误
    LKDCErrCodeUserCancel = 101605,     ///< 用户取消配网
    LKDCErrCodeServerFail = 101606,     ///< 服务端请求失败
    LKDCErrCodeProvisionTimeout = 101607,       ///<配网超时
    LKDCErrCodeRedoAddWhileAdding = 101608, ///<添加设备正在进行，不允许重复操作
    LKDCErrCodeGetTokenTimeout = 101609,   ///<配网超时
    LKDCErrCodeGetCipherFail = 101610,   ///<配网超时
    LKDCErrCodeCheckInFail = 101611,   ///<配网超时
    
    
};

#endif /* LKErrorDefine_h */
