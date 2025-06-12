/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package libpag4cj

@FastNative
foreign {
    func cj_PAGImageViewController_createPAGImageView(): Int64

    func cj_PAGImageViewController_setComposition(cjImageView: Int64, native: Int64, maxFrameRate: Float64): Unit

    func cj_PAGImageViewController_scaleMode(cjImageView: Int64): Int32

    func cj_PAGImageViewController_setScaleMode(cjImageView: Int64, scaleMode: Int32): Unit

    func cj_PAGImageViewController_matrix(cjImageView: Int64): CJFloat32Array

    func cj_PAGImageViewController_setMatrix(cjImageView: Int64, bytes: CPointer<Float32>): Unit

    func cj_PAGImageViewController_renderScale(cjImageView: Int64): Float64

    func cj_PAGImageViewController_setRenderScale(cjImageView: Int64, renderScale: Float64): Unit

    func cj_PAGImageViewController_cacheAllFramesInMemory(cjImageView: Int64): Bool

    func cj_PAGImageViewController_setCacheAllFramesInMemory(cjImageView: Int64, enable: Bool): Unit

    func cj_PAGImageViewController_currentFrame(cjImageView: Int64): Float64

    func cj_PAGImageViewController_setCurrentFrame(cjImageView: Int64, currentFrame: Float64): Unit

    func cj_PAGImageViewController_currentImage(cjImageView: Int64): CJPixelMap

    func cj_PAGImageViewController_play(cjImageView: Int64): Unit

    func cj_PAGImageViewController_isPlaying(cjImageView: Int64): Bool

    func cj_PAGImageViewController_pause(cjImageView: Int64): Unit

    func cj_PAGImageViewController_repeatCount(cjImageView: Int64): Int64

    func cj_PAGImageViewController_setRepeatCount(cjImageView: Int64, repeatCount: Int64): Unit

    func cj_PAGImageViewController_flush(cjImageView: Int64): Bool

    func cj_PAGImageViewController_uniqueID(cjImageView: Int64): CString

    func cj_PAGImageViewController_update(cjImageView: Int64): Unit
}

public abstract class PAGImageViewListener {
    /**
     * Notifies the start of the animation. It can be called from either the UI thread or the
     * thread that calls the play() method.
     */
    public var onAnimationStart: Option<(PAGImageViewController) -> Unit> = None

    /**
     * Notifies the end of the animation. It can only be called from the UI thread.
     */
    public var onAnimationEnd: Option<(PAGImageViewController) -> Unit> = None

    /**
     * Notifies the repetition of the animation. It can only be called from the UI thread.
     */
    public var onAnimationRepeat: Option<(PAGImageViewController) -> Unit> = None

    /**
     * Notifies the cancellation of the animation. It can be called from either the UI thread or
     * the thread that calls the stop() method.
     */
    public var onAnimationCancel: Option<(PAGImageViewController) -> Unit> = None

    /**
     * Notifies another frame of the animation has occurred. It may be called from an arbitrary
     * thread if the animation is running asynchronously.
     */
    public var onAnimationUpdate: Option<(PAGImageViewController) -> Unit> = None
}

public class PAGImageViewController <: XComponentController {
    private var composition: Option<PAGComposition> = None
    private var filePath: String = ""
    private var listeners: ArrayList<PAGImageViewListener> = ArrayList<PAGImageViewListener>(4)
    private var view: Option<PAGImageView> = None
    // Binding with C code, the object pointer returned by C code.
    private var cjImageView: Int64 = 0

    public init() {
        cjImageView
        unsafe {
            cjImageView = cj_PAGImageViewController_createPAGImageView()
        }
    }

    /**
     * Returns the current PAGComposition in the PAGImageView. Returns null if the internal
     * composition was loaded from a pag file path.
     */
    public func getComposition(): Option<PAGComposition> {
        if (this.filePath != "") {
            return None
        }
        return this.composition
    }

    /**
     * Sets a new PAGComposition to the PAGImageView with the maxFrameRate set to 30 fps. Note: If
     * the composition is already added to another PAGImageView, it will be removed from the
     * previous PAGImageView.
     */
    public func setComposition(composition: Option<PAGComposition>, maxFrameRate!: Float64 = 30.0): Unit {
        this.filePath = ""
        this.composition = composition

        unsafe {
            if (let Some(v) <- composition) {
                let native: Int64 = v.getNativeComposition()
                cj_PAGImageViewController_setComposition(cjImageView, native, maxFrameRate)
            }
        }
    }

    /**
     * Sets a new PAGComposition and the maxFrameRate limit to the PAGImageView. Note: If the
     * composition is already added to another PAGImageView, it will be removed from the previous
     * PAGImageView.
     */
    public func setComposition(composition: Int64, maxFrameRate!: Float64 = 30.0): Unit {
        this.filePath = ""
        unsafe {
            cj_PAGImageViewController_setComposition(cjImageView, composition, maxFrameRate)
        }
    }

    /**
     * The path string of a pag file set by setPath().
     */
    public func getPath(): String {
        return this.filePath
    }

    /**
     * Loads a pag file from the local path, returns false if the file does not exist or the data is not a pag file.
     * @param path
     * @returns
     */
    public func setPath(path: String, maxFrameRate!: Float64 = 30.0): Bool {
        this.filePath = path
        let file: Option<PAGFile> = PAGFile.LoadFromPath(path)

        unsafe {
            if (let Some(v) <- file) {
                this.composition = v
                let native: Int64 = v.getNativeComposition()
                cj_PAGImageViewController_setComposition(cjImageView, native, maxFrameRate)
                return true
            }
            this.composition = None
            return false
        }
    }

    /**
     * 从特定路径异步加载pag文件，该路径可以是网络路径或本地路径。
     * @param path
     * @returns
     */
    /*
    func setPathAsync(path: String, maxFrameRate!: Float64 = 30.0): Future<PAGFile> {
        this.filePath = path

        let fut: Future<PAGFile> = spawn { =>
            let futPAGFile: Future<PAGFile> = PAGFile.LoadFromPathAsync(path)
            let pagFile: PAGFile = futPAGFile.get()
            this.composition = pagFile

            unsafe {
                //this.cjImageView.setComposition(pagFile?.getNativeComposition(), maxFrameRate)
                let native: Int64 = pagFile.getNativeComposition()
                cj_PAGImageViewController_setComposition(cjImageView, native, maxFrameRate)
            }
            return pagFile
        }
        return fut
    }
     */

  /**
   * Returns the current scale mode.
   */
    public func scaleMode(): Int32 {
        unsafe {
            return cj_PAGImageViewController_scaleMode(cjImageView)
        }
    }

  /**
   * Specifies the rule of how to scale the pag content to fit the PAGImageView's size. The
   * current matrix of the PAGImageView changes when this method is called.
   */
    public func setScaleMode(scaleMode: Int32): Unit {
        unsafe {
            cj_PAGImageViewController_setScaleMode(cjImageView, scaleMode)
        }
    }

  /**
   * Returns a copy of the current matrix.
   */
    public func matrix(): Matrix4 {
        unsafe {
            let res: CJFloat32Array = cj_PAGImageViewController_matrix(cjImageView)
            let size: Int64 = res.size
            let buf: CPointer<Float32> = res.buf
            let bytes: Array<Float32> = Array<Float32>(size, repeat: 0.0)
            for (i in 0..size) {
                bytes[i] = (buf + i).read()
            }
            free_CPointer_Float32(buf)

            //如果 bytes 返回的结果是 长度为9的0.0的数组，则有可能传入的参数 bytes(VArray<Float32, $9>) 无效。需要换成 CPointer<UInt8>。
            return PAGUtils.ToTsMatrix(bytes)
        }
    }

    public func matrixToArray(): Array<Float32> {
        unsafe {
            let res: CJFloat32Array = cj_PAGImageViewController_matrix(cjImageView)
            let size: Int64 = res.size
            let buf: CPointer<Float32> = res.buf
            let bytes: Array<Float32> = Array<Float32>(size, repeat: 0.0)
            for (i in 0..size) {
                bytes[i] = (buf + i).read()
            }
            free_CPointer_Float32(buf)

            return bytes
        }
    }

  /**
   * Sets the transformation which will be applied to the composition. The scaleMode property
   * will be set to PAGScaleMode::None when this method is called.
   */
    public func setMatrix(matrix: Matrix4): Unit {
        unsafe {
            let buf: Array<Float32> = PAGUtils.ToNativeMatrix(matrix)
            let handle = acquireArrayRawData(buf)
            cj_PAGImageViewController_setMatrix(cjImageView, handle.pointer)
            releaseArrayRawData(handle)
        }
    }

    public func setMatrix(buf: Array<Float32>): Unit {
        unsafe {
            let handle = acquireArrayRawData(buf)
            cj_PAGImageViewController_setMatrix(cjImageView, handle.pointer)
            releaseArrayRawData(handle)
        }
    }

  /**
   * This value defines the scale factor for the size of the cached image frames, which ranges
   * from 0.0 to 1.0. A scale factor less than 1.0 may result in blurred output, but it can reduce
   * graphics memory usage, increasing the rendering performance. The default value is 1.0.
   */
    public func renderScale(): Float64 {
        unsafe {
            return cj_PAGImageViewController_renderScale(cjImageView)
        }
    }

  /**
   * Sets the value of the renderScale property.
   */
    public func setRenderScale(renderScale: Float64): Unit {
        unsafe {
            cj_PAGImageViewController_setRenderScale(cjImageView, renderScale)
        }
    }

  /**
   * If set to true, the PAGImageView loads all image frames into the memory, which will
   * significantly increase the rendering performance but may cost lots of additional memory. Set
   * it to true if you prefer rendering speed over memory usage. If set to false, the PAGImageView
   * loads only one image frame at a time into the memory. The default value is false.
   */
    public func cacheAllFramesInMemory(): Bool {
        unsafe {
            return cj_PAGImageViewController_cacheAllFramesInMemory(cjImageView)
        }
    }

  /**
   * Sets the value of the cacheAllFramesInMemory property.
   */
    public func setCacheAllFramesInMemory(enable: Bool): Unit {
        unsafe {
            cj_PAGImageViewController_setCacheAllFramesInMemory(cjImageView, enable)
        }
    }

  /**
   * Returns the current frame index the PAGImageView is rendering.
   */
    public func currentFrame(): Float64 {
        unsafe {
            return cj_PAGImageViewController_currentFrame(cjImageView)
        }
    }

  /**
   * Sets the frame index for the PAGImageView to render.
   */
    public func setCurrentFrame(currentFrame: Float64): Unit {
        unsafe {
            cj_PAGImageViewController_setCurrentFrame(cjImageView, currentFrame)
        }
    }

  /**
   * Returns a PixelMap capturing the contents of the current PAGImageView.
   */
    public func currentImage(): Option<PixelMap> {
        unsafe {
            let res: CJPixelMap = cj_PAGImageViewController_currentImage(cjImageView)
            let size: Int64 = res.size
            let buf: CPointer<UInt8> = res.buf
            if (size <= 0 || buf.isNull()) {
                return None
            }

            //InitializationOptions
            var alphaType: AlphaType = getAlphaType(res.alphaType) //!: AlphaType = AlphaType.UNKNOWN,
            var editable: Bool = res.editable                      //= false,
            var pixelFormat: PixelMapFormat = getPixelMapFormat(res.pixelFormat) //!: PixelMapFormat = PixelMapFormat.UNKNOWN,

            var height: Int32 = res.height
            var width: Int32 = res.width

            let bytes: Array<Byte> = Array<Byte>(size, repeat: 0)
            for (i in 0..size) {
                bytes[i] = buf.read(i)
            }
            free_CPointer_UInt8(buf)

            let opts: InitializationOptions = InitializationOptions(
                alphaType: alphaType,
                editable: editable,
                pixelFormat: pixelFormat,
                size: Size(height: height, width: width)
            )
            let pixelMap: PixelMap = createPixelMap(bytes, opts)

            return pixelMap
        }
    }

  /**
   * Starts to play the animation from the current position. Calling the play() method when the
   * animation is already playing has no effect. The play() method does not alter the animation's
   * current position. However, if the animation previously reached its end, it will restart from
   * the beginning.
   */
    public func play(): Unit {
        unsafe {
            cj_PAGImageViewController_play(cjImageView)
        }
    }

  /**
   * Indicates whether the animation is playing.
   */
    public func isPlaying(): Bool {
        unsafe {
            return cj_PAGImageViewController_isPlaying(cjImageView)
        }
    }

  /**
   * Cancels the animation at the current position. Calling the play() method can resume the
   * animation from the last paused position.
   */
    public func pause(): Unit {
        unsafe {
            cj_PAGImageViewController_pause(cjImageView)
        }
    }

  /**
   * The total number of times the animation is set to play. The default is 1, which means the
   * animation will play only once. If the repeat count is set to 0 or a negative value, the
   * animation will play infinity times.
   */
    public func repeatCount(): Int64 {
        unsafe {
            return cj_PAGImageViewController_repeatCount(cjImageView)
        }
    }

  /**
   * Set the number of times the animation to play.
   */
    public func setRepeatCount(repeatCount: Int64): Unit {
        unsafe {
            cj_PAGImageViewController_setRepeatCount(cjImageView, repeatCount)
        }
    }

  /**
   * Adds a listener to the set of listeners that are sent events through the life of an
   * animation, such as start, repeat, and end.
   */
    public func addListener(listener: PAGImageViewListener): Unit {
        this.listeners.add(listener)
    }

  /**
   * Removes a listener from the set listening to this animation.
   */
    public func removeListener(listener: PAGImageViewListener): Unit {
        for (i in 0..this.listeners.size) {
            if (refEq(this.listeners[i], listener)) {
                this.listeners.remove(at: i)
            }
        }
    }

  /**
   * Renders the current image frame immediately. Note that all the changes previously made to the
   * PAGImageView will only take effect after this method is called. If the play() method is
   * already called, there is no need to call it manually since it will be automatically called
   * every frame. Returns true if the content has changed.
   */
    public func flush(): Bool {
        unsafe {
            return cj_PAGImageViewController_flush(cjImageView)
        }
    }

    public func uniqueID(): String {
        unsafe {
            let retC: CString = cj_PAGImageViewController_uniqueID(cjImageView)
            let ret = retC.toString()
            LibC.free(retC)
            return ret
        }
    }

    public func update(): Unit {
        unsafe {
            return cj_PAGImageViewController_update(cjImageView)
        }
    }

    public func constructor(): Unit {
        //TODO: 需要把函数传入 C++ 中？？？
    }

    private func onAnimationStart(): Unit {
        for (listener in this.listeners) {
            if (let Some(v) <- listener.onAnimationStart) {
                v(this)
            }
        }
    }

    private func onAnimationEnd(): Unit {
        for (listener in this.listeners) {
            if (let Some(v) <- listener.onAnimationEnd) {
                v(this)
            }
        }
    }

    private func onAnimationCancel(): Unit {
        for (listener in this.listeners) {
            if (let Some(v) <- listener.onAnimationCancel) {
                v(this)
            }
        }
    }

    private func onAnimationRepeat(): Unit {
        for (listener in this.listeners) {
            if (let Some(v) <- listener.onAnimationRepeat) {
                v(this)
            }
        }
    }

    public func attachToView(view: PAGImageView) {
        if (let Some(v) <- this.view) {
            if (!refEq(v, view)) {
                Hilog.error(0, "PAGImageView", "[attachToView]-controller has attached to view.")
            }
        }
        this.view = view
    }

    public func detachFromView(): Unit {
        this.view = None
    }

    private func onAnimatorProgressUpdate(): Unit {
        for (listener in this.listeners) {
            if (let Some(v) <- listener.onAnimationUpdate) {
                v(this)
            }
        }
    }
}
