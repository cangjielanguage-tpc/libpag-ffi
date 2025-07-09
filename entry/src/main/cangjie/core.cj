/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package ohos_app_cangjie_entry

import ohos.state_macro_manage.*
import ohos.prompt_action.PromptAction
import std.random.*
import libpag4cj.*

@Entry
@Component
class Core {
    @State
    var controller: PAGViewController = PAGViewController()

    protected func aboutToAppear(): Unit {
        var path = '/data/storage/el1/bundle/entry/resources/resfile/resfile_test2.pag'
        // 设置要播放的pag文件路径。目前resfile目录下的pag文件只能通过绝对路径设置'/data/storage/el1/bundle/entry/resources/resfile/'+pag文件名
        this.controller.setPath(path)
        // 设置动画播放次数
        this.controller.setRepeatCount(1)
        Timer.once(50 * Duration.millisecond) {
            =>
            // 显示动画首帧
            this.controller.update()
        }
    }

    func showToast(message: String) {
        PromptAction.showToast(message: message, duration: 2000)
    }

    func build() {
        Column(20) {
            Row() {
                Image(@r(app.media.back))
                    .width(20)
                    .height(18)
                    .margin(top: 5, left: 5, right: 10)
                    .onClick({
                        event => Router.back()
                    })
                Text('核心功能').height(25).fontSize(23)
            }.width(90.percent)

            Column {
                PAGView(controller: this.controller)
            }.width(90.percent).height(50.percent)
            List() {
                ListItem() {
                    Column(5) {
                        CustomText(text: 'PAGView')
                        // play
                        Button('播放')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                => this.controller.play()
                            }

                        // pause
                        Button('暂停')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                => this.controller.pause()
                            }

                        // isPlaying
                        Button('是否播放')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                let value = this.controller.isPlaying()
                                if (value) {
                                    showToast("正在播放")
                                } else {
                                    showToast("未播放")
                                }
                            }

                        // setRepeatCount
                        Button('设置动画的重复次数')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                this.controller.setRepeatCount(2)
                                showToast("设置重复播放2次,点击播放按钮查看效果")
                            }

                        // repeatCount
                        Button('返回动画播放的总次数')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                let value = this.controller.repeatCount()
                                showToast("动画播放的总次数为${value}")
                            }

                        // setScaleMode(PAGScaleMode.None)
                        Button('缩放模式:None')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                this.controller.setScaleMode(PAGScaleMode.None)
                                // 刷新，测试效果用
                                this.controller.flush()
                            }

                        // setScaleMode(PAGScaleMode.Stretch)
                        Button('缩放模式:Stretch')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                this.controller.setScaleMode(PAGScaleMode.Stretch)
                                // 刷新，测试效果用
                                this.controller.flush()
                            }

                        // setScaleMode(PAGScaleMode.LetterBox)
                        Button('缩放模式:LetterBox')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                this.controller.setScaleMode(PAGScaleMode.LetterBox)
                                // 刷新，测试效果用
                                this.controller.flush()
                            }

                        // setScaleMode(PAGScaleMode.Zoom)
                        Button('缩放模式:Zoom')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                this.controller.setScaleMode(PAGScaleMode.Zoom)
                                // 刷新，测试效果用
                                this.controller.flush()
                            }

                        // scaleMode
                        Button('当前缩放模式')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                let mode = this.controller.scaleMode()
                                match (mode) {
                                    case 0 => showToast("当前缩放模式:None")
                                    case 1 => showToast("当前缩放模式:Stretch")
                                    case 2 => showToast("当前缩放模式:LetterBox")
                                    case 3 => showToast("当前缩放模式:Zoom")
                                    case _ => ()
                                }
                            }

                        // setMatrix
                        Button('设置矩阵变换')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                let values: Array<Float32> = [1.0, 0.5, 0.0, 0.0, 1.0, 0.0]
                                this.controller.setMatrix(values)
                                // 刷新，测试效果用
                                this.controller.flush()
                                showToast("查看是否纵向往右倾斜效果")
                            }

                        // matrix
                        Button('返回当前矩阵的副本')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                var msg = 'matrix:\n'
                                var matrix: Array<Float32> = this.controller.matrix()
                                for (i in 0..5) {
                                    msg += "matrix[${i}]:${matrix[i]} \n"
                                }
                                showToast(msg);
                            }

                        // currentFrame
                        Button('获取当前帧索引')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                let value = this.controller.currentFrame()
                                showToast("当前第${value}帧")
                            }

                        // setProgress
                        Button('设置播放的起始进度')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                this.controller.setProgress(0.5)
                                showToast("设置播放起始进度0.5")
                            }

                        // getProgress
                        Button('返回播放位置的当前进度')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                let value = this.controller.getProgress()
                                showToast("当前进度为${value}")
                            }

                        // cacheEnabled
                        Button('获取cacheEnabled属性的值')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                let value = this.controller.cacheEnabled()
                                showToast("当前值为${value}")
                            }

                        // setCacheEnabled
                        Button('设置cacheEnabled属性的值')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                this.controller.setCacheEnabled(false)
                                showToast("设置为false")
                            }

                        // setCacheScale
                        Button('设置cacheScale属性的值')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                this.controller.setCacheScale(0.1)
                                showToast("已设置为0.1,查看动画中静态图层是否比原来模糊")
                            }

                        // cacheScale
                        Button('获取cacheScale属性的值')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                let value = this.controller.cacheScale()
                                showToast("当前值为${value}")
                            }

                        // setMaxFrameRate
                        Button('设置最大帧率')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                this.controller.setMaxFrameRate(2.0)
                                showToast("不设置默认60,当前设置为2")
                                // 刷新，测试效果用
                                this.controller.flush()
                            }

                        // maxFrameRate
                        Button('获取最大帧率')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                let value = this.controller.maxFrameRate()
                                showToast("当前最大帧率为${value}")
                            }

                        // useDiskCache
                        Button('获取useDiskCache属性的值')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                let value = this.controller.useDiskCache()
                                showToast("值为${value}")
                            }

                        // setUseDiskCache
                        Button('设置useDiskCache属性的值')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                this.controller.setUseDiskCache(true)
                                showToast("设置为true")
                            }

                        // setPath
                        Button('从指定路径加载一个pag文件')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                var path = '/data/storage/el1/bundle/entry/resources/resfile/resfile_test.pag'
                                // 设置要播放的pag文件路径。目前resfile目录下的pag文件只能通过绝对路径设置'/data/storage/el1/bundle/entry/resources/resfile/'+pag文件名
                                this.controller.setPath(path)
                                // 刷新，测试效果用
                                this.controller.flush()
                            }

                        // getPath
                        Button('获取路径字符串')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                let value = this.controller.getPath()
                                showToast("由setPath()设置的pag文件的路径字符串为${value}")
                            }

                        // videoEnabled
                        Button('获取videoEnabled属性的值')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                let value = this.controller.videoEnabled()
                                showToast("值为${value}")
                            }

                        // setVideoEnabled
                        Button('设置videoEnabled属性的值')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                this.controller.setVideoEnabled(false)
                                showToast("设置为false,pag中视频部分将不渲染")
                            }

                        // duration()
                        Button('当前动画的总时长')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                let value = this.controller.duration()
                                showToast("动画的总时长为${value}微秒")
                            }

                        // flush
                        Button('刷新')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                let random: Random = Random()
                                let randomNum: Float32 = random.nextFloat32()
                                let values: Array<Float32> = [1.0, randomNum, 0.0, 0.0, 1.0, 0.0]
                                // 设置矩阵变换仅用于测试
                                this.controller.setMatrix(values)
                                let value = this.controller.flush()
                                if (value) {
                                    showToast("刷新成功")
                                } else {
                                    showToast("刷新失败")
                                }
                            }

                        // freeCache
                        Button('立即释放pag视图创建的缓存')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                // 测试方式
                                // hdc shell
                                // ps -ef|grep "应用包名"     找到应用pid(一般第二列)
                                // hidumper --mem 应用pid
                                // 看调用接口前后Total是否下降。实测有下降
                                this.controller.freeCache()
                            }

                        // getLayersUnderPoint
                        Button('返回位于指定点下方的图层数组')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                var array: Array<PAGLayer> = this.controller.getLayersUnderPoint(300.0, 300.0)
                                var msg = '返回位于指定点下方的图层数组长度:${array.size}\n'
                                for (i in 0..array.size) {
                                    msg += '${i} layerType:${array[i].layerType()} layerName:${array[i].layerName()}'
                                }
                                msg += '部分layerName显示空是正常的，底层接口获取到的就是空值'
                                showToast(msg)
                            }

                        CustomText(text: 'PAGFile')
                        // setDuration
                        Button('设置时长')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                var path = '/data/storage/el1/bundle/entry/resources/resfile/resfile_test2.pag'
                                var file = PAGFile.LoadFromPath(path)
                                if (file.isNone()) {
                                    showToast("pag文件不存在")
                                } else {
                                    // 单位微秒。这是设置2s
                                    file.getOrThrow().setDuration(2000000)
                                    if (let Some(composition) <- file) {
                                        this.controller.setComposition(composition)
                                    }
                                    showToast("设置动画时长为2s")
                                }
                            }

                        // loadFromPath
                        Button('加载pag文件')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                var path = '/data/storage/el1/bundle/entry/resources/resfile/resfile_test.pag'
                                var file = PAGFile.LoadFromPath(path)
                                if (let Some(composition) <- file) {
                                    this.controller.setComposition(composition)
                                } else {
                                    showToast("pag文件不存在")
                                }
                                // 刷新，测试效果用
                                this.controller.flush()
                            }

                        // duration
                        Button('持续时间')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                var path = '/data/storage/el1/bundle/entry/resources/resfile/resfile_test.pag'
                                var file = PAGFile.LoadFromPath(path)
                                if (file.isNone()) {
                                    showToast("pag文件不存在")
                                } else {
                                    let value = file.getOrThrow().duration()
                                    showToast("持续时间为${value}微秒")
                                }
                            }

                        // numImages
                        Button('可替换图像的数量')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                var path = '/data/storage/el1/bundle/entry/resources/resfile/resfile_test2.pag'
                                var file = PAGFile.LoadFromPath(path)
                                if (file.isNone()) {
                                    showToast("pag文件不存在")
                                } else {
                                    let value = file.getOrThrow().numImages()
                                    showToast("resfile/resfile_test2.pag可替换图像的数量为${value}")
                                }
                            }

                        // numTexts
                        Button('可编辑文本的数量')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                var path = '/data/storage/el1/bundle/entry/resources/resfile/resfile_test2.pag'
                                var file = PAGFile.LoadFromPath(path)
                                if (file.isNone()) {
                                    showToast("pag文件不存在")
                                } else {
                                    let value = file.getOrThrow().numTexts()
                                    showToast("resfile/resfile_test2.pag可编辑文本的数量为${value}")
                                }
                            }

                        // numVideos
                        Button('视频数量')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                var path = '/data/storage/el1/bundle/entry/resources/resfile/resfile_test2.pag'
                                var file = PAGFile.LoadFromPath(path)
                                if (file.isNone()) {
                                    showToast("pag文件不存在")
                                } else {
                                    let value = file.getOrThrow().numVideos()
                                    showToast("resfile/resfile_test2.pag动画中视频数量为${value}")
                                }
                            }

                        // path
                        Button('pag文件的路径字符串')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                var path = '/data/storage/el1/bundle/entry/resources/resfile/resfile_test2.pag'
                                var file = PAGFile.LoadFromPath(path)
                                if (file.isNone()) {
                                    showToast("pag文件不存在")
                                } else {
                                    let value = file.getOrThrow().path()
                                    showToast("pag文件的路径字符串:为${value}")
                                }
                            }

                        // MaxSupportedTagLevel
                        Button('最大标签等级')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                var value = PAGFile.MaxSupportedTagLevel()
                                showToast("当前SDK支持的最大标签等级为:${value}")
                            }

                        // getEditableIndices
                        Button('返回此PAG文件中可编辑图层的索引')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                var path = '/data/storage/el1/bundle/entry/resources/resfile/resfile_test2.pag'
                                var file = PAGFile.LoadFromPath(path)
                                if (file.isNone()) {
                                    showToast("pag文件不存在")
                                } else {
                                    // 3表示Text类型
                                    let layerType: Int32 = 3
                                    var array: Array<Int64> = file.getOrThrow().getEditableIndices(layerType)
                                    showToast("该动画中Text类型可编辑图层的索引为${array.toString()}")
                                }
                            }

                        // timeStretchMode
                        Button('返回当前动画在时长变化时的拉伸模式')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                var path = '/data/storage/el1/bundle/entry/resources/resfile/resfile_test.pag'
                                var file = PAGFile.LoadFromPath(path)
                                if (file.isNone()) {
                                    showToast("pag文件不存在")
                                } else {
                                    let mode = file.getOrThrow().timeStretchMode()
                                    match (mode) {
                                        case 0 => showToast("当前拉伸模式:None")
                                        case 1 => showToast("当前拉伸模式:Scale")
                                        case 2 => showToast("当前拉伸模式:Repeat")
                                        case 3 => showToast("当前拉伸模式:RepeatInverted")
                                        case _ => ()
                                    }
                                }
                            }

                        // setTimeStretchMode-None
                        Button('动画拉伸模式:None')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                var path = '/data/storage/el1/bundle/entry/resources/resfile/resfile_test2.pag'
                                var file = PAGFile.LoadFromPath(path)
                                if (file.isNone()) {
                                    showToast("pag文件不存在")
                                } else {
                                    // 设置动画拉伸模式:None 保持原速度，不够长就停在最后一帧
                                    file.getOrThrow().setTimeStretchMode(PAGTimeStretchMode.None)
                                    // 下面代码仅用于效果测试
                                    file.getOrThrow().setDuration(2000000) // 2s
                                    if (let Some(composition) <- file) {
                                        this.controller.setComposition(composition)
                                    }
                                    this.controller.setRepeatCount(1)
                                    this.controller.play()
                                    showToast("效果:保持原速度，不够长就停在最后一帧")
                                }
                            }

                        // setTimeStretchMode-Scale
                        Button('动画拉伸模式:Scale')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                var path = '/data/storage/el1/bundle/entry/resources/resfile/resfile_test2.pag'
                                var file = PAGFile.LoadFromPath(path)
                                if (file.isNone()) {
                                    showToast("pag文件不存在")
                                } else {
                                    // 设置动画拉伸模式:Scale 调整播放速度，使动画正好匹配目标时长
                                    file.getOrThrow().setTimeStretchMode(PAGTimeStretchMode.Scale)
                                    // 下面代码仅用于效果测试
                                    file.getOrThrow().setDuration(2000000) // 2s
                                    if (let Some(composition) <- file) {
                                        this.controller.setComposition(composition)
                                    }
                                    this.controller.setRepeatCount(1)
                                    this.controller.play()
                                    showToast("效果:调整播放速度，使动画正好匹配目标时长")
                                }
                            }

                        // setTimeStretchMode-Repeat
                        Button('设置动画拉伸模式:Repeat')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                var path = '/data/storage/el1/bundle/entry/resources/resfile/resfile_test2.pag'
                                var file = PAGFile.LoadFromPath(path)
                                if (file.isNone()) {
                                    showToast("pag文件不存在")
                                } else {
                                    // 设置动画拉伸模式:Repeat 保持原速度，不够就循环播放（默认方式）
                                    file.getOrThrow().setTimeStretchMode(PAGTimeStretchMode.Repeat)
                                    // 下面代码仅用于效果测试
                                    file.getOrThrow().setDuration(30000000) // 30s
                                    if (let Some(composition) <- file) {
                                        this.controller.setComposition(composition)
                                    }
                                    this.controller.setRepeatCount(1)
                                    this.controller.play()
                                    showToast("效果:保持原速度，不够就来回循环播放")
                                }
                            }

                        // setTimeStretchMode-RepeatInverted
                        Button('设置动画拉伸模式:RepeatInverted')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                var path = '/data/storage/el1/bundle/entry/resources/resfile/resfile_test2.pag'
                                var file = PAGFile.LoadFromPath(path)
                                if (file.isNone()) {
                                    showToast("pag文件不存在")
                                } else {
                                    // 设置动画拉伸模式:RepeatInverted 保持原速度，不够就来回循环播放（正播→倒播→正播...）
                                    file.getOrThrow().setTimeStretchMode(PAGTimeStretchMode.RepeatInverted)
                                    // 下面代码仅用于效果测试
                                    file.getOrThrow().setDuration(30000000) // 30s
                                    if (let Some(composition) <- file) {
                                        this.controller.setComposition(composition)
                                    }
                                    this.controller.setRepeatCount(1)
                                    this.controller.play()
                                    showToast("效果:保持原速度，不够就来回循环播放（正播→倒播→正播...）")
                                }
                            }

                        // tagLevel
                        Button('标签等级')
                            .width(90.percent)
                            .height(35)
                            .shape(ShapeType.Normal)
                            .onClick {
                                =>
                                var path = '/data/storage/el1/bundle/entry/resources/resfile/resfile_test2.pag'
                                var file: Option<PAGFile> = PAGFile.LoadFromPath(path)
                                if (file.isNone()) {
                                    showToast("pag文件不存在")
                                } else {
                                    let value = file.getOrThrow().tagLevel()
                                    showToast("该动画文件使用的标签等级为${value}")
                                }
                            }
                    }.width(100.percent)
                }
            }.width(100.percent).height(40.percent).scrollBar(BarState.Off)
        }.height(100.percent).width(100.percent).padding(left: 10, right: 10)
    }
}

// 自定义Text
@Component
class CustomText {
    @Prop
    var text: String
    func build() {
        Text(this.text)
            .width(100.percent)
            .height(40)
            .textAlign(TextAlign.Center)
            .fontSize(30)
            .fontColor(0xFFFFFF)
            .fontWeight(W400)
            .backgroundColor(0xFFC0CB)
    }
}
