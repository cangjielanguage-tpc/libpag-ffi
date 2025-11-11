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
    var controller: PAGImageViewController

    func build() {
        Column() {
            XComponent(id: this.controller.uniqueID(), `type`: XComponentType.TEXTURE, controller: controller)
                .width(100.percent)
                .height(100.percent)
        }.width(100.percent).height(100.percent)
    }

    protected func aboutToAppear(): Unit {
        this.controller.attachToView(this.controller.getImageView())
        if (imageViewControllerMap.contains(this.controller.getImageView())) {
            imageViewControllerMap[this.controller.getImageView()] = this.controller
        } else {
            imageViewControllerMap.add(this.controller.getImageView(), this.controller)
        }
    }

    protected func aboutToDisappear() {
        if (imageViewControllerMap.contains(this.controller.getImageView())) {
            imageViewControllerMap.remove(this.controller.getImageView())
        }
        this.controller.detachFromView();
        if (let Some(value) <- this.controller.getComposition()) {
            if (value.isRelease) {
                return
            }
            value.nativeRelease()
        }
    }
}
