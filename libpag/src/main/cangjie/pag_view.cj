/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package libpag4cj

import ohos.state_macro_manage.*
import std.convert.*
import std.sync.*
import ohos.net.http.*

/**
 * Compares two objects.
 * @param a The first object.
 * @param b The second object.
 * @return Whether the two objects are equal. Returns true if they are equal, false otherwise.
 * @throws UnsupportedException Thrown when the types of a or b are incorrect.
 */
public func equals<T>(a: T, b: T): Bool {
    match ((a, b)) {
        case (a: Equatable<T>, _: Equatable<T>) => a == b
        case (a: Object, b: Object) => refEq(a, b)
        case _ => throw UnsupportedException("${a as ToString} ${b as ToString}")
    }
}

/*
 * ArrayList utility interface
 */
public interface ArrayListExt<T> {
    /**
     * Removes the first matching value.
     * @param v The value to match and remove.
     * @return Whether the removal was successful.
     */
    func removeValue(v: T): Bool
}

/*
 * Extend ArrayList
 */
extend<T> ArrayList<T> <: ArrayListExt<T> {
    /**
     * Removes the first matching value.
     * @param v The value to be matched.
     * @return Whether the value was successfully removed.
     */
    public func removeValue(v: T): Bool {
        for (i in 0..this.size) {
            if (equals(this[i], v)) {
                this.remove(at: i)
                return true
            }
        }
        return false
    }
}

/**
 * Implementation of the IPAGViewListener interface.
 * This class allows clients to provide custom behavior for animation lifecycle callbacks
 */
public class PAGViewListener <: IPAGViewListener {
    private var onAnimationStartImpl: (PAGViewController) -> Unit
    private var onAnimationEndImpl: (PAGViewController) -> Unit
    private var onAnimationRepeatImpl: (PAGViewController) -> Unit
    private var onAnimationCancelImpl: (PAGViewController) -> Unit
    private var onAnimationUpdateImpl: (PAGViewController) -> Unit
    public init(
        onAnimationStart!: (PAGViewController) -> Unit,
        onAnimationEnd!: (PAGViewController) -> Unit,
        onAnimationRepeat!: (PAGViewController) -> Unit,
        onAnimationCancel!: (PAGViewController) -> Unit,
        onAnimationUpdate!: (PAGViewController) -> Unit
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
    public func onAnimationStart(viewController: PAGViewController): Unit {
        this.onAnimationStartImpl(viewController)
    }

    /**
     * Notifies the end of the animation. It can only be called from the UI thread.
     */
    public func onAnimationEnd(viewController: PAGViewController): Unit {
        this.onAnimationEndImpl(viewController)
    }

    /**
     * Notifies the repetition of the animation. It can only be called from the UI thread.
     */
    public func onAnimationRepeat(viewController: PAGViewController): Unit {
        this.onAnimationRepeatImpl(viewController)
    }

    /**
     * Notifies the cancellation of the animation. It can be called from either the UI thread or the
     * thread that calls the stop method.
     */
    public func onAnimationCancel(viewController: PAGViewController): Unit {
        this.onAnimationCancelImpl(viewController)
    }

    /**
     * Notifies another frame of the animation has occurred. It may be called from an arbitrary
     * thread if the animation is running asynchronously.
     */
    public func onAnimationUpdate(viewController: PAGViewController): Unit {
        this.onAnimationUpdateImpl(viewController)
    }
}

/**
 * Listener interface for receiving animation lifecycle events from a PAGViewController.
 */
protected interface IPAGViewListener {
    func onAnimationStart(viewController: PAGViewController): Unit

    func onAnimationEnd(viewController: PAGViewController): Unit

    func onAnimationRepeat(viewController: PAGViewController): Unit

    func onAnimationCancel(viewController: PAGViewController): Unit

    func onAnimationUpdate(viewController: PAGViewController): Unit
}

@FastNative
foreign {
    func cj_PAGViewController_createJPAGView(): Int64

    func cj_PAGViewController_destroyJPAGView(jView: CString): Unit

    func cj_PAGViewController_setComposition(jView: Int64, ptrComposition: Int64, isNull: Bool): Unit

    func cj_PAGViewController_play(jView: Int64): Unit

    func cj_PAGViewController_uniqueID(jView: Int64): CJBytesArray

    func cj_PAGViewController_update(jView: Int64): Unit

    func cj_PAGViewController_pause(jView: Int64): Unit

    func cj_PAGViewController_isPlaying(jView: Int64): Bool

    func cj_PAGViewController_isSync(jView: Int64): Bool

    func cj_PAGViewController_setSync(jView: Int64, isSync: Bool): Unit

    func cj_PAGViewController_repeatCount(jView: Int64): Int32

    func cj_PAGViewController_setRepeatCount(jView: Int64, repeatCount: Int32): Unit

    func cj_PAGViewController_videoEnabled(jView: Int64): Bool

    func cj_PAGViewController_setVideoEnabled(jView: Int64, enable: Bool): Unit

    func cj_PAGViewController_cacheEnabled(jView: Int64): Bool

    func cj_PAGViewController_setCacheEnabled(jView: Int64, enable: Bool): Unit

    func cj_PAGViewController_useDiskCache(jView: Int64): Bool

    func cj_PAGViewController_setUseDiskCache(jView: Int64, value: Bool): Unit

    func cj_PAGViewController_cacheScale(jView: Int64): Float32

    func cj_PAGViewController_setCacheScale(jView: Int64, value: Float32): Unit

    func cj_PAGViewController_maxFrameRate(jView: Int64): Float32

    func cj_PAGViewController_setMaxFrameRate(jView: Int64, value: Float32): Unit

    func cj_PAGViewController_scaleMode(jView: Int64): Int32

    func cj_PAGViewController_setScaleMode(jView: Int64, value: Int32): Unit

    func cj_PAGViewController_matrix(jView: Int64, values: VArray<Float32, $9>): Unit

    func cj_PAGViewController_setMatrix(jView: Int64, values: VArray<Float32, $9>): Unit

    func cj_PAGViewController_duration(jView: Int64): Int64

    func cj_PAGViewController_getProgress(jView: Int64): Float64

    func cj_PAGViewController_setProgress(jView: Int64, value: Float64): Unit

    func cj_PAGViewController_currentFrame(jView: Int64): Int32

    func cj_PAGViewController_flush(jView: Int64): Bool

    func cj_PAGViewController_freeCache(jView: Int64): Unit

    func cj_PAGViewController_SetSurfaceId(jView: Int64, surfaceId: Int64): Unit

    func cj_PAGViewController_ChangeSurface(jView: Int64): Unit

    func cj_PAGViewController_onAnimatorStateChange(jView: Int64, cb: CFunc<(UInt8, Int64) -> Unit>): Unit

    func cj_PAGViewController_onAnimatorProgress(jView: Int64, cb: CFunc<(Int64) -> Unit>): Unit

    func cj_PAGViewController_release(jView: Int64): Unit

    func cj_PAGViewController_getLayersUnderPoint(jView: Int64, localX: Float32, localY: Float32): CJInt64Array

    func cj_PAGViewController_getBounds(jView: Int64, ptrCJPAGLayerHandle: Int64, values: VArray<Float32, $4>): Unit

    func cj_PAGViewController_makeSnapshot(ptrCJPAGSurface: Int64): CJPixelMap
}

private var controllerMap: HashMap<Int64, Option<PAGViewController>> = HashMap<Int64, Option<PAGViewController>>()

/**
 * Animation state callback
 */
@C
func onStateChange(state: UInt8, jView: Int64): Unit {
    if (controllerMap.contains(jView)) {
        match (state) {
            case 0 => controllerMap[jView].getOrThrow().onAnimationStart()
            case 1 => controllerMap[jView].getOrThrow().onAnimationCancel()
            case 2 => controllerMap[jView].getOrThrow().onAnimationEnd()
            case 3 => controllerMap[jView].getOrThrow().onAnimationRepeat()
            case _ => ()
        }
    }
}

/**
 * Animation update callback
 */
@C
func onProgressUpdate(jView: Int64): Unit {
    if (controllerMap.contains(jView)) {
        if (let Some(v) <- controllerMap[jView]) {
            v.onAnimatorProgressUpdate()
        }
    }
}

/**
 * Enum representing the possible states of a PAG animation
 */
public enum PAGAnimatorState {
    | Start
    | Cancel
    | End
    | Repeat
    | NONE
}

/**
 * PAGView Controller
 */
public class PAGViewController <: XComponentController {
    private var mt = Mutex()
    private var id: String
    private var jView: Int64 = 0
    private var filePath: String = ''
    private var composition: Option<PAGComposition> = None
    private var listeners: ArrayList<PAGViewListener> = ArrayList<PAGViewListener>()

    public init() {
        unsafe {
            jView = cj_PAGViewController_createJPAGView()
            cj_PAGViewController_onAnimatorStateChange(jView, onStateChange)
            cj_PAGViewController_onAnimatorProgress(jView, onProgressUpdate)
            let res: CJBytesArray = cj_PAGViewController_uniqueID(jView)
            id = BytesArrayToString(res)
            free_CJBytesArray(res)
        }
    }

    protected func getView(): Int64 {
        return this.jView
    }

    protected override func onSurfaceCreated(surfaceId: String) {
        unsafe {
            cj_PAGViewController_SetSurfaceId(jView, Int64.parse(surfaceId))
        }
    }

    protected override func onSurfaceChanged(surfaceId: String, rect: SurfaceRect) {
        unsafe {
            cj_PAGViewController_ChangeSurface(jView)
        }
    }

    /**
     * Sets a new PAGComposition for PAGView to render as content. Note that if the composition is
     * already added to another PAGView, it will be removed from the previous PAGView.
     */
    public func setComposition(composition: Option<PAGComposition>): Unit {
        this.filePath = ''
        if (this.composition.isNone() && composition.isNone()) {
            return
        } else {
            var native: Int64 = 0
            unsafe {
                if (let Some(v) <- composition) {
                    this.composition = composition
                    native = v.getNativeComposition()
                    cj_PAGViewController_setComposition(jView, native, false)
                    return
                }
                if (let Some(v) <- this.composition) {
                    native = v.getNativeComposition()
                    cj_PAGViewController_setComposition(jView, native, true)
                }
                this.composition = None
            }
            return
        }
    }

    /*
     * Returns the current PAGComposition for PAGView to render as content.
     */
    public func getComposition(): Option<PAGComposition> {
        return this.composition;
    }

    /*
     * The path string of a pag file set by setPath().
     */
    public func getPath(): String {
        return filePath
    }

    /**
     * Loads a pag file from the local path, returns false if the file does not exist or the data is not a pag file.
     */
    public func setPath(path: String): Bool {
        let file: Option<PAGFile> = PAGFile.LoadFromPath(path)
        if (let Some(v) <- file) {
            setComposition(v)
            this.filePath = path
            return true
        } else {
            setComposition(Option<PAGComposition>.None)
            return false
        }
    }

    /**
     * Asynchronously load a pag file from the specific path which can be a network path or a local path.
     */
    public func setPathAsync(path: String, callback: (Option<PAGFile>) -> Unit): Unit {
        unsafe {
            if (PAGFile.IsNetWorkPath(path)) {
                let cacheData: Array<UInt8> = PAGDiskCache.readFile(path)
                if (cacheData.size > 0) {
                    let file: Option<PAGFile> = PAGFile.LoadFromBytes(cacheData)
                    if (let Some(v) <- file) {
                        setComposition(v)
                        this.filePath = path
                        callback(v)
                    }
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
                                Hilog.error(0, "PAGViewController", "setPathAsync httpRequest error:${e.message}")
                            }
                            if (let Some(r) <- resp) {
                                if (r.responseCode.getValue() == ResponseCode.OK.getValue()) {
                                    match (r.result) {
                                        case HttpData.STRING_DATA(str) => ()
                                        case HttpData.ARRAY_DATA(bytes) =>
                                            let file: Option<PAGFile> = PAGFile.LoadFromBytes(bytes)
                                            if (let Some(v) <- file) {
                                                setComposition(v)
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
                    setComposition(v)
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
     * Starts to play the animation from the current position. Calling the play() method when the
     * animation is already playing has no effect. The play() method does not alter the animation's
     * current position. However, if the animation previously reached its end, it will restart from
     * the beginning.
     */
    public func play(): Unit {
        unsafe {
            cj_PAGViewController_play(jView)
            return
        }
    }

    /**
     * Cancels the animation at the current position. Calling the play() method can resume the
     * animation from the last paused position.
     */
    public func pause(): Unit {
        unsafe {
            cj_PAGViewController_pause(jView)
            return
        }
    }

    /*
     * Indicates whether the animation is playing.
     */
    public func isPlaying(): Bool {
        unsafe {
            return cj_PAGViewController_isPlaying(jView)
        }
    }

    /*
     * Returns true if PAGView is playing in the main thread. The default value is false.
     */
    public func isSync(): Bool {
        unsafe {
            return cj_PAGViewController_isSync(jView)
        }
    }

    /*
     * Sets the sync flag for the PAGView.
     */
    public func setSync(isSync: Bool): Unit {
        unsafe {
            return cj_PAGViewController_setSync(jView, isSync)
        }
    }

    /*
     * Set the number of times the animation to play.
     */
    public func setRepeatCount(repeatCount: Int32): Unit {
        unsafe {
            return cj_PAGViewController_setRepeatCount(jView, repeatCount)
        }
    }

    /**
     * The total number of times the animation is set to play. The default is 1, which means the
     * animation will play only once. If the repeat count is set to 0 or a negative value, the
     * animation will play infinity times.
     */
    public func repeatCount(): Int32 {
        unsafe {
            return cj_PAGViewController_repeatCount(jView)
        }
    }

    /*
     * If set to false, PAGView skips rendering for video composition.
     */
    public func videoEnabled(): Bool {
        unsafe {
            return cj_PAGViewController_videoEnabled(jView)
        }
    }

    /*
     * Sets the value of videoEnabled property.
     */
    public func setVideoEnabled(enable: Bool): Unit {
        unsafe {
            return cj_PAGViewController_setVideoEnabled(jView, enable)
        }
    }

    /**
     * If set to true, PAG renderer caches an internal bitmap representation of the static content
     * for each layer. This caching can increase performance for layers that contain complex vector
     * content. The execution speed can be significantly faster depending on the complexity of the
     * content, but it requires extra graphics memory. The default value is true.
     */
    public func cacheEnabled(): Bool {
        unsafe {
            return cj_PAGViewController_cacheEnabled(jView)
        }
    }

    /*
     * Sets the value of cacheEnabled property.
     */
    public func setCacheEnabled(enable: Bool): Unit {
        unsafe {
            return cj_PAGViewController_setCacheEnabled(jView, enable)
        }
    }

    /**
     * If set to true, PAG will cache the associated rendering data into a disk file, such as the
     * decoded image frames of video compositions. This can help reduce memory usage and improve
     * rendering performance.
     */
    public func useDiskCache(): Bool {
        unsafe {
            return cj_PAGViewController_useDiskCache(jView)
        }
    }

    /*
     * Set the value of useDiskCache property.
     */
    public func setUseDiskCache(value: Bool): Unit {
        unsafe {
            return cj_PAGViewController_setUseDiskCache(jView, value)
        }
    }

    /**
     * This value defines the scale factor for internal graphics caches, ranges from 0.0 to 1.0. The
     * scale factors less than 1.0 may result in blurred output, but it can reduce the usage of
     * graphics memory which leads to better performance. The default value is 1.0.
     */
    public func cacheScale(): Float32 {
        unsafe {
            return cj_PAGViewController_cacheScale(jView)
        }
    }

    /*
     * Sets the value of cacheScale property.
     */
    public func setCacheScale(value: Float32): Unit {
        unsafe {
            return cj_PAGViewController_setCacheScale(jView, value)
        }
    }

    /**
     * The maximum frame rate for rendering. If set to a value less than the actual frame rate from
     * PAGFile, it drops frames but increases performance. Otherwise, it has no effect. The default
     * value is 60.
     */
    public func maxFrameRate(): Float32 {
        unsafe {
            return cj_PAGViewController_maxFrameRate(jView)
        }
    }

    /*
     * Sets the maximum frame rate for rendering.
     */
    public func setMaxFrameRate(value: Float32): Unit {
        if (value <= 0.0) {
            Hilog.error(0, 'PAGViewController', "setMaxFrameRate value range needs to be greater than 0.0");
            return
        }
        unsafe {
            return cj_PAGViewController_setMaxFrameRate(jView, value)
        }
    }

    /*
     * Returns the current scale mode.
     */
    public func scaleMode(): PAGScaleMode {
        unsafe {
            let mode = cj_PAGViewController_scaleMode(jView)
            return PAGScaleMode.int32ToMode(mode)
        }
    }

    /**
     * Specifies the rule of how to scale the pag content to fit the surface size. The matrix
     * changes when this method is called.
     */
    public func setScaleMode(mode: PAGScaleMode): Unit {
        var value = PAGScaleMode.modeToInt32(mode)
        unsafe {
            cj_PAGViewController_setScaleMode(jView, value)
        }
    }

    /**
     * Returns a copy of current matrix.
     */
    public func matrix(): Array<Float32> {
        unsafe {
            var values = VArray<Float32, $9>({i => 0.0})
            cj_PAGViewController_matrix(jView, inout values)
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
    public func setMatrix(values: Array<Float32>): Unit {
        if (values.size == 0) {
            Hilog.error(0, 'PAGViewController', "setMatrix invalid setting");
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
            cj_PAGViewController_setMatrix(jView, inout data)
        }
    }

    /*
     * The duration of current composition in microseconds.
     */
    public func duration(): Int64 {
        unsafe {
            return cj_PAGViewController_duration(jView)
        }
    }

    /*
     * Returns the current progress of play position, the value is from 0.0 to 1.0.
     */
    public func getProgress(): Float64 {
        unsafe {
            return cj_PAGViewController_getProgress(jView)
        }
    }

    /**
     * Sets the progress of play position, the valid value is from 0.0 to 1.0.
     */
    public func setProgress(value: Float64): Unit {
        unsafe {
            return cj_PAGViewController_setProgress(jView, value)
        }
    }

    /*
     * Returns the current frame.
     */
    public func currentFrame(): Int32 {
        unsafe {
            return cj_PAGViewController_currentFrame(jView)
        }
    }

    /**
     * Call this method to render current position immediately. Note that all the changes previously
     * made to the PAGView will only take effect after this method is called. If the play() method
     * is already called, there is no need to call it manually since it will be automatically called
     * every frame. Returns true if the content has changed.
     */
    public func flush(): Bool {
        unsafe {
            return cj_PAGViewController_flush(jView)
        }
    }

    /**
     * Returns an array of layers that lie under the specified point. The point is in pixels not dp.
     */
    public func getLayersUnderPoint(x: Float32, y: Float32): Array<PAGLayer> {
        unsafe {
            let res: CJInt64Array = cj_PAGViewController_getLayersUnderPoint(jView, x, y)
            let size: Int64 = res.size
            let buf: CPointer<Int64> = res.buf
            let bytes: Array<Int64> = Array<Int64>(size, repeat: 0)
            for (i in 0..size) {
                if (buf.isNotNull()) {
                    bytes[i] = buf.read(i)
                }
            }
            free_CPointer_Int64(buf)
            return PAGUtils.WarpJPAGLayers(bytes)
        }
    }

    /**
     * Free the cache created by the pag view immediately. Can be called to reduce memory pressure.
     */
    public func freeCache(): Unit {
        unsafe {
            cj_PAGViewController_freeCache(jView)
            return
        }
    }

    /**
     * Returns a bitmap capturing the contents of the PAGView. Subsequent rendering of the
     * PAGView will not be captured. Returns null if the PAGView hasn't been presented yet.
     */
    public func makeSnapshot(): Option<PixelMap> {
        unsafe {
            let res: CJPixelMap = cj_PAGViewController_makeSnapshot(jView)
            return ConvertToPixelMap(res)
        }
    }

    /**
     * Returns a rectangle in pixels that defines the displaying area of the specified layer, which
     * is in the coordinate of the PAGView.
     */
    public func getBounds(layer: PAGLayer): Rect {
        unsafe {
            var values = VArray<Float32, $4>({i => 0.0})
            cj_PAGViewController_getBounds(jView, layer.getptr(), inout values)
            var data: Array<Float32> = Array<Float32>(4, repeat: 0.0)
            for (i in 0..data.size) {
                data[i] = values[i]
            }
            return PAGUtils.ToTsRect(data)
        }
    }

    /**
     * Adds a listener to the set of listeners that are sent events through the life of an
     * animation, such as start, repeat, and end.
     */
    public func addListener(listener: PAGViewListener): Unit {
        synchronized(mt) {
            listeners.add(listener)
            return
        }
    }

    /**
     * Removes a listener from the set listening to this animation.
     */
    public func removeListener(listener: PAGViewListener): Unit {
        synchronized(mt) {
            listeners.removeValue(listener)
            return
        }
    }

    protected func attachToView(jView: Int64) {
        if (this.jView != 0 && this.jView != jView) {
            Hilog.error(0, 'PAGViewController', "attachToView controller has attached to view");
        }
        this.jView = jView
    }

    protected func detachFromView() {
        unsafe {
            let p = LibC.mallocCString(id)
            cj_PAGViewController_destroyJPAGView(p)
            LibC.free(p)
        }
        this.listeners.clear()
        this.jView = 0
    }

    /**
     * Free up resources used by the PAGViewController instance immediately instead of relying on the
     * garbage collector to do this for you at some point in the future.
     */
    public func releaseAll(): Unit {
        unsafe {
            cj_PAGViewController_release(jView)
            jView = 0
            if (id != "") {
                let p = LibC.mallocCString(id)
                cj_PAGViewController_destroyJPAGView(p)
                LibC.free(p)
                id = ""
            }
            setComposition(Option<PAGComposition>.None)
        }
    }

    public func uniqueID(): String {
        unsafe {
            if (jView == 0) {
                return ""
            }
            let res: CJBytesArray = cj_PAGViewController_uniqueID(jView)
            id = BytesArrayToString(res)
            free_CJBytesArray(res)
            return id
        }
    }

    public func update(): Unit {
        unsafe {
            cj_PAGViewController_update(jView)
            return
        }
    }

    protected func onAnimationStart() {
        synchronized(mt) {
            for (listener in this.listeners) {
                listener.onAnimationStart(this)
            }
        }
    }

    protected func onAnimationEnd() {
        synchronized(mt) {
            for (listener in this.listeners) {
                listener.onAnimationEnd(this)
            }
        }
    }

    protected func onAnimationCancel() {
        synchronized(mt) {
            for (listener in this.listeners) {
                listener.onAnimationCancel(this)
            }
        }
    }

    protected func onAnimationRepeat() {
        synchronized(mt) {
            for (listener in this.listeners) {
                listener.onAnimationRepeat(this)
            }
        }
    }

    protected func onAnimatorProgressUpdate() {
        synchronized(mt) {
            for (listener in this.listeners) {
                listener.onAnimationUpdate(this)
            }
        }
    }
}

@Component
public class PAGView {
    var controller: PAGViewController

    func build() {
        Column() {
            XComponent(id: this.controller.uniqueID(), `type`: XComponentType.TEXTURE, controller: controller)
                .width(100.percent)
                .height(100.percent)
        }.width(100.percent).height(100.percent)
    }

    protected func aboutToAppear(): Unit {
        this.controller.attachToView(this.controller.getView())
        if (controllerMap.contains(this.controller.getView())) {
            controllerMap[this.controller.getView()] = this.controller
        } else {
            controllerMap.add(this.controller.getView(), this.controller)
        }
    }

    protected func aboutToDisappear() {
        if (controllerMap.contains(this.controller.getView())) {
            controllerMap.remove(this.controller.getView())
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
