/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package libpag4cj

import std.convert.*
import std.sync.*
import ohos.net.http.*

@FastNative
foreign {
    func cj_PAGImageViewController_createPAGImageView(): Int64

    func cj_PAGImageViewController_setComposition(cjImageView: Int64, native: Int64, maxFrameRate: Float64, isNull: Bool): Unit

    func cj_PAGImageViewController_scaleMode(cjImageView: Int64): Int32

    func cj_PAGImageViewController_setScaleMode(cjImageView: Int64, scaleMode: Int32): Unit

    func cj_PAGImageViewController_matrix(cjImageView: Int64): CJFloat32Array

    func cj_PAGImageViewController_setMatrix(cjImageView: Int64, bytes: CPointer<Float32>): Unit

    func cj_PAGImageViewController_renderScale(cjImageView: Int64): Float32

    func cj_PAGImageViewController_setRenderScale(cjImageView: Int64, renderScale: Float32): Unit

    func cj_PAGImageViewController_cacheAllFramesInMemory(cjImageView: Int64): Bool

    func cj_PAGImageViewController_setCacheAllFramesInMemory(cjImageView: Int64, enable: Bool): Unit

    func cj_PAGImageViewController_currentFrame(cjImageView: Int64): Int64

    func cj_PAGImageViewController_setCurrentFrame(cjImageView: Int64, currentFrame: Int64): Unit

    func cj_PAGImageViewController_currentImage(cjImageView: Int64): CJPixelMap

    func cj_PAGImageViewController_play(cjImageView: Int64): Unit

    func cj_PAGImageViewController_isPlaying(cjImageView: Int64): Bool

    func cj_PAGImageViewController_pause(cjImageView: Int64): Unit

    func cj_PAGImageViewController_repeatCount(cjImageView: Int64): Int64

    func cj_PAGImageViewController_setRepeatCount(cjImageView: Int64, repeatCount: Int64): Unit

    func cj_PAGImageViewController_flush(cjImageView: Int64): Bool

    func cj_PAGImageViewController_uniqueID(cjImageView: Int64): CJBytesArray

    func cj_PAGImageViewController_update(cjImageView: Int64): Unit

    func cj_PAGImageViewController_SetSurfaceId(cjImageView: Int64, surfaceId: Int64): Unit

    func cj_PAGImageViewController_ChangeSurface(cjImageView: Int64): Unit

    func cj_PAGImageViewController_onAnimatorStateChange(cjImageView: Int64, cb: CFunc<(UInt8, Int64) -> Unit>): Unit

    func cj_PAGImageViewController_onAnimatorProgress(cjImageView: Int64, cb: CFunc<(Int64) -> Unit>): Unit

    func cj_PAGImageViewController_release(cjImageView: Int64): Unit

    func cj_PAGImageViewController_destroyJPAGImageView(id: CString): Unit

    func cj_PAGImageViewController_matrixFromArray(cjImageView: Int64, values: VArray<Float32, $9>): Unit

    func cj_PAGImageViewController_setMatrixFromArray(cjImageView: Int64, values: VArray<Float32, $9>): Unit
}

/**
 * Implementation of the IPAGImageViewListener interface.
 * This class allows clients to provide custom behavior for animation lifecycle callbacks
 */
public class PAGImageViewListener <: IPAGImageViewListener {
    private var onAnimationStartImpl: (PAGImageViewController) -> Unit
    private var onAnimationEndImpl: (PAGImageViewController) -> Unit
    private var onAnimationRepeatImpl: (PAGImageViewController) -> Unit
    private var onAnimationCancelImpl: (PAGImageViewController) -> Unit
    private var onAnimationUpdateImpl: (PAGImageViewController) -> Unit
    public init(
        onAnimationStart!: (PAGImageViewController) -> Unit,
        onAnimationEnd!: (PAGImageViewController) -> Unit,
        onAnimationRepeat!: (PAGImageViewController) -> Unit,
        onAnimationCancel!: (PAGImageViewController) -> Unit,
        onAnimationUpdate!: (PAGImageViewController) -> Unit
    ) {
        this.onAnimationStartImpl = onAnimationStart
        this.onAnimationEndImpl = onAnimationEnd
        this.onAnimationRepeatImpl = onAnimationRepeat
        this.onAnimationCancelImpl = onAnimationCancel
        this.onAnimationUpdateImpl = onAnimationUpdate
    }

    /**
     * Notifies the beginning of the animation. It can be called from either the UI thread or the thread
     * that calls the play method.
     */
    public func onAnimationStart(imageViewController: PAGImageViewController): Unit {
        this.onAnimationStartImpl(imageViewController)
    }

    /**
     * Notifies the end of the animation. It can only be called from the UI thread.
     */
    public func onAnimationEnd(imageViewController: PAGImageViewController): Unit {
        this.onAnimationEndImpl(imageViewController)
    }

    /**
     * Notifies the repetition of the animation. It can only be called from the UI thread.
     */
    public func onAnimationRepeat(imageViewController: PAGImageViewController): Unit {
        this.onAnimationRepeatImpl(imageViewController)
    }

    /**
     * Notifies the cancellation of the animation. It can be called from either the UI thread or the
     * thread that calls the stop method.
     */
    public func onAnimationCancel(imageViewController: PAGImageViewController): Unit {
        this.onAnimationCancelImpl(imageViewController)
    }

    /**
     * Notifies another frame of the animation has occurred. It may be called from an arbitrary
     * thread if the animation is running asynchronously.
     */
    public func onAnimationUpdate(imageViewController: PAGImageViewController): Unit {
        this.onAnimationUpdateImpl(imageViewController)
    }
}

/**
 * Listener interface for receiving animation lifecycle events from a PAGImageViewController.
 */
public interface IPAGImageViewListener {
    func onAnimationStart(imageViewController: PAGImageViewController): Unit

    func onAnimationEnd(imageViewController: PAGImageViewController): Unit

    func onAnimationRepeat(imageViewController: PAGImageViewController): Unit

    func onAnimationCancel(imageViewController: PAGImageViewController): Unit

    func onAnimationUpdate(imageViewController: PAGImageViewController): Unit
}

protected var imageViewControllerMap: HashMap<Int64, Option<PAGImageViewController>> = HashMap<Int64, Option<PAGImageViewController>>(
)

/**
 * Animation state callback
 */
@C
func onImageViewStateChange(state: UInt8, imageView: Int64): Unit {
    if (imageViewControllerMap.contains(imageView)) {
        match (state) {
            case 0 => imageViewControllerMap[imageView].getOrThrow().onAnimationStart()
            case 1 => imageViewControllerMap[imageView].getOrThrow().onAnimationCancel()
            case 2 => imageViewControllerMap[imageView].getOrThrow().onAnimationEnd()
            case 3 => imageViewControllerMap[imageView].getOrThrow().onAnimationRepeat()
            case _ => ()
        }
    }
}

/**
 * Animation update callback
 */
@C
func onImageViewProgressUpdate(imageView: Int64): Unit {
    if (imageViewControllerMap.contains(imageView)) {
        imageViewControllerMap[imageView].getOrThrow().onAnimatorProgressUpdate()
    }
}

public class PAGImageViewController <: XComponentController {
    private var mt = Mutex()
    private var composition: Option<PAGComposition> = None
    private var filePath: String = ""
    private var listeners: ArrayList<PAGImageViewListener> = ArrayList<PAGImageViewListener>(4)
    private var view: Option<PAGImageView> = None
    // Binding with C code, the object pointer returned by C code.
    private var cjImageView: Int64 = 0
    private var id: String
    public init() {
        unsafe {
            cjImageView = cj_PAGImageViewController_createPAGImageView()
            cj_PAGImageViewController_onAnimatorStateChange(cjImageView, onImageViewStateChange)
            cj_PAGImageViewController_onAnimatorProgress(cjImageView, onImageViewProgressUpdate)
            let uniqueID: CJBytesArray = cj_PAGImageViewController_uniqueID(cjImageView)
            id = BytesArrayToString(uniqueID)
            free_CJBytesArray(uniqueID)
        }
    }

    protected override func onSurfaceCreated(surfaceId: String) {
        unsafe {
            cj_PAGImageViewController_SetSurfaceId(cjImageView, Int64.parse(surfaceId))
        }
    }

    protected override func onSurfaceChanged(surfaceId: String, rect: SurfaceRect) {
        unsafe {
            cj_PAGImageViewController_ChangeSurface(cjImageView)
        }
    }

    /**
     * Returns the current PAGComposition in the PAGImageView. Returns null if the internal
     * composition was loaded from a pag file path.
     */
    public func getComposition(): Option<PAGComposition> {
        if (this.filePath == "") {
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
        if (this.composition.isNone() && composition.isNone()) {
            return
        } else {
            var native: Int64 = 0
            unsafe {
                if (let Some(v) <- composition) {
                    this.composition = composition
                    native = v.getNativeComposition()
                    cj_PAGImageViewController_setComposition(cjImageView, native, maxFrameRate, false)
                    return
                }
                if (let Some(v) <- this.composition) {
                    native = v.getNativeComposition()
                    cj_PAGImageViewController_setComposition(cjImageView, native, maxFrameRate, true)
                }
                this.composition = None
            }
        }
    }

    /**
     * Sets a new PAGComposition and the maxFrameRate limit to the PAGImageView. Note: If the
     * composition is already added to another PAGImageView, it will be removed from the previous
     * PAGImageView.
     */
    private func setComposition(composition: Int64, maxFrameRate!: Float64 = 30.0): Unit {
        this.filePath = ""
        unsafe {
            cj_PAGImageViewController_setComposition(cjImageView, composition, maxFrameRate, false)
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
        let file: Option<PAGFile> = PAGFile.LoadFromPath(path)
        if (let Some(v) <- file) {
            setComposition(v, maxFrameRate: maxFrameRate)
            this.filePath = path
            return true
        } else {
            setComposition(Option<PAGComposition>.None)
            return false
        }
    }

    /**
     * Asynchronously load a pag file from the specific path which can be a network path or a local path.
     * @param path
     * @returns
     */
    public func setPathAsync(path: String, callback: (Option<PAGFile>) -> Unit, maxFrameRate!: Float64 = 30.0): Unit {
        unsafe {
            if (PAGFile.IsNetWorkPath(path)) {
                let cacheData: Array<UInt8> = PAGDiskCache.readFile(path)
                if (cacheData.size > 0) {
                    let file: Option<PAGFile> = PAGFile.LoadFromBytes(cacheData)
                    if (let Some(v) <- file) {
                        setComposition(v, maxFrameRate: maxFrameRate)
                        this.filePath = path
                        callback(v)
                        return
                    }
                    setComposition(Option<PAGComposition>.None)
                    callback(Option<PAGFile>.None)
                } else {
                    let httpRequest = createHttp()
                    let option = HttpRequestOptions(
                        method: RequestMethod.GET,
                        expectDataType: HttpDataType.ARRAY_BUFFER
                    )
                    httpRequest.request(
                        path,
                        {
                            err, resp =>
                            if (let Some(e) <- err) {
                                Hilog.error(0, "PAGImageViewController", "setPathAsync httpRequest error:${e.message}")
                            }
                            if (let Some(r) <- resp) {
                                if (r.responseCode.getValue() == ResponseCode.OK.getValue()) {
                                    match (r.result) {
                                        case HttpData.STRING_DATA(str) => ()
                                        case HttpData.ARRAY_DATA(bytes) =>
                                            let file: Option<PAGFile> = PAGFile.LoadFromBytes(bytes)
                                            if (let Some(v) <- file) {
                                                setComposition(v, maxFrameRate: maxFrameRate)
                                                this.filePath = path
                                                callback(v)
                                                httpRequest.destroy()
                                                return
                                            }
                                        case _ => ()
                                    }
                                }
                            }
                            setComposition(Option<PAGComposition>.None)
                            callback(Option<PAGFile>.None)
                            httpRequest.destroy()
                        },
                        options: option
                    )
                }
            } else {
                var pagfile = PAGFile.LoadFromPath(path)
                if (let Some(v) <- pagfile) {
                    setComposition(v, maxFrameRate: maxFrameRate)
                    this.filePath = path
                    callback(v)
                    return
                }
                setComposition(Option<PAGComposition>.None)
                callback(Option<PAGFile>.None)
            }
        }
    }

    /**
     * Returns the current scale mode.
     */
    public func scaleMode(): PAGScaleMode {
        unsafe {
            let mode = cj_PAGImageViewController_scaleMode(cjImageView)
            return PAGScaleMode.int32ToMode(mode)
        }
    }

    /**
     * Specifies the rule of how to scale the pag content to fit the PAGImageView's size. The
     * current matrix of the PAGImageView changes when this method is called.
     */
    public func setScaleMode(mode: PAGScaleMode): Unit {
        var value = PAGScaleMode.modeToInt32(mode)
        unsafe {
            cj_PAGImageViewController_setScaleMode(cjImageView, value)
        }
    }

    private func matrixToMatrix4(): Matrix4 {
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

    /**
     * Returns a copy of the current matrix.
     */
    public func matrix(): Array<Float32> {
        unsafe {
            var values = VArray<Float32, $9>({i => 0.0})
            cj_PAGImageViewController_matrixFromArray(cjImageView, inout values)
            var data: Array<Float32> = Array<Float32>(6, repeat: 0.0)
            for (i in 0..6) {
                data[i] = values[i]
            }
            return data
        }
    }

    /**
     * Sets the transformation which will be applied to the composition. The scaleMode property
     * will be set to PAGScaleMode::None when this method is called.
     */
    private func setMatrixFormMatrix4(matrix: Matrix4): Unit {
        unsafe {
            let buf: Array<Float32> = PAGUtils.ToNativeMatrix(matrix)
            let handle = acquireArrayRawData(buf)
            cj_PAGImageViewController_setMatrix(cjImageView, handle.pointer)
            releaseArrayRawData(handle)
        }
    }

    public func setMatrix(values: Array<Float32>): Unit {
        if (values.size == 0) {
            Hilog.error(0, 'PAGImageViewController', "setMatrix invalid setting");
            return
        }
        unsafe {
            var data: VArray<Float32, $9> = VArray<Float32, $9>({i => 0.0})
            for (i in 0..values.size) {
                if (i > 5) {
                    break
                }
                data[i] = values[i]
            }
            cj_PAGImageViewController_setMatrixFromArray(cjImageView, inout data)
        }
    }

    /**
     * This value defines the scale factor for the size of the cached image frames, which ranges
     * from 0.0 to 1.0. A scale factor less than 1.0 may result in blurred output, but it can reduce
     * graphics memory usage, increasing the rendering performance. The default value is 1.0.
     */
    public func renderScale(): Float32 {
        unsafe {
            return cj_PAGImageViewController_renderScale(cjImageView)
        }
    }

    /**
     * Sets the value of the renderScale property.
     */
    public func setRenderScale(renderScale: Float32): Unit {
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
    public func currentFrame(): Int64 {
        unsafe {
            return cj_PAGImageViewController_currentFrame(cjImageView)
        }
    }

    /**
     * Sets the frame index for the PAGImageView to render.
     */
    public func setCurrentFrame(currentFrame: Int64): Unit {
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
            var alphaType: AlphaType = getAlphaType(res.alphaType)
            var editable: Bool = res.editable
            var pixelFormat: PixelMapFormat = getPixelMapFormat(res.pixelFormat)
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
        synchronized(mt) {
            listeners.add(listener)
        }
    }

    /**
     * Removes a listener from the set listening to this animation.
     */
    public func removeListener(listener: PAGImageViewListener): Unit {
        synchronized(mt) {
            listeners.removeValue(listener)
        }
    }

    /**
     * Renders the current image frame immediately. Note that all the changes previously made to the
     * PAGImageView will only take effect after this method is called. If the play() method is
     * already called, there is no need to call it manually since it will be automatically called
     * every frame. Returns true if the content has changed.
     */
    private func flush(): Bool {
        unsafe {
            return cj_PAGImageViewController_flush(cjImageView)
        }
    }

    public func uniqueID(): String {
        unsafe {
            if (cjImageView == 0) {
                return ""
            }
            let res: CJBytesArray = cj_PAGImageViewController_uniqueID(cjImageView)
            id = BytesArrayToString(res)
            free_CJBytesArray(res)
            return id
        }
    }

    public func update(): Unit {
        unsafe {
            return cj_PAGImageViewController_update(cjImageView)
        }
    }

    /**
     * Free up resources used by the PAGImageViewController instance immediately instead of relying on the
     * garbage collector to do this for you at some point in the future.
     */
    public func releaseAll(): Unit {
        unsafe {
            cj_PAGImageViewController_release(cjImageView)
            cjImageView = 0
            if (id != "") {
                let p = LibC.mallocCString(id)
                cj_PAGImageViewController_destroyJPAGImageView(p)
                LibC.free(p)
                id = ""
            }
            setComposition(Option<PAGComposition>.None)
        }
    }
    protected func onAnimationStart(): Unit {
        synchronized(mt) {
            for (listener in this.listeners) {
                listener.onAnimationStart(this)
            }
        }
    }

    protected func onAnimationEnd(): Unit {
        synchronized(mt) {
            for (listener in this.listeners) {
                listener.onAnimationEnd(this)
            }
        }
    }

    protected func onAnimationCancel(): Unit {
        synchronized(mt) {
            for (listener in this.listeners) {
                listener.onAnimationCancel(this)
            }
        }
    }

    protected func onAnimationRepeat(): Unit {
        synchronized(mt) {
            for (listener in this.listeners) {
                listener.onAnimationRepeat(this)
            }
        }
    }

    protected func attachToView(cjImageView: Int64) {
        if (this.cjImageView != 0 && this.cjImageView != cjImageView) {
            Hilog.error(0, 'PAGImageViewController', "attachToView controller has attached to view");
        }
        this.cjImageView = cjImageView
    }

    protected func detachFromView() {
        unsafe {
            let p = LibC.mallocCString(id)
            cj_PAGViewController_destroyJPAGView(p)
            LibC.free(p)
        }
        this.listeners.clear()
        this.cjImageView = 0
    }

    protected func onAnimatorProgressUpdate(): Unit {
        synchronized(mt) {
            for (listener in this.listeners) {
                listener.onAnimationUpdate(this)
            }
        }
    }

    protected func getImageView(): Int64 {
        return this.cjImageView
    }
}
