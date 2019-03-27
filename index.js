'use strict';

import { NativeModules,NativeEventEmitter } from 'react-native';
const sdk = NativeModules.AliLiving;

class NativePlugin{
    static async login(){
        return sdk.login();
    }
}
export default NativePlugin;