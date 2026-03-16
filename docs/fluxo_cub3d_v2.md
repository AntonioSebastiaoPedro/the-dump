# Fluxo Ideal do Projeto cub3D (42) --- Versão Completa

Este documento apresenta as **7 etapas ideais** para desenvolver o
projeto cub3D de forma organizada, segura e próxima do que avaliadores
esperam.

------------------------------------------------------------------------

## 🥇 Etapa 1 --- Parsing e Validação do `.cub`

Antes de qualquer parte gráfica.

### Leitura e permissões

-   Verificar extensão `.cub`
-   Confirmar permissões de leitura (`access`, `open`)
-   Tratar erros de ficheiro inexistente
-   Evitar diretórios no lugar de ficheiros

### Configuração

Validar:

-   Caminhos das texturas (existem e são acessíveis)
-   Duplicações de parâmetros
-   Cores RGB (0--255)
-   Ordem livre dos elementos

### Mapa

Validar:

-   Apenas caracteres permitidos
-   Apenas 1 jogador (N S E W)
-   Mapa fechado (sem fugas para o exterior)
-   Espaços tratados corretamente
-   Conversão para matrix consistente

Objetivo:

👉 Ter dados 100% seguros antes de qualquer janela abrir.

------------------------------------------------------------------------

## 🥈 Etapa 2 --- Inicialização MLX e DISPLAY

Antes de qualquer render.

### Conexão gráfica

-   Testar ligação ao servidor gráfico (`DISPLAY` no Linux)
-   Tratar `mlx_init()` a retornar NULL
-   Mensagem clara caso não exista ambiente gráfico

Exemplo comum:

-   executar via SSH sem X11 forwarding.

### Base MLX

Criar:

-   janela
-   image buffer
-   hooks básicos

Eventos mínimos:

-   ESC fecha corretamente
-   Botão X da janela termina programa

Leaks aqui são críticos.

------------------------------------------------------------------------

## 🥉 Etapa 3 --- Desenhar Pixels

Criar função:

`put_pixel(x, y, color)`

Testar:

-   tela inteira cor sólida
-   metade teto / metade chão
-   gradientes

Objetivo:

👉 dominar acesso direto ao buffer da imagem.

------------------------------------------------------------------------

## 🏅 Etapa 4 --- Jogador e Movimento 2D

Implementar:

-   posição float do jogador
-   vetor direção
-   plano de câmara

Movimentos:

-   frente / trás
-   strafing
-   rotação

Colisão:

-   impedir atravessar paredes
-   evitar clipping em cantos

Debug ideal:

👉 minimapa temporário.

------------------------------------------------------------------------

## 🏆 Etapa 5 --- Raycasting

O coração do projeto.

Para cada coluna do ecrã:

1.  Calcular direção do raio.
2.  DDA (grid traversal).
3.  Detectar parede.
4.  Calcular distância perpendicular.
5.  Evitar fish-eye effect.

Desenhar:

-   teto
-   parede
-   chão

Primeira versão:

👉 cores sólidas.

------------------------------------------------------------------------

## 🏆 Etapa 6 --- Texturas

Substituir cores por texturas XPM.

Validar:

-   ficheiro acessível
-   carregamento correto via MLX

Calcular:

-   lado da parede atingido
-   posição X da textura
-   passo vertical

Cuidados:

-   evitar segfaults ao ler pixels.
-   libertar imagens corretamente.

------------------------------------------------------------------------

## 👑 Etapa 7 --- Polimento e Bonus

Adicionar:

-   minimapa
-   rato
-   portas
-   sprites
-   animações

Garantir:

-   zero leaks
-   fechar MLX corretamente
-   destruir imagens e janela.

------------------------------------------------------------------------

## ⭐ Checklist Final

1.  Parsing robusto.
2.  Extensão `.cub` validada.
3.  Permissões de acesso verificadas.
4.  DISPLAY disponível.
5.  MLX inicializada corretamente.
6.  Movimento sólido.
7.  Raycasting estável.
8.  Texturas seguras.

Seguir esta ordem reduz drasticamente bugs e retrabalho.
