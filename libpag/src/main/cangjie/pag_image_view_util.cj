/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package libpag4cj

@C
protected struct CJPixelMap {
    var size: Int64
    var buf: CPointer<UInt8>
    var alphaType: UInt8
    var editable: Bool
    var pixelFormat: UInt8
    var height: Int32
    var width: Int32

    init(size: Int64, buf: CPointer<UInt8>, alphaType: UInt8, editable: Bool, pixelFormat: UInt8, height: Int32,
        width: Int32) {
        this.size = size
        this.buf = buf
        this.alphaType = alphaType
        this.editable = editable
        this.pixelFormat = pixelFormat
        this.height = height
        this.width = width
    }
}
