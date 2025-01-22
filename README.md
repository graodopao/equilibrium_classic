# Equilibrium | Balance City
Equilibrium, aka Balance City, is a game about balancing a city on top of a platform by controlling its weight, avoiding that the constructions slide off of the platform and break.

# Dependencies
SDL2, SDL2_image, SDL2_mixer, and SDL2_ttf were used for the creation of the engine behind the game (internally called Nashira). The game and the engine were built using C++.

# To-Do:
So far, I've refactored many aspects that were very unsatisfactory to me, as the code was written 4 years earlier. I wasn't able to address all the issues so far, which include:

- Assets in the game are very outdated, and I'd like to redraw a lot of things.
- Game managers are singletons, instead I'd like to entirely remove their objects and replace with static functions and properties.
- Most if not all the objects in the game and the engine are unnecessarily created in the heap. Future iterations will prioritize list initialization and the stack.
- Game object management is extremely rudimentary, and most instances are freed by hand, and game objects aren't have their own classes/structs.
- This is still under consideration, but I'd like to implement component driven systems in the engine. This is more an addition to Nashira than Balance City itself, but as this is the only project this engine is implemented in, I figured it was appropriate to include it here.
- In addition to the  components system, I'd like to implement unit testing in the future.

# Contact
My email: `tiago170304@gmail.com`

My discord: `graodopao`