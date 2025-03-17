add_library(${PROJECT_NAME}_lib STATIC 
    stb_image/stb_image.cpp
    image_handler.cpp
)

target_include_directories(${PROJECT_NAME}_lib PUBLIC 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/stb_image
)

