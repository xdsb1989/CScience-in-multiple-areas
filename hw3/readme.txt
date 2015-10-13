Read Me


(A)    Using the windows7 operator system,and compile the program on Dec-Cpp platform.If you can use the Dev-Cpp, open the Dev-Cpp and click file->open project or file->choose the existed C source code.
      If you are the first time to use Dev-Cpp,click tools->complier options->directions,and then add the absolute path C:\MinGW\bin to Binaries,pop it at the first position;add the absolute path C:\MinGW\lib to libraries,pop it at the first position;add the absolute path C:\MinGW\include to C Includes,pop it at the first position(You may have a different path to install the MinGW,using your own path,the "C:\MinGW\" just an example)
	Put the nf-rating,nf-quiz and toy-rating,toy-quiz the four files in the same folder with the source code.
	Click execute->compile&run.After the compiling,the commander window will comes out and then you need to input some code to run the program.


(B)    After the commander window comes out, you can follow the indications and make a choice.Choosing 1 is for toy-rating,choosing 2 is for nf-rating.After the running the program,you can find the output data files in the same folder with the source code.The data files will be refreshed and updated every time when you run the progrom.
      
¡¡¡¡
(C)Output of each algorithm for each input data set
All the following input will be same for both of the algorithms.

1.for the intersection algorithm:
---------------------------------------------------------------------------
please input the choice.
1 is for toy-file data
2 is for nf-file data
choice=:1
the number of customers with supersets:3
the number of customers with subset but not superset:6
number of customers with neither supersets nor subsets:1
the RMSE is:1.0488
---------------------------------------------------------------------------
please input the choice.
1 is for toy-file data
2 is for nf-file data
choice=:2
the number of customers with supersets:2
the number of customers with subset but not superset:163
number of customers with neither supersets nor subsets:0
the RMSE is:1.1230
---------------------------------------------------------------------------
2.For the K-Nearest-Neighbor algorithm:
---------------------------------------------------------------------------
please input the choice.
1 is for toy-file data
2 is for nf-file data
choice=:1
the number of customers with neighbor:9
number of customers with neither supersets nor subsets:1
the RMSE is:1.0488
---------------------------------------------------------------------------
please input the choice.
1 is for toy-file data
2 is for nf-file data
choice=:2
the number of customers with neighbor:165
number of customers with neither supersets nor subsets:0
the RMSE is:1.1643


