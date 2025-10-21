/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package libpag4cj

/**
 * Defines the values used in the setTimeStretchMode method of PAGFile.
 */
public enum PAGTimeStretchMode <: Equatable<PAGTimeStretchMode> {
    /**
     * Keep the original playing speed, and display the last frame if the content's duration is less than target duration.
     */
    | None // 0
    /*
     * Change the playing speed of the content to fit target duration.
     */
    | Scale // 1
    /**
     * Keep the original playing speed, but repeat the content if the content's duration is less than target duration.
     * This is the default mode.
     */
    | Repeat // 2
    /**
     * Keep the original playing speed, but repeat the content in reversed if the content's duration is less than
     * target duration.
     */
    | RepeatInverted // 3

    protected static func modeToInt32(value: PAGTimeStretchMode): Int32 {
        match (value) {
            case PAGTimeStretchMode.None => 0
            case PAGTimeStretchMode.Scale => 1
            case PAGTimeStretchMode.Repeat => 2
            case PAGTimeStretchMode.RepeatInverted => 3
            case _ => -1
        }
    }

    protected static func int32ToMode(value: Int32): PAGTimeStretchMode {
        match (value) {
            case 0 => PAGTimeStretchMode.None
            case 1 => PAGTimeStretchMode.Scale
            case 2 => PAGTimeStretchMode.Repeat
            case 3 => PAGTimeStretchMode.RepeatInverted
            case _ => PAGTimeStretchMode.Scale
        }
    }

    public operator func ==(that: PAGTimeStretchMode): Bool {
        match ((this, that)) {
            case (None, None) => true
            case (Scale, Scale) => true
            case (Repeat, Repeat) => true
            case (RepeatInverted, RepeatInverted) => true
            case _ => false
        }
    }

    public operator func !=(that: PAGTimeStretchMode): Bool {
        return !(this == that)
    }
}
