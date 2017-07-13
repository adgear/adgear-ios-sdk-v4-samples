//
//  AGEContext.h
//  AdGearAnalytics
//
//  Created by Boulat on 2015-11-09.
//  Copyright © 2015 AdGear. All rights reserved.
//

#import <Foundation/Foundation.h>

#define kDefaultBaseUrl         @"http://d.adgear.com"
#define kDefaultErThreshold     20

@interface AGEContext : NSObject

@property (nonatomic, strong, nullable) NSString *publisherId;
@property (nonatomic, strong, nullable) NSString *publisherKey;
@property (nonatomic, strong, nonnull) NSURL *baseUrl;

@property (nonatomic, strong, nullable) NSString *userAgent;
@property (nonatomic, strong, nonnull) NSString *iosId;
@property BOOL optout;
@property NSInteger erThreshold;

@property (nonatomic, strong, nonnull) NSURLSession *urlSession;

+ (nonnull instancetype)sharedInstance;

@end
