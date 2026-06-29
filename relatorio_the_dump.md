# UNIVERSIDADE INDEPENDENTE DE ANGOLA (UNIA)
## Faculdade de Engenharia e Tecnologias
### Curso de Engenharia Informática

---

# THE DUMP - O PESADELO DO LIXO
## Relatório do Projecto de Computação Gráfica

---

**Autor:** António Sebastião Pedro  
**Data:** Junho de 2026  
**Repositório Github:** [https://github.com/AntonioSebastiaoPedro/the-dump.git](https://github.com/AntonioSebastiaoPedro/the-dump.git)

---

## RESUMO

Este relatório documenta o desenvolvimento do jogo **"The Dump - O Pesadelo do Lixo"**, um jogo de tiro em primeira pessoa (FPS) com estética retro, desenvolvido inteiramente na linguagem de programação C pura. O projecto foi inicialmente proposto para ser desenvolvido na ferramenta Blender, contudo, como desafio pessoal e com a finalidade de aplicar de forma profunda e prática os conhecimentos matemáticos e algorítmicos leccionados na disciplina de Computação Gráfica, optou-se por construir o motor gráfico do zero.

Para tal, utilizou-se o algoritmo de *Raycasting*, *Digital Differential Analysis (DDA)* para detecção de colisões tridimensionais, bem como a manipulação directa de pixéis através da biblioteca *MiniLibX* (abstracção do X11 no Linux). O resultado é um jogo completo, com áudio espacial, inteligência artificial para os inimigos, sistema de progressão de níveis, renderização paralela com *threads* (para optimização de *performance*) e gestão complexa de texturas.

---

## 1. INTRODUÇÃO

O presente documento visa descrever as regras, jogabilidade, estrutura técnica e o cumprimento dos critérios de avaliação exigidos para o projecto prático de Computação Gráfica. O jogo "The Dump" coloca o jogador num ambiente hostil, inspirado nos clássicos dos anos 90 como *Wolfenstein 3D* e *Doom*, onde a sobrevivência e a navegação em labirintos tridimensionais são fundamentais.

### 1.1. Justificativa da Escolha da Tecnologia (C Puro vs Blender)

A escolha de desenvolver o jogo em C puro, abdicando de motores gráficos de alto nível como o Blender (ou Unity/Unreal), deve-se à vontade de compreender e implementar os fundamentos da Computação Gráfica. Ao criar o motor gráfico do zero, conceitos como matrizes de transformação, projecção de câmara, algoritmos de rasterização de linhas (DDA) e renderização de polígonos/texturas foram aplicados na prática. As texturas 2D actuam como os nossos "objectos modelados" no mundo tridimensional calculado matematicamente a cada *frame*.

---

## 2. REGRAS DO JOGO E JOGABILIDADE

Este capítulo descreve como o jogo funciona do ponto de vista do utilizador, abordando como jogar, vencer e os desafios enfrentados.

### 2.1. Como se Joga (Mecânicas e Controles)

O jogador assume o papel de um sobrevivente equipado com um arsenal de três armas distintas: Revólver, Gatling/Plasma e Rifle de Ferrolho. O objectivo central é navegar por um complexo de labirintos, encontrar chaves para destrancar portas, gerir recursos (munição e vida) e eliminar as ameaças.

*   **Movimentação:** O jogador move-se utilizando as teclas clássicas `W`, `A`, `S`, `D`.
*   **Câmara:** A visão é controlada pelo rato, permitindo uma rotação livre horizontal de 360 graus para explorar o ambiente.
*   **Interacção:** A tecla `Espaço` é utilizada para interagir com o ambiente (abrir portas).
*   **Combate:** O botão esquerdo do rato ou a tecla `Enter` são usados para disparar a arma equipada. As teclas numéricas `1`, `2` e `3` alternam as armas.
*   **Navegação Táctica:** A tecla `U` abre um minimapa táctico amplo, auxiliando na navegação em níveis complexos.

### 2.2. Como se Ganha e se Perde

*   **Progressão e Vitória:** O jogo possui uma campanha linear composta por **10 níveis progressivos**, culminando num **Nível de Chefe (Boss)**. Para avançar de nível, o jogador deve explorar o mapa e eliminar *todos* os inimigos presentes. No nível final, derrotar o Chefe Gigante garante a vitória absoluta e despoleta a tela de *Victory*.
*   **Derrota:** O jogador começa com 100 pontos de vida (HP). Se receber dano de inimigos (Soldados, Cães, Oficiais) ou for apanhado pela explosão de um barril interativo, a vida diminui. Se os pontos de vida chegarem a zero, o jogador morre, o jogo termina e surge a tela de *Game Over*.

---

## 3. COMPONENTE TÉCNICA E CRITÉRIOS DE AVALIAÇÃO

Neste capítulo, detalhamos como os códigos, algoritmos e abordagens técnicas foram utilizados para tornar o jogo possível, demonstrando o cumprimento de todos os critérios estabelecidos pelo professor.

### 3.1. [Critério 2] Jogador e Sistema de Som

O jogo conta com um sistema de primeira pessoa bem definido. O jogador (estrutura `t_player`) possui coordenadas cartesianas no mapa `(pos_x, pos_y)`, um vector de direcção `(dir_x, dir_y)` e um vector de plano de câmara `(plane_x, plane_y)` que definem o FOV (Campo de Visão).

Para a componente de áudio, utilizou-se a biblioteca **BASS** em C. No ficheiro `audio.c`, foram programados canais independentes (`HCHANNEL`) para reproduzir o som ambiente contínuo (em *loop*), os passos do jogador (sincronizados com a movimentação) e efeitos de evento sonoros espaciais (disparos de armas diferentes, grunhidos de inimigos, latidos de cães, explosões e som de portas a abrir).

### 3.2. [Critério 3] Objectos Diferentes e "Modelados"

Como o jogo foi construído num motor pseudo-3D customizado em C, o conceito de "modelagem" foi adaptado para a projecção matemática de texturas (Sprites) no espaço 3D. O jogo utiliza mais de 8 objectos e entidades diferentes que possuem física, volume percepcionado no motor de renderização e animações lógicas próprias:
1.  **Armas (3 tipos):** Revólver, Plasma e Rifle (com animações frame-a-frame de recuo).
2.  **Inimigos (4 tipos):** Soldado padrão, Cão de caça (veloz, corpo-a-corpo), Oficial (longa distância) e o Chefe Final.
3.  **Portas e Portas Trancadas:** Objectos que bloqueiam raios de visão e necessitam de interacção para abrir (animações de deslizamento).
4.  **Barril Explosivo:** Objecto estático interativo que calcula o raio de colisão quando atingido e causa dano em área (AOE).
5.  **Planta Dourada:** Um *power-up* que concede invencibilidade temporária.
6.  **Poço de Água:** Item de cura (restaura HP até ao máximo).
7.  **Kit Médico:** Cura e fornece munição para todas as armas.
8.  **Chave Azul:** Item coletável obrigatório para destrancar áreas seladas no mapa.

### 3.3. [Critério 4] Trabalhar com Diferentes Luzes

A iluminação em C puro num motor de raycasting foi alcançada através de técnicas de sombreamento por distância matemática e variação de paleta de cores.
1.  **Distance Shading (Z-Buffer):** As paredes e objectos perdem luminosidade consoante a distância (calculada no algoritmo DDA - `ray->perp_wall_dist`). Quanto mais longe o raio intersecta a parede, mais escura a cor do pixel é desenhada.
2.  **Ambiente por Estágio:** Cada um dos 10 mapas (`.cub`) possui configurações específicas para as cores do tecto (`C`) e do chão (`F`), simulando a iluminação ambiente. À medida que o jogador avança (ex: Nível 1 vs Nível do Boss), os parâmetros de luminosidade ambiente mudam drasticamente, passando de tons abertos para ambientes mais escuros e opressivos (como tons de vermelho escuro).

### 3.4. [Critério 5] Câmeras e Mudança de Ângulos

A manipulação da câmara foi implementada utilizando a matemática vetorial 2D combinada com matrizes de rotação.
Quando o rato é movido, os vectores de direcção da câmara (`dir_x`, `dir_y`) e o plano da câmara (`plane_x`, `plane_y`) são rodados. O código (ex: `cub->player->dir_x = dir_x * cos(rot) - dir_y * sin(rot)`) recalcula constantemente o ângulo, mudando a perspectiva em tempo real a 60 FPS.
Além da câmara principal de Primeira Pessoa, existe uma **Segunda Câmara**: o Radar / Minimapa Táctico. Esta câmara possui visão *Top-Down* (de cima para baixo), projectando raios (com *Bresenham's Line Algorithm* ou varrimentos radiais) para demonstrar as paredes adjacentes e a direcção para a qual o campo de visão da câmara principal está a apontar.

### 3.5. [Critério 6] Mínimo de 3 Níveis

O requisito mínimo foi amplamente superado. O projecto contém um sistema de *Level Manager* (`level_manager.c`) estruturado que carrega um vector sequencial de **10 mapas** (`level1.cub` a `level10.cub`), além do nível derradeiro do Boss (`boss.cub`).
Cada nível obedece a um *parser* customizado que lê o mapa de um ficheiro de texto, o que torna a criação de novos níveis extremamente modular e fácil.

### 3.6. [Critério 7] Tempo de Jogo (Cronómetro / Temporizador)

O factor de tempo foi incluído intrinsecamente na mecânica vital da **Planta Dourada** (*Gold Buff*). Ao recolher este item, inicia-se um **temporizador global de 10 segundos**. O temporizador utiliza a função `gettimeofday` na variável de *delta time* do motor para atualizar um *HUD* de cronómetro preciso que surge no ecrã. Durante este período contabilizado pelo cronómetro regressivo, o jogador ignora os cálculos de dano infligido pelos inimigos.

### 3.7. [Critério 8] Acrescentar Algo Novo (O Desafio C)

O maior diferencial e acréscimo deste projecto foi a própria implementação tecnológica do zero:
1.  **Motor Gráfico Criado de Raiz (Raycasting Engine):** Em vez de colocar objectos num ambiente 3D pré-construído do Blender, escrevi o algoritmo **DDA (Digital Differential Analyzer)** para efectuar *Ray Tracing* nas grelhas lógicas bidimensionais.
2.  **Multithreading em C (`pthread`):** Como os cálculos matemáticos para cada pixel horizontal no ecrã (1920x1080) são muito pesados para uma única *thread*, implementei um sistema de *Thread Pool* (*render.c* / *structs.h*) dividindo a tela em 4 secções processadas em paralelo. Isto manteve o jogo perfeitamente fluido a 60 FPS no sistema Linux.
3.  **Inteligência Artificial (Pathfinding e Flow Fields):** Os inimigos não se movem de forma aleatória. Foi implementado o algoritmo *Line of Sight (LOS)* para que saibam quando o jogador os pode ver, e um sistema avançado de *Flow Field Pathfinding* para que os cães contornem paredes e perigam o jogador inteligentemente através do labirinto (vide `enemy_ai.c`).

---

## 4. CONCLUSÃO

O projecto "The Dump" revelou-se um desafio imensamente gratificante. Abdicar das ferramentas facilitadoras modernas do Blender para entender o comportamento dos fotões virtuais através de *Raycasting* exigiu um aprofundamento sólido nas bases da trigonometria e cálculo vetorial.

Todos os requisitos exigidos pelo docente para a disciplina foram rigorosamente cumpridos, adaptados ao paradigma do desenvolvimento *low-level*. A gestão de memória dinâmica, renderização por *threads*, matrizes de som e simulação de câmara e luz por atenuação de distância garantiram que o projecto não só fosse um jogo funcional, como um motor computacional de aprendizagem.

O repositório do projecto contendo o código C e o ficheiro Make para a sua compilação está disponível no Github em anexo para validação e consulta.
