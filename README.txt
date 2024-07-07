Given that this assignment had no specific requests except for a few ones, I thought about making a list of all the features so here it is.
First of all I'm not a level designer and the map is pretty bad and small, but at least it showcases the features.
There shouldn't be any blueprint code, the only blueprint nodes that I placed are the ones in the animation blueprint to adapt it to my pawn
instead of the character class.
• Mandatory Features:
	- Movement: at first I wanted to make a very movement based project, but after some weeks trying to make it all work I just left it 
		    with the following features: movement is possible in any direction and it can go up slopes. The movement direction is 
		    related to the orientation of the camera (I'll talk about it later). There is acceleration, so you start slow and gain
		    speed with time. You can jump multiple times (the possible jumps number is editable).	  
		    Flaws: - if you land on the ground and the rotation of the pawn is not finished yet the pawn will keep hovering until
			     the rotation ends.
			   - when landing on "non-ground" objects the pawn will get stuck
			   - hitting a wall will block you. Just move away from the wall to unstuck.	
	- Input Binding: I used the new input system. I created the assets in editor and then binded actions in c++. To separate the pawn 
			 from the input, the input is handled in the player controller that calls the player functions using the an instance
			 of the "PlayerInputActions" interface. This way the player pawn should be able to receive input from other sources.
	- Save Game: It happens via checkpoints (saving) and resetvolumes (loading) -> resetvolumes are a way to avoid getting stuck in holes
		     or falling in the void. The three main parts are: "PlatformerSaveGame" (save game class) "Savable" (interface that has
		     to be implemented by actors or objects that want to be saved) and "SaveGameInterface" (interface implemented by the game
		     instance that has "Save()", "Load()" and "Add()" functions so it's callable anywhere).
		     Another important part are the structs that hold the data. All of the structs inherit from a base struct that only has the
	             name of the object.
		     The game instance holds the objects that want to enter the save system in separate arrays of "TScriptInterface<ISavable>"
		     so that when saving or loading it calls the specific "ISavable" interfaces functions for each type of object, because 
		     the data stored in the structs is different for each object and since structs polymorphism is very limited I had to create
		     different functions (I also tried to use objects instead of structs to hold the data to use polimorphysm effectively
		     but of course it would give null data because between sessions and after garbage collection the pointers would get lost.)
		     Every "Savable" has to add itself to the arrays and has to implement the correct "GetData()" and "RestoreData()" functions.
		     I added save functionality for the other features like: player, buttons, platforms, powerups and the puzzle (I'll talk 
		     about these later adding save information for each feature). I know that these are not things that usually get saved in
		     videogames but I had to improvise to actually use the save system in this "prototype" of a project.
		     Flaws: - I think it's only suitable for small project since the save and load functions get bigger for each new type of item
			      you want to save. To avoid this I should have used serialization I think, but since we did not cover the topic
			      I preferred to do it this way.
			    - Did not cover multiple save slots (I'm at my limit, sorry)

• Other features:
	- Orbital Camera: The player pawn is built like a third person character (a very sloppy version to be honest, I tried my best), so 
		          I implemented an orbital camera that actually influences the direction of the movement.
			  Flaws: - upper and lower limits don't work properly. The camera can get stuck when reaching the limits and if you 
			           move it too fast you can make it go upside down. 
				 - it clips through walls, didn't implement the logic at all.
	- Platforms: Simple platforms and moving platforms. Moving platforms can be active from the start, one shot (don't go back when reaching
		     end point), have an initial delay or be activated by a button. 
		     SaveGame: The save system stores the "bActive" property. If a platform is moving or has moved and you save the game, 
			       after loading it will be found moving in case it is not bOneShot or it is active from the start, otherwise if 
			       it is bOneShot it will be found still in the end point (you can actually skip the creation of the platforms 
		               bridge by activating it, passing the checkpoint before it and and falling through a reset volume, not a bad 
                               feature I think). If you activate a platform and don't save it will be resetted (only if it's not active from 	
		               start).
		     Flaws: - I don't know why but on different computers when loading a moving platform that is not one shot it sometimes telep
			      orts to the starting position but after that it works normally. (Might be related to execution order on different
			      framerates or something like that)
			    - The player doesn't move with a moving platform when standing on it. I know it's something related to the physics
			      simulation and I don't really like physics nor I am good at it so I didn't fix this.
	- PowerUp: there is a base power up class and a jump power up. The jump power up gives you an additional jump when taken. 
		   SaveGame: If a power up is taken and you save the game, the player will keep its effect and it will no longer be available 
                             to get. If you take a power up and reset without saving the power up will be reactivated and you will lose its
			     effect, you have to recollect it.
	- Interaction System: it's a macro feature like the save game. The main classes are: "Interactable" interface and "InteractionArgsBase"
			      (the base args for any interaction). There is also an enum with the interaction types. There are also the 
			      specific args classes that inherit from "InteractionArgsBase" that add the data specific to that kind of 
			      interaction. When the player interacts with an "IInteractable" it will ask it what kind of interaction is it and
			      will call the Interact function passing the correct args. To create a new kind of interaction you just have to 
			      add it to the enum, create the specific args class inheriting from the "InteractionArgsBase", add the logic in 
			      the player function and of course create the new actor that inherits from "IInteractable" and implement the logic.
			      For now I only implemented 3 types of interaction: Button, Push and Inspect. (push and inspectable actors were 
			      created only to show the versatility of the interaction system, they are nothing special). Player-wise it is a 
			      simple line trace activated by the "E" key, not optimal but it does the job for showcasing the mechanic.
			      Flaws: - Happens via line trace as already stated. Would be cool to make it better (again, I'm at my limit)
	- Button: It's part of the interaction system. It can be one shot or pressed multiple times. If it is one shot it will turn red. It
		  has a delegate that fires when it is pressed (Platforms subscribe to it to be activated).
		  SaveGame: buttons that are not one shot are always active. If u press a one shot button and you save before resetting, it will 
			    remain pressed and can no longer be pressed. If you don't save before resetting it will return to its "unpressed"
			    state and it can be pressed again.
	- Push Actor: simple pushable actor, you apply a force to it when interacting with it.
	- Inspectable actor: actor that you can inspect by interacting with it. (push and inspectable actors were created only to show the 
			     versatility of the interaction system, they are nothing special), by pressing "E" again on the actor or getting
			     far from it the inspection ends.
	- Button Puzzle: classic puzzle where you have to push the buttons in the correct order to succeed. You put as many buttons as you want
			 and give it the order that you want. Wrong indexing of the buttons will result in malfunctioning. Hitting a wrong 
		         button will of course reset the puzzle, but if you succeed all the buttons will turn green and a door will be opened.
			 (didn't have the will to actually make a door so I just put a one shot platform and referenced it to the puzzle).
			 SaveGame: you can save in every point during the puzzle and the state of the puzzle will be saved. If you load without
				   saving the puzzle will go back to the state it was in when you last saved the game. (I also put a small reset
				   volume to the left of the "door" to test this).
	
			      
	
	
			  
