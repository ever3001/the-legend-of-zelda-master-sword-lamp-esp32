
[![Build Status](https://gitlab.com/ever3001/the-legend-of-zelda-master-sword-lamp-esp32/badges/develop/pipeline.svg)](https://gitlab.com/ever3001/the-legend-of-zelda-master-sword-lamp-esp32)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

# The Legend of Zelda Master Sword Lamp esp32

<!-- TODO: Add schematics of the project -->

<!-- TODO: DESCRIPTIION -->


## Project status
[![Project Status: Active – The project has reached a stable, usable state and is being actively developed.](https://www.repostatus.org/badges/latest/active.svg)](https://www.repostatus.org/#active)

## Build and release process

This project uses Gitlab CI for testing and generating final binaries. For more information please visit the webpage [Job artifacts](https://docs.gitlab.com/ee/ci/pipelines/job_artifacts.html).

To run locally the project, please [install PlatformIO](https://platformio.org/install) before continue.

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

- [ ] Add description
- [ ] Add original schematics
- [ ] Add new schematics

## Contributors

Special thanks goes to all [contributors](https://github.com/thegeeklab/hugo-geekdoc/graphs/contributors). If you would like to contribute,
please see the [instructions](https://github.com/thegeeklab/hugo-geekdoc/blob/main/CONTRIBUTING.md).

Geekdoc is inspired and partially based on the [hugo-book](https://github.com/alex-shpak/hugo-book) theme, thanks [Alex Shpak](https://github.com/alex-shpak/) for your work.

## License

This project is licensed under the MIT License - see the [LICENSE](./LICENSE) file for details.

