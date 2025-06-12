/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package ohos_app_cangjie_entry

internal import ohos.base.*
internal import ohos.component.*
internal import ohos.state_manage.*
internal import ohos.router.*
internal import ohos.resource_manager.*
internal import std.sync.*
internal import std.time.*
import ohos.state_macro_manage.*
import libpag4cj.*

@Entry
@Component
class EntryView {
    @State
    var controller: PAGViewController = PAGViewController()

    protected func aboutToAppear(): Unit {
        var path = '/data/storage/el1/bundle/entry/resources/resfile/resfile_test.pag'
        // 设置要播放的pag文件路径。目前resfile目录下的pag文件只能通过绝对路径设置'/data/storage/el1/bundle/entry/resources/resfile/'+pag文件名
        this.controller.setPath(path)
        // 设置动画播放次数。-1表示循环播放
        this.controller.setRepeatCount(-1)
        Timer.once(50 * Duration.millisecond) {
            =>
            // 显示动画首帧
            this.controller.update()
        }
    }
    func build() {
        Column(20) {
            Column {
                PAGView(controller: this.controller)
            }.width(90.percent).height(60.percent)
            Row(50) {
                Button('播放').width(100).height(50).onClick {
                    => this.controller.play()
                }
                Button('暂停').width(100).height(50).onClick {
                    => this.controller.pause()
                }
            }
            Button('核心功能')
                .width(90.percent)
                .height(50)
                .shape(ShapeType.Normal)
                .onClick {
                    =>
                    // 核心功能页面core.cj
                    Router.push(url: "Core")
                }
        }.width(100.percent).height(100.percent).padding(top: 20, left: 10, right: 10)
    }
}
