# EscapeRoom
## Introduction
Small first person puzzle game made in UE4.
This game showcases several features common in First Person Adventure Games :
* Moving around in First Person view using mouse and keyboard
* Interacting with various items
* Picking up and dropping items
* Reading a text 

[Download the game on itch.io](https://jglgamedev.itch.io/escape-room)

## Description of the different classes
### PlayerCharacter
Main Player Character class. Can move and interact with objects
### EscapeRoomPlayerController
Main PlayerController for the game.
Handles HUD and ends the game.
### HUDWidget
Main HUD class.
Gets HUD information from PlayerCharacter.
### InteractInterface
Interface for actors that can be interacted with.
### GrabInterface
Interface for actor that can be grabbed.
### Artifact
Actor the player has to put on the correct Altar.
Changes color when interacted with.
Can be picked up.
### Altar
Actor where the player has to drop an Artifact into.
Correct Artifact Mesh and Material to be set in editor.
Can be called to check if the player guess if valid.
### InteractiveDoor
Actor representing a door that can be opened and closed.
Has a DoorFrame mesh and a Door mesh.
Door rotates relatives to the frame.
Uses a Timeline and a CurveFloat.
Implements InteractInterface.
### ReadableNote
Actor representing an object that the player can read.
Implements InteractInterface.
Display a widget to the screen when interacted with.
### Candle
Actor representing a light the player can turn on and off. 
### ValidationVolume
Actor representing a volume the Player has to step into to validate his guess.
