//
//  AGAdRequest.h
//  AdGearSDK
//
//  Created by Boulat on 2015-10-29.
//  Copyright © 2015 AdGear. All rights reserved.
//

#import "AGAd.h"

#define ERROR_AD                    [NSError errorWithDomain:@"com.adgear.sdk.adrequest" code:0 userInfo:@{NSLocalizedDescriptionKey:@"Ad error"}]
#define ERROR_AD_SPOT_ID            [NSError errorWithDomain:@"com.adgear.sdk.adrequest" code:1 userInfo:@{NSLocalizedDescriptionKey:@"Could not request ad with spot id"}]
#define ERROR_AD_URL                [NSError errorWithDomain:@"com.adgear.sdk.adrequest" code:2 userInfo:@{NSLocalizedDescriptionKey:@"Could not request ad with url"}]
#define ERROR_AD_JSON_STRING        [NSError errorWithDomain:@"com.adgear.sdk.adrequest" code:3 userInfo:@{NSLocalizedDescriptionKey:@"Could not request ad with json string"}]
#define ERROR_AD_CACHE_KEY          [NSError errorWithDomain:@"com.adgear.sdk.adrequest" code:4 userInfo:@{NSLocalizedDescriptionKey:@"Could not request ad with cache key"}]
#define ERROR_AD_DATA               [NSError errorWithDomain:@"com.adgear.sdk.adrequest" code:5 userInfo:@{NSLocalizedDescriptionKey:@"Could not request ad with data"}]
#define ERROR_AD_DELETE_CACHE_KEY   [NSError errorWithDomain:@"com.adgear.sdk.adrequest" code:6 userInfo:@{NSLocalizedDescriptionKey:@"Could not delete ad with cache key"}]
#define ERROR_AD_PAYLOAD_URL        [NSError errorWithDomain:@"com.adgear.sdk.adrequest" code:7 userInfo:@{NSLocalizedDescriptionKey:@"Payload url error"}]
#define ERROR_AD_FETCH_PAYLOAD      [NSError errorWithDomain:@"com.adgear.sdk.adrequest" code:8 userInfo:@{NSLocalizedDescriptionKey:@"Fetch payload error"}]
#define ERROR_AD_LOCAL_FILE_URL     [NSError errorWithDomain:@"com.adgear.sdk.adrequest" code:9 userInfo:@{NSLocalizedDescriptionKey:@"Local file url error"}]

@import Foundation;
@import AdGearEventManager;

@interface AGAdRequest : NSObject

+ (nullable NSURL *)idempotentURLForSpotId:(nonnull NSString *)spotId andTargetingParameters:(nullable NSDictionary *)params;
+ (void)adWithSpotId:(nonnull NSString *)spotId targetingParameters:(nullable NSDictionary *)params andCompletion:(nonnull void (^)(AGAd * _Nullable ad, NSError * _Nullable error))handler;
+ (void)adWithURL:(nonnull NSURL *)url andCompletion:(nonnull void (^)(AGAd * _Nullable ad, NSError * _Nullable error))handler;
+ (void)adWithJsonString:(nonnull NSString *)jsonString andCompletion:(nonnull void (^)(AGAd * _Nullable ad, NSError * _Nullable error))handler;
+ (void)adWithCachedURL:(nonnull NSURL *)url andCompletion:(nonnull void (^)(AGAd * _Nullable ad, NSError * _Nullable error))handler;
+ (void)adWithCachedKey:(nonnull NSString *)key andCompletion:(nonnull void (^)(AGAd * _Nullable ad, NSError * _Nullable error))handler;
+ (void)adWithData:(nonnull NSData *)data andCompletion:(nonnull void (^)(AGAd * _Nullable ad, NSError * _Nullable error))handler;
+ (void)cacheAdWithURL:(nonnull NSURL *)url andCompletion:(nonnull void (^)(NSString * _Nullable key, NSError * _Nullable error))handler;
+ (void)keysForCachedAdsWithCompletion:(nonnull void (^)(NSArray * _Nullable keys))handler;
+ (void)deleteCachedAdWithKey:(nonnull NSString *)key andCompletion:(nullable void (^)(NSError * _Nullable error))handler;

@end
