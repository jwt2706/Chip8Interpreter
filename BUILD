cc_library(
    name = "chip8",
    srcs = glob(["src/*.c"]),
    hdrs = glob(["include/*.h"]),
    includes = ["include"],
)

cc_binary(
    name = "main",
    srcs = ["src/main.c"],
    deps = [
        ":chip8",
        "@SDL2//:SDL2",
    ],
)