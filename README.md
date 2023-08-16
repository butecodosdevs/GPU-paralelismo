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
E é necessário baixar o ![CMake](https://cmake.org/download/), recomendo olhar os arquivos  
de ![build do CMake](demo/CMakeLists.txt) e ![os arquivos de script de build.](demo/compilar-win32.bat)

Para compilar no Kernel do Linux, pode executar os mesmo comandos portanto que tenha baixado todas as depêndencias.  

🐈‍⬛ -> 🐈 -> 🐈‍⬛ -> 🐈 -> 🐈‍⬛

----

![Sumario](sumario/sumario.md) 

![Apresentação e introdução](1/1-.md)  
![Qual a base de conhecimento e a preparação necessária para iniciar nessa área](2/2-.md)  
![Quais os diferentes campos e sua situação no mercado exterior](3/3-.md)  
![Situação do Brasil e o campo graphics programming](4/4-.md)  

---

🐈
