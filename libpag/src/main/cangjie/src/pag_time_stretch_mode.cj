/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package libpag4cj

/**
 * Defines the values used in the setTimeStretchMode method of PAGFile.
 */
public class PAGTimeStretchMode {
    /**
     * Keep the original playing speed, and display the last frame if the content's duration is less than target duration.
     */
    public static let None: Int32 = 0
    /*
     * Change the playing speed of the content to fit target duration.
     */
    public static let Scale: Int32 = 1
    /**
     * Keep the original playing speed, but repeat the content if the content's duration is less than target duration.
     * This is the default mode.
     */
    public static let Repeat: Int32 = 2
    /**
     * Keep the original playing speed, but repeat the content in reversed if the content's duration is less than
     * target duration.
     */
    public static let RepeatInverted: Int32 = 3
}
