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
- Basic ECS architecture completed!
- SMovement (basic player movement & follow-the-player enemy movement)
- SRenderer (wrapper for SDL_Renderer)
- SSpawner (spawns a player and enemies)
- SCollision (collision solver)
- SAudio (basic audio system)
- SObserver and SSubject for the observer/subject notifier system pattern

### To Do

**Systems:**
- Particles
- Animation state machine
- UI
- Scripts
- Camera
- Basic Scene Management (+ pausing)
- Game Logic (i.e. health, NPC states)
- Reading in game settings from a .txt file
- Better TileMap

### Resources
- Dave Churchill's [COMP4300 course videos](https://www.youtube.com/watch?v=S7lXSihz0ac&list=PL_xRyXins848nDj2v-TJYahzvs-XW9sVV) for literally all the core concepts I used
- [Game Programming Patterns](https://gameprogrammingpatterns.com/) for crucial design patterns so my code isn't trash
- Lazy Foo's [SDL2 Tutorials](https://lazyfoo.net/tutorials/SDL/index.php) for super helpful SDL2 tips
- Let's Make Games [Tutorials](https://www.youtube.com/watch?v=QQzAHcojEKg&list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx) were invaluable in getting me started
- SDL2 Official [Documentation](https://wiki.libsdl.org/) for when I wanted to explore more features
