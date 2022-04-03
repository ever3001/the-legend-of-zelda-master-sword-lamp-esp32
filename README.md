
[![Build Status](https://gitlab.com/ever3001/the-legend-of-zelda-master-sword-lamp-esp32/badges/develop/pipeline.svg)](https://gitlab.com/ever3001/the-legend-of-zelda-master-sword-lamp-esp32)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

# The Legend of Zelda Master Sword Lamp RGB esp32

<!-- TODO: Add schematics of the project -->

This project is a modification of the The Legend of Zelda Master Sword Lamp to add RGB LEDs. Inside the lamp there is esp32 which creates a server to control the color of the lamp. The code has OTA support, which means that once the code is flashed once, it is possible to send updates using Wi-Fi.

## Project status
[![Project Status: Active – The project has reached a stable, usable state and is being actively developed.](https://www.repostatus.org/badges/latest/active.svg)](https://www.repostatus.org/#active)

## Build and release process

This project uses Gitlab CI for testing and generating final binaries. For more information please visit the webpage [Job artifacts](https://docs.gitlab.com/ee/ci/pipelines/job_artifacts.html).

To run locally the project, please [install PlatformIO](https://platformio.org/install).

Before compile the project, please change the following definitions in [platformio.ini](./platformio.ini):

```
  ...
  -DCONFIG_WIFI_SSID='"YOUR SSID"'
  -DCONFIG_WIFI_PASS='"admin"'
  -DCONFIG_OTA_HOSTNAME='"esp32-master-sword"'
  -DCONFIG_OTA_PASSWORD='""'
  -DCONFIG_PIXELS_PIN=13
  -DCONFIG_PIXELS_COUNT=6
  ...

[ota]
upload_port = 192.168.1.16
```

### Build all environemnts

```Shell
platformio run
```

### Build just one environemnt

```Shell
platformio run --environment esp32-master-sword-debug
```

See the [platformio.ini](./platformio.ini) for details about the different environments.

## TODO

### Repository

- [ ] Add original schematics.
- [ ] Add new schematics.
- [ ] Create guide of how to modify the Master Sword Lamp.

### Project

- [ ] Add daylight lamp support.
- [ ] Add animations.
- [ ] Add music support.
## Contributors

If you would like to contribute, please see the [instructions](./CONTRIBUTING.md).

This project is inspired and partially based on the [ESP32-powered Programmable Neopixel Lamp](https://sudomod.com/wifi-neopixels-esp32/), thanks [sudomod](https://sudomod.com/) for your work.

## License

This project is licensed under the MIT License - see the [LICENSE](./LICENSE) file for details.
