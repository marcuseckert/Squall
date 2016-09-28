//
//  SLPublicProtocols.h
//  Squall
//
//  Created by Marcus Eckert on 20.09.2016.
//  Copyright © 2016 Marcus Eckert. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <QuartzCore/QuartzCore.h>

@class SLProperty;

@protocol SLLayerProtocol <NSObject>

/*!
 Returns an array containing all associated expression control effects (i.e. 3D Point Control, Angle Control etc.)
 */
@property (nonatomic, readonly) NSArray<SLProperty*>* expressionControls;

/*!
 Call this method to force evaluate any attached expressions.
 By default Squall evaluates expressions whenever the time of the animation changes.
 
 You can also call evaluateExpressions on the SLAnimation containing the layer to force expression evaluation on all layers.
 */
-(void)evaluateExpressions;

@end

