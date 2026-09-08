# Nova — harnais de développement

Étape 1/4 : fenêtre GLFW vide, pour valider la chaîne de build cross-platform
avant d'ajouter NanoVG (rendu) puis Clay (layout).

## Build

Nécessite : CMake ≥ 3.16, un compilateur C++17, et une connexion réseau la
première fois (GLFW est téléchargé via `FetchContent`).

```bash
cmake -B build -S .
cmake --build build --config Release
```

L'exécutable `nova_harness` s'ouvre dans `build/` (ou `build/Release/` sous
Windows avec Visual Studio). Une fenêtre grise doit s'ouvrir et rester stable
jusqu'à fermeture manuelle.

## Prochaines étapes

- Étape 2 : intégration de NanoVG + loader OpenGL (glad), rendu d'une forme
  de test.
- Étape 3 : intégration de Clay pour le layout.
- Étape 4 : unification souris/tactile (états Normal / Pressed / Disabled
  uniquement, pas de hover).
