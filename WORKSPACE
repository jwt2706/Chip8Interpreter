load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "SDL2",
    urls = ["https://www.libsdl.org/release/SDL2-2.0.14.tar.gz"],
    sha256 = "d8215b571a581be1332d2106f8036fcb03d12a70bae01e20f424976d275432bc",
    build_file_content = """
cc_library(
    name = "SDL2",
    srcs = glob(["SDL2-2.0.14/src/**/*.c"]),
    hdrs = glob(["SDL2-2.0.14/include/**/*.h"]),
    includes = ["SDL2-2.0.14/include"],
    visibility = ["//visibility:public"],
)
"""
)