//
//  ViewController.swift
//  Transition
//
//  Created by Marcus Eckert on 11.04.2016.
//  Copyright © 2016 Marcus Eckert AS. All rights reserved.
//

import UIKit

class FromViewController: UIViewController, UIViewControllerTransitioningDelegate {
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        self.view.backgroundColor = UIColor(red: 8.0/255.0, green: 17.0/255.0, blue: 28.0/255.0, alpha: 1.0)
        
        self.navigationController?.isNavigationBarHidden = true
        
        let newViewC = ToViewController(nibName: nil, bundle: nil)
        
        callBlockAfter({
            newViewC.view.frame = self.view.frame
            newViewC.modalPresentationStyle = .custom
            self.navigationController?.pushViewController(newViewC, animated: true)
            }, duration: 0.5)
        
        
    }
    override var prefersStatusBarHidden: Bool {
        get {
            return true
        }  
    }
    
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    
   
    
}

