# See the build system documentation in IDF programming guide
# for more information about component CMakeLists.txt files.

idf_component_register(
    SRCS 
        "main.c"
        "../Src/Hal/DHT11/dht.c"
        "../Src/Hal/MQTT/mqtt.c"
        "../Src/Hal/WiFi/wifi.c"
        "../Src/App/EnviroSense/envirosense.c"      # list the source files of this component
    INCLUDE_DIRS 
        "."
        "../Src/Hal/DHT11"
        "../Src/Hal/MQTT"
        "../Src/Hal/WiFi"
        "../Src/App/EnviroSense"      # optional, add here public include directories
    PRIV_INCLUDE_DIRS   # optional, add here private include directories
    REQUIRES            # optional, list the public requirements (component names)
    PRIV_REQUIRES       # optional, list the private requirements
)


