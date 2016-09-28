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
    
    func transitionDuration(using transitionContext: UIViewControllerContextTransitioning?) -> TimeInterval {
        return 4.0
    }
    
    func animateTransition(using transitionContext: UIViewControllerContextTransitioning) {
        
        //retrieving the transitioning views
        let toView = transitionContext.view(forKey: UITransitionContextViewKey.to)
        let fromView = transitionContext.view(forKey: UITransitionContextViewKey.from)
        
        let animationInfo = try! SLReader().parseFile(fromBundle: "transition.sqa")
        
        
        //We go through the layer properties of each layer
        //and replace the internal static value with the ones of our passed-in layers.
        animationInfo.adaptLayerProperties{ (property, layer) in
            
            if (layer == "viewIn") {
                if (property.name == "Width") {
                    property.value = toView?.bounds.size.width
                }
                else if (property.name == "Height") {
                    property.value = toView?.bounds.size.height
                } else if (property.name == "AnchorPoint") {
                    //Note that the Anchor Point has three values and is expressed in points.
                    property.value = [toView!.bounds.size.width*0.5, toView!.bounds.size.height*0.5, 0]
                }
            } else if (layer == "viewOut") {
                if (property.name == "Width") {
                    property.value = fromView?.bounds.size.width
                }
                else if (property.name == "Height") {
                    property.value = fromView?.bounds.size.height
                } else if (property.name == "AnchorPoint") {
                    //Note that the Anchor Point has three values and is expressed in points.
                    property.value = [fromView!.bounds.size.width*0.5, fromView!.bounds.size.height*0.5, 0]
                } else if (property.name == "Color") {
                    property.value = fromView!.backgroundColor;
                }
            }
            
        }
        
        //Before building we replace our solids with the transitioning views.
        //Transform values of the internal After Effects layers are transferred immediately.
        //So the layer bounds, position, anchor etc. on the passed-in layer may look different after this call.
        animationInfo.replaceLayer(withName: "viewIn", with: toView!.layer, error: nil)
        animationInfo.replaceLayer(withName: "viewOut", with: fromView!.layer, error: nil)
        
        //Try also building a SLSquallAnimation
        let animation  = SLCoreAnimation()
        
        //building the animation sets all initial, non-animated values for the layers
        //adapt any static properties after this call
        animation.build(with: animationInfo)
        animation.rootLayer?.masksToBounds = false;
       
        //centering our main animation
        animation.position = CGPoint(x: UIScreen.main.bounds.size.width*0.5, y: UIScreen.main.bounds.size.height*0.5)
        
        transitionContext.containerView.layer.addSublayer(animation)
       
        animation.play()
        
        //We listen for the event firing once the animation has ended and then do our cleanup
        animation.onAnimationEvent = {[unowned animation] event in
            if event == .end {
                toView?.frame = UIScreen.main.bounds
                transitionContext.containerView.addSubview(toView!)
                
                //calling complete transition right after results in a bad access violation due to the change in layer hierarchy
                callBlockAfter({
                    animation.removeFromSuperlayer()
                    transitionContext.completeTransition(true)
                }, duration: 0.01)
            }
        }
    }

}
