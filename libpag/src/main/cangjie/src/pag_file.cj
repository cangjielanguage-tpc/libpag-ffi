/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package libpag4cj

import std.regex.*
import ohos.net.http.*

@FastNative
foreign {
    func cj_PAGFile_MaxSupportedTagLevel(): UInt32

    func cj_PAGFile_LoadFromPath(path: CString): Int64

    func cj_PAGFile_LoadFromBytes(bytes: CPointer<UInt8>, length: Int64, path: CString): Int64

    func cj_PAGFile_tagLevel(ptr: Int64): Int64

    func cj_PAGFile_numTexts(ptr: Int64): Int64

    func cj_PAGFile_numImages(ptr: Int64): Int64

    func cj_PAGFile_numVideos(ptr: Int64): Int64

    func cj_PAGFile_path(ptr: Int64): CJBytesArray

    func cj_PAGFile_getTextData(ptr: Int64, index: Int32): PAGTextData

    func cj_PAGFile_replaceText(ptr: Int64, index: Int32, data: PAGTextData): Unit

    func cj_PAGFile_replaceImage(ptrPAGFile: Int64, index: Int32, ptrPAGImage: Int64): Unit

    func cj_PAGFile_replaceImageByName(ptrPAGFile: Int64, layerName: CString, ptrPAGImage: Int64): Unit

    func cj_PAGFile_getLayersByEditableIndex(ptrPAGFile: Int64, index: Int32, layerType: Int8): CJInt64Array

    func cj_PAGFile_getEditableIndices(ptrPAGFile: Int64, layerType: Int8): CJInt64Array

    func cj_PAGFile_timeStretchMode(ptr: Int64): Int32

    func cj_PAGFile_setTimeStretchMode(ptr: Int64, mode: Int32): Unit

    func cj_PAGFile_setDuration(ptr: Int64, duration: Int64): Unit

    func cj_PAGFile_copyOriginal(ptr: Int64): Int64

    func cj_PAGFile_release(ptrCJPAGImage: Int64): Unit
}

@C
struct PAGTextData {
    var applyFill: Bool = true
    var applyStroke: Bool = false
    var boxText: Bool = false
    var fauxBold: Bool = false
    var strokeOverFill: Bool = true
    var fauxItalic: Bool = false
    var baselineShift: Float32 = 0.0
    var firstBaseLine: Float32 = 0.0
    var fontSize: Float32 = 24.0
    var strokeWidth: Float32 = 1.0
    var leading: Float32 = 0.0
    var tracking: Float32 = 0.0
    var backgroundAlpha: UInt8 = 255
    var fillColor: UInt32 = 0
    var strokeColor: UInt32 = 0
    var backgroundColor: UInt32 = 0
    var justification: UInt8 = 0
    var boxTextRect = VArray<Float32, $4>({i => 0.0})
    var fontFamily: CJBytesArray
    var fontStyle: CJBytesArray
    var text: CJBytesArray

    public init(
        applyFill: Bool,
        applyStroke: Bool,
        boxText: Bool,
        fauxBold: Bool,
        strokeOverFill: Bool,
        fauxItalic: Bool,
        baselineShift: Float32,
        firstBaseLine: Float32,
        fontSize: Float32,
        strokeWidth: Float32,
        leading: Float32,
        tracking: Float32,
        backgroundAlpha: UInt8,
        fillColor: UInt32,
        strokeColor: UInt32,
        backgroundColor: UInt32,
        justification: UInt8,
        boxTextRect: VArray<Float32, $4>,
        fontFamily: CJBytesArray,
        fontStyle: CJBytesArray,
        text: CJBytesArray
    ) {
        this.applyFill = applyFill
        this.applyStroke = applyStroke
        this.boxText = boxText
        this.fauxBold = fauxBold
        this.strokeOverFill = strokeOverFill
        this.fauxItalic = fauxItalic
        this.baselineShift = baselineShift
        this.firstBaseLine = firstBaseLine
        this.fontSize = fontSize
        this.strokeWidth = strokeWidth
        this.leading = leading
        this.tracking = tracking
        this.backgroundAlpha = backgroundAlpha
        this.fillColor = fillColor
        this.strokeColor = strokeColor
        this.backgroundColor = backgroundColor
        this.justification = justification
        this.boxTextRect = boxTextRect
        this.fontFamily = CJBytesArray(fontFamily.size, fontFamily.buf)
        this.fontStyle = CJBytesArray(fontStyle.size, fontStyle.buf)
        this.text = CJBytesArray(text.size, text.buf)
    }
}

public class PAGFile <: PAGComposition {
    private var ptrPAGFile: Int64 = 0
    private static let cacheDir: String = '/data/storage/el2/base'
    init(nativeLayer: Int64) {
        super(nativeLayer)
        if (this.ptrPAGFile != 0 && this.ptrPAGFile != nativeLayer) {
            unsafe {
                cj_PAGFile_release(this.ptrPAGFile)
            }
        }
        this.ptrPAGFile = nativeLayer
    }

    /*
     * The maximum tag level current SDK supports.
     */
    public static func MaxSupportedTagLevel(): UInt32 {
        unsafe {
            return cj_PAGFile_MaxSupportedTagLevel()
        }
    }

    protected static func IsNetWorkPath(filePath: String): Bool {
        if (filePath == '') {
            return false
        } else {
            let rule = "^(http|https|ftp)://[^\\s]+$"
            let r = Regex(rule, RegexOption().ignoreCase())
            return r.matches(filePath)
        }
    }

    /**
     * Load a pag file from the local path, returns null if the file does not exist or the
     * data is not a pag file.
     * Note: All PAGFiles loaded by the same path share the same internal cache. The internal
     * cache is alive until all PAGFiles are released. Use 'PAGFile.LoadFromBytes()' instead
     * if you don't want to load a PAGFile from the internal caches.
     */
    public static func LoadFromPath(path: String): Option<PAGFile> {
        unsafe {
            PAGFont.initFontFallback()
            PAGDiskCache.SetCacheDir(cacheDir)
            let p = LibC.mallocCString(path)
            let instanceId = cj_PAGFile_LoadFromPath(p)
            LibC.free(p)
            if (instanceId == 0) {
                return Option<PAGFile>.None
            }
            return PAGFile(instanceId)
        }
    }

    /**
     * Load a pag file from the specified path which can be a network path or a local path, returns null if the file does
     * not exist or the data is not a pag file.
     * Note: All PAGFiles loaded by the same path share the same internal cache. The internal
     * cache is alive until all PAGFiles are released. Use 'PAGFile.LoadFromBytes()' instead
     * if you don't want to load a PAGFile from the internal caches.
     */
    public static func LoadFromPathAsync(filePath: String, callback: (Option<PAGFile>) -> Unit): Unit {
        unsafe {
            PAGFont.initFontFallback()
            PAGDiskCache.SetCacheDir(cacheDir)
            if (PAGFile.IsNetWorkPath(filePath)) {
                let cacheData: Array<UInt8> = PAGDiskCache.readFile(filePath)
                if (cacheData.size > 0) {
                    callback(PAGFile.LoadFromBytes(cacheData))
                } else {
                    let httpRequest = createHttp()
                    let option = HttpRequestOptions(
                        method: RequestMethod.GET,
                        expectDataType: HttpDataType.ARRAY_BUFFER
                    )
                    httpRequest.request(
                        filePath,
                        {
                            err, resp =>
                            if (let Some(e) <- err) {
                                Hilog.error(0, "PAGFile", "LoadFromPathAsync error:${e.message}")
                            }
                            if (let Some(r) <- resp) {
                                if (r.responseCode.getValue() == ResponseCode.OK.getValue()) {
                                    match (r.result) {
                                        case HttpData.STRING_DATA(str) => ()
                                        case HttpData.ARRAY_DATA(bytes) => callback(PAGFile.LoadFromBytes(bytes))
                                        case _ => ()
                                    }
                                } else {
                                    callback(Option<PAGFile>.None)
                                }
                            } else {
                                callback(Option<PAGFile>.None)
                            }
                            httpRequest.destroy()
                        },
                        options: option
                    )
                }
            } else {
                var pagfile = PAGFile.LoadFromPath(filePath)
                if (pagfile.isNone()) {
                    callback(Option<PAGFile>.None)
                } else {
                    callback(pagfile)
                }
            }
        }
    }

    /**
     * Load a pag file from ArrayBuffer, return null if data is empty or it’s not a valid pag file.
     */
    public static func LoadFromBytes(bytes: Array<UInt8>): Option<PAGFile> {
        unsafe {
            PAGFont.initFontFallback()
            PAGDiskCache.SetCacheDir(cacheDir)
            let path: String = ''
            let p = LibC.mallocCString(path)
            let handle = acquireArrayRawData(bytes)
            let instanceId = cj_PAGFile_LoadFromBytes(handle.pointer, bytes.size, p)
            releaseArrayRawData(handle)
            if (instanceId == 0) {
                return Option<PAGFile>.None
            }
            return PAGFile(instanceId)
        }
    }
    /**
     * Load a pag file from assets, returns null if the file does not exist or the data is not a
     * pag file.
     * Note: The same path shares resource in memory until the file is released. If the file
     * may be changed, please use 'PAGFile.LoadFromBytes()' instead
     */
    public static func LoadFromAssets(manager: ResourceManager, name: String): Option<PAGFile> {
        PAGFont.initFontFallback()
        PAGDiskCache.SetCacheDir(cacheDir)
        try {
            let data: Array<UInt8> = manager.getRawFileContent(name)
            var file: Option<PAGFile> = PAGFile.LoadFromBytes(data)
            if (let Some(v) <- file) {
                return file
            } else {
                return Option<PAGFile>.None
            }
        } catch (e: BusinessException) {
            Hilog.error(0, "PAGFile",
                "LoadFromAssets getRawFileContent failed, error code: ${e.code}, message: ${e.message}.")
            return Option<PAGFile>.None
        }
    }

    /*
     * The tag level this pag file requires.
     */
    public func tagLevel(): Int64 {
        unsafe {
            return cj_PAGFile_tagLevel(ptrPAGFile)
        }
    }

    /*
     * The number of editable texts.
     */
    public func numTexts(): Int64 {
        unsafe {
            return cj_PAGFile_numTexts(ptrPAGFile)
        }
    }

    /*
     * The number of replaceable images.
     */
    public func numImages(): Int64 {
        unsafe {
            return cj_PAGFile_numImages(ptrPAGFile)
        }
    }

    /*
     * The number of video compositions.
     */
    public func numVideos(): Int64 {
        unsafe {
            return cj_PAGFile_numVideos(ptrPAGFile)
        }
    }

    /*
     * The path string of this file, returns empty string if the file is loaded from byte stream.
     */
    public func path(): String {
        unsafe {
            let res: CJBytesArray = cj_PAGFile_path(ptrPAGFile)
            let str = BytesArrayToString(res)
            free_CJBytesArray(res)
            return str
        }
    }

    /**
     * Get a text data of the specified index. The index ranges from 0 to numTexts - 1.
     * Note: It always returns the default text data.
     */
    public func getTextData(index: Int32): PAGText {
        unsafe {
            var pagText: PAGText = PAGText()
            let data: PAGTextData = cj_PAGFile_getTextData(ptrPAGFile, index)
            pagText.applyFill = data.applyFill
            pagText.applyStroke = data.applyStroke
            pagText.boxText = data.boxText
            pagText.fauxBold = data.fauxBold
            pagText.strokeOverFill = data.strokeOverFill
            pagText.fauxItalic = data.fauxItalic
            pagText.baselineShift = data.baselineShift
            pagText.firstBaseLine = data.firstBaseLine
            pagText.fontSize = data.fontSize
            pagText.strokeWidth = data.strokeWidth
            pagText.leading = data.leading
            pagText.tracking = data.tracking
            pagText.backgroundAlpha = data.backgroundAlpha
            pagText.fillColor = data.fillColor
            pagText.strokeColor = data.strokeColor
            pagText.backgroundColor = data.backgroundColor
            pagText.justification = uint8ToJustification(data.justification)
            pagText.boxTextRect = Rect(
                left: data.boxTextRect[0],
                top: data.boxTextRect[1],
                right: data.boxTextRect[2],
                bottom: data.boxTextRect[3]
            )
            pagText.fontFamily = BytesArrayToString(data.fontFamily)
            free_CJBytesArray(data.fontFamily)
            pagText.fontStyle = BytesArrayToString(data.fontStyle)
            free_CJBytesArray(data.fontStyle)
            pagText.text = BytesArrayToString(data.text)
            free_CJBytesArray(data.text)
            return pagText
        }
    }

    /**
     * Replace the text data of the specified index. The index ranges from 0 to PAGFile.numTexts - 1. Passing in null
     * for the textData parameter will reset it to default text data.
     */
    public func replaceText(index: Int32, pagText: PAGText): Unit {
        unsafe {
            var boxTextRect = VArray<Float32, $4>({i => 0.0})
            boxTextRect[0] = pagText.boxTextRect.left
            boxTextRect[0] = pagText.boxTextRect.top
            boxTextRect[0] = pagText.boxTextRect.right
            boxTextRect[0] = pagText.boxTextRect.bottom
            let fontFamily: CString = LibC.mallocCString(pagText.fontFamily)
            let fontStyle: CString = LibC.mallocCString(pagText.fontStyle)
            let text: CString = LibC.mallocCString(pagText.text)
            var data: PAGTextData = PAGTextData(
                pagText.applyFill,
                pagText.applyStroke,
                pagText.boxText,
                pagText.fauxBold,
                pagText.strokeOverFill,
                pagText.fauxItalic,
                pagText.baselineShift,
                pagText.firstBaseLine,
                pagText.fontSize,
                pagText.strokeWidth,
                pagText.leading,
                pagText.tracking,
                pagText.backgroundAlpha,
                pagText.fillColor,
                pagText.strokeColor,
                pagText.backgroundColor,
                pagText.justification.justificationToUint8(pagText.justification),
                boxTextRect,
                CJBytesArray(fontFamily.size(), fontFamily.getChars()),
                CJBytesArray(fontStyle.size(), fontStyle.getChars()),
                CJBytesArray(text.size(), text.getChars()),
            )
            cj_PAGFile_replaceText(ptrPAGFile, index, data)
            LibC.free(fontFamily)
            LibC.free(fontStyle)
            LibC.free(text)
            return
        }
    }

    /**
     * Replace the image data of the specified index. The index ranges from 0 to PAGFile.numImages - 1. Passing in null
     * for the image parameter will reset it to default image data.
     */
    public func replaceImage(index: Int32, pagImage: Option<PAGImage>): Unit {
        unsafe {
            if (pagImage.isNone()) {
                cj_PAGFile_replaceImage(ptrPAGFile, index, 0);
            } else {
                cj_PAGFile_replaceImage(ptrPAGFile, index, pagImage.getOrThrow().ptrCJPAGImage);
            }
            return
        }
    }

    /**
     * Replace the image data of the specified layer name. Passing in null
     * for the image parameter will reset it to default image data.
     */
    public func replaceImageByName(layerName: String, pagImage: Option<PAGImage>): Unit {
        unsafe {
            let layerName = LibC.mallocCString(layerName)
            if (pagImage.isNone()) {
                cj_PAGFile_replaceImageByName(ptrPAGFile, layerName, 0);
            } else {
                cj_PAGFile_replaceImageByName(ptrPAGFile, layerName, pagImage.getOrThrow().ptrCJPAGImage);
            }
            LibC.free(layerName)
            return
        }
    }

    /*
     * Return an array of layers by specified editable index and layer type.
     */
    public func getLayersByEditableIndex(index: Int32, layerType: PAGLayerType): Array<PAGLayer> {
        unsafe {
            let res: CJInt64Array = cj_PAGFile_getLayersByEditableIndex(ptrPAGFile, index, PAGLayerType.typeToInt8(layerType))
            let size: Int64 = res.size
            let buf: CPointer<Int64> = res.buf
            let bytes: Array<Int64> = Array<Int64>(size, repeat: 0)
            for (i in 0..size) {
                if (buf.isNotNull()) {
                    bytes[i] = buf.read(i)
                }
            }
            LibC.free<Int64>(buf)
            return PAGUtils.WarpJPAGLayers(bytes)
        }
    }

    /**
     * Returns the indices of the editable layers in this PAGFile.
     * If the editableIndex of a PAGLayer is not present in the returned indices, the PAGLayer should
     * not be treated as editable.
     */
    public func getEditableIndices(layerType: PAGLayerType): Array<Int64> {
        unsafe {
            let res: CJInt64Array = cj_PAGFile_getEditableIndices(ptrPAGFile, PAGLayerType.typeToInt8(layerType));
            let size: Int64 = res.size
            let buf: CPointer<Int64> = res.buf
            let bytes: Array<Int64> = Array<Int64>(size, repeat: 0)
            for (i in 0..size) {
                if (buf.isNotNull()) {
                    bytes[i] = buf.read(i)
                }
            }
            LibC.free<Int64>(buf)
            return bytes
        }
    }

    /**
     * Indicate how to stretch the original duration to fit target duration when file's duration is changed.
     * The default value is PAGTimeStretchMode::Repeat.
     */
    public func timeStretchMode(): PAGTimeStretchMode {
        unsafe {
            let mode = cj_PAGFile_timeStretchMode(ptrPAGFile)
            return PAGTimeStretchMode.int32ToMode(mode)
        }
    }

    /**
     * Set the timeStretchMode of this file.
     */
    public func setTimeStretchMode(mode: PAGTimeStretchMode): Unit {
        var value = PAGTimeStretchMode.modeToInt32(mode)
        unsafe {
            cj_PAGFile_setTimeStretchMode(ptrPAGFile, value)
        }
    }

    /*
     * Set the duration of this PAGFile. Passing a value less than or equal to 0 resets the duration to its default value.
     */
    public func setDuration(duration: Int64): Unit {
        unsafe {
            cj_PAGFile_setDuration(ptrPAGFile, duration)
            return
        }
    }

    /**
     * Make a copy of the original file, any modification to current file has no effect on the result file.
     */
    public func copyOriginal(): Option<PAGFile> {
        unsafe {
            let instanceId = cj_PAGFile_copyOriginal(ptrPAGFile)
            if (instanceId == 0) {
                return Option<PAGFile>.None
            }
            return PAGFile(instanceId)
        }
    }

    public func release(): Unit {
        unsafe {
            cj_PAGFile_release(ptrPAGFile)
            ptrPAGFile = 0
            ptr = 0
            isRelease = true
            return
        }
    }

    private func uint8ToJustification(value: UInt8): PAGTextJustification {
        match (value) {
            case 0 => PAGTextJustification.Left
            case 1 => PAGTextJustification.Center
            case 2 => PAGTextJustification.Right
            case 3 => PAGTextJustification.FullJustifyLastLineLeft
            case 4 => PAGTextJustification.FullJustifyLastLineRight
            case 5 => PAGTextJustification.FullJustifyLastLineCenter
            case 6 => PAGTextJustification.FullJustifyLastLineFull
            case _ => PAGTextJustification.Left
        }
    }
}
