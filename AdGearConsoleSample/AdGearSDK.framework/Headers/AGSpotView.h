//
//  AGSpotView.h
//  AdGearSDK
//
//  Created by Boulat on 2015-10-23.
//  Copyright © 2015 AdGear. All rights reserved.
//

#import "AGAd.h"

@import UIKit;
@import AdGearMRAIDWebView;

@protocol AGSpotViewDelegate;

@interface AGSpotView : UIView

@property (nonatomic, weak, readonly, nullable) UIButton *imageView;
@property (nonatomic, weak, readonly, nullable) AGMraidView *webView;
@property (nonatomic, strong, readonly, nullable) AGAd *ad;
@property (nonatomic, weak, nullable) id<AGSpotViewDelegate> delegate;

- (void)loadAd:(nonnull AGAd *)ad;
- (void)registerImpressionWithCompletion:(nullable void(^)(BOOL success))block;
- (void)registerImpression;

@end

@protocol AGSpotViewDelegate <NSObject>

@required

- (nonnull UIViewController*)spotViewPresentingViewController;

@optional

// Spot view loaded
- (void)spotViewWillLoad:(nonnull AGSpotView *)spotView;
- (void)spotViewDidLoad:(nonnull AGSpotView *)spotView;
- (void)spotViewFailedToLoad:(nonnull AGSpotView *)spotView;

// Register impression
- (void)spotViewDidCallRegregisterImpression:(nonnull AGSpotView *)spotView;
- (void)spotViewFailedToCallRegregisterImpression:(nonnull AGSpotView *)spotView;

// Register event
- (void)spotView:(nonnull AGSpotView *)spotView didCallRegisterEventWithName:(nullable NSString *)name andUrl:(nullable NSURL *)url;
- (void)spotView:(nonnull AGSpotView *)spotView failedToRegisterEventWithName:(nullable NSString *)name andUrl:(nullable NSURL *)url;

// Load URL
- (BOOL)spotView:(nonnull AGSpotView *)spotView shouldOpen:(nullable NSURL *)url navigationAction:(nullable WKNavigationAction *)navigationAction;
- (void)spotView:(nonnull AGSpotView *)spotView willOpen:(nullable NSURL *)url navigationAction:(nullable WKNavigationAction *)navigationAction;
- (void)spotView:(nonnull AGSpotView *)spotView didOpen:(nullable NSURL *)url navigationAction:(nullable WKNavigationAction *)navigationAction;
- (void)spotView:(nonnull AGSpotView *)spotView failedToOpen:(nullable NSURL *)url navigationAction:(nullable WKNavigationAction *)navigationAction;

// Open
- (BOOL)mraidView:(nonnull AGMraidView *)mraidView shouldOpen:(nullable NSURL *)url navigationAction:(nullable WKNavigationAction *)navigationAction;
- (void)mraidView:(nonnull AGMraidView *)mraidView willOpen:(nullable NSURL *)url navigationAction:(nullable WKNavigationAction *)navigationAction;
- (void)mraidView:(nonnull AGMraidView *)mraidView didOpen:(nullable NSURL *)url navigationAction:(nullable WKNavigationAction *)navigationAction;
- (void)mraidView:(nonnull AGMraidView *)mraidView failedToOpen:(nullable NSURL *)url navigationAction:(nullable WKNavigationAction *)navigationAction;

// Expand
- (BOOL)mraidView:(nonnull AGMraidView *)mraidView shouldExpandFromRect:(CGRect)fromRect toRect:(CGRect)toRect;
- (void)mraidView:(nonnull AGMraidView *)mraidView willExpandFromRect:(CGRect)fromRect toRect:(CGRect)toRect;
- (void)mraidView:(nonnull AGMraidView *)mraidView didExpandFromRect:(CGRect)fromRect toRect:(CGRect)toRect;

// Resize
- (BOOL)mraidView:(nonnull AGMraidView *)mraidView shouldResizeFromRect:(CGRect)fromRect toRect:(CGRect)toRect;
- (void)mraidView:(nonnull AGMraidView *)mraidView willResizeFromRect:(CGRect)fromRect toRect:(CGRect)toRect;
- (void)mraidView:(nonnull AGMraidView *)mraidView didResizeFromRect:(CGRect)fromRect toRect:(CGRect)toRect;

// Collapse
- (BOOL)mraidView:(nonnull AGMraidView *)mraidView shouldCollapseFromRect:(CGRect)fromRect toRect:(CGRect)toRect;
- (void)mraidView:(nonnull AGMraidView *)mraidView willCollapseFromRect:(CGRect)fromRect toRect:(CGRect)toRect;
- (void)mraidView:(nonnull AGMraidView *)mraidView didCollapseFromRect:(CGRect)fromRect toRect:(CGRect)toRect;

// Hide
- (BOOL)mraidViewShouldHide:(nonnull AGMraidView *)mraidView;
- (void)mraidViewWillHide:(nonnull AGMraidView *)mraidView;
- (void)mraidViewDidHide:(nonnull AGMraidView *)mraidView;

// Play video/audio
- (BOOL)mraidView:(nonnull AGMraidView *)mraidView shouldPlayVideoURL:(nullable NSURL *)url;
- (void)mraidView:(nonnull AGMraidView *)mraidView willPlayVideoURL:(nullable NSURL *)url;
- (void)mraidView:(nonnull AGMraidView *)mraidView didPlayVideoURL:(nullable NSURL *)url;
- (void)mraidView:(nonnull AGMraidView *)mraidView failedToPlayVideoURL:(nullable NSURL *)url;

// Store picture
- (BOOL)mraidView:(nonnull AGMraidView *)mraidView shouldStorePictureWithURL:(nullable NSURL *)url;
- (void)mraidView:(nonnull AGMraidView *)mraidView willStorePictureWithURL:(nullable NSURL *)url;
- (void)mraidView:(nonnull AGMraidView *)mraidView didStorePictureWithURL:(nullable NSURL *)url;
- (void)mraidView:(nonnull AGMraidView *)mraidView failedToStorePictureWithURL:(nullable NSURL *)url;
- (void)mraidView:(nonnull AGMraidView *)mraidView refusedToStorePictureWithURL:(nullable NSURL *)url;

// Create calendar event
- (BOOL)mraidView:(nonnull AGMraidView *)mraidView shouldCreateCalendarEvent:(nullable NSString *)event;
- (void)mraidView:(nonnull AGMraidView *)mraidView willCreateCalendarEvent:(nullable NSString *)event;
- (void)mraidView:(nonnull AGMraidView *)mraidView didCreateCalendarEvent:(nullable NSString *)event;
- (void)mraidView:(nonnull AGMraidView *)mraidView failedToCreateCalendarEvent:(nullable NSString *)event;
- (void)mraidView:(nonnull AGMraidView *)mraidView refusedToCreateCalendarEvent:(nullable NSString *)event;

// Activate sensor
- (BOOL)mraidView:(nonnull AGMraidView *)mraidView shouldActivateSensor:(nullable NSString *)sensor;
- (void)mraidView:(nonnull AGMraidView *)mraidView willActivateSensor:(nullable NSString *)sensor;
- (void)mraidView:(nonnull AGMraidView *)mraidView didActivateSensor:(nullable NSString *)sensor;
- (void)mraidView:(nonnull AGMraidView *)mraidView failedToActivateSensor:(nullable NSString *)sensor;
- (void)mraidView:(nonnull AGMraidView *)mraidView refusedToActivateSensor:(nullable NSString *)sensor;
- (void)mraidView:(nonnull AGMraidView *)mraidView willDeactivateSensor:(nullable NSString *)sensor;
- (void)mraidView:(nonnull AGMraidView *)mraidView didDeactivateSensor:(nullable NSString *)sensor;

// State change
- (void)mraidView:(nonnull AGMraidView *)mraidView didChangeState:(nullable NSString *)state;

// Ready
- (void)mraidViewDidCallReady:(nonnull AGMraidView *)mraidView;

// Viewable change
- (void)mraidView:(nonnull AGMraidView *)mraidView didChangeViewable:(BOOL)viewable;

@end