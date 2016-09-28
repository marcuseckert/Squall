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



class ExpressionController: UIView {
    
    let motionManager = CMMotionManager()
    var accelerationProperty : SLProperty?
    var touchProperty : SLProperty?
    var accelerationX = 0.0
    var accelerationY = 0.0
    var accelerationZ = 0.0
    public var animation : SLAnimation?
    
    override init(frame: CGRect) {
        super.init(frame: frame)
        
        let pan = UIPanGestureRecognizer(target: self, action: #selector(onPan(_:)))
        self.addGestureRecognizer(pan)
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
        //If the animation is running expressions are invaluated anyway.
        //Also, we could call evaluateExpressions on the whole animation but since we
        //know which layer the expression is attached to we will just call it on this specific layer
        
        if self.animation != nil && self.animation!.isPaused() {
            self.animation?.getShapeLayer(withName: "shape")?.evaluateExpressions()
        }
    }
    
    private func startAccelerometer(){
        
        if motionManager.isAccelerometerAvailable {
            
            motionManager.startAccelerometerUpdates(to: OperationQueue.main, withHandler: {[unowned self] (data : CMAccelerometerData?, e : Error?) in
            
                if data != nil {
                    
                    //We are implementing a simple low-pass filter to reduce the noisiness of
                    //the accelerometer data.
                    //The higher the factor, the noisier the result.
                    let factor = 0.05;
                    
                    self.accelerationX = data!.acceleration.x * factor + self.accelerationX * (1.0-factor)
                    self.accelerationY = data!.acceleration.y * factor + self.accelerationY * (1.0-factor)
                    self.accelerationZ = data!.acceleration.z * factor + self.accelerationZ * (1.0-factor)
                    
                    
                    //Our acceleration property is a 3D point property and requires an array as input.
                    self.accelerationProperty?.value = [self.accelerationY,self.accelerationX, self.accelerationZ]
                    
                    self.updateAnimationifNecessary()
                }
            
           })
            
        }
        
    }
    
    //Expression controls in After Effects are often nested in several levels.
    //They can also contain properties that are not necessarily visible in the After Effects UI.
    //The structure in our comp looks as follows:
    //
    //Touch:
    //    Point:
    //    Compositing Options:
    //Accelerometer:
    //    3D-Point:
    //    Compositing Options:
    
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
            case "Accelerometer":
                
                for subProperty in p.subProperties {
                    if (subProperty.name == "3D Point") {
                        self.accelerationProperty = subProperty
                        startAccelerometer()
                    }
                }
                break
            default:
                break
            }
        }
    }
}
