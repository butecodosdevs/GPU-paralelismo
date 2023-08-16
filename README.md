# GPU-paralelismo
The aulas of gatinhos ao mesmo tempo

![Foi escrito um programa em C++ que implementa uma pequena demonstração do uso da GPU com OpenGL](demo/),  
em uma janela do ![SDL2](https://www.libsdl.org/).  

A biblioteca usada para obter as funções de extensão novas do OpenGL 4 é o ![GLEW](https://glew.sourceforge.net/).  
A biblioteca de matemática usada para fazer operações matemática de álgebra linear é o ![GLM](https://github.com/g-truc/glm).

As DLLs das biblioteca são 64, o mesmo programa pode ser compilado no Linux,  
mas você precisa baixar o `libsdl2-dev` e o `libglew-dev` com o gerenciador de pacotes.

No caso do Windows, foi disponibilizado as bibliotecas nativas prontas para serem copiadas  
e no caminho de bibliotecas do toolchain (compilador).

O compilador usado foi o GCC, no Windows ![MinGW-64w](https://www.mingw-w64.org/downloads/).  
E é necessário baixar o ![CMake](https://cmake.org/download/).

Para compilar no Kernel do Linux, pode executar os mesmo comandos portanto que tenha baixado todas as depêndencias.  

```bat
:: demo/

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
```

🐈‍⬛ -> 🐈 -> 🐈‍⬛ -> 🐈 -> 🐈‍⬛

----

![Sumario](sumario/sumario.md) 

![Apresentação e introdução](1/1-.md)  
![Qual a base de conhecimento e a preparação necessária para iniciar nessa área](2/2-.md)  
![Quais os diferentes campos e sua situação no mercado exterior](3/3-.md)  
![Situação do Brasil e o campo graphics programming](4/4-.md)  

---

🐈
