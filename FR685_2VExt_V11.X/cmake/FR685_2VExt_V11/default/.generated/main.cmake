include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")

set(FR685_2VExt_V11_default_library_list )

set(OUTPUT_SUFFIX elf)
# Handle files with suffix (s|as|asm|AS|ASM|As|aS|Asm), for group default-XC8
if(FR685_2VExt_V11_default_default_XC8_FILE_TYPE_assemble)
add_library(FR685_2VExt_V11_default_default_XC8_assemble OBJECT ${FR685_2VExt_V11_default_default_XC8_FILE_TYPE_assemble})
    FR685_2VExt_V11_default_default_XC8_assemble_rule(FR685_2VExt_V11_default_default_XC8_assemble)
    list(APPEND FR685_2VExt_V11_default_library_list "$<TARGET_OBJECTS:FR685_2VExt_V11_default_default_XC8_assemble>")

endif()

# Handle files with suffix S, for group default-XC8
if(FR685_2VExt_V11_default_default_XC8_FILE_TYPE_assemblePreprocess)
add_library(FR685_2VExt_V11_default_default_XC8_assemblePreprocess OBJECT ${FR685_2VExt_V11_default_default_XC8_FILE_TYPE_assemblePreprocess})
    FR685_2VExt_V11_default_default_XC8_assemblePreprocess_rule(FR685_2VExt_V11_default_default_XC8_assemblePreprocess)
    list(APPEND FR685_2VExt_V11_default_library_list "$<TARGET_OBJECTS:FR685_2VExt_V11_default_default_XC8_assemblePreprocess>")

endif()

# Handle files with suffix [cC], for group default-XC8
if(FR685_2VExt_V11_default_default_XC8_FILE_TYPE_compile)
add_library(FR685_2VExt_V11_default_default_XC8_compile OBJECT ${FR685_2VExt_V11_default_default_XC8_FILE_TYPE_compile})
    FR685_2VExt_V11_default_default_XC8_compile_rule(FR685_2VExt_V11_default_default_XC8_compile)
    list(APPEND FR685_2VExt_V11_default_library_list "$<TARGET_OBJECTS:FR685_2VExt_V11_default_default_XC8_compile>")

endif()

# Handle files with suffix elf, for group default-XC8
if(FR685_2VExt_V11_default_default_XC8_FILE_TYPE_objcopy_lss)
add_library(FR685_2VExt_V11_default_default_XC8_objcopy_lss OBJECT ${FR685_2VExt_V11_default_default_XC8_FILE_TYPE_objcopy_lss})
    FR685_2VExt_V11_default_default_XC8_objcopy_lss_rule(FR685_2VExt_V11_default_default_XC8_objcopy_lss)
    list(APPEND FR685_2VExt_V11_default_library_list "$<TARGET_OBJECTS:FR685_2VExt_V11_default_default_XC8_objcopy_lss>")

endif()


# Main target for this project
add_executable(FR685_2VExt_V11_default_image_DgC3OHwF ${FR685_2VExt_V11_default_library_list})

set_target_properties(FR685_2VExt_V11_default_image_DgC3OHwF PROPERTIES
    OUTPUT_NAME "default"
    SUFFIX ".elf"
    ADDITIONAL_CLEAN_FILES "${output_extensions}"
    RUNTIME_OUTPUT_DIRECTORY "${FR685_2VExt_V11_default_output_dir}")
target_link_libraries(FR685_2VExt_V11_default_image_DgC3OHwF PRIVATE ${FR685_2VExt_V11_default_default_XC8_FILE_TYPE_link})
# Add the link options from the rule file.
FR685_2VExt_V11_default_link_rule( FR685_2VExt_V11_default_image_DgC3OHwF)


#Add objcopy steps
FR685_2VExt_V11_default_objcopy_lss_rule(FR685_2VExt_V11_default_image_DgC3OHwF)

