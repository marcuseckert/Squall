//
//  SLAnimation.h
//  Squall
//
//  Created by Marcus Eckert on 09.01.2016.
//  Copyright © 2016 Marcus Eckert AS. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UiKit.h>
#import "SLAnimationInformation.h"
#import "SLTextLayer.h"
#import "SLShapeLayer.h"
#import "SLShapePathLayer.h"

/*!
 Type of event fired during the playback of an animation.
 @warning Does not honor any external timing changes made to Core animations (e.g. using the <SLCoreAnimationBuildDelegate>);
 */
typedef NS_ENUM(NSUInteger, SLAnimationEvent) {
    /*!
     Fires when time equals 0.0.
     @warning Does not fire when first starting the animation because animations are initialized with time at 0.0.
     */
    SLAnimationEventStart,
    /*!
     Fires when time equals animationDuration.
     */
    SLAnimationEventEnd,
    /*!
     Fires everytime the animation updates.
     */
    SLAnimationEventUpdate,
    /*!
     Fires when the playback rate of the animation changes.
     */
    SLAnimationEventRateChange
};


/*!
 Controls playback behavior of an animation.
 @warning Does not honor any external timing changes made to Core animations (e.g. using the <SLCoreAnimationBuildDelegate>);
 */
typedef NS_ENUM(NSUInteger, SLPlaybackType) {
/*!
Plays the animation once. *Default*
*/
    SLPlaybackTypeOnce,
/*!
Jumps to the beginning when the animation ends.
*/
    SLPlaybackTypeLoop,
/*!
Flips the playback direction when the animation approaches end or start.
*/
    SLPlaybackTypePingPong,
};


/*!
 Animation type all animation inherit from.
 Offsers basic playback support.
 @warning Cannot be directly instantiated. Use a subclass instead.
 */
@interface SLAnimation : CALayer
/*!
 Enums to control the playback behavior.
 Default: <SLPlaybackTypeOnce>
 @see SLAnimation
 @see SLPlaybackType
 */
@property (nonatomic, readwrite) SLPlaybackType playbackType;

/**
 *  Determines the rate of playback of the animation.
 *  Default: 0.0
 */
@property (nonatomic, readwrite) CGFloat rate;

@property (nonatomic, readwrite) NSInteger currentFrame;

/*!
 Time of the animation. Clamped to 0 and animation duration.
 (0 and 1 in evaluation mode).
 */
@property (nonatomic, readwrite) NSTimeInterval time;


/*!
 Playback progression of the animation.
 Progress = <time>/<animationDuration>.
 */
@property (nonatomic, readwrite) CGFloat progress;


/*!
 Animation information used to build the animation.
 @see SLReader
 */
@property (nonatomic, readonly) SLAnimationInformation* _Nullable animationInformation;


/*!
 Playback duration of the animation.
 */
@property (nonatomic, readonly) NSTimeInterval animationDuration;


/*!
 The root layer of the animation. 
 Corresponds to the main composition layer of your parsed AE composition and will interhit
 its size.<br>
 *Default:*     rootLayer.masksToBounds = true
 */
@property (nonatomic, readonly) CALayer* _Nullable rootLayer;

/*!
 Block called on specific animation events.
 @see SLAnimationEvent
 */
@property (nonatomic, copy) void (^_Nullable onAnimationEvent)(SLAnimationEvent);

/*!
 Start playing the animation.
 */
-(void)play;


/*!
 Pause the animation.
 */
-(void)pause;


/*!
 Convenience method to test if the animation is currently paused.
 Equals <rate> == 0.0.
 @return BOOL
 */
-(BOOL)isPaused;


/*!
 Play the animation backwards from its current time.
 Equals <rate> = -1.0.
 */
-(void)playBackwards;


/*!
 Returns all the layers with a specific name in your AE composition.
 Since AE does not enforce unique names it is possible that multiple layers are returned.
 It is recommended to use unique names in your AE comp if you want to retrieve a specific layer.
 
 @param name	AE composition layer name
 
 @return Array containing all the layers matching the input name.
 */
-(NSArray<CALayer*>*_Nullable)getLayersWithName:(NSString* _Nonnull)name;


/*!
 Convenience method that returns the first text layer matching the passed-in name.
 Make sure the AE layer name is unique.
 
 @param name	AE composition layer name
 
 @return First text layer matching the passed-in name or nil.
 */
-(SLTextLayer*_Nullable)getTextLayerWithName:(NSString* _Nonnull)name;

/*!
 Convenience method that returns the first <SLShapeLayer> matching the passed-in name.
 Make sure the AE layer name is unique.
 
 @param name	AE composition layer name
 
 @return First shape layer matching the passed-in name or nil.
 */
-(SLShapeLayer*_Nullable)getShapeLayerWithName:(NSString* _Nonnull)name;

/*!
 Convenience method that returns the first <SLShapePathLayer> of any <SLShapeLayer> matching the passed-in name.
 Make sure the AE path name is unique.
 Alternatively you can also first search for the <SLShapePathLayer> and then use its getPathLayersWithName method to look for any contained path layers.
 
 @param name	Path name as used in AE
 
 @return First path layer matching the passed-in name or nil.
 */
-(SLShapePathLayer*_Nullable)getPathLayerWithName:(NSString* _Nonnull)name;

/*!
 Build an animation with an <SLAnimationInformation> object output by <SLReader>. It is usually easier to use one of the convencience methods to build an animation but this gives you the oportunity to tweak some settings before building the animation, e.g. adding an <SLCoreAnimationBuildDelegate>.
 
    SLReader *reader = [[SLReader alloc] init];
    NSError* error;
    SLAnimationInformation *animationInformation = [reader parseFileFromBundle:@"myAnimation.sqa" error:&error];
    if (!error) {
        SLSquallAnimation* animation = [[SLSquallAnimation alloc] init];
        [animation buildWithInformation:animationInformation];
        [self.layer addSublayer:animation];
        [animation play];
    } else {
        NSLog(@"error %@", error);
    }
 
<!-- -->
 
    SWIFT
    let reader = SLReader()
    var animationInformation : SLAnimationInformation?
    do {
        animationInformation = try reader.parseFileFromBundle("myAnimation.sqa")
    } catch {
        print("error \(error)")
    }
    if animationInformation != nil {
        let animation = SLSquallAnimation.init()
        animation.buildWithInformation(animationInfo)
        animation.play()
        self.layer.addSublayer(animation)
    }

 
 @param buildInformation	information used to build the animation
 @see SLSquallAnimation
 @see SLCoreAnimation
 @see SLCoreAnimationBuildDelegate
 */
-(void)buildWithInformation:(SLAnimationInformation*_Nonnull)buildInformation;
@end
