%Projet 3a - Rapport intermédiaire
%Guillaume Hétier
%02/12/15

Énoncé du projet
=================

L'objectif de ce projet, que nous avons construit avec M. Jean-Christophe Filliatre, repose sur le "projet Euler". Il s'agit d'un site proposant de nombreux problèmes de mathématiques et d'algorithmique de difficultés variables.

Or, on peut remarquer que certains algorithmes reviennent très fréquemment dans ces problèmes, en plus d'être utilisé dans un cadre plus général. C'est en particulier le cas des algorithmes de crible ou de la mémoïsation.

C'est sur ce dernier point que nous avons choisi de nous pencher. La mémoïsation est en effet une technique puissante permettant d'améliorer la complexité de fonctions récursives, mais elle présente quelques inconvénients :

- Elle rend la création de la fonction récursive plus complexe, car elle requiert une table de hachage qui doit contenir les résultats intermédiaires ;
- Elle demande un espace mémoire proportionnel au nombre de valeurs intermédiaires à calculer, qui peut donc devenir trop important.

Nous avons donc fixé comme objectif pour ce projet 3a de, dans un premier temps, développer une bibliothèque automatisant la mémoïsation d'une fonction récursive. Dans un second temps, je me suis penché sur la mise en place d'une politique de cache dans les algorithmes de mémoïsation afin de limiter leur utilisation de la mémoire sans perdre à nouveau un classe de complexité.
La bibliothèque obtenue a été testée tout du long sur différents exercices issus du projet Euler, afin de vérifier son efficacité et améliorer son usage par l'utilisateur.

Rappel sur la mémoïsation
=========================

Certains problèmes définis récursivement, comme le calcul d'un élément de la suite de Fibonacci ou du triangle de Pascal, conduisent à une complexité exponentielle lors de leur calcul à partir d'une fonction récursive naïve. Ils exigent en effet des appels récursifs multiples.
Pourtant, le nombre de valeurs différentes à calculer reste polynomial. La complexité n'explose que parce que ces résultats sont calculés de nombreuses fois lors de l'exécution de l'algorithme.

La mémoïsation est l'une des techniques (avec la programmation dynamique) permettant d'effectuer ces calculs en temps polynomial.
L'idée est de, lors de appels récursifs, stocker dans une table de hachage les résultats intermédiaires. Lors de l'exécution d'un appel récursif, il suffira alors de vérifier si le résultat n'est pas déjà présent dans la table afin de ne pas exécuter le calcul une nouvelle fois.
Ce gain en temps est donc obtenu au prix d'une utilisation plus importante de mémoire.

Par exemple, la mémoïsation ramène le calcul d'un élément de la suite de Fibonacci à une complexité linéaire au prix de l'utilisation d'une quantité linéaire de mémoire ; et le calcul de l'élément $(n,k)$ du triangle de Pascal à un temps $O(nk)$ au prix d'un espace $O(nk)$ en mémoire.

Bibliothèque de mémoïsation
===========================

Le projet a donc commencé par la mise en place d'une bibliothèque permettant d'automatiser la mémoïsation d'une fonction : l'objectif était de, à partir du code d'une fonction récursive, obtenir sa version mémoïsée.

Choix du langage
----------------

J'ai choisi de réaliser cette bibliothèque en C++. Pourquoi ce langage ? Les raisons sont les suivantes :

- Produire une bibliothèque est difficile en C++, qui n'est pas un langage orienté fonctionnel et propose peut de structures standard. Mon travail pourrait donc avoir une utilité potentielle et être réutilisé ensuite, car il propose des fonctionnalités n'existant pas encore dans une bibliothèque C++.
- Les normes C++11 et C++14 ont introduit les clôtures en C++, permettant de réaliser ces tâches relativement simplement. C'était pour moi l'occasion de me familiariser avec ces normes.

Mise en place d'un point fixe
------------------------------

La mémoïsation d'une fonction récursive va passer par la création d'un point fixe.
Un point fixe d'une fonction $f$ prenant en argument une fonction est une fonction $g$ telle que : $f(g) = g$.

Dans notre cas, l'utilisateur va fournir la fonction $f$, qui va correspondre à la fonction récursive, au détail près que l'appel récursif ne se fera pas sur la fonction $f$ elle même, mais sur la fonction $g$ passée en paramètre. La construction du point fixe va alors permettre la récursion.

Si l'on désirait seulement une fonction récursive, le point fixe suivant serait suffisant (c'est ce qui est implicitement construit par le système en OCaml par exemple) :

\newpage{}

```cpp
Rec(std::function<U(std::function<U(K)>, K)> frec)
{
    // Création d'une cloture
    pfixe = [this, &frec](K n){
            return frec(pfixe, n);
        }
    };
}
```

La fonction $pfixe$ est ici un point fixe de la fonction $frec$. Dans notre cas, on va en plus vouloir que le pont fixe vérifie si le résultat n'est pas déjà présent dans une table afin d'éviter un calcul inutile, et qu'il l'y stocke en cas de calcul. On réalise alors le point fixe suivant :

```cpp
Memo(std::function<U(std::function<U(K)>, K)> frec)
{
    // Création d'une cloture
    fmemo = [this, &frec](K n){
        try{
            // Si le résultat est déjà calculé, on le récupère dans la table
            return table.at(n);
        }
        catch(std::out_of_range e){
            // Sinon, on le calcule récursivement
            U r = frec(fmemo, n);
            // Et on le stocke dans la table pour une utilisation future
            table.insert(std::make_pair(n, r));
            return r;
        }
    };
}
```

La fonction $Memo$ est ici un constructeur d'un objet contenant entre autre la table de hachage $table$, la fonction $fmemo$ et une fonction permettant d'appliquer $fmemo$ à un argument. Les initialisations ont été retirées ici par soucis de clarté.

Du point de vue de l'utilisateur, l'utilisation est alors particulièrement simple. Voici un exemple de la mémoïsation de la fonction de Fibonacci :

```Cpp
// Construction de la fonction récursive
// La seule différence avec une fonction récursive naïve est que on fera
// l'appel récursif sur une fonction passée en premier paramètre.
auto fib = [](function<int(int)> f, int n){
        if (n<2)
            return 1;

        return f(n-1) + f(n-2);
    };

// Construction du point fixe
Memo<int, int> fibo(fib);

std::cout << fibo(42) << std::endl;
```

Extension des fonctions de hachage standard
--------------------------------------------

Essayons maintenant de mémoïser le calcul d'un coefficient du triangle de Pascal. Afin de passer les deux paramètres lignes et colonne, on va utiliser une paire. On aurait donc le code suivant :

```Cpp
auto pascal = [](function<long(pair<int, int>)> f, pair<long, long> p){
        int n = get<0>(p);
        int k = get<1>(p);

        if(n<k)
            return (long)0;
        if(k == 0)
            return (long)1;

        return f(make_pair(n-1,k)) + f(make_pair(n-1, k-1));
    };

Memo<pair<int, int>, long> trianglePascal(pascal);
```

Mais là, rien ne va plus. En effet, la bibliothèque standard C++ ne propose pas de fonction de hachage par défaut pour les paires ou les tupples. Afin de rectifier ce point et permettre à l'utilisateur de fournir ses propres fonctions de hachage de manière non intrusive par rapport à la bibliothèque standard, il m'a donc été nécessaire de redéfinir un objet représentant les fonctions de hachage et permettant en particulier de combiner de manière récursive les membres d'une collection.
Ceci a été rendu possible grâce à l'introduction des templates variadiques en C++11.

Cette modification, ainsi que quelques autres, peuvent être constatée dans les sources jointes à ce rapport. On pourra en particulier noter que l'utilisateur peut choisir le type de la table de hachage. Ceci m'a été utile afin d'utiliser des tables de hachage spécifiques, dans la seconde partie de ce projet.

Mémoïsation limitée en mémoire
==============================

Une limite de la mémoïsation
----------------------------

Si les principaux avantages de la mémoïsation face à la programmation dynamique sont sa généricité et sa facilité de mise en place (il n'y a pas à déterminer l'ordre dans lequel effectuer les calculs), l'un de ses inconvénients est que l'on ne peut limiter l'usage de la mémoire aussi facilement.

En particulier, dans l'exemple du triangle de Pascal, on s'aperçoit que la fonction mémoïsée peut consommer une quantité quadratique de mémoire, ce devient excessif pour un ordinateur alors que le temps de calcul reste de l'ordre de quelques minutes. Face au même problème, un algorithme utilisant la programmation dynamique peut n'utiliser qu'une quantité linéaire de mémoire.

Il semblerait donc intéressant de parvenir à limiter l'utilisation de la mémoire par une fonction mémoïsée tout en limitant la perte de performance.

Une politique de cache
----------------------

Afin de restreindre l'utilisation de la mémoire, on va donc fixer une taille maximale à la table de hachage servant à fixer les résultats intermédiaires. Lorsque celle-ci sera pleine, il sera donc nécessaire de supprimer un élément de la table pour en rajouter un nouveau, ce qui se rapproche de l'usage des caches entre le processeur et la mémoire vive. En effet :
- Une donnée présente dans la table est accessible directement, il est sinon nécessaire de la recalculer.
- Le choix des valeurs à chasser de la table est crucial. Si on chasse systématiquement une valeur dont on a besoin pour le calcul suivant, on retombe dans le cas de complexité exponentielle.

Nous allons donc nous inspirer des algorithmes de cache afin de sélectionner la valeur à remplacer.

Différentes stratégies
----------------------

Différentes stratégies de cache peuvent être envisagées et doivent être choisie selon les problèmes.

À l'heure actuelle, seule une stratégie *Least recently used* a été mise en place : il s'agit de supprimer les données utilisées le moins récemment pour le calcul.

Bien qu'elle puisse rencontrer des cas sous optimaux, cette stratégie nous a permis d'obtenir des résultats étonnant dans le cas du triangle de Pascal. En effet, non seulement son utilisation de la mémoire est linéaire, mais son exécution est *plus rapide* que avec une mémoire non limitée. Ce phénomène est du à l'ordre des calculs de cet algorithme, qui se prête particulièrement bien à cette stratégie et n'oblige à refaire aucun calcul. La mémoire utilisée par la table restant bien plus faible, sa gestion est alors plus rapide est permet à la fonction de gagner en performances.

Cette remarque renforce donc encore l'intérêt de comprendre et trouver des algorithmes de sélection efficaces pour les données à supprimer : ils pourraient permettre non seulement de limiter l'usage de la mémoire sans sacrifier trop de performance, mais aussi de simplement gagner encore en performance.

C'est dans cette direction que s'oriente la suite de mon travail, pour la seconde moitié du projet.

Conclusion
==========

À ce stade, j'ai pu développer un outil de mémoïsation fonctionnel, simple d'utilisation et paramétrable par l'utilisateur. Le code de celui-ci sera encore amené à évoluer en fonction de la suite du projet mais ne devrait plus connaître de grandes modification. Je pourrais ainsi bientôt en réaliser une documentation précise et éventuellement le diffuser.

D'autre part, les premières expérimentations sur la mémoïsation limitée en mémoire ont eu des conséquences prometteuses mais le travail n'en est qu'à ses débuts. 
C'est ce sujet qui sera le cœur de mon travail durant la seconde moitié de ce projet, avec pour objectif déterminer si la mémoïsation avec usage limité de la mémoire peut permettre de réaliser des calculs dans des temps acceptables par rapports à ceux obtenus par la programmation dynamique.

Bibliographie
=============

- Documentation de Boost, <http://www.boost.org/doc/libs/1_59_0/doc/html/hash/combine.html>
- François Potier, December 2009, *Functionnal Pearl, Lazy least fixed points in ML*
