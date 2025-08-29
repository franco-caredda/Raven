# Raven

Raven is a souls-like single-player game demo made in Unreal Engine 5.  
The goal of this project is to learn how the essential gameplay mechanics that drive souls-like games work and how to implement them.  
The project levarages of the `Gameplay Ability System` provided by the engine and other systems, such as: `behaviour trees`, `EQS`, `UMG`.

## Assets

The project uses these assets:
1. Low Poly RPG Fantasy Weapons Lite by JustCreate.
2. Animations "Shield And Sword" from Mixamo.

## Implemented Features

- [X] Input handling for abilities.
- [X] Input buffering.
- [X] On-demand asset loading.
- [ ] Weapon system.
- [ ] Combat system using GAS.
- [ ] Inventory.
- [ ] UI.
- [ ] AI.
- [ ] Demo level.

## Download And Build

### Download

This repository doesn't contain any assets, so if you'd like to take a look at blueprints and animations or test the game, you can download either/both the build or/and source files.
This repository contains only the source code in C++.

1. Project files: [Google Drive](https://google.com).
2. Build: [Itch.io](https://itch.io).

### Build

|Tool|Version|
|--|--|
|Unreal Engine|5.6|
|Rider|2025.1.3|

Build process:
1. Download the project from Google Drive.
2. Dearchive the downloaded *.zip file.
3. Open Rider -> Press Open.
4. Find the *.uproject file and open it.
5. Wait until Rider has finished to build the project model.
6. Build the solution and launch the editor.

NOTE: if you use Visual Studio 2022 as the environment of choice, UE5 might ask you to compile the code manually, but Visual Studio doesn't open .uproject files like Rider does.  
To solve this problem, follow these steps:
1. In `<path to UE5.6>\Engine\Binaries\DotNET\UnrealBuildTool`, open the command line.
2. Run `dotnet "UnrealBuildTool.dll" -projectfiles -project="<path to the .uproject file>" -game -rocket -progress`.
3. After the generation of the Visual Studio solution, open it in the IDE.  
4. Build it.
5. Launch the editor from Visual Studio  

After doing these steps, the source should be built and you should be able to launch the editor and from there generate the solution for Visual Studio.