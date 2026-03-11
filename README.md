🎒 Long Prep

Long Prep é um protótipo de jogo em desenvolvimento focado em um sistema de inventário físico, inspirado em jogos como Resident Evil e Cairn, onde os itens possuem peso, colisão e comportamento físico dentro da mochila.

A ideia é transformar o inventário em um espaço interativo, onde os objetos realmente caem, se empilham e ocupam espaço, em vez de apenas existir em slots estáticos.

🧠 Ideia do Projeto

Em muitos jogos o inventário é apenas uma grade simples.
Neste projeto, a proposta é criar um sistema onde:

📦 Itens possuem forma e tamanho

⚖️ Existe peso e física

🪨 Objetos colidem e se empilham

🎒 A mochila funciona como um container físico

🖱️ O jogador pode arrastar e manipular os itens

🛠 Tecnologias utilizadas

🎮 Raylib — renderização gráfica e input

⚙️ Box2D — física 2D (colisão, gravidade, corpos rígidos)

🧱 C++

🔧 CMake — sistema de build multiplataforma

As dependências são baixadas automaticamente usando FetchContent, então não é necessário instalar bibliotecas manualmente.

🚀 Como rodar o projeto
1️⃣ Clonar o repositório
git clone https://github.com/hfp-br/long-prep
cd long-prep
2️⃣ Gerar o build
cmake -B build
3️⃣ Compilar
cmake --build build
4️⃣ Executar

Linux:

./build/meu_jogo

Windows:

build/Debug/meu_jogo.exe
