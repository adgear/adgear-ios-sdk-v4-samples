//
//  AGMraidView.h
//  AdGearSDK
//
//  Created by Boulat on 2015-11-02.
//  Copyright © 2015 AdGear. All rights reserved.
//

@import WebKit;

typedef NS_ENUM(NSInteger, AGMraidState) {
    AGMraidStateLoading = 0,
    AGMraidStateDefault = 1,
    AGMraidStateExpanded = 2,
    AGMraidStateResized = 3,
    AGMraidStateHidden = 4
};

@protocol AGMraidViewDelegate;

@interface AGMraidView : WKWebView

@property (nonatomic, weak) id<AGMraidViewDelegate> delegate;
@property AGMraidState mraidState;

+ (void)mraidViewWithFrame:(CGRect)frame userJavaScript:(NSString *)userJavaScript userJavaScriptHandler:(NSString *)userJavaScript delegate:(id<AGMraidViewDelegate>)delegate andCompletion:(void(^)(AGMraidView *mraidView))handler;
- (void)mraidHideIfExpanded;
- (void)mraidUnhideIfExpanded;

@end

@protocol AGMraidViewDelegate <NSObject>

@required

- (UIViewController *)adPresentingViewController;

@optional

// Open
- (BOOL)mraidView:(AGMraidView *)mraidView shouldOpen:(NSURL *)url navigationAction:(WKNavigationAction *)navigationAction;
- (void)mraidView:(AGMraidView *)mraidView willOpen:(NSURL *)url navigationAction:(WKNavigationAction *)navigationAction;
- (void)mraidView:(AGMraidView *)mraidView didOpen:(NSURL *)url navigationAction:(WKNavigationAction *)navigationAction;
- (void)mraidView:(AGMraidView *)mraidView failedToOpen:(NSURL *)url navigationAction:(WKNavigationAction *)navigationAction;

// Expand
- (BOOL)mraidView:(AGMraidView *)mraidView shouldExpandFromRect:(CGRect)fromRect toRect:(CGRect)toRect;
- (void)mraidView:(AGMraidView *)mraidView willExpandFromRect:(CGRect)fromRect toRect:(CGRect)toRect;
- (void)mraidView:(AGMraidView *)mraidView didExpandFromRect:(CGRect)fromRect toRect:(CGRect)toRect;

// Resize
- (BOOL)mraidView:(AGMraidView *)mraidView shouldResizeFromRect:(CGRect)fromRect toRect:(CGRect)toRect;
- (void)mraidView:(AGMraidView *)mraidView willResizeFromRect:(CGRect)fromRect toRect:(CGRect)toRect;
- (void)mraidView:(AGMraidView *)mraidView didResizeFromRect:(CGRect)fromRect toRect:(CGRect)toRect;

// Collapse
- (BOOL)mraidView:(AGMraidView *)mraidView shouldCollapseFromRect:(CGRect)fromRect toRect:(CGRect)toRect;
- (void)mraidView:(AGMraidView *)mraidView willCollapseFromRect:(CGRect)fromRect toRect:(CGRect)toRect;
- (void)mraidView:(AGMraidView *)mraidView didCollapseFromRect:(CGRect)fromRect toRect:(CGRect)toRect;

// Hide
- (BOOL)mraidViewShouldHide:(AGMraidView *)mraidView;
- (void)mraidViewWillHide:(AGMraidView *)mraidView;
- (void)mraidViewDidHide:(AGMraidView *)mraidView;

// Play video/audio
- (BOOL)mraidView:(AGMraidView *)mraidView shouldPlayVideoURL:(NSURL *)url;
- (void)mraidView:(AGMraidView *)mraidView willPlayVideoURL:(NSURL *)url;
- (void)mraidView:(AGMraidView *)mraidView didPlayVideoURL:(NSURL *)url;
- (void)mraidView:(AGMraidView *)mraidView failedToPlayVideoURL:(NSURL *)url;

// Store picture
- (BOOL)mraidView:(AGMraidView *)mraidView shouldStorePictureWithURL:(NSURL *)url;
- (void)mraidView:(AGMraidView *)mraidView willStorePictureWithURL:(NSURL *)url;
- (void)mraidView:(AGMraidView *)mraidView didStorePictureWithURL:(NSURL *)url;
- (void)mraidView:(AGMraidView *)mraidView failedToStorePictureWithURL:(NSURL *)url;
- (void)mraidView:(AGMraidView *)mraidView refusedToStorePictureWithURL:(NSURL *)url;

// Create calendar event
- (BOOL)mraidView:(AGMraidView *)mraidView shouldCreateCalendarEvent:(NSString *)event;
- (void)mraidView:(AGMraidView *)mraidView willCreateCalendarEvent:(NSString *)event;
- (void)mraidView:(AGMraidView *)mraidView didCreateCalendarEvent:(NSString *)event;
- (void)mraidView:(AGMraidView *)mraidView failedToCreateCalendarEvent:(NSString *)event;
- (void)mraidView:(AGMraidView *)mraidView refusedToCreateCalendarEvent:(NSString *)event;

// Activate sensor
- (BOOL)mraidView:(AGMraidView *)mraidView shouldActivateSensor:(NSString *)sensor;
- (void)mraidView:(AGMraidView *)mraidView willActivateSensor:(NSString *)sensor;
- (void)mraidView:(AGMraidView *)mraidView didActivateSensor:(NSString *)sensor;
- (void)mraidView:(AGMraidView *)mraidView failedToActivateSensor:(NSString *)sensor;
- (void)mraidView:(AGMraidView *)mraidView refusedToActivateSensor:(NSString *)sensor;
- (void)mraidView:(AGMraidView *)mraidView willDeactivateSensor:(NSString *)sensor;
- (void)mraidView:(AGMraidView *)mraidView didDeactivateSensor:(NSString *)sensor;

// State change
- (void)mraidView:(AGMraidView *)mraidView didChangeState:(NSString *)state;

// Ready
- (void)mraidViewDidCallReady:(AGMraidView *)mraidView;

// Viewable change
- (void)mraidView:(AGMraidView *)mraidView didChangeViewable:(BOOL)viewable;

// Navigation
- (void)mraidView:(AGMraidView *)mraidView didStartNavigation:(WKNavigation *)navigation;
- (void)mraidView:(AGMraidView *)mraidView didFailNavigation:(WKNavigation *)navigation withError:(NSError *)error;
- (void)mraidView:(AGMraidView *)mraidView didFinishNavigation:(WKNavigation *)navigation;

- (void)mraidView:(AGMraidView *)mraidView didReceiveScriptMessage:(WKScriptMessage *)message;

@end
