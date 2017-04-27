//
//  AppDelegate.swift
//  Spinner
//
//  Created by Marcus Eckert on 10.05.2016.
//  Copyright © 2016 Marcus Eckert AS. All rights reserved.
//

import UIKit
import Squall

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate {

    var window: UIWindow?

    func applicationDidFinishLaunching(_ application: UIApplication) {
        Squall.setLicenseKey("LICENSE-KEY")
        
        print("Don't forget to set your Squall license key in the app delegate!")

    }

}

