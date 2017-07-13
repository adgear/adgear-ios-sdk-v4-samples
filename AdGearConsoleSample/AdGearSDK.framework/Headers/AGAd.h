//
//  AGAd.h
//  AdGearSDK
//
//  Created by Boulat on 2015-10-23.
//  Copyright © 2015 AdGear. All rights reserved.
//

@import UIKit;

typedef NS_ENUM(NSInteger, AGAdType) {
    AGAdTypeUnknown = 0,
    AGAdTypeImage = 1,
    AGAdTypeJavaScript = 2,
    AGAdTypeThirdParty = 3,
    AGAdTypeHTML5 = 4
};

typedef NS_ENUM(NSInteger, AGAdSource) {
    AGAdSourceUnknown = 0,
    AGAdSourceDelivery = 1,
    AGAdSourceBundle = 2,
    AGAdSourceBundlePreview = 3,
    AGAdSourceLocalCache = 4
};

@interface AGAd : NSObject

@property (nonatomic) AGAdType type;
@property (nonatomic) AGAdSource source;
@property (nonatomic, strong, nullable) NSDictionary *dict;
@property (nonatomic, strong, nullable) NSData *image;
@property (nonatomic, strong, nullable) NSString *html;
@property (nonatomic, strong, nullable) NSURL *localFileUrl;

@property (nonatomic, readonly) bool isValid;

- (nonnull instancetype)init;

- (void)registerImpressionWithCompletion:(nullable void(^)(BOOL success))block;
- (nullable NSURL *)adInteractionURLForKey:(nonnull NSString *)key;
- (nullable NSURL *)adClickURLForKey:(nonnull NSString *)key;
- (nullable NSURL *)adDeclaredClickURLForKey:(nonnull NSString *)key;

@end