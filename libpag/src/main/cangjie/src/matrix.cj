/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package libpag4cj

public class Matrix4 {
    public var props: Array<Float32> = Array<Float32>(16, repeat: 0.0)

    var _identity: Bool = true
    var _identityCalculated: Bool = false

    // Binding with C code, the object pointer returned by C code.
    private var ptr: Int64 = 0

    public init(ptr: Int64) {
        this.ptr = ptr
    }

    public init() {
        this.props[0] = 1.0
        this.props[5] = 1.0
        this.props[10] = 1.0
        this.props[15] = 1.0
    }
    public init(props: Array<Float32>) {
        this.props = props
    }
}
