/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package libpag4cj

public enum PAGScaleMode <: Equatable<PAGScaleMode> {
    /**
     * The content is not scaled.
     */
    | None // 0
    /**
     * The content is stretched to fit.
     */
    | Stretch // 1
    /**
     * The content is scaled with respect to the original unscaled image's aspect ratio.
     * This is the default value.
     */
    | LetterBox // 2
    /**
     * The content is scaled to fit with respect to the original unscaled image's aspect ratio.
     * This results in cropping on one axis.
     */
    | Zoom // 3

    protected static func modeToInt32(value: PAGScaleMode): Int32 {
        match (value) {
            case PAGScaleMode.None => 0
            case PAGScaleMode.Stretch => 1
            case PAGScaleMode.LetterBox => 2
            case PAGScaleMode.Zoom => 3
            case _ => 2
        }
    }

    protected static func int32ToMode(value: Int32): PAGScaleMode {
        match (value) {
            case 0 => PAGScaleMode.None
            case 1 => PAGScaleMode.Stretch
            case 2 => PAGScaleMode.LetterBox
            case 3 => PAGScaleMode.Zoom
            case _ => PAGScaleMode.LetterBox
        }
    }

    public operator func ==(that: PAGScaleMode): Bool {
        match ((this, that)) {
            case (None, None) => true
            case (Stretch, Stretch) => true
            case (LetterBox, LetterBox) => true
            case (Zoom, Zoom) => true
            case _ => false
        }
    }

    public operator func !=(that: PAGScaleMode): Bool {
        return !(this == that)
    }
}
