# Needed
- Refraction materials
- Cast rays to light emitters more frequently
  use normalization by solid angle? computed by emitters

# Features
+ Multithreading
- OpenMP
- Distributed computing (TCP)

# Refactoring
+ Use lines instead of tiles
- Replace vec4 using as a color with special Light class
- Start beam from lens for depth effect

# Ideas for rendering
- Menger sponge
- Room with lighter above
- Refraction (and caustics (maybe wine in glass?))
- Projecting through the lens
? Difraction on the slot
- Liquid modelling
- Fire modelling
