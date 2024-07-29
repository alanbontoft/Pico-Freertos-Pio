add_executable(${PROJECT_NAME})

pico_generate_pio_header(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/ledcounter.pio)

target_sources(${PROJECT_NAME} PRIVATE main.c)

target_link_libraries(${PROJECT_NAME} PRIVATE pico_stdlib hardware_pio freertos)

pico_add_extra_outputs(${PROJECT_NAME})

pico_enable_stdio_usb(${PROJECT_NAME} 0)
pico_enable_stdio_uart(${PROJECT_NAME} 1)

