# Dizemos a versão.
cmake_minimum_required(VERSION 3.9)

# Nome do projeto.
project(chorume)

# Nesse set especificamos a versão do C++ 
set(CMAKE_CXX_STANDARD     17)

# Por padrão a pasta aonde o executavel é gerado,
# é dentro dos arquivos gerados pelo cmake.
# Mas para mudarmos isso, basta alterar o caminho
# voltando uma pasta usando ../ e colocando uma
# pasta nova.
set(EXECUTABLE_OUTPUT_PATH "../build")


# O CMake te deixa gerar construir um projeto para diferentes plataformas.
if(WIN32)
    set(THIRD_PARTY_LIBRARIES mingw32 SDL2main SDL2 glew32 opengl32)
else()
    set(THIRD_PARTY_LIBRARIES glew SDL2main SDL2) # Os linkers do Linux são diferentes.
endif()

# GLOB RECURSE, significa que essa função vai buscar por qualquer arquivo
# source, mesmo dentro de pastas (recursivo).
file(GLOB_RECURSE SRC_FILES "src/*.cpp")

# Add executable é um comando para criar o executavel,
# adicionando os arquivos de cima.
add_executable(chorume ${SRC_FILES})

# Target link libraries é para embutir as bibliotecas
# dentro do executavel.

# Nesse caso, algumas bibliotecas do compilador MinGW devem
# ser embutidas junto ao executavel, pois isso bate com
# a licensa de distribuição das DLLs do toolchain.
# Essas bibliotecas são a padrão do C++.

target_link_libraries(chorume ${THIRD_PARTY_LIBRARIES}
                              -static-libgcc -static-libstdc++)