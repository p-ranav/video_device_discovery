## Video device discovery

This app is used to detect video devices connected to the NVIDIA Jetson computer. 

## Build

```bash
make
```

## Sample output

Here is the sample output when run on NVIDIA Jetson Xavier NX.

* 2 CSI cameras are connected to the platform
* 1 USB camera - Intel® RealSense™ D435i

***NOTE*** Use the device.bus_info information to detect USB vs CSI camera. USB cameras will start with `usb-` and CSI cameras will start with `platform:`

```console
$ ./app
/dev/video0
 Driver: tegra-video
 Card: vi-output, imx219 9-0010
 Bus info: platform:15c10000.vi:0
 Pixel Format:
 - 10-bit Bayer RGRG/GBGB
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
 Pixel Format:
 - 10-bit Bayer RGRG/GBGB
 Resolutions:
 - 3264x2464
 - 3264x1848
 - 1920x1080
 - 1640x1232
 - 1280x720


/dev/video2
 Driver: uvcvideo
 Card: Intel(R) RealSense(TM) Depth Ca
 Bus info: usb-3610000.xhci-2.2
 Pixel Format:
 - 16-bit Depth
 - 16-bit Depth
 Resolutions:
 - 256x144
 - 480x270
 - 640x480
 - 1280x720
 - 256x144
 - 480x270
 - 640x480
 - 1280x720
```