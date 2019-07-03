# Moxa Platform Example codes

We provide the following example codes:
* [hello world](/hello)
* [crypto device](/cryptodev)
* [rtc](/rtc)
* [watchdog](/watchdog)
* [moxa-gpio-control](https://github.com/Moxa-Linux/moxa-gpio-control/tree/master/example)
* [moxa-dio-control](https://github.com/Moxa-Linux/moxa-dio-control/tree/master/example)
* [moxa-uart-control](https://github.com/Moxa-Linux/moxa-uart-control/tree/master/example)
* [moxa-led-control](https://github.com/Moxa-Linux/moxa-led-control/tree/master/example)
* [moxa-push-button](https://github.com/Moxa-Linux/moxa-push-button/tree/master/example)

Click the link to see the example codes.

## Makefile example

We provide Makefile for all examples.

On Moxa UC devices, you can build example codes easily by using `make`.

Install build-essential for `make` tool:
```
# apt-get install build-essential
```

Build codes:
```
# make
```

If you want to cross compile on a x86 computer, just add parameters when using `make`:
```
# make CC=arm-linux-gnueabihf-gcc
```