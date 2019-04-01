//
//  ALBBOpenAccountEmailFindPwdViewController.h
//  ALBBOpenAccountUI
//
//  Created by yixiao on 2018/6/15.
//  Copyright © 2018年 Alipay. All rights reserved.
//

#import "ALBBOpenAccountBaseController.h"
#import "ALBBOpenAccountWrapperView.h"

@interface ALBBOpenAccountEmailFindPwdViewController : ALBBOpenAccountBaseController


//预留的外挂引用
@property (nonatomic, strong) IBOutletCollection(NSObject)  NSArray *outletCollection;

// wrapper
@property (weak, nonatomic) IBOutlet ALBBOpenAccountWrapperView *wrapperView;

// username
@property (weak, nonatomic) IBOutlet UILabel *usernameLabel;
@property (weak, nonatomic) IBOutlet UITextField *usernameField;
// smscode
@property (weak, nonatomic) IBOutlet UILabel *emailCodeLabel;
@property (weak, nonatomic) IBOutlet UITextField *emailCodeField;
@property (weak, nonatomic) IBOutlet UIButton *sendButton;

// control
@property (weak, nonatomic) IBOutlet UIButton *nextButton;


@end
