//
//  animation.swift
//  Rubberhose
//
//  Created by Marcus Eckert on 26.03.2017.
//  Copyright © 2017 Forge and Form GmbH. All rights reserved.
//

import Foundation
import QuartzCore

class Animation: NSObject {
    
    private var displayLink : CADisplayLink?
    private var targetValue = 0.0
    private var currentValue = 0.0
    private var convergenceThreshold = 0.001
    private var onAnimate : ((Double)->())!
    
    init(onAnimate : @escaping (Double)->()) {
        super.init()
        self.onAnimate = onAnimate
        
    }
    
    public func animate(from : Double, to : Double) {
        
        if from != to {
            currentValue = from
            targetValue = to
            play()
        }
        
    }
    
    internal func onDisplay(){
        currentValue += (targetValue - currentValue)*0.1
        if (fabs(targetValue - currentValue) <= self.convergenceThreshold) {
            currentValue = targetValue
        }
        self.onAnimate(currentValue)
        if currentValue == targetValue {
            pause()
        }
    }
    
    public func pause(){
        displayLink?.invalidate()
        displayLink = nil
    }
    
    public func play(){
        
        if displayLink == nil {
            displayLink = CADisplayLink(target: self, selector: #selector(Animation.onDisplay))
            displayLink!.add(to: .main, forMode: .commonModes)
        }
    }
    
}
