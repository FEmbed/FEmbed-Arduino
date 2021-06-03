idf_build_get_property(components_to_build BUILD_COMPONENTS)

set(src)
set(include)
set(priv_requires)

set(srcs    "src/esp_port.c"
            "src/base64.cpp" 
            "src/libb64/cdecode.c"
            "src/libb64/cencode.c"
            "src/crc.cpp"
            "src/md5.c" 
            "src/MD5Builder.cpp"
            "src/IPAddress.cpp"
            "src/Stream.cpp"
            "src/Print.cpp"
            "src/StreamString.cpp"
            "src/WMath.cpp"
            "src/WString.cpp"
            )
set(include "src" )

idf_component_register(SRCS "${srcs}"
                       INCLUDE_DIRS ${include}
                       PRIV_REQUIRES ${priv_requires})