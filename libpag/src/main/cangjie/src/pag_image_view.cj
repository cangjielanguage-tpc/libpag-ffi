/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package libpag4cj

internal import std.collection.ArrayList
import ohos.base.*
import ohos.component.*
import ohos.state_manage.*
import ohos.state_macro_manage.*

@Component
public class PAGImageView {
    //@Watch[watchViewController]
    //@Link
    var controller: PAGImageViewController

    func build() {
        Column() {
        // SURFACE TEXTURE
        //    XComponent(id:this.controller.uniqueID(),`type`:XComponentType.TEXTURE,controller:controller).width(100.percent).height(100.percent)
        }.width(100.percent).height(100.percent)
    }

    protected override func onPageHide(): Unit {}

    protected override func onPageShow(): Unit {
        this.controller.update()
    }

    protected override func aboutToAppear(): Unit {
        this.controller.attachToView(this)
    }

    protected override func aboutToDisappear(): Unit {
        this.controller.detachFromView()
    }
}
