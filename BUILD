cc_library(
    name = "chip8",
    srcs = ["src/chip8.c"],
    hdrs = ["include/chip8.h"],
)

cc_library(
    name = "sdlutils",
    srcs = ["src/sdlutils.c"],
    hdrs = ["include/sdlutils.h"],
    deps = ["@sdl2//:sdl2"],
)

cc_library(
    name = "load",
    srcs = ["src/load.c"],
    hdrs = ["include/load.h"],
    deps = [":chip8"],
)

cc_binary(
    name = "main",
    srcs = ["src/main.c"],
    deps = [
        ":chip8",
        ":sdlutils",
        ":load",
        "@sdl2//:sdl2",
    ],
)