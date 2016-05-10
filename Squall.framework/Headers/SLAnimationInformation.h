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

/*!
 Before building an animation you can replace the internal layers with already existing layers.
 The new layers will then receive all transformations and animations the internal layers would otherwise receive.
 Make sure the name of the layer you want to replace is unique.
 @warning AE shape- and text layers cannot be replaced.
 
 @param name							Name of the layer in your AE comp to be replaced
 @param replacementLayer	Layer replacing the stand-in
 @param error						Optional error pointer or nil.
 */
-(void)replaceLayerWithName:(NSString*_Nonnull)name withLayer:(CALayer*_Nonnull)replacementLayer error:(NSError*_Nullable*_Nullable)error;

/*!
 Before building an animation you can filter through the layer properties and determine if you want them to be evaluated or not. This can be especially useful when replacing animation layers with already existing ones.
 
 @param propertyFilter	Filter block called for every filterable property on every layer from your After Effects composition.
 */
-(void)filterLayerProperties:(BOOL (^_Nonnull)(SLProperty*_Nonnull property, NSString*_Nonnull layerName))propertyFilter;

@end
