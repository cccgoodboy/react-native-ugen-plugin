//
//  ALBBOpenAccountCountryCodeViewController.h
//  ALBBOpenAccountUI
//
//  Created by yixiao on 16/6/21.
//  Copyright © 2016年 Alipay. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ALBBOpenAccountBaseController.h"

@protocol ALBBOpenAccountPhonePrefixDelegate <NSObject>
@optional
-(void)updatePhonePrefix:(NSString *)phonePrefix;
@end

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
@interface ALBBOpenAccountCountryCodeViewController :
ALBBOpenAccountBaseController

@property (weak, nonatomic)id<ALBBOpenAccountPhonePrefixDelegate> delegate;

@property (weak, nonatomic) IBOutlet UITableView *countryCodeTableView;
@property (strong, nonatomic) IBOutlet UISearchDisplayController *searchDisplayController;
@property (strong, nonatomic) IBOutlet UISearchBar *searchBar;

@end

#pragma mark diagnostic pop
