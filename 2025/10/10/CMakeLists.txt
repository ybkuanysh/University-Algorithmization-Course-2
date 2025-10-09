# Переменные для общих путей
set(LIB_SOURCE_DIR "lib/src")
set(LIB_INCLUDE_DIR "lib/inc")

# --- Библиотека для задания Базового уровня ---
add_library(Glazunova_5_2_basic_lib STATIC
    ${LIB_SOURCE_DIR}/glazunova_5_2_basic_lib.cpp
)
target_include_directories(Glazunova_5_2_basic_lib PUBLIC
    ${LIB_INCLUDE_DIR}
)

# --- Библиотека для задания Среднего уровня ---
add_library(Glazunova_5_2_middle_lib STATIC
    ${LIB_SOURCE_DIR}/glazunova_5_2_middle_lib.cpp
)
target_include_directories(Glazunova_5_2_middle_lib PUBLIC
    ${LIB_INCLUDE_DIR}
)
