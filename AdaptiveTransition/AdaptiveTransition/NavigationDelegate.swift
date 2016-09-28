//
//  NavigationDelegate.swift
//  SquallExamples
//
//  Created by Marcus Eckert on 12.04.2016.
//  Copyright © 2016 Marcus Eckert AS. All rights reserved.
//

import Foundation
import UIKit

class NavigationDelegate: NSObject, UINavigationControllerDelegate {
    
    var transitionManager = TransitionManager()
    
    override func awakeFromNib() {
        
    }
    
    func navigationController(_ navigationController: UINavigationController, animationControllerFor operation: UINavigationControllerOperation, from fromVC: UIViewController, to toVC: UIViewController) -> UIViewControllerAnimatedTransitioning? {
        return self.transitionManager
    }
    
}
