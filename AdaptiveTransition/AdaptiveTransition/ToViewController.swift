//
//  toViewController.swift
//  SquallExamples
//
//  Created by Marcus Eckert on 11.04.2016.
//  Copyright © 2016 Marcus Eckert AS. All rights reserved.
//

import Foundation
import UIKit

class ToViewController: UIViewController {
    override init(nibName nibNameOrNil: String?, bundle nibBundleOrNil: NSBundle?) {
        super.init(nibName: nibNameOrNil, bundle: nibBundleOrNil)
        
        //The glitching seems to have to due with the webview
        
        let url = NSURL(string:"http://www.zeit.de")
        let req = NSURLRequest(URL:url!)
        let w = UIWebView(frame: UIScreen.mainScreen().bounds)
        w.loadRequest(req)
        
        self.view.addSubview(w)
    }
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    override func prefersStatusBarHidden() -> Bool {
        return true
    }
    
    
}

