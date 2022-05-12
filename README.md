# Sandbox: A Pseudo Physics Simulation
This engine uses a grid based approach to simulate a pseudo physics sandbox. The game state consists of a 2D grid spanning the entire game window 
and all entities that are currently within the window.

## Pseudo Physics Engine
The driving force of the simulation is the 2D grid. Each entity updates it's own state through the state of the grid, 
i.e., a falling block will check the immediate space below to determine it's next action. That is why I have opted to call this 'Pseudo physics' rather than
'Real physics'.

## Entities
There are three (3) different entities available in the simulation each with their own rules.
### Sand
Has gravity. Forms a pyramid shape with other sand entities. Sinks in water.
### Stone
Stationary.
### Water
Has gravity. Forms a pool shape with other water entities.
