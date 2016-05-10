//
//  TransitionManager.swift
//  SquallExamples
//
//  Created by Marcus Eckert on 11.04.2016.
//  Copyright © 2016 Marcus Eckert AS. All rights reserved.
//

import UIKit
import Squall

class TransitionManager: NSObject, UIViewControllerAnimatedTransitioning {
    
    var currentAnimation : SLAnimation?
    
    func transitionDuration(transitionContext: UIViewControllerContextTransitioning?) -> NSTimeInterval {
        return 4.0
    }
    
    func animateTransition(transitionContext: UIViewControllerContextTransitioning) {
        
        //retrieving the transitioning views
        let toView = transitionContext.viewForKey(UITransitionContextToViewKey)
        let fromView = transitionContext.viewForKey(UITransitionContextFromViewKey)
        
        let animationInfo = try! SLReader().parseFileFromBundle("transition.sqa")
       
        //before building we replace our solids with the transitioning views
        animationInfo.replaceLayerWithName("viewIn", withLayer: toView!.layer, error: nil)
        animationInfo.replaceLayerWithName("viewOut", withLayer: fromView!.layer, error: nil)
        
        //we filter out properties we don't want applied to our swapped out layers
        //we could alternatively also just reset them after the animation is built
        animationInfo.filterLayerProperties { (p, n) -> Bool in
            if (n == "viewIn" || n == "viewOut") {
                if (p.name == "Color" || p.name == "Width" || p.name == "Height") {
                    return false;
                }
            }
            return true
        }
        
        //Try also building a SLSquallAnimation
        let animation  = SLSquallAnimation()
        
        //building the animation sets all initial, non-animated values for the layers
        //adapt any static properties after this call
        animation.buildWithInformation(animationInfo)
        animation.rootLayer?.masksToBounds = false;
       
        //getting the offset to the screen center
        let aeCompositionSize = animation.frame.size
        let aeCompositionMiddle = CGPointMake(aeCompositionSize.width*0.5, aeCompositionSize.height*0.5)
        
        let screenMiddle = CGPointMake(UIScreen.mainScreen().bounds.size.width*0.5, UIScreen.mainScreen().bounds.size.height*0.5)
        let differenceToScreenMiddle = CGPointMake(screenMiddle.x-aeCompositionMiddle.x, screenMiddle.y-aeCompositionMiddle.y);
        
        //centering our main animation
        animation.position = CGPointMake(animation.position.x+differenceToScreenMiddle.x,
                                               animation.position.y+differenceToScreenMiddle.y)
        
        //reversing this offset for our passed in layers since they are the correct size and fill the screen
        fromView?.layer.position = CGPointMake(fromView!.layer.position.x-differenceToScreenMiddle.x,
                                               fromView!.layer.position.y-differenceToScreenMiddle.y)
        
        toView?.layer.position = CGPointMake(toView!.layer.position.x-differenceToScreenMiddle.x,
                                             toView!.layer.position.y-differenceToScreenMiddle.y)
        
        transitionContext.containerView()?.layer.addSublayer(animation)
        
        animation.play()
        
        //We listen for the event firing once the animation has ended and then do our cleanup
        animation.onAnimationEvent = {[unowned animation] event in
            if event == .End {
                toView?.frame = UIScreen.mainScreen().bounds
                transitionContext.containerView()?.addSubview(toView!)
                
                //calling complete transition right after results in a bad access violation due to the change in layer hierarchy
                callBlockAfter({
                    animation.removeFromSuperlayer()
                    transitionContext.completeTransition(true)
                }, duration: 0.01)
            }
        }
    }

}
