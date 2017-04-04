//
//  expressionController.swift
//  Accelerometer
//
//  Created by Marcus Eckert on 20.09.2016.
//  Copyright © 2016 Marcus Eckert AS. All rights reserved.
//

import Foundation
import Squall
import CoreMotion



class ExpressionController: UIView  {
    
    private let motionManager = CMMotionManager()
    private var touchForceProperty : SLProperty?
    private var touchProperty : SLProperty?
    private var touchForceAnimation : Animation?
    
    //Whenever the touchForce value is being set, either by an actual touch or by our
    //animation, we propagate the value to the touchForceProperty we got when digging
    //through the expression controls attached to the "Squall Controls" null
    //
    //We update the animation on every change of the value.
    
    private var touchForce = 0.0 {
        didSet {
            touchForceProperty?.value = NSNumber.init(value: touchForce)
            updateAnimationifNecessary()
        }
    }
    
    public var animation : SLAnimation?
    
    override init(frame: CGRect) {
        super.init(frame: frame)
        
        //We add a touch recognizer to make the circle pannable
        let pan = UIPanGestureRecognizer(target: self, action: #selector(onPan(_:)))
        self.addGestureRecognizer(pan)
        
        //We use a simple animation class to animate the touch force value back to zero
        //whenever needed.
        touchForceAnimation = Animation(onAnimate: {[unowned self] value in
            self.touchForce = value
        })
        
    }
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    func onPan(_ pan : UIPanGestureRecognizer) {
        
        if self.animation != nil {
            
            //If the animation is scaled (such as by setting it to a frame with a size other than
            //its native comp size, we will need to convert the touch position to the appropriate
            //layer space.
            
            let location = pan.location(in: self)
            let touchPointInAnimation = self.animation!.rootLayer!.convert(location, from:self.layer)
            
            //Our touch property is a Point property and requires a CGPoint wrapped in a NSValue as input.
            //If you are unsure what sort of value is required you could just read out the value
            //of the SLProperty and set a breakpoint (or print it to the console)
            //Invalid input will throw an exception
            self.touchProperty?.value = NSValue(cgPoint: touchPointInAnimation)
            updateAnimationifNecessary()
        }
    }
    
    private func updateAnimationifNecessary(){
        //Updating an expression can be costly so we will only update the expression if
        //the animation is currently paused (or if you need the update this instant)
        //If the animation is running expressions are evaluated anyway.
        
        if self.animation != nil && self.animation!.isPaused() {
            self.animation?.evaluateExpressions()
        }
    }
    
    //We hook into the touches... methods, get the first touch in the set and conform
    //the touch force value to a value between zero and one by dividing it by its
    //highest possible value (.maximumPossibleForce)
    
    internal override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        touchForceAnimation?.pause()
        self.touchForce = Double(touches.first!.force/touches.first!.maximumPossibleForce)
    }
    
    internal override func touchesMoved(_ touches: Set<UITouch>, with event: UIEvent?) {
        self.touchForce = Double(touches.first!.force/touches.first!.maximumPossibleForce)
    }
    
    //When the touches have ended or are cancelled we use a simple animation class to 
    //animate the touch value back down to zero
    
    internal override func touchesCancelled(_ touches: Set<UITouch>, with event: UIEvent?) {
        touchForceAnimation?.animate(from: self.touchForce, to: 0)
    }
    
    internal override func touchesEnded(_ touches: Set<UITouch>, with event: UIEvent?) {
        touchForceAnimation?.animate(from: self.touchForce, to: 0)
    }

    //Expression controls in After Effects are often nested in several levels.
    //They can also contain properties that are not necessarily visible in the After Effects UI.
    //The structure in our comp looks as follows:
    //
    //Touch:
    //    Point:
    //    Compositing Options:
    //3D Touch Force:
    //    Slider:
    //    Compositing Options:
    //
    //We are getting the controls from the "Squall Controls" null passed-in and dig through
    //the hierarchy to find the properties we are looking for.
    
    func connectControlsFromProperties(properties : [SLProperty]) -> Void {
        for p in properties {
            
            switch p.name {
            case "Touch":
                for subProperty in p.subProperties {
                    if (subProperty.name == "Point") {
                        self.touchProperty = subProperty
                    }
                }
                break
            case "3D Touch Force":
                
                for subProperty in p.subProperties {
                    if (subProperty.name == "Slider") {
                        self.touchForceProperty = subProperty
                    }
                }
                break
            default:
                break
            }
        }
    }
}
