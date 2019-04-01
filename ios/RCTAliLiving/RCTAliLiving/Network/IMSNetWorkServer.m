//
//  IMSNetWorkServer.m
//  LoginDemo
//
//  Created by 初程程 on 2018/7/3.
//  Copyright © 2018年 Facebook. All rights reserved.
//

#import "IMSNetWorkServer.h"
#import <IMSAuthentication/IMSIoTAuthentication.h>
#import "WebSocketClient.h"
#import "IMSOpenAccount.h"
@implementation IMSNetWorkServer
+ (void)sendRequestWithPath:(NSString *)path
                    version:(NSString *)version
                     params:(id)params
                    handler:(void(^)(BOOL isSuccess,id response,NSString *requestId))handler{
  NSLog(@"【网络请求】：\n路径:%@\n参数：%@",path,params);
  IMSIoTRequestBuilder *builder = [[IMSIoTRequestBuilder alloc] initWithPath:path
               apiVersion:version                                                                      params:params];
  
  [IMSRequestClient asyncSendRequest:builder.build responseHandler:^(NSError * _Nullable error, IMSResponse * _Nullable response) {
    if (error) {
      [self fetchError:error response:response handler:handler];
    }else{
      [self fetchSuccess:response handler:handler];
    }
  }];
}
+ (void)fetchSuccess:(IMSResponse *)response
             handler:(void(^)(BOOL isSuccess,id response,NSString *requestId))handler{
  
  IMSRequest *request = response.request;
  if (response.code==200) {
    NSLog(@"【请求结果返回】%@",response.data);
     handler(YES,response.data,request.msgId);
  }else if (response.code==401){
//    [[IMSOpenAccount sharedInstance] logout];
//    [[WebSocketClient sharedInstance] stopListener];
//    UIViewController *con = (UIViewController *)[[UIApplication sharedApplication] keyWindow].rootViewController;
//    [[IMSOpenAccount sharedInstance] showLoginWithController:con success:^(NSDictionary  *response) {
//
//    } failure:^(NSError *error) {
//
//      NSLog(@"%@",error);
//    }];
    NSError *error = [NSError errorWithDomain:response.message code:response.code userInfo:nil];
    handler(NO,error,request.msgId);
    
  }else{
    NSError *error = [NSError errorWithDomain:response.message code:response.code userInfo:nil];
    
//    [AlertShow showAlertWithMessage:[NSString stringWithFormat:@"请求错误\n errorCode:%ld\n errorMessage:%@",(long)response.code,response.message]];
    
    handler(NO,error,request.msgId);
  }
}
+ (void)fetchError:(NSError *)error
           response:(IMSResponse *)response
           handler:(void(^)(BOOL isSuccess,id response,NSString *requestId))handler{
//  [AlertShow showAlertWithMessage:error.domain];
  IMSRequest *request = response.request;
  handler(NO,error,request.msgId);
}
+ (void)sendIotAuthRequestWithPath:(NSString *)path
                           version:(NSString *)version
                            params:(id)params
                           handler:(void(^)(BOOL isSuccess,id response,NSString *requestId))handler{
  NSLog(@"【网络请求】：\n路径:%@\n参数：%@",path,params);
  IMSIoTRequestBuilder *builder = [[IMSIoTRequestBuilder alloc] initWithPath:path
               apiVersion:version                                                                      params:params];
  
  [builder setAuthenticationType:IMSAuthenticationTypeIoT];
  
  [IMSRequestClient asyncSendRequest:builder.build responseHandler:^(NSError * _Nullable error, IMSResponse * _Nullable response) {
    if (error) {
      [self fetchError:error response:response handler:handler];
    }else{
      [self fetchSuccess:response handler:handler];
    }
  }];
}
@end
