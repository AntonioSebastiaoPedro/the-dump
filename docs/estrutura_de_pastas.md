cub3d/
│
├── main.c                 # Função principal
│
├── init_mlx/              # Inicialização do MLX e structs
│   ├── init.c
│   └── init_structs.c
│
├── render/                # Raycasting e renderização
│   ├── raycast.c
│   ├── draw.c
│   └── textures.c
│
├── player/                # Movimentos e rotação do jogador
│   ├── move.c
│   └── rotation.c
│
├── parser/                # Leitura e validação do mapa
│   ├── parse_map.c
│   └── validate_map.c
│
├── utils/                 # Funções auxiliares (string, erros, matemática)
│   ├── ft_split.c
│   ├── error.c
│   └── vector.c
│
├── includes/              # Headers
│   ├── cub3d.h
│   ├── structs.h
│   └── mlx.h
│
├── assets/                # Texturas e sprites
│   ├── textures/
│   │   ├── wall_north.xpm
│   │   └── wall_south.xpm
│   └── sprites/
│       └── enemy.xpm
│
├── libs/                  # Libs externas (como libft)
│   └── libft/
│
├── maps/                  # Mapas de teste
│   ├── map1.cub
│   └── map2.cub
│
├── Makefile
└── README.md
