/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package libpag4cj

internal import ohos.resource_manager.*
internal import ohos.ability.*
import kit.UIKit.*
import std.unicode.UnicodeStringExtension

@FastNative
foreign {
    func cj_PAGFont_registerFont(fileName: CString, ttcIndex: Int32, fontFamily: CString, fontStyle: CString): Int64

    func cj_PAGFont_registerFontBytes(data: CPointer<UInt8>, length: Int32, ttcIndex: Int32, fontFamily: CString,
        fontStyle: CString): Int64

    func cj_PAGFont_unregisterFont(fontFamily: CString, fontStyle: CString): Unit

    func cj_PAGFont_setFallbackFontPaths(handlefns: CPointer<CString>, lenfn: Int64, handlettcs: CPointer<Int32>,
        lenttc: Int64): Unit

    func cj_PAGFont_getFontFamily(ptr: Int64): CJBytesArray

    func cj_PAGFont_getFontStyle(ptr: Int64): CJBytesArray
}

public class PAGFont {
    // Binding with C code, the object pointer returned by C code.
    protected let ptr: Int64

    /**
     * A string with the name of the font family.
     **/
    public var fontFamily: String = ""

    /**
     * A string with the style information — e.g., “bold”, “italic”.
     **/
    public var fontStyle: String = ""

    private static var hasInit: Bool = false;

    protected static func initFontFallback() {
        if (hasInit) {
            return
        }
        let fontConfig = Font.getUIFontConfig()
        var paths: ArrayList<String> = ArrayList<String>()
        var emojiPaths: ArrayList<String> = ArrayList<String>()
        for (element in fontConfig.fallbackGroups) {
            for (fallback in element.fallback) {
                var fontInfo = Font.getFontByName(fallback.family)
                if (fontInfo.isNone()) {
                    fontInfo = Font.getFontByName(fallback.family + " Regular")
                }
                if (let Some(info) <- fontInfo) {
                    let idxOpt = info.fullName.toLower().indexOf("emoji")
                    if (idxOpt.isSome() && idxOpt.getOrThrow() > 0) {
                        emojiPaths.add(info.path)
                    } else {
                        paths.add(info.path)
                    }
                }
            }
        }
        paths.add(all: emojiPaths)
        if (paths.size > 0) {
            var ttcIndices: Array<Int32> = Array<Int32>(paths.size, repeat: 0)
            let fontPathList: Array<String> = paths.toArray()
            setFallbackFontPaths(fontPathList, ttcIndices)
            hasInit = true
        }
    }

    protected init(fontFamily: String, fontStyle: String, ptr: Int64) {
        this.fontFamily = fontFamily
        this.fontStyle = fontStyle
        this.ptr = ptr
    }

    public init(fontFamily: String, fontStyle: String) {
        this.fontFamily = fontFamily
        this.fontStyle = fontStyle
        this.ptr = 0
    }

    public static func registerFontFromPath(fontPath: String, ttcIndex!: Int32 = 0, fontFamily!: String = "",
        fontStyle!: String = ""): PAGFont {
        return registerFont(fontPath, ttcIndex, fontFamily, fontStyle)
    }

    public static func registerFontFromAsset(context: Option<AbilityContext>, fileName: String, ttcIndex!: Int32 = 0,
        fontFamily!: String = "", fontStyle!: String = ""): PAGFont {
        return registerFont(context, fileName, ttcIndex, fontFamily, fontStyle)
    }

    protected static func registerFont(fontPath: String): PAGFont {
        return registerFont(fontPath, 0)
    }

    protected static func registerFont(fontPath: String, ttcIndex: Int32): PAGFont {
        return registerFont(fontPath, ttcIndex, "", "")
    }

    protected static func registerFont(fontPath: String, ttcIndex: Int32, fontFamily: String, fontStyle: String): PAGFont {
        unsafe {
            let f = LibC.mallocCString(fontPath)
            let ff = LibC.mallocCString(fontFamily)
            let fs = LibC.mallocCString(fontStyle)
            let id: Int64 = cj_PAGFont_registerFont(f, ttcIndex, ff, fs)
            LibC.free(f)
            LibC.free(ff)
            LibC.free(fs)
            return PAGUtils.ToPAGFont(id)
        }
    }

    protected static func registerFont(manager: Option<AbilityContext>, fileName: String): PAGFont {
        return registerFont(manager, fileName, 0)
    }

    protected static func registerFont(manager: Option<AbilityContext>, fileName: String, ttcIndex: Int32): PAGFont {
        return registerFont(manager, fileName, ttcIndex, "", "")
    }

    protected static func registerFont(context: Option<AbilityContext>, fileName: String, ttcIndex: Int32,
        fontFamily: String, fontStyle: String): PAGFont {
        let stageContext = getStageContext(context.getOrThrow())
        let resMgr = ResourceManager.getResourceManager(stageContext)
        try {
            var buf: Array<Byte> = resMgr.getRawFileContent(fileName)
            return registerFontBytes(buf, Int32(buf.size), ttcIndex, fontFamily, fontStyle)
        } catch (e: BusinessException) {
            Hilog.error(0, "PAGFont",
                "registerFont getRawFileContent failed, error code: ${e.code}, message: ${e.message}.")
            return PAGFont("", "", 0)
        }
    }

    private static func registerFontBytes(bytes: Array<Byte>, length: Int32, ttcIndex: Int32): PAGFont {
        return registerFontBytes(bytes, length, ttcIndex, "", "")
    }

    private static func registerFontBytes(data: Array<Byte>, length: Int32, ttcIndex: Int32, fontFamily: String,
        fontStyle: String): PAGFont {
        unsafe {
            let handle = acquireArrayRawData(data)

            let ff = LibC.mallocCString(fontFamily)
            let fs = LibC.mallocCString(fontStyle)
            let id: Int64 = cj_PAGFont_registerFontBytes(handle.pointer, length, ttcIndex, ff, fs)
            LibC.free(ff)
            LibC.free(fs)
            releaseArrayRawData(handle)
            return PAGUtils.ToPAGFont(id)
        }
    }

    public static func unregisterFont(font: PAGFont): Unit {
        unsafe {
            let ff = LibC.mallocCString(font.fontFamily)
            let fs = LibC.mallocCString(font.fontStyle)
            cj_PAGFont_unregisterFont(ff, fs)
            LibC.free(ff)
            LibC.free(fs)
        }
    }

    protected static func setFallbackFontPaths(fontNameList: Array<String>, ttcIndices: Array<Int32>): Unit {
        unsafe {
            let lenfn: Int64 = fontNameList.size
            let arrCString: Array<CString>
            if (lenfn > 0) {
                let fn0 = LibC.mallocCString(fontNameList[0])
                arrCString = Array<CString>(lenfn, repeat: fn0)
            } else {
                arrCString = Array<CString>()
            }
            for (i in 0..lenfn) {
                if (i == 0) {
                    continue
                }
                let fni = LibC.mallocCString(fontNameList[i])
                arrCString[i] = fni
            }
            let handlefns: CPointerHandle<CString> = acquireArrayRawData(arrCString)
            let handlettcs: CPointerHandle<Int32> = acquireArrayRawData(ttcIndices)
            cj_PAGFont_setFallbackFontPaths(handlefns.pointer, lenfn, handlettcs.pointer, ttcIndices.size)
            for (i in 0..lenfn) {
                LibC.free(arrCString[i])
            }
            releaseArrayRawData(handlefns)
            releaseArrayRawData(handlettcs)
        }
    }

    protected static func getFontFamily(ptr: Int64): String {
        unsafe {
            let res: CJBytesArray = cj_PAGFont_getFontFamily(ptr)
            let str = BytesArrayToString(res)
            free_CJBytesArray(res)
            return str
        }
    }

    protected static func getFontStyle(ptr: Int64): String {
        unsafe {
            let res: CJBytesArray = cj_PAGFont_getFontStyle(ptr)
            let str = BytesArrayToString(res)
            free_CJBytesArray(res)
            return str
        }
    }
}
