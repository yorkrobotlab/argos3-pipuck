# argos3-pipuck
ARGoS3 Plug-in for the pi-puck

## Compiling the code

Make sure you have ARGoS >= 3.0.0-beta56 installed

### If you have ARGoS installed system-wide
Commands:
```shell
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ../src
make
sudo make install
```

### If you have ARGoS installed locally

Make sure your environment variables are set up properly.
If you haven't set them up, set them up in bash like so (or add them to the end of your ~/.bashrc file):

```shell
export LD_LIBRARY_PATH=path/to/argos3_install/lib/argos3/:$LD_LIBRARY_PATH
export PKG_CONFIG_PATH=path/to/argos3_install/lib/pkgconfig/:$PKG_CONFIG_PATH
export PATH=path/to/argos3_install/bin:$PATH
```

Next do the following

```shell
mkdir build
cd build
cmake -D CMAKE_INSTALL_PREFIX=/DIR -DCMAKE_BUILD_TYPE=Release ../src
make
sudo make install
```

## Testing the code

You can check that the plugin has been properly installed by running the following command

```shell
argos3 -q pipuck
```
There is a demo that loads a lua controller that shows how to drive the robot around, how to use the ground sensors, and how to control the LEDs. You can run this with the following command:

```shell
argos3 -c path/to/argos3-pipuck/build/testing/pi-puck/test_pipuck.argos
```





