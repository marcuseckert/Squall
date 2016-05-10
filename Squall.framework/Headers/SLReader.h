//
//  SLReader.h
//  Squall
//
//  Created by Marcus Eckert on 09.01.2016.
//  Copyright © 2016 Marcus Eckert AS. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "SLAnimationInformation.h"

/*!
 SLReader is used so parse .sqa files. It creates an instance of <SLAnimationInformation> which can then be used to create a Squall or Core Animation.
 */

@interface SLReader : NSObject  

/*!
 Convenience method to read a .sqa file from the main bundle.
 
 @param fileName	Name of .sqa file contained in the main app bundle
 @param error   Optional pointer to an error
 
 @return <SLAnimationInformation> instance which can then be used to create an animation.
 */
-(SLAnimationInformation*_Nullable)parseFileFromBundle:(NSString* _Nonnull)fileName error:(NSError*_Nullable*_Nullable)error;

/*!
 Reads a .sqa file from the passed-in path.
 
 @param path	path to .sqa file
 @param error   Optional pointer to an error
 
 @return <SLAnimationInformation> instance which can then be used to create an animation.
 */

-(SLAnimationInformation*_Nullable)parseFileAtPath:(NSString* _Nonnull)path error:(NSError*_Nullable*_Nullable)error;

@end
