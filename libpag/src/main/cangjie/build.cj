/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2025-2025. All rights reserved.
 */

import std.posix.*
import std.process.*
import std.env.*
import std.fs.*
import std.sync.*
import std.time.*

// 此构建脚本是为了等待 c++侧so文件生成后,启动仓颉编译, 否则编译报so文件找不到.
main(): Int64 {
    let abi = getVariable("ABI").getOrThrow()
    let lib: Path = canonicalize(getcwd())
        .parent
        .parent
        .parent
        .join("build")
        .join("default")
        .join("intermediates")
        .join("libs")
        .join("default")
        .join(abi)
    while (!exists(lib)) {
        sleep(Duration.second)
    }
    let libSo = lib.join("libpag_native.so")
    while (!exists(libSo)) {
        sleep(Duration.second)
    }
    0
}
