# MarsTech C++ SYS Example
 - [Installation](#installation)
	 - [Configuration](#configuration)
 - [Source Code Documentation](#source-code-documentation)
 - [License](#license)

This is example how to use [MarsTech C++ SYS](https://github.com/Mars2004/msys) library and other [MarsTech](https://github.com/Mars2004) project.
It is very simple application which creates four modules (two static and two dynamic loaded from dynamic/shared libraries). Each module has one thread which logs one log message per 100 milliseconds.
The example application can be stopped by pressing **Ctrl + C**.

## Installation
Download all [MarsTech](https://github.com/Mars2004) dependencies and put them to a same directory. Create new subdirectory "3rdParty" and put there "3rdParty" dependencies ([inih](https://github.com/jtilly/inih), [SQLite3](https://www.sqlite.org/index.html)).
Then build whole solution and put "config.ini" file to the working directory (in most cases the same directory where binaries are stored).

### Dependencies

 - [MarsTech Headers](https://github.com/Mars2004/mheaders)
 - [MarsTech Dependency Injection](https://github.com/Mars2004/mdi)
 - [MarsTech Error Handling](https://github.com/Mars2004/merror)
 - [MarsTech Logging](https://github.com/Mars2004/mlogging)
 - [MarsTech Config](https://github.com/Mars2004/mconfig)
 - [MarsTech Threading](https://github.com/Mars2004/mthreading)
 - [MarsTech Dll Factory](https://github.com/Mars2004/mdllfactory)
 - [MarsTech Module](https://github.com/Mars2004/mmodule)
 - [MarsTech C++ SYS](https://github.com/Mars2004/msys)
 - [inih](https://github.com/jtilly/inih)
 - [SQLite3](https://www.sqlite.org/index.html)

### Configuration
No build configuration is needed - just build whole solution. Application passive configuration is stored in "config.ini".

## Source Code Documentation
You can find generated source code documentation at [https://www.marstech.cz/projects/msys/1.0.1/doc](https://www.marstech.cz/projects/msys/1.0.1/doc).

## License
This project is released under GNU General Public License version 3. If you can not or do not want to accept GNU GPLv3 license and you would like to use this project under another license, please contact me on [info@marstech.cz](mailto:info@marstech.cz) or visit [www.marstech.cz](https://www.marstech.cz/en).
