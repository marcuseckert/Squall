//
//  SLLivePreview.h
//  Squall
//
//  Created by Marcus Eckert on 21.02.2016.
//  Copyright © 2016 Marcus Eckert AS. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SLAnimation.h"

/*!
 Enum to determine how animations are resized to fit a another layer. Used in <SLLivePreview>.
 */
typedef NS_ENUM(NSUInteger, SLSizing) {
/*!
Layer gets resized to fit the bounds of the containing layer and retains its aspect ratio.
*/
SLSizingAspectFit,
/*!
Layer gets resized to fill the bounds of the containing layer and retains its aspect ratio.
*/
SLSizingAspectFill,
/*!
Layer does not get resize when added to a layer.
*/
SLSizingOriginal,
};

@class SLLivePreview;
/*!
 Delegate that gets messages when specific live preview events happen.
 */
@protocol SLLivePreviewDelegate <NSObject>

@optional
/*!
 Callback when Squall has established a connection and <ipAddress> returns the address of your iOS device.
 
 @param livePreview	Live preview instance
 */
-(void)squallEstablishedConnection:(SLLivePreview*)livePreview;
/*!
 Callback when Squall has established a connection with Bonjour and <bounjourName> returns the name of your iOS device.
 @warning Mac only
 
 @param livePreview	Live preview instance
 */
-(void)squallEstablishedBonjourRegistration:(SLLivePreview*)livePreview;
/*!
 Callback when Squall has received a new animation from After Effects. The property <runningAnimation> will allow you to access the animation.
 
 @param livePreview	Live preview instance
 */
-(void)squallReceivedAnimation:(SLLivePreview*)livePreview;
/*!
 Callback when Squall encountered an error.
 
 @param error	Live preview instance
 */
-(void)squallEncounteredError:(NSError*)error;
@end

/*!
 Allows you to preview animations from AE in your production app.
 
 
    //previewLayer is the layer incoming animation will be added to.
    //SLLivePreview should be an instance variable, property or otherwise retained.
    //This code would release the preview right away.
    SLLivePreview* preview = [[SLLivePreview alloc] initWithPreviewLayer:previewLayer];
 
<!-- -->
 
    SWIFT
    //previewLayer is the layer incoming animation will be added to.
    //SLLivePreview should be an instance variable, property or otherwise retained.
    //This code would release the preview right away.
    let preview = SLLivePreview(previewLayer: previewLayer)
 
 */
@interface SLLivePreview : NSObject
/*!
 Determines how incoming animations are resized to fit the preview layer.
 @see SLSizing
*/
@property (nonatomic, readwrite) SLSizing resizingBehavior;
/*!
 The animation currently running.
 Use the delegate to be notified when an animation has come in.
 
 @see SLAnimation
 @see SLLivePreviewDelegate
 */
@property (nonatomic, readonly) SLAnimation* runningAnimation;
/*!
 Device name that can be used in the Squall AE extension.
 Use the delegate to be notified when the bonjour name has become available.
 
 @warning Only valid on Mac OS X.
 @see SLLivePreviewDelegate
 */
@property (nonatomic, readonly) NSString* bonjourName;
/*!
 Device address to use in the Squall AE extension.
 Use the delegate to be notified when the ip address has become available.
 
 @warning Only valid when the SLLivePreview has made a connection with AE
 @see SLLivePreviewDelegate
 */
@property (nonatomic, readonly) NSString* ipAddress;
/*!
 Delegate notified when specific events occur.
 @see SLLivePreviewDelegate
 */
@property (nonatomic, weak) id<SLLivePreviewDelegate> delegate;
/*!
 
 Initializer to pass in the layer any incoming animation will be added to.
 @param previewLayer	Layer any incoming animations will be added to.
 
 @return SLLivePreview instance
 */
- (instancetype)initWithPreviewLayer:(CALayer*)previewLayer;
@end
