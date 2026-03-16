# 🎮 cub3D - Plano de Colaboração

**Developers:** Paulo & Amândio  
**Data:** 2026-03-02  
**Projeto:** cub3D (42 School)

---

## 📋 Divisão de Responsabilidades

### **Paulo - Parsing & MLX Setup**
- ✅ Etapa 1: Parsing e Validação do `.cub`
- ✅ Etapa 2: Inicialização MLX e DISPLAY
- ✅ Etapa 3: Função `put_pixel(x, y, color)`
- 🔄 Etapa 6: Texturas (com Amândio)
- 🔄 Etapa 7: Polimento (com Amândio)

### **Amândio - Player & Raycasting**
- ✅ Etapa 4: Jogador e Movimento 2D
- ✅ Etapa 5: Raycasting
- 🔄 Etapa 6: Texturas (com Amândio)
- 🔄 Etapa 7: Polimento (com Paulo)

---

## 🏗️ Estrutura Principal - `t_cub`

Struct principal que encapsula todo o estado do jogo. Facilita liberação de memória e passagem de dados:

```c
typedef struct s_cub
{
    // Parsing & Mapa
    t_map       *map;           // Mapa do jogo (grid, dimensões)
    t_config    *config;        // Configurações do .cub
    
    // Jogador & Movimento
    t_player    *player;        // Posição, direção, plano câmara
    
    // Gráficos & MLX
    t_mlx       *mlx;           // Contexto MLX (janela, buffer, imagem)
    
    // Texturas & Assets
    t_textures  *textures;      // XPM textures carregadas
    
    // Cores
    int         floor_color;    // Cor do chão (RGB)
    int         ceiling_color;  // Cor do teto (RGB)
}   t_cub;
```

**Vantagem:** Uma única struct para passar em funções, fácil cleanup com uma única função `free_cub()`.

---

## 📋 Fase 1: Estudo & Design

*Ambos trabalham juntos*

```
□ Desenhar arquitetura no whiteboard
□ Definir structs principais (usar t_cub como container)
□ Documentar fluxo completo
□ Decidir convenções de código
□ Definir nomes de ficheiros e funções
```

**Resultado esperado:** Ambos entendem o big picture e arquitetura.

---

## 📋 Fase 2: Implementação Paralela

### **Paulo implementa: Etapas 1, 2 e 3**

#### **Etapa 1: Parsing e Validação do `.cub`**

```
Subtarefas:
├── Leitura de ficheiro
│   ├── Verificar extensão .cub
│   ├── Confirmar permissões de leitura
│   ├── Tratar erro de ficheiro inexistente
│   └── Evitar diretórios no lugar de ficheiros
│
├── Parsing de configuração
│   ├── Ler texturas (NO, SO, EA, WE, F, C)
│   ├── Validar caminhos de texturas (acessíveis e .xpm)
│   ├── Detectar duplicações de parâmetros
│   ├── Validar cores RGB (0-255)
│   └── Ordem livre dos elementos
│
├── Parsing de mapa
│   ├── Ler grid do mapa
│   ├── Validar apenas caracteres permitidos (0,1,N,S,E,W, espaços)
│   ├── Detectar exatamente 1 jogador (N, S, E, W)
│   ├── Validar mapa fechado (sem fugas)
│   ├── Tratar espaços corretamente
│   └── Converter para matriz 2D (t_map)
│
└── Preenchimento de t_cub->config
    └── Armazenar todos os dados parseados
```

**Função principal:** `t_cub *parse_cub(char *filename)`

**Documentar:** Como cada struct é preenchida, validações realizadas.

---

#### **Etapa 2: Inicialização MLX e DISPLAY**

```
Subtarefas:
├── Verificação gráfica
│   ├── Testar conexão ao servidor gráfico (DISPLAY)
│   ├── Tratar mlx_init() retornando NULL
│   └── Mensagem clara se não houver ambiente gráfico
│
├── Inicialização MLX
│   ├── mlx_init()
│   ├── mlx_new_window()
│   ├── mlx_new_image()
│   └── Alocar buffer de imagem
│
├── Hooks básicos
│   ├── ESC fecha programa
│   ├── Botão X da janela encerra
│   └── Handlers de teclado/rato preparados (não implementados aqui)
│
└── Preenchimento de t_cub->mlx
    ├── mlx_ptr
    ├── win_ptr
    ├── img (imagem e buffer)
    └── Dimensões (width, height)
```

**Funções principais:**
- `t_mlx *init_mlx(void)`
- `void handle_close(t_cub *cub)`

**Documentar:** Inicialização order, tratamento de erros gráficos.

---

#### **Etapa 3: Função `put_pixel()`**

```
Subtarefas:
├── Implementar put_pixel(t_cub *cub, int x, int y, int color)
│   ├── Validar limites (0 <= x < width, 0 <= y < height)
│   ├── Calcular offset no buffer
│   ├── Escrever pixel na imagem
│   └── Tratar endianness corretamente
│
└── Testes básicos
    ├── Tela inteira cor sólida
    ├── Meia tela teto / meia chão
    └── Gradiente simples
```

**Função principal:** `void put_pixel(t_cub *cub, int x, int y, int color)`

**Documentar:** Cálculo de offset, endianness, limites.

---

### **Amândio implementa: Etapas 4 e 5**

#### **Etapa 4: Jogador e Movimento 2D**

```
Subtarefas:
├── Estrutura t_player
│   ├── float x, y (posição do jogador)
│   ├── float dirx, diry (vetor direção normalizado)
│   ├── float planex, planey (plano da câmara)
│   └── float move_speed, rotate_speed
│
├── Inicialização do jogador
│   ├── Posição inicial do parser (t_cub->map->player_x/y)
│   ├── Direção baseada em (N, S, E, W) do parser
│   ├── Plano câmara perpendicular à direção
│   └── Velocidades de movimento/rotação
│
├── Movimento (atualizar t_player)
│   ├── Frente (W) - mover na direção
│   ├── Trás (S) - mover inverso à direção
│   ├── Esquerda (A) - strafing esquerda
│   ├── Direita (D) - strafing direita
│   ├── Rotação esquerda (← ou Q)
│   └── Rotação direita (→ ou E)
│
├── Colisão com paredes
│   ├── Verificar próxima posição no mapa
│   ├── Impedir atravessar paredes (grid == 1)
│   ├── Evitar clipping em cantos (margem de segurança)
│   └── Permitir deslizamento nas paredes
│
└── Debug
    └── Minimapa temporário (opcional, para testar)
```

**Funções principais:**
- `t_player *init_player(t_cub *cub)`
- `void update_player(t_player *player, t_map *map, int key)`
- `int is_wall(t_map *map, float x, float y)`

**Documentar:** Cálculos de direção, colisão, movimento.

---

#### **Etapa 5: Raycasting**

```
Subtarefas:
├── Algoritmo DDA (grid traversal)
│   ├── Começar na posição do jogador
│   ├── Seguir raio até encontrar parede
│   ├── Otimizar com step sizes
│   └── Detectar lado da parede (N, S, E, W)
│
├── Para cada coluna do ecrã
│   ├── Calcular ângulo do raio
│   ├── Aplicar DDA
│   ├── Detectar parede atingida
│   ├── Calcular distância perpendicular (evitar fish-eye)
│   └── Armazenar para desenho
│
├── Renderização
│   ├── Desenhar coluna do teto (ceiling_color)
│   ├── Desenhar coluna da parede
│   ├── Desenhar coluna do chão (floor_color)
│   └── Cores sólidas (sem texturas por enquanto)
│
├── Otimizações
│   ├── Evitar fish-eye effect
│   ├── Calcular altura da parede corretamente
│   └── Limitar altura máxima/mínima
│
└── Teste visual
    └── Janela inteira renderizada com raycasting
```

**Funções principais:**
- `void cast_rays(t_cub *cub)`
- `int dda(t_player *player, float angle, t_map *map, float *distance)`
- `void draw_column(t_cub *cub, int col, int wall_height, int color)`

**Documentar:** Algoritmo DDA, cálculos de distância, altura de parede.

---

## 🧪 Teste de Integração

Ambos implementam este teste juntos no ficheiro `tests/test_integration.c`:

```c
#include <assert.h>
#include "cub3d.h"

/**
 * Test Integration: Valida que parsing, MLX e raycasting funcionam juntos
 * Desenvolvido por: Paulo & Amândio
 */

int main(void)
{
    // PASSO 1: Parsear um .cub válido (Paulo implementou)
    t_cub *cub = parse_cub("maps/test.cub");
    assert(cub != NULL);
    assert(cub->map != NULL);
    assert(cub->player != NULL);
    assert(cub->player->x > 0);
    assert(cub->player->y > 0);
    printf("✓ Parsing OK\n");

    // PASSO 2: Inicializar gráficos (Paulo implementou)
    if (init_mlx_graphics(cub) == 0)
    {
        assert(cub->mlx != NULL);
        assert(cub->mlx->mlx_ptr != NULL);
        assert(cub->mlx->win_ptr != NULL);
        assert(cub->mlx->img.buffer != NULL);
        printf("✓ MLX Init OK\n");
    }
    else
    {
        printf("✗ MLX não disponível (esperado em headless)\n");
    }

    // PASSO 3: Renderizar raycasting (Amândio implementou)
    cast_rays(cub);
    assert(cub->mlx->img.buffer != NULL);
    printf("✓ Raycasting OK\n");

    // PASSO 4: Verificar estruturas
    assert(cub->config != NULL);
    assert(cub->floor_color >= 0);
    assert(cub->ceiling_color >= 0);
    printf("✓ Estruturas OK\n");

    printf("\n✅ INTEGRAÇÃO COMPLETA - Pronto para Fase 3!\n");
    
    free_cub(cub);
    return (0);
}
```

---

## 📋 Fase 3: Code Review Cruzado

Ambos revisam o código um do outro para garantir qualidade e compreensão.

### **Paulo revê Raycasting de Amândio:**

```
Estrutura:
□ Funções bem separadas (DDA, draw_column, cast_rays)
□ Parâmetros corretos (recebem t_cub ou structs específicas)
□ Retorno correto de valores

Lógica:
□ DDA funciona sem loops infinitos
□ Raios são calculados para cada coluna
□ Distância perpendicular evita fish-eye
□ Altura da parede é calculada corretamente

Colisões & Limites:
□ Sem segfaults ao acessar t_cub->map->grid
□ Sem buffer overflows ao desenhar colunas
□ Limites de coluna respeitados (0 até width-1)

Documentação:
□ Funções têm comentários explicando lógica
□ Parâmetros estão documentados
□ Algoritmo DDA está explicado
```

### **Amândio revê Parsing de Paulo:**

```
Leitura de Ficheiro:
□ Extensão .cub validada
□ Permissões de leitura verificadas
□ Erros de ficheiro tratados corretamente
□ Diretórios rejeitados

Validação de Config:
□ Caminhos de texturas existem e são acessíveis
□ Duplicações de parâmetros detectadas
□ Cores RGB estão no intervalo 0-255
□ Ordem livre dos elementos funciona

Validação de Mapa:
□ Apenas caracteres permitidos no mapa
□ Exatamente 1 jogador detectado
□ Mapa é fechado (sem fugas)
□ Espaços tratados corretamente
□ Grid 2D tem dimensões consistentes

Estrutura:
□ t_cub->config está preenchida corretamente
□ t_cub->map está preenchida corretamente
□ t_cub->player está inicializada corretamente

Memory & Cleanup:
□ Allocação de memória correta
□ Sem memory leaks
□ Função free_config() e free_map() funcionam

Documentação:
□ Funções têm comentários explicando fluxo
□ Validações estão documentadas
□ Estruturas estão comentadas
```

---

## 📋 Fase 4: Integração & Polimento

### **Etapa 6: Texturas**

```
Subtarefas:
├── Carregamento de texturas (ambos)
│   ├── Ler ficheiros .xpm
│   ├── Carregar com mlx_xpm_file_to_image()
│   ├── Validar dimensões (deve ser 64x64)
│   ├── Tratar erros de ficheiro
│   └── Armazenar em t_cub->textures
│
├── Mapeamento de texturas no raycasting (ambos)
│   ├── Detectar lado da parede atingido (N, S, E, W)
│   ├── Calcular posição X na textura (baseado em ponto de colisão)
│   ├── Mapear cada linha da parede para textura
│   ├── Evitar segfaults ao ler pixels de textura
│   └── Aplicar texturas às colunas desenhadas
│
├── Liberação de texturas (ambos)
│   ├── mlx_destroy_image() para cada textura
│   ├── Função free_textures()
│   └── Integrar em free_cub()
│
└── Teste visual
    └── Paredes com texturas visíveis no render
```

**Funções principais:**
- `t_textures *load_textures(t_cub *cub)`
- `int get_texture_x(float collision_x, float collision_y, int side)`
- `int get_texture_pixel(t_textures *tex, int tex_id, int x, int y)`
- `void apply_texture(t_cub *cub, ...)`

---

### **Etapa 7: Polimento & Bonus**

```
Subtarefas Obrigatórias:
├── Memory Management (ambos)
│   ├── Verificar zero memory leaks
│   ├── Função free_cub() completa
│   ├── Destruir todas imagens MLX
│   ├── Fechar janela MLX
│   ├── Desalocar structs
│   └── Teste com valgrind
│
├── Tratamento de Erros (ambos)
│   ├── Mensagens de erro claras
│   ├── Validações robustas
│   └── Graceful shutdown em caso de erro
│
├── Norma & Código (ambos)
│   ├── Respeitar norma 42
│   ├── Nomes de funções consistentes
│   ├── Indentação correta
│   └── Comentários úteis (não triviais)
│
└── Makefile & Build (ambos)
    ├── Compilação sem erros
    ├── Sem warnings desnecessários
    ├── make clean, make fclean, make re
    └── Linking correto com MLX

Subtarefas Bonus (Opcional):
├── Minimapa
│   ├── Renderizar mapa 2D pequeno
│   ├── Mostrar posição do jogador
│   └── Mostrar direção
│
├── Controle com rato
│   ├── Rotação com movimento do rato
│   └── Sensibilidade ajustável
│
├── Portas
│   ├── Identificar portas no mapa
│   ├── Abrir/fechar com tecla
│   └── Renderizar estado de porta
│
├── Sprites (objetos)
│   ├── Renderizar sprites no mundo
│   ├── Mapeamento de distância e ângulo
│   └── Ordenação por profundidade
│
└── Animações
    ├── Armas animadas
    ├── Sprites animados
    └── Frames por segundo consistente
```

---

## 📊 Responsabilidades Finais (Ambos Sabem Tudo)

| Aspecto | Principal | Entende | Ambos Sabem |
|---------|-----------|---------|-----------|
| **Parsing .cub** | Paulo | Amândio | ✅ Sim |
| **MLX Setup** | Paulo | Amândio | ✅ Sim |
| **put_pixel()** | Paulo | Amândio | ✅ Sim |
| **Player 2D** | Amândio | Paulo | ✅ Sim |
| **Raycasting** | Amândio | Paulo | ✅ Sim |
| **Carregamento Texturas** | Ambos | Ambos | ✅ Sim |
| **Mapeamento Texturas** | Ambos | Ambos | ✅ Sim |
| **Memory Management** | Ambos | Ambos | ✅ Sim |
| **Polimento & Bonus** | Ambos | Ambos | ✅ Sim |

---

## 💡 Dicas Importantes

✅ **Git desde o início** - branches separadas, merges coordenadas  
✅ **Documentação inline** - expliquem o código um para o outro  
✅ **Testes unitários** - testam suas partes antes de integrar  
✅ **Reuniões regulares** - sincronizem sobre progresso e blockers  
✅ **Pair programming em blockers** - quando alguém fica preso  
✅ **t_cub como container** - simplifica passagem de dados e cleanup  

---

## 🎯 Fluxo Geral de Desenvolvimento

1. **Fase 1** → Estudo & Design (Ambos)
2. **Fase 2** → Implementação Paralela (Paulo: Etapas 1-3, Amândio: Etapas 4-5)
3. **Fase 3** → Code Review Cruzado (Ambos revisam)
4. **Fase 4** → Integração (Ambos, Etapas 6-7)

