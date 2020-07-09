//
//  ViewController.swift
//  myApp
//
//  Created by chents on 2020/6/28.
//  Copyright © 2020 chents. All rights reserved.
//

import Cocoa

class ViewController: NSViewController {
    let btn = NSButton.init(title:"", target:nil, action:nil)

    var recStatus: Bool = false;
    var thread: Thread?
    override func viewDidLoad() {
        super.viewDidLoad()

        //设置窗口大小
        self.view.setFrameSize(NSSize(width: 222, height: 222))
        
//        let btn = NSButton.init(title: "button",  target: nil, action: nil)
        btn.title = "hello"
        btn.frame = NSRect(x:222/2-40,y:222/2-15,width:80,height:30)
        btn.setButtonType(.pushOnPushOff)
        btn.bezelStyle = .rounded
        btn.target = self
        
        btn.action = #selector(myfunc)
        
        self.view.addSubview(btn)
        // Do any additional setup after loading the view.
    }
    
    @objc
    func myfunc(){
        print(" this is func!")
        self.recStatus = !self.recStatus;
        
        if recStatus {
            thread = Thread.init(target: self,
                                 selector: #selector(self.recAudio),
                                 object: nil)
            thread?.start()
            
            self.btn.title = "停止录制"
        }else{
            setStatus(0);
            self.btn.title = "开始录制"
        }
    }
    
    @objc func recAudio(){
        //print("start thread")
        rec_audio()
    }
    override var representedObject: Any? {
        didSet {
        // Update the view, if already loaded.
        }
    }


}

