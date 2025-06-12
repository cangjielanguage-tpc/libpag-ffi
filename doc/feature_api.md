## libpag API

### 介绍

libapg是基于仓颉语言适配的动画渲染库。

### 1. 提供PAGView动画播放组件
#### 1.1 PAGView
通用动画渲染组件，支持实时 PAG 动画播放及交互效果。
```cangjie
public class PAGView {
    /**
    * 初始化PAGView组件
    *
    * @param controller - PAGViewController控制器
    */
    PAGView(controller: controller)
}
```

#### 1.2 PAGViewController
PAGView控制器。
```cangjie
public class PAGViewController <: XComponentController {
    /*
     * 为PAGView设置新的PAGComposition以呈现为内容。请注意，如果组成是已添加到另一个PAGView，
	 * 它将从之前的PAGView中删除。
     * 
     * @param composition - PAGComposition对象，表示要渲染的动画内容
     * @return Unit - Unit
     */
    public func setComposition(composition: Option<PAGComposition>)
	
	/*
     * 返回当前PAGComposition，以便PAGView作为内容呈现。
     * 
     * @return Option<PAGComposition> -  返回一个Option类型的PAGComposition对象
     */
    public func getComposition():Option<PAGComposition>

	/*
     * setPath（）设置的pag文件的路径字符串。
     * 
     * @return String - 返回设置的pag文件的路径字符串
     */
    public func getPath():String
	
	/*
     * 从本地路径加载pag文件，如果文件不存在或数据不是pag文件则返回false。
     * 
	 * @param path - PAG文件的沙箱路径.目前只支持/data/storage/el1/bundle/entry/resources/resfile下的沙箱路径。
     * @return Bool - 返回是否成功加载
     */
    public func setPath(path: String): Bool
	
	/*
     * 从特定路径异步加载pag文件，该路径可以是网络路径或本地路径。
     * 
	 * @param path - 加载pag文件的路径。可以是网络路径或本地路径
	 * @param callback - 回调函数，接收一个 Option 类型的 PAGFile 对象。
     * @return Unit - Unit
     */
    public func setPathAsync(path: String, callback: (Option<PAGFile>) -> Unit): Unit

	/*
     * 从当前位置开始播放动画。如果动画已经在播放中，调用此方法不会产生任何效果。
     * play() 方法不会改变动画的当前位置。但是，如果动画之前已经播放到结尾，则会从头开始重新播放。
     * 
     * @return Unit - Unit
     */
    public func play(): Unit

	/*
     * 取消当前动画的播放，停留在当前位置。调用 play() 方法可以从上次暂停的位置继续播放动画。
	 * 
     * @return Unit - Unit
     */
    public func pause(): Unit

	/*
     * 指示动画是否正在播放。
	 * 
     * @return Bool - 返回是否正在播放
     */
    public func isPlaying(): Bool
	
	/*
     * 如果PAGView正在主线程中播放，则返回true。默认值为false。
	 * 
     * @return Bool - 返回是否正在主线程中播放
     */
    public func isSync(): Bool

	/*
     * 设置PAGView的同步标志。
	 * 
	 * @param isSync - 是否同步
     * @return Unit - Unit
     */
    public func setSync(isSync: Bool): Unit
	
	/*
     * 设置动画播放的次数。
	 * 
	 * @param repeatCount - 动画播放次数。小于或等于0：动画将无限循环播放。
     * @return Unit - Unit
     */
    public func setRepeatCount(repeatCount: Int32): Unit
	
	/*
     * 播放动画的总次数
	 * 
	 * @return Int32 - 播放动画的总次数
     */
    public func repeatCount(): Int32
	
	/*
     * 如果设置为false，PAGView将跳过视频合成的渲染。
	 * 
	 * @return Bool - 是否跳过视频合成的渲染。false表示跳过视频合成的渲染
     */
    public func videoEnabled(): Bool
	
	/*
     * 设置videoEnabled属性的值。
	 * 
	 * @param enable - 是否支持视频渲染
	 * @return Unit - Unit
     */
    public func setVideoEnabled(enable: Bool): Unit
	
	/*
     * 如果设置为 true，PAG 渲染器会为每一层的静态内容缓存一个内部的位图表示。这种缓存可以
	 * 提高包含复杂矢量内容的图层的渲染性能。根据内容的复杂程度，执行速度可能会显著加快，
     * 但需要额外的图形内存。默认值为 true。
	 * 
	 * @return Bool - 返回是否启用了 PAG 渲染器的位图缓存功能
     */
    public func cacheEnabled(): Bool
	
	/*
     * 设置cacheEnabled属性的值。
	 * 
	 * @param enable - 设置是否启用PAG 渲染器的位图缓存功能
	 * @return Unit - Unit
     */
    public func setVideoEnabled(enable: Bool): Unit
	
	/*
     * 如果设置为 true，PAG 会将相关的渲染数据缓存到磁盘文件中，例如视频合成的解码图像帧。
     * 这有助于减少内存使用并提高渲染性能。
	 * 
	 * @return Bool - 返回是否启用缓存功能
     */
    public func useDiskCache(): Bool

	/*
     * 设置useDiskCache属性的值。
	 * 
	 * @param value - 是否启用缓存功能
     */
    public func setUseDiskCache(value: Bool): Unit

	/*
     * 此值定义了内部图形缓存的缩放因子，范围从 0.0 到 1.0。小于 1.0 的缩放因子可能会导致输
	 * 出图像模糊，但可以减少图形内存的使用，从而提高性能。默认值为 1.0。
	 * 
	 * @return Float32 - 缩放因子值
     */
    public func cacheScale(): Float32

	/*
     * 设置cacheScale属性的值。
	 * 
	 * @param value - 缩放因子值
     */
    public func setCacheScale(value: Float32): Unit
	
	/*
     * 渲染的最大帧速率。如果设置为小于实际帧速率的值，则PAGFile，它可以降低帧数，但可以
	 * 提高性能。否则，它没有任何效果。默认值为60。
	 * 
	 * @return Float32 - 最大帧速率
     */
    public func maxFrameRate(): Float32
	
	/*
     * 设置渲染的最大帧速率。
	 * 
	 * @param value - 最大帧速率值
     */
    public func setMaxFrameRate(value: Float32): Unit
	
	/*
     * 返回当前缩放模式。
	 * 
	 * @return Int32 - 缩放模式。0：None（不缩放）、1：Stretch（拉伸填充）、2：LetterBox（按宽高比缩放并填充黑边，默认模式）、3：Zoom（按宽高比缩放并可能裁剪）
     */
    public func scaleMode(): Int32

	/*
     * 指定如何缩放页面内容以适应曲面大小的规则。矩阵调用此方法时会发生变化。
	 * 
	 * @param value - 缩放模式。0：None（不缩放）、1：Stretch（拉伸填充）、2：LetterBox（按宽高比缩放并填充黑边，默认模式）、3：Zoom（按宽高比缩放并可能裁剪）
     */
    public func setScaleMode(value: Int32): Unit
	
	/*
     * 返回当前矩阵的副本。
	 * 
	 * @return Array<Float32> - 当前矩阵的副本
     */
    public func matrix(): Array<Float32>
	
	/*
     * 设置将应用于合成的变换。scaleMode属性调用此方法时，将设置为PAGScaleMode:：None。
	 * 
	 * @param value - 要设置的变换矩阵
     */
    public func setMatrix(values: Array<Float32>): Unit
	
	/*
     * 当前合成的持续时间（以微秒为单位）
	 * 
	 * @return Int64 - 返回当前合成的持续时间
     */
    public func duration(): Int64
	
	/*
     * 返回当前播放位置的进度，该值在0.0到1.0之间。
	 * 
	 * @return Float64 - 当前播放位置的进度值
     */
    public func getProgress(): Float64
	
	/*
     * 设置播放位置的进度，有效值为0.0到1.0。
	 * 
	 * @param value - 要设置的播放进度
     */
    public func setProgress(value: Float64): Unit

	/*
     * 返回当前帧。
	 * 
	 * @return Int32 - 当前帧
     */
    public func currentFrame(): Int32
	
	/*
     * 调用此方法可立即渲染当前位置。请注意，之前对 PAGView 所做的所有更改仅在此方法被
	 * 调用后才会生效。如果已经调用了 play() 方法，则无需手动调用此方法，因为它会在每一
	 * 帧自动被调用。如果内容发生了变化，则返回 true。
	 * 
	 * @return Bool - 内容是否发生变化
     */
    public func flush(): Bool
	
	/*
     * 返回位于指定点下方的图层数组。该点以像素为单位。
	 * 
	 * @param x - 指定点的水平方向上的坐标
	 * @param y - 指定点的垂直方向上的坐标
	 * @return Array<PAGLayer> - 返回位于指定点下方的图层数组
     */
    public func getLayersUnderPoint(x: Float32, y: Float32): Array<PAGLayer>
	
	/*
     * 立即释放pag视图创建的缓存。可以调用以减轻内存压力。
	 * 
     */
    public func freeCache(): Unit
	
	/*
     * 返回一个捕获PAGView内容的位图。后续渲染PAGView将不会被捕获。如果PAGView尚未显示，则返回null。
	 * 
	 * @return Option<PixelMap> - 返回一个捕获PAGView内容的位图
     */
    public func makeSnapshot(): Option<PixelMap>
	
	/*
     * 返回一个以像素为单位的矩形，该矩形定义了指定层的显示区域位于PAGView的坐标系中。
	 *
	 * @param layer - 需要获取显示区域的图层
	 * @return Array<Float32> - 返回一个以像素为单位的矩形
     */
    public func getBounds(layer: Option<PAGLayer>): Array<Float32>
	
	/*
     * 添加一个监听器到监听器集合中，这些监听器会在动画的生命周期内接收到事件，例如开始、重复和结束事件。
	 *
	 * @param listener - 要添加的动画监听器对象
	 *
     */
    public func addListener(listener: PAGViewListener)
	
	/*
     * 从集合中删除收听此动画的收听者。
	 *
	 * @param listener - 要删除的动画监听器对象
	 *
     */
    public func removeListener(listener: PAGViewListener)
	
	/*
     * 立即释放 PAGViewController 实例所使用的资源，而不是依赖垃圾收集器在未来某个时刻为你完成这项工作。
	 *
     */
    public func releaseAll(): Unit

	/*
     * 获取当前 PAGView 实例的唯一标识符
     *
	 * @return String - 返回当前 PAGView 对象对应的唯一字符串ID
     */
    public func uniqueID(): String

	/*
     * 手动触发动画的帧更新
	 *
     */
    public func update(): Unit
}

```

### 2. 提供PAGImageView动画播放组件

#### 2.1 PAGImageView
UI 场景专用渲染组件，通过磁盘缓存优化多动画同时播放的性能。
```cangjie
public class PAGImageView {
    /**
    * 初始化PAGImageView组件
    *
    * @param controller - PAGImageViewController控制器
    */
    PAGImageView(controller: controller)
}
```

#### 2.2 PAGImageViewController
PAGImageView控制器。
```cangjie
public class PAGImageViewController <: XComponentController {

    /*
     * 返回 PAGImageView 中的当前 PAGComposition。如果内部组合是从 pag 文件路径加载的，则返回 null
     * 
     * @return Option<PAGComposition> - 返回 PAGImageView 中的当前 PAGComposition，可能为 null
     */
    public func getComposition(): Option<PAGComposition>
    
    /*
     * 设置一个新的 PAGComposition 到 PAGImageView，并将最大帧率设置为 30 fps。注意：
	 * 如果该组合已添加到另一个 PAGImageView，它将从之前的 PAGImageView 中移除
     * 
     * @param composition - 要设置的 PAGComposition，可能为 null
     * @param maxFrameRate - 可选参数，设置最大帧率，默认为 30.0
     */
    public func setComposition(composition: Option<PAGComposition>, maxFrameRate!: Float64 = 30.0): Unit

    /*
     * 设置一个新的 PAGComposition 到 PAGImageView，并将最大帧率设置为 30 fps。注意：如果
	 * 该组合已添加到另一个 PAGImageView，它将从之前的 PAGImageView 中移除
     * 
     * @param composition - 要设置的 PAGComposition，可能为 null
     * @param maxFrameRate - 可选参数，设置最大帧率，默认为 30.0
     */
    public func setComposition(composition: Option<PAGComposition>, maxFrameRate!: Float64 = 30.0): Unit
    
    /*
     * 获取通过 setPath() 方法设置的 pag 文件的路径字符串
     * 
     * @return String - 返回 pag 文件的路径字符串
     */
    public func getPath(): String
    
    /*
     * 从本地路径加载 pag 文件，如果文件不存在或数据不是 pag 文件，则返回 false
     * 
     * @param path - 要加载的 pag 文件的路径
     * @param maxFrameRate - 可选参数，设置最大帧率，默认为 30.0
     * @return Bool - 返回加载是否成功，true 表示成功，false 表示失败
     */
    public func setPath(path: String, maxFrameRate!: Float64 = 30.0): Bool
    
    /*
     * 返回当前的缩放模式
     * 
     * @return Int32 - 返回当前的缩放模式
     */
    public func scaleMode(): Int32

    /*
     * 指定如何缩放 pag 内容以适应 PAGImageView 的大小的规则。调用此方法时，PAGImageView
	 * 的当前矩阵会发生变化
     * 
     * @param scaleMode - 指定缩放模式的整数值
     */
    public func setScaleMode(scaleMode: Int32): Unit

    /*
     * 返回当前矩阵的一个副本
     * 
     * @return Matrix4 - 返回当前矩阵的一个副本
     */
    public func matrix(): Matrix4

    /*
     * 设置将应用于组合的变换。调用此方法时，scaleMode 属性将被设置为 PAGScaleMode::None
     * 
     * @param matrix - 要设置的变换矩阵
     * @return Unit - 无返回值
     */
    public func setMatrix(matrix: Matrix4): Unit

    /*
     * 该值定义了缓存图像帧大小的缩放因子，范围从 0.0 到 1.0。小于 1.0 的缩放因子可能导致输出
     * 模糊，但可以减少图形内存使用，提高渲染性能。默认值为 1.0
     * 
     * @return Float64 - 返回当前的缩放因子
     */
    public func renderScale(): Float64
    
    /*
     * 设置 renderScale 属性的值
     * 
     * @param renderScale - 要设置的缩放因子
     * @return Unit - 无返回值
     */
    public func setRenderScale(renderScale: Float64): Unit
    
    /*
     * 如果设置为 true，PAGImageView 将所有图像帧加载到内存中，这将显著提高渲染性能，但可能会
     * 消耗大量额外内存。如果优先考虑渲染速度而不是内存使用，请将其设置为 true。如果设置为
     * false，PAGImageView 一次只将一个图像帧加载到内存中。默认值为 false
     * 
     * @return Bool - 返回是否缓存所有帧到内存中的状态
     */
    public func cacheAllFramesInMemory(): Bool
    
    /*
     * 设置 cacheAllFramesInMemory 属性的值
     * 
     * @param enable - 要设置的缓存状态
     */
    public func setCacheAllFramesInMemory(enable: Bool): Unit
    
    /*
     * 返回 PAGImageView 正在渲染的当前帧索引
     * 
     * @return Float64 - 返回当前帧索引
     */
    public func currentFrame(): Float64
    
    /*
     * 设置 PAGImageView 要渲染的帧索引
     * 
     * @param currentFrame - 要设置的帧索引
     */
    public func setCurrentFrame(currentFrame: Float64): Unit
    
    /*
     * 返回捕获当前 PAGImageView 内容的 PixelMap
     * 
     * @return Option<PixelMap> - 返回当前 PAGImageView 内容的 PixelMap，可能为 null
     */
    public func currentImage(): Option<PixelMap>
    
    /*
     * 从当前位置开始播放动画。如果动画已经在播放，调用 play() 方法没有效果。play() 方法不
     * 会改变动画的当前位置。但是，如果动画之前到达了结尾，它将从头开始重新播放
     *
     */
    public func play(): Unit
    
    /*
     * 指示动画是否正在播放
     * 
     * @return Bool - 返回动画是否正在播放的状态
     */
    public func isPlaying(): Bool
    
    /*
     * 在当前位置暂停动画。调用 play() 方法可以从上次暂停的位置恢复动画
     * 
     */
    public func pause(): Unit
    
    /*
     * 动画要播放的总次数。默认值为 1，表示动画只会播放一次。如果重复次数设置为 0 或负值，
     * 动画将无限次播放
     * 
     * @return Int64 - 返回动画的重复次数
     */
    public func repeatCount(): Int64

    /*
     * 设置动画播放的次数
     * 
     * @param repeatCount - 要设置的动画重复次数
     */
    public func setRepeatCount(repeatCount: Int64): Unit
    
    /*
     * 添加一个监听器到动画生命周期事件监听器集合中，例如开始、重复和结束事件
     * 
     * @param listener - 要添加的 PAGImageViewListener 监听器
     */
    public func addListener(listener: PAGImageViewListener): Unit
    
    /*
     * 从动画监听器集合中移除一个监听器
     * 
     * @param listener - 要移除的 PAGImageViewListener 监听器
     */
    public func removeListener(listener: PAGImageViewListener): Unit
    
    /*
     * 立即渲染当前图像帧。注意，之前对 PAGImageView 的所有更改将在此方法调用后生效。如果 play() 方法已经被调用，则无需手动调用此方法，因为它将在每一帧自动调用。如果内容已更改，则返回 true
     * 
     * @return Bool - 返回内容是否已更改
     */
    public func flush(): Bool

}

```

### 3. 其他接口

#### 3.1 PAGComposition
PAG 动画层容器，负责管理动画的分层结构与属性。
```cangjie
public class PAGComposition <: PAGLayer {

	/*
     * 创建一个指定大小的空 PAGComposition
     * 
     * @param width - PAGComposition 的宽度
     * @param height - PAGComposition 的高度
     * @return Option<PAGComposition> - 返回一个空 PAGComposition 的选项
     */
    public static func make(width: Int32, height: Int32): Option<PAGComposition>

    /*
     * 返回合成物的宽度
     * 
     * @return Int64 - 返回合成物的宽度
     */
    public func width(): Int64
    
    /*
     * 返回合成物的高度
     * 
     * @return Int64 - 返回合成物的高度
     */
    public func height(): Int64
    
    /*
     * 设置合成物的大小
     * 
     * @param width - 要设置的合成物的宽度
     * @param height - 要设置的合成物的高度
     */
    public func setContentSize(width: Int64, height: Int64): Unit
    
    /*
     * 返回此组合中子层的数量
     * 
     * @return Int64 - 返回子层的数量
     */
    public func numChildren(): Int64
    
    /*
     * 返回指定索引位置的子层
     * 
     * @param index - 子层的索引位置
     * @return Option<PAGLayer> - 返回指定索引位置的子层
     */
    public func getLayerAt(index: Int64): Option<PAGLayer>

    /*
     * 返回指定子层的索引位置
     * 
     * @param layer - 要被识别的层实例
     * @return Int64 - 返回要被识别的子层的索引位置
     */
    public func getLayerIndex(layer: PAGLayer): Int64
    
    /*
     * 更改容器中现有子项的位置。这将影响子层的层叠顺序。
     * 
     * @param layer - 需要更改索引的子层
     * @param index - 子层的目标索引
     */
    public func setLayerIndex(layer: PAGLayer, index: Int64): Unit
    
    /*
     * 将 PAGLayer 添加到当前 PAGComposition 的顶部
     * 
     * @param pagLayer - 要添加到 PAGComposition 的 PAGLayer
     * @return Bool - 返回操作是否成功
     */
    public func addLayer(pagLayer: PAGLayer): Bool
    
    /*
     * 将 PAGLayer 添加到当前 PAGComposition 的指定索引位置
     * 
     * @param pagLayer - 要添加到 PAGComposition 的 PAGLayer
     * @param index - 要添加 PAGLayer 的目标索引位置
     * @return Bool - 返回操作是否成功
     */
    public func addLayerAt(pagLayer: PAGLayer, index: Int64): Bool

    /*
     * 检查当前 PAGComposition 是否包含指定的 pagLayer
     * 
     * @param pagLayer - 要检查是否包含在 PAGComposition 中的 PAGLayer
     * @return Bool - 返回当前 PAGComposition 是否包含指定的 pagLayer
     */
    public func contains(pagLayer: PAGLayer): Bool

    /*
     * 从当前 PAGComposition 中移除指定的 PAGLayer
     * 
     * @param pagLayer - 要从 PAGComposition 中移除的 PAGLayer
     * @return Option<PAGLayer> - 返回被移除的 PAGLayer，如果未找到则返回 None
     */
    public func removeLayer(pagLayer: PAGLayer): Option<PAGLayer>

    /*
     * 从当前 PAGComposition 中移除指定索引位置的 PAGLayer
     * 
     * @param index - 要从 PAGComposition 中移除的 PAGLayer 的索引位置
     * @return Option<PAGLayer> - 返回被移除的 PAGLayer，如果未找到则返回 None
     */
    public func removeLayerAt(index: Int64): Option<PAGLayer>

    /*
     * 从当前 PAGComposition 中移除所有 PAG 层
     * 
     * @return Unit - 无返回值
     */
    public func removeAllLayers(): Unit

    /*
     * 交换两个 PAG 层的位置
     * 
     * @param pagLayer1 - 要交换的第一个 PAGLayer
     * @param pagLayer2 - 要交换的第二个 PAGLayer
     */
    public func swapLayer(pagLayer1: PAGLayer, pagLayer2: PAGLayer): Unit

    /*
     * 交换指定索引位置的两个 PAG 层
     * 
     * @param index1 - 要交换的第一个 PAGLayer 的索引位置
     * @param index2 - 要交换的第二个 PAGLayer 的索引位置
     * @return Unit - 无返回值
     */
    public func swapLayerAt(index1: Int64, index2: Int64): Unit

    /*
     * 获取此作品的音频数据，音频数据是 MPEG-4 容器中的 AAC 音频
     * 
     * @return Array<UInt8> - 返回音频数据的字节数组
     */
    public func audioBytes(): Array<UInt8>

    /*
     * 指示音乐片段时间轴中音频第一帧的播放时间
     * 
     * @return Int64 - 返回音频第一帧播放的时间位置
     */
    public func audioStartTime(): Int64

    /*
     * 返回此歌曲的音频标签
     * 
     * @return Array<PAGMarker> - 返回音频标签的数组
     */
    public func audioMarkers(): Array<PAGMarker>

    /*
     * 返回与指定图层名称匹配的图层数组
     * 
     * @param layerName - 要匹配的图层名称
     * @return Array<PAGLayer> - 返回匹配的图层数组
     */
    public func getLayersByName(layerName: String): Array<PAGLayer>

    /*
     * 返回位于指定点下方的图层数组。该点以像素为单位，来自 PAG 组合的本地坐标
     * 
     * @param localX - 点的 x 坐标，以像素为单位
     * @param localY - 点的 y 坐标，以像素为单位
     * @return Array<PAGLayer> - 返回位于指定点下方的图层数组
     */
    public func getLayersUnderPoint(localX: Float32, localY: Float32): Array<PAGLayer>

}

```

#### 3.2 PAGFile
PAG 动画文件加载器，解析并准备动画资源以供渲染。
```cangjie
public class PAGFile <: PAGComposition {
    /*
     * 当前SDK支持的最大标记级别。
     *
     * @return UInt32 - UInt32
     */
    public static func MaxSupportedTagLevel(): UInt32

    /*
     * 从本地路径加载一个 PAG 文件，如果文件不存在或数据不是 PAG 文件，则返回 null。
	 * 注意：通过相同路径加载的所有 PAGFile 实例共享同一个内部缓存。内部缓存会一直存在，
	 * 直到所有 PAGFile 实例都被释放。如果你不想从内部缓存加载 PAGFile，可以使用 
	 * PAGFile.LoadFromBytes() 方法。
     *
	 * @param path - PAG文件的沙箱路径.目前只支持/data/storage/el1/bundle/entry/resources/resfile下的沙箱路径。
     * @return Option<PAGFile> - 返回PAGFile对象
     */
    public static func LoadFromPath(path: String): Option<PAGFile>

    /*
     * 从指定的路径（可以是网络路径或本地路径）加载一个 PAG 文件，如果文件不存在或数据不是
     * PAG 文件，则返回 null。注意：通过相同路径加载的所有 PAGFile 实例共享同一个内部缓存。
	 * 内部缓存会一直存在，直到所有PAGFile 实例都被释放。如果你不想从内部缓存加载 PAGFile，
	 * 可以使用 PAGFile.LoadFromBytes() 方法。
     *
	 * @param callback - 回调函数，接收一个 Option 类型的 PAGFile 对象。
	 * @param filePath - PAG文件路径。本地路径目前只支持/data/storage/el1/bundle/entry/resources/resfile下的沙箱路径。
     */
    public static func LoadFromPathAsync(filePath: String, callback: (Option<PAGFile>) -> Unit): Unit

    /*
     * 从Array加载pag文件，如果数据为空或不是有效的pag文件则返回null。
     *
	 * @param bytes - pag文件的Array数据
     * @return Option<PAGFile> - 返回PAGFile对象
     */
    public static func LoadFromBytes(bytes: Array<UInt8>): Option<PAGFile>

    /*
     * 从 assets 加载一个 PAG 文件，如果文件不存在或数据不是 PAG 文件，则返回 null。注意：通过
	 * 相同路径加载的资源在内存中是共享的，直到文件被释放。如果文件可能会被更改，请使用 
	 * PAGFile.LoadFromBytes() 方法。
     *
	 * @param manager - 资源管理对象
	 * @param name - resources\rawfile目录下的pag文件名。
     * @return Option<PAGFile> - 返回PAGFile对象
     */
    public static func LoadFromAssets(manager: ResourceManager, name: String): Option<PAGFile>

    /*
     * 此pag文件所需的标记级别。
     *
     * @return Int64 - 返回标记级别
     */
    public func tagLevel(): Int64

    /*
     * 可编辑文本的数量。
     *
     * @return Int64 - 返回可编辑文本的数量
     */
    public func numTexts(): Int64

    /*
     * 可替换图像的数量。
     *
     * @return Int64 - 返回可替换图像的数量
     */
    public func numImages(): Int64

    /*
     * 视频作品的数量。
     *
     * @return Int64 - 返回视频作品的数量。
     */
    public func numVideos(): Int64

    /*
     * 如果文件是从字节流加载的，则此文件的路径字符串将返回空字符串。
     *
     * @return String - 返回文件的路径字符串
     */
    public func path(): String

    /*
     * 获取指定索引的文本数据。索引的范围从0到numTexts-1。注意：它总是返回默认的文本数据。
     *
	 * @param index - 文本数据索引
     * @return PAGText - 返回PAGText对象
     */
    public func getTextData(index: Int32): PAGText

    /*
     * 替换指定索引的文本数据。索引的范围从0到PAGFile.numTexts-1。为textData参数传递null将其重置为默认文本数据。
     *
	 * @param index - 文本数据索引
	 * @param pagText - 要替换的PAGText对象
     */
    public func replaceText(index: Int32, pagText: PAGText): Unit

    /*
     * 替换指定索引的图像数据。索引的范围从0到PAGFile.numImages-1。传入null后，图像参数将重置为默认图像数据。
     *
	 * @param index - 图像数据索引
	 * @param pagImage - 要替换的PAGImage对象
     */
    public func replaceImage(index: Int32, pagImage: Option<PAGImage>)

    /*
     * 替换指定图层名称的图像数据。为图像参数传入null将使其重置为默认图像数据。
     *
	 * @param layerName - 图像数据的图层名称
	 * @param pagImage - 要替换的PAGImage对象
     */
    public func replaceImageByName(layerName: String, pagImage: Option<PAGImage>): Unit

    /*
     * 按指定的可编辑索引和图层类型返回图层数组。
     *
	 * @param index - 可编辑图层索引
	 * @param layerType - 图层类型
	 * @return Array<PAGLayer> - 返回指定可编辑索引和图层类型的图层数组
     */
    public func getLayersByEditableIndex(index: Int32, layerType: Int32): Array<PAGLayer>
	
	/*
     * 返回此 PAGFile 中可编辑图层的索引。如果某个 PAGLayer 的 editableIndex 不在返回的索引中，
	 * 则该 PAGLayer 不应被视为可编辑。
     *
	 * @param layerType - 图层类型
	 * @return Array<Int64> 返回此PAGFile中可编辑图层的索引数组
     */
    public func getEditableIndices(layerType: Int32): Array<Int64>

	/*
     * 指示在文件时长发生变化时，如何拉伸原始时长以适应目标时长。默认值为 PAGTimeStretchMode::Repeat。
     *
	 * @return Int32 返回当前的时间拉伸模式。0：None（保持原速，不足时显示最后一帧）:1：Scale（调整播放速度以适应时长）:2：Repeat（保持原速，不足时重复内容，默认模式）:3：RepeatInverted（保持原速，不足时反向重复内容）
     */
    public func timeStretchMode(): Int32

	/*
     * 设置此文件的timeStretchMode。
     *
	 * @param mode - 要设置的时间拉伸模式。0：None（保持原速，不足时显示最后一帧）:1：Scale（调整播放速度以适应时长）:2：Repeat（保持原速，不足时重复内容，默认模式）:3：RepeatInverted（保持原速，不足时反向重复内容）
     */
    public func setTimeStretchMode(mode: Int32): Unit

	/*
     * 设置此PAG文件的持续时间。传递小于或等于0的值会将持续时间重置为默认值。
     *
	 * @param duration - 要设置的PAG文件持续时间
     */
    public func setDuration(duration: Int64): Unit

	/*
     * 复制原始文件，对当前文件的任何修改都不会对结果文件产生影响。
     *
	 * @return Option<PAGFile> 返回复制原始文件的PAGFile对象
     */
    public func copyOriginal(): Option<PAGFile>

	/*
     * 图层的时长（以微秒为单位），表示可见范围的时间长度。
     *
	 * @param duration - 要设置的图层时长
     */
    public func duration(duration: Int64): Int64
}

```

#### 3.3 PAGImage
PAG 动画中的图像工具类，支持纹理操作与图像处理。
```cangjie
public class PAGImage {
    /*
     * 从图像文件的路径创建PAGImage对象，如果该文件不存在或不是有效的图像文件，则返回null。
     * 
     * @param path - 图像文件的沙箱路径.目前只支持/data/storage/el1/bundle/entry/resources/resfile下的沙箱路径。
     * @return Option<PAGImage> - 返回PAGImage对象
     */
    public static func FromPath(path: String): Option<PAGImage>

    /*
     * 根据指定的字节数据创建PAGImage对象，如果字节为空或不是有效的图像文件，则返回null。
     * 
     * @param path - 图像字节数据
     * @return Option<PAGImage> - 返回PAGImage对象
     */
    public static func FromBytes(bytes: Array<UInt8>): Option<PAGImage>

    /*
     * 从资源加载pag文件，如果文件不存在或数据不是有效的图像文件，则返回null。
     * 
	 * @param manager - 资源管理对象
	 * @param name - resources\rawfile目录下的pag文件名。
     * @return Option<PAGImage> - 返回PAGImage对象
     */
    public static func LoadFromAssets(manager: ResourceManager, name: String): Option<PAGImage>

    /*
     * 返回图像的宽度（像素）。
     * 
     * @return Int64 - 返回图像的宽度
     */
    public func width(): Int64

    /*
     * 返回图像的高度（像素）。
     * 
     * @return Int64 - 返回图像的高度
     */
    public func height(): Int64

    /*
     * 返回当前缩放模式。
     * 
     * @return Int32 - 返回当前缩放模式
     */
    public func scaleMode(): Int32

    /*
     * 指定如何缩放图像内容以适应原始图像大小的规则。
     * 
     * @param mode - 要设置的缩放模式。0：None（内容不缩放）1：Stretch（内容被拉伸以适应）2：LetterBox（内容按原始未缩放图像的宽高比进行缩放）3：Zoom（内容按原始未缩放图像的宽高比进行缩放）
     */
    public func setScaleMode(mode: Int32): Unit

    /*
     * 返回当前矩阵的副本。
     * 
     * @return Array<Float32> - 返回当前矩阵的副本
     */
    public func matrix(): Array<Float32>

    /*
     * 设置将应用于图像内容的变换。
     * 
     * @param values - 要设置的变换矩阵
     */
    public func setMatrix(values: Array<Float32>): Unit
}

```

#### 3.4 PAGPlayer
PAG 动画核心播放控制器，管理时间轴、事件及渲染流程。
```cangjie
public class PAGPlayer {
    /*
     * 返回PAGPlayer渲染为内容的当前PAGComposition。
     * 
     * @return Option<PAGComposition> - 返回PAGPlayer渲染为内容的当前PAGComposition
     */
    public func getComposition(): Option<PAGComposition>

    /*
     * 为 PAGPlayer 设置一个新的 PAGComposition 作为渲染内容。注意：如果该合成（composition）
	 * 已经被添加到另一个 PAGPlayer 中，它将会从之前的 PAGPlayer 中移除。
     * 
     * @param composition - 要设置的新的PAGComposition
     */
    public func setComposition(composition: Option<PAGComposition>)

    /*
     * 返回PAGPlayer要渲染的PAGSurface对象。
     * 
     * @return Option<PAGSurface> - 返回PAGPlayer要渲染的PAGSurface对象
     */
    public func getSurface(): Option<PAGSurface>

    /*
     * 设置PAGPlayer要渲染的PAGSurface对象。
     * 
     * @param surface - 要渲染的PAGSurface对象
     */
    public func setSurface(surface: Option<PAGSurface>): Unit

    /*
     * 如果设置为false，播放器将跳过视频合成的渲染。
     * 
     * @return Bool - 是否跳过视频合成的渲染。false表示跳过视频合成的渲染
     */
    public func videoEnabled(): Bool

    /*
     * 设置videoEnabled属性的值。
     * 
     * @param value - 是否支持视频渲染
     */
    public func setVideoEnabled(value: Bool): Unit

    /*
     * 如果设置为 true，PAGPlayer 会为每个图层缓存静态内容的内部位图表示，这种缓存可以提
	 * 高包含复杂矢量内容的图层的性能，执行速度会根据内容的复杂度显著加快，但需要额外的图
	 * 形内存，默认值为 true。
     * 
     * @return Bool - 返回是否启用为每个图层缓存静态内容的内部位图表示的功能
     */
    public func cacheEnabled(): Bool

    /*
     * 设置cacheEnabled属性的值。
     * 
     * @param value - 设置是否启用为每个图层缓存静态内容的内部位图表示的功能
     */
    public func setCacheEnabled(value: Bool): Unit

    /*
     * 如果设置为 true，PAG 会将相关的渲染数据缓存到磁盘文件中，例如视频合成的解码图像帧，
	 * 这有助于减少内存使用并提高渲染性能。
     * 
     * @return Bool - 返回当前是否启用了将相关渲染数据缓存到磁盘文件的功能
     */
    public func useDiskCache(): Bool

    /*
     * 设置useDiskCache属性的值。
     * 
     * @param value - 设置是否启用了将相关渲染数据缓存到磁盘文件的功能
     */
    public func setUseDiskCache(value: Bool): Unit

	/*
     * 该值定义了内部图形缓存的缩放因子，范围从 0.0 到 1.0。小于 1.0 的缩放因子可能会导致输
	 * 出模糊，但可以减少图形内存的使用，从而提高性能。默认值为 1.0。
	 * 
	 * @return Float32 - 缩放因子值
     */
    public func cacheScale(): Float32

	/*
     * 设置cacheScale属性的值。
	 * 
	 * @param value - 缩放因子值
     */
    public func setCacheScale(value: Float32): Unit

	/*
     * 该设置定义了渲染的最大帧率，其取值范围在 1 到 60 之间。如果将其设置为一个低于合成
	 * 内容实际帧率的值，系统会丢弃部分帧以降低渲染压力，从而提高性能。反之，如果设置的值
	 * 不低于实际帧率，则该设置不会产生任何效果。默认值为 60。
	 * 
	 * @return Float32 - 最大帧速率
     */
    public func maxFrameRate(): Float32
	
	/*
     * 设置渲染的最大帧速率。
	 * 
	 * @param value - 最大帧速率值
     */
    public func setMaxFrameRate(value: Float32): Unit

	/*
     * 返回当前缩放模式。
	 * 
	 * @return Int32 - 缩放模式。0：None（不缩放）、1：Stretch（拉伸填充）、2：LetterBox（按宽高比缩放并填充黑边，默认模式）、3：Zoom（按宽高比缩放并可能裁剪）
     */
    public func scaleMode(): Int32

	/*
     * 该设置指定了如何将 PAG 内容缩放以适应目标表面（surface）大小的规则。
	 * 当调用此方法时，相关的变换矩阵（matrix）会随之更新。
	 * 
	 * @param value - 缩放模式。0：None（不缩放）、1：Stretch（拉伸填充）、2：LetterBox（按宽高比缩放并填充黑边，默认模式）、3：Zoom（按宽高比缩放并可能裁剪）
     */
    public func setScaleMode(value: Int32): Unit

	/*
     * 返回当前矩阵的副本。
	 * 
	 * @return Array<Float32> - 当前矩阵的副本
     */
    public func matrix(): Array<Float32>
	
	/*
     * 设置将应用于合成的变换。scaleMode属性调用此方法时，将设置为PAGScaleMode:：None。
	 * 
	 * @param value - 要设置的变换矩阵
     */
    public func setMatrix(values: Array<Float32>): Unit

	/*
     * 当前合成的持续时间（以微秒为单位）
	 * 
	 * @return Float64 - 返回当前合成的持续时间
     */
    public func duration(): Float64
	
	/*
     * 返回当前播放位置的进度，该值在0.0到1.0之间。
	 * 
	 * @return Float64 - 当前播放位置的进度值
     */
    public func getProgress(): Float64
	
	/*
     * 设置播放位置的进度，该值范围在 0.0 到 1.0 之间。此设置仅在合成对象不为空时生效
	 * 
	 * @param value - 要设置的播放进度
     */
    public func setProgress(value: Float64): Unit

	/*
     * 返回当前帧。
	 * 
	 * @return Int64 - 当前帧
     */
    public func currentFrame(): Int64

	/*
     * 为下一次的 flush() 调用准备播放器 它会收集从当前合成进度开始的所有 CPU 任务 并异步并行地执行它们 这通常用于加速首帧的渲染
	 * 
     */
    public func prepare(): Unit

	/*
     * 立即将所有待处理的更改应用到目标表面 如果内容已更改则返回 true
	 * 
	 * @return Bool - 内容是否发生变化
     */
    public func flush(): Bool

	/*
     * 返回一个以像素为单位的矩形 该矩形定义了指定图层在 PAGSurface 坐标系中的显示区域
	 *
	 * @param layer - 需要获取显示区域的图层
	 * @return Array<Float32> - 返回一个以像素为单位的矩形
     */
    public func getBounds(layer: Option<PAGLayer>): Array<Float32>

	/*
     * 返回位于指定点下方的图层数组 该点以像素为单位 且基于表面的坐标系
	 * 
	 * @param surfaceX - 指定点的水平方向上的坐标
	 * @param surfaceY - 指定点的垂直方向上的坐标
	 * @return Array<PAGLayer> - 返回位于指定点下方的图层数组
     */
    public func getLayersUnderPoint(surfaceX: Float32, surfaceY: Float32): Array<PAGLayer>

    /*
     * 评估 PAGLayer 是否与基于 PAGSurface 坐标系（而非包含该 PAGLayer 的 PAGComposition）的
	 * 指定点重叠或相交，如果 PAGLayer 或其父级（或更高层级的父级）未被添加到此 PAGPlayer，
	 * 则始终返回 false，pixelHitTest 参数用于指示是否检查对象的实际像素（true）或边界框
	 * （false），若 PAGLayer 与指定点重叠或相交则返回 true。
     * 
     * @param layer - 要检查的 PAGLayer
     * @param surfaceX - 指定点的水平方向上的坐标
     * @param surfaceY - 指定点的垂直方向上的坐标
     * @param pixelHitTest - 指示是否检查对象的实际像素（true）或边界框（false）
     * @return Bool - 如果 PAGLayer 与指定点重叠或相交则返回 true
     */
    public func hitTestPoint(layer: Option<PAGLayer>, surfaceX: Float32, surfaceY: Float32, pixelHitTest: Bool): Bool

	/*
     * 立即释放 PAGPlayer 实例占用的资源，而不是依赖垃圾回收器在未来某个时间点自动释放。
	 *
     */
    public func release(): Unit
}

```