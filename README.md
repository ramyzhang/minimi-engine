### Minimi Engine for Minimi the Game!

I am working on creating a simple 2D game engine, assisted by SDL2, for an arcade-style desktop game. Runs on Mac with XCode, though I intend to learn how to compile this cross-platform with CMake later down the line ^_^
All game assets were created by me!

![Screenshot 2024-10-10 at 3 48 11 PM](https://github.com/user-attachments/assets/501a0833-ce02-4d2f-802a-5b4e60575f39)

### Completed Systems

**Components:**
- CTransform
- CSprite
- CAnimator
- CBoxCollider

**Systems:**
- ECS architecture completed! Thank you to Dave Churchill for making his [COMP4300 course videos](https://www.youtube.com/watch?v=S7lXSihz0ac&list=PL_xRyXins848nDj2v-TJYahzvs-XW9sVV) publicly available, they were invaluable for this part!
- SMovement (basic player movement & follow-the-player enemy movement)
- SRenderer (wrapper for SDL_Renderer)
- SSpawner (spawns a player and enemies)
- SCollision (collision solver)
- SAudio (basic audio system)

### To Do

**Components:**
- CCircleCollider (maybe?)
- CAnimator state machine

**Systems:**
- Particles
- UI
- Camera
- Basic Scene Management (+ pausing)
- Game Logic (i.e. health, NPC states)
- Reading in game settings from a .txt file
- Better TileMap
