//
//  SLShapeLayer.h
//  Squall
//
//  Created by Marcus Eckert on 27.03.2016.
//  Copyright © 2016 Marcus Eckert AS. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>
#import "SLShapePathLayer.h"
#import "SLLayer.h"

/*!
 One of the layer types used to represent a layer from After Effects in a built Squall- or Core Animation.
 Contained rectangles, ellipses and freeform paths are represented by <SLShapePathLayer>.
 */
@interface SLShapeLayer : SLLayer

/*!
 Returns all the paths contained in this shape layer with the specified name (as named in your AE composition).
 Freeform paths, rectangles and ellipses all resolve to path layers.
 Since AE does not enforce unique names it is possible that multiple path layers are returned.
 It is recommended to use unique names in your AE comp if you want to retrieve a specific layer.
 
 @param name	Name of the group containing the path in AE (do not use the name of the group that also contains stroke, fill etc.)
 
 @return Array with path layers representating a freeform path, rectangle or ellipse
 */
-(NSArray<SLShapePathLayer*>* _Nonnull)getPathLayersWithName:(NSString* _Nonnull)name;

@end
