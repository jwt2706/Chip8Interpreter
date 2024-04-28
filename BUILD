cc_library(
    name = "chip8",
    srcs = ["chip8.c"],
    hdrs = ["chip8.h"],
)

cc_binary(
    name = "main",
    srcs = ["main.c"],
    deps = [":chip8"],
)