# SildeQtUtils
Some classes and GUI controls comon on my QT projects

If any of my projects doesn't compile due a missing header, it should be here.

Clone this repository in the same directory where are the projects, and all wil compile fine.
Meaning: you'll need a structure like this:

```
<YourProjectDir> -> SildeQtUtils
                 -> QMikPPPManager
                 -> BasicSNMP
                 -> <other>
```

NOTE for those who like to use this classes to ther own projects.

Using any class that have a .cpp file, like IPv4Range, need to be compiled along with your project. So add them explicitly in your .pro file. Heather files (.h) are compiled automatically so no need to do so.
