
# philosophers

## Table des Matières

- [Introduction](#introduction)
- [Fonctionnalités](#fonctionnalités)
- [Utilisation](#utilisation)
- [Concepts Importants](#concepts-importants)
- [Fonctions Standards](#fonctions-standards)

---

## Introduction

**philosophe** est un projet de l'École 42 qui explore la concurrence, le multithreading et la synchronisation à travers le célèbre problème des "Philosophes Dîneurs". Le projet simule des philosophes autour d’une table, alternant entre manger, penser et dormir, tout en gérant les ressources partagées (fourchettes) avec des exclusions mutuelles pour éviter les blocages et les conditions de course.

---

## Fonctionnalités

- Simule le problème des Philosophes Dîneurs en utilisant des threads et des mutex.
- Démontre l’utilisation du contrôle de concurrence pour gérer l’accès aux ressources partagées.
- Assure que chaque philosophe peut manger uniquement lorsque les fourchettes adjacentes sont disponibles.
- Gère les erreurs liées à la création et à la synchronisation des threads.

---

## Utilisation

### Utilisation de base

```bash
./philosophe nombre_de_philosophes temps_avant_mort temps_pour_manger temps_pour_dormir [nombre_de_repas_par_philosophe]
```

- `nombre_de_philosophes` : Nombre de philosophes et de fourchettes.
- `temps_avant_mort` : Temps (en millisecondes) pendant lequel un philosophe peut survivre sans manger.
- `temps_pour_manger` : Temps (en millisecondes) qu’un philosophe passe à manger.
- `temps_pour_dormir` : Temps (en millisecondes) qu’un philosophe passe à dormir.
- `nombre_de_repas_par_philosophe` (optionnel) : Nombre de fois qu’un philosophe doit manger avant la fin de la simulation.

Exemple :

```bash
./philosophe 5 800 200 200
```

Cette commande simule cinq philosophes, chacun ayant un délai de 800 ms avant la mort, un temps de 200 ms pour manger et un temps de 200 ms pour dormir.

---

## Concepts Importants

### Threads

Les threads permettent l'exécution concurrente de plusieurs séquences d'instructions dans un programme. Dans le projet **philosophe**, chaque philosophe est représenté par un thread distinct, permettant à chaque philosophe de penser, manger ou dormir indépendamment des autres.

- **pthread_create** : Cette fonction crée un nouveau thread, permettant à une fonction de s'exécuter en parallèle.
- **pthread_join** : Cette fonction attend qu'un thread spécifique termine son exécution, empêchant le programme principal de se terminer avant que tous les threads soient finis.

### Mutex

Un mutex (exclusion mutuelle) est utilisé pour empêcher plusieurs threads d'accéder simultanément à une ressource partagée, ce qui pourrait provoquer des conditions de course. Dans ce projet, les mutex contrôlent l’accès aux fourchettes pour s'assurer qu’un seul philosophe à la fois peut utiliser chaque fourchette.

- **pthread_mutex_init** : Initialise un mutex.
- **pthread_mutex_lock** : Verrouille un mutex, empêchant les autres threads d’accéder à la ressource partagée tant qu'il n'est pas déverrouillé.
- **pthread_mutex_unlock** : Déverrouille un mutex, permettant à d'autres threads d'accéder à la ressource.
- **pthread_mutex_destroy** : Détruit un mutex, libérant ses ressources.

---

## Fonctions Standards

### `usleep`

- **Utilisation** : `usleep(microsecondes);`
- Met en pause l’exécution d’un thread pour un nombre de microsecondes spécifié. Cette fonction est utilisée pour simuler le temps que chaque philosophe passe à manger, dormir ou penser.

### `gettimeofday`

- **Utilisation** : `gettimeofday(&tv, NULL);`
- Obtient l’heure actuelle, ce qui est utile pour suivre combien de temps chaque philosophe a passé dans un état spécifique (par exemple, manger ou dormir) et vérifier s’il risque de mourir de faim.

### `pthread_create`

- **Utilisation** : `pthread_create(&thread, NULL, fonction, argument);`
- Crée un nouveau thread qui commence à exécuter la fonction spécifiée. Chaque philosophe est représenté par un thread créé avec cette fonction.

### `pthread_join`

- **Utilisation** : `pthread_join(thread, NULL);`
- Attend qu’un thread spécifique se termine, assurant que les ressources sont correctement libérées avant que le programme ne se termine.

### `pthread_mutex_init`

- **Utilisation** : `pthread_mutex_init(&mutex, NULL);`
- Initialise un mutex qui peut être utilisé pour verrouiller les ressources partagées (fourchettes) et éviter les accès simultanés.

### `pthread_mutex_lock`

- **Utilisation** : `pthread_mutex_lock(&mutex);`
- Verrouille un mutex, bloquant les autres threads d’accéder à la ressource tant qu’il n’est pas déverrouillé.

### `pthread_mutex_unlock`

- **Utilisation** : `pthread_mutex_unlock(&mutex);`
- Déverrouille un mutex, permettant aux autres threads d'accéder à la ressource partagée.

### `pthread_mutex_destroy`

- **Utilisation** : `pthread_mutex_destroy(&mutex);`
- Détruit un mutex, libérant ses ressources.

---
