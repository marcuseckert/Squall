//
//  ViewController.swift
//  Spinner
//
//  Created by Marcus Eckert on 10.05.2016.
//  Copyright © 2016 Marcus Eckert AS. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        
        self.view.backgroundColor = UIColor(red: 8.0/255.0, green: 17.0/255.0, blue: 28.0/255.0, alpha: 1.0)
        
        let spinner = Spinner(frame: CGRectZero)
        spinner.center = self.view.center
        self.view.addSubview(spinner)
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

