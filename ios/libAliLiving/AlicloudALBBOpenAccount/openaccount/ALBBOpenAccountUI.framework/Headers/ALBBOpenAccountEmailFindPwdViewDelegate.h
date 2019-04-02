//
//  ALBBOpenAccountEmailFindPwdViewDelegate.h
//  ALBBOpenAccountUI
//
//  Created by yixiao on 2018/6/15.
//  Copyright © 2018年 Alipay. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ALBBOpenAccountEmailFindPwdViewController.h"

@protocol ALBBOpenAccountEmailFindPwdViewDelegate <NSObject>

@optional

- (void)emailFindPwdViewDidLoad:(ALBBOpenAccountEmailFindPwdViewController *) viewController;


- (void)emailFindPwdViewWillAppear:(ALBBOpenAccountEmailFindPwdViewController *) viewController;
- (void)emailFindPwdViewDidAppear:(ALBBOpenAccountEmailFindPwdViewController *) viewController;

- (void)emailFindPwdViewWillDisappear;
- (void)emailFindPwdViewDidDisappear;

- (void)emailFindPwdViewWillLayoutSubviews:(ALBBOpenAccountEmailFindPwdViewController *) viewController;
- (void)emailFindPwdViewDidLayoutSubviews:(ALBBOpenAccountEmailFindPwdViewController *) viewController;

@end
