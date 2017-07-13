//
//  AGEnalytics.h
//  AdGearAnalytics
//
//  Created by Boulat on 2015-06-16.
//  Copyright (c) 2015 AdGear. All rights reserved.
//

#import <Foundation/Foundation.h>

extern NSString * _Nonnull const kAGEWillRequestUrlNotification;
extern NSString * _Nonnull const kAGEDidRequestUrlNotification;
extern NSString * _Nonnull const kAGEDidFailToRequestUrlNotification;
extern NSString * _Nonnull const kAGEDidRequeueFailedUrlNotification;
extern NSString * _Nonnull const kAGEDidRemoveFailedUrlNotification;

@interface AGEventManager : NSObject

+ (nonnull instancetype)sharedManager;

- (void)setTcpSessionMaxRequests:(NSInteger)val;
- (void)setTcpSessionMaxDuration:(NSInteger)val;
- (void)setTcpPauseSessionDuration:(NSInteger)val;

- (void)registerEvent:(nonnull NSString *)name params:(nullable NSDictionary *)params;
- (void)registerEvent:(nonnull NSString *)name params:(nullable NSDictionary *)params withCompletion:(nullable void(^)(BOOL success))block;

- (void)registerUrl:(nonnull NSURL *)url andPayload:(nullable NSString *)payload;
- (void)registerUrl:(nonnull NSURL *)url andPayload:(nullable NSString *)payload withCompletion:(nullable void(^)(BOOL success))block;
- (void)registerUrl:(nonnull NSURL *)url andPayload:(nullable NSString *)payload mocked:(BOOL)mocked withCompletion:(nullable void(^)(BOOL success))block;

- (void)deleteAllRequestsWithCompletion:(nullable void(^)(void))block;

@end
