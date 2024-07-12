# SDLxQt
This demo app shows how to use both Qt6 and SDL3 in the same process. 
It creates two separate windows, one owned by SDL and one owned by Qt, and sets up event listening in each.

<img width="355" alt="image" src="https://github.com/user-attachments/assets/ac0fa987-d0db-4028-88c7-8b802207f8d4">

### Building
1. Install the Qt6 Widgets development libraries.
2. git clone with `--recurse-submodules` flag. This will ensure SDL3 is available.
3. `cmake -S . -B build`
4. `cmake --build build --target SDLxQt`

