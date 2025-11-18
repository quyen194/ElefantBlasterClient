BomberManClient
===============

BombermanGame/
│
├── assets/                 # Chứa tất cả tài nguyên của game
│   ├── audio/
│   │   ├── sfx/            # Sound effects (tiếng nổ, đặt bom, bước chân)
│   │   └── music/          # Nhạc nền
│   │
│   ├── fonts/              # Font chữ cho UI, điểm số
│   │
│   ├── graphics/           # Tất cả hình ảnh
│   │   ├── spritesheets/   # Các file ảnh lớn chứa nhiều frame animation
│   │   ├── tilesets/       # Các file ảnh cho map (tường, gạch, nền)
│   │   └── ui/             # Các icon, button, background cho giao diện
│   │
│   └── levels/             # Dữ liệu màn chơi (ví dụ: file .json, .xml, .tmx)
│
├── build/                  # Thư mục chứa kết quả build (sẽ được CMake tạo ra)
│
├── docs/                   # Tài liệu thiết kế, ghi chú
│
├── external/               # Các thư viện bên thứ ba (ví dụ: SFML, SDL2, glad)
│
├── src/                    # Toàn bộ mã nguồn của game
│   │
│   ├── Core/               # Các thành phần cốt lõi, có thể tái sử dụng
│   │   ├── Animation.h/.cpp
│   │   ├── AssetManager.h/.cpp
│   │   ├── GameState.h/.cpp
│   │   ├── InputHandler.h/.cpp
│   │   └── Window.h/.cpp
│   │
│   ├── Entities/           # Các đối tượng trong game
│   │   ├── Bomb.h/.cpp
│   │   ├── Enemy.h/.cpp
│   │   ├── Entity.h/.cpp   # Lớp cơ sở
│   │   ├── Explosion.h/.cpp
│   │   ├── Player.h/.cpp
│   │   └── PowerUp.h/.cpp
│   │
│   ├── Map/                # Mọi thứ liên quan đến bản đồ, màn chơi
│   │   ├── Level.h/.cpp
│   │   ├── Tile.h/.cpp
│   │   └── TileMap.h/.cpp
│   │
│   ├── States/             # Quản lý các trạng thái của game (State Machine)
│   │   ├── GameOverState.h/.cpp
│   │   ├── GamePlayState.h/.cpp
│   │   └── MainMenuState.h/.cpp
│   │
│   ├── main.cpp            # Điểm khởi đầu của chương trình
│   └── CMakeLists.txt      # File CMake cho thư mục src
│
├── .gitignore              # Chỉ định các file/thư mục mà Git sẽ bỏ qua (vd: build/)
├── CMakeLists.txt          # File CMake cấp cao nhất
└── README.md               # Mô tả dự án