/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package libpag4cj

public class Rect <: ToString {

    /* Top margin */
    public var top: Float32 = 0.0

    /* Left margin */
    public var left: Float32 = 0.0

    /* The right */
    public var right: Float32 = 0.0

    /* The bottom */
    public var bottom: Float32 = 0.0

    /**
     * Create a SourceRect instance.
     */
    public init() {}

    /**
     * Create a SourceRect instance based on parameters.
     *
     * @param left - Type of Float32, Left margin of SourceRect.
     * @param top - Type of Float32, Top margin of SourceRect.
     * @param right - Type of Float32, The right of SourceRect.
     * @param bottom - Type of Float32, The bottom of SourceRect.
     */
    public init(left!: Float32, top!: Float32, right!: Float32, bottom!: Float32) {
        this.right = right
        this.bottom = bottom
        this.top = top
        this.left = left
    }

    /**
     * Return to convert the instance into a string and return.
     *
     * @return Type of String, converted String.
     */
    public func toString(): String {
        return "SourceRect = {(top = ${top}), (left = ${left}), (right = ${right}), (bottom = ${bottom})}"
    }
}
