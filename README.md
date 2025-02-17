# Objective

1. make a simple multithreaded graphical application
2. replicate the architecture shown in both
  - [this video](https://youtu.be/1bAb1CfgZrs)
  - [this blogpost](http://croakingkero.com/tutorials/multi_threaded_framework/)
3. please @TheCherno

# Installation

```bash
git clone --branch=TODO --depth=1 https://github.com/RichardSartori/TODO
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j 8
```

# Options

-f / --fullscreen : start in fullscreen mode
-g / --gravity    : apply gravity to the entities
-h / --help       : print the help

# Controls

Q - quit
Y - confirm quitting
N - deny quitting
F - toggle fullscreen

# TODOs

- push to github
- add entities, physics and collisions
- make the entities bounce on the edge of the screen
- add audio thread, play sound when entities collide
- switch to double buffer technique (avoid mutexes)
- make the update thread use std::chrono for its delta_time
- see [this video](https://youtu.be/bBFWtnqQnQU?si=LwdXE1duTNB5k-Dk) and check
- check that there is no 100% CPU usage
- `grep TODO` and check
- add ability to drag and drop entities
- mail The Cherno

Sorry for bad writing, English is not my first language (baguette œuf fromage oui oui I'm French). I'm Richard Sartori, and I come from a very low level C background, but I really enjoy C++ and I've had a Rust formation, which is a language I really like as well. I'm a huge fan of your videos, I find them very educational and easy to understand. I started learning C++ watching your videos, as well as those of OneLoneCoder. Here is my first attempt at creating a multithreaded graphical application using raylib. There aren't many features, but I think its a good base. I won't brag about how perfect it is ;-), my opinion is highly subjective and not very much informed, that is why I would like to have yours. I watched "5 MOST COMMON MISTAKES in my Code Review series" and applied every recommandation as best as I could. I'm sure you'll still have a lot of useful advice, so please feel free to roast me, everyone watching you (including me) is here to learn and have some fun :-).

# Interrogations

- avoid rust `?` operator pattern?
- add `using namespace _`? (only in .cpp files)

# Acknowledgements

- [raylib](https://www.raylib.com/)
- [Croaking Kero](https://www.youtube.com/@UltimaN3rd)
- [Tsoding](https://www.youtube.com/tsoding)
- [The Cherno](https://www.youtube.com/@TheCherno)
- [OneLoneCoder](https://www.youtube.com/javidx9)