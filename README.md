### Minimi Engine for Minimi the Game!

I am working on creating a very simple 2D game engine, heavily assisted by SDL2, for an arcade-style desktop game. Runs on Mac with XCode, though I intend to compile cross-platform with CMake later down the line.

![Screenshot 2024-10-10 at 3 48 11 PM](https://github.com/user-attachments/assets/501a0833-ce02-4d2f-802a-5b4e60575f39)

### Completed Systems

**Components:**
- CTransform
- CSprite
- CAnimator

**Systems:**
- SMovement (basic player movement & follow-the-player enemy movement)
- SRenderer (wrapper for SDL_Renderer)
- SSpawner (spawns a player and enemies)

### To Do

**Components:**
- CBoxCollider
- CCircleCollider (maybe?)

**Systems:**
- Audio
- Collision Physics
- Particles
- UI
- Camera
- Basic Scene Management
- Better TileMap
