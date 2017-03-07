//
//  SLShapePathLayer.h
//  Squall
//
//  Created by Marcus Eckert on 20.02.2016.
//  Copyright © 2016 Marcus Eckert AS. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>
#import <UIKit/UIKit.h>

/*!
 Layer type used by Squall to display and animate shape layers.
 Future implementations might expose additional functionality.
 */
@interface SLShapePathLayer : CALayer

/*!
 Internal CAShapeLayer used to render the shape.
 */
@property (nonatomic, readonly) CAShapeLayer* shape;

@end
