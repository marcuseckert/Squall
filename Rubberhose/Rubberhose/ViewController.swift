//
//  ViewController.swift
//  Rubberhose
//
//  Created by Marcus Eckert on 25.03.2017.
//  Copyright © 2017 Forge and Form GmbH. All rights reserved.
//

import UIKit
import Squall

//Rubberhose

//This project is a proof of concept and is meant to illustrate the power of dynamic expressions in Squall.
//
//The AE comp was setup with version 1 of the popular Rubberhose plugin which makes extensive use of expressions
//to create floppy limbs. But this first version of Rubberhose also uses a lot of code obfuscation techniques
//which make it very difficult and computationally expensive to properly resolve the attached expressions.
//Squall can resolve the controls accurately but it is not very fast. Future version of Rubberhose or Squall may 
//change this.
//
//The project shows a circle which is attached to two rubber hoses. You can move it around by panning the screen or 
//you can grow the circle by pressing down on the display (your iOS device needs to support force touch).
//This is achieved by connecting the touch input of the device to the expression controls in our After Effects
//composition and then Squall dynamically reevaluating the connected expressions.
//
//This mechanism is employed similarly in the Squall companion app.


class ViewController: UIViewController {

    var expressionController : ExpressionController!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        //We setup our animation with a file included in the app bundle and add it to
        //the view hierarchy
        let rubberHoseAnimation = SLSquallAnimation(fromBundle: "rubberHose.sqa")
        self.view.layer.addSublayer(rubberHoseAnimation!)
        
        //This class connect the input from a pan control and our touch force to the expression controls
        //in our AE comp
        self.expressionController = ExpressionController(frame: self.view.bounds)
        self.expressionController.animation = rubberHoseAnimation
        
        //We look for the null layer called "Squall Controls" in our AE composition
        //and pass its expression controls array to the expressionController for further processing
        let controlLayer = rubberHoseAnimation?.getLayersWithName("Squall Controls")?.first
        self.expressionController.connectControlsFromProperties(properties: (controlLayer?.expressionControls)!)
        
        //The expressionController is a UIView and has to be added to the hierarchy 
        //since it has to receive touch input
        self.view.addSubview(self.expressionController)
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

