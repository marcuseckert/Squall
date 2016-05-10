//
//  Tools.swift
//  AdaptiveTransition
//
//  Created by Marcus Eckert on 10.05.2016.
//  Copyright © 2016 Marcus Eckert AS. All rights reserved.
//

import Foundation

func callBlockAfter(block : ()->(), duration : Double) {
    let delayTime = dispatch_time(DISPATCH_TIME_NOW, Int64(duration * Double(NSEC_PER_SEC)))
    dispatch_after(delayTime, dispatch_get_main_queue(), { () -> Void in
        block()
    })
}