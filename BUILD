cc_library(
    name = "lib",
    srcs = [
        "src/chip8.c",
        "src/sdlutils.c",
        "src/load.c",
    ],
    hdrs = [
        "include/chip8.h",
        "include/sdlutils.h",
        "include/load.h",
    ],
    deps = ["@sdl2//:sdl2"],
)

cc_binary(
    name = "main",
    srcs = ["src/main.c"],
    deps = [":lib"],
)