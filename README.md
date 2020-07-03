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

As you’ll be using custom models, you need to make sure ARGoS is looking for them in the correct directory. (For more information on this, see the [README](https://github.com/ilpincy/argos3/blob/master/README.asciidoc "ARGoS README") for ilpincy/argos3)
If you’re using Linux, you need to edit `$HOME/.config/Iridia-ULB/ARGoS.conf` with the following:
```shell
[MainWindow]
#
# other stuff
#
icon_dir=/PATH/TO/argos3/src/plugins/simulator/visualizations/qt-opengl/icons/
texture_dir=/PATH/TO/argos3/src/plugins/simulator/visualizations/qt-opengl/textures/
model_dir=/PATH/TO/argos3/src/plugins/simulator/visualizations/qt-opengl/models/
#
# more stuff
#
```
On Mac, write the following into your command line:
```shell
$ defaults write info.argos-sim.ARGoS MainWindow.texture_dir -string "/PATH/TO/argos3/src/plugins/simulator/visualizations/qt-opengl/textures/"
$ defaults write info.argos-sim.ARGoS MainWindow.model_dir -string "/PATH/TO/argos3/src/plugins/simulator/visualizations/qt-opengl/models/"
$ defaults write info.argos-sim.ARGoS MainWindow.icon_dir -string "/PATH/TO/argos3/src/plugins/simulator/visualizations/qt-opengl/icons/"
$ killall -u YOURUSERNAME cfprefsd
```
substituting /PATH/TO/ with the path to your ARGoS installation and and USERNAME with your own username.

You should now be able to run the pipuck example with
```shell
argos3 -c path/to/argos3-pipuck/build/testing/pi-puck/test_pipuck.argos
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





