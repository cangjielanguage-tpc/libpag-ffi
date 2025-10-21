/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package libpag4cj

@FastNative
foreign {
    func cj_VideoDecoder_registerSoftwareDecoderFactory(factory: Int64): Unit

    func cj_VideoDecoder_setMaxHardwareDecoderCount(maxCount: Int32): Unit
}

public abstract class VideoDecoder {

    /**
     * Register a software decoder factory to implement the decoder fallback mechanism.
     */
    public static func registerSoftwareDecoderFactory(factory: Int64): Unit {
        unsafe {
            cj_VideoDecoder_registerSoftwareDecoderFactory(factory)
        }
    }

    /**
     * Set the maximum number of hardware video decoders that can be create.
     */
    public static func setMaxHardwareDecoderCount(maxCount: Int32): Unit {
        unsafe {
            cj_VideoDecoder_setMaxHardwareDecoderCount(maxCount)
        }
    }
}
