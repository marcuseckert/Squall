//
//  Tools.swift
//  AdaptiveTransition
//
//  Created by Marcus Eckert on 10.05.2016.
//  Copyright © 2016 Marcus Eckert AS. All rights reserved.
//

import Foundation

func callBlockAfter(_ block : @escaping ()->(), duration : Double) {
    let delayTime = DispatchTime.now() + Double(Int64(duration * Double(NSEC_PER_SEC))) / Double(NSEC_PER_SEC)
    DispatchQueue.main.asyncAfter(deadline: delayTime, execute: { () -> Void in
        block()
    })
}
