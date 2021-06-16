## Video device discovery

A small standalone app to detect video devices connected to a Linux-based embedded platform.

## Sample Output

Here's a sample output from this program.

* Executed on NVIDIA Jetson Xavier NX
* Connected video devices:
  - 2 x Arducam CSI cameras
  - 1 x USB camera - Intel® RealSense™ D435i

```console
$ make
g++ -std=c++17 -Iinclude -o app src/main.cpp -lstdc++fs

$ ./app
/dev/video0
 Driver: tegra-video
 Card: vi-output, imx219 9-0010
 Bus info: platform:15c10000.vi:0
 Pixel Format: 10-bit Bayer RGRG/GBGB
 Resolutions:
 - 3264x2464
 - 3264x1848
 - 1920x1080
 - 1640x1232
 - 1280x720


/dev/video1
 Driver: tegra-video
 Card: vi-output, imx219 10-0010
 Bus info: platform:15c10000.vi:2
 Pixel Format: 10-bit Bayer RGRG/GBGB
 Resolutions:
 - 3264x2464
 - 3264x1848
 - 1920x1080
 - 1640x1232
 - 1280x720


/dev/video2
 Driver: uvcvideo
 Card: Intel(R) RealSense(TM) Depth Ca
 Bus info: usb-3610000.xhci-2.1
 Pixel Format: 16-bit Depth
 Resolutions:
 - 256x144
 - 480x270
 - 640x480
 - 1280x720
 - 256x144
 - 480x270
 - 640x480
 - 1280x720


/dev/video3
 Driver: uvcvideo
 Card: Intel(R) RealSense(TM) Depth Ca
 Bus info: usb-3610000.xhci-2.1
 Pixel Format: 8-bit Greyscale
 Resolutions:
 - 256x144
 - 480x270
 - 640x480
 - 1280x720
 - 256x144
 - 480x270
 - 640x480
 - 1280x720
 - 256x144
 - 480x270
 - 640x480
 - 1280x720


/dev/video4
 Driver: uvcvideo
 Card: Intel(R) RealSense(TM) Depth Ca
 Bus info: usb-3610000.xhci-2.1
 Pixel Format: YUYV 4:2:2
 Resolutions:
 - 424x240
 - 640x480
 - 1280x720
```

## Notes

The `bus_info` field in `VideoDevice` class can be used to differentiate CSI cameras from USB cameras.

From the [v4l2_capability docs](https://www.kernel.org/doc/html/v4.12/media/uapi/v4l/vidioc-querycap.html),

> bus_info: Location of the device in the system, a NUL-terminated ASCII string. For example: “PCI:0000:05:06.0”. This information is intended for users, to distinguish multiple identical devices. If no such information is available the field must simply count the devices controlled by the driver (“platform:vivi-000”). The bus_info must start with “PCI:” for PCI boards, “PCIe:” for PCI Express boards, “usb-” for USB devices, “I2C:” for i2c devices, “ISA:” for ISA devices, “parport” for parallel port devices and “platform:” for platform devices.

For CSI cameras, the `bus_info` will start with `"platform:"`. For USB cameras, the `bus_info` will start with `"usb-"`.
