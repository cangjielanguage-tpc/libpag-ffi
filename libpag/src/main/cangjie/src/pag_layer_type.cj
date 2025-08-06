/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package libpag4cj

/*
 * Layer is always one of the following types.
 */
public enum PAGLayerType <: Equatable<PAGLayerType> {
    | Unknown // 0
    | Null // 1
    | Solid // 2
    | Text // 3
    | Shape // 4
    | Image // 5
    | PreCompose // 6

    protected static func typeToInt8(value: PAGLayerType): Int8 {
        match (value) {
            case PAGLayerType.Unknown => 0
            case PAGLayerType.Null => 1
            case PAGLayerType.Solid => 2
            case PAGLayerType.Text => 3
            case PAGLayerType.Shape => 4
            case PAGLayerType.Image => 5
            case PAGLayerType.PreCompose => 6
            case _ => 0
        }
    }

    protected static func int8ToType(value: Int8): PAGLayerType {
        match (value) {
            case 0 => PAGLayerType.Unknown
            case 1 => PAGLayerType.Null
            case 2 => PAGLayerType.Solid
            case 3 => PAGLayerType.Text
            case 4 => PAGLayerType.Shape
            case 5 => PAGLayerType.Image
            case 6 => PAGLayerType.PreCompose
            case _ => PAGLayerType.Unknown
        }
    }

    public operator func ==(that: PAGLayerType): Bool {
        match ((this, that)) {
            case (Unknown, Unknown) => true
            case (Null, Null) => true
            case (Solid, Solid) => true
            case (Text, Text) => true
            case (Shape, Shape) => true
            case (Image, Image) => true
            case (PreCompose, PreCompose) => true
            case _ => false
        }
    }

    public operator func !=(that: PAGLayerType): Bool {
        return !(this == that)
    }

    public func toString(): String {
        var str: String = ''
        match (this) {
            case PAGLayerType.Unknown => str = "Unknown"
            case PAGLayerType.Null => str = "Null"
            case PAGLayerType.Solid => str = "Solid"
            case PAGLayerType.Text => str = "Text"
            case PAGLayerType.Shape => str = "Shape"
            case PAGLayerType.Image => str = "Image"
            case PAGLayerType.PreCompose => str = "PreCompose"
            case _ => str = "Unknown"
        }
        return str
    }
}
