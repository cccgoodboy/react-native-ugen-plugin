'use strict';

import { NativeModules,NativeEventEmitter } from 'react-native';
const sdk = NativeModules.AliLiving;

class AliLiving{
    //登录
    static async login(){
        return sdk.login();
    }
    //退出登录
    static async logout(){
        return sdk.logout();
    }
    //获取登录状态
    static async isLogin(){
        return sdk.isLogin();
    }
    //开始搜寻设备
    static startScanLocalDevice(){
        sdk.startScanLocalDevice();
    }
    //停止搜寻设备
    static stopScanLocalDevice(){
        sdk.stopScanLocalDevice();
    }
    //添加配网设备
    static startAddDevice(productKey){
        sdk.startAddDevice(productKey);
    }
    //中止配网流程
    static stopAddDevice(){
        sdk.stopAddDevice();
    }
    //添加配网的wifi和wifi密码
    static toggleProvision(wifiName,wifiPassword,timeout){
        sdk.toggleProvision(wifiName,wifiPassword,timeout);
    }
    //获取设备token
    static async getDeviceToken(pk,dn,timeout){
        return sdk.getDeviceToken(pk,dn,timeout);
    }
    //开启飞燕长连接
    static startAliSocketListener(){
        return sdk.startAliSocketListener();
    }
    //关闭飞燕长连接
    static stopAliSocketListener(){
        return sdk.stopAliSocketListener();
    }
    //获取长连接状态
    static getAliSocketListenerState(){
        return sdk.getAliSocketListenerState();
    }
    //获取账号信息
    static async getCurrentAccountMessage(){
        return sdk.getCurrentAccountMessage();
    }
    //发送客户端API
    static async send(path,params,version,iotAuth){
        return sdk.send(path,params,version,iotAuth);
    }
}
export default AliLiving;