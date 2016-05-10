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
 Represents animated and non-animated properties applied to each layer extracted from the AE composition.
 */
@interface SLProperty : NSObject
/*!
 The name identifying the property. Most often closely resembles the AE counterpart.
 */
@property (nonatomic, readonly) NSString* name;

@end
