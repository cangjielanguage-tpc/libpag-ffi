/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package libpag4cj

@C
struct CJPAGVideoRange {
    var startTime: Int64
    var endTime: Int64
    var playDuration: Int64
    var reversed: Bool

    public init(startTime: Int64, endTime: Int64, playDuration: Int64, reversed: Bool) {
        this.startTime = startTime
        this.endTime = endTime
        this.playDuration = playDuration
        this.reversed = reversed
    }
}

/**
 * Represents a time range from the content of PAGImageLayer.
 */
public class PAGVideoRange {
    /**
     * The start time of the source video, in microseconds.
     */
    public var startTime: Int64 = 0
    /**
     * The end time of the source video (not included), in microseconds.
     */
    public var endTime: Int64 = 0
    /**
     * The duration for playing after applying speed.
     */
    public var playDuration: Int64 = 0
    /**
     * Indicates whether the video should play backward.
     */
    public var reversed: Bool = false

    public init() {}

    public init(startTime: Int64, endTime: Int64, playDuration: Int64, reversed: Bool) {
        this.startTime = startTime
        this.endTime = endTime
        this.playDuration = playDuration
        this.reversed = reversed
    }
}
