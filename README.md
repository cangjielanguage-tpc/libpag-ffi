<div align="center">
<h1>libpag-cj</h1>
</div>
<p align="center">
<img alt="" src="https://img.shields.io/badge/release-v.0.0.2-brightgreen" style="display: inline-block;" />
<img alt="" src="https://img.shields.io/badge/build-pass-brightgreen" style="display: inline-block;" />
<img alt="" src="https://img.shields.io/badge/cjc-v1.0.0-brightgreen" style="display: inline-block;" />
<img alt="" src="https://img.shields.io/badge/cjcov-NA-red" style="display: inline-block;" />
<img alt="" src="https://img.shields.io/badge/project-open-brightgreen" style="display: inline-block;" />
</p>




## <img alt="" src="./doc/assets/readme-icon-introduction.png" style="display: inline-block;" width=3%/>介绍

libpag-cj是一款在仓颉环境下适配的动态图形渲染库，它基于腾讯的 libpag 开发，并对 libpag 进行了封装。libpag 旨在为仓颉开发者提供高效的矢量动画与序列帧渲染支持。

### 特性

- 🚀 支持加载本地文件方式加载pag动画
- 🚀 支持加载网络URI路径方式加载pag动画
- 🚀 支持动画播放、暂停、销毁等功能

##    <img alt="" src="./doc/assets/readme-icon-framework.png" style="display: inline-block;" width=3%/> 架构

### 源码目录

```shell
├── LICENSE  
├── doc                      # 文档目录
│   ├── assets               # 文档资源目录
│   └── feature_api.md       # API接口文档
├── entry                    # 示例代码文件夹
├── libpag                   # libpag库文件夹
│    ├─ libs                 # 依赖三方库so目录
│    ├─ src/main/cangjie/src # 仓颉侧核心代码
│    ├─ src/main/cpp/cangjie # 仓颉ffi核心代码
│    └─ src/main/external    # 仓颉依赖的三方库头文件
└── README.md                # 安装使用方法   
```

### 接口说明：

主要类和函数接口说明详见 [API](./doc/feature_api.md)

## <img alt="" src="./doc/assets/readme-icon-compile.png" style="display: inline-block;" width=3%/> 使用说明

### 编译构建

#### 依赖的三方库编译指导

1. 安装[node.js](https://nodejs.org/zh-cn)最新版本

2. 从[libpag](https://github.com/Tencent/libpag)通过git clone git@github.com:Tencent/libpag.git拉取最新三方库源码（需在github上自行添加SSH keys）

3. git checkout -b 本地分支名 origin/release/4.4 切换到[release/4.4](https://github.com/Tencent/libpag/tree/release/4.4)分支

4. 打开Git Bash在仓库根目录下执行 npm install -g depsync

5. 首次检出的仓库需要在项目根目录同步第三方依赖仓库执行 depsync 。

6. depsync完成后，打开libpag\ohos\libpag\build-profile.json5，在"externalNativeOptions"中添加"abiFilters": ["arm64-v8a","x86_64"]

7. 用DevEco Studio打开前面拉取的源码中的ohos项目工程。打开libpag\CMakeLists.txt和libpag\third_party\tgfx\CMakeLists.txt 分别注释掉里面的set(CMAKE_CXX_VISIBILITY_PRESET hidden)（这样做可以避免因为符号被隐藏，导致外部模块无法正确链接或调用库中的函数或类）

8. 在DevEco Studio中点击选中libpag\ohos\libpag目录，在顶部菜单栏选择 Build - Make Module 'libpag'，构建libpag模块

9. 构建完成后，在libpag\ohos\libpag\build\default\outputs\default下找到libpag.har，将后缀.har改成.zip，解压，然后将package\libs下的两个目录arm64-v8a和x86_64拷贝到本项目仓库libpag-cj\libpag\libs下

10. 使用 DevEco Studio 构建工程项目, 生成 hap 包即可

#### 使用说明

1. 通过 module 引入
    1. 克隆下载项目
    2. 将 libpag 模块拷贝到应用项目下
    3. 修改自身应用 entry 下的 oh-package.json5 文件，在 dependencies 字段添加 'libpag': "file:../libpag"
      ```json
      {
        "name": "entry",
        "version": "1.0.0",
        "description": "Please describe the basic information.",
        "main": "",
        "author": "",
        "license": "",
        "dependencies": {
          '@cangjie-tpc/libpag': "file:../libpag"
        }
      }
      ```
    4. 修改自身应用 entry 下的 cjpm.toml 文件，在 [dependencies] 字段下添加   [dependencies.libpag4cj]
    path = "${libpag}"
      ```toml
      [dependencies]
        [dependencies.libpag4cj]
          path = "${libpag}"
      ```
    5. 在项目中使用 import libpag4cj.* 引用 libpag 项目
      ```cangjie
      import libpag4cj.*
      ```
2. 把 libpag4cj 作为三方库依赖引入
    1. 克隆下载项目
	2. 用DevEco Studio打开工程，选中libpag目录，点击顶部菜单栏“Build”-“Make Module ‘libpag’”构建
    3. 构建成功后，在libpag的build目录中找到libpag.har，将libpag.har拷贝到需要引入的工程中。例如，在需要引入的工程entry目录下新建一个har目录，将libpag.har拷贝进去
	4. 打开 entry/oh-package.json5 在 “dependencies” 字段下添加'@cangjie-tpc/libpag':   "file:../entry/har/libpag.har"
      ```json
      "dependencies": {
        '@cangjie-tpc/libpag': "file:../entry/har/libpag.har"
      }
      ```
    5. 在项目中使用 libpag
      ```cangjie
      import libpag4cj.*
      ```

### 功能示例

#### PAGView

```cangjie
internal import ohos.base.*
internal import ohos.component.*
internal import ohos.state_manage.*
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
        // 设置动画播放次数。小于等于0表示循环播放
        this.controller.setRepeatCount(-1)
        Timer.once(50 * Duration.millisecond) {
            =>
            // 显示动画首帧
            this.controller.update()
        }
    }

    protected func aboutToDisappear() {
        // 需要在不再使用时调用 releaseAll() 来释放资源
        this.controller.releaseAll()
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
        }.width(100.percent).height(100.percent).padding(top: 20, left: 10, right: 10)
    }
}
```

#### PAGImageView

```cangjie
internal import ohos.base.*
internal import ohos.component.*
internal import ohos.state_manage.*
internal import ohos.resource_manager.*
internal import std.sync.*
internal import std.time.*
import ohos.state_macro_manage.*
import libpag4cj.*

@Entry
@Component
class EntryView {
    @State
    var controller: PAGImageViewController = PAGImageViewController()

    protected func aboutToAppear(): Unit {
        var path = '/data/storage/el1/bundle/entry/resources/resfile/resfile_test.pag'
        // 设置要播放的pag文件路径。目前resfile目录下的pag文件只能通过绝对路径设置'/data/storage/el1/bundle/entry/resources/resfile/'+pag文件名
        this.controller.setPath(path)
        // 设置动画播放次数。小于等于0表示循环播放
        this.controller.setRepeatCount(-1)
        Timer.once(50 * Duration.millisecond) {
            =>
            // 显示动画首帧
            this.controller.update()
        }
    }

    protected func aboutToDisappear() {
        // 需要在不再使用时调用 releaseAll() 来释放资源
        this.controller.releaseAll()
    }

    func build() {
        Column(20) {
            Column {
                PAGImageView(controller: this.controller)
            }.width(90.percent).height(60.percent)
            Row(50) {
                Button('播放').width(100).height(50).onClick {
                    => this.controller.play()
                }
                Button('暂停').width(100).height(50).onClick {
                    => this.controller.pause()
                }
            }
        }.width(100.percent).height(100.percent).padding(top: 20, left: 10, right: 10)
    }
}
```

## 约束和限制
在下述版本验证通过：

    DevEco Studio 5.1.0 Release(5.1.0.828SP1) 
    Cangjie Support Plugin 5.1.0.828
    Cangjie Compiler: 1.0.0(cjnative)
    SdkVersion需使用支持19及以上版本

## 开源协议

本项目基于 [Apache License Version 2.0](/LICENSE) ，请自由的享受和参与开源。

## <img alt="" src="./doc/assets/readme-icon-contribute.png" style="display: inline-block;" width=3%/> 参与贡献

欢迎给我们提交 PR，欢迎给我们提交 issue，欢迎参与任何形式的贡献。