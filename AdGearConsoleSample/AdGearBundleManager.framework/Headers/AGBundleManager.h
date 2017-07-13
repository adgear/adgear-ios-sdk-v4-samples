//
//  AGBundleManager.h
//  AdGearBundleManager
//
//  Created by Boulat on 2015-11-03.
//  Copyright © 2015 AdGear. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface AGBundleManager : NSObject

+ (nonnull instancetype)sharedInstance;

- (void)processAdsBundle:(nonnull NSString *)srcPath forEditionName:(nonnull NSString *)editionName operationQueue:(nullable dispatch_queue_t)queue completion:(nullable void(^)(NSError * _Nullable error, NSDictionary * _Nullable bundleDict))block;
- (void)processPreviewBundle:(nonnull NSString *)srcPath operationQueue:(nullable dispatch_queue_t)queue completion:(nullable void(^)(NSError * _Nullable error))block;

- (void)fetchJsonStringForReplicaSpotName:(nonnull NSString*)spotName editionName:(nonnull NSString*)editionName operationQueue:(nullable dispatch_queue_t)queue completion:(nullable void (^)(NSString * _Nullable jsonString))block;
- (void)fetchJsonStringForPreviewAdUnitId:(nonnull NSString *)adUnitId operationQueue:(nullable dispatch_queue_t)queue completion:(nullable void (^)(NSString * _Nullable jsonString))block;

- (void)flushAllAdsWithOperationQueue:(nullable dispatch_queue_t)queue completion:(nullable void(^)())block;
- (void)flushAllPreviewAdsWithOperationQueue:(nullable dispatch_queue_t)queue completion:(nullable void(^)())block;
- (void)flushAdsForEditionName:(nonnull NSString *)editionName operationQueue:(nullable dispatch_queue_t)queue completion:(nullable void(^)())block;

@end
