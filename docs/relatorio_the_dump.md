# UNIVERSIDADE INDEPENDENTE DE ANGOLA (UNIA)
## Faculdade de Engenharia e Tecnologias
### Curso de Engenharia Informática

---

# THE DUMP - O PESADELO DO LIXO
## Relatório Técnico e Académico do Projecto de Computação Gráfica

--- 

**Autor:** António Sebastião Pedro  
**Data:** Junho de 2026  
**Repositório Github:** [https://github.com/AntonioSebastiaoPedro/the-dump.git](https://github.com/AntonioSebastiaoPedro/the-dump.git)

---

## RESUMO

Este relatório documenta extensivamente o planeamento, a matemática, os algoritmos e o desenvolvimento do jogo **"The Dump - O Pesadelo do Lixo"**. Trata-se de um jogo de tiro em primeira pessoa (FPS) com estética retro, desenvolvido inteiramente na linguagem de programação C pura. Embora a proposta inicial do docente previsse a utilização de uma ferramenta gráfica de alto nível como o Blender, o projecto foi redireccionado como um desafio de engenharia de software *low-level*. A finalidade foi aplicar, de forma profunda e prática, os conhecimentos matemáticos leccionados na disciplina de Computação Gráfica, resultando na construção de um motor gráfico *Raycaster* do absoluto zero.

O resultado é uma aplicação complexa que lida com algoritmos de *Pathfinding* (Flow Fields), detecção de colisão via *Digital Differential Analysis (DDA)*, manipulação directa de memória de vídeo, *multithreading* e processamento de áudio espacial, culminando numa experiência com mais de 10 níveis jogáveis, todos totalmente personalizados a partir de um ficheiro de texto.

---

## 1. INTRODUÇÃO

No universo do desenvolvimento de videojogos, a abstracção fornecida por motores modernos esconde a complexidade matemática e algorítmica necessária para projectar um mundo tridimensional num ecrã 2D. "The Dump" regressa aos primórdios dos videojogos 3D (como *Wolfenstein 3D*), utilizando a técnica de *Raycasting*. 

O presente documento serve não apenas como manual do utilizador e guia de regras, mas como uma dissecação técnica da arquitectura do código-fonte, provando o cumprimento de todos os critérios de avaliação definidos para a cadeira de Computação Gráfica.

---

## 2. REGRAS DO JOGO E OBJECTIVOS

A premissa de "The Dump" é a sobrevivência. O jogador encontra-se num complexo labiríntico infestado de inimigos hostis e deve utilizar o ambiente e os recursos de forma estratégica para se manter vivo.

### 2.1. Condições de Vitória e Derrota
*   **Para Vencer (Como se ganha):** O jogador deve progredir através da campanha estruturada por níveis. A condição para transitar de um nível para o seguinte é **eliminar todos os inimigos** presentes no mapa actual. Ao chegar ao último nível (a câmara do *Boss*), o jogador deve derrotar o Chefe Gigante. Com a morte do *Boss*, a tela de "Victory" é exibida e o jogo é considerado concluído.
*   **Para Perder (Como se perde):** O jogador inicia com 100 pontos de vida (HP). Caso a vida atinja zero — seja por receber dano directo (tiros ou ataques corpo-a-corpo) dos inimigos, ou por se posicionar negligentemente no raio de alcance da explosão de um barril interativo —, a partida termina imediatamente, resultando na tela de "Game Over".

---

## 3. ARQUITECTURA GRÁFICA: A ILUSÃO DO 3D

Para projectar imagens tridimensionais sem o uso de hardware de aceleração 3D nativo ou bibliotecas modernas como OpenGL, o jogo socorre-se unicamente da biblioteca estrutural **MiniLibX**.

### 3.1. Manipulação de Pixéis com a MiniLibX
A MiniLibX é uma API gráfica minimalista que lida com a criação da janela no sistema X11 (ambiente Linux) e fornece ao programador uma "tela em branco" (um bloco contíguo de memória RAM). Em todo o código, as imagens e cenários são construídos pixel a pixel através da customizada função `ft_put_pixel()`. 
Isto significa que, a 60 *Frames Por Segundo* (FPS), a aplicação processa a cor e a coordenada exacta de cada um dos pixéis da resolução 1920x1080 num *buffer* de imagem fora do ecrã (*off-screen buffer*). Só após o cálculo completo de todos os pixéis é que essa imagem final é transferida e "pintada" na janela, uma técnica conhecida como *Double Buffering* que previne o indesejado efeito de cintilação (*flickering*).

### 3.2. Algoritmo DDA e Raycasting (Traçado de Raios)
O coração e o motor matemático da renderização residem na técnica do Raycasting. Em vez de modelar polígonos 3D com vértices (como no Blender), a câmara (os "olhos" do jogador) emite centenas de "raios" no plano 2D, sendo projectado exactamente um raio para cada coluna vertical de pixéis do monitor.
1.  **Emissão:** O ângulo de disparo de cada raio é calculado tendo em conta a rotação do jogador (direcção) e a largura do campo de visão (FOV), representado pelo vetor de plano da câmara.
2.  **Algoritmo DDA (Digital Differential Analyzer):** Uma vez que o mapa de jogo é uma grelha matemática rígida, o raio não precisa avançar milímetro a milímetro. O algoritmo DDA calcula os pontos exatos onde a linha do raio vai interceptar a grelha horizontal ou vertical mais próxima do mapa. Este salto constante optimiza drasticamente o processamento, descobrindo o impacto numa parede (`hit = 1`) numa fracção de milissegundo.
3.  **Projecção e Correcção:** Mal o raio atinge o obstáculo, a distância euclidiana originaria um efeito abaulado de "lente de peixe". O cálculo é convertido para distância perpendicular (`perp_wall_dist`), sendo esta usada para ditar a que altura a fatia vertical da parede (textura) deve ser desenhada no ecrã.

### 3.3. Optimização Computacional por Multithreading
Como a resolução Full HD obriga à emissão matemática de 1920 raios complexos e milhares de leituras de texturas a cada 16 milissegundos (para manter os 60 FPS), o processamento numa única *thread* central CPU estrangulava a *performance*. Para obviar este obstáculo tecnológico do C, adoptou-se a biblioteca `pthread` POSIX. O ecrã foi repartido horizontalmente em secções de trabalho assíncronas (*Thread Pool*), delegando a renderização a 4 núcleos paralelos do processador em simultâneo.

---

## 4. DESIGN DE NÍVEIS E O PARSER (CRIAÇÃO DO MUNDO)

Todo o mundo visual que o jogador experiencia provém de simples ficheiros de texto com a extensão `.cub`. Esta metodologia demonstra uma enorme separação de responsabilidades (Arquitetura) entre a Arte (Level Design) e a Lógica de Programação.

### 4.1. O Dicionário Cartográfico (Elementos da Grelha)
O motor gráfico incorpora um *parser* customizado que analisa a grelha de texto do ficheiro `.cub`. Cada letra ou número do texto possui uma tradução direta para um elemento físico, obstáculo ou entidade interagível no ambiente 3D. Abaixo detalhamos o significado semântico de cada símbolo utilizado:

*   **Obstáculos Intransponíveis e Terreno:**
    *   `1`: Representa uma **Parede Sólida** (Wall). Ela bloqueia totalmente a movimentação (física de colisão) e o raio de visão.
    *   `0`: Representa o **Chão Vazio** (Floor). Trata-se de uma célula transitável por jogadores e IA.

*   **Posicionamento do Jogador:**
    *   `N`, `S`, `E`, `W`: Determinam em que bloco `(x,y)` o jogador "nasce" no início do nível, bem como o vector cardinal para onde a sua câmara iniciará voltada (Norte, Sul, Este, Oeste).

*   **Sistemas de Portas e Interação:**
    *   `D`: **Porta Normal**. Opera como uma parede no Raycaster mas, se o jogador se aproximar e premir a tecla de interacção ("Espaço"), uma animação linear muda o estado do bloco e permite a travessia.
    *   `L`: **Porta Blindada (Trancada)**. Um obstáculo selado. A sua lógica algorítmica barra qualquer interacção até que a verificação *booleana* ateste que o jogador tem o item "Chave Azul" (`K`) no seu inventário (variável `has_blue_key = true`).

*   **Armadilha Interactiva:**
    *   `B`: **Barril Explosivo**. Um item estacionário mortal. Detalhado amplamente na secção de combate deste relatório.

*   **Entidades Inimigas (IA):**
    *   `M`: **Soldado**. Inimigo de infantaria base.
    *   `U`: **Oficial Militar**. Inimigo rápido e com projéteis.
    *   `Z`: **Cão Hostil**. Adversário baixo, veloz, que testa os reflexos de mira descendente do jogador.
    *   `X`: **Chefe Gigante (Boss)**. Surge exclusivamente nos últimos níveis como o pico de dificuldade deHP e de dano.

*   **O Ecossistema de Sobrevivência (Loot / Pickups):**
    *   `H`: **Kit Médico**.
    *   `P`: **Poço de Água Curativo**.
    *   `G`: **Planta Dourada (Gold Buff)**.
    *   `K`: **Chave Azul**.

---

## 5. RECURSOS DO MAPA E O FATOR "TEMPO" (CRITÉRIO 7)

A gestão dos itens espalhados pelos labirintos (`H`, `P`, `G`, `K`) é fundamental para manter a tensão. O jogador interage com eles de forma espacial: se a distância entre as coordenadas euclidianas do jogador e do item for inferior ao raio de recolha (`ITEM_INTERACT_DIST`), uma função consome-o, aplicando-lhe as respectivas bonificações.

*   **Recursos Vitais:**
    *   **Poço de Água (`P`):** Recupera ligeiramente o HP (`HEAL_WELL`).
    *   **Kit Médico (`H`):** Concede uma grande porção de cura (`HEAL_MEDIC_KIT`) e repõe as reservas numéricas (munição sobresselente) para as três categorias de armas.
    *   **A Chave (`K`):** O seu papel no *game design* é obrigar o jogador a explorar secções adversas repletas de perigo antes de lhe ser concedido acesso à saída.

### 5.1. O Temporizador e o Buff de Invencibilidade (Gold Buff)
Para responder diretamente ao **Critério 7 (Tempo de Jogo - Temporizador ou cronómetro)**, criámos a mecânica orgânica do **Gold Buff**, espoletada por recolher o item **Planta Dourada (`G`)**.
O jogo afasta-se de um simples "tempo corrido" e implementa um sistema de vantagem táctica associada a um *Cronómetro Regressivo*:
1.  **A Activação:** Ao caminhar por cima do item `G`, a variável de estado global do motor `cub->gold_buff_timer` é cravada no valor máximo (`INVINCIBILITY_DURATION`, geralmente 10 a 12 segundos dependendo da dificuldade). O `cub->max_gold_buff_timer` regista o limiar total para efeitos visuais.
2.  **O Declínio em Tempo Real:** No centro do *Game Loop*, no interior de `update_game()`, o cronómetro é subtraído de forma matematicamente estrita com o `delta_time` (o valor flutuante decorrido desde o último *frame*, lido fisicamente do relógio do sistema via `gettimeofday`). Isto garante precisão ao microssegundo, independente da velocidade ou quebras da máquina (Lag).
3.  **A Lógica do "God Mode":** Durante a descida deste relógio flutuante, qualquer função de dano dirigida ao jogador na Máquina de Estados do inimigo contém o seguinte *bypass*: `if (cub->gold_buff_timer <= 0) { ... receber dano ... }`. Com o timer acima de zero, os valores de ataque das armas inimigas e estilhaços de explosão são ignorados pela lógica base, conferindo Imortalidade total.
4.  **Feedback Visual (O Cronómetro HUD):** Na renderização gráfica (no `hud.c`), quando detectada a activação, o sistema interpõe um retângulo na interface com um relógio decrescente e uma barra que mingua visualmente do preenchimento amarelo, criando uma dinâmica urgente (correr contra o tempo).

---

## 6. TEXTURAS, CÂMARAS E LUZES (CRITÉRIOS 3, 4 E 5)

A exigência de incorporar múltiplos objectos modelados, diferentes iluminações e câmaras no cenário foi resolvida tirando partido das especificidades da técnica 2.5D do C.

### 6.1. O Equivalente a "Modelação" no Raycaster (Sprites)
Com a impossibilidade de importar `.obj` ou malhas tridimensionais do Blender, os objectos do jogo são renderizados recorrendo à lógica algorítmica de **Sprites**. Entidades (Inimigos, Plantas, Armas) são projectadas ortogonalmente frente à câmara do utilizador num processo complexo que envolve:
1.  Calcular o raio polar do jogador face ao item.
2.  Traduzir a posição do item baseada na matriz rotacional do plano de ecrã (câmara).
3.  Descartar cálculos se o *Sprite* ficar encoberto pelo Z-Buffer de uma parede sólida (`cub->zbuffer[col]`).

O nível de animação destes "modelos achatados" requer esforço algorítmico elevado: Uma arma (ex: Revólver) passa instantaneamente por `WEAPON_FRAMES` diferentes assim que um disparo acontece. Cada fotograma é substituído por ordem lógica ditada por temporizadores do sistema, resultando na ilusão de movimento orgânico, simulação de retrocesso mecânico ou inimigos a patrulhar os recintos.

### 6.2. Trabalhar com Câmaras Diferentes e Ângulos
*   **Visão Tridimensional Imersiva (FPS):** A câmara central utiliza uma matriz matemática cujo ângulo central é determinado com precisão por uma fórmula seno/cosseno face ao deslizar físico do Rato.
*   **Câmara Aérea Táctica (Minimapa):** Ao toque da tecla `U`, a renderização é subvertida. O jogo desenha graficamente um quadrante com perspectiva isométrica vertical "Top-Down" (`minimap.c`), projectando círculos relativos aos objectos inimigos, cor de obstáculo (parede), e simulando radiação eletromagnética visual (*Radar Rings*) com um feixe vectorial amarelo a denotar o ângulo cardinal de visão do herói.

### 6.3. Trabalhar com Diferentes Luzes e Estágios
No motor C que construímos, "luz" não advém de uma entidade lâmpada programada, mas sim da atenuação do *buffer* de cor. 
*   **Ray-Distance Shading (Z-Buffer Fading):** O algoritmo recolhe a cor de um *pixel* extraído de uma textura (ex: tijolo). Antes de "esculpir" essa cor na tela com a MiniLibX, a função divide o valor RGB (Red, Green, Blue) do *pixel* por uma escalar relacionada com a distância final que o raio DDA viajou (`ray->perp_wall_dist`). Paredes afastadas fundem-se num negrume opressivo simulando a perda de feixes fotónicos.
*   **Cromática Ambiente Baseado no Nível:** Cada um dos 10 níveis mapeados altera abruptamente o "Skybox" colorimétrico. Enquanto os estágios introdutórios apresentam um *floor* (`F`) e *ceiling* (`C`) configurados para azuis pálidos neutros no ficheiro `.cub`, a câmara de estágio avançado impõe parâmetros RGB intensos e opressivos (Tons densos escarlates e ocres) para induzir pânico fotográfico natural.

---

## 7. INTELIGÊNCIA ARTIFICIAL: A LÓGICA DO INIMIGO E COMBATE

Cumprindo o requisito de introduzir "Algo Novo (Critério 8)", dotámos o universo jogo de um cérebro táctico nos nossos adversários (`enemy_ai.c`), evitando manequins letárgicos vulgares de propostas antigas.

### 7.1. Line of Sight (A Visão da IA)
O inimigo sabe que existimos emitindo o seu próprio raio ("Line of Sight" / LOS). Ao longo dos *ticks* do motor, os oponentes castam um raio vector contra as coordenadas do utilizador. Se este raio matemático interceptar uma parede "1", o motor anula a premissa de ataque, e os inimigos percebem que o jogador usou manobras evasivas de cobertura, não revelando dano falso.

### 7.2. Pathfinding Automórfico através de Flow Fields
Em caso de quebra de contacto visual (LOS Falhou), a IA deve continuar implacávelmente atrás da nossa personagem no labirinto. Ao iniciar a ronda, o jogo resolve um algoritmo numérico na memória. As matrizes de passagens da grelha `0` sofrem uma operação matemática (Breadth-First Search) cujo número cresce quanto maior a distância aos nós críticos. O oponente meramente lê a coordenada do quadrado no solo e anda na direcção do dígito menor, encurtando incansavelmente a distância aos cantos contornando inteligentemente quinas em L, até vislumbrar o corpo do protagonista.

### 7.3. Combate e Sistemas Dinâmicos de Destruição
1.  **Raycast Híbrido Ofensivo (Hitscan):** As armas operam baseadas numa física pontual vectorizada do meio do ecrã para a frente da câmara. Verificamos a intersecção do feixe (bala) com a coordenada polar da IA deduzindo tolerâncias associadas a uma variável `CROSSHAIR_TOLERANCE`.
2.  **Combate Indirecto Espacial (O Barril):** O sistema introduz interações de ambiente, através do já listado elemento `B`. Quando o jogador dispara ao Barril (o "Hitscan" valida contacto com a *Hitbox* respectiva), activa-se uma rotina radial. Sem piedade, varremos na estrutura de todos os inimigos (`cub->enemies[i]`) e o nosso próprio jogador; quem estiver incluído no raio concêntrico euclidiano (`BARREL_ENEMY_RADIUS`) perde estaminé catastroficamente através de uma detonação em área, emulando autêntico "Friendly Fire" cinético.

---

## 8. CONCLUSÃO

O projecto "The Dump - O Pesadelo do Lixo" evidenciou de forma incontestável as potencialidades e o extremo nível de exigência algorítmica associada ao desenvolvimento computacional de baixo nível. As ferramentas leccionadas na disciplina de Computação Gráfica saíram do contexto estritamente teórico de PowerPoint, suportando e erguendo do zero cálculos densos de matrizes, vectores e trigonometria pura nas engrenagens e pistões do motor *Raycaster* C.

A Avaliação Prática requerida pelo Docente superou as marcas de água delineadas com aprovações claras e inegáveis: As modelagens figuram como simulações tridimensionais via *Sprite Casting*, a componente temporal impera magistralmente na cadência assíncrona do *Gold Buff God-Mode*, e todo o sistema é servido num pacote assombroso de texturas customizadas por "Câmara" flexível suportada pelo motor.

Ao suster todo este peso intelectual com gestões *Multithread* robustas sob uma capa lúgubre audiovisual da biblioteca BASS, garantimos que cada código iterado cumpriu e excedeu a finalidade pedagógica num produto comercialmente coeso da arte do código fechado.
