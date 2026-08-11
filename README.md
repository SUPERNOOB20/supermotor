# supermotor
My own C++ game engine <br>
<br>

<p align="center"> <img src = "https://files.catbox.moe/1xxcpu.png"></p>
<br>
<br>

## Requirements
* [SDL3](https://wiki.libsdl.org/SDL3/FrontPage)
* [SDL3_ttf](https://wiki.libsdl.org/SDL3_ttf/FrontPage) (just for the text features)
<br>

## Features
<br>
( ✅️ means already implemented )<br>
( 🔨 means work in progress (WIP) )<br>
( 🔜 means planned for the near future ) (planned for supermotor v1.1.0 for example) <br>
( 🔜🔜 means planned, but not for the near future (low priority in my to-do list) (it's even less priority than 🔜) (not planned for supermotor v1.1.0 or for any time soon... )<br>
( ❌️ is out of the scope for this project for now ) <br>
<br>
<br>
<br>
✅️   Batch rendering (loading data to the <ins>CPU / GPU</ins> in bulk, recursively from a directory, or from given filenames!)<br>
✅️   Galleries (grids, image galleries, etc. Anything that can be looped, basically)<br>
✅️   Collisions<br>
✅️   Batch text handling<br><br>
✅️   Screenshots<br>
✅️   Generalized math stuff (manhattan distance and euclidean distance) for N dimensions (1D, 2D, 3D, 4D, 5D, 6D, etc)<br>

🔜   Pausing<br>

🔜   Animations (atlas)<br>
🔜   Hurtboxes<br>
🔜   Transient objects (memory management, despawn)<br>

🔜🔜 Squishing and streching <br>
🔜🔜 Bezier trayectories and transitions <br>

❌️   Cameras (and corresponding transformations) <br>
❌️   Lerps (linear interpolations)<br>
❌️   Shaders, Graphics pipelines<br>
❌️   3D<br>


<br>

## Why you should use supermotor
<br>

* It's simple and easy to understand. <br>
* It's open source. <br>
* It's free. <br>
* It's powered by SDL3. <br>
* It's somewhat fast (Written in C++ and GPU accelerated). <br>
* Working with simple implementations for simple gamedev problems is a great hands-on learning experience that will strengthen your problem-solving skills <br>
* It's merely a collection of libraries, so it comes with all the advantages of a library:<br>
  * <ins>Customizable</ins> — add, remove, or refactor to your hearts content. You can even make your own game engine off of it :)<br>
  * <ins>Modular</ins> — Each feature is in a separate header file, so you can include only the features that you need - no bloat. <br>
  * <ins>Universal</ins> — no GUIs, no hidden dependencies, fully ISO compliant (adaptable to the compiler of your choice!). <br>
  * <ins>Multipurpose</ins> — Even if it's aimed at making videogames, it can also be used for graphics in general. Productivity software, text editors, drawing programs, animations, videos, movies... the limit is your imagination :3 <br>
* I'm always willing to explain how it works whenever you need it <br>
