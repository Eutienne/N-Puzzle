# N-PUZZLE


A [sliding puzzle](https://tristanpenman.com/demos/n-puzzle/) solver using the A* search algorithm with several heuristics.

The goal is to solve in a snail pattern, with a target of under 10 seconds for puzzle size 3.
See the [subject](https://github.com/Eutienne/N-Puzzle/blob/master/en.subject.pdf) for more details.

starting 8-puzzle        |  goal 8-puzzle
:---------------------:|:-------------------------:
<img src="image/InitialState.png" alt="drawing" width="200"/>   |   <img src="image/GoalState.png" alt="drawing" width="200"/> 

```
Usage : ./[executeble] [file] [--A_STAR*] [--GREEDY*] [--UNIFORM*]
        [--MANHATTAN / --m**] [--EUCLIDEAN / -e**] [--HAMMING / --h**] [--VERBOSE***]  

positional arguments:
    file                  input file

Optional choice of heuristic and search

* : --A_STAR                use A_star search
    --GREEDY                use greedy search
    --UNIFORM               use uniform search

**: --MANHATTAN, --m        use manhattan heuristic
    --EUCLIDEAN, --e        use euclidean heuristic
    --HAMMING, --h          use manhattan heuristic

***:--VERBOSE               gui visualizer

```
