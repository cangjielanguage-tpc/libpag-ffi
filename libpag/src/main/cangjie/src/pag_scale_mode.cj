/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package libpag4cj

/**
 * Define the values used in the setScaleMode method of PAGPlayer.
 */
public class PAGScaleMode {
    /**
     * The content is not scaled.
     */
    public static let None: Int32 = 0
    /**
     * The content is stretched to fit.
     */
    public static let Stretch: Int32 = 1
    /**
     * The content is scaled with respect to the original unscaled image's aspect ratio.
     * This is the default value.
     */
    public static let LetterBox: Int32 = 2
    /**
     * The content is scaled to fit with respect to the original unscaled image's aspect ratio.
     * This results in cropping on one axis.
     */
    public static let Zoom: Int32 = 3
}
