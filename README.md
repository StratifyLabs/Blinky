# Blinky

This project shows just how easy it is to write programs for Stratify OS.  Stratity OS including accessing GPIO and using timers.

If you haven't already done so, you need to get set up with some hardware and the software tools using the [Stratify Labs web application](https://app.stratifylabs.co/) which has installation instructions and tutorials.

Once you install the command line tool, you can clone and build Blinky using:

```
sl application.create:name=Blinky,from=Blinky
sl application.build:path=Blinky
sl application.install:path=Blinky,run,terminal # need connected hardware for this one
```

