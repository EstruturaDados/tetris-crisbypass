# CMakeList.txt: arquivo de projeto de CMake de nível superior, fazer configuração global
# e possibilita incluir subprojetos aqui.

cmake_minimum_required (VERSION 3.8)

# Habilite a Recarga Dinâmica para compiladores MSVC, se houver suporte.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Projeto primário.

project ("tetris")

# Inclua subprojetos, se desejar.

# add_subdirectory ("tetris")

# Executáveis.
add_executable(tetris_novato "tetris_novato.c")
add_executable(tetris_aventureiro "tetris_aventureiro.c")
add_executable(tetris_mestre "tetris_mestre.c")

# Configuração de Warnings, etc.
foreach(target tetris_novato tetris_aventureiro tetris_mestre)
    if(MSVC)
        target_compile_options(${target} PRIVATE
            /W3          # Warning level 3
            /wd4996      # Desabilita warning de funções deprecated
            /WX-         # Não trata warnings como erros            
        )
    else()
        target_compile_options(${target} PRIVATE
            -Wall
            -Wextra
            -Wno-unused-parameter
            -Wno-unused-variable
            -Werror       # Warnings como erros
        )
    endif()
endforeach()

