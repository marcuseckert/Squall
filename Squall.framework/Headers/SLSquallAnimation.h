//
//  SLSquallAnimation.h
//  Squall
//
//  Created by Marcus Eckert on 21.02.2016.
//  Copyright © 2016 Marcus Eckert AS. All rights reserved.
//

#import "SLAnimation.h"


/*!
 SLSquallAnimation is backed by a CADisplayLink and updates the animation whenever
 the display refreshes.
 
 This type of animation will be the most faithful to what you are seeing in After Effects.
 
 All of the updates occur on the main thread. SLSquallAnimations are therefore more susceptible
 to stalls from heavy CPU load than <SLCoreAnimation>.
 
 
    SLSquallAnimation* animation = [SLSquallAnimation animationFromBundle:@"myAnimation.sqa"];
    [animation play];
    [self.layer addSublayer:animation];
 
 <!-- -->
 
    SWIFT
    let animation = SLCoreAnimation(fromBundle: "myAnimation.sqa")
    animation.play()
    self.view.layer.addSublayer(animation!);

 
 @performance Do not use in highly constrained performance situations.
 */
@interface SLSquallAnimation : SLAnimation

/*!
 Convenience method to initialize a SLSquallAnimation with a .sqa file contained
 in your main app bundle.
 
 @param fileName	.sqa file name of the animation to build
 @param error		Optional pointer to a NSError
 
 @return SLSquallAnimation or nil on error
 */
+(SLSquallAnimation* _Nullable)animationFromBundle:(NSString*_Nonnull)fileName error:(NSError*_Nullable*_Nullable)error;

/*!
 Convenience method to initialize a SLSquallAnimation with a .sqa file at the passed-in path.
 
 @param path	Path to the .sqa file
 @param error	Optional pointer to a NSError
 
 @return SLSquallAnimation or nil on error
 */
+(SLSquallAnimation* _Nullable)animationFromPath:(NSString* _Nonnull)path error:(NSError*_Nonnull*_Nonnull)error;

/*!
 Convenience method to initialize an SLSquallAnimation with an animation file contained
 in your main app bundle.
 
 @param fileName	.sqa file name of the animation to build
 
 @return SLSquallAnimation or nil on error
 */
+(SLSquallAnimation* _Nullable)animationFromBundle:(NSString*_Nonnull)fileName;
/*!
 This method allows you to have an existing layer in your app inherit the 2D (!) transform
 transformations (position, scale, rotation, anchor point) from a layer in your AE
 animation.
 It works exactly like the parenting behavior in After Effects.
 Place your app layer wherever you need it, add it to the layer hierarchy and then call this method to tie it to a specific AE layer. The app layer will now behave as if glued to this AE layer.
 @warning Do not modify the transform property on the app layer while the parent-child relationship.
 @warning Does not honor 3D transformations.
 is active.
 @see removeParentFromLayer:
 
 @param layerName	AE layer name of the parent layer. Make sure it is unique.
 @param layer			App layer to inherit the transformation of the AE layer. Must be part of the layer hierarchy.
 @param error			Optional pointer to a NSError
 */
-(void)parentLayerWithName:(NSString *_Nonnull)layerName toLayer:(CALayer *_Nonnull)layer error:(NSError*_Nullable*_Nullable)error;

/*!
 Call this method to dissolve a parent-child relationship.
 
 @param layer	The app layer that is tied to an AE layer.
 */

-(void)removeParentFromLayer:(CALayer*_Nonnull)layer;

@end
