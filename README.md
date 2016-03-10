# MakeAmericaGreatAgain
MakeAmericaGreatAgain is part of my home exam in "Designing User Experiences" at Chalmers in Gothenburg.
It is designed to be a critical game about us-americans attitude to elections.

The point is: **Think before you vote!**

My home exam is not about implementing the game, however I decided to implement one of the three minigames included in the game.
There's also a small chance, that i'm gonna implement more.

![HeadCooker](img/office.jpg)


<!-- [toc] -->
## Table of Contents

   * [Compilation and dependencies](#compilation-and-dependencies)
     * [Dependencies](#dependencies)
       * [QT5](#qt5)
     * [Compilation](#compilation)
   * [Goal](#goal)
   * [Content](#content)
     * [TV duells (not planned)](#tv-duells-not-planned)
     * [Phone interview (currently impelmenting this)](#phone-interview-currently-impelmenting-this)
     * [Tweeting stuff (not planned)](#tweeting-stuff-not-planned)

<!-- [toc] -->
## Compilation and dependencies ##

### Dependencies ###

#### QT5 ####
MakeAmericaGreatAgain depents on QT5 so make sure QT5 is installed:

**Linux:** (run as root or via sudo)
``` bash
apt-get install qt5-default qt5-qmake
```

**Windows:**

Check http://www.qt.io/download/

### Compilation ###

Run following in your MakeAmericaGreatAgain directory:
``` bash
mkdir build
cd build
qmake ..
make
```

You can now run MakeAmericaGreatAgain via ```./MakeAmericaGreatAgain``` in your build directory

## Goal
Convince the nation that you'll be a good president...

## Content
The game is based on four minigames:
* TV Duells
* Phone interviews (gonna implement this one)
* Tweeting stuff

Furthermore You sometimes have to react to events, e.g. the NSA can't unlock an iphone, North Korea is pretending to do nuclear bomb tests...

### TV duells (not planned)
You have to fight agains the other candidates in a tv duell.
Therefore you usually don't have to know facts, you should just attack all other candidates and underline that you are very rich, very popular and you're the only one who is self funding his campain, oh almost forgot, you also should lie...

**Sorry** for not implementing this, could also be a lot of fun to play this.

### Phone interview (currently impelmenting this)
Have you ever seen "Who Wants to Be a Millionaire"?
You get questions from the reporter on the other line. For this purpose you're getting 4 possible answeres and you have to choose the "right" one, ha ha ha... just kidding, you have to lie, deny and change the subject.
All interviews are from original interviews.
In most of the questions you can also get to a following question by chosing the "wrong" answere however this answere was then considered as possible and also leads to the following question.
If you're answering a question in a way which makes the following question unpossible, then the moderator changes the subject.

Every answere you make increases or decreases your electometer and therefor your goal to be president.
Act like one of the candidates of the current campaign to get the points.

### Tweeting stuff (not planned)
Exactly what it says, tweet stuff like:
* "It is better to live one day as a lion then 100 years as a sheep" ... thats Mussolini
* "I would like to extend my best wishes to all, even the haters and losers, on this special date, September 11th"
* "You know, look, I’m on a lot of covers. I think maybe more than almost any supermodel. I think more than any supermodel."
