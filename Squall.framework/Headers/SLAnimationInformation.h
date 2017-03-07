//
//  SLAnimationInformation.h
//  Squall
//
//  Created by Marcus Eckert on 09.01.2016.
//  Copyright © 2016 Marcus Eckert AS. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>
#import "SLProperty.h"

/*!
 Contains all the information needed to construct a Squall or Core Animation.
 @see SLReader
 */
@interface SLAnimationInformation : NSObject

/**
 Returns true if the animation package contains a layer with the passed-in name.
 The name should match the one you set in After Effects.

 @param name Name of the layer you are looking for
 @return YES if it contains the layer in question
 */
-(BOOL)hasLayerWithName:(NSString*)name;

/*!
 Before building an animation you can replace the internal layers with already existing layers.
 The new layers will then receive all transformations and animations the internal layers would otherwise receive.
 Make sure the name of the layer you want to replace is unique.
 Transform values, position, anchor point and bounds are transferred immediately to the passed-in layer from the internal After Effects
 layer.
 @warning AE shape- and text layers cannot be replaced.
 
 @param name							Name of the layer in your AE comp to be replaced
 @param replacementLayer	Layer replacing the stand-in
 @param error						Optional error pointer or nil.
 */
-(void)replaceLayerWithName:(NSString*_Nonnull)name withLayer:(CALayer*_Nonnull)replacementLayer error:(NSError*_Nullable*_Nullable)error;

/*!
 Before building an animation you can go through a selection portion of the layer properties, read out and/or change their static values.
 A property's value range is oriented along that of the After Effects counterpart and maybe unexpected. Reading out a value before setting it
 can be helpful in these circumstances.
 @warning Properties which are time varying (with keyframes, expressions) will almost always disregard the static value of a property.
 
 @param propertyFilter	Block called for every adaptable property on every layer from your After Effects composition.
 */
-(void)adaptLayerProperties:(void (^_Nonnull)(SLProperty*_Nonnull property, NSString*_Nonnull layerName))propertyFilter;

@end
