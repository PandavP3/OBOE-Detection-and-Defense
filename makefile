PLUGIN_NAME = gcc_oboe_plugin.so
PLUGIN_SRC = gcc_oboe_plugin.cpp
PLUGIN_OUT = sample
GCC_PLUGIN_DIR = /usr/lib/gcc/x86_64-linux-gnu/14/plugin/include

all: plugin compile

plugin:
        g++ -Wall -fPIC -shared -fno-rtti -fno-exceptions -o $(PLUGIN_NAME) $(PLUGIN_SRC) -I$(GCC_PLUGIN_DIR)

compile:
        g++ -fplugin=./$(PLUGIN_NAME) test.cpp -o $(PLUGIN_OUT)

clean:
        rm -f *.so $(PLUGIN_OUT)
