load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "sdl2",
    build_file_content = """
cc_library(
    name = "sdl2",
    hdrs = glob([
        "include/**/*.h",
        "src/**/*.h",
    ]),
    srcs = glob(["src/**/*.c"]),
    includes = ["include"],
    visibility = ["//visibility:public"],
)
""",
    strip_prefix = "SDL2-2.0.14",
    urls = ["https://www.libsdl.org/release/SDL2-2.0.14.tar.gz"],
)