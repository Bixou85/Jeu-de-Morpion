# Tic Tac Toe Project

## Description

Ce projet implémente un jeu de Tic Tac Toe en utilisant SDL pour l'interface graphique. Le projet utilise CMake pour la gestion de la compilation.

## Prérequi

Avant de commencer, assurez-vous d'avoir installé l'éléments suivant sur votre machine :

- [CMake](https://cmake.org/)

## Installation de SDL2 et SDL2_image

Vous pouvez installer SDL2 et SDL2_image en utilisant votre gestionnaire de paquets préféré. Par exemple, sur une distribution basée sur Debian (comme Ubuntu), vous pouvez utiliser les commandes suivantes :

```sh
sudo apt-get update
sudo apt-get install libsdl2-dev libsdl2-image-dev
```

## Création du répertoire de build et environnement

```sh
sudo mkdir -p /usr/lib/x86_64-linux-gnu/cmake/sdl2_image/
```

Mettre ce code dans le fichier /usr/lib/x86_64-linux-gnu/cmake/sdl2_image/sdl2_image-config.cmake

```sh
set(prefix "/usr") 
set(exec_prefix "${prefix}")
set(libdir "${prefix}/lib/x86_64-linux-gnu")
set(SDL2_IMAGE_PREFIX "/usr")
set(SDL2_IMAGE_EXEC_PREFIX "/usr")
set(SDL2_IMAGE_INCLUDE_DIRS "${prefix}/include/SDL2_image")
set(SDL2_IMAGE_LIBRARIES "-lSDL2_image")
```

## Build

```sh
mkdir build
cd build
cmake ..
make
./Maxime
```

## Lancer les projets déjà build

Une version de toutes les étapes est déjà compiler dans le dossier build