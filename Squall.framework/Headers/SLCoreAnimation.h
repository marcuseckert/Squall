//
//  SLCoreAnimation.h
//  Squall
//
//  Created by Marcus Eckert on 21.02.2016.
//  Copyright © 2016 Marcus Eckert AS. All rights reserved.
//

#import <Squall/Squall.h>

/*!
 Delegate protocol to control how and if animations are added to a layer.
 
    SLReader *reader = [[SLReader alloc] init];
 
    NSError* error;
    [reader parseFileFromBundle:@"myAnimation.sqa" error:&error];
 
    if (!error) {
        SLCoreAnimation* animation = [[SLCoreAnimation alloc] init];
        animation.buildDelegate = self; //self needs to implement <SLCoreAnimationBuildDelegate>
        [animation buildWithInformation:reader.buildInformation];
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
        animation.delegate = self
        animation.buildWithInformation(animationInfo)
        animation.play()
        self.layer.addSublayer(animation)
    }
 
 
 */
@protocol SLCoreAnimationBuildDelegate <NSObject>
/*!
 Implement it to control when and if an animation should be added to a <SLCoreAnimation>.
 
 @param group	Animation group containing all animations that Squall wants to add the to the layer.
 @param layer			CALayer the animation will be added to
 @param name			Name of the AE composition layer
 
 @return Return a modified or unmodified animation or nil to prevent the animation group from being added.
 @warning Names do not necessarily directly correspond to the AVLayers from After Effects
 */
-(CAAnimationGroup*_Nullable)shouldAddAnimations:(CAAnimationGroup*_Nonnull)group toLayer:(CALayer*_Nonnull)layer withName:(NSString*_Nonnull)name;
@end

/*!
 SLCoreAnimation support is experimental and should generally be used for simple, performance-critical animations.
 In a lot of scenarios it might deviate from what you are seeing in After Effects.
 SLCoreAnimations are less susceptible to stalls on the main thread and are therefore more suitable for situations when the CPU load is high.
 */
@interface SLCoreAnimation : SLAnimation
/*!
 A delegate to control how and if animations are added to specific AE layers.
 */
@property (nonatomic, weak)  id<SLCoreAnimationBuildDelegate>_Nullable buildDelegate;

/*!
 Convenience method to initialize a SLCoreAnimation with an animation file contained
 in your main app bundle.
 
 @param fileName	.sqa file name of the animation to build
 @param error		Optional pointer to an NSError
 
 @return SLCoreAnimation or nil on error
 */
+(SLCoreAnimation* _Nullable)animationFromBundle:(NSString*_Nonnull)fileName  error:(NSError*_Nullable*_Nullable)error;

/*!
 Convenience method to initialize a SLCoreAnimation with an animation file contained
 in your main app bundle.
 
 @param fileName	.sqa file name of the animation to build
 
 @return SLCoreAnimation or nil on error.
 */
+(SLCoreAnimation*_Nullable)animationFromBundle:(NSString*_Nonnull)fileName;

/*!
 Convenience method to initialize a SLCoreAnimation with an animation file from the passed-in path.
 
 @param path	Path to an .sqa file
 @param error   Optional pointer to an NSError
 
 @return SLCoreAnimation or nil on error
 */
+(SLCoreAnimation*_Nullable)animationFromPath:(NSString*_Nonnull)path error:(NSError*_Nullable*_Nullable)error;
@end
