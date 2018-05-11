# game:
![Screenshot previewing game](img/game_preview_screenshot.png "Preview of game")

## Overview
`'M4_LPROJECT_DESCRIPTION`' is a `'M4_PROJECT_DESCRIPTION_M4`'.

## Feature Highlights
	* Cross platform
	* Flexible command line argument handling 

## Versioning
game follows the [semantic](https://semver.org/) versioning scheme.

## Licensing
game is licensed under the MIT license. Check the [LICENSE.md file](LICENSE.md).
The documentation for game is licensed under the Creative Commons Attribution 4.0 International license. Check the [LICENSE-docs.md file](LICENSE-docs.md).

## Support
For generic questions about game you are encouraged to engage with the game community on [gitter](link)

## Documentation
The documentation for game is located in the `docs/` subdirectory. It uses the [Sphinx](http://sphinx-doc.org/)
framework, which makes it possible to build the documentation in multiple formats.

```bash
$ # navigate to the location of game's documentation:
$ cd docs/
$ # show supported documentation building options:
$ make help
$ # e.g build documentation as HTML:
$ make html
```

Documentation can also be browsed online [here](http://docs.libuv.org).

## Downloading

### Binary
Download the appropriate binaries for your OS from game [releases page](release link):
[Linux](project release link)
[Windows](project release link)
[Mac](project release link)

### Source
#### Prerequisites
##### Programs 

| Linux/Mac               | Windows |
| :---------------------: | :-----: |
| gcc > 5.0 or clang > 3.0 | visual studio > 2013|

##### Libraries

* libcheck (C unit testing framework)

#### Verifying
All game release tags are signed with the developer's key.
The relevent GPG key(s) to import are listed in the [MAINTAINERS.md](link) file.

```bash
$ # import gpg key:
$ gpg --keyserver pool.sks-keyservers.net --recv-keys <gpg-key>
$ # verify release tag:
$ git verify-tag <tag-name>
```
#### Obtain 
```bash
$ # clone the repository:
$ git clone (link)  
$ # navigate to game project directory:
$ cd game/
$ # prepare for game build compilation: 
$ sh autogen.sh
$ # list possible configure options for game:
$ ./configure --help
$ # e.g, generate a game release mode makefile:
$ ./configure --enable-release
$ # generate game' binary
$ make
$ # run game's test suite:
$ make check
$ # list possible arguments for game binary:
$ ./game --help
$ # e.g, run game binary with verbose enabled:
$ ./game --verbose

```

## Contributing
To obtain the guidelines for contributing to game, please refer to the [contributing file](CONTRIBUTING.md).



windows:
msys2 (x86_64) (install instructions)
(if already installed: pacman -Syuu; then pacman -S base-devel mingw-w64-x86_64-toolchain git)
(then open msys2 mingw 64-bit shell; can use gcc, make, autoreconf, etc.)
(pacman -S mingw-w64-x86_64-SDL2 mingw-w64-x86_64-SDL2_image mingw-w64-check)

-lmingw32 -lSDL2main -lSDL2 (this order is necessary as gcc only resolves undefined symbols. needed for WinMain)
