/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

package libpag4cj

@C
struct CJMarker {
    var mStartTime: Int64
    var mDuration: Int64
    var mComment: CString

    public CJMarker(startTime: Int64, duration: Int64, comment: CString) {
        this.mStartTime = startTime
        this.mDuration = duration
        this.mComment = comment
    }
}

/**
 * Marker stores comments and other metadata and mark important times in a composition or layer.
 */
public class PAGMarker {
    public let mStartTime: Int64
    public let mDuration: Int64
    public let mComment: String

    public PAGMarker(startTime: Int64, duration: Int64, comment: String) {
        this.mStartTime = startTime
        this.mDuration = duration
        this.mComment = comment
    }
}
