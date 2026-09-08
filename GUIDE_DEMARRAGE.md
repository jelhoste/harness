# Guide de démarrage — mettre le projet sur GitHub et voir tes premiers builds

Ce guide part du principe que tu n'as **jamais** utilisé Git ni GitHub.
Suis les étapes dans l'ordre, une par une. Ne saute rien.

---

## Étape 0 — Comprendre les deux outils

- **Git** : un programme installé sur *ton ordinateur*, qui garde l'historique
  de tes fichiers (un peu comme un "undo" illimité et daté).
- **GitHub** : un site web qui héberge une copie de ce projet en ligne, et qui
  propose "GitHub Actions" — le service qui va compiler ton code automatiquement
  sur Windows/Linux/macOS à chaque fois que tu envoies une modification.

Le mot **"push"** = envoyer tes fichiers de ton ordinateur vers GitHub.

---

## Étape 1 — Créer un compte GitHub

Si tu n'en as pas déjà un :
1. Va sur https://github.com
2. Clique sur "Sign up", suis les instructions (email, mot de passe, nom
   d'utilisateur).

---

## Étape 2 — Installer Git sur ton ordinateur

Git n'est pas forcément déjà installé.

- **Windows** : télécharge et installe https://git-scm.com/download/win
  (laisse toutes les options par défaut pendant l'installation).
- **macOS** : ouvre le Terminal et tape `git --version`. Si Git n'est pas
  installé, macOS te proposera automatiquement de l'installer.
- **Linux** : ouvre un terminal et tape `sudo apt install git` (Ubuntu/Debian)
  ou l'équivalent de ta distribution.

Pour vérifier que ça a marché, ouvre un terminal (ou "Git Bash" sur Windows,
installé en même temps que Git) et tape :

```bash
git --version
```

Tu dois voir un numéro de version s'afficher (ex : `git version 2.44.0`).

---

## Étape 3 — Créer le repo (dépôt) vide sur GitHub

1. Sur github.com, en haut à droite, clique sur le **+**, puis
   **"New repository"**.
2. Donne-lui un nom, par exemple `nova`.
3. Laisse-le en **Public** ou passe-le en **Private**, comme tu préfères
   (ça ne change rien pour Actions).
4. **Important** : ne coche **aucune** case ("Add a README", ".gitignore",
   "license") — le repo doit être créé **vide**. On a déjà tout ce qu'il
   faut dans l'archive.
5. Clique sur **"Create repository"**.

Sur la page qui s'affiche ensuite, GitHub te montre une URL du type :
```
https://github.com/TON_NOM_UTILISATEUR/nova.git
```
Garde cette page ouverte, tu en as besoin juste après.

---

## Étape 4 — Préparer le dossier sur ton ordinateur

1. Dézippe l'archive `nova-harness.zip` quelque part sur ton disque
   (par exemple sur le Bureau).
2. Ouvre un terminal **dans ce dossier** :
   - **Windows** : ouvre le dossier dans l'Explorateur, puis dans la barre
     d'adresse en haut, tape `cmd` et appuie sur Entrée (ça ouvre un terminal
     déjà positionné dans le bon dossier). Ou fais un clic droit → "Git Bash
     Here" si l'option est proposée.
   - **macOS/Linux** : clic droit dans le dossier → "Ouvrir un terminal ici"
     (le libellé exact dépend de ton système), ou navigue avec `cd`.

Vérifie que tu es au bon endroit :
```bash
ls
```
Tu dois voir `CMakeLists.txt`, `README.md`, le dossier `src`, etc.

---

## Étape 5 — Envoyer le projet sur GitHub (une seule fois)

Dans le terminal, tape ces commandes **une par une**, en appuyant sur Entrée
après chacune. Remplace `TON_NOM_UTILISATEUR` par ton vrai nom d'utilisateur
GitHub (visible dans l'URL de l'étape 3).

```bash
git init
git add .
git commit -m "Premier commit : harnais de dev, étape 1"
git branch -M main
git remote add origin https://github.com/TON_NOM_UTILISATEUR/nova.git
git push -u origin main
```

Détail de ce que fait chaque ligne :
| Commande | Ce qu'elle fait |
|---|---|
| `git init` | Transforme ce dossier en dépôt Git (une fois pour toutes) |
| `git add .` | Sélectionne tous les fichiers du dossier pour le prochain "commit" |
| `git commit -m "..."` | Enregistre un instantané de ces fichiers, avec un message descriptif |
| `git branch -M main` | Nomme la branche principale `main` |
| `git remote add origin ...` | Indique à Git l'adresse de ton repo GitHub |
| `git push -u origin main` | Envoie réellement tes fichiers sur GitHub |

Il est possible qu'une fenêtre s'ouvre te demandant de te connecter à GitHub
(authentification via navigateur) — c'est normal la première fois, suis les
instructions à l'écran.

---

## Étape 6 — Regarder tourner les builds

1. Retourne sur la page de ton repo, sur github.com
   (`https://github.com/TON_NOM_UTILISATEUR/nova`).
2. Clique sur l'onglet **"Actions"** en haut de la page.
3. Tu dois voir une ligne "Premier commit : harnais de dev, étape 1" avec un
   petit rond jaune (⏳ en cours) qui devient vert ✅ (réussi) ou rouge ❌
   (échec) au bout de quelques minutes.
4. Clique sur cette ligne pour ouvrir le détail : tu verras 3 jobs,
   `windows-latest`, `ubuntu-latest`, `macos-latest`, un par plateforme.
5. Si un job est rouge, clique dessus pour dérouler les logs et voir à quelle
   étape ça a échoué (configuration CMake ou compilation). N'hésite pas à me
   coller ici le message d'erreur, on le regardera ensemble.

---

## Étape 7 — Envoyer une modification plus tard

Une fois cette première mise en ligne faite, à chaque fois que tu modifies le
code (par exemple quand on ajoutera NanoVG à l'étape 2), tu n'auras plus
besoin de refaire tout ça : seulement ces 3 commandes, depuis le même
dossier :

```bash
git add .
git commit -m "Décris brièvement ce que tu as changé"
git push
```

Chaque `push` relance automatiquement les 3 builds dans l'onglet Actions.

---

## En cas de blocage

Colle-moi le message d'erreur exact affiché dans le terminal (ou dans les
logs Actions), et on avance ensemble à partir de là.
