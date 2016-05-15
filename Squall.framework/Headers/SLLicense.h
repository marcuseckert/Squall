//
//  SLLicense.h
//  Squall
//
//  Created by Marcus Eckert on 10.01.2016.
//  Copyright © 2016 Marcus Eckert AS. All rights reserved.
//

#import <Foundation/Foundation.h>
/*!
 Squall class taking care that everything is as it should be.
 */
@interface Squall : NSObject

/*!
 Set the license key before you use any of the Squall classes (e.g. the app delegate) to unlock the full functionality.
 
 @param license	Your (very long) license key
 */
+(void)setLicenseKey:(NSString*)license;

@end
