/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package libpag4cj

@FastNative
foreign {
    func cj_PAGDiskCache_maxDiskSize(): Int64

    func cj_PAGDiskCache_setMaxDiskSize(size: Int64): Unit

    func cj_PAGDiskCache_removeAll(): Unit

    func cj_PAGDiskCache_readFile(key: CString): CJBytesArray

    func cj_PAGDiskCache_writeFile(key: CString, bytes: CPointer<UInt8>, size: Int64): Bool

    func cj_PAGDiskCache_SetCacheDir(path: CString): Unit
}

/**
 * Defines methods to manage the disk cache capabilities.
 */
public class PAGDiskCache {
    let fid: Int64

    init(fid: Int64) {
        this.fid = fid
    }

    /**
     * Returns the size limit of the disk cache in bytes. The default value is 1 GB.
     */
    public static func maxDiskSize(): Int64 {
        unsafe {
            return cj_PAGDiskCache_maxDiskSize()
        }
    }

    /**
     * Sets the size limit of the disk cache in bytes, which will triggers the cache cleanup if the
     * disk usage exceeds the limit. The opened files are not removed immediately, even if their
     * disk usage exceeds the limit, and they will be rechecked after they are closed.
     */
    public static func setMaxDiskSize(size: Int64): Unit {
        if (size < 0) {
            return
        }
        unsafe {
            return cj_PAGDiskCache_setMaxDiskSize(size)
        }
    }

    /**
     * Removes all cached files from the disk. All the opened files will be also removed after they
     * are closed.
     */
    public static func removeAll(): Unit {
        unsafe {
            return cj_PAGDiskCache_removeAll()
        }
    }

    protected static func readFile(key: String): Array<UInt8> {
        unsafe {
            let k = LibC.mallocCString(key)
            let res: CJBytesArray = cj_PAGDiskCache_readFile(k)
            let size: Int64 = res.size
            let buf: CPointer<UInt8> = res.buf
            let bytes: Array<UInt8> = Array<UInt8>(size, repeat: 0)
            for (i in 0..size) {
                bytes[i] = (buf + i).read()
            }
            LibC.free(k)
            free_CPointer_UInt8(buf)
            return bytes
        }
    }

    protected static func writeFile(key: String, bytes: Array<Byte>): Bool {
        unsafe {
            let str = LibC.mallocCString(key)
            let handle = acquireArrayRawData(bytes)
            let flag: Bool = cj_PAGDiskCache_writeFile(str, handle.pointer, bytes.size)
            LibC.free(str)
            releaseArrayRawData(handle)
            return flag
        }
    }

    public static func SetCacheDir(path: String): Unit {
        unsafe {
            let p = LibC.mallocCString(path)
            cj_PAGDiskCache_SetCacheDir(p)
            LibC.free(p)
            return
        }
    }
}
