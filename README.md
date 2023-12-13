# GPU-paralelismo
The aulas of gatinhos ao mesmo tempo

Primeira aula:  
não gravou 🐈‍⬛🐮

Última aula:  
https://www.youtube.com/watch?v=TI9cmXJWuag

[Foi escrito uma demo em C++ que implementa uma simulação de um tecido-malha 3D em OpenGL](demo/),  
em uma janela do [SDL2](https://www.libsdl.org/).  

O compilador usado foi o GCC, no Windows [MinGW-64w](https://www.mingw-w64.org/downloads/).  
É necessário baixar o [CMake](https://cmake.org/download/).

A biblioteca usada para obter as funções de extensão novas do OpenGL 4 é o [GLEW](https://glew.sourceforge.net/).  
A biblioteca de matemática usada para fazer operações matemática de álgebra linear é o [GLM](https://github.com/g-truc/glm).

No caso do Windows, foi disponibilizado as bibliotecas nativas prontas para serem copiadas  
no caminho de bibliotecas do toolchain (compilador).  As DLLs das biblioteca são 64.

Para compilar no Linux, são os mesmo comandos portanto que tenha baixado todas as depêndencias.  
Devem ser baixadas `libsdl2-dev` e o `libglew-dev` com o gerenciador de pacotes do seu Linux.

`./demo/` Código fonte do simulador de malha 3D em C++.  

```bat
:: cd demo/

:: O CMake é uma linguagem intermediaria que gera makefiles para compilar cada arquivo
:: do C++.

:: S é de SOURCE, o . atual diz a pasta que o CMakeLists.txt está.
:: B é de BUILD, e diz aonde queremos que o CMake gere arquivos makefile.
:: G significa qual tipo de makefile para o toolchain (compilador) gerar,
:: poderiamos gerar makefiles com "MinGW Makefiles", ou
:: "Unix Makefiles" para sistema operacionais Linux.

:: Se você estiver no Linux:
cmake -S . -B ./cmake-build-debug -G "Unix Makefiles"

:: Se você estiver no Windows:
cmake -S . -B ./cmake-build-debug -G "MinGW Makefiles"

:: --build é um comando para pegar tudo que foi construido pelo comando acima,
:: e compilar o programa.
cmake --build ./cmake-build-debug
```

Em consideração foi escrito um site em cima do webgl que renderiza efeitos procedurais pela GPU. Use as teclas (left, right, up, down) para modificiar o efeito na tela.  
https://chorumedev.github.io/GPU-paralelismo/

`./index.html` HTML do site.  
`./website/` Scripts do site.  

🐈‍⬛ -> 🐈 -> 🐈‍⬛ -> 🐈 -> 🐈‍⬛

----

[Apresentação e introdução](1/1-.md) 
- Resumo sobre a GPU e a sua importância de um modo geral.

[Qual a base de conhecimento e a preparação necessária para iniciar nessa área](2/2-.md)  
- Informação sobre o conhecimento necessário para prosseguir com essa carreira.

[Quais os diferentes campos e sua situação no mercado exterior](3/3-.md)  
- Situação no mercado atual e como é o trabalho.  

[Situação do Brasil e o campo graphics programming](4/4-.md)
- Situação no cenário Brasileiro e uma crítica.

[Resumo sobre central processor unit (CPU) e graphics processor unit (GPU), e sua implementação via software](6/6-.md)  
- Um funcionamento geral dos microprocessadores e uma analise mais profunda sobre o funcionamento no caso das GPUs.
- Analise sobre as APIs de propósito gerais, aprofundamento sobre a filosofia das APIs modernas e suas diferenças com as legadas (OpenGL, DirectX 11).

[Diferenças entre APIs, detalhes e processo do pipeline gráfico.](7/7-.md)
- Uma analise mais profunda sobre as filosofias do Vulkan e OpenGL.
- O que é um buffer? sobre o termo buffer comumente usado em várias APIs.
- Processo de fetch de shader e detalhes sobre a execução das shaders.

[Microarquiteturas de fornecedores: NVIDIA, AMD e Intel](8/8-.md)
- Um pouco sobre as microarquiteturas e suas técnologias.
- Como diferentes fornecedores criam extensões para as APIs.
- Incompatibilidades de shaders.

---

# Agradecimentos, créditos e refêrencias.

Embora eu tenha escrito os textos, não posso deixar de citar as refêrencias das quais tive (e não só para esse projeto, mas durante meus anos de estudo).  
Outra coisa que preciso salientar, é que todo esse meu conhecimento não foi do dia para a noite, e não sei nem 5% sobre esse assunto, reconheço minha ignorância sobre alguns
aspectos desse assunto, busco compartilhar o que sei, e se estou errada, por favor, me corrija.  
Se você se interessou, não deixe de pesquisar, ir atrás, aprender ❤️💕.

Fetch de shaders no OpenGL: https://www.khronos.org/opengl/wiki/Shader  
Conceitos de rederização: https://developer.nvidia.com/gpugems/gpugems/contributors    
Stream processors: https://developer.nvidia.com/gpugems/gpugems2/part-iv-general-purpose-computation-gpus-primer/chapter-29-streaming-architectures  
OpenGL na Nvidia: https://on-demand.gputechconf.com/siggraph/2016/presentation/sig1609-kilgard-jeffrey-keil-nvidia-opengl-in-2016.pdf  
Livro citado: https://www.realtimerendering.com/  
Site interessante: https://iquilezles.org/articles/  
Especificações do i3 8100: https://www.intel.com.br/content/www/br/pt/products/sku/126688/intel-core-i38100-processor-6m-cache-3-60-ghz/specifications.html  
Intel ARC microarquitetura: https://www.intel.com.br/content/www/br/pt/products/docs/discrete-gpus/arc/technology/xe-hpg-microarchitecture.html  
NVIDIA Ada Lovelace (citei um texto): https://www.nvidia.com/pt-br/geforce/ada-lovelace-architecture/  
Preview da RX 480: https://www.anandtech.com/show/10446/the-amd-radeon-rx-480-preview/3  
Stream processing: https://pt.wikipedia.org/wiki/Stream_processing  
CPU pipeline: https://pt.wikipedia.org/wiki/Pipeline_(hardware)  
SIMD: https://en.wikipedia.org/wiki/Single_instruction,_multiple_data  
Pipeline de instruções: https://en.wikipedia.org/wiki/Instruction_pipelining   

🐈💕
