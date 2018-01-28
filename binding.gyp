{
  "targets": [
    {
      "target_name": "addon",
      "sources": [
        "src/wrapper/addon.cc",
        "src/wrapper/myobject.cc",
        # "src/LEDStrip/LEDStrip.cpp",
        "src/libs/dma.c",
        "src/libs/pwm.c",
        "src/libs/ws2811.c",
        "src/libs/mailbox.c",
        "src/libs/rpihw.c",
        "src/libs/pcm.c"
      ]
    }
  ]
}
