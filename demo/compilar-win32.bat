:: O CMake é uma linguagem intermediaria que gera makefiles para compilar cada arquivo
:: do C++.

:: S é de SOURCE, o . atual diz a pasta que o CMakeLists.txt está.
:: B é de BUILD, e diz aonde queremos que o CMake gere arquivos makefile.
:: G significa qual tipo de makefile para o toolchain (compilador),
:: nesse caso é o ninja, mas poderiamos gerar makefiles com "MinGW Makefiles",
:: ou "Unix Makefiles" para sistema operacionais Linux.

cmake -S . -B ./cmake-build-debug -G "Ninja"

:: --build é um comando para pegar tudo que foi construido pelo comando acima,
:: e compilar o programa.
cmake --build ./cmake-build-debug