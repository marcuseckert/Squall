//
//  SLTextLayer.h
//  Squall
//
//  Created by Marcus Eckert on 20.02.2016.
//  Copyright © 2016 Marcus Eckert AS. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>
#import <UIKit/UIKit.h>
#import "SLLayer.h"

/*!
 The layer type used by Squall to render and layout text coming from After Effects.
 You can change attributes of the layer and have the animations adapt accordingly.
 
 Call <layoutText> after you have made changes to the text layer.
 
 
    NSError* error;
    SLSquallAnimation *animation = [SLSquallAnimation animationFromBundle:@"myAETextAnimation.sqa"
                                                      error:&error];
    if (!error) {
        SLTextLayer* testLayer = [animation getTextLayerWithName:@"myAETextLayer"];
        textLayer.text = @"new Text";
        [textLayer layoutText];
 
        //Prevents the animation to clip the text layer should it
        //now exceed the bounds of the main composition layer.
        animation.rootLayer.masksToBounds = false;
 
        [animation play];
        [self.view.layer addSublayer:animation];
    }
<!-- -->
    
    SWIFT
    let animation = SLSquallAnimation(fromBundle: "myAETextAnimation.sqa")
    let textLayer = animation?.getTextLayerWithName("myAETextLayer")
    textLayer?.text = "new Text";
    textLayer?.layoutText()
 
    //Prevents the animation to clip the text layer should it
    //now exceed the bounds of the main composition layer.
    animation?.rootLayer?.masksToBounds = false
    animation?.play()
    if animation != nil {
        self.view.layer.addSublayer(animation!)
    }
 
 */
@interface SLTextLayer : SLLayer
/*!
 String rendered by the layer
 */
@property (nonatomic, strong) NSString *text;
/*!
 Text color
 */
@property (nonatomic, strong) UIColor* textColor;
/*!
 Font name used by the text layer.
 */
@property (nonatomic, strong) NSString* font;
/*!
 Font size
 */
@property (nonatomic, readwrite) CGFloat fontSize;
/*!
 Tracking
 */
@property (nonatomic, readwrite) CGFloat tracking;
/*!
 Bounding boxes of all contained glyphs.
 */
@property (nonatomic, readonly) NSArray<NSValue*>* glyphBounds;
/*!
 Call this method after having made changes to any SLTextLayer properties.
 */
-(void)layoutText;

/*!
 Call to size and position the layer to fit the label.
 Resizes the label to fit the text line.
 For exact fitting use <sizeToFitGlyphBounds>
 */
-(void)sizeToFit;

/*!
 Call to size and position the layer to fit the bounds of all contained glyphs;
 */
-(void)sizeToFitGlyphBounds;
@end
