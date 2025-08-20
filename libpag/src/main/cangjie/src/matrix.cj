/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package libpag4cj

public class Matrix4 {
    public var props: Array<Float32> = Array<Float32>(16, repeat: 0.0)

    public init(props: Array<Float32>) {
        this.props = props
    }
}
