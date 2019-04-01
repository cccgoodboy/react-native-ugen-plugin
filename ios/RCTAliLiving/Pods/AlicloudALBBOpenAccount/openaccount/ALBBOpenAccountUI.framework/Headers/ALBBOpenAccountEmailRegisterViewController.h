//
//  ALBBOpenAccountEmailRegisterViewController.h
//  ALBBOpenAccountUI
//
//  Created by yixiao on 16/6/30.
//  Copyright © 2016年 Alibaba. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ALBBOpenAccountBaseController.h"
#import "ALBBOpenAccountWrapperView.h"


@interface ALBBOpenAccountEmailRegisterViewController : ALBBOpenAccountBaseController


//预留的外挂引用
@property (nonatomic, strong) IBOutletCollection(NSObject)  NSArray *outletCollection;

@property (weak, nonatomic) IBOutlet NSLayoutConstraint *formHeight;

// wrapper
@property (weak, nonatomic) IBOutlet ALBBOpenAccountWrapperView *wrapperView;

// email
@property (weak, nonatomic) IBOutlet UILabel *emailLabel;
@property (weak, nonatomic) IBOutlet UITextField *emailField;

//smscode
@property (weak, nonatomic) IBOutlet UIButton *sendButton;

// password
@property (weak, nonatomic) IBOutlet UILabel *passwordLabel;
@property (weak, nonatomic) IBOutlet UITextField *passwordField;
@property (weak, nonatomic) IBOutlet UIButton *visibleButton;

// checkcode
@property (weak, nonatomic) IBOutlet UILabel *checkcodeLabel;
@property (weak, nonatomic) IBOutlet UIView *checkcodeView;
@property (weak, nonatomic) IBOutlet UITextField *checkcodeField;

@property (weak, nonatomic) IBOutlet UILabel *tipLabel;

// control
@property (weak, nonatomic) IBOutlet UIButton *submitButton;


@end
