//
//  AGContext.h
//  AdGearSDK
//
//  Created by Boulat on 2015-10-27.
//  Copyright © 2015 AdGear. All rights reserved.
//

@import Foundation;

@interface AGContext : NSObject

@property (nonatomic, strong, nonnull) NSURL *baseURL;
@property (nonatomic, strong, nullable) NSString *mobileAppId;
@property (nonatomic, strong, nullable) NSString *mobileAppChipKey;
@property (nonatomic, strong, nonnull, readonly) NSDateFormatter *dateFormatter;

+ (nonnull instancetype)sharedInstance;

- (void)callDownloadTracker:(nullable NSDictionary *)dict withCompletion:(nullable void(^)(BOOL success))block;

@end
