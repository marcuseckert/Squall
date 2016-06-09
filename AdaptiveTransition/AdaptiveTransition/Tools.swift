//
//  Tools.swift
//  AdaptiveTransition
//
//  Created by Marcus Eckert on 10.05.2016.
//  Copyright © 2016 Marcus Eckert AS. All rights reserved.
//

import Foundation

public struct Queue {
    static func main(after seconds: Double, block: dispatch_block_t) {
        let delayTime = dispatch_time(DISPATCH_TIME_NOW, Int64(seconds * Double(NSEC_PER_SEC)))
        dispatch_after(delayTime, dispatch_get_main_queue(), block)
    }
}