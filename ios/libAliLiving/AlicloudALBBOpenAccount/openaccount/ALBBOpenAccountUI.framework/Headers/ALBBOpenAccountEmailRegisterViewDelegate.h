//
//  ALBBOpenAccountEmailRegisterViewDelegate.h
//  ALBBOpenAccountUI
//
//  Created by yixiao on 16/7/8.
//  Copyright © 2016年 Alibaba. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "ALBBOpenAccountEmailRegisterViewController.h"


@protocol ALBBOpenAccountEmailRegisterViewDelegate <NSObject>

@optional

- (void)emailRegisterViewDidLoad:(ALBBOpenAccountEmailRegisterViewController *) viewController;


- (void)emailRegisterViewWillAppear:(ALBBOpenAccountEmailRegisterViewController *) viewController;
- (void)emailRegisterViewDidAppear:(ALBBOpenAccountEmailRegisterViewController *) viewController;

- (void)emailRegisterViewWillDisappear;

- (void)emailRegisterViewWillLayoutSubviews:(ALBBOpenAccountEmailRegisterViewController *) viewController;
- (void)emailRegisterViewDidLayoutSubviews:(ALBBOpenAccountEmailRegisterViewController *) viewController;


@end
