//
//  SignProtocol.h
//  APIGateway
//
//  Created by Hager Hu on 30/10/2017.
//

#import <Foundation/Foundation.h>

@protocol SignProtocol <NSObject>

- (NSString *)signMethod;

- (NSString *)appKey;

- (NSString *)signWithData:(NSString *)data;

@end
