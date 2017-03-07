//
//  SLProperty.h
//  Squall
//
//  Created by Marcus Eckert on 09.01.2016.
//  Copyright © 2016 Marcus Eckert AS. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>

/*!
 Represents animated and non-animated properties and effects applied to each layer extracted from the AE composition.
 */
@interface SLProperty : NSObject
/*!
 The name label from After Effects identifying the property.
 */
@property (nonatomic, readonly) NSString* name;

/*!
 The internal name identifying a property's nature. 
 Identifying properties via their match name can be useful since match names cannot be changed in After Effects.
 
 Note: The Squall match names closely resemble but are not identical to the ones used in After Effects.
 Typically the ADBE prefix and any white space is removed.
 */
@property (nonatomic, readonly) NSString* matchName;


/*!
 The static value associated with the property. 
 
 Some properties such as property groups, gradient and text properties cannot
 be assigned or return a value and will throw an exception on assignment.
 
 If you are unsure which type of value to assign try reading out the property and log the result.
 
 If the property is animated via keyframes any externally set value will be overwritten whenever the animation
 is evaluated.
 
 Expression control properties map to the following value types:
 
 3D Point Control   -> NSArray
 Angle Control      -> NSNumber
 Checkbox Control   -> NSNumber
 Color Control      -> UIColor
 Point Control      -> NSValue (with CGPoint)
 Slider Control     -> NSNumber
 
 */
@property (nonatomic, strong) id value;

/*!
 If the property is a property group this will return an array containing all subproperties.
 */
@property (nonatomic, readonly) NSArray<SLProperty*> *subProperties;

@end
