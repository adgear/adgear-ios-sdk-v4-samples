//
//  ViewController.m
//  AdGearConsoleSample
//
//  Created by Boulat Oulmachev on 2017-07-12.
//  Copyright © 2017 Boulat Oulmachev. All rights reserved.
//

@import AdGearSDK;

#import "ViewController.h"

@interface ViewController () <AGSpotViewDelegate>
@property (nonatomic, strong) AGSpotView *spotView;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // Create spot view and add it as a subview
    self.spotView = [[AGSpotView alloc] initWithFrame:CGRectMake(0, 20, 336, 280)];
    [self.view addSubview:self.spotView];
    
    // Set spot view delegate
    self.spotView.delegate = self;
    
    // Request AGAd
    [AGAdRequest adWithSpotId:@"10746221" targetingParameters:nil andCompletion:^(AGAd * _Nullable ad, NSError * _Nullable error) {
        
        // Check for errors
        if (error != nil) {
            NSLog(@"Error: %@", error);
            return;
        }
        
        // Load the ad
        [self.spotView loadAd:ad];
        
        // Register impression
        [self.spotView registerImpression];
    }];
}

# pragma mark - AGSpotViewDelegate methods

// Add required AGSpotViewDelegate method that returns a reference to the presenting view controller
- (UIViewController *)spotViewPresentingViewController {
    return self;
}

@end
