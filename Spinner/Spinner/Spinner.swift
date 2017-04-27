//
//  Spinner.swift
//  SquallExamples
//
//  Created by Marcus Eckert on 05.04.2016.
//  Copyright © 2016 Marcus Eckert AS. All rights reserved.
//

import Foundation
import Darwin
import UIKit
import Squall

class Spinner: UIView, SLCoreAnimationBuildDelegate {
    
    var spinnerAnimation : SLCoreAnimation!
    
    override init(frame: CGRect) {
        super.init(frame: frame);
                
        let r = SLReader()
        var animationInfo : SLAnimationInformation?
        do {
            animationInfo = try r.parseFile(fromBundle:"spinner.sqa")
        } catch {
            print("error \(error)")
        }
        if animationInfo != nil {
            let a = SLCoreAnimation.init()
            a.buildDelegate = self
            a.build(with:animationInfo!)
            
            //We set the playback type to custom since we 
            //are controlling the timing ourselves and don't 
            //want Squall to stop the animation once it has played
            a.playbackType = SLPlaybackTypeCustom
            a.play()
            
            //We set the view's frame to the frame of the animation
            //The animation frame inherits its size from the parse AE (root) composition 
            self.frame = a.frame
            self.layer.addSublayer(a)
        }
    }
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    //This delegate method gets all the animations Squall wants to add to a layer.
    //Plus the layer Squall created and its name as it is in the AE comp.
    func shouldAddAnimations(_ group: CAAnimationGroup, to layer: CALayer, withName name:String) -> CAAnimationGroup? {
        switch name {
        case "Null":
                for ani in group.animations! as! [CAKeyframeAnimation] {
                    if ani.keyPath == "transform.rotation.z" {
                        //We set the repeat count to the hightest amount possible
                        ani.repeatCount = Float.greatestFiniteMagnitude
                    }
                }
            
        case "SpinnerPath":
                for ani in group.animations! as! [CAKeyframeAnimation] {
                    if  ani.keyPath == "strokeColor" || ani.keyPath == "strokeEnd" {
                        ani.repeatCount = Float.greatestFiniteMagnitude
                    }
                }
        case "SpinnerGroup":
                for ani in group.animations! as! [CAKeyframeAnimation] {
                    if ani.keyPath == "transform.rotation.z" {
                        ani.repeatCount = Float.greatestFiniteMagnitude
                    }
                }
        default:
            break
        }
        //We set the duration for all animation groups to the hightest amount possible
        group.duration = Double.greatestFiniteMagnitude

        //Printing the output before manipulating the animations is a good idea.
        
        //print("AE Layer: \(name)")
        //for ani : CAKeyframeAnimation in group.animations! as! [CAKeyframeAnimation] {
        //    print("\tanimating \(ani.keyPath!)")
        //}
        return group;
    }
    
}
